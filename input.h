
//========================
//�C���v�b�g�w�b�^�[
//Auther�Fhamada ryuuga
//========================
#ifndef _INPUT_H_ 
#define _INPUT_H_

#include"main.h"
//�L�[�̎��
typedef enum
{
	JOYKEY_UP = 0, //�\����L�[
	JOYKEY_DOWN,	//�\�����L�[
	JOYKEY_LEFT,	//�\�����L�[
	JOYKEY_RIGHT,	//�\���E�L�[
	JOYKEY_START,	//�X�^�[�g�{�^��
	JOYKEY_PUSHLSTICX,//���X�e�B�b�N
	JOYKEY_PUSHRSTICX,//�E�X�e�B�b�N��������
	JOYKEY_LBUTTON5,    //���{�^����
	JOYKEY_RBUTTON5,    //�E�{�^����
	JOYKEY_10,            //�s��
	JOYKEY_11,            //�s��
	JOYKEY_A,            //A�{�^��
	JOYKEY_X,            //X�{�^��
	JOYKEY_B,            //B�{�^��
	JOYKEY_Y,            //Y�{�^��
	JOYKE_LEFT_STICK,  //L�X�e�C
	JOYKE_RIGHT_STICK, //R�X�e�C
}JOYKEY;

//�v���g�^�C�v�錾
HRESULT lnitKeyboard(HINSTANCE hlnstance, HWND hWnd);//�L�[�{�[�h
void UninitKeyboard(void);//�j��
void UpdateKeyboard(void);//�X�V
bool GetKeyboardPress(int nKey);//�L�[�{�[�h�擾
bool GetKeyboardTrigger(int nKey);//�L�[�{�[�h�擾
HRESULT lnitJoypad(void);//�p�b�g������
void UninitJoypad(void);//�p�b�g�j��
void UpdateJoypad(void);//�p�b�g�X�V
bool GetKeyboardPress(JOYKEY nKey);//�p�b�g�v���X
bool GetKeyboardTrigger(JOYKEY nKey);//�p�b�g�g���K�[
D3DXVECTOR3 GatStick(JOYKEY nKey);//�p�b�g�X�e�B�b�N
void vidjoipad(int Taimvib, int vibmove);//�p�b�g�U��
#endif


