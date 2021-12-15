//=================
//ブロックｈ
//Auther：hamada ryuuga
//=================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"

#define	MAX_BLOCK	(1)
#define	MAX_RECIPE	(5)

//プロトタイプ宣言
void Initblock(void);//初期化
void Uninitblock(void);//破棄
void Updateblock(void);//更新
void Drawblock(void);//描画
void Setblock(D3DXVECTOR3 pos, float fheight, float fwidth, int nType);//場所.幅.高さ.タイプ
//bool CollisionblockUP(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fheight, float fwidth, int nPow);
//bool CollisionblockDW(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fheight, float fwidth);
//BLOCK *GetBlock(void);






#endif 
