//======================
//�~�����~���b�V���ݒ�
//Auther�Fhamada ryuuga
//======================
#include "cylinder.h"
#include "input.h"

//------------------------------------
// static�ϐ�
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// ���_�o�b�t�@�[�ւ̃|�C���^�㔼��
static LPDIRECT3DTEXTURE9 s_pTextureCylinder = {}; //�e�N�X�`���̃|�C���^
static LPDIRECT3DINDEXBUFFER9 s_pIdxBuff = {};  //�C���f�b�N�X�o�b�t�@



static CYLINDER s_Cylinder;	// �|���S���̍\����
static int n,o;

#define MAX_SIZCYLINDER (10.0f)
#define MAX_CYLINDER (20)

//=========================================
// ����������
//=========================================
void InitCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ����������
	s_Cylinder.pos = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	s_Cylinder.rot = D3DXVECTOR3(0.0f, 0.0f,0.0f );	// ��]���W

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/11112.png",
		&s_pTextureCylinder);

	//������
	s_Cylinder.xsiz = MAX_CYLINDER;
	s_Cylinder.zsiz = MAX_CYLINDER;
	s_Cylinder.ysiz = MAX_CYLINDER;

	//�ӂ̒��_��
	s_Cylinder.X = s_Cylinder.xsiz + 1;//1��������
	s_Cylinder.Z = s_Cylinder.zsiz + 1;//1��������
	s_Cylinder.Y = s_Cylinder.ysiz + 1;

							   //���_��
	s_Cylinder.Vtx = s_Cylinder.X* s_Cylinder.Z;//���_�����g���Ă��

									//�C���f�b�N�X��
	s_Cylinder.Index = (2 * s_Cylinder.X * s_Cylinder.zsiz + 2 * (s_Cylinder.zsiz - 1));

	s_Cylinder.por = s_Cylinder.Index - 2;
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * s_Cylinder.Vtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(sizeof(WORD) * s_Cylinder.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&s_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float rotDiffZ = (D3DX_PI *  2 / s_Cylinder.zsiz);

		for (int Z = 0; Z <= s_Cylinder.zsiz; Z++)
		{
			float rotDiffX = (D3DX_PI / s_Cylinder.xsiz);
			float rotZ = rotDiffZ * Z - D3DX_PI * 0.5f;

			for (int X = 0; X <= s_Cylinder.xsiz; X++)
			{
				float rotX = rotDiffX * X;

				//���i�j
				pVtx[X + Z * s_Cylinder.X].pos = D3DXVECTOR3((sinf(rotX) * sinf(rotZ) * MAX_SIZCYLINDER),
															cosf(rotX)*MAX_SIZCYLINDER,
															sinf(rotX) *cosf(rotZ)*MAX_SIZCYLINDER);
				pVtx[X + Z * s_Cylinder.X].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[X + Z * s_Cylinder.X].tex = D3DXVECTOR2((float)X, (float)Z);

			
				//�@��
				float fNor = atan2f(pVtx[X + Z * s_Cylinder.X].pos.x, pVtx[X + Z * s_Cylinder.X].pos.z);
				pVtx[X + Z * s_Cylinder.X].nor = D3DXVECTOR3(sinf(fNor), 0.0f, cosf(fNor));
				D3DXVec3Normalize(&pVtx[X + Z * s_Cylinder.X].nor, &pVtx[X + Z * s_Cylinder.X].nor);	
				//�x�̊p�x�̐ݒ�
				//float fRot = (D3DX_PI*2.0f) / s_Cylinder.xsiz * X;
				//�~��
				//pVtx[X + Z * s_Cylinder.X].pos = D3DXVECTOR3((sinf(fRot)*5),Z*MAX_SIZCYLINDER, (cosf(fRot) * 5));
			}	
			
			
		}
	
	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < s_Cylinder.zsiz; z++)
	{
		int linetop = z * (s_Cylinder.X * 2 + 2);
		for (int x = 0; x < s_Cylinder.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = x + (z * s_Cylinder.X);
			pIdx[nIdxData] = pIdx[nIdxData + 1] + s_Cylinder.X;
			//����͉����l��������
			//pIdx[(x*2+1+((z*Cylinder.Z +1))*z)] = x+(z*Cylinder.X);
			//pIdx[(x*2 + ((z*Cylinder.Z)+3)*z)] = (x+ (Cylinder.Z)) + (z*Cylinder.X);	
		}
		//�k�ރ|���S���ݒ�
		if (z < s_Cylinder.xsiz - 1)
		{
			pIdx[s_Cylinder.X * 2 + 0 + linetop] = s_Cylinder.xsiz + s_Cylinder.X*z;
			pIdx[s_Cylinder.X * 2 + 1 + linetop] = s_Cylinder.X * 2 + s_Cylinder.X * z;
		}

	}

	// ���_���W���A�����b�N
	s_pIdxBuff->Unlock();



}

//=========================================
// �I������
//=========================================
void UninitCylinder(void)
{
	// ���_�o�b�t�@�[�̉��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pTextureCylinder != NULL)
	{
		s_pTextureCylinder->Release();
		s_pTextureCylinder = NULL;
	}
	if (s_pIdxBuff != NULL)
	{
		s_pIdxBuff->Release();
		s_pIdxBuff = NULL;
	}

	
	
	
}

//=========================================
// �X�V����
//=========================================
void UpdateCylinder(void)
{	// ���_���W�����b�N

	//���f���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_N) && s_Cylinder.xsiz < MAX_CYLINDER)
	{

		s_Cylinder.zsiz++;
		s_Cylinder.xsiz++;
		SetCylinder(s_Cylinder.xsiz, s_Cylinder.zsiz);
	}

	//���f���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_M) && s_Cylinder.xsiz > 1)
	{
		s_Cylinder.zsiz--;
		s_Cylinder.xsiz--;
		SetCylinder(s_Cylinder.xsiz, s_Cylinder.zsiz);
	}
}

//=========================================
// �`�揈��
//=========================================
void DrawCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
							// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&s_Cylinder.mtxWorld);

	// �����𔽉f
	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Cylinder.rot.y, s_Cylinder.rot.x, s_Cylinder.rot.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&s_Cylinder.mtxWorld, &s_Cylinder.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, s_Cylinder.pos.x, s_Cylinder.pos.y, s_Cylinder.pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&s_Cylinder.mtxWorld, &s_Cylinder.mtxWorld, &mtxTrans);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &s_Cylinder.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�ݒ�
	pDevice->SetIndices(s_pIdxBuff);
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, s_pTextureCylinder);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, s_Cylinder.Vtx, 0, s_Cylinder.por);
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}
//----------------
//���b�V���ݒ�
//----------------
void SetCylinder(int X, int Z)//�ꏊ.��]
{
	UninitCylinder();
	InitCylinder();
}
//----------------------
//�Q�b�g(�\����)
//-----------------------
CYLINDER *GetCylinder(void)
{
	return &s_Cylinder;
}