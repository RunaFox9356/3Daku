//=================
//メッシュｈ
//Auther：hamada ryuuga
//=================
#ifndef _MESH_H_
#define _MESH_H_

#include"main.h"

#define	MESHX	(1)
#define	MESHY	(5)
#define MAX_SIZMESH (10.0f)
#define MAX_MESH (20)
//------------------------------------
// ポリゴンの構造体を定義
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 rot;	// 回転座標
	D3DXMATRIX mtxWorld;// ワールドマトリックス
	int xsiz;//面数
	int zsiz;//面数
	int X;//辺の頂点数
	int Z;//辺の頂点数
	int Vtx;//頂点数
	int Index; //インデックス
	int por;

} MESH;

//プロトタイプ宣言
void InitMesh(void);//初期化
void UninitMesh(void);//破棄
void UpdateMesh(void);//更新
void DrawMesh(void);//描画
void SetMesh(int X ,int Z);//場所.回転
MESH *GetMesh(void);

#endif