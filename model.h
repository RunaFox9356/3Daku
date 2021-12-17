//=====================
//���f����
//Auther�Fhamada ryuuga
//=====================
#ifndef _MODEL_H_
#define _MODEL_H_

#include"main.h"

typedef struct
{ 
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//��]
	D3DXVECTOR3 RotMove;//��]���[�u
	D3DXVECTOR3 ModelMin;
	D3DXVECTOR3 ModelMax;
	D3DXMATRIX MtxWorld; //�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	int nType;			//�^�C�v
	int nShadow;		//�e�ԍ�
	bool bUse;			//�g���Ă邩�g���ĂȂ���
	bool bMystery;
	LPD3DXMESH s_pVtxMesh;	// ���b�V���̃|�C���^
	LPD3DXBUFFER s_pBuffModel; //�o�b�t�@�̃|�C���^
	DWORD s_Model;		//�}�e���A�����
	float consumption;
}MODEL;

//�v���g�^�C�v�錾
void InitModel(void);//������
void UninitModel(void);//�j��
void UpdateModel(void);//�X�V
void DrawModel(void);//�`��
void SetModel(D3DXVECTOR3 pos, char *Filename);//�Z�b�g�������W�Ɠǂݍ��ރt�@�C����
MODEL *GetModel(void);
void  CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Max, D3DXVECTOR3 Min);

#endif