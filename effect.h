#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"main.h"

#define	MAX_EFFECT	(4096)
#define	MAX_RECIPEEFFECT	(15)
#define EFFECT_LIFE (800)

#define LOOD_FILE_NAME_EFFECT		"Effect.txt"
#define LOOD_FILE_NAME_MAGIC		"Magic.txt"
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
	EFFECTTYPE_CLOCK10,	//�Z�j
	EFFECTTYPE_CLOCK11, //���j
	EFFECTTYPE_MAX
}EFFECTTYPE;

typedef enum
{
	LISTS_ZERO = 0,	//0
	LISTS_I,		//1
	LISTS_II,		//2
	LISTS_III,		//3
	LISTS_IV,		//4
	LISTS_V,		//5
	LISTS_VI,		//6
	LISTS_VII,		//7
	LISTS_VIII,		//8
	LISTS_IX,		//9
	LISTS_X,		//10
	LISTS_XI,		//11
	LISTS_XII,		//12
	LISTS_XIII,		//13
	LISTS_XIV,		//14
	LISTS_XV,		//15
	LISTS_XVI,		//16
	LISTS_XVII,		//17
	LISTS_XVIII,	//18
	LISTS_XVIX,		//19
	LISTS_XX,		//20
	LISTS_XXI,		//21
	LISTS_XXII,		//22
	LISTS_XXIII,	//23
	LISTS_XXIV,		//24
	LISTS_XXV,		//25
	LISTS_XXVI,		//26
	LISTS_XXVII,	//27
	LISTS_XXVIII,	//28
	LISTS_XXIX,		//29
	LISTS_MAX		//30
}LISTS;


//�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//���b�g
	D3DXCOLOR col;		//�J���[
	EFFECTTYPE nType;	//�^�C�v
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
	int RotSpin;		//��]���x
	float fRadeius;		//���a
	bool bSpin;			//��邩���Ȃ���
	bool bCourse;	//��]�������
	bool bCol;			//�A���t�@�l�����񂾂񂾂���
	bool bSiz;			//�������Ȃ��ďo�Ă��邩
	bool bLin;			//�g����
	bool bRot;			//���Ă邩���ɂȂ��Ă邩
	bool bUse;			//�g�p���Ă邩�ǂ���
	bool bZbf;			//�[�b�g�e�X�g�g�����ǂ���
	bool bAbf;			//�A���t�@�e�X�g�g�����ǂ���
	D3DXMATRIX mtxWorld; //�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
}Effect;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//���b�g
	D3DXCOLOR col;		//�J���[
	EFFECTTYPE nType;	//�^�C�v
	float fRadeius;		//���a
	int nMaxLife;		//�ő�̎���
	int RotSpin;		//��]���x
	bool bCourse;	//��]�������
	bool bSpin;			//��邩���Ȃ���
	bool bCol;			//�A���t�@�l�����񂾂񂾂���
	bool bRot;			//��邩
	bool bLin;
	bool bUse;			//�g�p���Ă邩�ǂ���
	bool bZbf;			//�[�b�g�e�X�g�g�����ǂ���
	bool bAbf;			//�A���t�@�e�X�g�g�����ǂ���
}EffectFile;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(int a);
void SetEffectFile(char *Filename);
//�ݒ�ł��邱�ƍ��W�A�F�A���a�A���C�t�A�^�C�v�A�[�b�g�e�X�g�g�����ǂ����A���t�@�e�X�g�g�����ǂ����A���t�@�l�����񂾂�傫���Ȃ邩

#endif 
