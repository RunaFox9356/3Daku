//======================================
//モデル表示処理
//Auther：hamada ryuuga
//======================================

#include<stdio.h>
#include "model.h"
#include "input.h"
#include"camera.h"
#include"shadow.h"
#include"kitune.h"
#include"file.h"
#include"mesh.h"
#include"paticle.h"
#include"ken.h"

//マクロ
#define Attenuation	(0.5f)		//減衰係数
#define Spede	(1.0f)			//スピード
#define WIDTH (10.0f)			//モデルの半径
#define MAX_MODEL (16)			//最大数
//------------------------------------
// static変数
//------------------------------------
static MODEL Modelpolygon[MAX_MODEL];	// ポリゴンの構造体
static int s_nNanba,s_nSet;//現在使用してるやつと最大数

//=========================================
// 初期化処理
//=========================================
void InitModel(void)
{
	//カメラのデータ取得
	CAMERA *pCamera;
	pCamera = GetCamera();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_MODEL; i++)
	{
		// 初期化処理
		Modelpolygon[i].s_pBuffModel = NULL;
		Modelpolygon[i].s_Model = 0;
		Modelpolygon[i].s_pVtxMesh = NULL;			//縦　　　　　　　　　　//横
		Modelpolygon[i].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
		Modelpolygon[i].consumption = 0.0f;
		Modelpolygon[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
		Modelpolygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標
		Modelpolygon[i].nShadow = 0;
		Modelpolygon[i].bUse = false;

	}
	s_nNanba = 0;
	s_nSet = 0;
}

//=========================================
// 終了処理
//=========================================
void UninitModel(void)
{
	for (int i = 0; i < MAX_MODEL; i++)
	{
		// 頂点バッファーの解放
		if (Modelpolygon[i].s_pVtxMesh != NULL)
		{
			Modelpolygon[i].s_pVtxMesh->Release();
			Modelpolygon[i].s_pVtxMesh = NULL;
		}
		if (Modelpolygon[i].s_pBuffModel != NULL)
		{
			Modelpolygon[i].s_pBuffModel->Release();
			Modelpolygon[i].s_pBuffModel = NULL;
		}
	}
	
}

//=========================================
// 更新処理
//=========================================
void UpdateModel(void)
{
	//カメラのデータ取得
	CAMERA *pCamera;
	pCamera = GetCamera();
	float consumption = 0;
	
	if (GetKeyboardPress(DIK_1))
	{//1押したときパーティクル

		SetParticle(Modelpolygon[s_nNanba].pos - D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_KITUNE, true);
		
	}
	if (GetKeyboardPress(DIK_2))
	{//1押したときパーティクル

		SetParticle(Modelpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_LIGHTNING, true);
	

	}if (GetKeyboardPress(DIK_3))
	{//1押したときパーティクル

		SetParticle(Modelpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_OUKAN, true);


	}
	//モデルの切り替え
	if (GetKeyboardTrigger(DIK_V))
	{
		s_nNanba++;
		s_nNanba %= s_nSet;
	}
	Modelpolygon[s_nNanba].consumption = 0.0f;
	if (GetKeyboardPress(DIK_I))
	{//I押したとき上加速
		Modelpolygon[s_nNanba].pos.x += sinf(pCamera->rot.y)*Spede;
		Modelpolygon[s_nNanba].pos.z += cosf(pCamera->rot.y)*Spede;

		Modelpolygon[s_nNanba].consumption = Modelpolygon[s_nNanba].RotMove.x - Modelpolygon[s_nNanba].rot.y + pCamera->rot.y;

	}
	if (GetKeyboardPress(DIK_K))
	{//K押したと下加速
		Modelpolygon[s_nNanba].pos.x -= sinf(pCamera->rot.y)*Spede;
		Modelpolygon[s_nNanba].pos.z -= cosf(pCamera->rot.y)*Spede;

		Modelpolygon[s_nNanba].consumption = Modelpolygon[s_nNanba].RotMove.x - D3DX_PI - Modelpolygon[s_nNanba].rot.y + pCamera->rot.y;

	}
	if (GetKeyboardPress(DIK_L))
	{//L押したとき右加速
		Modelpolygon[s_nNanba].pos.x -= sinf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;
		Modelpolygon[s_nNanba].pos.z -= cosf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;

		Modelpolygon[s_nNanba].consumption = Modelpolygon[s_nNanba].RotMove.y - D3DX_PI - Modelpolygon[s_nNanba].rot.y + pCamera->rot.y;

	}
	if (GetKeyboardPress(DIK_J))
	{//j押したと左加速
		Modelpolygon[s_nNanba].pos.x += sinf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;
		Modelpolygon[s_nNanba].pos.z += cosf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;

		Modelpolygon[s_nNanba].consumption = Modelpolygon[s_nNanba].RotMove.y - Modelpolygon[s_nNanba].rot.y + pCamera->rot.y;

	}
	if (GetKeyboardTrigger(DIK_RETURN))
	{//エンターリセット
	 // 初期化処理
		Modelpolygon[s_nNanba].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
		Modelpolygon[s_nNanba].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

	}
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//SetKen(Modelpolygon[s_nNanba].pos);
		SetKitune(D3DXVECTOR3(Modelpolygon[s_nNanba].pos.x, Modelpolygon[s_nNanba].pos.y, Modelpolygon[s_nNanba].pos.z) ,
			Modelpolygon[s_nNanba].rot,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1);//場所.回転.色.タイプ
	}
	
	//正規化
	if (Modelpolygon[s_nNanba].consumption > D3DX_PI)
	{
		Modelpolygon[s_nNanba].consumption -= D3DX_PI * 2;
	}
	if (Modelpolygon[s_nNanba].consumption < -D3DX_PI)
	{
		Modelpolygon[s_nNanba].consumption += D3DX_PI * 2;
	}

	//減算設定（感性）
	Modelpolygon[s_nNanba].rot.y += (Modelpolygon[s_nNanba].consumption)* Attenuation;//目的の値-現在の値）＊減衰係数

	//正規化
	if (Modelpolygon[s_nNanba].rot.y > D3DX_PI)
	{
		Modelpolygon[s_nNanba].rot.y -= D3DX_PI * 2;
	}
	if (Modelpolygon[s_nNanba].rot.y <= -D3DX_PI)
	{
		Modelpolygon[s_nNanba].rot.y += D3DX_PI * 2;
	}

	//影更新
	SetposShadow(Modelpolygon[s_nNanba].nShadow, Modelpolygon[s_nNanba].pos);
	MESH *pMesh = GetMesh();
	//壁
	if (Modelpolygon[s_nNanba].pos.x <pMesh->xsiz *-MAX_SIZMESH/2)
	{
		Modelpolygon[s_nNanba].pos.x = pMesh->xsiz * -MAX_SIZMESH / 2;
	}
	if (Modelpolygon[s_nNanba].pos.x >pMesh->xsiz * MAX_SIZMESH / 2)
	{
		Modelpolygon[s_nNanba].pos.x = pMesh->xsiz * MAX_SIZMESH / 2;
	}
	if (Modelpolygon[s_nNanba].pos.z < pMesh->zsiz *-MAX_SIZMESH / 2)
	{
		Modelpolygon[s_nNanba].pos.z = pMesh->zsiz * -MAX_SIZMESH / 2;
	}
	if (Modelpolygon[s_nNanba].pos.z >pMesh->zsiz * MAX_SIZMESH / 2)
	{
		Modelpolygon[s_nNanba].pos.z = pMesh->zsiz *MAX_SIZMESH / 2;
	}
}

