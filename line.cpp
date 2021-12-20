//======================
//ビルボード設定
//Auther：hamada ryuuga
//======================
#include "line.h"
#include "camera.h"
#include"shadow.h"
#include "prayer.h"
#include"effect.h"

//------------------------------------
// static変数
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// 頂点バッファーへのポインタ
static LINE s_Line[MAX_LINE];								// ポリゴンの構造体
static D3DXVECTOR3 s_RotMove;

//=========================================
// 初期化処理
//=========================================
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;
	//カメラのデータ取得

	// 頂点座標をロック
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < MAX_LINE; i++)
	{

		// 初期化処理
		s_Line[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
		s_Line[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

															// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

		// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
		// テクスチャ座標の設定
		s_Line[i].bUse = false;

		s_Line[i].nType = 0;
		pVtx += 2;
	}
	// 頂点座標をアンロック
	s_pVtxBuff->Unlock();
}

//=========================================
// 終了処理
//=========================================
void UninitLine(void)
{
	// 頂点バッファーの解放
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}



}

//=========================================
// 更新処理
//=========================================
void UpdateLine(void)
{
	//カメラのデータ取得
	CAMERA *pCamera = GetCamera();

	VERTEX_3D* pVtx = NULL;
	// 頂点座標をロック


}

//=========================================
// 描画処理
//=========================================
void DrawLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	DWORD Test = 0;


	pDevice->GetRenderState(D3DRS_ALPHAFUNC, &Test);//より大きい

	for (int i = 0; i < MAX_LINE; i++)
	{
		if (s_Line[i].bUse)
		{
			// ワールドマトリックスの初期化
			// 行列初期化関数(第1引数の行列を単位行列に初期化)
			D3DXMatrixIdentity(&s_Line[i].mtxWorld);

			//ビルボードの設定
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);


			// 位置を反映
			// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, s_Line[i].pos.x, s_Line[i].pos.y, s_Line[i].pos.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&s_Line[i].mtxWorld, &s_Line[i].mtxWorld, &mtxTrans);

			//ライト設定falseにするとライトと食らわない
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ワールド座標行列の設定
			pDevice->SetTransform(D3DTS_WORLD, &s_Line[i].mtxWorld);


		
			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_LINELIST,  i * 2, 1);

		}



	}

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}
//----------------------------------
//セット
//----------------------------------
void SetLine(D3DXVECTOR3 Maxpos, D3DXVECTOR3  Minpos,D3DXVECTOR3 pos )//場所.回転.色.タイプ
{

	PRAYER *pPrayer = GetPrayer();

	// 頂点座標をロック
	VERTEX_3D*pVtx; //頂点へのポインタ
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int i;
	for (i = 0; i < MAX_LINE; i++)
	{
		if (s_Line[i].bUse == false)
		{
	
			// 頂点座標の設定
			pVtx[0].pos = pos + Minpos;
			pVtx[1].pos = pos + Maxpos;


			// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			
			// 頂点カラーの設定
			
			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		


																				 //使ってるかどうか
			s_Line[i].bUse = true;
			break;

		}
		pVtx += 2;
	}

	// 頂点座標をアンロック
	s_pVtxBuff->Unlock();

}

