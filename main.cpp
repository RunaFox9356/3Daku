//=================================================
//	�A�N�V�����Q�[������
//
//  Auther�F hamadaryuuga
//=================================================
#include<stdio.h>
#include"main.h"
#include "input.h"
#include"block.h"
#include"camera.h"
#include"light.h"
#include"model.h"
#include"shadow.h"
#include"wall.h"
#include"kitune.h"
#include"file.h"
#include"mesh.h"
#include"cylinder.h"
#include"paticle.h"
#include"ken.h"
#include"effect.h"
#include"Prayer.h"

#define MAX_NAME (10)

//�O���[�o���ϐ�(�K�{)
LPDIRECT3D9 g_pD3D = NULL; //Direct3d�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; //Direct3d�f�o�C�X�ւ̂ۂ���
MODE g_mode = MODE_TITLE;//���[�h
LPD3DXFONT g_pFont = NULL; //�t�H���g�̃|�C���^
int g_nCountFPS;
int g_nUseWireFrame;
bool bLine;//line���[�h
//===================
//���C���֐�
//===================
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hlnstacePrev, LPSTR ipCmdLine, int nCmdShow)
{
	HWND hWnd;	//Window�n���h�����ʎq
	MSG msg;	//���b�Z�[�W���i�[����ϐ�
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),	//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,			//�E�C���h�E�̃X�^�C��
		WindowProc,			//Window�v���V�[�W��  
		0,					//�[���ɂ���
		0,					//�[���ɂ���
		hinstance,			//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),//�N���C�A���g�̗̈�w�i�F
		NULL,						//���j���[�o�[
		CLASS_NAME,					//Window�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)//�t�@�C���A�C�R��
	};

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(
		0,//�g��Windows�X�^�C��
		CLASS_NAME,//Window�N���X�̖��O
		WINDOW_NAME,//Window�̖��O
		WS_OVERLAPPEDWINDOW,//Window�X�^�C��
		CW_USEDEFAULT,//Window�̍���X���W
		CW_USEDEFAULT,//Window����Y���W
		(rect.right - rect.left),//Window��
		(rect.bottom - rect.top),//Window����
		NULL,//�eWindow�̃n���h��
		NULL,//���j���[�n���h���܂��͌qWindowID
		hinstance,//�C���X�^���X�n���h��
		NULL);//Window�쐬�f�[�^

	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExedastTime;//�Ō�X�V����
	DWORD dwFrameCount; //�t���[���J�E���g
	DWORD dwFPSLastTime; //��������FPS

	if (FAILED(Init(hinstance, hWnd, TRUE)))//������false�ɂ���Ƒ��ʂɂȂ�
	{//�����������s�����ꍇ

		return -1;
	}

	//Windowm�\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//����\�̐ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExedastTime = timeGetTime();

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯂Ƃ����烁�b�Z�[�W��[�Ղ𔲂���
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();//���ݎ������擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
			 //FPS�v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExedastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExedastTime = dwCurrentTime;//�����J�n�̎���[���ݎ���]��ۑ�
											  //�X�V����
				Update();

				//�`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	//�I������
	Uninit();


	//���@�\��߂�
	timeEndPeriod(1);
	//Window�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//========================
//�E�B���h�E�v���V�[�W��
//========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;//�Ԃ�l���i�[

	switch (uMsg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN: //	�L�[�̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE: //�G�X�P�[�v�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I���̃R�}���h", MB_YESNO | MB_TOPMOST);
			//��������NULL�ɂ���ƃ��b�Z�[�WBOX�A�N�e�B�u�E�B���h�E�ɂȂ�Ȃ�
			//��������hWnd�ɂ���Ƃ��̃E�B���h�E���e(�I�[�i�[)�ɂȂ�A
			//���̃��b�Z�[�WBOX���������Ȃ�����ق��̏������ł��Ȃ�
			if (nID == IDYES)
			{//Window��j�󂷂�(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
				break;
			}
			break;

		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//===================
//�f�o�C�X�擾
//===================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//===================
//����������
//===================
HRESULT Init(HINSTANCE hlnstance, HWND hWnd, BOOL bWindow)//TRUE�F�E�C���h�E/FALSE:�t���X�N���[��
{
	D3DDISPLAYMODE d3ddm;//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp; //�v���[���e�[�V�����p�����[�^

								 //Direct3d�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	if (FAILED(lnitKeyboard(hlnstance, hWnd)))
	{
		return E_FAIL;
	}

	//�|���S���̏���������
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//�Q�[����ʃT�C�Y
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�Q�[����ʃT�C�Y
	d3dpp.BackBufferFormat = d3ddm.Format; //�o�b�N�΂��ӂ��̌`����
	d3dpp.BackBufferCount = 1;//�o�b�N�΂��ӂ��̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; //���Ԃ�΂��ӂ��̐؂�ւ��i�f���M���̓����j
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; //�f�v�X�΂��ӂ��Ƃ��ĂP�U��it���g��
	d3dpp.Windowed = bWindow;//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���()
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���()
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))

			{
				return E_FAIL;
			}
		}
	}

	//���W�_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//�A���t�@�u�����h�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//�A���t�@�u�����h�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//�A���t�@�u�����h�ݒ�
	
	
	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);//�������̊g��
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);//�傫���̏k��
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);


	//�e�N�X�`���X�e�[�W�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//�|���S���ƃe�N�X�`���̐F��������
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	
	if (FAILED(lnitKeyboard(hlnstance, hWnd)))
	{

		return E_FAIL;
	}
	if (FAILED(lnitJoypad()))
	{

		return E_FAIL;
	}

	//�f�o�b�N�\���p�̃t�H���g
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "UD�f�W�^�����ȏ��� NP-B", &g_pFont);
	
	bLine = false;
	
	//���C�g
	InitLighe();

	//�J����
	InitCamera();

	//�~��
	InitCylinder();

	//�p�[�e�B�N��������
	InitParticle();
	
	//ken�p�[�e�B�N��������
	InitKen();

	//�e
	InitShadow();

	//���f��
	InitPrayer();

	//���f��
	InitModel();
	//���b�V��
	InitMesh();

	//�G�t�F�N�g
	InitEffect();

	//Initblock();

	//��
	InitWall();
	
	//�r���{�[�h
	InitKitune();

	//�t�@�C��
	LoodSetFile();

	//�Z�b�g
	set();

	/*InitSound(hWnd);

	InitFade(g_mode);

	ResetRanking();
*/

	return S_OK;
}

