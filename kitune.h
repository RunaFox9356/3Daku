//========================
//�r���{�[�h��
//Auther�Fhamada ryuuga
//========================

#ifndef _KITUNE_H_
#define _KITUNE_H_

#include"main.h"

#define	MAX_KITUNE	(4096)
#define	MAX_RECIPE	(5)
#define MAX_TEX (2)
#define BallSpede (1)

//------------------------------------
// �|���S���̍\���̂��`
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 rot;	// ��]���W
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	bool bUse; //�g���Ă邩
	int nType;
	int nShadow;
	int des;
	float moveX;
	float moveZ;
	float consumption;
} KITUNE;

//�v���g�^�C�v�錾
void InitKitune(void);//������
void UninitKitune(void);//�j��
void UpdateKitune(void);//�X�V
void DrawKitune(void);//�`��
void SetKitune(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, int nType);//�ꏊ.��]
KITUNE *GetKitune(void);
#endif
