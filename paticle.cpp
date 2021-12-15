//＝＝＝＝＝＝＝＝＝＝＝＝＝
//effect.cpp
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "paticle.h"
#include "model.h"
#include "input.h"
#include <stdlib.h>
#include <assert.h>

//グローバル変数宣言
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;
static LPDIRECT3DTEXTURE9	s_pTexture[NUM_PARTICLE] = {};
PARTICLE s_aParticle[MAX_PARTICLE];



//＝＝＝＝＝＝＝＝＝＝＝＝＝
//PARTICLEの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/pipo-btleffect040.png",
		&s_pTexture[PARTICLETYPE_LIGHTNING]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Sprite-0001-Sheet.png",
		&s_pTexture[PARTICLETYPE_KITUNE]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/pipo-gwspinitem017.png",
		&s_pTexture[PARTICLETYPE_OUKAN]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Title102.png",
		&s_pTexture[PARTICLETYPE_MERA]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Flare001.jpg",
		&s_pTexture[EFFECTTYPE_FLARE2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Flare001.jpg",
		&s_pTexture[EFFECTTYPE_FLARE3]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Glitter000.jpg",
		&s_pTexture[EFFECTTYPE_GLITTER]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Glitter000.jpg",
		&s_pTexture[EFFECTTYPE_AWA]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		s_aParticle[nCntParticle].pos = {};											// 位置
		s_aParticle[nCntParticle].posPop = {};										// 発生位置
		s_aParticle[nCntParticle].rot = {};// 向き
		s_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			// カラー
		s_aParticle[nCntParticle].fRadius = 0.0f;									// 半径
		s_aParticle[nCntParticle].speed = 0;										// 移動速度
		s_aParticle[nCntParticle].nLife = 0;											// 寿命																// 発生時間
		s_aParticle[nCntParticle].bUse = false;
		s_aParticle[nCntParticle].nMaxLife = 0;				//最大ライフ
		s_aParticle[nCntParticle].nParticleNumber = 0;		//パーティクルの番号
		s_aParticle[nCntParticle].nCounterAnim = 0;			//アニメーションカウント
		s_aParticle[nCntParticle].nPatternAnim = 0;			//動きのカウント
		s_aParticle[nCntParticle].nDivisionMAX = 0;			//何分割するかのカウント
		s_aParticle[nCntParticle].nDivisionY = 0;				//Y何分割するかのカウント
		s_aParticle[nCntParticle].nDivisionX = 0;
		s_aParticle[nCntParticle].fWidth = 0.0f;				//幅//X何分割するかのカウント
		s_aParticle[nCntParticle].fLarge = 0.0f;				//まわす幅//頂点座標の設定
		s_aParticle[nCntParticle].fHeight = 0.0f;				//高さ
		s_aParticle[nCntParticle].fRadius = 0.0f;				//半径
		s_aParticle[nCntParticle].fAngle = 0.0f;				//角度
		s_aParticle[nCntParticle].fLength = 0.0f;				//長さ
		s_aParticle[nCntParticle].fAttenuation = 0.0f;			//減衰


		pVtx[0].pos = s_aParticle[nCntParticle].pos;
		pVtx[1].pos = s_aParticle[nCntParticle].pos;
		pVtx[2].pos = s_aParticle[nCntParticle].pos;
		pVtx[3].pos = s_aParticle[nCntParticle].pos;

		//各頂点の法線の設定　※　ベクトルの大きさは1にする必要がある
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		s_aParticle[nCntParticle].speed = 1;
		s_aParticle[nCntParticle].nDivisionMAX = 1;
		s_aParticle[nCntParticle].nDivisionX = 1;
		s_aParticle[nCntParticle].nDivisionY = 1;
		Settex(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);
		pVtx += 4;
	}

	//頂点バッファのアンロック
	s_pVtxBuff->Unlock();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//PARTICLEの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void UninitParticle(void)
{
	//テクスチャの破棄
	for (int nCntParticle = 0; nCntParticle < NUM_PARTICLE; nCntParticle++)
	{
		if (s_pTexture[nCntParticle] != NULL)
		{
			s_pTexture[nCntParticle]->Release();
			s_pTexture[nCntParticle] = NULL;
		}
	}

	//頂点バッファの破壊
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//PARTICLEの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void UpdateParticle(void)
{
	//float X, Y;//データ計測用
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//位置を更新
		s_aParticle[nCntParticle].pos.x += s_aParticle[nCntParticle].move.x;
		s_aParticle[nCntParticle].pos.y += s_aParticle[nCntParticle].move.y;
		s_aParticle[nCntParticle].pos.z += s_aParticle[nCntParticle].move.z;

		//==========================
		//PARTICLEの種類
		//==========================
		switch (s_aParticle[nCntParticle].type)
		{
		case PARTICLETYPE_LIGHTNING:	//かみなり
			s_aParticle[nCntParticle].col.g -= 0.0075f;
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fWidth -= 0.002f;
			s_aParticle[nCntParticle].fHeight -= 0.002f;
			s_aParticle[nCntParticle].fAngle -= 30.0f;
			s_aParticle[nCntParticle].fRadius += s_aParticle[nCntParticle].fAngle * (D3DX_PI * 2);
			s_aParticle[nCntParticle].fAttenuation = 250.0f;
			s_aParticle[nCntParticle].fAttenuation -= 30.0f;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));
			s_aParticle[nCntParticle].move.y -= tanf(D3DX_PI) * s_aParticle[nCntParticle].fRadius / 2;
			s_aParticle[nCntParticle].move.z = -cosf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));
			break;
		case PARTICLETYPE_KITUNE:	//狐火	/*動き方は回転をしながら上昇*/
			s_aParticle[nCntParticle].col.g -= 0.0075f;
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fWidth -= 0.002f;
			s_aParticle[nCntParticle].fHeight -= 0.002f;
			s_aParticle[nCntParticle].fAngle -= 30.0f;
			s_aParticle[nCntParticle].fRadius += s_aParticle[nCntParticle].fAngle * (D3DX_PI * 2);
			s_aParticle[nCntParticle].fAttenuation = 250.0f;
			s_aParticle[nCntParticle].fAttenuation -= 30.0f;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation))) * 3;
			s_aParticle[nCntParticle].move.y -= tanf(D3DX_PI) * s_aParticle[nCntParticle].fRadius / 10;
			s_aParticle[nCntParticle].move.z = -cosf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));		
			break;
		case PARTICLETYPE_OUKAN:	//王冠	/*動き方は回転をしながら上昇*/
			s_aParticle[nCntParticle].col.g -= 0.0075f;
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fWidth -= 0.002f;
			s_aParticle[nCntParticle].fHeight -= 0.002f;
			s_aParticle[nCntParticle].fAngle -= 30.0f;
			s_aParticle[nCntParticle].fRadius += s_aParticle[nCntParticle].fAngle * (D3DX_PI * 2);
			s_aParticle[nCntParticle].fAttenuation = 250.0f;
			s_aParticle[nCntParticle].fAttenuation -= 30.0f;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation))) ;
			s_aParticle[nCntParticle].move.y -= tanf(D3DX_PI) * s_aParticle[nCntParticle].fRadius / 10;
			s_aParticle[nCntParticle].move.z = -cosf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));	
			break;
		case PARTICLETYPE_MERA:	//一枚絵	/*動き方は回転をしながら上昇*/
			s_aParticle[nCntParticle].col.g -= 0.0075f;
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fWidth -= 0.002f;
			s_aParticle[nCntParticle].fHeight -= 0.002f;
			s_aParticle[nCntParticle].fAngle -= 30.0f;
			s_aParticle[nCntParticle].fRadius += s_aParticle[nCntParticle].fAngle * (D3DX_PI * 2);
			s_aParticle[nCntParticle].fAttenuation = 250.0f;
			s_aParticle[nCntParticle].fAttenuation -= 30.0f;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation))) * 3;
			s_aParticle[nCntParticle].move.y -= tanf(D3DX_PI) * s_aParticle[nCntParticle].fRadius / 2;
			s_aParticle[nCntParticle].move.z = -cosf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));			
			break;
		case EFFECTTYPE_FLARE2: // フレア３と併用する場合は事前にposX + 20.0f程加算する
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fAngle += 10.0f;
			s_aParticle[nCntParticle].fAttenuation = 50.0f;
			s_aParticle[nCntParticle].fAttenuation += 30.0f;
			s_aParticle[nCntParticle].fLarge = 6;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI)-(s_aParticle[nCntParticle].fAngle / s_aParticle[nCntParticle].fAttenuation)) * s_aParticle[nCntParticle].fLarge;
			s_aParticle[nCntParticle].move.z = cosf((D3DX_PI)-(s_aParticle[nCntParticle].fAngle / s_aParticle[nCntParticle].fAttenuation)) * s_aParticle[nCntParticle].fLarge;
			s_aParticle[nCntParticle].nDivisionX = 1;
			s_aParticle[nCntParticle].nDivisionY = 1;
			if (s_aParticle[nCntParticle].col.r == 1.0f)
			{
				s_aParticle[nCntParticle].col.g += 0.02f;    //前FF0000
			}

			if (s_aParticle[nCntParticle].col.g >= 1.0f)
			{
				s_aParticle[nCntParticle].col.r -= 0.02f;    //前FFFF00
			}

			if (s_aParticle[nCntParticle].col.r <= 0.0f)
			{
				s_aParticle[nCntParticle].col.b += 0.05f;    //前00FF00
			}

			if (s_aParticle[nCntParticle].col.b >= 1.0f)
			{
				s_aParticle[nCntParticle].col.g -= 0.05f;    //前00FFFF
			}

			if (s_aParticle[nCntParticle].col.g <= 0.0f)
			{
				s_aParticle[nCntParticle].col.r += 0.05f;    //前0000FF
			}

			if (s_aParticle[nCntParticle].col.r >= 1.0f)
			{
				s_aParticle[nCntParticle].col.b -= 0.04f;    //前FF00FF
			}
			break;
			//フレア3                /フレア２と併用する場合は事前にposX - 20.0f程減算する/
		case EFFECTTYPE_FLARE3:
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fAngle += 10.0f;
			s_aParticle[nCntParticle].fAttenuation = 50.0f;
			s_aParticle[nCntParticle].fAttenuation += 30.0f;
			s_aParticle[nCntParticle].fLarge = 6;
		
			s_aParticle[nCntParticle].move.x = sinf((D3DX_PI)-(s_aParticle[nCntParticle].fAngle / s_aParticle[nCntParticle].fAttenuation)) * s_aParticle[nCntParticle].fLarge;
			s_aParticle[nCntParticle].move.z = -cosf((D3DX_PI)-(s_aParticle[nCntParticle].fAngle / s_aParticle[nCntParticle].fAttenuation)) * s_aParticle[nCntParticle].fLarge;
			s_aParticle[nCntParticle].nDivisionX = 1;
			s_aParticle[nCntParticle].nDivisionY = 1;
			if (s_aParticle[nCntParticle].col.r == 1.0f)
			{
				s_aParticle[nCntParticle].col.g += 0.02f;    //前FF0000
			}

			if (s_aParticle[nCntParticle].col.g >= 1.0f)
			{
				s_aParticle[nCntParticle].col.r -= 0.02f;    //前FFFF00
			}

			if (s_aParticle[nCntParticle].col.r <= 0.0f)
			{
				s_aParticle[nCntParticle].col.b += 0.05f;    //前00FF00
			}

			if (s_aParticle[nCntParticle].col.b >= 1.0f)
			{
				s_aParticle[nCntParticle].col.g -= 0.05f;    //前00FFFF
			}

			if (s_aParticle[nCntParticle].col.g <= 0.0f)
			{
				s_aParticle[nCntParticle].col.r += 0.05f;    //前0000FF
			}

			if (s_aParticle[nCntParticle].col.r >= 1.0f)
			{
				s_aParticle[nCntParticle].col.b -= 0.04f;    //前FF00FF
			}
			break;
			//光が少ないキラキラ
		case EFFECTTYPE_GLITTER:

			s_aParticle[nCntParticle].fAngle += 10.0f;
			s_aParticle[nCntParticle].fAttenuation = 50.0f;
			s_aParticle[nCntParticle].fAttenuation += 30.0f;
			s_aParticle[nCntParticle].fLarge = 6;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI * nCntParticle / 2) - (s_aParticle[nCntParticle].fAngle / s_aParticle[nCntParticle].fAttenuation) + rand() % 2) * s_aParticle[nCntParticle].fLarge;
			s_aParticle[nCntParticle].move.z = cosf((D3DX_PI * nCntParticle / 2) - (s_aParticle[nCntParticle].fAngle / s_aParticle[nCntParticle].fAttenuation) + rand() % 2) * s_aParticle[nCntParticle].fLarge;
			s_aParticle[nCntParticle].nDivisionX = 1;
			s_aParticle[nCntParticle].nDivisionY = 1;
			if (s_aParticle[nCntParticle].col.r == 1.0f)
				{
					s_aParticle[nCntParticle].col.g += 0.02f;    //前FF0000
				}

				if (s_aParticle[nCntParticle].col.g >= 1.0f)
				{
					s_aParticle[nCntParticle].col.r -= 0.02f;    //前FFFF00
				}

				if (s_aParticle[nCntParticle].col.r <= 0.0f)
				{
					s_aParticle[nCntParticle].col.b += 0.05f;    //前00FF00
				}

				if (s_aParticle[nCntParticle].col.b >= 1.0f)
				{
					s_aParticle[nCntParticle].col.g -= 0.05f;    //前00FFFF
				}

				if (s_aParticle[nCntParticle].col.g <= 0.0f)
				{
					s_aParticle[nCntParticle].col.r += 0.05f;    //前0000FF
				}

				if (s_aParticle[nCntParticle].col.r >= 1.0f)
				{
					s_aParticle[nCntParticle].col.b -= 0.04f;    //前FF00FF
				}
			break;
			case EFFECTTYPE_AWA:
				// 位置の算出
				s_aParticle[nCntParticle].pos.x =s_aParticle[nCntParticle].pos.x + (float)(-(int)(s_aParticle[nCntParticle].posPop.x / 2.0f) + rand() % ((int)(s_aParticle[nCntParticle].posPop.x) + 1));
				s_aParticle[nCntParticle].pos.y =s_aParticle[nCntParticle].pos.y + (float)(-(int)(s_aParticle[nCntParticle].posPop.y / 2.0f) + rand() % ((int)(s_aParticle[nCntParticle].posPop.y) + 1));
				s_aParticle[nCntParticle].pos.z =s_aParticle[nCntParticle].pos.z + (float)(-(int)(s_aParticle[nCntParticle].posPop.z / 2.0f) + rand() % ((int)(s_aParticle[nCntParticle].posPop.z) + 1));

				// 半径の算出
				s_aParticle[nCntParticle].fRadius = (float)(rand() % ((int)(s_aParticle[nCntParticle].fRadius * 100.0f) + 1)) / 100.0f;

				// 寿命の算出
				//s_aParticle[nCntParticle].nLife = rand() % (s_aParticle[nCntParticle].nLife + 1) + 1;

				// 移動速度の算出
				s_aParticle[nCntParticle].fSpeed = (float)(rand() % ((int)(s_aParticle[nCntParticle].fSpeed * 1000.0f) + 1)) / 1000.0f;

				// 移動方向の算出
				s_aParticle[nCntParticle].rot.x = (((int)((D3DX_PI * 2) *s_aParticle[nCntParticle].rot.x * 100.0f) / 2) - (rand() % ((int)((D3DX_PI * 2) *s_aParticle[nCntParticle].rot.x * 100.0f) + 1))) / 100.0f;
				s_aParticle[nCntParticle].rot.y = (((int)((D3DX_PI * 2) *s_aParticle[nCntParticle].rot.y * 100.0f) / 2) - (rand() % ((int)((D3DX_PI * 2) *s_aParticle[nCntParticle].rot.y * 100.0f) + 1))) / 100.0f;
				s_aParticle[nCntParticle].rot.z = 0.0f;

				//ムーブ更新																									// 移動量の算出
				s_aParticle[nCntParticle].move.z = sinf(s_aParticle[nCntParticle].rot.x) * cosf(s_aParticle[nCntParticle].rot.y) * s_aParticle[nCntParticle].fSpeed;
				s_aParticle[nCntParticle].move.x = sinf(s_aParticle[nCntParticle].rot.x) * sinf(s_aParticle[nCntParticle].rot.y) * s_aParticle[nCntParticle].fSpeed;
				s_aParticle[nCntParticle].move.y = cosf(s_aParticle[nCntParticle].rot.x) * s_aParticle[nCntParticle].fSpeed;
				s_aParticle[nCntParticle].pos += s_aParticle[nCntParticle].move;


				break;
		default:	//上記以外
			break;
		}

		//PARTICLEの寿命
		s_aParticle[nCntParticle].nLife--;

		if (s_aParticle[nCntParticle].nLife == 0)
		{
			DeleteParticle(nCntParticle);
		}
		// 頂点情報へのポインタを生成
		VERTEX_3D *pVtx;
		// 頂点バッファをロックし、頂点情報へのポインタを取得
		s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntParticle;	// 頂点データのポインタを4つ分進める
		//テクスチャ設定
		s_aParticle[nCntParticle].col.a -= 1.0f / s_aParticle[nCntParticle].nMaxLife;
		s_aParticle[nCntParticle].nCounterAnim++;
		if ((s_aParticle[nCntParticle].nCounterAnim % s_aParticle[nCntParticle].speed) == 0)//ここで速度調整
		{
			s_aParticle[nCntParticle].nPatternAnim = (s_aParticle[nCntParticle].nPatternAnim + 1) % s_aParticle[nCntParticle].nDivisionMAX;

			//表示座標を更新
			Settex(pVtx,
				1.0f / s_aParticle[nCntParticle].nDivisionX * (s_aParticle[nCntParticle].nPatternAnim % (s_aParticle[nCntParticle].nDivisionX))
				, 1.0f / s_aParticle[nCntParticle].nDivisionX *(s_aParticle[nCntParticle].nPatternAnim % (s_aParticle[nCntParticle].nDivisionX)) + 1.0f / s_aParticle[nCntParticle].nDivisionX
				, 1.0f / s_aParticle[nCntParticle].nDivisionY * (s_aParticle[nCntParticle].nPatternAnim / (s_aParticle[nCntParticle].nDivisionY))
				, 1.0f / s_aParticle[nCntParticle].nDivisionY * (s_aParticle[nCntParticle].nPatternAnim / (s_aParticle[nCntParticle].nDivisionY) + 1.0f / s_aParticle[nCntParticle].nDivisionY* s_aParticle[nCntParticle].nDivisionY));
		}

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-s_aParticle[nCntParticle].fWidth, s_aParticle[nCntParticle].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(s_aParticle[nCntParticle].fWidth, s_aParticle[nCntParticle].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-s_aParticle[nCntParticle].fWidth, -s_aParticle[nCntParticle].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(s_aParticle[nCntParticle].fWidth, -s_aParticle[nCntParticle].fHeight, 0.0f);

		//頂点カラー
		pVtx[0].col = s_aParticle[nCntParticle].col;
		pVtx[1].col = s_aParticle[nCntParticle].col;
		pVtx[2].col = s_aParticle[nCntParticle].col;
		pVtx[3].col = s_aParticle[nCntParticle].col;

		//頂点バッファのアンロック
		s_pVtxBuff->Unlock();
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//PARTICLEの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void DrawParticle(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans, mtxView;				//計算用マトリックス

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		switch (s_aParticle[nCntParticle].type)
		{

		case EFFECTTYPE_AWA:
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		default:
			//加算合成
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		}
		if (s_aParticle[nCntParticle].bUse)
		{
			//ワールドマトリックスを初期化
			D3DXMatrixIdentity(&s_aParticle[nCntParticle].mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を設定
			s_aParticle[nCntParticle].mtxWorld._11 = mtxView._11;
			s_aParticle[nCntParticle].mtxWorld._12 = mtxView._21;
			s_aParticle[nCntParticle].mtxWorld._13 = mtxView._31;
			s_aParticle[nCntParticle].mtxWorld._21 = mtxView._12;
			s_aParticle[nCntParticle].mtxWorld._22 = mtxView._22;
			s_aParticle[nCntParticle].mtxWorld._23 = mtxView._32;
			s_aParticle[nCntParticle].mtxWorld._31 = mtxView._13;
			s_aParticle[nCntParticle].mtxWorld._32 = mtxView._23;
			s_aParticle[nCntParticle].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, s_aParticle[nCntParticle].pos.x, s_aParticle[nCntParticle].pos.y, s_aParticle[nCntParticle].pos.z);
			D3DXMatrixMultiply(&s_aParticle[nCntParticle].mtxWorld, &s_aParticle[nCntParticle].mtxWorld, &mtxTrans);


			//ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//Zバッファに関わらず描画
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);


			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//Aテスト
																 //デフォルトはfalseです
			pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000000);//色せってい
																	   //これは消したいいろを選択します
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);//より大きい


			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &s_aParticle[nCntParticle].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, s_pTexture[s_aParticle[nCntParticle].type]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntParticle * 4,
				2);

			//ライトを有効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Zテストの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//テクスチャを引き継がない
	pDevice->SetTexture(0, NULL);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//PARTICLEの設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight, PARTICLETYPE type,int nLife)
{
	VERTEX_3D * pVtx = NULL;
	int nCntParticle;
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (!s_aParticle[nCntParticle].bUse)
		{
			// 頂点情報へのポインタを生成
			VERTEX_3D *pVtx;
			// 頂点バッファをロックし、頂点情報へのポインタを取得
			s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * nCntParticle;	// 頂点データのポインタを4つ分進める
			s_aParticle[nCntParticle].pos = pos;
			s_aParticle[nCntParticle].move = move;
			s_aParticle[nCntParticle].col = col;
			s_aParticle[nCntParticle].type = type;
			s_aParticle[nCntParticle].fWidth = fWidth;
			s_aParticle[nCntParticle].fHeight = fHeight;
			s_aParticle[nCntParticle].fAngle = 5.0f;
			s_aParticle[nCntParticle].nLife = nLife;
			s_aParticle[nCntParticle].nMaxLife = s_aParticle[nCntParticle].nLife;
			switch (s_aParticle[nCntParticle].type)
			{

			case PARTICLETYPE_LIGHTNING:	//かみなり
				s_aParticle[nCntParticle].nDivisionX = 8;
				s_aParticle[nCntParticle].nDivisionY = 1;
				s_aParticle[nCntParticle].speed = 5;
				break;
			case PARTICLETYPE_KITUNE:	//狐火	/*動き方は回転をしながら上昇*/
				s_aParticle[nCntParticle].nDivisionX = 5;
				s_aParticle[nCntParticle].nDivisionY = 1;
				s_aParticle[nCntParticle].speed = 5;			
				break;
			case PARTICLETYPE_OUKAN:	//王冠	/*動き方は回転をしながら上昇*/
				s_aParticle[nCntParticle].nDivisionX = 5;
				s_aParticle[nCntParticle].nDivisionY = 4;
				s_aParticle[nCntParticle].speed = 10;
				break;
			case PARTICLETYPE_MERA:	//一枚絵	/*動き方は回転をしながら上昇*/
				
				s_aParticle[nCntParticle].nDivisionX = 1;
				s_aParticle[nCntParticle].nDivisionY = 1;
				s_aParticle[nCntParticle].speed = 1;
				break;
			case EFFECTTYPE_AWA:
				s_aParticle[nCntParticle].posPop = D3DXVECTOR3(105.0f, 105.0f, 105.0f);
				s_aParticle[nCntParticle].nDivisionX = 1;
				s_aParticle[nCntParticle].nDivisionY = 1;
				s_aParticle[nCntParticle].speed = 10;
				s_aParticle[nCntParticle].fSpeed = 0.1f;
				break;
			default:	//上記以外
				break;
			}
			Settex(pVtx, 0.0f, 1.0f / s_aParticle[nCntParticle].nDivisionX, 0.0f, 1.0f / s_aParticle[nCntParticle].nDivisionY);
			s_aParticle[nCntParticle].nDivisionMAX = s_aParticle[nCntParticle].nDivisionX*s_aParticle[nCntParticle].nDivisionY;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-s_aParticle[nCntParticle].fWidth, s_aParticle[nCntParticle].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(s_aParticle[nCntParticle].fWidth, s_aParticle[nCntParticle].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-s_aParticle[nCntParticle].fWidth, -s_aParticle[nCntParticle].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(s_aParticle[nCntParticle].fWidth, -s_aParticle[nCntParticle].fHeight, 0.0f);

			//頂点カラー
			pVtx[0].col = s_aParticle[nCntParticle].col;
			pVtx[1].col = s_aParticle[nCntParticle].col;
			pVtx[2].col = s_aParticle[nCntParticle].col;
			pVtx[3].col = s_aParticle[nCntParticle].col;

			//頂点バッファのアンロック
			s_pVtxBuff->Unlock();

			s_aParticle[nCntParticle].bUse = true;

			break;
		}
	
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//サブPARTICLEの設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void SubSetParticle(int nSubParticle, PARTICLETYPE type)
{

}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//PARTICLEの削除
//＝＝＝＝＝＝＝＝＝＝＝＝＝
void DeleteParticle(int nParticle)
{
	s_aParticle[nParticle].bUse = false;
	s_aParticle[nParticle].move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	s_aParticle[nParticle].fAngle = 0.0f;
	s_aParticle[nParticle].fRadius = 0.0f;
	s_aParticle[nParticle].fAttenuation = 0.0f;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝
//PARTICLEの取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝
PARTICLE *GetParticle(void)
{
	return &s_aParticle[0];
}