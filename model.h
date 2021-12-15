//=====================
//モデルｈ
//Auther：hamada ryuuga
//=====================
#ifndef _MODEL_H_
#define _MODEL_H_

#include"main.h"

typedef struct
{ 
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//回転
	D3DXVECTOR3 RotMove;//回転ムーブ
	D3DXMATRIX MtxWorld; //マトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	int nType;			//タイプ
	int nShadow;		//影番号
	bool bUse;			//使ってるか使ってないか
	bool bMystery;
	LPD3DXMESH s_pVtxMesh;	// メッシュのポインタ
	LPD3DXBUFFER s_pBuffModel; //バッファのポインタ
	DWORD s_Model;		//マテリアル情報
	float consumption;
}MODEL;

//プロトタイプ宣言
void InitModel(void);//初期化
void UninitModel(void);//破棄
void UpdateModel(void);//更新
void DrawModel(void);//描画
MODEL *GetModel(void);//セット
void SetModel(D3DXVECTOR3 pos, char *Filename);//セット引数座標と読み込むファイル名
int GetnNanba(void);//ゲット(使ってる場番号)
#endif