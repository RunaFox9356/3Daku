//=================
//���b�V����
//Auther�Fhamada ryuuga
//=================
#ifndef _MESH_H_
#define _MESH_H_

#include"main.h"

#define	MESHX	(1)
#define	MESHY	(5)
#define MAX_SIZMESH (10.0f)
#define MAX_MESH (20)
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
	int X;//�ӂ̒��_��
	int Z;//�ӂ̒��_��
	int Vtx;//���_��
	int Index; //�C���f�b�N�X
	int por;

} MESH;

//�v���g�^�C�v�錾
void InitMesh(void);//������
void UninitMesh(void);//�j��
void UpdateMesh(void);//�X�V
void DrawMesh(void);//�`��
void SetMesh(int X ,int Z);//�ꏊ.��]
MESH *GetMesh(void);

#endif