//=================
//�u���b�N��
//Auther�Fhamada ryuuga
//=================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"

#define	MAX_BLOCK	(1)
#define	MAX_RECIPE	(5)

//�v���g�^�C�v�錾
void Initblock(void);//������
void Uninitblock(void);//�j��
void Updateblock(void);//�X�V
void Drawblock(void);//�`��
void Setblock(D3DXVECTOR3 pos, float fheight, float fwidth, int nType);//�ꏊ.��.����.�^�C�v
//bool CollisionblockUP(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fheight, float fwidth, int nPow);
//bool CollisionblockDW(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fheight, float fwidth);
//BLOCK *GetBlock(void);






#endif 
