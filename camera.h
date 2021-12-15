//=================
//���߂炈
//Auther�Fhamada ryuuga
//=================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"



//�\����
typedef struct
{
	D3DXVECTOR3 posV;	//�ʒu
	D3DXVECTOR3 posR;	//�����_
	D3DXVECTOR3 vecU;	//�x�N�g��
	D3DXVECTOR3 directionV; //��]�̌����ʒu
	D3DXVECTOR3 directionR;//��]�̌��������_
	D3DXVECTOR3 rot;//�ʒu��]
	float fDistance;//����
	float fDistanceY;
	bool bBool;
	D3DXVECTOR3 posVDest, posRDest;
	D3DXMATRIX MtxProje; //�v���W�F�N�V�����}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	D3DXMATRIX MtxView; //�r���[�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
}CAMERA;

void InitCamera(void);//������
void UninitCamera(void);//�j��
void UpdateCamera(void);//�X�V
void SetCamera(void);//��ʐݒ�
CAMERA *GetCamera(void); //�Q�b�g
#endif
