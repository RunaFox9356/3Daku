//��������������������������
//effect.cpp
//��������������������������
#include "paticle.h"
#include "model.h"
#include "input.h"
#include <stdlib.h>
#include <assert.h>

//�O���[�o���ϐ��錾
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;
static LPDIRECT3DTEXTURE9	s_pTexture[NUM_PARTICLE] = {};
PARTICLE s_aParticle[MAX_PARTICLE];



//��������������������������
//PARTICLE�̏�����
//��������������������������
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/pipo-btleffect040.png",
		&s_pTexture[PARTICLETYPE_LIGHTNING]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Sprite-0001-Sheet.png",
		&s_pTexture[PARTICLETYPE_KITUNE]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/pipo-gwspinitem017.png",
		&s_pTexture[PARTICLETYPE_OUKAN]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/Title102.png",
		&s_pTexture[PARTICLETYPE_MERA]);
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//���_�o�b�t�@�����b�N
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = s_aParticle[nCntParticle].pos;
		pVtx[1].pos = s_aParticle[nCntParticle].pos;
		pVtx[2].pos = s_aParticle[nCntParticle].pos;
		pVtx[3].pos = s_aParticle[nCntParticle].pos;

		//�e���_�̖@���̐ݒ�@���@�x�N�g���̑傫����1�ɂ���K�v������
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		s_aParticle[nCntParticle].speed = 1;
		s_aParticle[nCntParticle].nDivisionMAX = 1;
		s_aParticle[nCntParticle].nDivisionX = 1;
		s_aParticle[nCntParticle].nDivisionY = 1;
		Settex(pVtx, 0.0f, 1.0f, 0.0f, 1.0f);
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	s_pVtxBuff->Unlock();
}

