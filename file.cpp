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

//=====================================
// マクロ定義
//=====================================
#define LOOD_FILE_NAME_000		"model.txt"
#define LOOD_FILE_NAME_001		"model2.txt"
//=====================================
// グローバル変数
//=====================================
static D3DXVECTOR3		g_modelpos;
static char				g_modelFile[128];
static char				g_aString[128];

//---------------------------------------------------------------------------
// ファイル読み込み処理
//---------------------------------------------------------------------------
void LoodSetFile(void)
{
	// ファイルポインタの宣言
	FILE * pFile;

	char aFile[128] = FILE_3D_SYSTEM;
	strcat(aFile, LOOD_FILE_NAME_000);//合成　aFile＜-こいつに入れる

	//ファイルを開く
	pFile = fopen(aFile, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		fscanf(pFile, "%s", &g_aString);

		if (strcmp(&g_aString[0], "SCRIPT") == 0)
		{// 文字列が一致した場合
			while (1)
			{// 文字列の初期化と読み込み
				g_aString[0] = {};
				fscanf(pFile, "%s", &g_aString[0]);
			
				if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
				{// 文字列が一致した場合
					fscanf(pFile, "%s", &g_modelFile);
				}
				else if (strcmp(&g_aString[0], "MODELSET") == 0)
				{// 文字列が一致した場合
					while (1)
					{
						// 文字列の初期化と読み込み
						g_aString[0] = {};
						fscanf(pFile, "%s", &g_aString[0]);

						if (strcmp(&g_aString[0], "POS") == 0)
						{// 文字列が一致した場合
							fscanf(pFile, "%f", &g_modelpos.x);
							fscanf(pFile, "%f", &g_modelpos.y);
							fscanf(pFile, "%f", &g_modelpos.z);
						}
						if (strcmp(&g_aString[0], "END_MODELSET") == 0)
						{// 文字列が一致した場合
						 // モデルの設置
							SetModel(g_modelpos, g_modelFile);
						

							break;
						}
					}
				}
				else if (strcmp(&g_aString[0], "END_SCRIPT") == 0)
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



	char aFile2[128] = FILE_3D_SYSTEM;
	strcat(aFile2, LOOD_FILE_NAME_001);//合成　aFile＜-こいつに入れる

									  //ファイルを開く
	pFile = fopen(aFile2, "r");

	if (pFile != NULL)
	{//ファイルが開いた場合
		fscanf(pFile, "%s", &g_aString);

		if (strcmp(&g_aString[0], "SCRIPT") == 0)
		{// 文字列が一致した場合
			while (1)
			{// 文字列の初期化と読み込み
				g_aString[0] = {};
				fscanf(pFile, "%s", &g_aString[0]);

				if (strcmp(&g_aString[0], "MODEL_FILENAME") == 0)
				{// 文字列が一致した場合
					fscanf(pFile, "%s", &g_modelFile);
				}
				else if (strcmp(&g_aString[0], "MODELSET") == 0)
				{// 文字列が一致した場合
					while (1)
					{
						// 文字列の初期化と読み込み
						g_aString[0] = {};
						fscanf(pFile, "%s", &g_aString[0]);

						if (strcmp(&g_aString[0], "POS") == 0)
						{// 文字列が一致した場合
							fscanf(pFile, "%f", &g_modelpos.x);
							fscanf(pFile, "%f", &g_modelpos.y);
							fscanf(pFile, "%f", &g_modelpos.z);
						}
						if (strcmp(&g_aString[0], "END_MODELSET") == 0)
						{// 文字列が一致した場合
						 // モデルの設置
							SetModel(g_modelpos, g_modelFile);
							
							break;
						}
					}
				}
				else if (strcmp(&g_aString[0], "END_SCRIPT") == 0)
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

//---------------------------------------------------------------------------
// ファイル更新処理
//---------------------------------------------------------------------------
void OutputSetFile(void)
{
}