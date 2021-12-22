//=====================================
// ファイル読み込み処理
// Auther：hamada ryuuga
//=====================================

//=====================================
// インクルード
//=====================================
#include<stdio.h>
#include "main.h"
#include "file.h"
#include"file.h"
#include"model.h"
#include"Prayer.h"
//=====================================
// プロトタイプ宣言
//=====================================
void	LoodKeySetFile(FILE*pFile);
//=====================================
// マクロ定義
//=====================================
#define LOOD_FILE_NAME_000		"Prayer.txt"
#define LOOD_FILE_NAME_001		"model.txt"

//=====================================
// グローバル変数
//=====================================

static char				s_aString[256];//
static ModelData		s_ModelData;
static int	nSetModel = 0;
static int nSetKey = 0;


//---------------------------------------------------------------------------
// ファイル読み込み処理
//---------------------------------------------------------------------------
void LoodSetFile(void)
{
	char s_modelFile[128];
	int	 s_nIndex = 0;
	// ファイルポインタの宣言
	FILE* pFile;

	char aFile[128] = FILE_3D_SYSTEM;
	strcat(aFile, LOOD_FILE_NAME_000);//合成　aFile＜-こいつに入れる

	//ファイルを開く
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		fscanf(pFile, "%s", &s_aString);
		while (strncmp(&s_aString[0], "SCRIPT", 6) != 0)
		{
			s_aString[0] = {};
			fscanf(pFile, "%s", &s_aString[0]);
		}

		while (strncmp(&s_aString[0], "END_SCRIPT", 10) != 0)
		{// 文字列の初期化と読み込み// 文字列の初期化と読み込み
			//s_aString[0] = {};
			fscanf(pFile, "%s", &s_aString[0]);

			if (strcmp(&s_aString[0], "MODEL_FILENAME") == 0)
			{// 文字列が一致した場合
				fscanf(pFile, "%s", &s_modelFile);
			}
			else if (strcmp(&s_aString[0], "MODELSET") == 0)
			{// 文字列が一致した場合
				 D3DXVECTOR3	s_modelpos = D3DXVECTOR3(0.0f,0.0f,0.0f);
				 D3DXVECTOR3	s_modelrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				while (1)
				{
					// 文字列の初期化と読み込み
					s_aString[0] = {};

					fscanf(pFile, "%s", &s_aString[0]);

					if (strncmp(&s_aString[0], "#", 1) == 0)
					{
						fscanf(pFile, "%s", &s_aString[0]);
						continue;
					}
					if (strcmp(&s_aString[0], "POS") == 0)
					{// 文字列が一致した場合

						fscanf(pFile, "%s", &s_aString[0]);
						fscanf(pFile, "%f", &s_modelpos.x);
						fscanf(pFile, "%f", &s_modelpos.y);
						fscanf(pFile, "%f", &s_modelpos.z);
					}
					if (strcmp(&s_aString[0], "ROT") == 0)
					{// 文字列が一致した場合
						fscanf(pFile, "%s", &s_aString[0]);
						fscanf(pFile, "%f", &s_modelrot.x);
						fscanf(pFile, "%f", &s_modelrot.y);
						fscanf(pFile, "%f", &s_modelrot.z);
					}
					if (strcmp(&s_aString[0], "PARENT") == 0)
					{// 文字列が一致した場合
						fscanf(pFile, "%d", &s_nIndex);

					}
					if (strcmp(&s_aString[0], "LOOP") == 0)
					{// 文字列が一致した場合
						fscanf(pFile, "%d", &s_ModelData.LOOP);

					}
					if (strcmp(&s_aString[0], "NUM_KEY") == 0)
					{// 文字列が一致した場合
						fscanf(pFile, "%d", &s_ModelData.NUM_KEY);

					}
					if (strcmp(&s_aString[0], "KEYSET") == 0)
					{// 文字列が一致した場合
						LoodKeySetFile(pFile);
					}
					if (strcmp(&s_aString[0], "END_MODELSET") == 0)
					{// 文字列が一致した場合
					 // モデルの設置
						SetPrayer(s_modelpos, s_modelrot, s_modelFile, s_nIndex);
						break;
					}
					else if (strcmp(&s_aString[0], "END_SCRIPT") == 0)
					{// 文字列が一致した場合
						break;
					}
				}
			}
			else if (strcmp(&s_aString[0], "END_SCRIPT") == 0)
			{// 文字列が一致した場合
				break;
			}

		}
	}

	//ファイルを閉じる
	fclose(pFile);

	char aFile2[128] = FILE_3D_SYSTEM;
	strcat(aFile2, LOOD_FILE_NAME_001);//合成　aFile＜-こいつに入れる

									   //ファイルを開く
	pFile = fopen(aFile2, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		fscanf(pFile, "%s", &s_aString);

		if (strcmp(&s_aString[0], "SCRIPT") == 0)
		{// 文字列が一致した場合
			while (1)
			{// 文字列の初期化と読み込み
				s_aString[0] = {};
				fscanf(pFile, "%s", &s_aString[0]);

				if (strcmp(&s_aString[0], "MODEL_FILENAME") == 0)
				{// 文字列が一致した場合
					fscanf(pFile, "%s", &s_modelFile);
				}
				else if (strcmp(&s_aString[0], "MODELSET") == 0)
				{// 文字列が一致した場合4
					D3DXVECTOR3	s_modelpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					while (1)
					{
						// 文字列の初期化と読み込み
						s_aString[0] = {};
						fscanf(pFile, "%s", &s_aString[0]);
						if (strcmp(&s_aString[0], "POS") == 0)
						{// 文字列が一致した場合
							fscanf(pFile, "%f", &s_modelpos.x);
							fscanf(pFile, "%f", &s_modelpos.y);
							fscanf(pFile, "%f", &s_modelpos.z);
						}
						if (strcmp(&s_aString[0], "END_MODELSET") == 0)
						{// 文字列が一致した場合
						 // モデルの設置
							SetModel(s_modelpos, s_modelFile);
							break;
						}
					}
				}
				else if (strcmp(&s_aString[0], "END_SCRIPT") == 0)
				{// 文字列が一致した場合
					break;
				}
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けない場合
		printf("\n * * * ファイルが開けません * * * \n");
	}

}

void LoodKeySetFile(FILE * pFile)
{


	if (strcmp(&s_aString[0], "KEYSET") == 0)
	{// 文字列が一致した場合
		while (1)
		{	
			// 文字列の初期化と読み込み
			s_aString[0] = {};

			fscanf(pFile, "%s", &s_aString[0]);
			if (strncmp(&s_aString[0], "#", 1) == 0)
			{
				fgets(&s_aString[0], sizeof(s_aString), pFile);
				continue;
			}

			if (strcmp(&s_aString[0], "FRAME") == 0)
			{// 文字列が一致した場合
				fscanf(pFile, "%d", &s_ModelData.KeySet[nSetModel].KeyFrame);
			}
			if (strcmp(&s_aString[0], "KEY") == 0)
			{
				while (1)
				{// 文字列の初期化と読み込み
					s_aString[0] = {};
					fscanf(pFile, "%s", &s_aString[0]);
					if (strncmp(&s_aString[0], "#", 1) == 0)
					{
						fgets(&s_aString[0], sizeof(s_aString), pFile);
						continue;
					}
					if (strcmp(&s_aString[0], "POS") == 0)
					{// 文字列が一致した場合
						fscanf(pFile, "%s", &s_aString[0]);
						fscanf(pFile, "%f", &s_ModelData.KeySet[nSetModel].key[nSetKey].pos.x);
						fscanf(pFile, "%f", &s_ModelData.KeySet[nSetModel].key[nSetKey].pos.y);
						fscanf(pFile, "%f", &s_ModelData.KeySet[nSetModel].key[nSetKey].pos.z);
					}
					if (strcmp(&s_aString[0], "ROT") == 0)
					{// 文字列が一致した場合
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
			{// 文字列が一致した場合
				nSetModel++;
				nSetKey = 0;
				break;
			}
		}
	}
	


}
//---------------------------------------------------------------------------
// ファイル更新処理
//---------------------------------------------------------------------------
void OutputSetFile(void)
{


}