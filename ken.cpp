//======================================
//モデル表示処理
//Auther：hamada ryuuga
//======================================

#include<stdio.h>
#include "ken.h"
#include"model.h"
#include "input.h"
#include"camera.h"
#include"shadow.h"
#include"kitune.h"
#include"file.h"
#include"mesh.h"
#include"paticle.h"
#include"effect.h"

//マクロ
#define Attenuation	(0.5f)		//減衰係数
#define Spede	(10.0f)			//スピード
#define WIDTH (10.0f)			//モデルの半径
#define MAX_KEN (6)			//最大数
//------------------------------------
// static変数
//------------------------------------
static KEN Kenpolygon[MAX_KEN];	// ポリゴンの構造体


//=========================================
// 初期化処理
//=========================================
void InitKen(void)
{
	//カメラのデータ取得
	CAMERA *pCamera;
	pCamera = GetCamera();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//カメラのデータ取得
	MODEL *pModel;
	pModel = GetModel();

	for (int i = 0; i < MAX_KEN; i++)
	{
		// 初期化処理
		Kenpolygon[i].s_pBuffKen = NULL;
		Kenpolygon[i].s_Ken = 0;
		Kenpolygon[i].s_pVtxMesh = NULL;			//縦　　　　　　　　　　//横
		Kenpolygon[i].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
		Kenpolygon[i].consumption = 0.0f;
		Kenpolygon[i].nLif = 100;
		if (i <= MAX_KEN/2)
		{
			Kenpolygon[i].pos = Kenpolygon[i].pos = D3DXVECTOR3(pModel->pos.x + (10 * i), pModel->pos.y, pModel->pos.z);
		}
		else
		{
			Kenpolygon[i].pos = Kenpolygon[i].pos = D3DXVECTOR3(pModel->pos.x - (10 * (i/2)), pModel->pos.y, pModel->pos.z);
		}
		Kenpolygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標
		Kenpolygon[i].bUse = true;
		Kenpolygon[i].bFri = false;


	}
	
	D3DXLoadMeshFromX("Data/Model/2dure.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[0].s_pBuffKen,
		NULL,		
		&Kenpolygon[0].s_Ken,
		&Kenpolygon[0].s_pVtxMesh
	);

	D3DXLoadMeshFromX("Data/Model/ru-n.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[1].s_pBuffKen,
		NULL,
		&Kenpolygon[1].s_Ken,
		&Kenpolygon[1].s_pVtxMesh
	);

	D3DXLoadMeshFromX("Data/Model/ru-n.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[2].s_pBuffKen,
		NULL,		
		&Kenpolygon[2].s_Ken,
		&Kenpolygon[2].s_pVtxMesh
	);
	D3DXLoadMeshFromX("Data/Model/basuta.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[3].s_pBuffKen,
		NULL,		
		&Kenpolygon[3].s_Ken,
		&Kenpolygon[3].s_pVtxMesh
	);
	D3DXLoadMeshFromX("Data/Model/basuta.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[4].s_pBuffKen,
		NULL,		
		&Kenpolygon[4].s_Ken,
		&Kenpolygon[4].s_pVtxMesh
	);
	D3DXLoadMeshFromX("Data/Model/fa-suto.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[5].s_pBuffKen,
		NULL,		
		&Kenpolygon[5].s_Ken,
		&Kenpolygon[5].s_pVtxMesh
	);

}

//=========================================
// 終了処理
//=========================================
void UninitKen(void)
{
	for (int i = 0; i < MAX_KEN; i++)
	{
		// 頂点バッファーの解放
		if (Kenpolygon[i].s_pVtxMesh != NULL)
		{
			Kenpolygon[i].s_pVtxMesh->Release();
			Kenpolygon[i].s_pVtxMesh = NULL;
		}
		if (Kenpolygon[i].s_pBuffKen != NULL)
		{
			Kenpolygon[i].s_pBuffKen->Release();
			Kenpolygon[i].s_pBuffKen = NULL;
		}
	}

}

