#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

#define	MAX_EFFECT	(4096)
#define	MAX_RECIPEEFFECT	(15)
#define EFFECT_LIFE (800)
typedef enum
{
	EFFECTTYPE_LINE = 0,		//�L���L��
	EFFECTTYPE_MP,		//���@�w
	EFFECTTYPE_MP2,		//���@�w
	EFFECTTYPE_MP3,		//���@�w
	EFFECTTYPE_MP4,		//���@�w
	EFFECTTYPE_MP5,		//���@�w
	EFFECTTYPE_CLOCK,	//���Ԍ�����
	EFFECTTYPE_CLOCK2,	//���ԃz�C�[��
	EFFECTTYPE_CLOCK3,	//���ԍH�ƕ�
	EFFECTTYPE_CLOCK4,	//���ԌÕ�
	EFFECTTYPE_CLOCK5,	//���v�O�g�P
	EFFECTTYPE_CLOCK6,	//���v�������O�g
	EFFECTTYPE_CLOCK7,	//���ԏ�����Ă�g
	EFFECTTYPE_CLOCK8,	//�g
	EFFECTTYPE_CLOCK9,	//�^�񒆃p�[�c
	EFFECTTYPE_CLOCK10,	//�j
	EFFECTTYPE_MAX
}EFFECTTYPE;


//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//���b�g
	D3DXCOLOR col;		//�J���[
	EFFECTTYPE nType;			//�^�C�v
	int nLife;			//����
	int nMaxLife;		//�ő�̎���
	int Trigger;		//���
	int nCounterAnim;	//�A�j���[�V�����J�E���g
	int nPatternAnim;	//�A�j���[�V�����J�E���g
	int nDivisionX;		//�A�j���[�V����X�̖���
	int nDivisionY;		//�A�j���[�V����Y�̖���
	int nDivisionMAX;	//�A�j���[�V�����̍ő喇��
	int easeInspeed;	//���[����
	int speed;			//�X�s�[�h
	bool bCol;			//�A���t�@�l�����񂾂񂾂���
	bool bSiz;			//�������Ȃ��ďo�Ă��邩
	bool bRot;			//��邩
	bool bUse;			//�g�p���Ă邩�ǂ���
	bool bZbf;			//�[�b�g�e�X�g�g�����ǂ���
	bool bAbf;			//�A���t�@�e�X�g�g�����ǂ���
	float fRadeius;		//���a
	D3DXMATRIX mtxWorld; //�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife, EFFECTTYPE nType,bool bZbf, bool bAbf, bool bCol,bool bRot);
//�ݒ�ł��邱�ƍ��W�A�F�A���a�A���C�t�A�^�C�v�A�[�b�g�e�X�g�g�����ǂ����A���t�@�e�X�g�g�����ǂ����A���t�@�l�����񂾂�傫���Ȃ邩

#endif 
