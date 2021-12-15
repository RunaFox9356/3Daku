//==================
//エフェクト
//autho hamadaryuuga
//==================
#include"effect.h"
#include"paticle.h"
#include "comn.h"

//スタティック変数///スタティックをヘッタに使うなよ？
#define NUM_MAX (16)  

static LPDIRECT3DTEXTURE9 s_pTextureEffect[NUM_MAX] = {}; //テクスチャのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffEffect = NULL; //頂点バッファの設定
static Effect s_aEffect[MAX_EFFECT];


void InitEffect(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/effect000.jpg",
		&s_pTextureEffect[EFFECTTYPE_LINE]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle1.png",
		&s_pTextureEffect[EFFECTTYPE_MP]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle2.png",
		&s_pTextureEffect[EFFECTTYPE_MP2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle3.png",
		&s_pTextureEffect[EFFECTTYPE_MP3]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle4.png",
		&s_pTextureEffect[EFFECTTYPE_MP4]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle5.png",
		&s_pTextureEffect[EFFECTTYPE_MP5]);
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-27.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-29.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-28.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK3]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-26.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK4]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-32.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK5]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-33.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK6]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-37.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK7]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-36.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK8]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-35.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK9]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-38.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK10]);
	

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,//ここ頂点フォーマット
		&s_pVtxBuffEffect,
		NULL);

	VERTEX_3D*pVtx; //頂点へのポインタ
	//頂点バッファをロックし頂点情報へのポインタを取得
	s_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//初期化忘れない
		s_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.1f, 0.0f);	// 回転座標
		s_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aEffect[nCntEffect].nLife = 0;
		s_aEffect[nCntEffect].bUse = false;
		s_aEffect[nCntEffect].bSiz = false;
		s_aEffect[nCntEffect].fRadeius = 0;
		s_aEffect[nCntEffect].Trigger = 0;   //種類
		s_aEffect[nCntEffect].nType = EFFECTTYPE_LINE;//
		s_aEffect[nCntEffect].nDivisionX = 1;
		s_aEffect[nCntEffect].nDivisionY = 1;
		s_aEffect[nCntEffect].nDivisionMAX = 1;
		s_aEffect[nCntEffect].speed = 1;
		SetNorotpos(pVtx,
			s_aEffect[nCntEffect].pos.x - MAX_RECIPEEFFECT - s_aEffect[nCntEffect].fRadeius,
			s_aEffect[nCntEffect].pos.x + MAX_RECIPEEFFECT + s_aEffect[nCntEffect].fRadeius,
			s_aEffect[nCntEffect].pos.y - MAX_RECIPEEFFECT - s_aEffect[nCntEffect].fRadeius,
			s_aEffect[nCntEffect].pos.y + MAX_RECIPEEFFECT + s_aEffect[nCntEffect].fRadeius,
			0.0f,
			0.0f);
		//頂点座標
	
		//頂点カラーの設定
		pVtx[0].col = s_aEffect[nCntEffect].col;
		pVtx[1].col = s_aEffect[nCntEffect].col;
		pVtx[2].col = s_aEffect[nCntEffect].col;
		pVtx[3].col = s_aEffect[nCntEffect].col;

		//テクスチャの座標設定
		
		Settex(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4; //頂点ポイントを四つ進む
	}

	//頂点バッファをアンロック
	s_pVtxBuffEffect->Unlock();
}
void UninitEffect(void)
{
	//
	for (int i = 0; i < NUM_MAX; i++)
	{
		if (s_pTextureEffect[i] != NULL)
		{
			s_pTextureEffect[i]->Release();
			s_pTextureEffect[i] = NULL;
		}
	}
	

	//頂点バッファの破棄
	if (s_pVtxBuffEffect != NULL)
	{
		s_pVtxBuffEffect->Release();
		s_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_3D*pVtx; //頂点へのポインタ
					//頂点バッファをアンロック
	s_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (s_aEffect[nCntEffect].bUse)
		{
			switch (s_aEffect[nCntEffect].nType)
			{
				//魔法陣回転速度
			case EFFECTTYPE_MP:
			case EFFECTTYPE_CLOCK:
				if (s_aEffect[nCntEffect].easeInspeed <= 120)//最高速度制限
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}		
				if (s_aEffect[nCntEffect].bRot)//＜-これは　立てるか床にするか
				{	//イージング　二乗してる　D3DX_PI / Xの数を回転速度に二乗してます
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 3100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{	
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 1100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}	
				break;
			case EFFECTTYPE_MP2:
			case EFFECTTYPE_CLOCK2:
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 3100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 1000.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			case EFFECTTYPE_MP3:
			case EFFECTTYPE_CLOCK3:
			
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}	
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 3100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 1200.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			case EFFECTTYPE_MP4:
			case EFFECTTYPE_CLOCK4:
			
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 3100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 800.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			case EFFECTTYPE_MP5:
			case EFFECTTYPE_CLOCK5:
			
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}	
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 5100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 900.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			case EFFECTTYPE_CLOCK6:
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z -= SeteaseIn((D3DX_PI / 2100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 900.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			default:
				break;
			}
		
			if (s_aEffect[nCntEffect].rot.y > D3DX_PI)
				{
					s_aEffect[nCntEffect].rot.y -= D3DX_PI * 2;
				}
				if (s_aEffect[nCntEffect].rot.y < -D3DX_PI)
				{
					s_aEffect[nCntEffect].rot.y += D3DX_PI * 2;

				}
			switch (s_aEffect[nCntEffect].nType)
			{
			case EFFECTTYPE_LINE:
				

				SetNorotpos(pVtx,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					0.0f,
					0.0f);

				//寿命が尽きたとき
				s_aEffect[nCntEffect].fRadeius-=0.1f;
				if (s_aEffect[nCntEffect].fRadeius <= 0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				break;
			case EFFECTTYPE_MP:
			case EFFECTTYPE_MP2:
			case EFFECTTYPE_MP3:
			case EFFECTTYPE_MP4:
			case EFFECTTYPE_MP5:
	

				s_aEffect[nCntEffect].nLife--;
				//魔法陣を大きく表示する
				if (s_aEffect[nCntEffect].nLife<= s_aEffect[nCntEffect].nMaxLife&& s_aEffect[nCntEffect].nLife >= s_aEffect[nCntEffect].nMaxLife -60)
				{
					s_aEffect[nCntEffect].fRadeius += 1.0f;
				}

				//最後に小さくする
				if (s_aEffect[nCntEffect].nLife <= 60 && s_aEffect[nCntEffect].nLife >= 40)
				{
					s_aEffect[nCntEffect].fRadeius += 1.5f;
				}
				if (s_aEffect[nCntEffect].nLife <= 40 && s_aEffect[nCntEffect].nLife >= 0)
				{
					s_aEffect[nCntEffect].fRadeius -= 5.0f;
				}
				if (s_aEffect[nCntEffect].fRadeius <= 0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}


				//アニメーションテクスチャ設定
				if ((s_aEffect[nCntEffect].nCounterAnim % s_aEffect[nCntEffect].speed) == 0)//ここで速度調整
				{
					s_aEffect[nCntEffect].nPatternAnim++;

					//表示座標を更新
					Settex(pVtx
						, 1.0f / s_aEffect[nCntEffect].nDivisionX * (s_aEffect[nCntEffect].nPatternAnim % (s_aEffect[nCntEffect].nDivisionX ))
						, 1.0f / s_aEffect[nCntEffect].nDivisionX *(s_aEffect[nCntEffect].nPatternAnim % (s_aEffect[nCntEffect].nDivisionX )) + 1.0f / s_aEffect[nCntEffect].nDivisionX
						, 1.0f / s_aEffect[nCntEffect].nDivisionY * (s_aEffect[nCntEffect].nPatternAnim / (s_aEffect[nCntEffect].nDivisionY))
						, 1.0f / s_aEffect[nCntEffect].nDivisionY * (s_aEffect[nCntEffect].nPatternAnim / ( s_aEffect[nCntEffect].nDivisionY) + 1.0f / s_aEffect[nCntEffect].nDivisionY* s_aEffect[nCntEffect].nDivisionY));
				if (s_aEffect[nCntEffect].nLife <=0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				}
				if (s_aEffect[nCntEffect].nLife <= s_aEffect[nCntEffect].nMaxLife&& s_aEffect[nCntEffect].nLife >= s_aEffect[nCntEffect].nMaxLife - 10)
				{
					s_aEffect[nCntEffect].fRadeius += 1.0f;
				}
				if (s_aEffect[nCntEffect].nLife <= s_aEffect[nCntEffect].nMaxLife&& s_aEffect[nCntEffect].nLife >= s_aEffect[nCntEffect].nMaxLife - 30)
				{//サイズを+３０する
					s_aEffect[nCntEffect].fRadeius += 1.0f;
				}
				//最後に小さくする
				if (s_aEffect[nCntEffect].nLife <= 60 && s_aEffect[nCntEffect].nLife >= 40)
				{
					s_aEffect[nCntEffect].fRadeius += 1.5f;
				}
				if (s_aEffect[nCntEffect].nLife <= 40 && s_aEffect[nCntEffect].nLife >= 0)
				{
					s_aEffect[nCntEffect].fRadeius -= 5.0f;
				}
				if (s_aEffect[nCntEffect].fRadeius <= 0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				s_aEffect[nCntEffect].nCounterAnim++;
			
				break;
			case EFFECTTYPE_CLOCK:
			case EFFECTTYPE_CLOCK2:
			case EFFECTTYPE_CLOCK3:
			case EFFECTTYPE_CLOCK4:
			case EFFECTTYPE_CLOCK5:
			case EFFECTTYPE_CLOCK6:
			case EFFECTTYPE_CLOCK7:
			case EFFECTTYPE_CLOCK8:
			case EFFECTTYPE_CLOCK9:
			case EFFECTTYPE_CLOCK10:

				s_aEffect[nCntEffect].nLife--;
				if (s_aEffect[nCntEffect].nLife <= 0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				//最後に小さくする
				if (s_aEffect[nCntEffect].nLife <= 60 && s_aEffect[nCntEffect].nLife >= 40)
				{
					s_aEffect[nCntEffect].col.a -= 0.05f;
				}
				if (s_aEffect[nCntEffect].nLife <= 40 && s_aEffect[nCntEffect].nLife >= 0)
				{
					s_aEffect[nCntEffect].col.a -= 0.05f;
				}
				
			default:
				break;

			}
			if (!s_aEffect[nCntEffect].bRot)
			{
				//設定
				SetNorotpos(pVtx,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					+1.0f,
					+1.0f,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius);
			}
			else
			{
				//設定
				SetNorotpos(pVtx,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					+1.0f,
					+1.0f);

			}
			if (s_aEffect[nCntEffect].bCol)
			{
				if (s_aEffect[nCntEffect].col.r == 1.0f)
				{
					s_aEffect[nCntEffect].col.g += 0.02f;    //前FF0000
				}
				if (s_aEffect[nCntEffect].col.r >= 1.0f)
				{
					s_aEffect[nCntEffect].col.b -= 0.04f;    //前FF00FF

				}
				if (s_aEffect[nCntEffect].col.g >= 1.0f)
				{
					s_aEffect[nCntEffect].col.r -= 0.02f;    //前FFFF00
				}

				if (s_aEffect[nCntEffect].col.r <= 0.0f)
				{
					s_aEffect[nCntEffect].col.b += 0.05f;    //前00FF00
				}

				if (s_aEffect[nCntEffect].col.b >= 1.0f)
				{
					s_aEffect[nCntEffect].col.g -= 0.05f;    //前00FFFF
				}

				if (s_aEffect[nCntEffect].col.g <= 0.0f)
				{
					s_aEffect[nCntEffect].col.r += 0.05f;    //前0000FF
				}
				
				
			}
			else
			{
				if (s_aEffect[nCntEffect].col.a >= 0.0f&&s_aEffect[nCntEffect].col.a <= 0.5f)
				{
					s_aEffect[nCntEffect].col.a += 0.005f;
				}
			}
			//頂点カラーの設定
			pVtx[0].col = s_aEffect[nCntEffect].col;
			pVtx[1].col = s_aEffect[nCntEffect].col;
			pVtx[2].col = s_aEffect[nCntEffect].col;
			pVtx[3].col = s_aEffect[nCntEffect].col;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	s_pVtxBuffEffect->Unlock();
}



void DrawEffect(void)
{
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxTrans, mtxRot;	// 計算用マトリックス

		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (s_aEffect[nCntEffect].bUse)
		{

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, s_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			// ワールドマトリックスの初期化
			// 行列初期化関数(第1引数の行列を単位行列に初期化)
			D3DXMatrixIdentity(&s_aEffect[nCntEffect].mtxWorld);
			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			switch (s_aEffect[nCntEffect].nType)
			{
			case EFFECTTYPE_LINE:
				//逆数設定
				s_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
				s_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
				s_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
				s_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
				s_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
				s_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
				s_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
				s_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
				s_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;
				break;

			default:
				break;
			}
			if (s_aEffect[nCntEffect].bZbf)
			{	//設定falseにするZ起動
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);//Zテスト
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			}
			if (!s_aEffect[nCntEffect].bZbf)
			{	//設定falseにするZ起動
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);//Zテスト
				// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
				D3DXMatrixRotationYawPitchRoll(&mtxRot, s_aEffect[nCntEffect].rot.y, s_aEffect[nCntEffect].rot.x, s_aEffect[nCntEffect].rot.z);
				// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
				D3DXMatrixMultiply(&s_aEffect[nCntEffect].mtxWorld, &s_aEffect[nCntEffect].mtxWorld, &mtxRot);
			}
			if (s_aEffect[nCntEffect].bAbf)
			{

				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//Aテスト
																	 //デフォルトはfalseです
				pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000000);//色せってい
																		   //これは消したいいろを選択します
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);//より大きい
			}
		
			// 位置を反映
			// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, s_aEffect[nCntEffect].pos.x, s_aEffect[nCntEffect].pos.y, s_aEffect[nCntEffect].pos.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&s_aEffect[nCntEffect].mtxWorld, &s_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			//ライト設定falseにするとライトと食らわない
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			
			// ワールド座標行列の設定
			pDevice->SetTransform(D3DTS_WORLD, &s_aEffect[nCntEffect].mtxWorld);

			//テクスチャの設定
			pDevice->SetTexture(0, s_pTextureEffect[s_aEffect[nCntEffect].nType]);
			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, s_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//かりんぐ設定初期化

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//Zテスト初期化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//Aテスト初期化

	//加算合成初期化
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife, EFFECTTYPE nType, bool bZbf, bool bAbf, bool bCol,bool bRot)
{
	int nCntEffect;
	VERTEX_3D*pVtx; //頂点へのポインタ
	s_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (s_aEffect[nCntEffect].bUse == false)
		{

			//エフェクトが使用されてない場合
			s_aEffect[nCntEffect].fRadeius = fRadeius;
			s_aEffect[nCntEffect].pos = pos;
			s_aEffect[nCntEffect].bAbf = bAbf;
			s_aEffect[nCntEffect].bZbf = bZbf;
			s_aEffect[nCntEffect].bCol = bCol;
			s_aEffect[nCntEffect].nType = nType;
			s_aEffect[nCntEffect].nCounterAnim = 0;
			s_aEffect[nCntEffect].nPatternAnim = 0;
			s_aEffect[nCntEffect].nMaxLife = nLife;
			s_aEffect[nCntEffect].bRot = bRot;
		
			//アニメーション最大数
			s_aEffect[nCntEffect].nDivisionMAX = s_aEffect[nCntEffect].nDivisionX*s_aEffect[nCntEffect].nDivisionY;

			//テクスチャ設定
			Settex(pVtx, 0.0f, 1.0f / s_aEffect[nCntEffect].nDivisionX, 0.0f, 1.0f / s_aEffect[nCntEffect].nDivisionY);

			if (!s_aEffect[nCntEffect].bRot)
			{
				// 回転座標
				s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
				//設定
				SetNorotpos(pVtx,
					-fRadeius,
					+fRadeius,
					+1.0f,
					+1.0f,
					-fRadeius,
					+fRadeius);
			}
			else
			{
				s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//設定
				SetNorotpos(pVtx,
					-fRadeius,
					+fRadeius,
					-fRadeius,
					+fRadeius,
					+1.0f,
					+1.0f);
					
			}
			//ムーブ
			s_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//イージング
			s_aEffect[nCntEffect].easeInspeed = 0;

			//生存時間
			s_aEffect[nCntEffect].nLife = nLife;

			//使用チェック
			s_aEffect[nCntEffect].bUse = true;

			//カラー
			s_aEffect[nCntEffect].col = col;
			switch (s_aEffect[nCntEffect].nType)
			{
			case EFFECTTYPE_LINE:
				s_aEffect[nCntEffect].nDivisionX = 1;
				s_aEffect[nCntEffect].nDivisionY = 1;
				s_aEffect[nCntEffect].speed = 1;
				break;
			case EFFECTTYPE_CLOCK6:
				s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 3.0f);
			case EFFECTTYPE_CLOCK7:
				s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 3.1f);
				break;
			default:
				s_aEffect[nCntEffect].nDivisionX = 1;
				s_aEffect[nCntEffect].nDivisionY = 1;
				s_aEffect[nCntEffect].speed = 5;
				break;
			}
			//頂点カラーの設定
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	s_pVtxBuffEffect->Unlock();
	
}
