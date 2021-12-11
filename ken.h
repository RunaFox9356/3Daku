//=====================
//モデルｈ
//Auther：hamada ryuuga
//=====================
#ifndef _KEN_H_
#define _KEN_H_

#include"main.h"

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//回転
	D3DXVECTOR3 RotMove;//回転ムーブ
	D3DXMATRIX MtxWorld; //マトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	D3DXVECTOR3 move;
	int nType;			//タイプ
	int nShadow;		//影番号
	int nLif;//ライフ
	bool bUse;			//使ってるか使ってないか
	bool bFri;			//使ってるか使ってないか
	LPD3DXMESH s_pVtxMesh;	// メッシュのポインタ
	LPD3DXBUFFER s_pBuffKen; //バッファのポインタ
	DWORD s_Ken;		//マテリアル情報
	float consumption;

}KEN;

//プロトタイプ宣言
void InitKen(void);//初期化
void UninitKen(void);//破棄
void UpdateKen(void);//更新
void DrawKen(void);//描画
KEN *GetKen(void);//セット
void SetKen(D3DXVECTOR3 pos);//セット引数座標と読み込むファイル名

#endif