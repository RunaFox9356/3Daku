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
static LPDIRECT3DTEXTURE9 s_pTextureLine[MAX_TEX] = {}; //テクスチャのポインタ
static LINE s_Line[MAX_LINE];								// ポリゴンの構造体
static D3DXVECTOR3 s_RotMove;

//=========================================
// 初期化処理
//=========================================
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/211.png",
		&s_pTextureLine[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/bullet004.png",
		&s_pTextureLine[1]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_LINE,
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
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);

		// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定

		Settex(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);
		s_Line[i].bUse = false;

		s_Line[i].nType = 0;
		pVtx += 4;
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

	for (int i = 0; i < MAX_TEX; i++)
	{
		if (s_pTextureLine[i] != NULL)
		{
			s_pTextureLine[i]->Release();
			s_pTextureLine[i] = NULL;
		}
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
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_LINE; i++)
	{
		if (s_Line[i].bUse)
		{
			if (s_Line[i].nType == 1)
			{
				s_Line[i].des--;
				s_Line[i].pos.x = s_Line[i].pos.x -= s_Line[i].moveX*BallSpede;
				s_Line[i].pos.z = s_Line[i].pos.z -= s_Line[i].moveZ*BallSpede;
				SetposShadow(s_Line[i].nShadow, s_Line[i].pos);
				SetEffect(s_Line[i].pos, D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.5f), 15.0, 150, EFFECTTYPE_LINE, true, true, false, false);

				/*if (s_Line[i].pos.x < -90.0f)
				{
				s_Line[i].bUse = false;
				DisappearanceShadow(s_Line[i].nShadow);
				}
				if (s_Line[i].pos.x > 90.0f)
				{
				s_Line[i].bUse = false;
				DisappearanceShadow(s_Line[i].nShadow);
				}
				if (s_Line[i].pos.z < -90.0f)
				{
				s_Line[i].bUse = false;
				DisappearanceShadow(s_Line[i].nShadow);
				}
				if (s_Line[i].pos.z > 90.0f)
				{
				s_Line[i].bUse = false;
				DisappearanceShadow(s_Line[i].nShadow);
				}*/

				if (s_Line[i].des < 0)
				{
					s_Line[i].bUse = false;
					DisappearanceShadow(s_Line[i].nShadow);
				}
			}
		}
		pVtx += 4;
	}

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

			//２がついてるやつけすとY方向
			//逆数設定
			s_Line[i].mtxWorld._11 = mtxView._11;
			s_Line[i].mtxWorld._12 = mtxView._21;
			s_Line[i].mtxWorld._13 = mtxView._31;
			//s_Line[i].mtxWorld._21 = mtxView._12;
			//s_Line[i].mtxWorld._22 = mtxView._22;
			//s_Line[i].mtxWorld._23 = mtxView._32;
			s_Line[i].mtxWorld._31 = mtxView._13;
			s_Line[i].mtxWorld._32 = mtxView._23;
			s_Line[i].mtxWorld._33 = mtxView._33;

			// 位置を反映
			// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, s_Line[i].pos.x, s_Line[i].pos.y, s_Line[i].pos.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&s_Line[i].mtxWorld, &s_Line[i].mtxWorld, &mtxTrans);

			//ライト設定falseにするとライトと食らわない
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			if (s_Line[i].nType == 0)
			{
				//Zテスト
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			}
			if (s_Line[i].nType == 1)
			{//アルファテスト
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//でかえれます
																	 //デフォルトはfalseです
				pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);//色せってい
																		   //これは消したいいろを選択します
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);//より大きい
			}


			// ワールド座標行列の設定
			pDevice->SetTransform(D3DTS_WORLD, &s_Line[i].mtxWorld);


			//テクスチャの設定
			pDevice->SetTexture(0, s_pTextureLine[s_Line[i].nType]);
			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);

		}



	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//Aテスト初期化
	pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);//色せってい//これは消したいいろを選択します
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);//より大きい

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//Zテスト初期化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}
//----------------------------------
//セット
//----------------------------------
void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nType)//場所.回転.色.タイプ
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
			// 初期化処理
			s_Line[i].pos = pos;	// 頂点座標
			s_Line[i].rot = rot;	// 回転座標
			s_Line[i].nType = nType;
			s_Line[i].des = 100;
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+10.0f, 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+10.0f, 0.0f, 0.0f);

			// 各頂点の法線の設定(※ベクトルの大きさは1にする必要がある)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			s_Line[i].moveX = sinf(pPrayer->rot.y);
			s_Line[i].moveZ = cosf(pPrayer->rot.y);
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

			s_Line[i].nShadow = SetShadow(s_Line[i].pos, s_Line[i].rot, 1);//場所.回転


																				 //使ってるかどうか
			s_Line[i].bUse = true;
			break;

		}
		pVtx += 4;
	}

	// 頂点座標をアンロック
	s_pVtxBuff->Unlock();

}
//----------------------
//ゲット
//-----------------------
LINE *GetLine(void)
{
	return &s_Line[0];
}
