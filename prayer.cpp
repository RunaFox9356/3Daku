//======================================
//プレイヤー処理
//Auther：hamada ryuuga
//======================================

#include<stdio.h>
#include "Prayer.h"
#include "input.h"
#include"camera.h"
#include"shadow.h"
#include"kitune.h"
#include"file.h"
#include"mesh.h"
#include"paticle.h"
#include"ken.h"
#include"effect.h"

//マクロ
#define Attenuation	(0.5f)		//減衰係数
#define Spede	(1.0f)			//スピード
#define WIDTH (10.0f)			//モデルの半径
#define MAX_PRAYER (16)			//最大数
//------------------------------------
// static変数
//------------------------------------
static PRAYER Prayerpolygon[MAX_PRAYER];	// ポリゴンの構造体
static int s_nNanba, s_nSet, s_nTime;//現在使用してるやつと最大数
static D3DXVECTOR3 mystery;
//=========================================
// 初期化処理
//=========================================
void InitPrayer(void)
{
	//カメラのデータ取得
	CAMERA *pCamera;
	pCamera = GetCamera();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_PRAYER; i++)
	{
		// 初期化処理
		Prayerpolygon[i].s_pBuffPrayer = NULL;
		Prayerpolygon[i].s_Prayer = 0;
		Prayerpolygon[i].s_pVtxMesh = NULL;			//縦　　　　　　　　　　//横
		Prayerpolygon[i].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
		Prayerpolygon[i].consumption = 0.0f;
		Prayerpolygon[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
		Prayerpolygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標
		Prayerpolygon[i].nShadow = 0;
		Prayerpolygon[i].bUse = false;
		Prayerpolygon[i].bMystery = false;
		Prayerpolygon[i].ModelMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		Prayerpolygon[i].ModelMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	}
	s_nNanba = 0;
	s_nSet = 0;
	s_nTime = 0;
}

//=========================================
// 終了処理
//=========================================
void UninitPrayer(void)
{
	for (int i = 0; i < MAX_PRAYER; i++)
	{
		// 頂点バッファーの解放
		if (Prayerpolygon[i].s_pVtxMesh != NULL)
		{
			Prayerpolygon[i].s_pVtxMesh->Release();
			Prayerpolygon[i].s_pVtxMesh = NULL;
		}
		if (Prayerpolygon[i].s_pBuffPrayer != NULL)
		{
			Prayerpolygon[i].s_pBuffPrayer->Release();
			Prayerpolygon[i].s_pBuffPrayer = NULL;
		}
	}

}

