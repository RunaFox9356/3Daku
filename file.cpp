//=====================================
// �t�@�C���ǂݍ��ݏ���
// Auther�Fhamada ryuuga
//=====================================

//=====================================
// �C���N���[�h
//=====================================
#include<stdio.h>
#include "main.h"
#include "file.h"
#include"file.h"
#include"model.h"
#include"Prayer.h"
//=====================================
// �v���g�^�C�v�錾
//=====================================
void	LoodKeySetFile(FILE*pFile);
//=====================================
// �}�N����`
//=====================================
#define LOOD_FILE_NAME_000		"Prayer.txt"
#define LOOD_FILE_NAME_001		"model.txt"

//=====================================
// �O���[�o���ϐ�
//=====================================

static char				s_aString[256];//
static ModelData		s_ModelData;
static int	nSetModel = 0;
static int nSetKey = 0;


//---------------------------------------------------------------------------
// �t�@�C���ǂݍ��ݏ���
//---------------------------------------------------------------------------
void LoodSetFile(void)
{
	char s_modelFile[128];
	int	 s_nIndex = 0;
	// �t�@�C���|�C���^�̐錾
	FILE* pFile;

	char aFile[128] = FILE_3D_SYSTEM;
	strcat(aFile, LOOD_FILE_NAME_000);//�����@aFile��-�����ɓ����

	//�t�@�C�����J��
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		fscanf(pFile, "%s", &s_aString);
		while (strncmp(&s_aString[0], "SCRIPT", 6) != 0)
		{
			s_aString[0] = {};
			fscanf(pFile, "%s", &s_aString[0]);
		}

		while (strncmp(&s_aString[0], "END_SCRIPT", 10) != 0)
		{// ������̏������Ɠǂݍ���// ������̏������Ɠǂݍ���
			//s_aString[0] = {};
			fscanf(pFile, "%s", &s_aString[0]);

			if (strcmp(&s_aString[0], "MODEL_FILENAME") == 0)
			{// �����񂪈�v�����ꍇ
				fscanf(pFile, "%s", &s_modelFile);
			}
			else if (strcmp(&s_aString[0], "MODELSET") == 0)
			{// �����񂪈�v�����ꍇ
				 D3DXVECTOR3	s_modelpos = D3DXVECTOR3(0.0f,0.0f,0.0f);
				 D3DXVECTOR3	s_modelrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				while (1)
				{
					// ������̏������Ɠǂݍ���
					s_aString[0] = {};

					fscanf(pFile, "%s", &s_aString[0]);

					if (strncmp(&s_aString[0], "#", 1) == 0)
					{
						fscanf(pFile, "%s", &s_aString[0]);
						continue;
					}
					if (strcmp(&s_aString[0], "POS") == 0)
					{// �����񂪈�v�����ꍇ

						fscanf(pFile, "%s", &s_aString[0]);
						fscanf(pFile, "%f", &s_modelpos.x);
						fscanf(pFile, "%f", &s_modelpos.y);
						fscanf(pFile, "%f", &s_modelpos.z);
					}
					if (strcmp(&s_aString[0], "ROT") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%s", &s_aString[0]);
						fscanf(pFile, "%f", &s_modelrot.x);
						fscanf(pFile, "%f", &s_modelrot.y);
						fscanf(pFile, "%f", &s_modelrot.z);
					}
					if (strcmp(&s_aString[0], "PARENT") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%d", &s_nIndex);

					}
					if (strcmp(&s_aString[0], "LOOP") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%d", &s_ModelData.LOOP);

					}
					if (strcmp(&s_aString[0], "NUM_KEY") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%d", &s_ModelData.NUM_KEY);

					}
					if (strcmp(&s_aString[0], "KEYSET") == 0)
					{// �����񂪈�v�����ꍇ
						LoodKeySetFile(pFile);
					}
					if (strcmp(&s_aString[0], "END_MODELSET") == 0)
					{// �����񂪈�v�����ꍇ
					 // ���f���̐ݒu
						SetPrayer(s_modelpos, s_modelrot, s_modelFile, s_nIndex);
						break;
					}
					else if (strcmp(&s_aString[0], "END_SCRIPT") == 0)
					{// �����񂪈�v�����ꍇ
						break;
					}
				}
			}
			else if (strcmp(&s_aString[0], "END_SCRIPT") == 0)
			{// �����񂪈�v�����ꍇ
				break;
			}

		}
	}

	//�t�@�C�������
	fclose(pFile);

	char aFile2[128] = FILE_3D_SYSTEM;
	strcat(aFile2, LOOD_FILE_NAME_001);//�����@aFile��-�����ɓ����

									   //�t�@�C�����J��
	pFile = fopen(aFile2, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		fscanf(pFile, "%s", &s_aString);

		if (strcmp(&s_aString[0], "SCRIPT") == 0)
		{// �����񂪈�v�����ꍇ
			while (1)
			{// ������̏������Ɠǂݍ���
				s_aString[0] = {};
				fscanf(pFile, "%s", &s_aString[0]);

				if (strcmp(&s_aString[0], "MODEL_FILENAME") == 0)
				{// �����񂪈�v�����ꍇ
					fscanf(pFile, "%s", &s_modelFile);
				}
				else if (strcmp(&s_aString[0], "MODELSET") == 0)
				{// �����񂪈�v�����ꍇ4
					D3DXVECTOR3	s_modelpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					while (1)
					{
						// ������̏������Ɠǂݍ���
						s_aString[0] = {};
						fscanf(pFile, "%s", &s_aString[0]);
						if (strcmp(&s_aString[0], "POS") == 0)
						{// �����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &s_modelpos.x);
							fscanf(pFile, "%f", &s_modelpos.y);
							fscanf(pFile, "%f", &s_modelpos.z);
						}
						if (strcmp(&s_aString[0], "END_MODELSET") == 0)
						{// �����񂪈�v�����ꍇ
						 // ���f���̐ݒu
							SetModel(s_modelpos, s_modelFile);
							break;
						}
					}
				}
				else if (strcmp(&s_aString[0], "END_SCRIPT") == 0)
				{// �����񂪈�v�����ꍇ
					break;
				}
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		printf("\n * * * �t�@�C�����J���܂��� * * * \n");
	}

}

void LoodKeySetFile(FILE * pFile)
{


	if (strcmp(&s_aString[0], "KEYSET") == 0)
	{// �����񂪈�v�����ꍇ
		while (1)
		{	
			// ������̏������Ɠǂݍ���
			s_aString[0] = {};

			fscanf(pFile, "%s", &s_aString[0]);
			if (strncmp(&s_aString[0], "#", 1) == 0)
			{
				fgets(&s_aString[0], sizeof(s_aString), pFile);
				continue;
			}

			if (strcmp(&s_aString[0], "FRAME") == 0)
			{// �����񂪈�v�����ꍇ
				fscanf(pFile, "%d", &s_ModelData.KeySet[nSetModel].KeyFrame);
			}
			if (strcmp(&s_aString[0], "KEY") == 0)
			{
				while (1)
				{// ������̏������Ɠǂݍ���
					s_aString[0] = {};
					fscanf(pFile, "%s", &s_aString[0]);
					if (strncmp(&s_aString[0], "#", 1) == 0)
					{
						fgets(&s_aString[0], sizeof(s_aString), pFile);
						continue;
					}
					if (strcmp(&s_aString[0], "POS") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%s", &s_aString[0]);
						fscanf(pFile, "%f", &s_ModelData.KeySet[nSetModel].key[nSetKey].pos.x);
						fscanf(pFile, "%f", &s_ModelData.KeySet[nSetModel].key[nSetKey].pos.y);
						fscanf(pFile, "%f", &s_ModelData.KeySet[nSetModel].key[nSetKey].pos.z);
					}
					if (strcmp(&s_aString[0], "ROT") == 0)
					{// �����񂪈�v�����ꍇ
						fscanf(pFile, "%s", &s_aString[0]);
						fscanf(pFile, "%f", &s_ModelData.KeySet[nSetModel].key[nSetKey].rot.x);
						fscanf(pFile, "%f", &s_ModelData.KeySet[nSetModel].key[nSetKey].rot.y);
						fscanf(pFile, "%f", &s_ModelData.KeySet[nSetModel].key[nSetKey].rot.z);
					}
					if (strcmp(&s_aString[0], "END_KEY") == 0)
					{
						nSetKey++;
						break;
					}
				}
			}
			if (strcmp(&s_aString[0], "END_KEYSET") == 0)
			{// �����񂪈�v�����ꍇ
				nSetModel++;
				nSetKey = 0;
				break;
			}
		}
	}
	


}
//---------------------------------------------------------------------------
// �t�@�C���X�V����
//---------------------------------------------------------------------------
void OutputSetFile(void)
{


}