//=========================================
// 更新処理
//=========================================
void UpdateKen(void)
{	//カメラのデータ取得
	MODEL *pModel;
	pModel = GetModel();
	//カメラのデータ取得
	CAMERA *pCamera;
	pCamera = GetCamera();
	float consumption = 0;
	for (int i = 0; i < MAX_KEN; i++)
	{

		if (Kenpolygon[i].bUse)
		{

		if (GetKeyboardTrigger(DIK_SPACE))
		{
			Kenpolygon[i].bFri = true;	
			Kenpolygon[i].move.x = sinf(pModel->rot.y);
			Kenpolygon[i].move.y = cosf(pModel->rot.y);
		}
		if (GetKeyboardTrigger(DIK_O))
		{
			Kenpolygon[i].bFri = false;
			Kenpolygon[i].move.x = sinf(pModel->rot.y);
			Kenpolygon[i].move.y = cosf(pModel->rot.y);
		}

		
			Kenpolygon[i].consumption = 0.0f;
			if (Kenpolygon[i].bFri ==true)
			{
				//SetEffect(Kenpolygon[i].pos,
					//D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 5, 100);

					Kenpolygon[i].pos.x -= Kenpolygon[i].move.x *Spede;
					Kenpolygon[i].pos.z -= Kenpolygon[i].move.y *Spede;

					Kenpolygon[i].consumption = Kenpolygon[i].RotMove.x - Kenpolygon[i].rot.y + pCamera->rot.y;
					Kenpolygon[i].nLif--;
				if (Kenpolygon[i].nLif == 0)
				{
					Kenpolygon[i].nLif = 100;
					Kenpolygon[i].bFri = false;
				}
			}
			else
			{
				if (i <= MAX_KEN / 2)
				{
					Kenpolygon[i].pos = Kenpolygon[i].pos = D3DXVECTOR3(pModel->pos.x + (10 * i), pModel->pos.y + 10 + 20 * i, pModel->pos.z);
				}
				else
				{
					Kenpolygon[i].pos = Kenpolygon[i].pos = D3DXVECTOR3(pModel->pos.x - (10 * (i / 2)), pModel->pos.y+10+20 * i/2, pModel->pos.z);
				}
				Kenpolygon[i].rot = D3DXVECTOR3(pModel->rot);	// 回転座標
			}
		}
	}

}

//=========================================
// 描画処理
//=========================================
void DrawKen(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//D3DXMATRIX mtxScale, mtxTrans, mtxRot;	// 計算用マトリックス
	//D3DMATERIAL9 marDef;
	//D3DXMATERIAL *pMat;
	//MESH *pMesh = GetMesh();
	for (int j = 0; j < MAX_KEN; j++)//出てるモデルの数だけ回す
	{
		if (Kenpolygon[j].bUse)//使ってるやつ出す
		{
			//// ワールドマトリックスの初期化
			//// 行列初期化関数(第1引数の行列を単位行列に初期化)
			//D3DXMatrixIdentity(&Kenpolygon[j].MtxWorld);

			////サイズ変更
			//D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
			//
			//// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			//D3DXMatrixMultiply(&Kenpolygon[j].MtxWorld, &Kenpolygon[j].MtxWorld, &mtxScale);

			//// 向きを反映
			//// 行列回転関数(第1引数にヨー(y)ピッチ(x)ロール(z)方向の回転行列を作成)
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, Kenpolygon[j].rot.y, Kenpolygon[j].rot.x, Kenpolygon[j].rot.z);
			//// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			//D3DXMatrixMultiply(&Kenpolygon[j].MtxWorld, &Kenpolygon[j].MtxWorld, &mtxRot);

			//// 位置を反映
			//// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
			//D3DXMatrixTranslation(&mtxTrans, Kenpolygon[j].pos.x, Kenpolygon[j].pos.y, Kenpolygon[j].pos.z);
			//// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
			//D3DXMatrixMultiply(&Kenpolygon[j].MtxWorld, &Kenpolygon[j].MtxWorld, &mtxTrans);

			//// ワールド座標行列の設定
			//pDevice->SetTransform(D3DTS_WORLD, &Kenpolygon[j].MtxWorld);

			////現在のマテリアルを保持
			//pDevice->GetMaterial(&marDef);

			////マテリアルデータのポインタを取得
			//pMat = (D3DXMATERIAL*)Kenpolygon[j].s_pBuffKen->GetBufferPointer();

			//for (int i = 0; i < (int)Kenpolygon[j].s_Ken; i++)
			//{
			//	//テクスチャの設定
			//	pDevice->SetTexture(0, NULL);
			//	//マテリアルの設定
			//	pDevice->SetMaterial(&pMat[i].MatD3D);

			//	//モデルパーツの描画
			//	Kenpolygon[j].s_pVtxMesh->DrawSubset(i);
			//}

			////現在のマテリアルを保持
			//pDevice->SetMaterial(&marDef);
		}
	}


}
void SetKen(D3DXVECTOR3 pos)
{
	//カメラのデータ取得
	CAMERA *pCamera;
	pCamera = GetCamera();
	//カメラのデータ取得
	MODEL *pModel;
	pModel = GetModel();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_KEN; i++)
	{
		Kenpolygon[i].nLif = 100;
		Kenpolygon[i].RotMove = D3DXVECTOR3(D3DX_PI + pModel->rot.y, D3DX_PI*0.5f + pModel->rot.y, 0.0f);
		// 初期化処理

		Kenpolygon[i].pos.x = pos.x+i * 20.0f;	// 頂点座標
		Kenpolygon[i].pos.y = pos.y+i*20.0f;	// 頂点座標
		Kenpolygon[i].pos.z = pos.z;	// 頂点座標
		Kenpolygon[i].move.x = sinf(pModel->rot.y);
		Kenpolygon[i].move.y = cosf(pModel->rot.y);
		Kenpolygon[i].rot = D3DXVECTOR3(pModel->rot);	// 回転座標
		Kenpolygon[i].bUse = true;
		Kenpolygon[i].nType = i;
	}

}
