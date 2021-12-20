//=================
//メッシュｈ
//Auther：hamada ryuuga
//=================
#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include"main.h"

#define	CYLINDERX	(1)
#define	CYLINDERY	(5)

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
	int ysiz;
	int X;//辺の頂点数
	int Z;//辺の頂点数
	int Y;
	int Vtx;//頂点数
	int Index; //インデックス
	int por;
} CYLINDER;

//プロトタイプ宣言
void InitCylinder(void);//初期化
void UninitCylinder(void);//破棄
void UpdateCylinder(void);//更新
void DrawCylinder(void);//描画
void SetCylinder(void);//場所.回転
CYLINDER *GetCylinder(void);

#endif