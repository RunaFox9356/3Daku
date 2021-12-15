//=======================
//壁ｈ
//Auther：hamada ryuuga
//=======================

#ifndef _WALL_H_
#define _WALL_H_

#include"main.h"

#define	MAX_WALL	(16)
#define	MAX_RECIPE	(5)

//プロトタイプ宣言
void InitWall(void);//初期化
void UninitWall(void);//破棄
void UpdateWall(void);//更新
void DrawWall(void);//描画
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col);//場所.回転


#endif
