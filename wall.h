//=======================
//�ǂ�
//Auther�Fhamada ryuuga
//=======================

#ifndef _WALL_H_
#define _WALL_H_

#include"main.h"

#define	MAX_WALL	(16)
#define	MAX_RECIPE	(5)

//�v���g�^�C�v�錾
void InitWall(void);//������
void UninitWall(void);//�j��
void UpdateWall(void);//�X�V
void DrawWall(void);//�`��
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXCOLOR col);//�ꏊ.��]


#endif
