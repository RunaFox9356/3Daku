//=====================
//プレイヤーｈ
//Auther：hamada ryuuga
//=====================
#ifndef _PRAYER_H_
#define _PRAYER_H_

#include"main.h"

typedef struct
{
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
	LPD3DXMESH s_pVtxMesh;	// メッシュのポインタ
	LPD3DXBUFFER s_pBuffPrayer; //バッファのポインタ
	DWORD s_Prayer;		//マテリアル情報
	float consumption;
}PRAYER;

//プロトタイプ宣言
void InitPrayer(void);//初期化
void UninitPrayer(void);//破棄
void UpdatePrayer(void);//更新
void DrawPrayer(void);//描画
PRAYER *GetPrayer(void);//セット
void SetPrayer(D3DXVECTOR3 pos, char *Filename);//セット引数座標と読み込むファイル名
int GetnNanba(void);//ゲット(使ってる場番号)
#endif