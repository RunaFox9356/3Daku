//======================
//���b�V���ݒ�
//Auther�Fhamada ryuuga
//======================
#include "mesh.h"
#include "input.h"



//------------------------------------
// static�ϐ�
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// ���_�o�b�t�@�[�ւ̃|�C���^
static LPDIRECT3DTEXTURE9 s_pTextureMesh = {}; //�e�N�X�`���̃|�C���^
static LPDIRECT3DINDEXBUFFER9 s_pIdxBuff = {};  //�C���f�b�N�X�o�b�t�@
static MESH s_Mesh;								// �|���S���̍\����



//=========================================
// ����������
//=========================================
void InitMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ����������
	s_Mesh.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_Mesh.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/sky_00290.png",
		&s_pTextureMesh);
	//������
	s_Mesh.xsiz = MAX_MESH;
	s_Mesh.zsiz = MAX_MESH;
	
	//�ӂ̒��_��
	s_Mesh.X = s_Mesh.xsiz + 1;//1��������
	s_Mesh.Z = s_Mesh.zsiz + 1;//1��������

	//���_��
	s_Mesh.Vtx = s_Mesh.X* s_Mesh.Z;//���_�����g���Ă��

	//�C���f�b�N�X��
	s_Mesh.Index = (2 * s_Mesh.X * s_Mesh.zsiz + 2 *(s_Mesh.zsiz - 1));

	s_Mesh.por = s_Mesh.Index - 2;
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * s_Mesh.Vtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(sizeof(WORD) * s_Mesh.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&s_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int i = 0; i < s_Mesh.Vtx; i++)
	{
		float posx = ((i % s_Mesh.X)-1.0f);
		float posz = ((i / s_Mesh.Z)- 1.0f)*-1.0f;
		
		float texU = 1.0f / s_Mesh.xsiz*(i % s_Mesh.X);
		float texV = 1.0f / s_Mesh.zsiz*(i / s_Mesh.Z);
		//�߂������^�񒆂ɂ���␳
		s_Mesh.pos = D3DXVECTOR3(-(posx - 1)*MAX_SIZMESH / 2, 0.0f, -posz * MAX_SIZMESH / 2);

		pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZMESH , 0.0f/D3DX_PI, posz * MAX_SIZMESH);

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ���_�J���[�̐ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < s_Mesh.zsiz; z++)
	{
		int linetop = z * (s_Mesh.X * 2 +2);
		for (int x = 0; x < s_Mesh.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = x + (z * s_Mesh.X);
			pIdx[nIdxData] = pIdx[nIdxData + 1] + s_Mesh.X;
			//pIdx[(x*2+1+((z*Mesh.Z +1))*z)] = x+(z*Mesh.X);
			//pIdx[(x*2 + ((z*Mesh.Z)+3)*z)] = (x+ (Mesh.Z)) + (z*Mesh.X);	
		}
		//�k�ރ|���S���ݒ�
		if (z < s_Mesh.xsiz - 1)
			{
				pIdx[s_Mesh.X * 2+ 0 + linetop] =  s_Mesh.xsiz + s_Mesh.X*z;
				pIdx[s_Mesh.X * 2 + 1 + linetop] = s_Mesh.X * 2 + s_Mesh.X * z;
			}
		
 	}

	// ���_���W���A�����b�N
	s_pIdxBuff->Unlock();

}

