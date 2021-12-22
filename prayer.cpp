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
#include"model.h"
//�}�N��
#define Attenuation	(0.5f)		//�����W��
#define Spede	(1.0f)			//�X�s�[�h
#define WIDTH (10.0f)			//���f���̔��a
#define MAX_PRAYER (16)			//�ő吔
//------------------------------------
// static�ϐ�
//------------------------------------
static PRAYER s_Prayer;	// �|���S���̍\����
static int s_nNanba, s_nSet, s_nTime,s_nParts;//���ݎg�p���Ă��ƍő吔
static float nTime = 0;
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
												//�c�@�@�@�@�@�@�@�@�@�@//��
		s_Prayer.RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
		s_Prayer.consumption = 0.0f;
		s_Prayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		s_Prayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
		s_Prayer.nShadow = 0;
		s_Prayer.bUse = false;
		s_Prayer.bMystery = false;
		s_Prayer.ModelMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
		s_Prayer.ModelMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (int nSet = 0; nSet < MAX_MODELPARTS; nSet++)
		{
			s_Prayer.Parts[nSet].nIdxModelParent = 0;
		}
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
	for (int i = 0; i < s_nParts; i++)
	{
		// ���_�o�b�t�@�[�̉��
		if (s_Prayer.Parts[i].pBuffMat != NULL)
		{
			s_Prayer.Parts[i].pBuffMat->Release();
			s_Prayer.Parts[i].pBuffMat = NULL;
		}
		if (s_Prayer.Parts[i].pMesh != NULL)
		{
			s_Prayer.Parts[i].pMesh->Release();
			s_Prayer.Parts[i].pMesh = NULL;
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
		SetParticle(s_Prayer.pos - D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_KITUNE, LIGHTNINGLIFE);
	}
	if (GetKeyboardPress(DIK_2))
	{//�Q�������Ƃ��p�[�e�B�N��
		SetParticle(s_Prayer.pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_LIGHTNING, KITUNELIFE);
	}
	if (GetKeyboardPress(DIK_3))
	{//�R�������Ƃ��p�[�e�B�N��
		SetParticle(s_Prayer.pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_OUKAN, OUKANLIFE);
	}
	if (GetKeyboardPress(DIK_4))
	{//�S�������Ƃ��p�[�e�B�N��

		SetParticle(s_Prayer.pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 20.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
			, 10.0f, 10.0f, PARTICLETYPE_MERA, MERALIFE);
	}
	if (GetKeyboardPress(DIK_7))
	{//���@�w����//0.0�̃J���[�̂�͘g��
	}
	if (GetKeyboardTrigger(DIK_8))
	{//���v����//0.0�̃J���[�̂�͘g��

		mystery = s_Prayer.pos;
		//�e�N�X�`���̍��W�ݒ�
		SetEffectFile(LOOD_FILE_NAME_EFFECT);
		int a = GetEffectFile();

		for (int i = 0; i < a; i++)
		{
			SetEffect(i, mystery);
		}

	}
	if (GetKeyboardTrigger(DIK_0))
	{//���@�w����//0.0�̃J���[�̂�͘g��
		s_Prayer.bMystery = true;
		mystery = s_Prayer.pos;
	}
	if (s_Prayer.bMystery)
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
			SetEffect(LISTS_ZERO, mystery);

			SetEffect(LISTS_I, mystery);

			SetEffect(LISTS_II, mystery);

			//�������牺�����F
			SetEffect(LISTS_III, mystery);

			SetEffect(LISTS_IV, mystery);

			SetEffect(LISTS_V, mystery);

			SetEffect(LISTS_VI, mystery);

			SetEffect(LISTS_VII, mystery);
		}
		if (s_nTime == 100)
		{
			SetEffect(LISTS_VIII, mystery);
			//�������牺�����F
			SetEffect(LISTS_IX, mystery);

			SetEffect(LISTS_X, mystery);
		}
		if (s_nTime == 200)
		{
			SetEffect(LISTS_XI, mystery);

			SetEffect(LISTS_XII, mystery);

			//�������牺�����F
			SetEffect(LISTS_XIII, mystery);

			SetEffect(LISTS_XIV, mystery);
		}
		if (s_nTime == 300)
		{
			SetEffect(LISTS_XV, mystery);

			SetEffect(LISTS_XVI, mystery);

			//�������牺�����F
			SetEffect(LISTS_XVII, mystery);

			SetEffect(LISTS_XVIII, mystery);
		}
		if (s_nTime == 400)
		{

			SetEffect(LISTS_XVIX, mystery);

			SetEffect(LISTS_XX, mystery);

			//�������牺�����F
			SetEffect(LISTS_XXI,mystery);

			SetEffect(LISTS_XXII, mystery);
		}
		if (s_nTime == EFFECT_LIFE)
		{
			s_nTime = 0;
			s_Prayer.bMystery = false;

		}
	}

	//���f���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_V))
	{
		s_nNanba++;
		s_nNanba %= s_nSet;
	}

	s_Prayer.posOld = s_Prayer.pos;//�ߋ��̈ړ��ʂ�ۑ�

	s_Prayer.consumption = 0.0f;
	if (GetKeyboardPress(DIK_I))
	{//I�������Ƃ������
		s_Prayer.pos.x += sinf(pCamera->rot.y)*Spede;
		s_Prayer.pos.z += cosf(pCamera->rot.y)*Spede;

		s_Prayer.consumption = s_Prayer.RotMove.x - s_Prayer.rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_K))
	{//K�������Ɖ�����
		s_Prayer.pos.x += sinf(pCamera->rot.y - D3DX_PI)*Spede;
		s_Prayer.pos.z += cosf(pCamera->rot.y - D3DX_PI)*Spede;

		s_Prayer.consumption = (s_Prayer.RotMove.x - 
												D3DX_PI - s_Prayer.rot.y 
												+ pCamera->rot.y);
	}
	if (GetKeyboardPress(DIK_L))
	{//L�������Ƃ��E����
		s_Prayer.pos.x += sinf(D3DX_PI *0.5f + pCamera->rot.y)*Spede;
		s_Prayer.pos.z += cosf(D3DX_PI *0.5f + pCamera->rot.y)*Spede;

		s_Prayer.consumption = s_Prayer.RotMove.y - D3DX_PI - s_Prayer.rot.y + pCamera->rot.y;
	}
	if (GetKeyboardPress(DIK_J))
	{//nSet�������ƍ�����
		s_Prayer.pos.x += sinf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;
		s_Prayer.pos.z += cosf(D3DX_PI *-0.5f + pCamera->rot.y)*Spede;

		s_Prayer.consumption = s_Prayer.RotMove.y - s_Prayer.rot.y + pCamera->rot.y;
	}
	if (GetKeyboardTrigger(DIK_RETURN))
	{//�G���^�[���Z�b�g
	 // ����������
		s_Prayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		s_Prayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W	
	}
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//SetKen(Prayerpolygon[s_nNanba].pos);
		SetKitune(D3DXVECTOR3(s_Prayer.pos.x, s_Prayer.pos.y, s_Prayer.pos.z),
			s_Prayer.rot,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			1);//�ꏊ.��].�F.�^�C�v
	}
	CollisionModel(&s_Prayer.pos, &s_Prayer.posOld, s_Prayer.ModelMax - s_Prayer.ModelMin);
	//���K��
	if (s_Prayer.consumption > D3DX_PI)
	{
		s_Prayer.consumption += D3DX_PI * 2;
	}
	if (s_Prayer.consumption < -D3DX_PI)
	{
		s_Prayer.consumption += -D3DX_PI * 2;
	}

	//���Z�ݒ�i�����j
	s_Prayer.rot.y += (s_Prayer.consumption)* Attenuation;//�ړI�̒l-���݂̒l�j�������W��

																					  //���K��
	if (s_Prayer.rot.y > D3DX_PI)
	{
		s_Prayer.rot.y += -D3DX_PI * 2;
	}
	if (s_Prayer.rot.y <= -D3DX_PI)
	{
		s_Prayer.rot.y += D3DX_PI * 2;
	}
	
	//�e�X�V
	SetposShadow(s_Prayer.nShadow, s_Prayer.pos);
	MESH *pMesh = GetMesh();
	//��
	if (s_Prayer.pos.x <pMesh->xsiz *-MAX_SIZMESH / 2)
	{
		s_Prayer.pos.x = pMesh->xsiz * -MAX_SIZMESH / 2;
	}
	if (s_Prayer.pos.x >pMesh->xsiz * MAX_SIZMESH / 2)
	{
		s_Prayer.pos.x = pMesh->xsiz * MAX_SIZMESH / 2;
	}
	if (s_Prayer.pos.z < pMesh->zsiz *-MAX_SIZMESH / 2)
	{
		s_Prayer.pos.z = pMesh->zsiz * -MAX_SIZMESH / 2;
	}
	if (s_Prayer.pos.z >pMesh->zsiz * MAX_SIZMESH / 2)
	{
		s_Prayer.pos.z = pMesh->zsiz *MAX_SIZMESH / 2;
	}
	
	


		s_Prayer.Parts[6].rot.z += D3DX_PI / 50.0f * sinf(nTime / 6.0f);
		nTime++;

	
	
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

	if (s_Prayer.bUse)//�g���Ă��o��
	{
		// ���[���h�}�g���b�N�X�̏�����
		// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
		D3DXMatrixIdentity(&s_Prayer.MtxWorld);

		D3DXMatrixScaling(&mtxScale, 0.8, 0.8, 0.8);

		// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		D3DXMatrixMultiply(&s_Prayer.MtxWorld, &s_Prayer.MtxWorld, &mtxScale);

		// �����𔽉f
		// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
		D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Prayer.rot.y, s_Prayer.rot.x, s_Prayer.rot.z);
		// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		D3DXMatrixMultiply(&s_Prayer.MtxWorld, &s_Prayer.MtxWorld, &mtxRot);

		// �ʒu�𔽉f
		// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
		D3DXMatrixTranslation(&mtxTrans, s_Prayer.pos.x, s_Prayer.pos.y, s_Prayer.pos.z);
		// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
		D3DXMatrixMultiply(&s_Prayer.MtxWorld, &s_Prayer.MtxWorld, &mtxTrans);

		for (int i = 0; i < s_nParts; i++)
		{
			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			D3DXMatrixIdentity(&s_Prayer.Parts[i].MtxWorld);

			

			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Prayer.Parts[i].MtxWorld, &s_Prayer.Parts[i].MtxWorld, &mtxScale);

			// �����𔽉f
			// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Prayer.Parts[i].rot.y, s_Prayer.Parts[i].rot.x, s_Prayer.Parts[i].rot.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Prayer.Parts[i].MtxWorld, &s_Prayer.Parts[i].MtxWorld, &mtxRot);

			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, s_Prayer.Parts[i].pos.x, s_Prayer.Parts[i].pos.y, s_Prayer.Parts[i].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Prayer.Parts[i].MtxWorld, &s_Prayer.Parts[i].MtxWorld, &mtxTrans);

			D3DXMATRIX mtxParent;

			//���݂̃}�e���A�����l��
			pDevice->GetMaterial(&marDef);

			if (s_Prayer.Parts[i].nIdxModelParent == -1)
			{
				mtxParent = s_Prayer.MtxWorld;
			}
			else
			{
				mtxParent = s_Prayer.Parts[s_Prayer.Parts[i].nIdxModelParent].MtxWorld;
			}
			D3DXMatrixMultiply(&s_Prayer.Parts[i].MtxWorld, &s_Prayer.Parts[i].MtxWorld, &mtxParent);

			// ���[���h���W�s��̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &s_Prayer.Parts[i].MtxWorld);
			//�}�e���A���f�[�^�̃|�C���^���擾
			pMat = (D3DXMATERIAL*)s_Prayer.Parts[i].pBuffMat->GetBufferPointer();
			for (int j = 0; j < (int)s_Prayer.Parts[i].nNumMat; j++)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[j].MatD3D);
				//���f���p�[�c�̕`��
				s_Prayer.Parts[i].pMesh->DrawSubset(j);
			}


		}
		//���݂̃}�e���A�������ɖ߂�
		pDevice->SetMaterial(&marDef);
	}
}
void SetPrayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *Filename,int nIdxModelParent)
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
		&s_Prayer.Parts[s_nParts].pBuffMat,
		NULL,
		&s_Prayer.Parts[s_nParts].nNumMat,
		&s_Prayer.Parts[s_nParts].pMesh
	);
	SizSet();
	s_Prayer.Parts[s_nParts].nIdxModelParent = nIdxModelParent;
	s_Prayer.RotMove = D3DXVECTOR3(D3DX_PI + pCamera->rot.y, D3DX_PI*0.5f + pCamera->rot.y, 0.0f);
	// ����������
	s_Prayer.Parts[s_nParts].pos = pos;	// ���_���W
	s_Prayer.Parts[s_nParts].rot = rot;	// ��]���W
	s_Prayer.bUse = true;
	if (s_Prayer.Parts[s_nParts].nIdxModelParent==-1)
	{
		s_Prayer.nShadow = SetShadow(s_Prayer.pos, s_Prayer.rot, 0);//�ꏊ.��]
	}
	s_nParts++;
}
//----------------------
//�Q�b�g(�\����)
//-----------------------
PRAYER *GetPrayer(void)
{
	return &s_Prayer;
}

