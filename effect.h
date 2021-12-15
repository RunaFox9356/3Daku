#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

#define	MAX_EFFECT	(4096)
#define	MAX_RECIPEEFFECT	(15)
#define EFFECT_LIFE (800)
typedef enum
{
	EFFECTTYPE_LINE = 0,		//キラキラ
	EFFECTTYPE_MP,		//魔法陣
	EFFECTTYPE_MP2,		//魔法陣
	EFFECTTYPE_MP3,		//魔法陣
	EFFECTTYPE_MP4,		//魔法陣
	EFFECTTYPE_MP5,		//魔法陣
	EFFECTTYPE_CLOCK,	//歯車穴あき
	EFFECTTYPE_CLOCK2,	//歯車ホイール
	EFFECTTYPE_CLOCK3,	//歯車工業風
	EFFECTTYPE_CLOCK4,	//歯車古風
	EFFECTTYPE_CLOCK5,	//時計外枠１
	EFFECTTYPE_CLOCK6,	//時計内巻き外枠
	EFFECTTYPE_CLOCK7,	//時間書かれてる枠
	EFFECTTYPE_CLOCK8,	//枠
	EFFECTTYPE_CLOCK9,	//真ん中パーツ
	EFFECTTYPE_CLOCK10,	//針
	EFFECTTYPE_MAX
}EFFECTTYPE;


//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//ロット
	D3DXCOLOR col;		//カラー
	EFFECTTYPE nType;			//タイプ
	int nLife;			//寿命
	int nMaxLife;		//最大の寿命
	int Trigger;		//種類
	int nCounterAnim;	//アニメーションカウント
	int nPatternAnim;	//アニメーションカウント
	int nDivisionX;		//アニメーションXの枚数
	int nDivisionY;		//アニメーションYの枚数
	int nDivisionMAX;	//アニメーションの最大枚数
	int easeInspeed;	//いーじんぐ
	int speed;			//スピード
	bool bCol;			//アルファ値をだんだんだすか
	bool bSiz;			//小さくなって出てくるか
	bool bRot;			//回るか
	bool bUse;			//使用してるかどうか
	bool bZbf;			//ゼットテスト使うかどうか
	bool bAbf;			//アルファテスト使うかどうか
	float fRadeius;		//半径
	D3DXMATRIX mtxWorld; //マトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
}Effect;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife, EFFECTTYPE nType,bool bZbf, bool bAbf, bool bCol,bool bRot);
//設定できること座標、色、半径、ライフ、タイプ、ゼットテスト使うかどうかアルファテスト使うかどうかアルファ値がだんだん大きくなるか

#endif 
