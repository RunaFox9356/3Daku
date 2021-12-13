//======================
//�r���{�[�h�ݒ�
//Auther�Fhamada ryuuga
//======================
#include "kitune.h"
#include "camera.h"
#include"shadow.h"
#include "model.h"
#include"effect.h"

//------------------------------------
// static�ϐ�
//------------------------------------
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// ���_�o�b�t�@�[�ւ̃|�C���^
static LPDIRECT3DTEXTURE9 s_pTextureKitune[MAX_TEX] = {}; //�e�N�X�`���̃|�C���^
static KITUNE s_Kitune[MAX_KITUNE];								// �|���S���̍\����
static D3DXVECTOR3 s_RotMove;

//=========================================
// ����������
//=========================================
void InitKitune(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/211.png",
		&s_pTextureKitune[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/bullet004.png",
		&s_pTextureKitune[1]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_KITUNE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;
	//�J�����̃f�[�^�擾
	
	// ���_���W�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < MAX_KITUNE; i++)
	{

		// ����������
		s_Kitune[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
		s_Kitune[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-10.0f,0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 10.0f,0.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 10.0f, 0.0f);

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�

		Settex(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);
		s_Kitune[i].bUse = false;
			
		s_Kitune[i].nType = 0;
		pVtx += 4;
	}
	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();
}

//=========================================
// �I������
//=========================================
void UninitKitune(void)
{
	// ���_�o�b�t�@�[�̉��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
	
	for (int i = 0; i < MAX_TEX; i++)
	{
		if (s_pTextureKitune[i] != NULL)
		{
			s_pTextureKitune[i]->Release();
			s_pTextureKitune[i] = NULL;
		}
	}


}

//=========================================
// �X�V����
//=========================================
void UpdateKitune(void)
{
	//�J�����̃f�[�^�擾
	CAMERA *pCamera= GetCamera();
	
	VERTEX_3D* pVtx = NULL;
	// ���_���W�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_KITUNE; i++)
	{
		if (s_Kitune[i].bUse)
		{
			if (s_Kitune[i].nType == 1)
			{
				s_Kitune[i].des--;
				s_Kitune[i].pos.x = s_Kitune[i].pos.x -= s_Kitune[i].moveX*BallSpede;
				s_Kitune[i].pos.z = s_Kitune[i].pos.z -= s_Kitune[i].moveZ*BallSpede;
				SetposShadow(s_Kitune[i].nShadow, s_Kitune[i].pos);
				SetEffect(s_Kitune[i].pos, D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.5f), 15.0, 150, EFFECTTYPE_LINE, true, true);

				/*if (s_Kitune[i].pos.x < -90.0f)
				{
					s_Kitune[i].bUse = false;
					DisappearanceShadow(s_Kitune[i].nShadow);
				}
				if (s_Kitune[i].pos.x > 90.0f)
				{
					s_Kitune[i].bUse = false;
					DisappearanceShadow(s_Kitune[i].nShadow);
				}
				if (s_Kitune[i].pos.z < -90.0f)
				{
					s_Kitune[i].bUse = false;
					DisappearanceShadow(s_Kitune[i].nShadow);
				}
				if (s_Kitune[i].pos.z > 90.0f)
				{
					s_Kitune[i].bUse = false;
					DisappearanceShadow(s_Kitune[i].nShadow);
				}*/

				if (s_Kitune[i].des < 0)
				{
					s_Kitune[i].bUse = false;
					DisappearanceShadow(s_Kitune[i].nShadow);
				}
			}
		}
		pVtx += 4;
	}

}

//=========================================
// �`�揈��
//=========================================
void DrawKitune(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	DWORD Test = 0;


	pDevice->GetRenderState(D3DRS_ALPHAFUNC, &Test);//���傫��

	for (int i = 0; i < MAX_KITUNE; i++)
	{
		if (s_Kitune[i].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			D3DXMatrixIdentity(&s_Kitune[i].mtxWorld);
			
			//�r���{�[�h�̐ݒ�
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�Q�����Ă�������Y����
			//�t���ݒ�
			s_Kitune[i].mtxWorld._11 = mtxView._11;
			s_Kitune[i].mtxWorld._12 = mtxView._21;
			s_Kitune[i].mtxWorld._13 = mtxView._31;
			//s_Kitune[i].mtxWorld._21 = mtxView._12;
			//s_Kitune[i].mtxWorld._22 = mtxView._22;
			//s_Kitune[i].mtxWorld._23 = mtxView._32;
			s_Kitune[i].mtxWorld._31 = mtxView._13;
			s_Kitune[i].mtxWorld._32 = mtxView._23;
			s_Kitune[i].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, s_Kitune[i].pos.x, s_Kitune[i].pos.y, s_Kitune[i].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_Kitune[i].mtxWorld, &s_Kitune[i].mtxWorld, &mtxTrans);

			//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			if (s_Kitune[i].nType == 0)
			{
				//Z�e�X�g
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			}
			if (s_Kitune[i].nType == 1)
			{//�A���t�@�e�X�g
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//�ł�����܂�
				//�f�t�H���g��false�ł�
				pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);//�F�����Ă�
																			   //����͏������������I�����܂�
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);//���傫��
			}
			

			// ���[���h���W�s��̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &s_Kitune[i].mtxWorld);
			

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, s_pTextureKitune[s_Kitune[i].nType]);
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);

		}
			


	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//�ł�����܂�
	pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);//�F�����Ă�//����͏������������I�����܂�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);//���傫��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}
//----------------------------------
//�Z�b�g
//----------------------------------
void SetKitune(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,int nType)//�ꏊ.��].�F.�^�C�v
{	
	
	MODEL *pModel;
	pModel = GetModel();
	// ���_���W�����b�N
	VERTEX_3D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int i;
	for (i = 0; i < MAX_KITUNE; i++)
	{
		if (s_Kitune[i].bUse == false)
		{
			// ����������
			s_Kitune[i].pos = pos;	// ���_���W
			s_Kitune[i].rot = rot;	// ��]���W
			s_Kitune[i].nType = nType;
			s_Kitune[i].des = 100;
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+10.0f, 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f,  0.0f);
			pVtx[3].pos = D3DXVECTOR3(+10.0f, 0.0f,  0.0f);

			// �e���_�̖@���̐ݒ�(���x�N�g���̑傫����1�ɂ���K�v������)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			s_Kitune[i].moveX = sinf(pModel->rot.y);
			s_Kitune[i].moveZ = cosf(pModel->rot.y);
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
		
 			s_Kitune[i].nShadow = SetShadow(s_Kitune[i].pos, s_Kitune[i].rot,1);//�ꏊ.��]
			
			
			//�g���Ă邩�ǂ���
			s_Kitune[i].bUse = true;
			break;

		}
		pVtx += 4;
	}

	// ���_���W���A�����b�N
	s_pVtxBuff->Unlock();

}
//----------------------
//�Q�b�g
//-----------------------
KITUNE *GetKitune(void)
{
	return &s_Kitune[0];
}

