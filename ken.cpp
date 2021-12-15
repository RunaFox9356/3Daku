//======================================
//���f���\������
//Auther�Fhamada ryuuga
//======================================

#include<stdio.h>
#include "ken.h"
#include"model.h"
#include "input.h"
#include"camera.h"
#include"shadow.h"
#include"kitune.h"
#include"file.h"
#include"mesh.h"
#include"paticle.h"
#include"effect.h"

//�}�N��
#define Attenuation	(0.5f)		//�����W��
#define Spede	(10.0f)			//�X�s�[�h
#define WIDTH (10.0f)			//���f���̔��a
#define MAX_KEN (6)			//�ő吔
//------------------------------------
// static�ϐ�
//------------------------------------
static KEN Kenpolygon[MAX_KEN];	// �|���S���̍\����


//=========================================
// ����������
//=========================================
void InitKen(void)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�J�����̃f�[�^�擾
	MODEL *pModel;
	pModel = GetModel();

	for (int i = 0; i < MAX_KEN; i++)
	{
		// ����������
		Kenpolygon[i].s_pBuffKen = NULL;
		Kenpolygon[i].s_Ken = 0;
		Kenpolygon[i].s_pVtxMesh = NULL;			//�c�@�@�@�@�@�@�@�@�@�@//��
		Kenpolygon[i].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
		Kenpolygon[i].consumption = 0.0f;
		Kenpolygon[i].nLif = 100;
		if (i <= MAX_KEN/2)
		{
			Kenpolygon[i].pos = Kenpolygon[i].pos = D3DXVECTOR3(pModel->pos.x + (10 * i), pModel->pos.y, pModel->pos.z);
		}
		else
		{
			Kenpolygon[i].pos = Kenpolygon[i].pos = D3DXVECTOR3(pModel->pos.x - (10 * (i/2)), pModel->pos.y, pModel->pos.z);
		}
		Kenpolygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
		Kenpolygon[i].bUse = true;
		Kenpolygon[i].bFri = false;


	}
	
	D3DXLoadMeshFromX("Data/Model/2dure.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[0].s_pBuffKen,
		NULL,		
		&Kenpolygon[0].s_Ken,
		&Kenpolygon[0].s_pVtxMesh
	);

	D3DXLoadMeshFromX("Data/Model/ru-n.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[1].s_pBuffKen,
		NULL,
		&Kenpolygon[1].s_Ken,
		&Kenpolygon[1].s_pVtxMesh
	);

	D3DXLoadMeshFromX("Data/Model/ru-n.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[2].s_pBuffKen,
		NULL,		
		&Kenpolygon[2].s_Ken,
		&Kenpolygon[2].s_pVtxMesh
	);
	D3DXLoadMeshFromX("Data/Model/basuta.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[3].s_pBuffKen,
		NULL,		
		&Kenpolygon[3].s_Ken,
		&Kenpolygon[3].s_pVtxMesh
	);
	D3DXLoadMeshFromX("Data/Model/basuta.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[4].s_pBuffKen,
		NULL,		
		&Kenpolygon[4].s_Ken,
		&Kenpolygon[4].s_pVtxMesh
	);
	D3DXLoadMeshFromX("Data/Model/fa-suto.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Kenpolygon[5].s_pBuffKen,
		NULL,		
		&Kenpolygon[5].s_Ken,
		&Kenpolygon[5].s_pVtxMesh
	);

}

//=========================================
// �I������
//=========================================
void UninitKen(void)
{
	for (int i = 0; i < MAX_KEN; i++)
	{
		// ���_�o�b�t�@�[�̉��
		if (Kenpolygon[i].s_pVtxMesh != NULL)
		{
			Kenpolygon[i].s_pVtxMesh->Release();
			Kenpolygon[i].s_pVtxMesh = NULL;
		}
		if (Kenpolygon[i].s_pBuffKen != NULL)
		{
			Kenpolygon[i].s_pBuffKen->Release();
			Kenpolygon[i].s_pBuffKen = NULL;
		}
	}

}

