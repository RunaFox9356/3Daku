//=========================
//インプットファイル
//Auther：hamada ryuuga 
//=========================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX (256)  //キー入力最大数

//グローバル関数
LPDIRECTINPUT8 g_plnput = NULL;   //Directlnputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//入力デバイスへのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];//キーボードのトリガー情報
D3DXVECTOR3 joyKeyStk;  //スティック
XINPUT_STATE g_joyKeyState; //スティック
int g_ajoyKeyStateTrigger;	//ジョイパッドのトリガー情報
int g_ajoyKeyStateRelese;	//ジョイパッドのリリース情報
XINPUT_VIBRATION nVib; //スティック
int nVibTim; //振動
int nVibPow; //振動

//===================
//キーボード初期化設定
//===================
HRESULT lnitKeyboard(HINSTANCE hlnstance, HWND hWnd)
{
	//Directinputオブジェクトの生成
	if (FAILED(DirectInput8Create(hlnstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_plnput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイス（キーボード）の生成
	if (FAILED(g_plnput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットのを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権
	g_pDevKeyboard->Acquire();
	return S_OK;

}

//===================
//終了処理
//===================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//キーボードへのアクセス権を放棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	if (g_plnput != NULL)
	{
		g_plnput->Release();
		g_plnput = NULL;
	}
}

//===================
//更新処理
//===================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報

	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])& aKeyState[nCntKey];
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

//==========================
//キーボードの情報
//==========================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;

}

bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;

}

//ジョイパット初期化処理
HRESULT lnitJoypad(void)
{
	nVibTim = 0;
	nVibPow = 0;
	//めもりくりあ
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//xinputのステートを設定（有効）
	XInputEnable(true);

	 ZeroMemory(&nVib,sizeof(XINPUT_VIBRATION));
	return S_OK;
}

//ジョイパットの終了
void UninitJoypad(void)
{
	//xinputのステートを設定（無効）
	XInputEnable(false);
}

//ジョイパット更新
void UpdateJoypad(void)
{
	XINPUT_STATE joyKeyState;

	//ジョイパッドの状態の取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_ajoyKeyStateTrigger = ~g_joyKeyState.Gamepad.wButtons & joyKeyState.Gamepad.wButtons;
		g_ajoyKeyStateRelese = g_joyKeyState.Gamepad.wButtons & ~joyKeyState.Gamepad.wButtons;
		g_joyKeyState = joyKeyState;	//ジョイパッドのプレス情報を保存
	}
	nVib.wLeftMotorSpeed = nVibPow;
	nVib.wRightMotorSpeed = nVibPow;

	XInputSetState(0, &nVib);

	if (nVibTim > 0)
	{
		nVibTim--;
	}
	else
	{
		nVibPow = 0;
		nVibTim = 0;
	}
}

//パットプレス
bool GetKeyboardPress(JOYKEY nKey)
{
	return (g_joyKeyState.Gamepad.wButtons&(0x01 << nKey)) ? true : false;
}

//パットトリガー
bool GetKeyboardTrigger(JOYKEY nKey)
{
	return (g_ajoyKeyStateTrigger &(0x01 << nKey)) ? true : false;
}

//パットスティック
D3DXVECTOR3 GatStick(JOYKEY nKey)
{
	D3DXVECTOR3 stick;
	switch (nKey)
	{
	case JOYKE_LEFT_STICK:  //Lスティック
		stick = D3DXVECTOR3(g_joyKeyState.Gamepad.sThumbLX / 30000.0f, -g_joyKeyState.Gamepad.sThumbLY / 30000.0f,0.0f);
		break;
	case JOYKE_RIGHT_STICK: //Rスティック
		stick = D3DXVECTOR3(g_joyKeyState.Gamepad.sThumbRX / 30000.0f, -g_joyKeyState.Gamepad.sThumbRY / 30000.0f, 0.0f);
		break;
	}
	return stick;
}

//パット振動
void vidjoipad(int Taimvib, int vibmove)
{
	nVibPow = vibmove;
	nVibTim = Taimvib;
}