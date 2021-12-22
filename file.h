//====================================
// �t�@�C��.h
// Auther�Fhamada ryuuga
//=====================================
#ifndef _FILE_H_			// ���̃}�N����`������ĂȂ�������
#define _FILE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//=====================================
// �C���N���[�h
//=====================================
#include"main.h"
//=====================================
//�@�t�@�C���p�X�܂Ƃ�
//=====================================
#define FILE_3D_PRAYER  "Data/Model/"
#define FILE_3D_MODEL  "Data/Model/"
#define FILE_3D_SYSTEM "Data/system/"

#define MAX_MODELPARTS (9)
#define MAX_KEY  (5)

//�L�[�̍\����//
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3  rot;
}kEY;

//�L�[�Z�b�g�̍\����//
typedef struct
{
	int KeyFrame;
	kEY key[MAX_MODELPARTS];
}kEYSET;

//model�f�[�^�̍\����//
typedef struct
{
	int  LOOP;		// ���[�v���邩�ǂ���[0:���[�v���Ȃ� / 1 : ���[�v����]
	int NUM_KEY;  	// �L�[��
	kEYSET KeySet[MAX_KEY];
}ModelData;

//=====================================
// �v���g�^�C�v�錾
//=====================================
// ����֐�
void	LoodSetFile(void);
void	OutputSetFile(void);

#endif

