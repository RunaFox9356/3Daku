//=====================
//�v���C���[��
//Auther�Fhamada ryuuga
//=====================
#ifndef _PRAYER_H_
#define _PRAYER_H_

#include"main.h"

#define MAX_MODELPARTS (9)
#define MAX_KEY  (5)

//�L�[�̍\����//
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3  rot;
}kEYPRAYER;

//�L�[�Z�b�g�̍\����//
typedef struct
{
	int KeyFrame;
	kEYPRAYER key[MAX_MODELPARTS];
}kEYSETPRAYER;

//model�f�[�^�̍\����//
typedef struct
{
	int  LOOP;		// ���[�v���邩�ǂ���[0:���[�v���Ȃ� / 1 : ���[�v����]
	int NUM_KEY;  	// �L�[��
	kEYSETPRAYER KeySet[MAX_KEY];
}ModelDataPRAYER;

//���f���̍\����//
typedef struct
{
	D3DXMATRIX MtxWorld; //�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	D3DXVECTOR3 pos;
	D3DXVECTOR3  rot;
	int nIdxModelParent;          //�e�̃C���f�b�N�X       aModel[   ] �̔ԍ�
}ModelParts;

typedef struct
{
	ModelParts Parts[MAX_MODELPARTS];	//model�̐�
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
	float consumption;
}PRAYER;

//�v���g�^�C�v�錾
void InitPrayer(void);//������
void UninitPrayer(void);//�j��
void UpdatePrayer(void);//�X�V
void DrawPrayer(void);//�`��
PRAYER *GetPrayer(void);//�Z�b�g
void SetPrayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *Filename, int nIdxModelParent);//�Z�b�g�������W�Ɠǂݍ��ރt�@�C����
int GetnNanba(void);//�Q�b�g(�g���Ă��ԍ�)
void SizSet(void);
#endif