//========================
//�r���{�[�h��
//Auther�Fhamada ryuuga
//========================

#ifndef _LINE_H_
#define _LINE_H_

#include"main.h"

#define	MAX_LINE	(4096)
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
} LINE;

//�v���g�^�C�v�錾
void InitLine(void);//������
void UninitLine(void);//�j��
void UpdateLine(void);//�X�V
void DrawLine(void);//�`��
void SetLine(D3DXVECTOR3 Maxpos, D3DXVECTOR3  Minpos, D3DXVECTOR3 pos);//�ꏊ.��].�F.�^�C�v

#endif

