//======================
//ライトｈ
//Auther：hamada ryuuga
//======================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include"main.h"

void InitLighe(void);//初期化
void UninitLighe(void);//破棄
void UpdateLighe(void);//更新
void SetLighe(D3DXVECTOR3 pos, float fheight, float fwidth, int nType);//場所.幅.高さ.タイプ

#endif