//======================
//円柱＆円メッシュ設定
//Auther：hamada ryuuga
//======================
#include "cylinder.h"
#include "input.h"

//------------------------------------
// static変数
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// 頂点バッファーへのポインタ上半分
static LPDIRECT3DTEXTURE9 s_pTextureCylinder = {}; //テクスチャのポインタ
static LPDIRECT3DINDEXBUFFER9 s_pIdxBuff = {};  //インデックスバッファ



static CYLINDER s_Cylinder;	// ポリゴンの構造体
static int n,o;

#define MAX_SIZCYLINDER (10.0f)
#define MAX_CYLINDER (20)

//=========================================
// 初期化処理
//=========================================
void InitCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 初期化処理
	s_Cylinder.pos = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	s_Cylinder.rot = D3DXVECTOR3(0.0f, 0.0f,0.0f );	// 回転座標

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/11112.png",
		&s_pTextureCylinder);

	//初期化
	s_Cylinder.xsiz = MAX_CYLINDER;
	s_Cylinder.zsiz = MAX_CYLINDER;
	s_Cylinder.ysiz = MAX_CYLINDER;

	//辺の頂点数
	s_Cylinder.X = s_Cylinder.xsiz + 1;//1多い数字
	s_Cylinder.Z = s_Cylinder.zsiz + 1;//1多い数字
	s_Cylinder.Y = s_Cylinder.ysiz + 1;

							   //頂点数
	s_Cylinder.Vtx = s_Cylinder.X* s_Cylinder.Z;//頂点数を使ってるよ

									//インデックス数
	s_Cylinder.Index = (2 * s_Cylinder.X * s_Cylinder.zsiz + 2 * (s_Cylinder.zsiz - 1));

	s_Cylinder.por = s_Cylinder.Index - 2;
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * s_Cylinder.Vtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * s_Cylinder.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&s_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点座標をロック
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float rotDiffZ = (D3DX_PI *  2 / s_Cylinder.zsiz);

		for (int Z = 0; Z <= s_Cylinder.zsiz; Z++)
		{
			float rotDiffX = (D3DX_PI / s_Cylinder.xsiz);
			float rotZ = rotDiffZ * Z - D3DX_PI * 0.5f;

			for (int X = 0; X <= s_Cylinder.xsiz; X++)
			{
				float rotX = rotDiffX * X;

				//球（）
				pVtx[X + Z * s_Cylinder.X].pos = D3DXVECTOR3((sinf(rotX) * sinf(rotZ) * MAX_SIZCYLINDER),
															cosf(rotX)*MAX_SIZCYLINDER,
															sinf(rotX) *cosf(rotZ)*MAX_SIZCYLINDER);
				pVtx[X + Z * s_Cylinder.X].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[X + Z * s_Cylinder.X].tex = D3DXVECTOR2((float)X, (float)Z);

			
				//法線
				float fNor = atan2f(pVtx[X + Z * s_Cylinder.X].pos.x, pVtx[X + Z * s_Cylinder.X].pos.z);
				pVtx[X + Z * s_Cylinder.X].nor = D3DXVECTOR3(sinf(fNor), 0.0f, cosf(fNor));
				D3DXVec3Normalize(&pVtx[X + Z * s_Cylinder.X].nor, &pVtx[X + Z * s_Cylinder.X].nor);	
				//Ｙの角度の設定
				//float fRot = (D3DX_PI*2.0f) / s_Cylinder.xsiz * X;
				//円柱
				//pVtx[X + Z * s_Cylinder.X].pos = D3DXVECTOR3((sinf(fRot)*5),Z*MAX_SIZCYLINDER, (cosf(fRot) * 5));
			}	
			
			
		}
	
	// 頂点座標をアンロック
	s_pVtxBuff->Unlock();

	//インデックスバッファのロック
	WORD* pIdx;
	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < s_Cylinder.zsiz; z++)
	{
		int linetop = z * (s_Cylinder.X * 2 + 2);
		for (int x = 0; x < s_Cylinder.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = x + (z * s_Cylinder.X);
			pIdx[nIdxData] = pIdx[nIdxData + 1] + s_Cylinder.X;
			//これは俺が考えた戒め
			//pIdx[(x*2+1+((z*Cylinder.Z +1))*z)] = x+(z*Cylinder.X);
			//pIdx[(x*2 + ((z*Cylinder.Z)+3)*z)] = (x+ (Cylinder.Z)) + (z*Cylinder.X);	
		}
		//縮退ポリゴン設定
		if (z < s_Cylinder.xsiz - 1)
		{
			pIdx[s_Cylinder.X * 2 + 0 + linetop] = s_Cylinder.xsiz + s_Cylinder.X*z;
			pIdx[s_Cylinder.X * 2 + 1 + linetop] = s_Cylinder.X * 2 + s_Cylinder.X * z;
		}

	}

	// 頂点座標をアンロック
	s_pIdxBuff->Unlock();



}

//=========================================
// 終了処理
//=========================================
void UninitCylinder(void)
{
	// 頂点バッファーの解放
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pTextureCylinder != NULL)
	{
		s_pTextureCylinder->Release();
		s_pTextureCylinder = NULL;
	}
	if (s_pIdxBuff != NULL)
	{
		s_pIdxBuff->Release();
		s_pIdxBuff = NULL;
	}

	
	
	
}

//=========================================
// 更新処理
//=========================================
void UpdateCylinder(void)
{	// 頂点座標をロック

	//モデルの切り替え
	if (GetKeyboardTrigger(DIK_N) && s_Cylinder.xsiz < MAX_CYLINDER)
	{

		s_Cylinder.zsiz++;
		s_Cylinder.xsiz++;
		SetCylinder(s_Cylinder.xsiz, s_Cylinder.zsiz);
	}

	//モデルの切り替え
	if (GetKeyboardTrigger(DIK_M) && s_Cylinder.xsiz > 1)
	{
		s_Cylinder.zsiz--;
		s_Cylinder.xsiz--;
		SetCylinder(s_Cylinder.xsiz, s_Cylinder.zsiz);
	}
}

//=========================================
// 描画処理
//=========================================
void DrawCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
							// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(&s_Cylinder.mtxWorld);

	// 向きを反映
	// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Cylinder.rot.y, s_Cylinder.rot.x, s_Cylinder.rot.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&s_Cylinder.mtxWorld, &s_Cylinder.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, s_Cylinder.pos.x, s_Cylinder.pos.y, s_Cylinder.pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&s_Cylinder.mtxWorld, &s_Cylinder.mtxWorld, &mtxTrans);

	// ワールド座標行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &s_Cylinder.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファ設定
	pDevice->SetIndices(s_pIdxBuff);
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, s_pTextureCylinder);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, s_Cylinder.Vtx, 0, s_Cylinder.por);
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}
//----------------
//メッシュ設定
//----------------
void SetCylinder(int X, int Z)//場所.回転
{
	UninitCylinder();
	InitCylinder();
}
//----------------------
//ゲット(構造体)
//-----------------------
CYLINDER *GetCylinder(void)
{
	return &s_Cylinder;
}