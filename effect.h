#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

#define	MAX_EFFECT	(4096)
#define	MAX_RECIPEEFFECT	(15)

typedef enum
{
	EFFECTTYPE_LINE = 0,		//キラキラ
	EFFECTTYPE_MP,	//魔法陣
	EFFECTTYPE_OUKAN,		//王冠
	EFFECTTYPE_MERA,		//一枚絵
	EFFECTTYPE_MAX
}EFFECTTYPE;

//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		//カラー
	int nLife;			//寿命
	int Trigger;		//種類
	EFFECTTYPE nType;			//タイプ
	int nCounterAnim;
	int nPatternAnim;
	int nDivisionX;
	int nDivisionY;
	int nDivisionMAX;
	int speed;
	bool bUse;			//使用してるかどうか
	bool bZbf;			//ゼットバッファ使うかどうか
	bool bAbf;			//アルファバッファ使うかどうか
	float fRadeius;		//半径
	D3DXMATRIX mtxWorld; //マトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
}Effect;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife, EFFECTTYPE nType,bool bZbf, bool bAbf);//設定できること座標、色、半径、ライフ、タイプ、ゼットバッファ使うかどうかアルファバッファ使うかどうか

#endif 
