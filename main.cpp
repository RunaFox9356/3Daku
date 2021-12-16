//=================================================
//	アクションゲーム制作
//
//  Auther： hamadaryuuga
//=================================================
#include<stdio.h>
#include"main.h"
#include "input.h"
#include"block.h"
#include"camera.h"
#include"light.h"
#include"model.h"
#include"shadow.h"
#include"wall.h"
#include"kitune.h"
#include"file.h"
#include"mesh.h"
#include"cylinder.h"
#include"paticle.h"
#include"ken.h"
#include"effect.h"
#include"Prayer.h"

#define MAX_NAME (10)

//グローバル変数(必須)
LPDIRECT3D9 g_pD3D = NULL; //Direct3dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; //Direct3dデバイスへのぽいんた
MODE g_mode = MODE_TITLE;//モード
LPD3DXFONT g_pFont = NULL; //フォントのポインタ
int g_nCountFPS;
int g_nUseWireFrame;
bool bLine;//lineモード
//===================
//メイン関数
//===================
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hlnstacePrev, LPSTR ipCmdLine, int nCmdShow)
{
	HWND hWnd;	//Windowハンドル識別子
	MSG msg;	//メッセージを格納する変数
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),	//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,			//ウインドウのスタイル
		WindowProc,			//Windowプロシージャ  
		0,					//ゼロにする
		0,					//ゼロにする
		hinstance,			//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),//クライアントの領域背景色
		NULL,						//メニューバー
		CLASS_NAME,					//Windowクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)//ファイルアイコン
	};

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(
		0,//拡張Windowsスタイル
		CLASS_NAME,//Windowクラスの名前
		WINDOW_NAME,//Windowの名前
		WS_OVERLAPPEDWINDOW,//Windowスタイル
		CW_USEDEFAULT,//Windowの左上X座標
		CW_USEDEFAULT,//Window左上Y座標
		(rect.right - rect.left),//Window幅
		(rect.bottom - rect.top),//Window高さ
		NULL,//親Windowのハンドル
		NULL,//メニューハンドルまたは個子WindowID
		hinstance,//インスタンスハンドル
		NULL);//Window作成データ

	DWORD dwCurrentTime;//現在時刻
	DWORD dwExedastTime;//最後更新時刻
	DWORD dwFrameCount; //フレームカウント
	DWORD dwFPSLastTime; //さいごのFPS

	if (FAILED(Init(hinstance, hWnd, TRUE)))//ここをfalseにすると大画面になる
	{//初期化が失敗した場合

		return -1;
	}

	//Windowm表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//分解能の設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExedastTime = timeGetTime();

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受けとったらメッセージるーぷを抜ける
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();//現在時刻を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
			 //FPS計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExedastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExedastTime = dwCurrentTime;//処理開始の時刻[現在時刻]を保存
											  //更新処理
				Update();

				//描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}
	//終了処理
	Uninit();


	//分機能を戻す
	timeEndPeriod(1);
	//Windowクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//========================
//ウィンドウプロシージャ
//========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;//返り値を格納

	switch (uMsg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //	キーのメッセージ

		switch (wParam)
		{
		case VK_ESCAPE: //エスケープが押された
			nID = MessageBox(hWnd, "終了しますか？", "終わりのコマンド", MB_YESNO | MB_TOPMOST);
			//第一引数をNULLにするとメッセージBOXアクティブウィンドウにならない
			//第一引数をhWndにするとこのウィンドウが親(オーナー)になり、
			//このメッセージBOXを処理しない限りほかの処理ができない
			if (nID == IDYES)
			{//Windowを破壊する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
				break;
			}
			break;

		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//===================
//デバイス取得
//===================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//===================
//初期化処理
//===================
HRESULT Init(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow)//TRUE：ウインドウ/FALSE:フルスクリーン
{
	D3DDISPLAYMODE d3ddm;//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp; //プレゼンテーションパラメータ

								 //Direct3dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	if (FAILED(lnitKeyboard(hlnstance, hWnd)))
	{
		return E_FAIL;
	}

	//ポリゴンの初期化処理
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//ゲーム画面サイズ
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面サイズ
	d3dpp.BackBufferFormat = d3ddm.Format; //バックばっふぁの形式数
	d3dpp.BackBufferCount = 1;//バックばっふぁの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //だぶるばっふぁの切り替え（映像信号の同期）
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //デプスばっふぁとして１６ｂitを使う
	d3dpp.Windowed = bWindow;//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル

	//Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成()
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成()
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))

			{
				return E_FAIL;
			}
		}
	}

	//レジダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//アルファブレンド設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//アルファブレンド設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//アルファブレンド設定
	
	
	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//小さいの拡大
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);//大きいの縮小
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);


	//テクスチャステージの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//ポリゴンとテクスチャの色を混ぜる
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	
	if (FAILED(lnitKeyboard(hlnstance, hWnd)))
	{

		return E_FAIL;
	}
	if (FAILED(lnitJoypad()))
	{

		return E_FAIL;
	}

	//デバック表示用のフォント
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "UDデジタル教科書体 NP-B", &g_pFont);
	
	bLine = false;
	
	//ライト
	InitLighe();

	//カメラ
	InitCamera();

	//円柱
	InitCylinder();

	//パーティクル初期化
	InitParticle();
	
	//kenパーティクル初期化
	InitKen();

	//影
	InitShadow();

	//モデル
	InitPrayer();

	//モデル
	InitModel();
	//メッシュ
	InitMesh();

	//エフェクト
	InitEffect();

	//Initblock();

	//壁
	InitWall();
	
	//ビルボード
	InitKitune();

	//ファイル
	LoodSetFile();

	//セット
	set();

	/*InitSound(hWnd);

	InitFade(g_mode);

	ResetRanking();
*/

	return S_OK;
}

