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
#include"effect.h"
#include"line.h"

//�}�N��
#define Attenuation	(0.5f)		//�����W��
#define Spede	(1.0f)			//�X�s�[�h
#define WIDTH (10.0f)			//���f���̔��a
#define MAX_MODEL (16)			//�ő吔
//------------------------------------
// static�ϐ�
//------------------------------------
static bool s_bIsLanding;
static MODEL Modelpolygon[MAX_MODEL];	// �|���S���̍\����
static int s_nSet; //�ő吔

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
		Modelpolygon[i].ModelMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		Modelpolygon[i].ModelMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	}
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
			
			D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
			
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
	//��������X�t�@�C����ǂݍ��񂾌�

	//���ׂĂ̒��_����ۑ�����֐������
	int NumVpx;	//���_��
	//��̒��_�̃T�C�Y������֐�
	DWORD sizeFVF;
	//�o�C�g�����̃|�C���^�[char
	BYTE *pVtxBuff;

	//�����Œ��_�����Q��
	NumVpx = Modelpolygon[s_nSet].s_pVtxMesh->GetNumVertices();

	//�����ŃT�C�Y������
	sizeFVF = D3DXGetFVFVertexSize(Modelpolygon[s_nSet].s_pVtxMesh->GetFVF());

	//	���_�o�b�t�@�̃��b�N���܂��傤
	Modelpolygon[s_nSet].s_pVtxMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


	for (int i = 0; i < NumVpx; i++)
	{

		D3DXVECTOR3 pVtx = *(D3DXVECTOR3*)pVtxBuff;
		//������g���ă��f���̍ő�l�ƍŏ��l���g���ċ��߂�
		//XYZ�S�����߂�
		if (pVtx.x <= Modelpolygon[s_nSet].ModelMin.x)
		{
			Modelpolygon[s_nSet].ModelMin.x = pVtx.x;
		}
		if (pVtx.x >= Modelpolygon[s_nSet].ModelMax.x)
		{
			Modelpolygon[s_nSet].ModelMax.x = pVtx.x;
		}
		if (pVtx.y <= Modelpolygon[s_nSet].ModelMin.y)
		{
			Modelpolygon[s_nSet].ModelMin.y = pVtx.y;
		}
		if (pVtx.y >= Modelpolygon[s_nSet].ModelMax.y)
		{
			Modelpolygon[s_nSet].ModelMax.y = pVtx.y;
		}
		if (pVtx.z <= Modelpolygon[s_nSet].ModelMin.z)
		{
			Modelpolygon[s_nSet].ModelMin.z = pVtx.z;
		}
		if (pVtx.z >= Modelpolygon[s_nSet].ModelMax.z)
		{
			Modelpolygon[s_nSet].ModelMax.z = pVtx.z;
		}

		

		//������߂��玟�ɐ��������̂�
		pVtxBuff += sizeFVF;
		//��������΍ő�ŏ������߂���

	}
	//	���_�o�b�t�@�̃��b�N���܂��傤
	Modelpolygon[s_nSet].s_pVtxMesh->UnlockVertexBuffer();

	// ����������
	Modelpolygon[s_nSet].pos = pos;	// ���_���W
	Modelpolygon[s_nSet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
	Modelpolygon[s_nSet].nShadow = SetShadow(Modelpolygon[s_nSet].pos, Modelpolygon[s_nSet].rot,0);//�ꏊ.��]
	Modelpolygon[s_nSet].bUse = true;
	Modelpolygon[s_nSet].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);


#ifdef _DEBUG
	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMin.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y+1, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMax.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z), Modelpolygon[s_nSet].pos);
	
	
	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y , Modelpolygon[s_nSet].ModelMax.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y, Modelpolygon[s_nSet].ModelMax.z), Modelpolygon[s_nSet].pos);


	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y , Modelpolygon[s_nSet].ModelMin.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y , Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);
	

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);


	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMax.y, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);

	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMax.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);


	SetLine(D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMax.z),
		D3DXVECTOR3(Modelpolygon[s_nSet].ModelMin.x, Modelpolygon[s_nSet].ModelMin.y + 1, Modelpolygon[s_nSet].ModelMin.z), Modelpolygon[s_nSet].pos);
#endif // DEBUG

	s_nSet++;
}

MODEL *GetModel(void)
{
	return &Modelpolygon[0];
}
void  CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 Siz)
{
	{
		for (int nCnt = 0; nCnt < s_nSet; nCnt++)
		{
			if (Modelpolygon[nCnt].bUse)
			{
				//���E�̕�
				if (pPosOld->z + Siz.z > Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMax.z
					&& pPosOld->z - Siz.z < Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMin.z)
				{
					if (pPos->x + Siz.x / 2 > Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMin.x
						&& pPosOld->x + Siz.x / 2 <= Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMin.x)
					{//�u���b�N�̍��W�ƍ��W���d�Ȃ荇������//�ʏ탂�[�h//��
						pPos->x = Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMin.x - Siz.x / 2.0f;
					}
					if (pPos->x - Siz.x / 2 < Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMax.x
						&& pPosOld->x - Siz.x / 2 >= Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMax.x)
					{//�u���b�N�̍��W�ƍ��W���d�Ȃ荇������//�ʏ탂�[�h//�E
						pPos->x = Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMax.x + Siz.x / 2.0f+0.01f;
					}
				}
				//�㉺�̕�
				if (pPosOld->x + Siz.x / 2 > Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMin.x
					&& pPosOld->x - Siz.x / 2 < Modelpolygon[nCnt].pos.x + Modelpolygon[nCnt].ModelMax.x)
				{
					if (pPos->z + Siz.z / 2 > Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMin.z
						&& pPosOld->z + Siz.z / 2 <= Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMin.z)
					{//�u���b�N�̍��W�ƍ��W���d�Ȃ荇������//�ʏ탂�[�h//��
						pPos->z = Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMin.z - Siz.z / 2.0f;
					}
					if (pPos->z - Siz.z / 2 < Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMax.z
						&& pPosOld->z - Siz.z / 2 >= Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMax.z)
					{//�u���b�N�̍��W�ƍ��W���d�Ȃ荇������//�ʏ탂�[�h//��
						pPos->z = Modelpolygon[nCnt].pos.z + Modelpolygon[nCnt].ModelMax.z + Siz.z / 2.0f + 0.01f;
					}
					
				}

			}
		}
	}
}

