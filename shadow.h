//======================
//e
//AutherFhamada ryuuga
//======================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include"main.h"

#define	MAX_SHADOW	(4096)
#define	MAX_RECIPE	(5)

//vg^CvιΎ
void InitShadow(void);//ϊ»
void UninitShadow(void);//jό
void UpdateShadow(void);//XV
void DrawShadow(void);//`ζ
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);//κ.ρ]
void SetposShadow(int nNumber, D3DXVECTOR3 pos);
void DisappearanceShadow(int nNumber);//eπΑ·
#endif