//----------------------
//�Q�b�g(�g���Ă��ԍ�)
//-----------------------
int GetnNanba(void)
{
	return s_nNanba;
}
void SizSet(void)
{
	//���ׂĂ̒��_����ۑ�����֐������
	int NumVpx;	//���_��
	//��̒��_�̃T�C�Y������֐�
	DWORD sizeFVF;
	//�o�C�g�����̃|�C���^�[char
	BYTE *pVtxBuff;

	//�����Œ��_�����Q��
	NumVpx = s_Prayer.Parts[s_nParts].pMesh->GetNumVertices();

	//�����ŃT�C�Y������
	sizeFVF = D3DXGetFVFVertexSize(s_Prayer.Parts[s_nParts].pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N���܂��傤
	s_Prayer.Parts[s_nParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int i = 0; i < NumVpx; i++)
	{
		D3DXVECTOR3 pVtx = *(D3DXVECTOR3*)pVtxBuff;
		//������g���ă��f���̍ő�l�ƍŏ��l���g���ċ��߂�
		//XYZ�S�����߂�
		if (pVtx.x < s_Prayer.ModelMin.x)
		{
			s_Prayer.ModelMin.x = pVtx.x;
		}
		if (pVtx.x > s_Prayer.ModelMax.x)
		{
			s_Prayer.ModelMax.x = pVtx.x;
		}
		if (pVtx.y < s_Prayer.ModelMin.y)
		{
			s_Prayer.ModelMin.y = pVtx.y;
		}
		if (pVtx.y > s_Prayer.ModelMax.y)
		{
			s_Prayer.ModelMax.y = pVtx.y;
		}
		if (pVtx.z < s_Prayer.ModelMin.z)
		{
			s_Prayer.ModelMin.z = pVtx.z;
		}
		if (pVtx.z > s_Prayer.ModelMax.z)
		{
			s_Prayer.ModelMax.z = pVtx.z;
		}


		//������߂��玟�ɐ��������̂�
		pVtxBuff += sizeFVF;
		//��������΍ő�ŏ������߂���
	}

	//���_�o�b�t�@�̃��b�N���܂��傤
	s_Prayer.Parts[s_nParts].pMesh->UnlockVertexBuffer();
}

