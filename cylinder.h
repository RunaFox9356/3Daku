//=================
//���b�V����
//Auther�Fhamada ryuuga
//=================
#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include"main.h"

#define	CYLINDERX	(1)
#define	CYLINDERY	(5)

//------------------------------------
// �|���S���̍\���̂��`
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 rot;	// ��]���W
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	int xsiz;//�ʐ�
	int zsiz;//�ʐ�
	int ysiz;
	int X;//�ӂ̒��_��
	int Z;//�ӂ̒��_��
	int Y;
	int Vtx;//���_��
	int Index; //�C���f�b�N�X
	int por;
} CYLINDER;

//�v���g�^�C�v�錾
void InitCylinder(void);//������
void UninitCylinder(void);//�j��
void UpdateCylinder(void);//�X�V
void DrawCylinder(void);//�`��
void SetCylinder(void);//�ꏊ.��]
CYLINDER *GetCylinder(void);

#endif