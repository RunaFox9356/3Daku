//======================
//メッシュ設定
//Auther：hamada ryuuga
//======================
#include "mesh.h"
#include "input.h"



//------------------------------------
// static変数
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// 頂点バッファーへのポインタ
static LPDIRECT3DTEXTURE9 s_pTextureMesh = {}; //テクスチャのポインタ
static LPDIRECT3DINDEXBUFFER9 s_pIdxBuff = {};  //インデックスバッファ
static MESH s_Mesh;								// ポリゴンの構造体



//=========================================
// 初期化処理
//=========================================
void InitMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 初期化処理
	s_Mesh.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_Mesh.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/sky_00290.png",
		&s_pTextureMesh);
	//初期化
	s_Mesh.xsiz = MAX_MESH;
	s_Mesh.zsiz = MAX_MESH;
	
	//辺の頂点数
	s_Mesh.X = s_Mesh.xsiz + 1;//1多い数字
	s_Mesh.Z = s_Mesh.zsiz + 1;//1多い数字

	//頂点数
	s_Mesh.Vtx = s_Mesh.X* s_Mesh.Z;//頂点数を使ってるよ

	//インデックス数
	s_Mesh.Index = (2 * s_Mesh.X * s_Mesh.zsiz + 2 *(s_Mesh.zsiz - 1));

	s_Mesh.por = s_Mesh.Index - 2;
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * s_Mesh.Vtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * s_Mesh.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&s_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点座標をロック
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	for (int i = 0; i < s_Mesh.Vtx; i++)
	{
		float posx = ((i % s_Mesh.X)-1.0f);
		float posz = ((i / s_Mesh.Z)- 1.0f)*-1.0f;
		
		float texU = 1.0f / s_Mesh.xsiz*(i % s_Mesh.X);
		float texV = 1.0f / s_Mesh.zsiz*(i / s_Mesh.Z);
		//めっしゅを真ん中にする補正
		s_Mesh.pos = D3DXVECTOR3(-(posx - 1)*MAX_SIZMESH / 2, 0.0f, -posz * MAX_SIZMESH / 2);

		pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZMESH , 0.0f/D3DX_PI, posz * MAX_SIZMESH);

		// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// 頂点カラーの設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// 頂点座標をアンロック
	s_pVtxBuff->Unlock();

	//インデックスバッファのロック
	WORD* pIdx;
	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < s_Mesh.zsiz; z++)
	{
		int linetop = z * (s_Mesh.X * 2 +2);
		for (int x = 0; x < s_Mesh.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = x + (z * s_Mesh.X);
			pIdx[nIdxData] = pIdx[nIdxData + 1] + s_Mesh.X;
			//pIdx[(x*2+1+((z*Mesh.Z +1))*z)] = x+(z*Mesh.X);
			//pIdx[(x*2 + ((z*Mesh.Z)+3)*z)] = (x+ (Mesh.Z)) + (z*Mesh.X);	
		}
		//縮退ポリゴン設定
		if (z < s_Mesh.xsiz - 1)
			{
				pIdx[s_Mesh.X * 2+ 0 + linetop] =  s_Mesh.xsiz + s_Mesh.X*z;
				pIdx[s_Mesh.X * 2 + 1 + linetop] = s_Mesh.X * 2 + s_Mesh.X * z;
			}
		
 	}

	// 頂点座標をアンロック
	s_pIdxBuff->Unlock();

}

