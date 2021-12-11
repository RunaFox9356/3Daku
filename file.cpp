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

//=====================================
// �}�N����`
//=====================================
#define LOOD_FILE_NAME_000		"model.txt"
#define LOOD_FILE_NAME_001		"model2.txt"
//=====================================
// �O���[�o���ϐ�
//=====================================
static D3DXVECTOR3		g_modelpos;
static char				g_modelFile[128];
static char				g_aString[128];

//---------------------------------------------------------------------------
// �t�@�C���ǂݍ��ݏ���
//---------------------------------------------------------------------------
void LoodSetFile(void)
{
	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	char aFile[128] = FILE_3D_SYSTEM;
	strcat(aFile, LOOD_FILE_NAME_000);//�����@aFile��-�����ɓ����

	//�t�@�C�����J��
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		fscanf(pFile, "%s", &g_aString);

		if (strcmp(&g_aString[0], "SCRIPT") == 0)
		{// �����񂪈�v�����ꍇ
			while (1)
			{// ������̏������Ɠǂݍ���
				g_aString[0] = {};
				fscanf(pFile, "%s", &g_aString[0]);
			
				if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
				{// �����񂪈�v�����ꍇ
					fscanf(pFile, "%s", &g_modelFile);
				}
				else if (strcmp(&g_aString[0], "MODELSET") == 0)
				{// �����񂪈�v�����ꍇ
					while (1)
					{
						// ������̏������Ɠǂݍ���
						g_aString[0] = {};
						fscanf(pFile, "%s", &g_aString[0]);

						if (strcmp(&g_aString[0], "POS") == 0)
						{// �����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &g_modelpos.x);
							fscanf(pFile, "%f", &g_modelpos.y);
							fscanf(pFile, "%f", &g_modelpos.z);
						}
						if (strcmp(&g_aString[0], "END_MODELSET") == 0)
						{// �����񂪈�v�����ꍇ
						 // ���f���̐ݒu
							SetModel(g_modelpos, g_modelFile);
						

							break;
						}
					}
				}
				else if (strcmp(&g_aString[0], "END_SCRIPT") == 0)
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



	char aFile2[128] = FILE_3D_SYSTEM;
	strcat(aFile2, LOOD_FILE_NAME_001);//�����@aFile��-�����ɓ����

									  //�t�@�C�����J��
	pFile = fopen(aFile2, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		fscanf(pFile, "%s", &g_aString);

		if (strcmp(&g_aString[0], "SCRIPT") == 0)
		{// �����񂪈�v�����ꍇ
			while (1)
			{// ������̏������Ɠǂݍ���
				g_aString[0] = {};
				fscanf(pFile, "%s", &g_aString[0]);

				if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
				{// �����񂪈�v�����ꍇ
					fscanf(pFile, "%s", &g_modelFile);
				}
				else if (strcmp(&g_aString[0], "MODELSET") == 0)
				{// �����񂪈�v�����ꍇ
					while (1)
					{
						// ������̏������Ɠǂݍ���
						g_aString[0] = {};
						fscanf(pFile, "%s", &g_aString[0]);

						if (strcmp(&g_aString[0], "POS") == 0)
						{// �����񂪈�v�����ꍇ
							fscanf(pFile, "%f", &g_modelpos.x);
							fscanf(pFile, "%f", &g_modelpos.y);
							fscanf(pFile, "%f", &g_modelpos.z);
						}
						if (strcmp(&g_aString[0], "END_MODELSET") == 0)
						{// �����񂪈�v�����ꍇ
						 // ���f���̐ݒu
							SetModel(g_modelpos, g_modelFile);
							
							break;
						}
					}
				}
				else if (strcmp(&g_aString[0], "END_SCRIPT") == 0)
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

//---------------------------------------------------------------------------
// �t�@�C���X�V����
//---------------------------------------------------------------------------
void OutputSetFile(void)
{
}