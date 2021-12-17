//=====================
//�v���C���[��
//Auther�Fhamada ryuuga
//=====================
#ifndef _PRAYER_H_
#define _PRAYER_H_

#include"main.h"

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;
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
	LPD3DXBUFFER s_pBuffPrayer; //�o�b�t�@�̃|�C���^
	DWORD s_Prayer;		//�}�e���A�����
	float consumption;
}PRAYER;

//�v���g�^�C�v�錾
void InitPrayer(void);//������
void UninitPrayer(void);//�j��
void UpdatePrayer(void);//�X�V
void DrawPrayer(void);//�`��
PRAYER *GetPrayer(void);//�Z�b�g
void SetPrayer(D3DXVECTOR3 pos, char *Filename);//�Z�b�g�������W�Ɠǂݍ��ރt�@�C����
int GetnNanba(void);//�Q�b�g(�g���Ă��ԍ�)
#endif