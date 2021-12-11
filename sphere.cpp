//**************************************************************************************************
//
// 円柱描画処理(splhere.cpp)
// Auther：唐﨑結斗
//
//**************************************************************************************************

//***************************************************************************
// インクルード
//***************************************************************************
#include "main.h"
#include "sphere.h"
#include"file.h"

//***************************************************************************
// マクロ定義
//***************************************************************************
#define CYLINDER_X_BLOCK2			(10)						// X方向のブロック数
#define CYLINDER_Z_BLOCK2			(10)						// Z方向のブロック数

// ブロック数 + 1
#define MESHBLOCK_X_ADD_ONE		(CYLINDER_X_BLOCK2 + 1)
#define MESHBLOCK_Z_ADD_ONE		(CYLINDER_Z_BLOCK2 + 1)

// 1列頂点数
#define CYLINDER_RHINE_VTX_ONE		(CYLINDER_X_BLOCK2 * 2 + 2)

// 円柱の頂点数
#define MAX_CYLINDER_VERTEX			(MESHBLOCK_X_ADD_ONE * MESHBLOCK_Z_ADD_ONE)		

// 円柱のポリゴン数
#define MAX_CYLINDER_POLYGON		((CYLINDER_X_BLOCK2 * CYLINDER_Z_BLOCK2 * 2) + (((CYLINDER_Z_BLOCK2 - 1) * 2) * 2))

// 円柱のインデックス数
#define MAX_CYLINDER_INDEX			((CYLINDER_RHINE_VTX_ONE * CYLINDER_Z_BLOCK2) + ((CYLINDER_Z_BLOCK2 - 1) * 2))	

// 円柱サイズ
#define MAX_CYLINDER_SIZE			(10.0f)

// 円柱の半径の長さ
#define CYLINDER_RADIUS				(50.0f)


//***************************************************************************
// グローバル変数
//***************************************************************************
static LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffSplhere = NULL;		// 頂点バッファへのポインタ
static LPDIRECT3DTEXTURE9			g_pTextureSplhere = NULL;		// テクスチャへのポインタ
static LPDIRECT3DINDEXBUFFER9		g_pIdzBuffSplhere = NULL;		// インデックスバッファへのポインタ
static Sphere						g_Splhere;						// 円柱情報の取得

																	//---------------------------------------------------------------------------
																	// 円柱初期化処理
																	//---------------------------------------------------------------------------
