#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

#define	MAX_EFFECT	(4096)
#define	MAX_RECIPEEFFECT	(15)

//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col; //�J���[
	int nLife;			//����
	bool bUse;		//�g�p���Ă邩�ǂ���
	int Trigger;   //���
	float fRadeius;//���a
	int nType;//
	D3DXMATRIX mtxWorld; //�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife);

#endif 