//��������������������������
//PARTICLE�̏I��
//��������������������������
void UninitParticle(void)
{
	//�e�N�X�`���̔j��
	for (int nCntParticle = 0; nCntParticle < NUM_PARTICLE; nCntParticle++)
	{
		if (s_pTexture[nCntParticle] != NULL)
		{
			s_pTexture[nCntParticle]->Release();
			s_pTexture[nCntParticle] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//��������������������������
//PARTICLE�̍X�V
//��������������������������
void UpdateParticle(void)
{
	//float X, Y;//�f�[�^�v���p
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		//�ʒu���X�V
		s_aParticle[nCntParticle].pos.x += s_aParticle[nCntParticle].move.x;
		s_aParticle[nCntParticle].pos.y += s_aParticle[nCntParticle].move.y;
		s_aParticle[nCntParticle].pos.z += s_aParticle[nCntParticle].move.z;

		//==========================
		//PARTICLE�̎��
		//==========================
		switch (s_aParticle[nCntParticle].type)
		{
		case PARTICLETYPE_LIGHTNING:	//���݂Ȃ�
			s_aParticle[nCntParticle].col.g -= 0.0075f;
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fWidth -= 0.002f;
			s_aParticle[nCntParticle].fHeight -= 0.002f;
			s_aParticle[nCntParticle].fAngle -= 30.0f;
			s_aParticle[nCntParticle].fRadius += s_aParticle[nCntParticle].fAngle * (D3DX_PI * 2);
			s_aParticle[nCntParticle].fAttenuation = 250.0f;
			s_aParticle[nCntParticle].fAttenuation -= 30.0f;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));
			s_aParticle[nCntParticle].move.y -= tanf(D3DX_PI) * s_aParticle[nCntParticle].fRadius / 2;
			s_aParticle[nCntParticle].move.z = -cosf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));
		

			break;
		case PARTICLETYPE_KITUNE:	//�ω�	/*�������͉�]�����Ȃ���㏸*/
			s_aParticle[nCntParticle].col.g -= 0.0075f;
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fWidth -= 0.002f;
			s_aParticle[nCntParticle].fHeight -= 0.002f;
			s_aParticle[nCntParticle].fAngle -= 30.0f;
			s_aParticle[nCntParticle].fRadius += s_aParticle[nCntParticle].fAngle * (D3DX_PI * 2);
			s_aParticle[nCntParticle].fAttenuation = 250.0f;
			s_aParticle[nCntParticle].fAttenuation -= 30.0f;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation))) * 3;
			s_aParticle[nCntParticle].move.y -= tanf(D3DX_PI) * s_aParticle[nCntParticle].fRadius / 10;
			s_aParticle[nCntParticle].move.z = -cosf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));
		

			break;
		case PARTICLETYPE_OUKAN:	//����	/*�������͉�]�����Ȃ���㏸*/
			s_aParticle[nCntParticle].col.g -= 0.0075f;
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fWidth -= 0.002f;
			s_aParticle[nCntParticle].fHeight -= 0.002f;
			s_aParticle[nCntParticle].fAngle -= 30.0f;
			s_aParticle[nCntParticle].fRadius += s_aParticle[nCntParticle].fAngle * (D3DX_PI * 2);
			s_aParticle[nCntParticle].fAttenuation = 250.0f;
			s_aParticle[nCntParticle].fAttenuation -= 30.0f;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation))) ;
			s_aParticle[nCntParticle].move.y -= tanf(D3DX_PI) * s_aParticle[nCntParticle].fRadius / 10;
			s_aParticle[nCntParticle].move.z = -cosf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));
		

			break;
		case PARTICLETYPE_MERA:	//�ꖇ�G	/*�������͉�]�����Ȃ���㏸*/
			s_aParticle[nCntParticle].col.g -= 0.0075f;
			s_aParticle[nCntParticle].col.a -= 0.005f;
			s_aParticle[nCntParticle].fWidth -= 0.002f;
			s_aParticle[nCntParticle].fHeight -= 0.002f;
			s_aParticle[nCntParticle].fAngle -= 30.0f;
			s_aParticle[nCntParticle].fRadius += s_aParticle[nCntParticle].fAngle * (D3DX_PI * 2);
			s_aParticle[nCntParticle].fAttenuation = 250.0f;
			s_aParticle[nCntParticle].fAttenuation -= 30.0f;
			s_aParticle[nCntParticle].move.x = -sinf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation))) * 3;
			s_aParticle[nCntParticle].move.y -= tanf(D3DX_PI) * s_aParticle[nCntParticle].fRadius / 2;
			s_aParticle[nCntParticle].move.z = -cosf((D3DX_PI * nCntParticle / 10) - (s_aParticle[nCntParticle].fAngle / (5 * s_aParticle[nCntParticle].fAttenuation)));
			

			break;
		default:	//��L�ȊO
			break;
		}

		//PARTICLE�̎���
		s_aParticle[nCntParticle].nLife--;

		if (s_aParticle[nCntParticle].nLife == 0)
		{
			DeleteParticle(nCntParticle);
		}
		// ���_���ւ̃|�C���^�𐶐�
		VERTEX_3D *pVtx;
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntParticle;	// ���_�f�[�^�̃|�C���^��4���i�߂�
		//�e�N�X�`���ݒ�
		s_aParticle[nCntParticle].col.a -= 1.0f / s_aParticle[nCntParticle].nMaxLife;
		s_aParticle[nCntParticle].nCounterAnim++;
		if ((s_aParticle[nCntParticle].nCounterAnim % s_aParticle[nCntParticle].speed) == 0)//�����ő��x����
		{
			s_aParticle[nCntParticle].nPatternAnim = (s_aParticle[nCntParticle].nPatternAnim + 1) % s_aParticle[nCntParticle].nDivisionMAX;

			//�\�����W���X�V
			Settex(pVtx,
				1.0f / s_aParticle[nCntParticle].nDivisionX * (s_aParticle[nCntParticle].nPatternAnim % (s_aParticle[nCntParticle].nDivisionX ))
				, 1.0f / s_aParticle[nCntParticle].nDivisionX *(s_aParticle[nCntParticle].nPatternAnim % (s_aParticle[nCntParticle].nDivisionX )) + 1.0f / s_aParticle[nCntParticle].nDivisionX
				, 1.0f / s_aParticle[nCntParticle].nDivisionY * (s_aParticle[nCntParticle].nPatternAnim / ( s_aParticle[nCntParticle].nDivisionY))
				, 1.0f / s_aParticle[nCntParticle].nDivisionY * (s_aParticle[nCntParticle].nPatternAnim / ( s_aParticle[nCntParticle].nDivisionY) + 1.0f / s_aParticle[nCntParticle].nDivisionY* s_aParticle[nCntParticle].nDivisionY));
		}

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-s_aParticle[nCntParticle].fWidth, s_aParticle[nCntParticle].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(s_aParticle[nCntParticle].fWidth, s_aParticle[nCntParticle].fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-s_aParticle[nCntParticle].fWidth, -s_aParticle[nCntParticle].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(s_aParticle[nCntParticle].fWidth, -s_aParticle[nCntParticle].fHeight, 0.0f);

		//���_�J���[
		pVtx[0].col = s_aParticle[nCntParticle].col;
		pVtx[1].col = s_aParticle[nCntParticle].col;
		pVtx[2].col = s_aParticle[nCntParticle].col;
		pVtx[3].col = s_aParticle[nCntParticle].col;

		//���_�o�b�t�@�̃A�����b�N
		s_pVtxBuff->Unlock();
	}
}

//��������������������������
//PARTICLE�̕`��
//��������������������������
void DrawParticle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X
	int nCntParticle;

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (s_aParticle[nCntParticle].bUse)
		{
			//���[���h�}�g���b�N�X��������
			D3DXMatrixIdentity(&s_aParticle[nCntParticle].mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�J�����̋t�s���ݒ�
			s_aParticle[nCntParticle].mtxWorld._11 = mtxView._11;
			s_aParticle[nCntParticle].mtxWorld._12 = mtxView._21;
			s_aParticle[nCntParticle].mtxWorld._13 = mtxView._31;
			s_aParticle[nCntParticle].mtxWorld._21 = mtxView._12;
			s_aParticle[nCntParticle].mtxWorld._22 = mtxView._22;
			s_aParticle[nCntParticle].mtxWorld._23 = mtxView._32;
			s_aParticle[nCntParticle].mtxWorld._31 = mtxView._13;
			s_aParticle[nCntParticle].mtxWorld._32 = mtxView._23;
			s_aParticle[nCntParticle].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, s_aParticle[nCntParticle].pos.x, s_aParticle[nCntParticle].pos.y, s_aParticle[nCntParticle].pos.z);
			D3DXMatrixMultiply(&s_aParticle[nCntParticle].mtxWorld, &s_aParticle[nCntParticle].mtxWorld, &mtxTrans);

			//���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			//Z�o�b�t�@�Ɋւ�炸�`��
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &s_aParticle[nCntParticle].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, s_pTexture[s_aParticle[nCntParticle].type]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntParticle * 4,
				2);

			//���C�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	//�ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�o�b�t�@�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�e�N�X�`���������p���Ȃ�
	pDevice->SetTexture(0, NULL);
}

