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
#include"effect.h"
#include"line.h"

//マクロ
#define Attenuation	(0.5f)		//減衰係数
#define Spede	(1.0f)			//スピード
#define WIDTH (10.0f)			//モデルの半径
#define MAX_MODEL (16)			//最大数
//------------------------------------
// static変数
//------------------------------------
static bool s_bIsLanding;
static MODEL Modelpolygon[MAX_MODEL];	// ポリゴンの構造体
static int s_nSet; //最大数

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
		Modelpolygon[i].ModelMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		Modelpolygon[i].ModelMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	}
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
			
			D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
			
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
	//初期化のXファイルを読み込んだ後

	//すべての頂点数を保存する関数を作る
	int NumVpx;	//頂点数
	//一つの頂点のサイズを入れる関数
	DWORD sizeFVF;
	//バイトがたのポインターchar
	BYTE *pVtxBuff;

	//ここで頂点数を参照
	NumVpx = Modelpolygon[s_nSet].s_pVtxMesh->GetNumVertices();

	//ここでサイズを入れる
	sizeFVF = D3DXGetFVFVertexSize(Modelpolygon[s_nSet].s_pVtxMesh->GetFVF());

	//	頂点バッファのロックしましょう
	Modelpolygon[s_nSet].s_pVtxMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


	for (int i = 0; i < NumVpx; i++)
	{

		D3DXVECTOR3 pVtx = *(D3DXVECTOR3*)pVtxBuff;
		//それを使ってモデルの最大値と最小値を使って求める
		//XYZ全部求める
		if (pVtx.x <= Modelpolygon[s_nSet].ModelMin.x)
		{
			Modelpolygon[s_nSet].ModelMin.x = pVtx.x;
		}
		if (pVtx.x >= Modelpolygon[s_nSet].ModelMax.x)
		{
			Modelpolygon[s_nSet].ModelMax.x = pVtx.x;
		}
		if (pVtx.y <= Modelpolygon[s_nSet].ModelMin.y)
		{
			Modelpolygon[s_nSet].ModelMin.y = pVtx.y;
		}
		if (pVtx.y >= Modelpolygon[s_nSet].ModelMax.y)
		{
			Modelpolygon[s_nSet].ModelMax.y = pVtx.y;
		}
		if (pVtx.z <= Modelpolygon[s_nSet].ModelMin.z)
		{
			Modelpolygon[s_nSet].ModelMin.z = pVtx.z;
		}
		if (pVtx.z >= Modelpolygon[s_nSet].ModelMax.z)
		{
			Modelpolygon[s_nSet].ModelMax.z = pVtx.z;
		}

		

		//一個分求めたら次に生きたいので
		pVtxBuff += sizeFVF;
		//これをやれば最大最小を求められる

	}
	//	頂点バッファのロックしましょう
	Modelpolygon[s_nSet].s_pVtxMesh->UnlockVertexBuffer();

	// 初期化処理
	Modelpolygon[s_nSet].pos = pos;	// 頂点座標
	Modelpolygon[s_nSet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標
	Modelpolygon[s_nSet].nShadow = SetShadow(Modelpolygon[s_nSet].pos, Modelpolygon[s_nSet].rot,0);//場所.回転
	Modelpolygon[s_nSet].bUse = true;
	Modelpolygon[s_nSet].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);


#ifdef _DEBUG
	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMin.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y+1, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMax.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z), Modelpolygon[s_nSet].pos);
	
	
	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y , Modelpolygon[s_nSet].ModelMax.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y, Modelpolygon[s_nSet].ModelMax.z), Modelpolygon[s_nSet].pos);


	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y , Modelpolygon[s_nSet].ModelMin.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y , Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);
	

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);


	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);


	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);
#endif // DEBUG

	s_nSet++;
}

MODEL *GetModel(void)
{
	return &Modelpolygon[0];
}
void  CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz)
{
	{
		for (int nCnt = 0; nCnt < s_nSet; nCnt++)
		{
			if (Modelpolygon[nCnt].bUse)
			{
				//左右の壁
				if (pPosOld->z + Siz.z > Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMax.z
					&& pPosOld->z - Siz.z < Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMin.z)
				{
					if (pPos->x + Siz.x / 2 > Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMin.x
						&& pPosOld->x + Siz.x / 2 <= Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMin.x)
					{//ブロックの座標と座標が重なり合ったら//通常モード//左
						pPos->x = Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMin.x - Siz.x / 2.0f;
					}
					if (pPos->x - Siz.x / 2 < Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMax.x
						&& pPosOld->x - Siz.x / 2 >= Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMax.x)
					{//ブロックの座標と座標が重なり合ったら//通常モード//右
						pPos->x = Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMax.x + Siz.x / 2.0f+0.01f;
					}
				}
				//上下の壁
				if (pPosOld->x + Siz.x / 2 > Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMin.x
					&& pPosOld->x - Siz.x / 2 < Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMax.x)
				{
					if (pPos->z + Siz.z / 2 > Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMin.z
						&& pPosOld->z + Siz.z / 2 <= Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMin.z)
					{//ブロックの座標と座標が重なり合ったら//通常モード//下
						pPos->z = Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMin.z - Siz.z / 2.0f;
					}
					if (pPos->z - Siz.z / 2 < Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMax.z
						&& pPosOld->z - Siz.z / 2 >= Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMax.z)
					{//ブロックの座標と座標が重なり合ったら//通常モード//上
						pPos->z = Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMax.z + Siz.z / 2.0f + 0.01f;
					}
					
				}

			}
		}
	}
}

