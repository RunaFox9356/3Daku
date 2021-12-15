//======================
//�e�ݒ�
//Auther�Fhamada ryuuga
//======================
#include "shadow.h"
#include"kitune.h"

//------------------------------------
// �|���S���̍\���̂��`
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 rot;	// ��]���W
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	bool bUse; //�g���Ă邩
	int nType;
} SHADOW;


//------------------------------------
// static�ϐ�
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// ���_�o�b�t�@�[�ւ̃|�C���^
static LPDIRECT3DTEXTURE9 s_pTextureShadow = {}; //�e�N�X�`���̃|�C���^
static SHADOW Shadow[MAX_SHADOW];								// �|���S���̍\����

//=========================================
// ����������
//=========================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/shadow000.jpg",
		&s_pTextureShadow);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < MAX_SHADOW; i++)
	{
		
		// ����������
		Shadow[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		Shadow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.1f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f,  0.1f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.1f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f,  0.1f, -10.0f);

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		Shadow[i].bUse = false;

		pVtx += 4;
	}
	// ���_���W���A�����b�N
		s_pVtxBuff->Unlock();
}

//=========================================
// �I������
//=========================================
void UninitShadow(void)
{
	// ���_�o�b�t�@�[�̉��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pTextureShadow != NULL)
	{
		s_pTextureShadow->Release();
		s_pTextureShadow = NULL;
	}
}

//=========================================
// �X�V����
//=========================================
void UpdateShadow(void)
{
}

//=========================================
// �`�揈��
//=========================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		
	for (int i = 0; i < MAX_SHADOW; i++)
	{
		if (Shadow[i].bUse)
		{

			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			D3DXMatrixIdentity(&Shadow[i].mtxWorld);

			// �����𔽉f
			// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, Shadow[i].rot.y, Shadow[i].rot.x, Shadow[i].rot.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&Shadow[i].mtxWorld, &Shadow[i].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, Shadow[i].pos.x, Shadow[i].pos.y, Shadow[i].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&Shadow[i].mtxWorld, &Shadow[i].mtxWorld, &mtxTrans);

			// ���[���h���W�s��̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Shadow[i].mtxWorld);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, s_pTextureShadow);
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
		
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}
//----------------------------------
//�Z�b�g
//----------------------------------
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType)//�ꏊ.��]
{	// ���_���W�����b�N
	VERTEX_3D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int i;
	for (i = 0; i < MAX_SHADOW; i++)
	{
		if (Shadow[i].bUse == false)
		{
			// ����������
			Shadow[i].pos = pos;	// ���_���W
			Shadow[i].rot = rot;	// ��]���W
			Shadow[i].nType = nType;
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3( - 10.0f, 0.2f,  + 10.0f);
			pVtx[1].pos = D3DXVECTOR3( + 10.0f, 0.2f,  + 10.0f);
			pVtx[2].pos = D3DXVECTOR3( - 10.0f, 0.2f,  - 10.0f);
			pVtx[3].pos = D3DXVECTOR3( + 10.0f, 0.2f,  - 10.0f);

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			Shadow[i].bUse = true;
			break;
		
		}	
		pVtx += 4;
	}
	return i;
	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();

}
//-------------------------------
//�ʒu�X�V
//-------------------------------
void SetposShadow(int nNumber, D3DXVECTOR3 pos)
{
	Shadow[nNumber].pos = pos;
}
//-------------------------------
//�e���E��
//-------------------------------
void DisappearanceShadow(int nNumber)
{
	Shadow[nNumber].bUse = false;
}