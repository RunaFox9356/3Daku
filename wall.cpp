//=======================
//壁設定
//Auther：hamada ryuuga
//=======================
#include "wall.h"
#include"mesh.h"

//------------------------------------
// ポリゴンの構造体を定義
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 rot;	// 回転座標
	D3DXMATRIX mtxWorld;// ワールドマトリックス
	bool bUse; //使ってるか

} WALL;


//------------------------------------
// static変数
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// 頂点バッファーへのポインタ
static LPDIRECT3DTEXTURE9 s_pTextureWall = {}; //テクスチャのポインタ
static WALL s_Wall[MAX_WALL];								// ポリゴンの構造体

//=========================================
// 初期化処理
//=========================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/sky_00290.png",
		&s_pTextureWall);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// 頂点座標をロック
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < MAX_WALL; i++)
	{

		// 初期化処理
		s_Wall[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
		s_Wall[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f,  100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f,  0.0f, 0.0f);

		// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		s_Wall[i].bUse = false;

		pVtx += 4;
	}
	// 頂点座標をアンロック
	s_pVtxBuff->Unlock();
}

//=========================================
// 終了処理
//=========================================
void UninitWall(void)
{
	// 頂点バッファーの解放
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pTextureWall != NULL)
	{
		s_pTextureWall->Release();
		s_pTextureWall = NULL;
	}
}

//=========================================
// 更新処理
//=========================================
void UpdateWall(void)
{

}

//=========================================
// 描画処理
//=========================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

									//減算合成


	for (int i = 0; i < MAX_WALL; i++)
	{
		if (s_Wall[i].bUse)
		{

			// ワールドマトリックスの初期化
			// 行列初期化関数(第1引数の行列を単位行列に初期化)
			D3DXMatrixIdentity(&s_Wall[i].mtxWorld);

			// 向きを反映
			// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Wall[i].rot.y, s_Wall[i].rot.x, s_Wall[i].rot.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&s_Wall[i].mtxWorld, &s_Wall[i].mtxWorld, &mtxRot);

			// 位置を反映
			// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, s_Wall[i].pos.x, s_Wall[i].pos.y, s_Wall[i].pos.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&s_Wall[i].mtxWorld, &s_Wall[i].mtxWorld, &mtxTrans);

			// ワールド座標行列の設定
			pDevice->SetTransform(D3DTS_WORLD, &s_Wall[i].mtxWorld);
			//テクスチャの設定
			pDevice->SetTexture(0, s_pTextureWall);
			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
		}
	}
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

}
//----------------------------------
//セット
//----------------------------------
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)//場所.回転.色
{	// 頂点座標をロック
	VERTEX_3D*pVtx; //頂点へのポインタ
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int i;
	for (i = 0; i < MAX_WALL; i++)
	{
		if (s_Wall[i].bUse == false)
		{
			// 初期化処理
			s_Wall[i].pos = pos;	// 頂点座標
			s_Wall[i].rot = rot;	// 回転座標
			
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3( - 100.0f, 100.0f,0.0f );
			pVtx[1].pos = D3DXVECTOR3( + 100.0f, 100.0f,0.0f );
			pVtx[2].pos = D3DXVECTOR3( - 100.0f, 0.0f,	0.0f );
			pVtx[3].pos = D3DXVECTOR3( + 100.0f, 0.0f,  0.0f );

			// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの設定
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			s_Wall[i].bUse = true;
			break;

		}
		pVtx += 4;
	}

	// 頂点座標をアンロック
	s_pVtxBuff->Unlock();

}
