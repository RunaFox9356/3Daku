//==================
//�G�t�F�N�g
//autho hamadaryuuga
//==================
#include"effect.h"
#include"paticle.h"
#include "comn.h"

//�X�^�e�B�b�N�ϐ�///�X�^�e�B�b�N���w�b�^�Ɏg���Ȃ�H
#define NUM_MAX (16)  

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
		&s_pTextureEffect[EFFECTTYPE_LINE]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle1.png",
		&s_pTextureEffect[EFFECTTYPE_MP]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle2.png",
		&s_pTextureEffect[EFFECTTYPE_MP2]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle3.png",
		&s_pTextureEffect[EFFECTTYPE_MP3]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle4.png",
		&s_pTextureEffect[EFFECTTYPE_MP4]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/MagicCircle5.png",
		&s_pTextureEffect[EFFECTTYPE_MP5]);
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-27.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-29.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK2]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-28.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK3]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-26.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK4]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-32.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK5]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-33.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK6]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-37.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK7]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-36.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK8]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-35.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK9]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"Data/TEXTURE/50-38.jpg",
		&s_pTextureEffect[EFFECTTYPE_CLOCK10]);
	

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
		s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.1f, 0.0f);	// ��]���W
		s_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		s_aEffect[nCntEffect].nLife = 0;
		s_aEffect[nCntEffect].bUse = false;
		s_aEffect[nCntEffect].bSiz = false;
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
				//���@�w��]���x
			case EFFECTTYPE_MP:
			case EFFECTTYPE_CLOCK:
				if (s_aEffect[nCntEffect].easeInspeed <= 120)//�ō����x����
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}		
				if (s_aEffect[nCntEffect].bRot)//��-����́@���Ă邩���ɂ��邩
				{	//�C�[�W���O�@��悵�Ă�@D3DX_PI / X�̐�����]���x�ɓ�悵�Ă܂�
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 3100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{	
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 1100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}	
				break;
			case EFFECTTYPE_MP2:
			case EFFECTTYPE_CLOCK2:
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 3100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 1000.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			case EFFECTTYPE_MP3:
			case EFFECTTYPE_CLOCK3:
			
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}	
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 3100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 1200.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			case EFFECTTYPE_MP4:
			case EFFECTTYPE_CLOCK4:
			
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 3100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 800.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			case EFFECTTYPE_MP5:
			case EFFECTTYPE_CLOCK5:
			
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}	
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z += SeteaseIn((D3DX_PI / 5100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 900.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			case EFFECTTYPE_CLOCK6:
				if (s_aEffect[nCntEffect].easeInspeed <= 120)
				{
					s_aEffect[nCntEffect].easeInspeed++;
				}
				if (s_aEffect[nCntEffect].bRot)
				{
					s_aEffect[nCntEffect].rot.z -= SeteaseIn((D3DX_PI / 2100.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				else
				{
					s_aEffect[nCntEffect].rot.y += SeteaseIn((D3DX_PI / 900.0f) *s_aEffect[nCntEffect].easeInspeed);
				}
				break;
			default:
				break;
			}
		
			if (s_aEffect[nCntEffect].rot.y > D3DX_PI)
				{
					s_aEffect[nCntEffect].rot.y -= D3DX_PI * 2;
				}
				if (s_aEffect[nCntEffect].rot.y < -D3DX_PI)
				{
					s_aEffect[nCntEffect].rot.y += D3DX_PI * 2;

				}
			switch (s_aEffect[nCntEffect].nType)
			{
			case EFFECTTYPE_LINE:
				

				SetNorotpos(pVtx,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					0.0f,
					0.0f);

				//�������s�����Ƃ�
				s_aEffect[nCntEffect].fRadeius-=0.1f;
				if (s_aEffect[nCntEffect].fRadeius <= 0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				break;
			case EFFECTTYPE_MP:
			case EFFECTTYPE_MP2:
			case EFFECTTYPE_MP3:
			case EFFECTTYPE_MP4:
			case EFFECTTYPE_MP5:
	

				s_aEffect[nCntEffect].nLife--;
				//���@�w��傫���\������
				if (s_aEffect[nCntEffect].nLife<= s_aEffect[nCntEffect].nMaxLife&& s_aEffect[nCntEffect].nLife >= s_aEffect[nCntEffect].nMaxLife -60)
				{
					s_aEffect[nCntEffect].fRadeius += 1.0f;
				}

				//�Ō�ɏ���������
				if (s_aEffect[nCntEffect].nLife <= 60 && s_aEffect[nCntEffect].nLife >= 40)
				{
					s_aEffect[nCntEffect].fRadeius += 1.5f;
				}
				if (s_aEffect[nCntEffect].nLife <= 40 && s_aEffect[nCntEffect].nLife >= 0)
				{
					s_aEffect[nCntEffect].fRadeius -= 5.0f;
				}
				if (s_aEffect[nCntEffect].fRadeius <= 0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}


				//�A�j���[�V�����e�N�X�`���ݒ�
				if ((s_aEffect[nCntEffect].nCounterAnim % s_aEffect[nCntEffect].speed) == 0)//�����ő��x����
				{
					s_aEffect[nCntEffect].nPatternAnim++;

					//�\�����W���X�V
					Settex(pVtx
						, 1.0f / s_aEffect[nCntEffect].nDivisionX * (s_aEffect[nCntEffect].nPatternAnim % (s_aEffect[nCntEffect].nDivisionX ))
						, 1.0f / s_aEffect[nCntEffect].nDivisionX *(s_aEffect[nCntEffect].nPatternAnim % (s_aEffect[nCntEffect].nDivisionX )) + 1.0f / s_aEffect[nCntEffect].nDivisionX
						, 1.0f / s_aEffect[nCntEffect].nDivisionY * (s_aEffect[nCntEffect].nPatternAnim / (s_aEffect[nCntEffect].nDivisionY))
						, 1.0f / s_aEffect[nCntEffect].nDivisionY * (s_aEffect[nCntEffect].nPatternAnim / ( s_aEffect[nCntEffect].nDivisionY) + 1.0f / s_aEffect[nCntEffect].nDivisionY* s_aEffect[nCntEffect].nDivisionY));
				if (s_aEffect[nCntEffect].nLife <=0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				}
				if (s_aEffect[nCntEffect].nLife <= s_aEffect[nCntEffect].nMaxLife&& s_aEffect[nCntEffect].nLife >= s_aEffect[nCntEffect].nMaxLife - 10)
				{
					s_aEffect[nCntEffect].fRadeius += 1.0f;
				}
				if (s_aEffect[nCntEffect].nLife <= s_aEffect[nCntEffect].nMaxLife&& s_aEffect[nCntEffect].nLife >= s_aEffect[nCntEffect].nMaxLife - 30)
				{//�T�C�Y��+�R�O����
					s_aEffect[nCntEffect].fRadeius += 1.0f;
				}
				//�Ō�ɏ���������
				if (s_aEffect[nCntEffect].nLife <= 60 && s_aEffect[nCntEffect].nLife >= 40)
				{
					s_aEffect[nCntEffect].fRadeius += 1.5f;
				}
				if (s_aEffect[nCntEffect].nLife <= 40 && s_aEffect[nCntEffect].nLife >= 0)
				{
					s_aEffect[nCntEffect].fRadeius -= 5.0f;
				}
				if (s_aEffect[nCntEffect].fRadeius <= 0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				s_aEffect[nCntEffect].nCounterAnim++;
			
				break;
			case EFFECTTYPE_CLOCK:
			case EFFECTTYPE_CLOCK2:
			case EFFECTTYPE_CLOCK3:
			case EFFECTTYPE_CLOCK4:
			case EFFECTTYPE_CLOCK5:
			case EFFECTTYPE_CLOCK6:
			case EFFECTTYPE_CLOCK7:
			case EFFECTTYPE_CLOCK8:
			case EFFECTTYPE_CLOCK9:
			case EFFECTTYPE_CLOCK10:

				s_aEffect[nCntEffect].nLife--;
				if (s_aEffect[nCntEffect].nLife <= 0)
				{
					s_aEffect[nCntEffect].bUse = false;
				}
				//�Ō�ɏ���������
				if (s_aEffect[nCntEffect].nLife <= 60 && s_aEffect[nCntEffect].nLife >= 40)
				{
					s_aEffect[nCntEffect].col.a -= 0.05f;
				}
				if (s_aEffect[nCntEffect].nLife <= 40 && s_aEffect[nCntEffect].nLife >= 0)
				{
					s_aEffect[nCntEffect].col.a -= 0.05f;
				}
				
			default:
				break;

			}
			if (!s_aEffect[nCntEffect].bRot)
			{
				//�ݒ�
				SetNorotpos(pVtx,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					+1.0f,
					+1.0f,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius);
			}
			else
			{
				//�ݒ�
				SetNorotpos(pVtx,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					-s_aEffect[nCntEffect].fRadeius,
					+s_aEffect[nCntEffect].fRadeius,
					+1.0f,
					+1.0f);

			}
			if (s_aEffect[nCntEffect].bCol)
			{
				if (s_aEffect[nCntEffect].col.r == 1.0f)
				{
					s_aEffect[nCntEffect].col.g += 0.02f;    //�OFF0000
				}
				if (s_aEffect[nCntEffect].col.r >= 1.0f)
				{
					s_aEffect[nCntEffect].col.b -= 0.04f;    //�OFF00FF

				}
				if (s_aEffect[nCntEffect].col.g >= 1.0f)
				{
					s_aEffect[nCntEffect].col.r -= 0.02f;    //�OFFFF00
				}

				if (s_aEffect[nCntEffect].col.r <= 0.0f)
				{
					s_aEffect[nCntEffect].col.b += 0.05f;    //�O00FF00
				}

				if (s_aEffect[nCntEffect].col.b >= 1.0f)
				{
					s_aEffect[nCntEffect].col.g -= 0.05f;    //�O00FFFF
				}

				if (s_aEffect[nCntEffect].col.g <= 0.0f)
				{
					s_aEffect[nCntEffect].col.r += 0.05f;    //�O0000FF
				}
				
				
			}
			else
			{
				if (s_aEffect[nCntEffect].col.a >= 0.0f&&s_aEffect[nCntEffect].col.a <= 0.5f)
				{
					s_aEffect[nCntEffect].col.a += 0.005f;
				}
			}
			//���_�J���[�̐ݒ�
			pVtx[0].col = s_aEffect[nCntEffect].col;
			pVtx[1].col = s_aEffect[nCntEffect].col;
			pVtx[2].col = s_aEffect[nCntEffect].col;
			pVtx[3].col = s_aEffect[nCntEffect].col;
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
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
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

			default:
				break;
			}
			if (s_aEffect[nCntEffect].bZbf)
			{	//�ݒ�false�ɂ���Z�N��
				pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);//Z�e�X�g
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			}
			if (!s_aEffect[nCntEffect].bZbf)
			{	//�ݒ�false�ɂ���Z�N��
				pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);//Z�e�X�g
				// �s���]�֐�(��1�����Ƀ��[(y)�s�b�`(x)���[��(z)�����̉�]�s����쐬)
				D3DXMatrixRotationYawPitchRoll(&mtxRot, s_aEffect[nCntEffect].rot.y, s_aEffect[nCntEffect].rot.x, s_aEffect[nCntEffect].rot.z);
				// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
				D3DXMatrixMultiply(&s_aEffect[nCntEffect].mtxWorld, &s_aEffect[nCntEffect].mtxWorld, &mtxRot);
			}
			if (s_aEffect[nCntEffect].bAbf)
			{

				pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);//A�e�X�g
																	 //�f�t�H���g��false�ł�
				pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000000);//�F�����Ă�
																		   //����͏������������I�����܂�
				pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);//���傫��
			}
		
			// �ʒu�𔽉f
			// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
			D3DXMatrixTranslation(&mtxTrans, s_aEffect[nCntEffect].pos.x, s_aEffect[nCntEffect].pos.y, s_aEffect[nCntEffect].pos.z);
			// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
			D3DXMatrixMultiply(&s_aEffect[nCntEffect].mtxWorld, &s_aEffect[nCntEffect].mtxWorld, &mtxTrans);

			//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			
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
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//����񂮐ݒ菉����

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);//Z�e�X�g������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//A�e�X�g������

	//���Z����������
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadeius, int nLife, EFFECTTYPE nType, bool bZbf, bool bAbf, bool bCol,bool bRot)
{
	int nCntEffect;
	VERTEX_3D*pVtx; //���_�ւ̃|�C���^
	s_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (s_aEffect[nCntEffect].bUse == false)
		{

			//�G�t�F�N�g���g�p����ĂȂ��ꍇ
			s_aEffect[nCntEffect].fRadeius = fRadeius;
			s_aEffect[nCntEffect].pos = pos;
			s_aEffect[nCntEffect].bAbf = bAbf;
			s_aEffect[nCntEffect].bZbf = bZbf;
			s_aEffect[nCntEffect].bCol = bCol;
			s_aEffect[nCntEffect].nType = nType;
			s_aEffect[nCntEffect].nCounterAnim = 0;
			s_aEffect[nCntEffect].nPatternAnim = 0;
			s_aEffect[nCntEffect].nMaxLife = nLife;
			s_aEffect[nCntEffect].bRot = bRot;
		
			//�A�j���[�V�����ő吔
			s_aEffect[nCntEffect].nDivisionMAX = s_aEffect[nCntEffect].nDivisionX*s_aEffect[nCntEffect].nDivisionY;

			//�e�N�X�`���ݒ�
			Settex(pVtx, 0.0f, 1.0f / s_aEffect[nCntEffect].nDivisionX, 0.0f, 1.0f / s_aEffect[nCntEffect].nDivisionY);

			if (!s_aEffect[nCntEffect].bRot)
			{
				// ��]���W
				s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
				//�ݒ�
				SetNorotpos(pVtx,
					-fRadeius,
					+fRadeius,
					+1.0f,
					+1.0f,
					-fRadeius,
					+fRadeius);
			}
			else
			{
				s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//�ݒ�
				SetNorotpos(pVtx,
					-fRadeius,
					+fRadeius,
					-fRadeius,
					+fRadeius,
					+1.0f,
					+1.0f);
					
			}
			//���[�u
			s_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//�C�[�W���O
			s_aEffect[nCntEffect].easeInspeed = 0;

			//��������
			s_aEffect[nCntEffect].nLife = nLife;

			//�g�p�`�F�b�N
			s_aEffect[nCntEffect].bUse = true;

			//�J���[
			s_aEffect[nCntEffect].col = col;
			switch (s_aEffect[nCntEffect].nType)
			{
			case EFFECTTYPE_LINE:
				s_aEffect[nCntEffect].nDivisionX = 1;
				s_aEffect[nCntEffect].nDivisionY = 1;
				s_aEffect[nCntEffect].speed = 1;
				break;
			case EFFECTTYPE_CLOCK6:
				s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 3.0f);
			case EFFECTTYPE_CLOCK7:
				s_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 3.1f);
				break;
			default:
				s_aEffect[nCntEffect].nDivisionX = 1;
				s_aEffect[nCntEffect].nDivisionY = 1;
				s_aEffect[nCntEffect].speed = 5;
				break;
			}
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
