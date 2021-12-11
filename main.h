//========================
//メインヘッター
//Auther：hamada ryuuga
//========================
#ifndef _MAIN_H_
#define _MAIN_H_
#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include"dinput.h"
#include"xaudio2.h"
#include"xinput.h"//ジョイパット入力に必要

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")//ジョイパット入力に必要

//マクロ定義
#define SCREEN_WIDTH	(1280)			//幅サイズ
#define SCREEN_HEIGHT	(720)			//高さサイズ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define CLASS_NAME		"WindowClass"   //クラスの名前
#define WINDOW_NAME		"狐ラン"	//名前決めるとこ
#define ID_BUTTON_FINISH (101)			//終了ボタンのID
#define WORLDSIZ (100.0f)
//頂点情報「２ｄ」の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

//頂点情報「3ｄ」の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	D3DXVECTOR3 nor;//ベクトル
	D3DCOLOR col;//カラー
	D3DXVECTOR2 tex;//テクスチャ

}VERTEX_3D;

//モードの種類
typedef enum
{
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_GAMEOVER,
	MODE_RANKING,
	MODE_MAX
}MODE;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//ウィンドウプロシージャ
HRESULT Init(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow);//初期化
void Uninit(void);//破棄設定
void Update(void);//更新
void Draw(void);//描画処理
void SetMode(MODE mode);//セット
MODE GetMode(void);//取得
void DrawDebug(void);//debugこれ設定
void Settex(VERTEX_3D *pVtx, float left, float right, float top, float down);
void Normal(float standard);
void set(void); //セット処理まとめ
//POSの設定まとめ
void SetNorotpos(VERTEX_3D *pVtx, float XUP, float XDW, float YUP, float YDW, float ZUP, float ZDW);


#endif
