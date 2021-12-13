#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

#define	MAX_EFFECT	(4096)
#define	MAX_RECIPEEFFECT	(15)

typedef enum
{
	EFFECTTYPE_LINE = 0,		//�L���L��
	EFFECTTYPE_MP,	//���@�w
	EFFECTTYPE_OUKAN,		//����
	EFFECTTYPE_MERA,		//�ꖇ�G
	EFFECTTYPE_MAX
}EFFECTTYPE;

//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�J���[
	int nLife;			//����
	int Trigger;		//���
	EFFECTTYPE nType;			//�^�C�v
	int nCounterAnim;
	int nPatternAnim;
	int nDivisionX;
	int nDivisionY;
	int nDivisionMAX;
	int speed;
	bool bUse;			//�g�p���Ă邩�ǂ���
	bool bZbf;			//�[�b�g�o�b�t�@�g�����ǂ���
	bool bAbf;			//�A���t�@�o�b�t�@�g�����ǂ���
	float fRadeius;		//���a
	D3DXMATRIX mtxWorld; //�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife, EFFECTTYPE nType,bool bZbf, bool bAbf);//�ݒ�ł��邱�ƍ��W�A�F�A���a�A���C�t�A�^�C�v�A�[�b�g�o�b�t�@�g�����ǂ����A���t�@�o�b�t�@�g�����ǂ���

#endif 