//=========================================
// �X�V����
//=========================================
void UpdateKen(void)
{	//�J�����̃f�[�^�擾
	MODEL *pModel;
	pModel = GetModel();
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();
	float consumption = 0;
	for (int i = 0; i < MAX_KEN; i++)
	{

		if (Kenpolygon[i].bUse)
		{

		if (GetKeyboardTrigger(DIK_SPACE))
		{
			Kenpolygon[i].bFri = true;	
			Kenpolygon[i].move.x = sinf(pModel->rot.y);
			Kenpolygon[i].move.y = cosf(pModel->rot.y);
		}
		if (GetKeyboardTrigger(DIK_O))
		{
			Kenpolygon[i].bFri = false;
			Kenpolygon[i].move.x = sinf(pModel->rot.y);
			Kenpolygon[i].move.y = cosf(pModel->rot.y);
		}

		
			Kenpolygon[i].consumption = 0.0f;
			if (Kenpolygon[i].bFri ==true)
			{
				//SetEffect(Kenpolygon[i].pos,
					//D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 5, 100);

					Kenpolygon[i].pos.x -= Kenpolygon[i].move.x *Spede;
					Kenpolygon[i].pos.z -= Kenpolygon[i].move.y *Spede;

					Kenpolygon[i].consumption = Kenpolygon[i].RotMove.x - Kenpolygon[i].rot.y + pCamera->rot.y;
					Kenpolygon[i].nLif--;
				if (Kenpolygon[i].nLif == 0)
				{
					Kenpolygon[i].nLif = 100;
					Kenpolygon[i].bFri = false;
				}
			}
			else
			{
				if (i <= MAX_KEN / 2)
				{
					Kenpolygon[i].pos = Kenpolygon[i].pos = D3DXVECTOR3(pModel->pos.x + (10 * i), pModel->pos.y + 10 + 20 * i, pModel->pos.z);
				}
				else
				{
					Kenpolygon[i].pos = Kenpolygon[i].pos = D3DXVECTOR3(pModel->pos.x - (10 * (i / 2)), pModel->pos.y+10+20 * i/2, pModel->pos.z);
				}
				Kenpolygon[i].rot = D3DXVECTOR3(pModel->rot);	// ��]���W
			}
		}
	}

}

//=========================================
// �`�揈��
//=========================================
void DrawKen(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//D3DXMATRIX mtxScale, mtxTrans, mtxRot;	// �v�Z�p�}�g���b�N�X
	//D3DMATERIAL9 marDef;
	//D3DXMATERIAL *pMat;
	//MESH *pMesh = GetMesh();
	for (int j = 0; j < MAX_KEN; j++)//�o�Ă郂�f���̐�������
	{
		if (Kenpolygon[j].bUse)//�g���Ă��o��
		{
			//// ���[���h�}�g���b�N�X�̏�����
			//// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			//D3DXMatrixIdentity(&Kenpolygon[j].MtxWorld);

			////�T�C�Y�ύX
			//D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
			//
			//// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			//D3DXMatrixMultiply(&Kenpolygon[j].MtxWorld, &Kenpolygon[j].MtxWorld, &mtxScale);

			//// �����𔽉f
			//// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, Kenpolygon[j].rot.y, Kenpolygon[j].rot.x, Kenpolygon[j].rot.z);
			//// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			//D3DXMatrixMultiply(&Kenpolygon[j].MtxWorld, &Kenpolygon[j].MtxWorld, &mtxRot);

			//// �ʒu�𔽉f
			//// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			//D3DXMatrixTranslation(&mtxTrans, Kenpolygon[j].pos.x, Kenpolygon[j].pos.y, Kenpolygon[j].pos.z);
			//// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			//D3DXMatrixMultiply(&Kenpolygon[j].MtxWorld, &Kenpolygon[j].MtxWorld, &mtxTrans);

			//// ���[���h���W�s��̐ݒ�
			//pDevice->SetTransform(D3DTS_WORLD, &Kenpolygon[j].MtxWorld);

			////���݂̃}�e���A����ێ�
			//pDevice->GetMaterial(&marDef);

			////�}�e���A���f�[�^�̃|�C���^���擾
			//pMat = (D3DXMATERIAL*)Kenpolygon[j].s_pBuffKen->GetBufferPointer();

			//for (int i = 0; i < (int)Kenpolygon[j].s_Ken; i++)
			//{
			//	//�e�N�X�`���̐ݒ�
			//	pDevice->SetTexture(0, NULL);
			//	//�}�e���A���̐ݒ�
			//	pDevice->SetMaterial(&pMat[i].MatD3D);

			//	//���f���p�[�c�̕`��
			//	Kenpolygon[j].s_pVtxMesh->DrawSubset(i);
			//}

			////���݂̃}�e���A����ێ�
			//pDevice->SetMaterial(&marDef);
		}
	}


}
void SetKen(D3DXVECTOR3 pos)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();
	//�J�����̃f�[�^�擾
	MODEL *pModel;
	pModel = GetModel();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_KEN; i++)
	{
		Kenpolygon[i].nLif = 100;
		Kenpolygon[i].RotMove = D3DXVECTOR3(D3DX_PI + pModel->rot.y, D3DX_PI*0.5f + pModel->rot.y, 0.0f);
		// ����������

		Kenpolygon[i].pos.x = pos.x+i * 20.0f;	// ���_���W
		Kenpolygon[i].pos.y = pos.y+i*20.0f;	// ���_���W
		Kenpolygon[i].pos.z = pos.z;	// ���_���W
		Kenpolygon[i].move.x = sinf(pModel->rot.y);
		Kenpolygon[i].move.y = cosf(pModel->rot.y);
		Kenpolygon[i].rot = D3DXVECTOR3(pModel->rot);	// ��]���W
		Kenpolygon[i].bUse = true;
		Kenpolygon[i].nType = i;
	}

}