//=========================================
// �I������
//=========================================
void UninitMesh(void)
{
	// ���_�o�b�t�@�[�̉��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pTextureMesh != NULL)
	{
		s_pTextureMesh->Release();
		s_pTextureMesh = NULL;
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
void UpdateMesh(void)
{	
	//���f���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_N))
	{
		
		s_Mesh.zsiz++;
		s_Mesh.xsiz++;
		SetMesh(s_Mesh.xsiz, s_Mesh.zsiz);
	}

	//���f���̐؂�ւ�
	if (GetKeyboardTrigger(DIK_M)&& s_Mesh.xsiz > 1)
	{
		s_Mesh.zsiz--;
		s_Mesh.xsiz--;
		SetMesh(s_Mesh.xsiz, s_Mesh.zsiz);
	}
}

//=========================================
// �`�揈��
//=========================================
void DrawMesh(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&s_Mesh.mtxWorld);

	// �����𔽉f
	// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, s_Mesh.rot.y, s_Mesh.rot.x, s_Mesh.rot.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&s_Mesh.mtxWorld, &s_Mesh.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, s_Mesh.pos.x, s_Mesh.pos.y, s_Mesh.pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&s_Mesh.mtxWorld, &s_Mesh.mtxWorld, &mtxTrans);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &s_Mesh.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�ݒ�
	pDevice->SetIndices(s_pIdxBuff);
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, s_pTextureMesh);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, s_Mesh.Vtx,0, s_Mesh.por);
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}
//----------------
//���b�V���ݒ�
//----------------
void SetMesh(int X ,int Z)//�ꏊ.��]
{
	// ���_�o�b�t�@�[�̉��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	if (s_pIdxBuff != NULL)
	{
		s_pIdxBuff->Release();
		s_pIdxBuff = NULL;
	}
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ����������
	s_Mesh.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_Mesh.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

	//������
	s_Mesh.xsiz = X;
	s_Mesh.zsiz = Z;

	//�ӂ̒��_��
	s_Mesh.X = s_Mesh.xsiz + 1;//1��������
	s_Mesh.Z = s_Mesh.zsiz + 1;//1��������

	s_Mesh.Vtx = s_Mesh.X* s_Mesh.Z;//���_�����g���Ă��

	//�C���f�b�N�X��
	s_Mesh.Index = (2 * s_Mesh.X * s_Mesh.zsiz + 2 * (s_Mesh.zsiz - 1));

	s_Mesh.por = s_Mesh.Index - 2;
	 //���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * s_Mesh.Vtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(sizeof(WORD) * s_Mesh.Index,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&s_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	// ���_���W�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	for (int i = 0; i < s_Mesh.Vtx; i++)
	{
		float posx = ((i % s_Mesh.X) - 1.0f);
		float posz = ((i / s_Mesh.Z) - 1.0f)*-1.0f;

		float texU = 1.0f / s_Mesh.xsiz*(i % s_Mesh.X);
		float texV = 1.0f / s_Mesh.zsiz*(i / s_Mesh.Z);

		//�߂������^�񒆂ɂ���␳
		s_Mesh.pos = D3DXVECTOR3(-(posx-1)*MAX_SIZMESH / 2, 0.0f, -posz * MAX_SIZMESH / 2);
		//pos
		pVtx[i].pos += D3DXVECTOR3(posx*MAX_SIZMESH, 0.0f, posz * MAX_SIZMESH);

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		
		// ���_�J���[�̐ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[i].tex = D3DXVECTOR2(texU, texV);

	}

	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	s_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int z = 0; z < s_Mesh.zsiz; z++)
	{
		int linetop = z * (s_Mesh.X * 2 + 2);
		for (int x = 0; x < s_Mesh.X; x++)
		{
			int nIdxData = x * 2 + linetop;
			pIdx[nIdxData + 1] = x + (z * s_Mesh.X);
			pIdx[nIdxData] = pIdx[nIdxData + 1] + s_Mesh.X;
			//pIdx[(x*2+1+((z*Mesh.Z +1))*z)] = x+(z*Mesh.X);
			//pIdx[(x*2 + ((z*Mesh.Z)+3)*z)] = (x+ (Mesh.Z)) + (z*Mesh.X);	
		}
		//�k�ރ|���S���ݒ�
		if (z < s_Mesh.xsiz - 1)
		{
			pIdx[s_Mesh.X * 2 + 0 + linetop] = s_Mesh.xsiz + s_Mesh.X*z;
			pIdx[s_Mesh.X * 2 + 1 + linetop] = s_Mesh.X * 2 + s_Mesh.X * z;
		}
	}

	// ���_���W���A�����b�N
	s_pIdxBuff->Unlock();
}
//----------------------
//�Q�b�g(�\����)
//-----------------------
MESH *GetMesh(void)
{
	return &s_Mesh;
}