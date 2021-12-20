//======================
//�r���{�[�h�ݒ�
//Auther�Fhamada ryuuga
//======================
#include "line.h"
#include "camera.h"
#include"shadow.h"
#include "prayer.h"
#include"effect.h"

//------------------------------------
// static�ϐ�
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// ���_�o�b�t�@�[�ւ̃|�C���^
static LINE s_Line[MAX_LINE];								// �|���S���̍\����
static D3DXVECTOR3 s_RotMove;

//=========================================
// ����������
//=========================================
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * MAX_LINE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;
	//�J�����̃f�[�^�擾

	// ���_���W�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < MAX_LINE; i++)
	{

		// ����������
		s_Line[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		s_Line[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

															// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
		// �e�N�X�`�����W�̐ݒ�
		s_Line[i].bUse = false;

		s_Line[i].nType = 0;
		pVtx += 2;
	}
	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();
}

//=========================================
// �I������
//=========================================
void UninitLine(void)
{
	// ���_�o�b�t�@�[�̉��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}



}

//=========================================
// �X�V����
//=========================================
void UpdateLine(void)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera = GetCamera();

	VERTEX_3D* pVtx = NULL;
	// ���_���W�����b�N


}

//=========================================
// �`�揈��
//=========================================
void DrawLine(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	DWORD Test = 0;


	pDevice->GetRenderState(D3DRS_ALPHAFUNC, &Test);//���傫��

	for (int i = 0; i < MAX_LINE; i++)
	{
		if (s_Line[i].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			D3DXMatrixIdentity(&s_Line[i].mtxWorld);

			//�r���{�[�h�̐ݒ�
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);


			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, s_Line[i].pos.x, s_Line[i].pos.y, s_Line[i].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Line[i].mtxWorld, &s_Line[i].mtxWorld, &mtxTrans);

			//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// ���[���h���W�s��̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &s_Line[i].mtxWorld);


		
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_LINELIST,  i * 2, 1);

		}



	}

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}
//----------------------------------
//�Z�b�g
//----------------------------------
void SetLine(D3DXVECTOR3 Maxpos, D3DXVECTOR3  Minpos,D3DXVECTOR3 pos )//�ꏊ.��].�F.�^�C�v
{

	PRAYER *pPrayer = GetPrayer();

	// ���_���W�����b�N
	VERTEX_3D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int i;
	for (i = 0; i < MAX_LINE; i++)
	{
		if (s_Line[i].bUse == false)
		{
	
			// ���_���W�̐ݒ�
			pVtx[0].pos = pos + Minpos;
			pVtx[1].pos = pos + Maxpos;


			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			
			// ���_�J���[�̐ݒ�
			
			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		


																				 //�g���Ă邩�ǂ���
			s_Line[i].bUse = true;
			break;

		}
		pVtx += 2;
	}

	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();

}