//=========================================
// 更新処理
//=========================================
void UpdatePrayer(void)
{
	//カメラのデータ取得
	CAMERA *pCamera;
	pCamera = GetCamera();
	float consumption = 0;

	if (GetKeyboardPress(DIK_1))
	{//1押したときパーティクル
		SetParticle(Prayerpolygon[s_nNanba].pos - D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_KITUNE, LIGHTNINGLIFE);
	}
	if (GetKeyboardPress(DIK_2))
	{//２押したときパーティクル
		SetParticle(Prayerpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_LIGHTNING, KITUNELIFE);
	}
	if (GetKeyboardPress(DIK_3))
	{//３押したときパーティクル
		SetParticle(Prayerpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_OUKAN, OUKANLIFE);
	}
	if (GetKeyboardPress(DIK_4))
	{//４押したときパーティクル

		SetParticle(Prayerpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_MERA, MERALIFE);
	}
	if (GetKeyboardPress(DIK_7))
	{//魔法陣発動//0.0のカラーのやつは枠線
	}
	if (GetKeyboardTrigger(DIK_8))
	{//時計発動//0.0のカラーのやつは枠線
	 //SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife, EFFECTTYPE nType,bool bZbf, bool bAbf, bool bCol,bool bRot);
		mystery = Prayerpolygon[s_nNanba].pos;
		//テクスチャの座標設定
		SetEffectFile(LOOD_FILE_NAME_EFFECT);

		SetEffect(LISTS_ZERO);
		SetEffect(LISTS_I);
		SetEffect(LISTS_II);
		SetEffect(LISTS_III);
		SetEffect(LISTS_IV);
		SetEffect(LISTS_V);
		SetEffect(LISTS_VI);
		SetEffect(LISTS_VII);
		SetEffect(LISTS_VIII);
		SetEffect(LISTS_IX);
		SetEffect(LISTS_X);
		SetEffect(LISTS_XI);
		SetEffect(LISTS_XII);
		SetEffect(LISTS_XIII);
		SetEffect(LISTS_XIV);
	}
	if (GetKeyboardTrigger(DIK_0))
	{//魔法陣発動//0.0のカラーのやつは枠線
		Prayerpolygon[s_nNanba].bMystery = true;
		mystery = Prayerpolygon[s_nNanba].pos;

	}
	if (Prayerpolygon[s_nNanba].bMystery)
	{
		SetEffectFile(LOOD_FILE_NAME_MAGIC);
		s_nTime++;
		SetParticle(D3DXVECTOR3(mystery),
			D3DXVECTOR3(0.0, 0.0, 0.0),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3.5f, 6.5f, EFFECTTYPE_AWA, 150);

		SetParticle(D3DXVECTOR3(mystery),
			D3DXVECTOR3(-sinf(mystery.y), 3.5f, -cosf(mystery.y)),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 3.5f, 6.5f, EFFECTTYPE_GLITTER, 150);

		if (s_nTime == 10)
		{
			SetEffect(LISTS_ZERO);

			SetEffect(LISTS_I);

			SetEffect(LISTS_II);

			//ここから下が虹色
			SetEffect(LISTS_III);

			SetEffect(LISTS_IV);

			SetEffect(LISTS_V);

			SetEffect(LISTS_VI);

			SetEffect(LISTS_VII);
		}
		if (s_nTime == 100)
		{
			SetEffect(LISTS_VIII);
			//ここから下が虹色
			SetEffect(LISTS_IX);

			SetEffect(LISTS_X);
		}
		if (s_nTime == 200)
		{
			SetEffect(LISTS_XI);

			SetEffect(LISTS_XII);

			//ここから下が虹色
			SetEffect(LISTS_XIII);

			SetEffect(LISTS_XIV);
		}
		if (s_nTime == 300)
		{
			SetEffect(LISTS_XV);

			SetEffect(LISTS_XVI);

			//ここから下が虹色
			SetEffect(LISTS_XVII);

			SetEffect(LISTS_XVIII);
		}
		if (s_nTime == 400)
		{

			SetEffect(LISTS_XVIX);

			SetEffect(LISTS_XX);

			//ここから下が虹色
			SetEffect(LISTS_XXI);

			SetEffect(LISTS_XXII);
		}
		if (s_nTime == EFFECT_LIFE)
		{
			s_nTime = 0;
			Prayerpolygon[s_nNanba].bMystery = false;

		}
	}

	//モデルの切り替え
	if (GetKeyboardTrigger(DIK_V))
	{
		s_nNanba++;
		s_nNanba %= s_nSet;
	}
	Prayerpolygon[s_nNanba].consumption = 0.0f;
	if (GetKeyboardPress(DIK_I))
	{//I押したとき上加速
		Prayerpolygon[s_nNanba].pos.x += sinf(pCamera->rot.y)*Spede;
		Prayerpolygon[s_nNanba].pos.z += cosf(pCamera->rot.y)*Spede;

		Prayerpolygon[s_nNanba].consumption = Prayerpolygon[s_nNanba].RotMove.x - Prayerpolygon[s_nNanba].rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_K))
	{//K押したと下加速
		Prayerpolygon[s_nNanba].pos.x += sinf(pCamera->rot.y - D3DX_PI)*Spede;
		Prayerpolygon[s_nNanba].pos.z += cosf(pCamera->rot.y - D3DX_PI)*Spede;

		Prayerpolygon[s_nNanba].consumption = Prayerpolygon[s_nNanba].RotMove.x - D3DX_PI - Prayerpolygon[s_nNanba].rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_L))
	{//L押したとき右加速
		Prayerpolygon[s_nNanba].pos.x += sinf(D3DX_PI *0.5f + pCamera->rot.y)*Spede;
		Prayerpolygon[s_nNanba].pos.z += cosf(D3DX_PI *0.5f + pCamera->rot.y)*Spede;

		Prayerpolygon[s_nNanba].consumption = Prayerpolygon[s_nNanba].RotMove.y - D3DX_PI - Prayerpolygon[s_nNanba].rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_J))
	{//j押したと左加速
		Prayerpolygon[s_nNanba].pos.x += sinf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;
		Prayerpolygon[s_nNanba].pos.z += cosf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;

		Prayerpolygon[s_nNanba].consumption = Prayerpolygon[s_nNanba].RotMove.y - Prayerpolygon[s_nNanba].rot.y + pCamera->rot.y;
	}
	if (GetKeyboardTrigger(DIK_RETURN))
	{//エンターリセット
	 // 初期化処理
		Prayerpolygon[s_nNanba].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
		Prayerpolygon[s_nNanba].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標	
	}
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//SetKen(Prayerpolygon[s_nNanba].pos);
		SetKitune(D3DXVECTOR3(Prayerpolygon[s_nNanba].pos.x, Prayerpolygon[s_nNanba].pos.y, Prayerpolygon[s_nNanba].pos.z),
			Prayerpolygon[s_nNanba].rot,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1);//場所.回転.色.タイプ
	}

	//正規化
	if (Prayerpolygon[s_nNanba].consumption > D3DX_PI)
	{
		Prayerpolygon[s_nNanba].consumption -= D3DX_PI * 2;
	}
	if (Prayerpolygon[s_nNanba].consumption < -D3DX_PI)
	{
		Prayerpolygon[s_nNanba].consumption += D3DX_PI * 2;
	}

	//減算設定（感性）
	Prayerpolygon[s_nNanba].rot.y += (Prayerpolygon[s_nNanba].consumption)* Attenuation;//目的の値-現在の値）＊減衰係数

																					  //正規化
	if (Prayerpolygon[s_nNanba].rot.y > D3DX_PI)
	{
		Prayerpolygon[s_nNanba].rot.y -= D3DX_PI * 2;
	}
	if (Prayerpolygon[s_nNanba].rot.y <= -D3DX_PI)
	{
		Prayerpolygon[s_nNanba].rot.y += D3DX_PI * 2;
	}

	//影更新
	SetposShadow(Prayerpolygon[s_nNanba].nShadow, Prayerpolygon[s_nNanba].pos);
	MESH *pMesh = GetMesh();
	//壁
	if (Prayerpolygon[s_nNanba].pos.x <pMesh->xsiz *-MAX_SIZMESH / 2)
	{
		Prayerpolygon[s_nNanba].pos.x = pMesh->xsiz * -MAX_SIZMESH / 2;
	}
	if (Prayerpolygon[s_nNanba].pos.x >pMesh->xsiz * MAX_SIZMESH / 2)
	{
		Prayerpolygon[s_nNanba].pos.x = pMesh->xsiz * MAX_SIZMESH / 2;
	}
	if (Prayerpolygon[s_nNanba].pos.z < pMesh->zsiz *-MAX_SIZMESH / 2)
	{
		Prayerpolygon[s_nNanba].pos.z = pMesh->zsiz * -MAX_SIZMESH / 2;
	}
	if (Prayerpolygon[s_nNanba].pos.z >pMesh->zsiz * MAX_SIZMESH / 2)
	{
		Prayerpolygon[s_nNanba].pos.z = pMesh->zsiz *MAX_SIZMESH / 2;
	}
}

