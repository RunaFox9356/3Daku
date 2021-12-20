//========================
//ビルボードｈ
//Auther：hamada ryuuga
//========================

#ifndef _LINE_H_
#define _LINE_H_

#include"main.h"

#define	MAX_LINE	(4096)
#define	MAX_RECIPE	(5)
#define MAX_TEX (2)
#define BallSpede (1)

//------------------------------------
// ポリゴンの構造体を定義
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 rot;	// 回転座標
	D3DXMATRIX mtxWorld;// ワールドマトリックス
	bool bUse; //使ってるか
	int nType;
	int nShadow;
	int des;
	float moveX;
	float moveZ;
	float consumption;
} LINE;

//プロトタイプ宣言
void InitLine(void);//初期化
void UninitLine(void);//破棄
void UpdateLine(void);//更新
void DrawLine(void);//描画
void SetLine(D3DXVECTOR3 Maxpos, D3DXVECTOR3  Minpos, D3DXVECTOR3 pos);//場所.回転.色.タイプ

#endif

