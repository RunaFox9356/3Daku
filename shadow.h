//======================
//�e��
//Auther�Fhamada ryuuga
//======================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include"main.h"

#define	MAX_SHADOW	(4096)
#define	MAX_RECIPE	(5)

//�v���g�^�C�v�錾
void InitShadow(void);//������
void UninitShadow(void);//�j��
void UpdateShadow(void);//�X�V
void DrawShadow(void);//�`��
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);//�ꏊ.��]
void SetposShadow(int nNumber, D3DXVECTOR3 pos);
void DisappearanceShadow(int nNumber);//�e������
#endif