//��������������������������
//PARTICLE�̐ݒ�
//��������������������������
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight, PARTICLETYPE type,int nLife)
{
	VERTEX_3D * pVtx = NULL;
	int nCntParticle;
	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (!s_aParticle[nCntParticle].bUse)
		{
			// ���_���ւ̃|�C���^�𐶐�
			VERTEX_3D *pVtx;
			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * nCntParticle;	// ���_�f�[�^�̃|�C���^��4���i�߂�
			s_aParticle[nCntParticle].pos = pos;
			s_aParticle[nCntParticle].move = move / 5;
			s_aParticle[nCntParticle].col = col;
			s_aParticle[nCntParticle].type = type;
			s_aParticle[nCntParticle].fWidth = fWidth;
			s_aParticle[nCntParticle].fHeight = fHeight;
			s_aParticle[nCntParticle].fAngle = 5.0f;
			s_aParticle[nCntParticle].nLife = nLife;
			s_aParticle[nCntParticle].nMaxLife = s_aParticle[nCntParticle].nLife;
			switch (s_aParticle[nCntParticle].type)
			{

			case PARTICLETYPE_LIGHTNING:	//���݂Ȃ�
				s_aParticle[nCntParticle].nDivisionX = 8;
				s_aParticle[nCntParticle].nDivisionY = 1;
				s_aParticle[nCntParticle].speed = 5;
				break;
			case PARTICLETYPE_KITUNE:	//�ω�	/*�������͉�]�����Ȃ���㏸*/
				s_aParticle[nCntParticle].nDivisionX = 5;
				s_aParticle[nCntParticle].nDivisionY = 1;
				s_aParticle[nCntParticle].speed = 5;			
				break;
			case PARTICLETYPE_OUKAN:	//����	/*�������͉�]�����Ȃ���㏸*/
				s_aParticle[nCntParticle].nDivisionX = 5;
				s_aParticle[nCntParticle].nDivisionY = 4;
				s_aParticle[nCntParticle].speed = 10;
				break;
			case PARTICLETYPE_MERA:	//�ꖇ�G	/*�������͉�]�����Ȃ���㏸*/
				
				s_aParticle[nCntParticle].nDivisionX = 1;
				s_aParticle[nCntParticle].nDivisionY = 1;
				s_aParticle[nCntParticle].speed = 1;
				break;
			default:	//��L�ȊO
				break;
			}
			Settex(pVtx, 0.0f, 1.0f / s_aParticle[nCntParticle].nDivisionX, 0.0f, 1.0f / s_aParticle[nCntParticle].nDivisionY);
			s_aParticle[nCntParticle].nDivisionMAX = s_aParticle[nCntParticle].nDivisionX*s_aParticle[nCntParticle].nDivisionY;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-s_aParticle[nCntParticle].fWidth, s_aParticle[nCntParticle].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(s_aParticle[nCntParticle].fWidth, s_aParticle[nCntParticle].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-s_aParticle[nCntParticle].fWidth, -s_aParticle[nCntParticle].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(s_aParticle[nCntParticle].fWidth, -s_aParticle[nCntParticle].fHeight, 0.0f);

			//���_�J���[
			pVtx[0].col = s_aParticle[nCntParticle].col;
			pVtx[1].col = s_aParticle[nCntParticle].col;
			pVtx[2].col = s_aParticle[nCntParticle].col;
			pVtx[3].col = s_aParticle[nCntParticle].col;

			//���_�o�b�t�@�̃A�����b�N
			s_pVtxBuff->Unlock();

			s_aParticle[nCntParticle].bUse = true;

			break;
		}
	
	}
}

//��������������������������
//�T�uPARTICLE�̐ݒ�
//��������������������������
void SubSetParticle(int nSubParticle, PARTICLETYPE type)
{

}

//��������������������������
//PARTICLE�̍폜
//��������������������������
void DeleteParticle(int nParticle)
{
	s_aParticle[nParticle].bUse = false;
	s_aParticle[nParticle].move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	s_aParticle[nParticle].fAngle = 0.0f;
	s_aParticle[nParticle].fRadius = 0.0f;
	s_aParticle[nParticle].fAttenuation = 0.0f;
}

//��������������������������
//PARTICLE�̎擾
//��������������������������
PARTICLE *GetParticle(void)
{
	return &s_aParticle[0];
}