//===================
//終了処理
//===================
void Uninit(void)
{
	//ジョイパット
	UninitJoypad();

	UninitCylinder();
	//モデル
	UninitPrayer();

	//メッシュ
	UninitMesh();

	//Uninitblock();
	
	//パーティクル破棄
	UninitParticle();

	//ライト
	UninitLighe();
	
	//カメラ
	UninitCamera();
	
	UninitEffect();
	
	//kenパーティクル
	UninitKen();
	//モデル
	UninitModel();
	//影
	UninitShadow();

	//壁
	UninitWall();

	//ビルボード
	UninitKitune();
	//キーボードの終了処理
	UninitKeyboard();

	////タイトル
	//UninitTitle();

	////チュートリアル
	//UninitTutorial();

	////ゲーム
	//UninitGame();

	////リザルト
	//UninitResult();

	////ゲームオーバー
	//UninitGameover();

	////フェード
	//UninitFade();

	////サウンド終了処理
	//UninitSound();

	////ランキング終了処理
	//UninitRanking();

	//デバックの表示フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
}

//===================
//更新処理
//===================
void Update(void)
{
	//キーボードの更新処理
	UpdateKeyboard();

	//カメラ
	UpdateCylinder();
	//モデル
	UpdatePrayer();

	UpdateLighe();

	//パーティクル更新処理
	UpdateParticle();

	//kenパーティクル
	UpdateKen();

	//メッシュ
	UpdateMesh();

	//Uninitblock();
	//モデル
	UpdateModel();
	//ライト
	UpdateLighe();

	//カメラ
	UpdateCamera();

	UpdateEffect();

	//影
	UpdateShadow();

	//壁
	UpdateWall();

	//ビルボード
	UpdateKitune();

	//ジョイパット
	UpdateJoypad();

	if (GetKeyboardTrigger(DIK_P))
	{
		bLine = !bLine;
	}
	if (bLine)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//senn
	}
	if (bLine == false)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);//senn
	}

	//switch (g_mode)
	//{
	//case MODE_TITLE:
	//	UpdateTitle();
	//	break;
	//case MODE_TUTORIAL:
	//	UpdateTutorial();
	//	break;
	//case MODE_GAME:
	//	UpdateGame();
	//	break;
	//case MODE_RESULT:
	//	UpdateResult();
	//	break;
	//case MODE_GAMEOVER:
	//	UpdateGameover();
	//	break;
	//case MODE_RANKING:
	//	UpdateRanking();
	//	break;
	//}
	////フェード
	//UpdateFade();

}

