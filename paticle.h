#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_


#include "main.h"

//マクロ定義
#define MAX_PARTICLE	(2048)		//パーティクルの最大数
#define NUM_PARTICLE	(24)		//パーティクルの種類
#define LIGHTNINGLIFE (120)
#define KITUNELIFE	 (150)
#define OUKANLIFE	 (70)
#define MERALIFE	(50)
//列挙型
typedef enum
{
	PARTICLETYPE_LIGHTNING = 0,		//キラキラ
	PARTICLETYPE_KITUNE,	//丸
	PARTICLETYPE_OUKAN,		//王冠
	PARTICLETYPE_MERA,		//一枚絵
	PARTICLETYPE_MAX
}PARTICLETYPE;

//構造体
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	D3DXCOLOR col;				//色
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	PARTICLETYPE type;			//パーティクルの種類
	float fWidth;				//幅
	float fHeight;				//高さ
	float fRadius;				//半径
	float fAngle;				//角度
	float fLength;				//長さ
	float fAttenuation;			//減衰
	int nLife;					//消えるまでの時間
	int nMaxLife;				//最大ライフ
	int nParticleNumber;		//パーティクルの番号
	int nCounterAnim;			//アニメーションカウント
	int nPatternAnim;			//動きのカウント
	int nDivisionMAX;				//何分割するかのカウント
	int nDivisionY;				//Y何分割するかのカウント
	int nDivisionX;				//X何分割するかのカウント
	int speed;					//アニメーションの速度
	bool bUse;					//使用しているかどうか
}PARTICLE;

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight, PARTICLETYPE type, int nLife);
void SubSetParticle(int nSubParticle, PARTICLETYPE type);
void DeleteParticle(int nParticle);
PARTICLE *GetParticle(void);

#endif