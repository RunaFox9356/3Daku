//=====================
//���f����
//Auther�Fhamada ryuuga
//=====================
#ifndef _KEN_H_
#define _KEN_H_

#include"main.h"

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//��]
	D3DXVECTOR3 RotMove;//��]���[�u
	D3DXMATRIX MtxWorld; //�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	D3DXVECTOR3 move;
	int nType;			//�^�C�v
	int nShadow;		//�e�ԍ�
	int nLif;//���C�t
	bool bUse;			//�g���Ă邩�g���ĂȂ���
	bool bFri;			//�g���Ă邩�g���ĂȂ���
	LPD3DXMESH s_pVtxMesh;	// ���b�V���̃|�C���^
	LPD3DXBUFFER s_pBuffKen; //�o�b�t�@�̃|�C���^
	DWORD s_Ken;		//�}�e���A�����
	float consumption;

}KEN;

//�v���g�^�C�v�錾
void InitKen(void);//������
void UninitKen(void);//�j��
void UpdateKen(void);//�X�V
void DrawKen(void);//�`��
KEN *GetKen(void);//�Z�b�g
void SetKen(D3DXVECTOR3 pos);//�Z�b�g�������W�Ɠǂݍ��ރt�@�C����

#endif