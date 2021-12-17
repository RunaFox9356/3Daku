#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

#define	MAX_EFFECT	(4096)
#define	MAX_RECIPEEFFECT	(15)
#define EFFECT_LIFE (800)

#define LOOD_FILE_NAME_EFFECT		"Effect.txt"
#define LOOD_FILE_NAME_MAGIC		"Magic.txt"
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
	EFFECTTYPE_CLOCK10,	//短針
	EFFECTTYPE_CLOCK11, //長針
	EFFECTTYPE_MAX
}EFFECTTYPE;

typedef enum
{
	LISTS_ZERO = 0,	//0
	LISTS_I,		//1
	LISTS_II,		//2
	LISTS_III,		//3
	LISTS_IV,		//4
	LISTS_V,		//5
	LISTS_VI,		//6
	LISTS_VII,		//7
	LISTS_VIII,		//8
	LISTS_IX,		//9
	LISTS_X,		//10
	LISTS_XI,		//11
	LISTS_XII,		//12
	LISTS_XIII,		//13
	LISTS_XIV,		//14
	LISTS_XV,		//15
	LISTS_XVI,		//16
	LISTS_XVII,		//17
	LISTS_XVIII,	//18
	LISTS_XVIX,		//19
	LISTS_XX,		//20
	LISTS_XXI,		//21
	LISTS_XXII,		//22
	LISTS_XXIII,	//23
	LISTS_XXIV,		//24
	LISTS_XXV,		//25
	LISTS_XXVI,		//26
	LISTS_XXVII,	//27
	LISTS_XXVIII,	//28
	LISTS_XXIX,		//29
	LISTS_MAX		//30
}LISTS;


//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//ロット
	D3DXCOLOR col;		//カラー
	EFFECTTYPE nType;	//タイプ
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
	int RotSpin;		//回転速度
	float fRadeius;		//半径
	bool bSpin;			//回るか回らないか
	bool bCourse;	//回転する向き
	bool bCol;			//アルファ値をだんだんだすか
	bool bSiz;			//小さくなって出てくるか
	bool bLin;			//枠線化
	bool bRot;			//立てるか横になってるか
	bool bUse;			//使用してるかどうか
	bool bZbf;			//ゼットテスト使うかどうか
	bool bAbf;			//アルファテスト使うかどうか
	D3DXMATRIX mtxWorld; //マトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
}Effect;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//ロット
	D3DXCOLOR col;		//カラー
	EFFECTTYPE nType;	//タイプ
	float fRadeius;		//半径
	int nMaxLife;		//最大の寿命
	int RotSpin;		//回転速度
	bool bCourse;	//回転する向き
	bool bSpin;			//回るか回らないか
	bool bCol;			//アルファ値をだんだんだすか
	bool bRot;			//回るか
	bool bLin;
	bool bUse;			//使用してるかどうか
	bool bZbf;			//ゼットテスト使うかどうか
	bool bAbf;			//アルファテスト使うかどうか
}EffectFile;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(int a);
void SetEffectFile(char *Filename);
//設定できること座標、色、半径、ライフ、タイプ、ゼットテスト使うかどうかアルファテスト使うかどうかアルファ値がだんだん大きくなるか

#endif 
