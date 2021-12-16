//======================================
//�v���C���[����
//Auther�Fhamada ryuuga
//======================================

#include<stdio.h>
#include "Prayer.h"
#include "input.h"
#include"camera.h"
#include"shadow.h"
#include"kitune.h"
#include"file.h"
#include"mesh.h"
#include"paticle.h"
#include"ken.h"
#include"effect.h"

//�}�N��
#define Attenuation	(0.5f)		//�����W��
#define Spede	(1.0f)			//�X�s�[�h
#define WIDTH (10.0f)			//���f���̔��a
#define MAX_PRAYER (16)			//�ő吔
//------------------------------------
// static�ϐ�
//------------------------------------
static PRAYER Prayerpolygon[MAX_PRAYER];	// �|���S���̍\����
static int s_nNanba, s_nSet, s_nTime;//���ݎg�p���Ă��ƍő吔
static D3DXVECTOR3 mystery;
//=========================================
// ����������
//=========================================
void InitPrayer(void)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int i = 0; i < MAX_PRAYER; i++)
	{
		// ����������
		Prayerpolygon[i].s_pBuffPrayer = NULL;
		Prayerpolygon[i].s_Prayer = 0;
		Prayerpolygon[i].s_pVtxMesh = NULL;			//�c�@�@�@�@�@�@�@�@�@�@//��
		Prayerpolygon[i].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
		Prayerpolygon[i].consumption = 0.0f;
		Prayerpolygon[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		Prayerpolygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
		Prayerpolygon[i].nShadow = 0;
		Prayerpolygon[i].bUse = false;
		Prayerpolygon[i].bMystery = false;
		Prayerpolygon[i].ModelMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		Prayerpolygon[i].ModelMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	}
	s_nNanba = 0;
	s_nSet = 0;
	s_nTime = 0;
}

//=========================================
// �I������
//=========================================
void UninitPrayer(void)
{
	for (int i = 0; i < MAX_PRAYER; i++)
	{
		// ���_�o�b�t�@�[�̉��
		if (Prayerpolygon[i].s_pVtxMesh != NULL)
		{
			Prayerpolygon[i].s_pVtxMesh->Release();
			Prayerpolygon[i].s_pVtxMesh = NULL;
		}
		if (Prayerpolygon[i].s_pBuffPrayer != NULL)
		{
			Prayerpolygon[i].s_pBuffPrayer->Release();
			Prayerpolygon[i].s_pBuffPrayer = NULL;
		}
	}

}

