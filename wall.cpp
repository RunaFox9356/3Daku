//=======================
//�ǐݒ�
//Auther�Fhamada ryuuga
//=======================
#include "wall.h"
#include"mesh.h"

//------------------------------------
// �|���S���̍\���̂��`
//------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 rot;	// ��]���W
	D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	bool bUse; //�g���Ă邩

} WALL;


//------------------------------------
// static�ϐ�
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// ���_�o�b�t�@�[�ւ̃|�C���^
static LPDIRECT3DTEXTURE9 s_pTextureWall = {}; //�e�N�X�`���̃|�C���^
static WALL s_Wall[MAX_WALL];								// �|���S���̍\����

//=========================================
// ����������
//=========================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/sky_00290.png",
		&s_pTextureWall);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < MAX_WALL; i++)
	{

		// ����������
		s_Wall[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		s_Wall[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f,  100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f,  0.0f, 0.0f);

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

		s_Wall[i].bUse = false;

		pVtx += 4;
	}
	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();
}

//=========================================
// �I������
//=========================================
void UninitWall(void)
{
	// ���_�o�b�t�@�[�̉��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pTextureWall != NULL)
	{
		s_pTextureWall->Release();
		s_pTextureWall = NULL;
	}
}

//=========================================
// �X�V����
//=========================================
void UpdateWall(void)
{

}

//=========================================
// �`�揈��
//=========================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

									//���Z����


	for (int i = 0; i < MAX_WALL; i++)
	{
		if (s_Wall[i].bUse)
		{

			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			D3DXMatrixIdentity(&s_Wall[i].mtxWorld);

			// �����𔽉f
			// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
			D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Wall[i].rot.y, s_Wall[i].rot.x, s_Wall[i].rot.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Wall[i].mtxWorld, &s_Wall[i].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, s_Wall[i].pos.x, s_Wall[i].pos.y, s_Wall[i].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Wall[i].mtxWorld, &s_Wall[i].mtxWorld, &mtxTrans);

			// ���[���h���W�s��̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &s_Wall[i].mtxWorld);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, s_pTextureWall);
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
		}
	}
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

}
//----------------------------------
//�Z�b�g
//----------------------------------
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col)//�ꏊ.��].�F
{	// ���_���W�����b�N
	VERTEX_3D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int i;
	for (i = 0; i < MAX_WALL; i++)
	{
		if (s_Wall[i].bUse == false)
		{
			// ����������
			s_Wall[i].pos = pos;	// ���_���W
			s_Wall[i].rot = rot;	// ��]���W
			
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3( - 100.0f, 100.0f,0.0f );
			pVtx[1].pos = D3DXVECTOR3( + 100.0f, 100.0f,0.0f );
			pVtx[2].pos = D3DXVECTOR3( - 100.0f, 0.0f,	0.0f );
			pVtx[3].pos = D3DXVECTOR3( + 100.0f, 0.0f,  0.0f );

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			s_Wall[i].bUse = true;
			break;

		}
		pVtx += 4;
	}

	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();

}