void InitSphere(void)
{
	g_Splhere.pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);



	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_CYLINDER_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSplhere,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MAX_CYLINDER_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdzBuffSplhere,
		NULL);

	// 頂点情報の取得
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffSplhere->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV < CYLINDER_Z_BLOCK2 + 1; nCntV++)
	{
		for (int nCntH = 0; nCntH < CYLINDER_X_BLOCK2 + 1; nCntH++)
		{// 変数宣言
			float fRot = ((D3DX_PI * 2.0f) / CYLINDER_X_BLOCK2) * nCntH;		// 角度の設定

																				// 頂点座標の設定
			pVtx[0].pos.x = sinf(fRot) * CYLINDER_RADIUS;
			pVtx[0].pos.z = cosf(fRot) * CYLINDER_RADIUS;
			pVtx[0].pos.y = MAX_CYLINDER_SIZE * nCntV;

			// 各頂点の法線の設定(*ベクトルの大きさは1にする必要がある)
			pVtx[0].nor.x = pVtx[0].pos.x;
			pVtx[0].nor.z = pVtx[0].pos.z;
			pVtx[0].nor.y = 0.0f;
			D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f / CYLINDER_X_BLOCK2 * nCntH, 1.0f / CYLINDER_X_BLOCK2 * nCntV);

			pVtx++;
		}
	}

	// インデックスバッファをロック
	WORD *pIdx;
	g_pIdzBuffSplhere->Lock(0, 0, (void**)&pIdx, 0);

	// インデックスの設定
	for (int nCntZ = 0; nCntZ < CYLINDER_Z_BLOCK2; nCntZ++)
	{
		for (int nCntX = 0; nCntX < MESHBLOCK_X_ADD_ONE; nCntX++)
		{// 変数宣言
			int nIndexZ = nCntX * 2 + (nCntZ * (MESHBLOCK_Z_ADD_ONE * 2 + 2));
			int nIndexX = nCntX * 2 + 1 + (nCntZ * (MESHBLOCK_Z_ADD_ONE * 2 + 2));
			int Z = nCntX + (MESHBLOCK_X_ADD_ONE * nCntZ + (MESHBLOCK_X_ADD_ONE));
			int X = nCntX + (MESHBLOCK_X_ADD_ONE * nCntZ);

			// インデックス数の設定
			pIdx[nIndexZ] = Z;
			pIdx[nIndexX] = X;
		}

		if (nCntZ != CYLINDER_Z_BLOCK2)
		{// 最大数以下の時
		 // 変数宣言
			int X = MESHBLOCK_X_ADD_ONE * 2 + (nCntZ * (MESHBLOCK_Z_ADD_ONE * 2 + 2));
			int Z = MESHBLOCK_X_ADD_ONE * 2 + 1 + (nCntZ * (MESHBLOCK_Z_ADD_ONE * 2 + 2));
			int nIndexX = CYLINDER_X_BLOCK2 + (nCntZ * MESHBLOCK_X_ADD_ONE);
			int nIndexZ = CYLINDER_RHINE_VTX_ONE + (nCntZ * MESHBLOCK_Z_ADD_ONE);

			// インデックス数
			pIdx[X] = nIndexX;
			pIdx[Z] = nIndexZ;
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffSplhere->Unlock();

	// 頂点バッファのアンロック
	g_pIdzBuffSplhere->Unlock();
}

//---------------------------------------------------------------------------
// 円柱終了処理
//---------------------------------------------------------------------------
void UninitSphere(void)
{
	// テクスチャの破棄	  
	if (g_pTextureSplhere != NULL)
	{
		g_pTextureSplhere->Release();
		g_pTextureSplhere = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffSplhere != NULL)
	{
		g_pVtxBuffSplhere->Release();
		g_pVtxBuffSplhere = NULL;
	}

	// インデックスバッファの破棄	  
	if (g_pIdzBuffSplhere != NULL)
	{
		g_pIdzBuffSplhere->Release();
		g_pIdzBuffSplhere = NULL;
	}
}

//---------------------------------------------------------------------------
// 円柱更新処理
//---------------------------------------------------------------------------
void UpdateSphere(void)
{

}

//---------------------------------------------------------------------------
// 円柱描画処理
//---------------------------------------------------------------------------
void DrawSphere(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9	pDevice = GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;			// 計算用マトリックス

													// ワールドマトリックスの初期化
													// 行列初期化関数(第一引数の[行列]を[単位行列]に初期化)
	D3DXMatrixIdentity(&g_Splhere.mtxWorld);

	// 向きの反映
	// 行列回転関数 (第一引数に[ヨー(y)ピッチ(x)ロール(z)]方向の回転行列を作成)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Splhere.rot.y, g_Splhere.rot.x, g_Splhere.rot.z);

	// 行列掛け算関数 (第二引数 * 第三引数を第一引数に格納)
	D3DXMatrixMultiply(&g_Splhere.mtxWorld, &g_Splhere.mtxWorld, &mtxRot);

	// 位置を反映
	// 行列移動関数 (第一引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, g_Splhere.pos.x, g_Splhere.pos.y, g_Splhere.pos.z);
	D3DXMatrixMultiply(&g_Splhere.mtxWorld, &g_Splhere.mtxWorld, &mtxTrans);						// 行列掛け算関数

																									// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Splhere.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSplhere, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdzBuffSplhere);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSplhere);

	// 円柱描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_CYLINDER_VERTEX, 0, MAX_CYLINDER_POLYGON);

	// テクスチャの解除
	pDevice->SetTexture(0, NULL);
}