//=========================================
// 描画処理
//=========================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxTrans,mtxRot;	// 計算用マトリックス
	D3DMATERIAL9 marDef;
	D3DXMATERIAL *pMat;
	MESH *pMesh = GetMesh();
	for (int j = 0; j < s_nSet; j++)//出てるモデルの数だけ回す
	{
		if (Modelpolygon[j].bUse)//使ってるやつ出す
		{
			// ワールドマトリックスの初期化
			// 行列初期化関数(第1引数の行列を単位行列に初期化)
			D3DXMatrixIdentity(&Modelpolygon[j].MtxWorld);

			if (pMesh->xsiz/ 10 ==0)
			{
				//サイズ変更
				D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//サイズ変更
				D3DXMatrixScaling(&mtxScale, pMesh->xsiz / 10, pMesh->xsiz / 10, pMesh->xsiz / 10);
			}
			
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&Modelpolygon[j].MtxWorld, &Modelpolygon[j].MtxWorld, &mtxScale);

			// 向きを反映
			// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, Modelpolygon[j].rot.y, Modelpolygon[j].rot.x, Modelpolygon[j].rot.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&Modelpolygon[j].MtxWorld, &Modelpolygon[j].MtxWorld, &mtxRot);

			// 位置を反映
			// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
			D3DXMatrixTranslation(&mtxTrans, Modelpolygon[j].pos.x, Modelpolygon[j].pos.y, Modelpolygon[j].pos.z);
			// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			D3DXMatrixMultiply(&Modelpolygon[j].MtxWorld, &Modelpolygon[j].MtxWorld, &mtxTrans);

			// ワールド座標行列の設定
			pDevice->SetTransform(D3DTS_WORLD, &Modelpolygon[j].MtxWorld);

			//現在のマテリアルを保持
			pDevice->GetMaterial(&marDef);

			//マテリアルデータのポインタを取得
			pMat = (D3DXMATERIAL*)Modelpolygon[j].s_pBuffModel->GetBufferPointer();

			for (int i = 0; i < (int)Modelpolygon[j].s_Model; i++)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, NULL);
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[i].MatD3D);

				//モデルパーツの描画
				Modelpolygon[j].s_pVtxMesh->DrawSubset(i);
			}

			//現在のマテリアルを保持
			pDevice->SetMaterial(&marDef);
		}
	}


}
void SetModel(D3DXVECTOR3 pos, char *Filename)
{
	//カメラのデータ取得
	CAMERA *pCamera;
	pCamera = GetCamera();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char aFile[128] = FILE_3D_MODEL;

	strcat(aFile, &Filename[0]);//合成　aFile＜-こいつに入れる

	D3DXLoadMeshFromX(&aFile[0],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Modelpolygon[s_nSet].s_pBuffModel,
		NULL,
		&Modelpolygon[s_nSet].s_Model,
		&Modelpolygon[s_nSet].s_pVtxMesh
	);

	Modelpolygon[s_nSet].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
	// 初期化処理
	Modelpolygon[s_nSet].pos = pos;	// 頂点座標
	Modelpolygon[s_nSet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標
	Modelpolygon[s_nSet].nShadow = SetShadow(Modelpolygon[s_nSet].pos, Modelpolygon[s_nNanba].rot,0);//場所.回転
	Modelpolygon[s_nSet].bUse = true;
	s_nSet++;
}
//----------------------
//ゲット(構造体)
//-----------------------
MODEL *GetModel(void)
{
	return &Modelpolygon[s_nNanba];
}

//----------------------
//ゲット(使ってる場番号)
//-----------------------
int GetnNanba(void)
{
	return s_nNanba;
}
