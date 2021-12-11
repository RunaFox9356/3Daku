#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

#define	MAX_EFFECT	(4096)
#define	MAX_RECIPEEFFECT	(15)

//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col; //カラー
	int nLife;			//寿命
	bool bUse;		//使用してるかどうか
	int Trigger;   //種類
	float fRadeius;//半径
	int nType;//
	D3DXMATRIX mtxWorld; //マトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
}Effect;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife);

#endif 
