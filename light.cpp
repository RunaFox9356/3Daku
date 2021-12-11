//=======================
//���C�g�ݒ�
//Auther�Fhamada ryuuga
//=======================

#include"light.h"

#define MAXLIT (3) 
static D3DLIGHT9  s_light[MAXLIT];

//----------------------------
//����������
//----------------------------
void InitLighe(void)
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAXLIT];
	//�������N���A
	ZeroMemory(&s_light[0], sizeof(s_light));

	//0�Ԗڃ��C�g
	s_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vecDir[0] = D3DXVECTOR3(0.2f, -0.7f, -0.4f);

	//1�Ԗڃ��C�g
	s_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vecDir[1] = D3DXVECTOR3(0.2f, -0.7f, 0.4f);

	//2�Ԗڃ��C�g
	s_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	vecDir[2] = D3DXVECTOR3(0.2f, 0.7f, -0.4f);

	for (int i = 0; i < MAXLIT; i++)
	{
		//���C�g�^�C�v
		s_light[i].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�x�N�g�������P�ɂ���
		D3DXVec3Normalize(&vecDir[i], &vecDir[i]);
		s_light[i].Direction = vecDir[i];

		pDevice->SetLight(i, &s_light[i]);

		pDevice->LightEnable(i, TRUE);
	}

	
}

//----------------------------
//�I������
//----------------------------
void UninitLighe(void)
{
}

//----------------------------
//�X�V����
//----------------------------
void UpdateLighe(void)
{
}
