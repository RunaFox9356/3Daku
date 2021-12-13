//==================
//�G�t�F�N�g
//autho hamadaryuuga
//==================
#include"effect.h"

//�X�^�e�B�b�N�ϐ�///�X�^�e�B�b�N���w�b�^�Ɏg���Ȃ�H
#define NUM_MAX (3)  

static LPDIRECT3DTEXTURE9 s_pTextureEffect[NUM_MAX] = {}; //�e�N�X�`���̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuffEffect = NULL; //���_�o�b�t�@�̐ݒ�
static Effect s_aEffect[MAX_EFFECT];


void InitEffect(void)
{
	LPDIRECT3DDEVICE9  pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/effect000.jpg",
		&s_pTextureEffect[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/pipo-btleffect007.png",
		&s_pTextureEffect[1]);
	

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,//�������_�t�H�[�}�b�g
		&s_pVtxBuffEffect,
		NULL);

	VERTEX_3D*pVtx; //���_�ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	s_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//�������Y��Ȃ�
		s_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		s_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aEffect[nCntEffect].nLife = 0;
		s_aEffect[nCntEffect].bUse = false;
		s_aEffect[nCntEffect].fRadeius = 0;
		s_aEffect[nCntEffect].Trigger = 0;   //���
		s_aEffect[nCntEffect].nType = EFFECTTYPE_LINE;//
		s_aEffect[nCntEffect].nDivisionX = 1;
		s_aEffect[nCntEffect].nDivisionY = 1;
		s_aEffect[nCntEffect].nDivisionMAX = 1;
		s_aEffect[nCntEffect].speed = 1;
		SetNorotpos(pVtx,
			s_aEffect[nCntEffect].pos.x - MAX_RECIPEEFFECT - s_aEffect[nCntEffect].fRadeius,
			s_aEffect[nCntEffect].pos.x + MAX_RECIPEEFFECT + s_aEffect[nCntEffect].fRadeius,
			s_aEffect[nCntEffect].pos.y - MAX_RECIPEEFFECT - s_aEffect[nCntEffect].fRadeius,
			s_aEffect[nCntEffect].pos.y + MAX_RECIPEEFFECT + s_aEffect[nCntEffect].fRadeius,
			0.0f,
			0.0f);
		//���_���W
	
		//���_�J���[�̐ݒ�
		pVtx[0].col = s_aEffect[nCntEffect].col;
		pVtx[1].col = s_aEffect[nCntEffect].col;
		pVtx[2].col = s_aEffect[nCntEffect].col;
		pVtx[3].col = s_aEffect[nCntEffect].col;

		//�e�N�X�`���̍��W�ݒ�
		
		Settex(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);

		pVtx += 4; //���_�|�C���g���l�i��
	}

	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffEffect->Unlock();
}
void UninitEffect(void)
{
	//
	for (int i = 0; i < NUM_MAX; i++)
	{
		if (s_pTextureEffect[i] != NULL)
		{
			s_pTextureEffect[i]->Release();
			s_pTextureEffect[i] = NULL;
		}
	}
	

	//���_�o�b�t�@�̔j��
	if (s_pVtxBuffEffect != NULL)
	{
		s_pVtxBuffEffect->Release();
		s_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_3D*pVtx; //���_�ւ̃|�C���^
					//���_�o�b�t�@���A�����b�N
	s_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (s_aEffect[nCntEffect].bUse)
		{
			switch (s_aEffect[nCntEffect].nType)
			{
			case EFFECTTYPE_LINE:
				s_aEffect[nCntEffect].fRadeius -= 0.05f;

				SetNorotpos(pVtx,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					0.0f,
					0.0f);

				//���_�J���[�̐ݒ�
				pVtx[0].col = s_aEffect[nCntEffect].col;
				pVtx[1].col = s_aEffect[nCntEffect].col;
				pVtx[2].col = s_aEffect[nCntEffect].col;
				pVtx[3].col = s_aEffect[nCntEffect].col;

				//�������s�����Ƃ�
				//s_aEffect[nCntEffect].nLife--;
				if (s_aEffect[nCntEffect].fRadeius <= 0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				break;
			case EFFECTTYPE_MP:

				if ((s_aEffect[nCntEffect].nCounterAnim % s_aEffect[nCntEffect].speed) == 0)//�����ő��x����
				{
					s_aEffect[nCntEffect].nPatternAnim++;

					//�\�����W���X�V
					Settex(pVtx
						, 1.0f / s_aEffect[nCntEffect].nDivisionX * (s_aEffect[nCntEffect].nPatternAnim % (s_aEffect[nCntEffect].nDivisionX ))
						, 1.0f / s_aEffect[nCntEffect].nDivisionX *(s_aEffect[nCntEffect].nPatternAnim % (s_aEffect[nCntEffect].nDivisionX )) + 1.0f / s_aEffect[nCntEffect].nDivisionX
						, 1.0f / s_aEffect[nCntEffect].nDivisionY * (s_aEffect[nCntEffect].nPatternAnim / (s_aEffect[nCntEffect].nDivisionY))
						, 1.0f / s_aEffect[nCntEffect].nDivisionY * (s_aEffect[nCntEffect].nPatternAnim / ( s_aEffect[nCntEffect].nDivisionY) + 1.0f / s_aEffect[nCntEffect].nDivisionY* s_aEffect[nCntEffect].nDivisionY));
				if (s_aEffect[nCntEffect].nPatternAnim >= s_aEffect[nCntEffect].nDivisionMAX)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				}
				s_aEffect[nCntEffect].fRadeius -= 0.5f;

				SetNorotpos(pVtx,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					+1.0f,
					+1.0f,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius);

				//���_�J���[�̐ݒ�
				pVtx[0].col = s_aEffect[nCntEffect].col;
				pVtx[1].col = s_aEffect[nCntEffect].col;
				pVtx[2].col = s_aEffect[nCntEffect].col;
				pVtx[3].col = s_aEffect[nCntEffect].col;

				s_aEffect[nCntEffect].nCounterAnim++;
			

				//�������s�����Ƃ�
				//s_aEffect[nCntEffect].nLife--;
				
				break;
			default:
				break;
			}
			
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffEffect->Unlock();
}
void DrawEffect(void)
{
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScale, mtxTrans, mtxRot;	// �v�Z�p�}�g���b�N�X

		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (s_aEffect[nCntEffect].bUse)
		{

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, s_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// ���[���h�}�g���b�N�X�̏�����
			// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
			D3DXMatrixIdentity(&s_aEffect[nCntEffect].mtxWorld);
			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			switch (s_aEffect[nCntEffect].nType)
			{
			case EFFECTTYPE_LINE:
				//�t���ݒ�
				s_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
				s_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
				s_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
				s_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
				s_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
				s_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
				s_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
				s_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
				s_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;
				break;
			case EFFECTTYPE_MP:
				//�t���ݒ�
		
				break;
			default:
				break;
			}


			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, s_aEffect[nCntEffect].pos.x, s_aEffect[nCntEffect].pos.y, s_aEffect[nCntEffect].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_aEffect[nCntEffect].mtxWorld, &s_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			if (s_aEffect[nCntEffect].bZbf)
			{	//�ݒ�false�ɂ���Z�N��
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			}
			// ���[���h���W�s��̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &s_aEffect[nCntEffect].mtxWorld);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, s_pTextureEffect[s_aEffect[nCntEffect].nType]);
			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, s_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife, EFFECTTYPE nType, bool bZbf, bool bAbf)
{
	int nCntEffect;
	VERTEX_3D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (s_aEffect[nCntEffect].bUse == false)
		{

			//�G���g�p����ĂȂ��ꍇ
			s_aEffect[nCntEffect].fRadeius = fRadeius;
			s_aEffect[nCntEffect].pos = pos;
			s_aEffect[nCntEffect].bAbf = bAbf;
			s_aEffect[nCntEffect].bZbf = bZbf;
			s_aEffect[nCntEffect].nType = nType;
			s_aEffect[nCntEffect].nCounterAnim = 0;
			s_aEffect[nCntEffect].nPatternAnim = 0;

			switch (s_aEffect[nCntEffect].nType)
			{
			case EFFECTTYPE_LINE:
				s_aEffect[nCntEffect].nDivisionX = 1;
				s_aEffect[nCntEffect].nDivisionY = 1;
				s_aEffect[nCntEffect].speed = 1;
				break;
			case EFFECTTYPE_MP:
				s_aEffect[nCntEffect].nDivisionX = 14;
				s_aEffect[nCntEffect].nDivisionY = 1;
				s_aEffect[nCntEffect].speed = 5;
				break;
			default:
				break;
			}
			s_aEffect[nCntEffect].nDivisionMAX = s_aEffect[nCntEffect].nDivisionX*s_aEffect[nCntEffect].nDivisionY;
			Settex(pVtx, 0.0f, 1.0f / s_aEffect[nCntEffect].nDivisionX, 0.0f, 1.0f / s_aEffect[nCntEffect].nDivisionY);
			SetNorotpos(pVtx,
				 - fRadeius,
				 + fRadeius,
				+1.0f,
				+1.0f,
				 - fRadeius,
				 + fRadeius);

			s_aEffect[nCntEffect].nLife = nLife;
			s_aEffect[nCntEffect].bUse = true;
			s_aEffect[nCntEffect].col = col;
			
			//���_�J���[�̐ݒ�
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	s_pVtxBuffEffect->Unlock();
	
}