//=========================================
// 描画処理
//=========================================
void DrawPrayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxTrans, mtxRot;	// 計算用マトリックス
	D3DMATERIAL9 marDef;
	D3DXMATERIAL *pMat;
	MESH *pMesh = GetMesh();
	for (int j = 0; j < s_nSet; j++)//出てるモデルの数だけ回す
	{
		if (Prayerpolygon[j].bUse)//使ってるやつ出す
		{
			// ワールドマトリックスの初期化
			// 行列初期化関数(第1引数の行列を単位行列に初期化)
			D3DXMatrixIdentity(&Prayerpolygon[j].MtxWorld);

			if (pMesh->xsiz / 10 == 0)
			{
				//サイズ変更
				D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//サイズ変更
				D3DXMatrixScaling(&mtxScale, pMesh->xsiz / 50.0f, pMesh->xsiz / 50.0f, pMesh->xsiz / 50.0f);
			}

			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&Prayerpolygon[j].MtxWorld, &Prayerpolygon[j].MtxWorld, &mtxScale);

			// 向きを反映
			// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, Prayerpolygon[j].rot.y, Prayerpolygon[j].rot.x, Prayerpolygon[j].rot.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&Prayerpolygon[j].MtxWorld, &Prayerpolygon[j].MtxWorld, &mtxRot);

			// 位置を反映
			// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, Prayerpolygon[j].pos.x, Prayerpolygon[j].pos.y, Prayerpolygon[j].pos.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&Prayerpolygon[j].MtxWorld, &Prayerpolygon[j].MtxWorld, &mtxTrans);

			// ワールド座標行列の設定
			pDevice->SetTransform(D3DTS_WORLD, &Prayerpolygon[j].MtxWorld);

			//現在のマテリアルを保持
			pDevice->GetMaterial(&marDef);

			//マテリアルデータのポインタを取得
			pMat = (D3DXMATERIAL*)Prayerpolygon[j].s_pBuffPrayer->GetBufferPointer();

			for (int i = 0; i < (int)Prayerpolygon[j].s_Prayer; i++)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, NULL);
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[i].MatD3D);

				//モデルパーツの描画
				Prayerpolygon[j].s_pVtxMesh->DrawSubset(i);
			}

			//現在のマテリアルを保持
			pDevice->SetMaterial(&marDef);
		}
	}


}
void SetPrayer(D3DXVECTOR3 pos, char *Filename)
{
	//カメラのデータ取得
	CAMERA *pCamera;
	pCamera = GetCamera();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char aFile[128] = FILE_3D_PRAYER;

	strcat(aFile, &Filename[0]);//合成　aFile＜-こいつに入れる

	D3DXLoadMeshFromX(&aFile[0],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Prayerpolygon[s_nSet].s_pBuffPrayer,
		NULL,
		&Prayerpolygon[s_nSet].s_Prayer,
		&Prayerpolygon[s_nSet].s_pVtxMesh
	);
	//すべての頂点数を保存する関数を作る
	int NumVpx;	//頂点数
				//一つの頂点のサイズを入れる関数
	DWORD sizeFVF;
	//バイトがたのポインターchar
	BYTE *pVtxBuff;

	//ここで頂点数を参照
	NumVpx = Prayerpolygon[s_nSet].s_pVtxMesh->GetNumVertices();

	//ここでサイズを入れる
	sizeFVF = D3DXGetFVFVertexSize(Prayerpolygon[s_nSet].s_pVtxMesh->GetFVF());

	//	頂点バッファのロックしましょう
	Prayerpolygon[s_nSet].s_pVtxMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


	for (int i = 0; i < NumVpx; i++)
	{

		D3DXVECTOR3 pVtx = *(D3DXVECTOR3*)pVtxBuff;
		//それを使ってモデルの最大値と最小値を使って求める
		//XYZ全部求める
		if (pVtx.x <= Prayerpolygon[s_nSet].ModelMin.x)
		{
			Prayerpolygon[s_nSet].ModelMin.x = pVtx.x;
		}
		if (pVtx.x >= Prayerpolygon[s_nSet].ModelMax.x)
		{
			Prayerpolygon[s_nSet].ModelMax.x = pVtx.x;
		}
		if (pVtx.y <= Prayerpolygon[s_nSet].ModelMin.y)
		{
			Prayerpolygon[s_nSet].ModelMin.y = pVtx.y;
		}
		if (pVtx.y >= Prayerpolygon[s_nSet].ModelMax.y)
		{
			Prayerpolygon[s_nSet].ModelMax.y = pVtx.y;
		}
		if (pVtx.z <= Prayerpolygon[s_nSet].ModelMin.z)
		{
			Prayerpolygon[s_nSet].ModelMin.z = pVtx.z;
		}
		if (pVtx.z >= Prayerpolygon[s_nSet].ModelMax.z)
		{
			Prayerpolygon[s_nSet].ModelMax.z = pVtx.z;
		}

		//一個分求めたら次に生きたいので
		pVtxBuff += sizeFVF;
		//これをやれば最大最小を求められる

	}
	//	頂点バッファのロックしましょう
	Prayerpolygon[s_nSet].s_pVtxMesh->UnlockVertexBuffer();



	Prayerpolygon[s_nSet].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
	// 初期化処理
	Prayerpolygon[s_nSet].pos = pos;	// 頂点座標
	Prayerpolygon[s_nSet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標
	Prayerpolygon[s_nSet].nShadow = SetShadow(Prayerpolygon[s_nSet].pos, Prayerpolygon[s_nNanba].rot, 0);//場所.回転
	Prayerpolygon[s_nSet].bUse = true;
	s_nSet++;
}
//----------------------
//ゲット(構造体)
//-----------------------
PRAYER *GetPrayer(void)
{
	return &Prayerpolygon[s_nNanba];
}

//----------------------
//ゲット(使ってる場番号)
//-----------------------
int GetnNanba(void)
{
	return s_nNanba;
}