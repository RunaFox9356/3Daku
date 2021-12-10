//======================================
//���f���\������
//Auther�Fhamada ryuuga
//======================================

#include<stdio.h>
#include "model.h"
#include "input.h"
#include"camera.h"
#include"shadow.h"
#include"kitune.h"
#include"file.h"
#include"mesh.h"
#include"paticle.h"
#include"ken.h"

//�}�N��
#define Attenuation	(0.5f)		//�����W��
#define Spede	(1.0f)			//�X�s�[�h
#define WIDTH (10.0f)			//���f���̔��a
#define MAX_MODEL (16)			//�ő吔
//------------------------------------
// static�ϐ�
//------------------------------------
static MODEL Modelpolygon[MAX_MODEL];	// �|���S���̍\����
static int s_nNanba,s_nSet;//���ݎg�p���Ă��ƍő吔

//=========================================
// ����������
//=========================================
void InitModel(void)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_MODEL; i++)
	{
		// ����������
		Modelpolygon[i].s_pBuffModel = NULL;
		Modelpolygon[i].s_Model = 0;
		Modelpolygon[i].s_pVtxMesh = NULL;			//�c�@�@�@�@�@�@�@�@�@�@//��
		Modelpolygon[i].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
		Modelpolygon[i].consumption = 0.0f;
		Modelpolygon[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		Modelpolygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
		Modelpolygon[i].nShadow = 0;
		Modelpolygon[i].bUse = false;

	}
	s_nNanba = 0;
	s_nSet = 0;
}

//=========================================
// �I������
//=========================================
void UninitModel(void)
{
	for (int i = 0; i < MAX_MODEL; i++)
	{
		// ���_�o�b�t�@�[�̉��
		if (Modelpolygon[i].s_pVtxMesh != NULL)
		{
			Modelpolygon[i].s_pVtxMesh->Release();
			Modelpolygon[i].s_pVtxMesh = NULL;
		}
		if (Modelpolygon[i].s_pBuffModel != NULL)
		{
			Modelpolygon[i].s_pBuffModel->Release();
			Modelpolygon[i].s_pBuffModel = NULL;
		}
	}
	
}

//=========================================
// �X�V����
//=========================================
void UpdateModel(void)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();
	float consumption = 0;
	
	if (GetKeyboardPress(DIK_1))
	{//1�������Ƃ��p�[�e�B�N��

		SetParticle(Modelpolygon[s_nNanba].pos - D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_KITUNE, true);
		
	}
	if (GetKeyboardPress(DIK_2))
	{//1�������Ƃ��p�[�e�B�N��

		SetParticle(Modelpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_LIGHTNING, true);
	

	}if (GetKeyboardPress(DIK_3))
	{//1�������Ƃ��p�[�e�B�N��

		SetParticle(Modelpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_OUKAN, true);


	}
	//���f���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_V))
	{
		s_nNanba++;
		s_nNanba %= s_nSet;
	}
	Modelpolygon[s_nNanba].consumption = 0.0f;
	if (GetKeyboardPress(DIK_I))
	{//I�������Ƃ������
		Modelpolygon[s_nNanba].pos.x += sinf(pCamera->rot.y)*Spede;
		Modelpolygon[s_nNanba].pos.z += cosf(pCamera->rot.y)*Spede;

		Modelpolygon[s_nNanba].consumption = Modelpolygon[s_nNanba].RotMove.x - Modelpolygon[s_nNanba].rot.y + pCamera->rot.y;

	}
	if (GetKeyboardPress(DIK_K))
	{//K�������Ɖ�����
		Modelpolygon[s_nNanba].pos.x -= sinf(pCamera->rot.y)*Spede;
		Modelpolygon[s_nNanba].pos.z -= cosf(pCamera->rot.y)*Spede;

		Modelpolygon[s_nNanba].consumption = Modelpolygon[s_nNanba].RotMove.x - D3DX_PI - Modelpolygon[s_nNanba].rot.y + pCamera->rot.y;

	}
	if (GetKeyboardPress(DIK_L))
	{//L�������Ƃ��E����
		Modelpolygon[s_nNanba].pos.x -= sinf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;
		Modelpolygon[s_nNanba].pos.z -= cosf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;

		Modelpolygon[s_nNanba].consumption = Modelpolygon[s_nNanba].RotMove.y - D3DX_PI - Modelpolygon[s_nNanba].rot.y + pCamera->rot.y;

	}
	if (GetKeyboardPress(DIK_J))
	{//j�������ƍ�����
		Modelpolygon[s_nNanba].pos.x += sinf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;
		Modelpolygon[s_nNanba].pos.z += cosf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;

		Modelpolygon[s_nNanba].consumption = Modelpolygon[s_nNanba].RotMove.y - Modelpolygon[s_nNanba].rot.y + pCamera->rot.y;

	}
	if (GetKeyboardTrigger(DIK_RETURN))
	{//�G���^�[���Z�b�g
	 // ����������
		Modelpolygon[s_nNanba].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		Modelpolygon[s_nNanba].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

	}
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//SetKen(Modelpolygon[s_nNanba].pos);
		SetKitune(D3DXVECTOR3(Modelpolygon[s_nNanba].pos.x, Modelpolygon[s_nNanba].pos.y, Modelpolygon[s_nNanba].pos.z) ,
			Modelpolygon[s_nNanba].rot,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1);//�ꏊ.��].�F.�^�C�v
	}
	
	//���K��
	if (Modelpolygon[s_nNanba].consumption > D3DX_PI)
	{
		Modelpolygon[s_nNanba].consumption -= D3DX_PI * 2;
	}
	if (Modelpolygon[s_nNanba].consumption < -D3DX_PI)
	{
		Modelpolygon[s_nNanba].consumption += D3DX_PI * 2;
	}

	//���Z�ݒ�i�����j
	Modelpolygon[s_nNanba].rot.y += (Modelpolygon[s_nNanba].consumption)* Attenuation;//�ړI�̒l-���݂̒l�j�������W��

	//���K��
	if (Modelpolygon[s_nNanba].rot.y > D3DX_PI)
	{
		Modelpolygon[s_nNanba].rot.y -= D3DX_PI * 2;
	}
	if (Modelpolygon[s_nNanba].rot.y <= -D3DX_PI)
	{
		Modelpolygon[s_nNanba].rot.y += D3DX_PI * 2;
	}

	//�e�X�V
	SetposShadow(Modelpolygon[s_nNanba].nShadow, Modelpolygon[s_nNanba].pos);
	MESH *pMesh = GetMesh();
	//��
	if (Modelpolygon[s_nNanba].pos.x <pMesh->xsiz *-MAX_SIZMESH/2)
	{
		Modelpolygon[s_nNanba].pos.x = pMesh->xsiz * -MAX_SIZMESH / 2;
	}
	if (Modelpolygon[s_nNanba].pos.x >pMesh->xsiz * MAX_SIZMESH / 2)
	{
		Modelpolygon[s_nNanba].pos.x = pMesh->xsiz * MAX_SIZMESH / 2;
	}
	if (Modelpolygon[s_nNanba].pos.z < pMesh->zsiz *-MAX_SIZMESH / 2)
	{
		Modelpolygon[s_nNanba].pos.z = pMesh->zsiz * -MAX_SIZMESH / 2;
	}
	if (Modelpolygon[s_nNanba].pos.z >pMesh->zsiz * MAX_SIZMESH / 2)
	{
		Modelpolygon[s_nNanba].pos.z = pMesh->zsiz *MAX_SIZMESH / 2;
	}
}