//=========================================
// �X�V����
//=========================================
void UpdatePrayer(void)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();
	float consumption = 0;

	if (GetKeyboardPress(DIK_1))
	{//1�������Ƃ��p�[�e�B�N��
		SetParticle(Prayerpolygon[s_nNanba].pos - D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_KITUNE, LIGHTNINGLIFE);
	}
	if (GetKeyboardPress(DIK_2))
	{//�Q�������Ƃ��p�[�e�B�N��
		SetParticle(Prayerpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_LIGHTNING, KITUNELIFE);
	}
	if (GetKeyboardPress(DIK_3))
	{//�R�������Ƃ��p�[�e�B�N��
		SetParticle(Prayerpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_OUKAN, OUKANLIFE);
	}
	if (GetKeyboardPress(DIK_4))
	{//�S�������Ƃ��p�[�e�B�N��

		SetParticle(Prayerpolygon[s_nNanba].pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_MERA, MERALIFE);
	}
	if (GetKeyboardPress(DIK_7))
	{//���@�w����//0.0�̃J���[�̂�͘g��
	}
	if (GetKeyboardTrigger(DIK_8))
	{//���v����//0.0�̃J���[�̂�͘g��
	 //SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife, EFFECTTYPE nType,bool bZbf, bool bAbf, bool bCol,bool bRot);
		mystery = Prayerpolygon[s_nNanba].pos;
		//�e�N�X�`���̍��W�ݒ�
		SetEffectFile(LOOD_FILE_NAME_EFFECT);

		SetEffect(LISTS_ZERO);
		SetEffect(LISTS_I);
		SetEffect(LISTS_II);
		SetEffect(LISTS_III);
		SetEffect(LISTS_IV);
		SetEffect(LISTS_V);
		SetEffect(LISTS_VI);
		SetEffect(LISTS_VII);
		SetEffect(LISTS_VIII);
		SetEffect(LISTS_IX);
		SetEffect(LISTS_X);
		SetEffect(LISTS_XI);
		SetEffect(LISTS_XII);
		SetEffect(LISTS_XIII);
		SetEffect(LISTS_XIV);
	}
	if (GetKeyboardTrigger(DIK_0))
	{//���@�w����//0.0�̃J���[�̂�͘g��
		Prayerpolygon[s_nNanba].bMystery = true;
		mystery = Prayerpolygon[s_nNanba].pos;

	}
	if (Prayerpolygon[s_nNanba].bMystery)
	{
		SetEffectFile(LOOD_FILE_NAME_MAGIC);
		s_nTime++;
		SetParticle(D3DXVECTOR3(mystery),
			D3DXVECTOR3(0.0, 0.0, 0.0),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3.5f, 6.5f, EFFECTTYPE_AWA, 150);

		SetParticle(D3DXVECTOR3(mystery),
			D3DXVECTOR3(-sinf(mystery.y), 3.5f, -cosf(mystery.y)),
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 3.5f, 6.5f, EFFECTTYPE_GLITTER, 150);

		if (s_nTime == 10)
		{
			SetEffect(LISTS_ZERO);

			SetEffect(LISTS_I);

			SetEffect(LISTS_II);

			//�������牺�����F
			SetEffect(LISTS_III);

			SetEffect(LISTS_IV);

			SetEffect(LISTS_V);

			SetEffect(LISTS_VI);

			SetEffect(LISTS_VII);
		}
		if (s_nTime == 100)
		{
			SetEffect(LISTS_VIII);
			//�������牺�����F
			SetEffect(LISTS_IX);

			SetEffect(LISTS_X);
		}
		if (s_nTime == 200)
		{
			SetEffect(LISTS_XI);

			SetEffect(LISTS_XII);

			//�������牺�����F
			SetEffect(LISTS_XIII);

			SetEffect(LISTS_XIV);
		}
		if (s_nTime == 300)
		{
			SetEffect(LISTS_XV);

			SetEffect(LISTS_XVI);

			//�������牺�����F
			SetEffect(LISTS_XVII);

			SetEffect(LISTS_XVIII);
		}
		if (s_nTime == 400)
		{

			SetEffect(LISTS_XVIX);

			SetEffect(LISTS_XX);

			//�������牺�����F
			SetEffect(LISTS_XXI);

			SetEffect(LISTS_XXII);
		}
		if (s_nTime == EFFECT_LIFE)
		{
			s_nTime = 0;
			Prayerpolygon[s_nNanba].bMystery = false;

		}
	}

	//���f���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_V))
	{
		s_nNanba++;
		s_nNanba %= s_nSet;
	}
	Prayerpolygon[s_nNanba].consumption = 0.0f;
	if (GetKeyboardPress(DIK_I))
	{//I�������Ƃ������
		Prayerpolygon[s_nNanba].pos.x += sinf(pCamera->rot.y)*Spede;
		Prayerpolygon[s_nNanba].pos.z += cosf(pCamera->rot.y)*Spede;

		Prayerpolygon[s_nNanba].consumption = Prayerpolygon[s_nNanba].RotMove.x - Prayerpolygon[s_nNanba].rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_K))
	{//K�������Ɖ�����
		Prayerpolygon[s_nNanba].pos.x += sinf(pCamera->rot.y - D3DX_PI)*Spede;
		Prayerpolygon[s_nNanba].pos.z += cosf(pCamera->rot.y - D3DX_PI)*Spede;

		Prayerpolygon[s_nNanba].consumption = Prayerpolygon[s_nNanba].RotMove.x - D3DX_PI - Prayerpolygon[s_nNanba].rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_L))
	{//L�������Ƃ��E����
		Prayerpolygon[s_nNanba].pos.x += sinf(D3DX_PI *0.5f + pCamera->rot.y)*Spede;
		Prayerpolygon[s_nNanba].pos.z += cosf(D3DX_PI *0.5f + pCamera->rot.y)*Spede;

		Prayerpolygon[s_nNanba].consumption = Prayerpolygon[s_nNanba].RotMove.y - D3DX_PI - Prayerpolygon[s_nNanba].rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_J))
	{//j�������ƍ�����
		Prayerpolygon[s_nNanba].pos.x += sinf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;
		Prayerpolygon[s_nNanba].pos.z += cosf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;

		Prayerpolygon[s_nNanba].consumption = Prayerpolygon[s_nNanba].RotMove.y - Prayerpolygon[s_nNanba].rot.y + pCamera->rot.y;
	}
	if (GetKeyboardTrigger(DIK_RETURN))
	{//�G���^�[���Z�b�g
	 // ����������
		Prayerpolygon[s_nNanba].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		Prayerpolygon[s_nNanba].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W	
	}
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//SetKen(Prayerpolygon[s_nNanba].pos);
		SetKitune(D3DXVECTOR3(Prayerpolygon[s_nNanba].pos.x, Prayerpolygon[s_nNanba].pos.y, Prayerpolygon[s_nNanba].pos.z),
			Prayerpolygon[s_nNanba].rot,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1);//�ꏊ.��].�F.�^�C�v
	}

	//���K��
	if (Prayerpolygon[s_nNanba].consumption > D3DX_PI)
	{
		Prayerpolygon[s_nNanba].consumption -= D3DX_PI * 2;
	}
	if (Prayerpolygon[s_nNanba].consumption < -D3DX_PI)
	{
		Prayerpolygon[s_nNanba].consumption += D3DX_PI * 2;
	}

	//���Z�ݒ�i�����j
	Prayerpolygon[s_nNanba].rot.y += (Prayerpolygon[s_nNanba].consumption)* Attenuation;//�ړI�̒l-���݂̒l�j�������W��

																					  //���K��
	if (Prayerpolygon[s_nNanba].rot.y > D3DX_PI)
	{
		Prayerpolygon[s_nNanba].rot.y -= D3DX_PI * 2;
	}
	if (Prayerpolygon[s_nNanba].rot.y <= -D3DX_PI)
	{
		Prayerpolygon[s_nNanba].rot.y += D3DX_PI * 2;
	}

	//�e�X�V
	SetposShadow(Prayerpolygon[s_nNanba].nShadow, Prayerpolygon[s_nNanba].pos);
	MESH *pMesh = GetMesh();
	//��
	if (Prayerpolygon[s_nNanba].pos.x <pMesh->xsiz *-MAX_SIZMESH / 2)
	{
		Prayerpolygon[s_nNanba].pos.x = pMesh->xsiz * -MAX_SIZMESH / 2;
	}
	if (Prayerpolygon[s_nNanba].pos.x >pMesh->xsiz * MAX_SIZMESH / 2)
	{
		Prayerpolygon[s_nNanba].pos.x = pMesh->xsiz * MAX_SIZMESH / 2;
	}
	if (Prayerpolygon[s_nNanba].pos.z < pMesh->zsiz *-MAX_SIZMESH / 2)
	{
		Prayerpolygon[s_nNanba].pos.z = pMesh->zsiz * -MAX_SIZMESH / 2;
	}
	if (Prayerpolygon[s_nNanba].pos.z >pMesh->zsiz * MAX_SIZMESH / 2)
	{
		Prayerpolygon[s_nNanba].pos.z = pMesh->zsiz *MAX_SIZMESH / 2;
	}
}

