
//========================
//インプットヘッター
//Auther：hamada ryuuga
//========================
#ifndef _INPUT_H_ 
#define _INPUT_H_

#include"main.h"
//キーの種類
typedef enum
{
	JOYKEY_UP = 0, //十字上キー
	JOYKEY_DOWN,	//十字下キー
	JOYKEY_LEFT,	//十字左キー
	JOYKEY_RIGHT,	//十字右キー
	JOYKEY_START,	//スタートボタン
	JOYKEY_PUSHLSTICX,//左スティック
	JOYKEY_PUSHRSTICX,//右スティック押し込み
	JOYKEY_LBUTTON5,    //左ボタン上
	JOYKEY_RBUTTON5,    //右ボタン上
	JOYKEY_10,            //不明
	JOYKEY_11,            //不明
	JOYKEY_A,            //Aボタン
	JOYKEY_X,            //Xボタン
	JOYKEY_B,            //Bボタン
	JOYKEY_Y,            //Yボタン
	JOYKE_LEFT_STICK,  //Lステイ
	JOYKE_RIGHT_STICK, //Rステイ
}JOYKEY;

//プロトタイプ宣言
HRESULT lnitKeyboard(HINSTANCE hlnstance, HWND hWnd);//キーボード
void UninitKeyboard(void);//破棄
void UpdateKeyboard(void);//更新
bool GetKeyboardPress(int nKey);//キーボード取得
bool GetKeyboardTrigger(int nKey);//キーボード取得
HRESULT lnitJoypad(void);//パット初期化
void UninitJoypad(void);//パット破棄
void UpdateJoypad(void);//パット更新
bool GetKeyboardPress(JOYKEY nKey);//パットプレス
bool GetKeyboardTrigger(JOYKEY nKey);//パットトリガー
D3DXVECTOR3 GatStick(JOYKEY nKey);//パットスティック
void vidjoipad(int Taimvib, int vibmove);//パット振動
#endif