//=========================================
// �`�揈��
//=========================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxTrans,mtxRot;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 marDef;
	D3DXMATERIAL *pMat;
	MESH *pMesh = GetMesh();
	for (int j = 0; j < s_nSet; j++)//�o�Ă郂�f���̐�������
	{
		if (Modelpolygon[j].bUse)//�g���Ă��o��
		{
			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			D3DXMatrixIdentity(&Modelpolygon[j].MtxWorld);

			if (pMesh->xsiz/ 10 ==0)
			{
				//�T�C�Y�ύX
				D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//�T�C�Y�ύX
				D3DXMatrixScaling(&mtxScale, pMesh->xsiz / 10, pMesh->xsiz / 10, pMesh->xsiz / 10);
			}
			
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&Modelpolygon[j].MtxWorld, &Modelpolygon[j].MtxWorld, &mtxScale);

			// �����𔽉f
			// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, Modelpolygon[j].rot.y, Modelpolygon[j].rot.x, Modelpolygon[j].rot.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&Modelpolygon[j].MtxWorld, &Modelpolygon[j].MtxWorld, &mtxRot);

			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, Modelpolygon[j].pos.x, Modelpolygon[j].pos.y, Modelpolygon[j].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&Modelpolygon[j].MtxWorld, &Modelpolygon[j].MtxWorld, &mtxTrans);

			// ���[���h���W�s��̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Modelpolygon[j].MtxWorld);

			//���݂̃}�e���A����ێ�
			pDevice->GetMaterial(&marDef);

			//�}�e���A���f�[�^�̃|�C���^���擾
			pMat = (D3DXMATERIAL*)Modelpolygon[j].s_pBuffModel->GetBufferPointer();

			for (int i = 0; i < (int)Modelpolygon[j].s_Model; i++)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[i].MatD3D);

				//���f���p�[�c�̕`��
				Modelpolygon[j].s_pVtxMesh->DrawSubset(i);
			}

			//���݂̃}�e���A����ێ�
			pDevice->SetMaterial(&marDef);
		}
	}


}
void SetModel(D3DXVECTOR3 pos, char *Filename)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char aFile[128] = FILE_3D_MODEL;

	strcat(aFile, &Filename[0]);//�����@aFile��-�����ɓ����

	D3DXLoadMeshFromX(&aFile[0],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Modelpolygon[s_nSet].s_pBuffModel,
		NULL,
		&Modelpolygon[s_nSet].s_Model,
		&Modelpolygon[s_nSet].s_pVtxMesh
	);

	Modelpolygon[s_nSet].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
	// ����������
	Modelpolygon[s_nSet].pos = pos;	// ���_���W
	Modelpolygon[s_nSet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
	Modelpolygon[s_nSet].nShadow = SetShadow(Modelpolygon[s_nSet].pos, Modelpolygon[s_nNanba].rot,0);//�ꏊ.��]
	Modelpolygon[s_nSet].bUse = true;
	s_nSet++;
}
//----------------------
//�Q�b�g(�\����)
//-----------------------
MODEL *GetModel(void)
{
	return &Modelpolygon[s_nNanba];
}

//----------------------
//�Q�b�g(�g���Ă��ԍ�)
//-----------------------
int GetnNanba(void)
{
	return s_nNanba;
}
