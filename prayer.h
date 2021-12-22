//=====================
//プレイヤーｈ
//Auther：hamada ryuuga
//=====================
#ifndef _PRAYER_H_
#define _PRAYER_H_

#include"main.h"

#define MAX_MODELPARTS (9)
#define MAX_KEY  (5)

//キーの構造体//
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3  rot;
}kEYPRAYER;

//キーセットの構造体//
typedef struct
{
	int KeyFrame;
	kEYPRAYER key[MAX_MODELPARTS];
}kEYSETPRAYER;

//modelデータの構造体//
typedef struct
{
	int  LOOP;		// ループするかどうか[0:ループしない / 1 : ループする]
	int NUM_KEY;  	// キー数
	kEYSETPRAYER KeySet[MAX_KEY];
}ModelDataPRAYER;

//モデルの構造体//
typedef struct
{
	D3DXMATRIX MtxWorld; //マトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXVECTOR3 pos;
	D3DXVECTOR3  rot;
	int nIdxModelParent;          //親のインデックス       aModel[   ] の番号
}ModelParts;

typedef struct
{
	ModelParts Parts[MAX_MODELPARTS];	//modelの数
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;	//回転
	D3DXVECTOR3 RotMove;//回転ムーブ
	D3DXVECTOR3 ModelMin;
	D3DXVECTOR3 ModelMax;
	D3DXMATRIX MtxWorld; //マトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	int nType;			//タイプ
	int nShadow;		//影番号
	bool bUse;			//使ってるか使ってないか
	bool bMystery;
	float consumption;
}PRAYER;

//プロトタイプ宣言
void InitPrayer(void);//初期化
void UninitPrayer(void);//破棄
void UpdatePrayer(void);//更新
void DrawPrayer(void);//描画
PRAYER *GetPrayer(void);//セット
void SetPrayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *Filename, int nIdxModelParent);//セット引数座標と読み込むファイル名
int GetnNanba(void);//ゲット(使ってる場番号)
void SizSet(void);
#endif