//=========================================
// �`�揈��
//=========================================
void DrawPrayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxTrans, mtxRot;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 marDef;
	D3DXMATERIAL *pMat;
	MESH *pMesh = GetMesh();
	for (int j = 0; j < s_nSet; j++)//�o�Ă郂�f���̐�������
	{
		if (Prayerpolygon[j].bUse)//�g���Ă��o��
		{
			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			D3DXMatrixIdentity(&Prayerpolygon[j].MtxWorld);

			if (pMesh->xsiz / 10 == 0)
			{
				//�T�C�Y�ύX
				D3DXMatrixScaling(&mtxScale, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//�T�C�Y�ύX
				D3DXMatrixScaling(&mtxScale, pMesh->xsiz / 50.0f, pMesh->xsiz / 50.0f, pMesh->xsiz / 50.0f);
			}

			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&Prayerpolygon[j].MtxWorld, &Prayerpolygon[j].MtxWorld, &mtxScale);

			// �����𔽉f
			// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, Prayerpolygon[j].rot.y, Prayerpolygon[j].rot.x, Prayerpolygon[j].rot.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&Prayerpolygon[j].MtxWorld, &Prayerpolygon[j].MtxWorld, &mtxRot);

			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, Prayerpolygon[j].pos.x, Prayerpolygon[j].pos.y, Prayerpolygon[j].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&Prayerpolygon[j].MtxWorld, &Prayerpolygon[j].MtxWorld, &mtxTrans);

			// ���[���h���W�s��̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Prayerpolygon[j].MtxWorld);

			//���݂̃}�e���A����ێ�
			pDevice->GetMaterial(&marDef);

			//�}�e���A���f�[�^�̃|�C���^���擾
			pMat = (D3DXMATERIAL*)Prayerpolygon[j].s_pBuffPrayer->GetBufferPointer();

			for (int i = 0; i < (int)Prayerpolygon[j].s_Prayer; i++)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[i].MatD3D);

				//���f���p�[�c�̕`��
				Prayerpolygon[j].s_pVtxMesh->DrawSubset(i);
			}

			//���݂̃}�e���A����ێ�
			pDevice->SetMaterial(&marDef);
		}
	}


}
void SetPrayer(D3DXVECTOR3 pos, char *Filename)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera;
	pCamera = GetCamera();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	char aFile[128] = FILE_3D_PRAYER;

	strcat(aFile, &Filename[0]);//�����@aFile��-�����ɓ����

	D3DXLoadMeshFromX(&aFile[0],
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&Prayerpolygon[s_nSet].s_pBuffPrayer,
		NULL,
		&Prayerpolygon[s_nSet].s_Prayer,
		&Prayerpolygon[s_nSet].s_pVtxMesh
	);
	//���ׂĂ̒��_����ۑ�����֐������
	int NumVpx;	//���_��
				//��̒��_�̃T�C�Y������֐�
	DWORD sizeFVF;
	//�o�C�g�����̃|�C���^�[char
	BYTE *pVtxBuff;

	//�����Œ��_�����Q��
	NumVpx = Prayerpolygon[s_nSet].s_pVtxMesh->GetNumVertices();

	//�����ŃT�C�Y������
	sizeFVF = D3DXGetFVFVertexSize(Prayerpolygon[s_nSet].s_pVtxMesh->GetFVF());

	//	���_�o�b�t�@�̃��b�N���܂��傤
	Prayerpolygon[s_nSet].s_pVtxMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


	for (int i = 0; i < NumVpx; i++)
	{

		D3DXVECTOR3 pVtx = *(D3DXVECTOR3*)pVtxBuff;
		//������g���ă��f���̍ő�l�ƍŏ��l���g���ċ��߂�
		//XYZ�S�����߂�
		if (pVtx.x <= Prayerpolygon[s_nSet].ModelMin.x)
		{
			Prayerpolygon[s_nSet].ModelMin.x = pVtx.x;
		}
		if (pVtx.x >= Prayerpolygon[s_nSet].ModelMax.x)
		{
			Prayerpolygon[s_nSet].ModelMax.x = pVtx.x;
		}
		if (pVtx.y <= Prayerpolygon[s_nSet].ModelMin.y)
		{
			Prayerpolygon[s_nSet].ModelMin.y = pVtx.y;
		}
		if (pVtx.y >= Prayerpolygon[s_nSet].ModelMax.y)
		{
			Prayerpolygon[s_nSet].ModelMax.y = pVtx.y;
		}
		if (pVtx.z <= Prayerpolygon[s_nSet].ModelMin.z)
		{
			Prayerpolygon[s_nSet].ModelMin.z = pVtx.z;
		}
		if (pVtx.z >= Prayerpolygon[s_nSet].ModelMax.z)
		{
			Prayerpolygon[s_nSet].ModelMax.z = pVtx.z;
		}

		//������߂��玟�ɐ��������̂�
		pVtxBuff += sizeFVF;
		//��������΍ő�ŏ������߂���

	}
	//	���_�o�b�t�@�̃��b�N���܂��傤
	Prayerpolygon[s_nSet].s_pVtxMesh->UnlockVertexBuffer();



	Prayerpolygon[s_nSet].RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
	// ����������
	Prayerpolygon[s_nSet].pos = pos;	// ���_���W
	Prayerpolygon[s_nSet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
	Prayerpolygon[s_nSet].nShadow = SetShadow(Prayerpolygon[s_nSet].pos, Prayerpolygon[s_nNanba].rot, 0);//�ꏊ.��]
	Prayerpolygon[s_nSet].bUse = true;
	s_nSet++;
}
//----------------------
//�Q�b�g(�\����)
//-----------------------
PRAYER *GetPrayer(void)
{
	return &Prayerpolygon[s_nNanba];
}

//----------------------
//�Q�b�g(�g���Ă��ԍ�)
//-----------------------
int GetnNanba(void)
{
	return s_nNanba;
}