//=========================================
// 終了処理
//=========================================
void UninitMesh(void)
{
	// 頂点バッファーの解放
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pTextureMesh != NULL)
	{
		s_pTextureMesh->Release();
		s_pTextureMesh = NULL;
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
void UpdateMesh(void)
{	
	//モデルの切り替え
	if (GetKeyboardTrigger(DIK_N))
	{
		
		s_Mesh.zsiz++;
		s_Mesh.xsiz++;
		SetMesh(s_Mesh.xsiz, s_Mesh.zsiz);
	}

	//モデルの切り替え
	if (GetKeyboardTrigger(DIK_M)&& s_Mesh.xsiz > 1)
	{
		s_Mesh.zsiz--;
		s_Mesh.xsiz--;
		SetMesh(s_Mesh.xsiz, s_Mesh.zsiz);
	}
}

//=========================================
// 描画処理
//=========================================
void DrawMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(&s_Mesh.mtxWorld);

	// 向きを反映
	// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Mesh.rot.y, s_Mesh.rot.x, s_Mesh.rot.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&s_Mesh.mtxWorld, &s_Mesh.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, s_Mesh.pos.x, s_Mesh.pos.y, s_Mesh.pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&s_Mesh.mtxWorld, &s_Mesh.mtxWorld, &mtxTrans);

	// ワールド座標行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &s_Mesh.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファ設定
	pDevice->SetIndices(s_pIdxBuff);
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, s_pTextureMesh);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, s_Mesh.Vtx,0, s_Mesh.por);
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}
//----------------
//メッシュ設定
//----------------
void SetMesh(int X ,int Z)//場所.回転
{
	// 頂点バッファーの解放
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pIdxBuff != NULL)
	{
		s_pIdxBuff->Release();
		s_pIdxBuff = NULL;
	}
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 初期化処理
	s_Mesh.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_Mesh.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

	//初期化
	s_Mesh.xsiz = X;
	s_Mesh.zsiz = Z;

	//辺の頂点数
	s_Mesh.X = s_Mesh.xsiz + 1;//1多い数字
	s_Mesh.Z = s_Mesh.zsiz + 1;//1多い数字

	s_Mesh.Vtx = s_Mesh.X* s_Mesh.Z;//頂点数を使ってるよ

	//インデックス数
	s_Mesh.Index = (2 * s_Mesh.X * s_Mesh.zsiz + 2 * (s_Mesh.zsiz - 1));

	s_Mesh.por = s_Mesh.Index - 2;
	 //頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * s_Mesh.Vtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * s_Mesh.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&s_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点座標をロック
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	for (int i = 0; i < s_Mesh.Vtx; i++)
	{
		float posx = ((i % s_Mesh.X) - 1.0f);
		float posz = ((i / s_Mesh.Z) - 1.0f)*-1.0f;

		float texU = 1.0f / s_Mesh.xsiz*(i % s_Mesh.X);
		float texV = 1.0f / s_Mesh.zsiz*(i / s_Mesh.Z);

		//めっしゅを真ん中にする補正
		s_Mesh.pos = D3DXVECTOR3(-(posx-1)*MAX_SIZMESH / 2, 0.0f, -posz * MAX_SIZMESH / 2);
		//pos
		pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZMESH, 0.0f, posz * MAX_SIZMESH);

		// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		
		// 頂点カラーの設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// 頂点座標をアンロック
	s_pVtxBuff->Unlock();

	//インデックスバッファのロック
	WORD* pIdx;
	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < s_Mesh.zsiz; z++)
	{
		int linetop = z * (s_Mesh.X * 2 + 2);
		for (int x = 0; x < s_Mesh.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = x + (z * s_Mesh.X);
			pIdx[nIdxData] = pIdx[nIdxData + 1] + s_Mesh.X;
			//pIdx[(x*2+1+((z*Mesh.Z +1))*z)] = x+(z*Mesh.X);
			//pIdx[(x*2 + ((z*Mesh.Z)+3)*z)] = (x+ (Mesh.Z)) + (z*Mesh.X);	
		}
		//縮退ポリゴン設定
		if (z < s_Mesh.xsiz - 1)
		{
			pIdx[s_Mesh.X * 2 + 0 + linetop] = s_Mesh.xsiz + s_Mesh.X*z;
			pIdx[s_Mesh.X * 2 + 1 + linetop] = s_Mesh.X * 2 + s_Mesh.X * z;
		}
	}

	// 頂点座標をアンロック
	s_pIdxBuff->Unlock();
}
//----------------------
//ゲット(構造体)
//-----------------------
MESH *GetMesh(void)
{
	return &s_Mesh;
}