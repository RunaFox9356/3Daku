//=================
//かめらｈ
//Auther：hamada ryuuga
//=================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"



//構造体
typedef struct
{
	D3DXVECTOR3 posV;	//位置
	D3DXVECTOR3 posR;	//注視点
	D3DXVECTOR3 vecU;	//ベクトル
	D3DXVECTOR3 directionV; //回転の向き位置
	D3DXVECTOR3 directionR;//回転の向き注視点
	D3DXVECTOR3 rot;//位置回転
	float fDistance;//距離
	float fDistanceY;
	bool bBool;
	D3DXVECTOR3 posVDest, posRDest;
	D3DXMATRIX MtxProje; //プロジェクションマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	D3DXMATRIX MtxView; //ビューマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
}CAMERA;

void InitCamera(void);//初期化
void UninitCamera(void);//破棄
void UpdateCamera(void);//更新
void SetCamera(void);//画面設定
CAMERA *GetCamera(void); //ゲット
#endif
