//=========================
//�C���v�b�g�t�@�C��
//Auther�Fhamada ryuuga 
//=========================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256)  //�L�[���͍ő吔

//�O���[�o���֐�
LPDIRECTINPUT8 g_plnput = NULL;   //Directlnput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//���̓f�o�C�X�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];//�L�[�{�[�h�̃g���K�[���
D3DXVECTOR3 joyKeyStk;  //�X�e�B�b�N
XINPUT_STATE g_joyKeyState; //�X�e�B�b�N
int g_ajoyKeyStateTrigger;	//�W���C�p�b�h�̃g���K�[���
int g_ajoyKeyStateRelese;	//�W���C�p�b�h�̃����[�X���
XINPUT_VIBRATION nVib; //�X�e�B�b�N
int nVibTim; //�U��
int nVibPow; //�U��

//===================
//�L�[�{�[�h�������ݒ�
//===================
HRESULT lnitKeyboard(HINSTANCE hlnstance, HWND hWnd)
{
	//Directinput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hlnstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&g_plnput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(g_plnput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g�̂�ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X��
	g_pDevKeyboard->Acquire();
	return S_OK;

}

//===================
//�I������
//===================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�������
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
//�X�V����
//===================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��

	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
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
//�L�[�{�[�h�̏��
//==========================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;

}

bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;

}

//�W���C�p�b�g����������
HRESULT lnitJoypad(void)
{
	nVibTim = 0;
	nVibPow = 0;
	//�߂��肭�肠
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//xinput�̃X�e�[�g��ݒ�i�L���j
	XInputEnable(true);

	 ZeroMemory(&nVib,sizeof(XINPUT_VIBRATION));
	return S_OK;
}

//�W���C�p�b�g�̏I��
void UninitJoypad(void)
{
	//xinput�̃X�e�[�g��ݒ�i�����j
	XInputEnable(false);
}

//�W���C�p�b�g�X�V
void UpdateJoypad(void)
{
	XINPUT_STATE joyKeyState;

	//�W���C�p�b�h�̏�Ԃ̎擾
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_ajoyKeyStateTrigger = ~g_joyKeyState.Gamepad.wButtons & joyKeyState.Gamepad.wButtons;
		g_ajoyKeyStateRelese = g_joyKeyState.Gamepad.wButtons & ~joyKeyState.Gamepad.wButtons;
		g_joyKeyState = joyKeyState;	//�W���C�p�b�h�̃v���X����ۑ�
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

//�p�b�g�v���X
bool GetKeyboardPress(JOYKEY nKey)
{
	return (g_joyKeyState.Gamepad.wButtons&(0x01 << nKey)) ? true : false;
}

//�p�b�g�g���K�[
bool GetKeyboardTrigger(JOYKEY nKey)
{
	return (g_ajoyKeyStateTrigger &(0x01 << nKey)) ? true : false;
}

//�p�b�g�X�e�B�b�N
D3DXVECTOR3 GatStick(JOYKEY nKey)
{
	D3DXVECTOR3 stick;
	switch (nKey)
	{
	case JOYKE_LEFT_STICK:  //L�X�e�B�b�N
		stick = D3DXVECTOR3(g_joyKeyState.Gamepad.sThumbLX / 30000.0f, -g_joyKeyState.Gamepad.sThumbLY / 30000.0f,0.0f);
		break;
	case JOYKE_RIGHT_STICK: //R�X�e�B�b�N
		stick = D3DXVECTOR3(g_joyKeyState.Gamepad.sThumbRX / 30000.0f, -g_joyKeyState.Gamepad.sThumbRY / 30000.0f, 0.0f);
		break;
	}
	return stick;
}

//�p�b�g�U��
void vidjoipad(int Taimvib, int vibmove)
{
	nVibPow = vibmove;
	nVibTim = Taimvib;
}