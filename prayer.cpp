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
#include"model.h"
//マクロ
#define Attenuation	(0.5f)		//減衰係数
#define Spede	(1.0f)			//スピード
#define WIDTH (10.0f)			//モデルの半径
#define MAX_PRAYER (16)			//最大数
//------------------------------------
// static変数
//------------------------------------
static PRAYER s_Prayer;	// ポリゴンの構造体
static int s_nNanba, s_nSet, s_nTime,s_nParts;//現在使用してるやつと最大数
static float nTime = 0;
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
												//縦　　　　　　　　　　//横
		s_Prayer.RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
		s_Prayer.consumption = 0.0f;
		s_Prayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
		s_Prayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標
		s_Prayer.nShadow = 0;
		s_Prayer.bUse = false;
		s_Prayer.bMystery = false;
		s_Prayer.ModelMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		s_Prayer.ModelMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (int nSet = 0; nSet < MAX_MODELPARTS; nSet++)
		{
			s_Prayer.Parts[nSet].nIdxModelParent = 0;
		}
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
	for (int i = 0; i < s_nParts; i++)
	{
		// 頂点バッファーの解放
		if (s_Prayer.Parts[i].pBuffMat != NULL)
		{
			s_Prayer.Parts[i].pBuffMat->Release();
			s_Prayer.Parts[i].pBuffMat = NULL;
		}
		if (s_Prayer.Parts[i].pMesh != NULL)
		{
			s_Prayer.Parts[i].pMesh->Release();
			s_Prayer.Parts[i].pMesh = NULL;
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
		SetParticle(s_Prayer.pos - D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_KITUNE, LIGHTNINGLIFE);
	}
	if (GetKeyboardPress(DIK_2))
	{//２押したときパーティクル
		SetParticle(s_Prayer.pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_LIGHTNING, KITUNELIFE);
	}
	if (GetKeyboardPress(DIK_3))
	{//３押したときパーティクル
		SetParticle(s_Prayer.pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_OUKAN, OUKANLIFE);
	}
	if (GetKeyboardPress(DIK_4))
	{//４押したときパーティクル

		SetParticle(s_Prayer.pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_MERA, MERALIFE);
	}
	if (GetKeyboardPress(DIK_7))
	{//魔法陣発動//0.0のカラーのやつは枠線
	}
	if (GetKeyboardTrigger(DIK_8))
	{//時計発動//0.0のカラーのやつは枠線

		mystery = s_Prayer.pos;
		//テクスチャの座標設定
		SetEffectFile(LOOD_FILE_NAME_EFFECT);
		int a = GetEffectFile();

		for (int i = 0; i < a; i++)
		{
			SetEffect(i, mystery);
		}

	}
	if (GetKeyboardTrigger(DIK_0))
	{//魔法陣発動//0.0のカラーのやつは枠線
		s_Prayer.bMystery = true;
		mystery = s_Prayer.pos;
	}
	if (s_Prayer.bMystery)
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
			SetEffect(LISTS_ZERO, mystery);

			SetEffect(LISTS_I, mystery);

			SetEffect(LISTS_II, mystery);

			//ここから下が虹色
			SetEffect(LISTS_III, mystery);

			SetEffect(LISTS_IV, mystery);

			SetEffect(LISTS_V, mystery);

			SetEffect(LISTS_VI, mystery);

			SetEffect(LISTS_VII, mystery);
		}
		if (s_nTime == 100)
		{
			SetEffect(LISTS_VIII, mystery);
			//ここから下が虹色
			SetEffect(LISTS_IX, mystery);

			SetEffect(LISTS_X, mystery);
		}
		if (s_nTime == 200)
		{
			SetEffect(LISTS_XI, mystery);

			SetEffect(LISTS_XII, mystery);

			//ここから下が虹色
			SetEffect(LISTS_XIII, mystery);

			SetEffect(LISTS_XIV, mystery);
		}
		if (s_nTime == 300)
		{
			SetEffect(LISTS_XV, mystery);

			SetEffect(LISTS_XVI, mystery);

			//ここから下が虹色
			SetEffect(LISTS_XVII, mystery);

			SetEffect(LISTS_XVIII, mystery);
		}
		if (s_nTime == 400)
		{

			SetEffect(LISTS_XVIX, mystery);

			SetEffect(LISTS_XX, mystery);

			//ここから下が虹色
			SetEffect(LISTS_XXI,mystery);

			SetEffect(LISTS_XXII, mystery);
		}
		if (s_nTime == EFFECT_LIFE)
		{
			s_nTime = 0;
			s_Prayer.bMystery = false;

		}
	}

	//モデルの切り替え
	if (GetKeyboardTrigger(DIK_V))
	{
		s_nNanba++;
		s_nNanba %= s_nSet;
	}

	s_Prayer.posOld = s_Prayer.pos;//過去の移動量を保存

	s_Prayer.consumption = 0.0f;
	if (GetKeyboardPress(DIK_I))
	{//I押したとき上加速
		s_Prayer.pos.x += sinf(pCamera->rot.y)*Spede;
		s_Prayer.pos.z += cosf(pCamera->rot.y)*Spede;

		s_Prayer.consumption = s_Prayer.RotMove.x - s_Prayer.rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_K))
	{//K押したと下加速
		s_Prayer.pos.x += sinf(pCamera->rot.y - D3DX_PI)*Spede;
		s_Prayer.pos.z += cosf(pCamera->rot.y - D3DX_PI)*Spede;

		s_Prayer.consumption = (s_Prayer.RotMove.x - 
												D3DX_PI - s_Prayer.rot.y 
												+ pCamera->rot.y);
	}
	if (GetKeyboardPress(DIK_L))
	{//L押したとき右加速
		s_Prayer.pos.x += sinf(D3DX_PI *0.5f + pCamera->rot.y)*Spede;
		s_Prayer.pos.z += cosf(D3DX_PI *0.5f + pCamera->rot.y)*Spede;

		s_Prayer.consumption = s_Prayer.RotMove.y - D3DX_PI - s_Prayer.rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_J))
	{//nSet押したと左加速
		s_Prayer.pos.x += sinf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;
		s_Prayer.pos.z += cosf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;

		s_Prayer.consumption = s_Prayer.RotMove.y - s_Prayer.rot.y + pCamera->rot.y;
	}
	if (GetKeyboardTrigger(DIK_RETURN))
	{//エンターリセット
	 // 初期化処理
		s_Prayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
		s_Prayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標	
	}
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//SetKen(Prayerpolygon[s_nNanba].pos);
		SetKitune(D3DXVECTOR3(s_Prayer.pos.x, s_Prayer.pos.y, s_Prayer.pos.z),
			s_Prayer.rot,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1);//場所.回転.色.タイプ
	}
	CollisionModel(&s_Prayer.pos, &s_Prayer.posOld, s_Prayer.ModelMax - s_Prayer.ModelMin);
	//正規化
	if (s_Prayer.consumption > D3DX_PI)
	{
		s_Prayer.consumption += D3DX_PI * 2;
	}
	if (s_Prayer.consumption < -D3DX_PI)
	{
		s_Prayer.consumption += -D3DX_PI * 2;
	}

	//減算設定（感性）
	s_Prayer.rot.y += (s_Prayer.consumption)* Attenuation;//目的の値-現在の値）＊減衰係数

																					  //正規化
	if (s_Prayer.rot.y > D3DX_PI)
	{
		s_Prayer.rot.y += -D3DX_PI * 2;
	}
	if (s_Prayer.rot.y <= -D3DX_PI)
	{
		s_Prayer.rot.y += D3DX_PI * 2;
	}
	
	//影更新
	SetposShadow(s_Prayer.nShadow, s_Prayer.pos);
	MESH *pMesh = GetMesh();
	//壁
	if (s_Prayer.pos.x <pMesh->xsiz *-MAX_SIZMESH / 2)
	{
		s_Prayer.pos.x = pMesh->xsiz * -MAX_SIZMESH / 2;
	}
	if (s_Prayer.pos.x >pMesh->xsiz * MAX_SIZMESH / 2)
	{
		s_Prayer.pos.x = pMesh->xsiz * MAX_SIZMESH / 2;
	}
	if (s_Prayer.pos.z < pMesh->zsiz *-MAX_SIZMESH / 2)
	{
		s_Prayer.pos.z = pMesh->zsiz * -MAX_SIZMESH / 2;
	}
	if (s_Prayer.pos.z >pMesh->zsiz * MAX_SIZMESH / 2)
	{
		s_Prayer.pos.z = pMesh->zsiz *MAX_SIZMESH / 2;
	}
	
	


		s_Prayer.Parts[6].rot.z += D3DX_PI / 50.0f * sinf(nTime / 6.0f);
		nTime++;

	
	
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

	if (s_Prayer.bUse)//使ってるやつ出す
	{
		// ワールドマトリックスの初期化
		// 行列初期化関数(第1引数の行列を単位行列に初期化)
		D3DXMatrixIdentity(&s_Prayer.MtxWorld);

		D3DXMatrixScaling(&mtxScale, 0.8, 0.8, 0.8);

		// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
		D3DXMatrixMultiply(&s_Prayer.MtxWorld, &s_Prayer.MtxWorld, &mtxScale);

		// 向きを反映
		// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Prayer.rot.y, s_Prayer.rot.x, s_Prayer.rot.z);
		// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
		D3DXMatrixMultiply(&s_Prayer.MtxWorld, &s_Prayer.MtxWorld, &mtxRot);

		// 位置を反映
		// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
		D3DXMatrixTranslation(&mtxTrans, s_Prayer.pos.x, s_Prayer.pos.y, s_Prayer.pos.z);
		// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
		D3DXMatrixMultiply(&s_Prayer.MtxWorld, &s_Prayer.MtxWorld, &mtxTrans);

		for (int i = 0; i < s_nParts; i++)
		{
			// ワールドマトリックスの初期化
			// 行列初期化関数(第1引数の行列を単位行列に初期化)
			D3DXMatrixIdentity(&s_Prayer.Parts[i].MtxWorld);

			

			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&s_Prayer.Parts[i].MtxWorld, &s_Prayer.Parts[i].MtxWorld, &mtxScale);

			// 向きを反映
			// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Prayer.Parts[i].rot.y, s_Prayer.Parts[i].rot.x, s_Prayer.Parts[i].rot.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&s_Prayer.Parts[i].MtxWorld, &s_Prayer.Parts[i].MtxWorld, &mtxRot);

			// 位置を反映
			// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, s_Prayer.Parts[i].pos.x, s_Prayer.Parts[i].pos.y, s_Prayer.Parts[i].pos.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&s_Prayer.Parts[i].MtxWorld, &s_Prayer.Parts[i].MtxWorld, &mtxTrans);

			D3DXMATRIX mtxParent;

			//現在のマテリアルを獲得
			pDevice->GetMaterial(&marDef);

			if (s_Prayer.Parts[i].nIdxModelParent == -1)
			{
				mtxParent = s_Prayer.MtxWorld;
			}
			else
			{
				mtxParent = s_Prayer.Parts[s_Prayer.Parts[i].nIdxModelParent].MtxWorld;
			}
			D3DXMatrixMultiply(&s_Prayer.Parts[i].MtxWorld, &s_Prayer.Parts[i].MtxWorld, &mtxParent);

			// ワールド座標行列の設定
			pDevice->SetTransform(D3DTS_WORLD, &s_Prayer.Parts[i].MtxWorld);
			//マテリアルデータのポインタを取得
			pMat = (D3DXMATERIAL*)s_Prayer.Parts[i].pBuffMat->GetBufferPointer();
			for (int j = 0; j < (int)s_Prayer.Parts[i].nNumMat; j++)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, NULL);
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[j].MatD3D);
				//モデルパーツの描画
				s_Prayer.Parts[i].pMesh->DrawSubset(j);
			}


		}
		//現在のマテリアルを元に戻す
		pDevice->SetMaterial(&marDef);
	}
}
void SetPrayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *Filename,int nIdxModelParent)
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
		&s_Prayer.Parts[s_nParts].pBuffMat,
		NULL,
		&s_Prayer.Parts[s_nParts].nNumMat,
		&s_Prayer.Parts[s_nParts].pMesh
	);
	SizSet();
	s_Prayer.Parts[s_nParts].nIdxModelParent = nIdxModelParent;
	s_Prayer.RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
	// 初期化処理
	s_Prayer.Parts[s_nParts].pos = pos;	// 頂点座標
	s_Prayer.Parts[s_nParts].rot = rot;	// 回転座標
	s_Prayer.bUse = true;
	if (s_Prayer.Parts[s_nParts].nIdxModelParent==-1)
	{
		s_Prayer.nShadow = SetShadow(s_Prayer.pos, s_Prayer.rot, 0);//場所.回転
	}
	s_nParts++;
}
//----------------------
//ゲット(構造体)
//-----------------------
PRAYER *GetPrayer(void)
{
	return &s_Prayer;
}

