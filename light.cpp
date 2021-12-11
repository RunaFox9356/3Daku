//=======================
//ライト設定
//Auther：hamada ryuuga
//=======================

#include"light.h"

#define MAXLIT (3) 
static D3DLIGHT9  s_light[MAXLIT];

//----------------------------
//初期化処理
//----------------------------
void InitLighe(void)
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAXLIT];
	//メモリクリア
	ZeroMemory(&s_light[0], sizeof(s_light));

	//0番目ライト
	s_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vecDir[0] = D3DXVECTOR3(0.2f, -0.7f, -0.4f);

	//1番目ライト
	s_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vecDir[1] = D3DXVECTOR3(0.2f, -0.7f, 0.4f);

	//2番目ライト
	s_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vecDir[2] = D3DXVECTOR3(0.2f, 0.7f, -0.4f);

	for (int i = 0; i < MAXLIT; i++)
	{
		//ライトタイプ
		s_light[i].Type = D3DLIGHT_DIRECTIONAL;

		//ライトベクトル長さ１にする
		D3DXVec3Normalize(&vecDir[i], &vecDir[i]);
		s_light[i].Direction = vecDir[i];

		pDevice->SetLight(i, &s_light[i]);

		pDevice->LightEnable(i, TRUE);
	}

	
}

//----------------------------
//終了処理
//----------------------------
void UninitLighe(void)
{
}

//----------------------------
//更新処理
//----------------------------
void UpdateLighe(void)
{
}