//===================
//描画処理
//===================
void Draw(void)
{
	//画面クリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//成功したとき
		//Drawblock();

		//球
		DrawCylinder();
		
		//メッシュ
		DrawMesh();
		
		//kenパーティクル
		DrawKen();

		//モデル
		DrawPrayer();

		//シャドー
		DrawShadow();

		//モデル
		DrawModel();
		//かめら
		SetCamera();

		//壁
		DrawWall();
		//パーティクル描画処理
		DrawParticle();

		//エフェクト
		DrawEffect();

		//ビルボード
		DrawKitune();
		/*switch (g_mode)
		{*/
		//case MODE_TITLE:
		//	DrawTitle();
		//	break;
		//case MODE_TUTORIAL:
		//	DrawTutorial();
		//	break;
		//case MODE_GAME:
		//	DrawGame();
		//	break;
		//case MODE_RESULT:
		//	DrawResult();
		//	break;
		//case MODE_GAMEOVER:
		//	DrawGameover();
		//	break;
		//case MODE_RANKING:
		//	DrawRanking();
		//	break;
		//}
		////フェード表示
		//DrawFade();

#ifdef _DEBUG
		//debugの表示
		DrawDebug();
#endif // DEBUG
		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//セット処理
void SetMode(MODE mode)
{

	/*switch (g_mode)
	{*/
	/*case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_GAMEOVER:
		UninitGameover();
		break;
	case MODE_RANKING:
		UninitRanking();
		break;
	}
	ResetRanking();
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	case MODE_GAMEOVER:
		InitGameover();
		break;
	case MODE_RANKING:
		InitRanking();
		int pScore;
		pScore = GetScore();
		SetRanking(pScore);
		break;*/
	//}

	//g_mode = mode;
}

MODE GetMode(void)//取得
{
	return g_mode;
}

void DrawDebug(void)
{
	CAMERA *pCamera = GetCamera();
	PRAYER *pPrayer = GetPrayer();
	MESH *pMesh = GetMesh();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[MAX_NAME][256];
	int nNanba = GetnNanba();
	//文字列に代入
	wsprintf(&aStr[0][0], "FPS%d", g_nCountFPS);

	//文字列に代入
	sprintf(&aStr[1][0], "カメラ視点->(%.3f|%.3f|%.3f)", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);

	//文字列に代入
	sprintf(&aStr[2][0], "カメラ注視点->(%.3f|%.3f|%.3f)", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);

	//文字列に代入
	sprintf(&aStr[3][0], "カメラ回転->(%.3f|%.3f|%.3f)", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);

	//文字列に代入
	sprintf(&aStr[4][0], "モデル移動->(%.3f|%.3f|%.3f)", pPrayer->pos.x, pPrayer->pos.y, pPrayer->pos.z);
	
	//文字列に代入
	sprintf(&aStr[5][0], "モデル回転->(%.3f|%.3f|%.3f)", pPrayer->rot.x, pPrayer->rot.y, pPrayer->rot.z);

	sprintf(&aStr[6][0], "今動いてるモデルの番号（%d）動かすキャラ切り替えVキー", nNanba);
	
	sprintf(&aStr[7][0],"メッシュのバッファ%d,メッシュのインデックス%d サイズＸ%dサイズＹ%d", pMesh->Vtx, pMesh->Index,pMesh->xsiz, pMesh->zsiz);
	
	if (bLine)
	{
		sprintf(&aStr[8][0], "線モード[ON]");
	}
	if (bLine == false)
	{
		sprintf(&aStr[8][0], "線モード[OFF]");
	}
	wsprintf(&aStr[9][0], "★操作説明★\n視点横移動:A.D 視点縦移動:W.S\n上昇Lシフト下降Rシフト\n回転横:Q.E縦:Z.C\nカメラ移動:カーソルキー\nモデルの横移動:J.Lモデルの縦移動:I.K\n線モード:P\n狐好きでしょ？");
	for (int i = 0; i < MAX_NAME; i++)
	{
		rect = { 0,i*30,SCREEN_WIDTH,SCREEN_HEIGHT };
		//テキストの描画
		g_pFont->DrawText(NULL, &aStr[i][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 179, 0, 255));
	}	
}

void Settex(VERTEX_3D *pVtx, float left, float right, float top, float down)
{
	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, down);
	pVtx[3].tex = D3DXVECTOR2(right, down);

}
void Normal(float standard)
{
	//正規化
	if (standard > D3DX_PI)
	{
		standard -= D3DX_PI * 2;
	}
	if (standard < -D3DX_PI)
	{
		standard += D3DX_PI * 2;
	}

}
void SetNorotpos(VERTEX_3D *pVtx, float XUP, float XDW, float YUP, float YDW,float ZUP, float ZDW)
{
	pVtx[0].pos = D3DXVECTOR3(XDW, YUP,ZUP );
	pVtx[1].pos = D3DXVECTOR3(XUP, YUP,ZUP);
	pVtx[2].pos = D3DXVECTOR3(XDW, YDW,ZDW );
	pVtx[3].pos = D3DXVECTOR3(XUP, YDW,ZDW );
}
//--------------
//セットまとめ
//--------------
void set(void)
{

	//SetKitune(D3DXVECTOR3(50.0f, 0.0f, 100.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);//場所.回転.色
											 //手前 
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//場所.回転

										   //おく
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -100.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//場所.回転
										   //右
	SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//場所.回転

										   //左
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//場所.回転.色

										   //おく
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//場所.回転

	//									   //手前
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, -100.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//場所.回転

										   //右
	SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//場所.回転

										   //左
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//場所.回転.色
}

