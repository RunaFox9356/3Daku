//========================
//ビルボードｈ
//Auther：hamada ryuuga
//========================

#ifndef _KITUNE_H_
#define _KITUNE_H_

#include"main.h"

#define	MAX_KITUNE	(4096)
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
} KITUNE;

//プロトタイプ宣言
void InitKitune(void);//初期化
void UninitKitune(void);//破棄
void UpdateKitune(void);//更新
void DrawKitune(void);//描画
void SetKitune(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nType);//場所.回転
KITUNE *GetKitune(void);
#endif
