//====================================
// ファイル.h
// Auther：hamada ryuuga
//=====================================
#ifndef _FILE_H_			// このマクロ定義がされてなかったら
#define _FILE_H_			// 二重インクルード防止のマクロ定義

//=====================================
// インクルード
//=====================================
#include"main.h"
//=====================================
//　ファイルパスまとめ
//=====================================
#define FILE_3D_PRAYER  "Data/Model/"
#define FILE_3D_MODEL  "Data/Model/"
#define FILE_3D_SYSTEM "Data/system/"

#define MAX_MODELPARTS (9)
#define MAX_KEY  (5)

//キーの構造体//
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3  rot;
}kEY;

//キーセットの構造体//
typedef struct
{
	int KeyFrame;
	kEY key[MAX_MODELPARTS];
}kEYSET;

//modelデータの構造体//
typedef struct
{
	int  LOOP;		// ループするかどうか[0:ループしない / 1 : ループする]
	int NUM_KEY;  	// キー数
	kEYSET KeySet[MAX_KEY];
}ModelData;

//=====================================
// プロトタイプ宣言
//=====================================
// 制御関数
void	LoodSetFile(void);
void	OutputSetFile(void);

#endif