//===================
//�I������
//===================
void Uninit(void)
{
	//�W���C�p�b�g
	UninitJoypad();

	UninitCylinder();
	//���f��
	UninitPrayer();

	//���b�V��
	UninitMesh();

	//Uninitblock();
	
	//�p�[�e�B�N���j��
	UninitParticle();

	//���C�g
	UninitLighe();
	
	//�J����
	UninitCamera();
	
	UninitEffect();
	
	//ken�p�[�e�B�N��
	UninitKen();
	//���f��
	UninitModel();
	//�e
	UninitShadow();

	//��
	UninitWall();

	//�r���{�[�h
	UninitKitune();
	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	////�^�C�g��
	//UninitTitle();

	////�`���[�g���A��
	//UninitTutorial();

	////�Q�[��
	//UninitGame();

	////���U���g
	//UninitResult();

	////�Q�[���I�[�o�[
	//UninitGameover();

	////�t�F�[�h
	//UninitFade();

	////�T�E���h�I������
	//UninitSound();

	////�����L���O�I������
	//UninitRanking();

	//�f�o�b�N�̕\���t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
}

//===================
//�X�V����
//===================
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�J����
	UpdateCylinder();
	//���f��
	UpdatePrayer();

	UpdateLighe();

	//�p�[�e�B�N���X�V����
	UpdateParticle();

	//ken�p�[�e�B�N��
	UpdateKen();

	//���b�V��
	UpdateMesh();

	//Uninitblock();
	//���f��
	UpdateModel();
	//���C�g
	UpdateLighe();

	//�J����
	UpdateCamera();

	UpdateEffect();

	//�e
	UpdateShadow();

	//��
	UpdateWall();

	//�r���{�[�h
	UpdateKitune();

	//�W���C�p�b�g
	UpdateJoypad();

	if (GetKeyboardTrigger(DIK_P))
	{
		bLine = !bLine;
	}
	if (bLine)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//senn
	}
	if (bLine == false)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);//senn
	}

	//switch (g_mode)
	//{
	//case MODE_TITLE:
	//	UpdateTitle();
	//	break;
	//case MODE_TUTORIAL:
	//	UpdateTutorial();
	//	break;
	//case MODE_GAME:
	//	UpdateGame();
	//	break;
	//case MODE_RESULT:
	//	UpdateResult();
	//	break;
	//case MODE_GAMEOVER:
	//	UpdateGameover();
	//	break;
	//case MODE_RANKING:
	//	UpdateRanking();
	//	break;
	//}
	////�t�F�[�h
	//UpdateFade();

}

