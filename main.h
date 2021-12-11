//========================
//���C���w�b�^�[
//Auther�Fhamada ryuuga
//========================
#ifndef _MAIN_H_
#define _MAIN_H_
#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include"dinput.h"
#include"xaudio2.h"
#include"xinput.h"//�W���C�p�b�g���͂ɕK�v

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")//�W���C�p�b�g���͂ɕK�v

//�}�N����`
#define SCREEN_WIDTH	(1280)			//���T�C�Y
#define SCREEN_HEIGHT	(720)			//�����T�C�Y
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define CLASS_NAME		"WindowClass"   //�N���X�̖��O
#define WINDOW_NAME		"�σ���"	//���O���߂�Ƃ�
#define ID_BUTTON_FINISH (101)			//�I���{�^����ID
#define WORLDSIZ (100.0f)
//���_���u�Q���v�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

//���_���u3���v�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	D3DXVECTOR3 nor;//�x�N�g��
	D3DCOLOR col;//�J���[
	D3DXVECTOR2 tex;//�e�N�X�`��

}VERTEX_3D;

//���[�h�̎��
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

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//�E�B���h�E�v���V�[�W��
HRESULT Init(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow);//������
void Uninit(void);//�j���ݒ�
void Update(void);//�X�V
void Draw(void);//�`�揈��
void SetMode(MODE mode);//�Z�b�g
MODE GetMode(void);//�擾
void DrawDebug(void);//debug����ݒ�
void Settex(VERTEX_3D *pVtx, float left, float right, float top, float down);
void Normal(float standard);
void set(void); //�Z�b�g�����܂Ƃ�
//POS�̐ݒ�܂Ƃ�
void SetNorotpos(VERTEX_3D *pVtx, float XUP, float XDW, float YUP, float YDW, float ZUP, float ZDW);


#endif