//----------------------
//ゲット(使ってる場番号)
//-----------------------
int GetnNanba(void)
{
	return s_nNanba;
}
void SizSet(void)
{
	//すべての頂点数を保存する関数を作る
	int NumVpx;	//頂点数
	//一つの頂点のサイズを入れる関数
	DWORD sizeFVF;
	//バイトがたのポインターchar
	BYTE *pVtxBuff;

	//ここで頂点数を参照
	NumVpx = s_Prayer.Parts[s_nParts].pMesh->GetNumVertices();

	//ここでサイズを入れる
	sizeFVF = D3DXGetFVFVertexSize(s_Prayer.Parts[s_nParts].pMesh->GetFVF());

	//頂点バッファのロックしましょう
	s_Prayer.Parts[s_nParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int i = 0; i < NumVpx; i++)
	{
		D3DXVECTOR3 pVtx = *(D3DXVECTOR3*)pVtxBuff;
		//それを使ってモデルの最大値と最小値を使って求める
		//XYZ全部求める
		if (pVtx.x < s_Prayer.ModelMin.x)
		{
			s_Prayer.ModelMin.x = pVtx.x;
		}
		if (pVtx.x > s_Prayer.ModelMax.x)
		{
			s_Prayer.ModelMax.x = pVtx.x;
		}
		if (pVtx.y < s_Prayer.ModelMin.y)
		{
			s_Prayer.ModelMin.y = pVtx.y;
		}
		if (pVtx.y > s_Prayer.ModelMax.y)
		{
			s_Prayer.ModelMax.y = pVtx.y;
		}
		if (pVtx.z < s_Prayer.ModelMin.z)
		{
			s_Prayer.ModelMin.z = pVtx.z;
		}
		if (pVtx.z > s_Prayer.ModelMax.z)
		{
			s_Prayer.ModelMax.z = pVtx.z;
		}


		//一個分求めたら次に生きたいので
		pVtxBuff += sizeFVF;
		//これをやれば最大最小を求められる
	}

	//頂点バッファのロックしましょう
	s_Prayer.Parts[s_nParts].pMesh->UnlockVertexBuffer();
}

