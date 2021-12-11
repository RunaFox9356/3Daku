//======================
//影ｈ
//Auther：hamada ryuuga
//======================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include"main.h"

#define	MAX_SHADOW	(4096)
#define	MAX_RECIPE	(5)

//プロトタイプ宣言
void InitShadow(void);//初期化
void UninitShadow(void);//破棄
void UpdateShadow(void);//更新
void DrawShadow(void);//描画
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);//場所.回転
void SetposShadow(int nNumber, D3DXVECTOR3 pos);
void DisappearanceShadow(int nNumber);//影を消す
#endif