//===================
//�`�揈��
//===================
void Draw(void)
{
	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//���������Ƃ�
		//Drawblock();

		//��
		DrawCylinder();
		
		//���b�V��
		DrawMesh();
		
		//ken�p�[�e�B�N��
		DrawKen();

		//���f��
		DrawPrayer();

		//�V���h�[
		DrawShadow();

		//���f��
		DrawModel();
		//���߂�
		SetCamera();

		//��
		DrawWall();
		//�p�[�e�B�N���`�揈��
		DrawParticle();

		//�G�t�F�N�g
		DrawEffect();

		//�r���{�[�h
		DrawKitune();
		/*switch (g_mode)
		{*/
		//case MODE_TITLE:
		//	DrawTitle();
		//	break;
		//case MODE_TUTORIAL:
		//	DrawTutorial();
		//	break;
		//case MODE_GAME:
		//	DrawGame();
		//	break;
		//case MODE_RESULT:
		//	DrawResult();
		//	break;
		//case MODE_GAMEOVER:
		//	DrawGameover();
		//	break;
		//case MODE_RANKING:
		//	DrawRanking();
		//	break;
		//}
		////�t�F�[�h�\��
		//DrawFade();

#ifdef _DEBUG
		//debug�̕\��
		DrawDebug();
#endif // DEBUG
		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//�Z�b�g����
void SetMode(MODE mode)
{

	/*switch (g_mode)
	{*/
	/*case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_GAMEOVER:
		UninitGameover();
		break;
	case MODE_RANKING:
		UninitRanking();
		break;
	}
	ResetRanking();
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	case MODE_GAMEOVER:
		InitGameover();
		break;
	case MODE_RANKING:
		InitRanking();
		int pScore;
		pScore = GetScore();
		SetRanking(pScore);
		break;*/
	//}

	//g_mode = mode;
}

MODE GetMode(void)//�擾
{
	return g_mode;
}

void DrawDebug(void)
{
	CAMERA *pCamera = GetCamera();
	PRAYER *pPrayer = GetPrayer();
	MESH *pMesh = GetMesh();
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[MAX_NAME][256];
	int nNanba = GetnNanba();
	//������ɑ��
	wsprintf(&aStr[0][0], "FPS%d", g_nCountFPS);

	//������ɑ��
	sprintf(&aStr[1][0], "�J�������_->(%.3f|%.3f|%.3f)", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);

	//������ɑ��
	sprintf(&aStr[2][0], "�J���������_->(%.3f|%.3f|%.3f)", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);

	//������ɑ��
	sprintf(&aStr[3][0], "�J������]->(%.3f|%.3f|%.3f)", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);

	//������ɑ��
	sprintf(&aStr[4][0], "���f���ړ�->(%.3f|%.3f|%.3f)", pPrayer->pos.x, pPrayer->pos.y, pPrayer->pos.z);
	
	//������ɑ��
	sprintf(&aStr[5][0], "���f����]->(%.3f|%.3f|%.3f)", pPrayer->rot.x, pPrayer->rot.y, pPrayer->rot.z);

	sprintf(&aStr[6][0], "�������Ă郂�f���̔ԍ��i%d�j�������L�����؂�ւ�V�L�[", nNanba);
	
	sprintf(&aStr[7][0],"���b�V���̃o�b�t�@%d,���b�V���̃C���f�b�N�X%d �T�C�Y�w%d�T�C�Y�x%d", pMesh->Vtx, pMesh->Index,pMesh->xsiz, pMesh->zsiz);
	
	if (bLine)
	{
		sprintf(&aStr[8][0], "�����[�h[ON]");
	}
	if (bLine == false)
	{
		sprintf(&aStr[8][0], "�����[�h[OFF]");
	}
	wsprintf(&aStr[9][0], "�����������\n���_���ړ�:A.D ���_�c�ړ�:W.S\n�㏸L�V�t�g���~R�V�t�g\n��]��:Q.E�c:Z.C\n�J�����ړ�:�J�[�\���L�[\n���f���̉��ړ�:J.L���f���̏c�ړ�:I.K\n�����[�h:P\n�ύD���ł���H");
	for (int i = 0; i < MAX_NAME; i++)
	{
		rect = { 0,i*30,SCREEN_WIDTH,SCREEN_HEIGHT };
		//�e�L�X�g�̕`��
		g_pFont->DrawText(NULL, &aStr[i][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(200, 179, 0, 255));
	}	
}

void Settex(VERTEX_3D *pVtx, float left, float right, float top, float down)
{
	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(left, top);
	pVtx[1].tex = D3DXVECTOR2(right, top);
	pVtx[2].tex = D3DXVECTOR2(left, down);
	pVtx[3].tex = D3DXVECTOR2(right, down);

}
void Normal(float standard)
{
	//���K��
	if (standard > D3DX_PI)
	{
		standard -= D3DX_PI * 2;
	}
	if (standard < -D3DX_PI)
	{
		standard += D3DX_PI * 2;
	}

}
void SetNorotpos(VERTEX_3D *pVtx, float XUP, float XDW, float YUP, float YDW,float ZUP, float ZDW)
{
	pVtx[0].pos = D3DXVECTOR3(XDW, YUP,ZUP );
	pVtx[1].pos = D3DXVECTOR3(XUP, YUP,ZUP);
	pVtx[2].pos = D3DXVECTOR3(XDW, YDW,ZDW );
	pVtx[3].pos = D3DXVECTOR3(XUP, YDW,ZDW );
}
//--------------
//�Z�b�g�܂Ƃ�
//--------------
void set(void)
{

	//SetKitune(D3DXVECTOR3(50.0f, 0.0f, 100.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);//�ꏊ.��].�F
											 //��O 
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�ꏊ.��]

										   //����
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -100.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�ꏊ.��]
										   //�E
	SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�ꏊ.��]

										   //��
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�ꏊ.��].�F

										   //����
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�ꏊ.��]

	//									   //��O
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, -100.0f),
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�ꏊ.��]

										   //�E
	SetWall(D3DXVECTOR3(100.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�ꏊ.��]

										   //��
	SetWall(D3DXVECTOR3(-100.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�ꏊ.��].�F
}

