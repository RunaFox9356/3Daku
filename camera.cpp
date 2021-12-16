//========================
//カメラ設定
//Auther：hamadaryuuga
//========================
#include"camera.h"
#include"input.h"
#include"prayer.h"

#define Spede (1.0f)
#define rotSpede (0.01f)
//スタティック変数
static CAMERA s_aCamera;

//----------------------------
//初期化処理
//----------------------------
void InitCamera(void)
{
	s_aCamera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//視点　注視点　上方向　設定
	s_aCamera.posV = D3DXVECTOR3(0.0f, 75.0f, -145.0f);
	s_aCamera.posR = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
	s_aCamera.vecU  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	s_aCamera.directionR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_aCamera.directionV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_aCamera.bBool = false;
	s_aCamera.fDistance = sqrtf((s_aCamera.posR.x - s_aCamera.posV.x) * 
								(s_aCamera.posR.x - s_aCamera.posV.x) +
								(s_aCamera.posR.z - s_aCamera.posV.z) * 
								( s_aCamera.posR.z - s_aCamera.posV.z));

	s_aCamera.fDistance = sqrtf((s_aCamera.posR.y - s_aCamera.posV.y)*
								(s_aCamera.posR.y - s_aCamera.posV.y) +
								(s_aCamera.fDistance*s_aCamera.fDistance));

	s_aCamera.rot.x = atan2f((s_aCamera.posR.z - s_aCamera.posV.z),
							(s_aCamera.posR.y - s_aCamera.posV.y));

}

//----------------------------
//終了処理
//----------------------------
void UninitCamera(void)
{


}

//----------------------------
//更新処理
//----------------------------
void UpdateCamera(void)
{
	if (GetKeyboardTrigger(DIK_U))
	{

		if (s_aCamera.bBool == false)
		{
			s_aCamera.bBool = true;
			s_aCamera.posV = D3DXVECTOR3(0.0f, 75.0f, -145.0f);
			s_aCamera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			s_aCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			s_aCamera.directionR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			s_aCamera.directionV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			s_aCamera.bBool = false;
		}
		
	}
	if (s_aCamera.bBool == false)
	{
		if (GetKeyboardPress(DIK_A) ||
			GetKeyboardPress(DIK_D) ||
			GetKeyboardPress(DIK_S) ||
			GetKeyboardPress(DIK_W))
		{
			if (GetKeyboardPress(DIK_A))
			{//A押した回る視点左
				s_aCamera.rot.y -= rotSpede;
			}
			if (GetKeyboardPress(DIK_D))
			{//D押した回る視点右
				s_aCamera.rot.y += rotSpede;
			}
			if (GetKeyboardPress(DIK_S))
			{//s押した回る視点下
				s_aCamera.rot.x += rotSpede;
			}
			if (GetKeyboardPress(DIK_W))
			{//押した回る視点上
				s_aCamera.rot.x -= rotSpede;
			}

			//視点動かす
			s_aCamera.posR.x = s_aCamera.posV.x + sinf(s_aCamera.rot.x) * sinf(s_aCamera.rot.y) * s_aCamera.fDistance;
			s_aCamera.posR.y = s_aCamera.posV.y + cosf(s_aCamera.rot.x) * s_aCamera.fDistance;
			s_aCamera.posR.z = s_aCamera.posV.z + sinf(s_aCamera.rot.x) * cosf(s_aCamera.rot.y) * s_aCamera.fDistance;

		}
		if (GetKeyboardPress(DIK_Q) ||
			GetKeyboardPress(DIK_E) ||
			GetKeyboardPress(DIK_Z) ||
			GetKeyboardPress(DIK_C))
		{
			if (GetKeyboardPress(DIK_Q))
			{//A押した回る注視点左
				s_aCamera.rot.y -= rotSpede;
			}

			if (GetKeyboardPress(DIK_E))
			{//D押した回る注視点右
				s_aCamera.rot.y += rotSpede;
			}

			if (GetKeyboardPress(DIK_Z))
			{//s押した回る注視点上
				s_aCamera.rot.x -= rotSpede;
			}

			if (GetKeyboardPress(DIK_C))
			{//押した回る注視点下
				s_aCamera.rot.x += rotSpede;
			}

			//注視点動かす
			s_aCamera.posV.z = s_aCamera.posR.z - sinf(s_aCamera.rot.x) * cosf(s_aCamera.rot.y) * s_aCamera.fDistance;
			s_aCamera.posV.x = s_aCamera.posR.x - sinf(s_aCamera.rot.x) * sinf(s_aCamera.rot.y) * s_aCamera.fDistance;
			s_aCamera.posV.y = s_aCamera.posR.y - cosf(s_aCamera.rot.x) * s_aCamera.fDistance;

		}

		if (GetKeyboardPress(DIK_DOWN) ||
			GetKeyboardPress(DIK_UP) ||
			GetKeyboardPress(DIK_LEFT) ||
			GetKeyboardPress(DIK_RIGHT) ||
			GetKeyboardPress(DIK_LSHIFT) ||
			GetKeyboardPress(DIK_RSHIFT))
		{
			if (GetKeyboardPress(DIK_DOWN))
			{//うしろ移動
				s_aCamera.posR.x -= sinf(s_aCamera.rot.y)*Spede;
				s_aCamera.posR.z -= cosf(s_aCamera.rot.y)*Spede;
			}
			if (GetKeyboardPress(DIK_UP))
			{//前移動
				s_aCamera.posR.x += sinf(s_aCamera.rot.y)*Spede;
				s_aCamera.posR.z += cosf(s_aCamera.rot.y)*Spede;
			}
			if (GetKeyboardPress(DIK_LEFT))
			{//左移動
				s_aCamera.posR.x -= sinf(D3DX_PI *0.5f + s_aCamera.rot.y)*Spede;
				s_aCamera.posR.z -= cosf(D3DX_PI *0.5f + s_aCamera.rot.y)*Spede;
			}
			if (GetKeyboardPress(DIK_RIGHT))
			{//右移動
				s_aCamera.posR.x += sinf(D3DX_PI *0.5f + s_aCamera.rot.y)*Spede;
				s_aCamera.posR.z += cosf(D3DX_PI *0.5f + s_aCamera.rot.y)*Spede;
			}
			if (GetKeyboardPress(DIK_LSHIFT))
			{//左シフト浮く
				s_aCamera.posR.y += sinf(D3DX_PI *0.5f + s_aCamera.rot.x)*Spede;

			}
			if (GetKeyboardPress(DIK_RSHIFT))
			{//右シフト沈む
				s_aCamera.posR.y -= sinf(D3DX_PI *0.5f + s_aCamera.rot.x)*Spede;
			}
			//座標の更新
			s_aCamera.posV.x = s_aCamera.posR.x - sinf(s_aCamera.rot.x) * sinf(s_aCamera.rot.y) * s_aCamera.fDistance;
			s_aCamera.posV.y = s_aCamera.posR.y - cosf(s_aCamera.rot.x) * s_aCamera.fDistance;
			s_aCamera.posV.z = s_aCamera.posR.z - sinf(s_aCamera.rot.x) * cosf(s_aCamera.rot.y) * s_aCamera.fDistance;
		}

		if (GetKeyboardTrigger(DIK_RETURN))
		{//エンターリセット
			InitCamera();
		}
	}
	else
	{
		PRAYER *pPrayer = GetPrayer();

		s_aCamera.posRDest.x = pPrayer->pos.x + sinf(pPrayer->rot.y-D3DX_PI) *10.0f;         //目的の値
		//s_aCamera.posRDest.y = pPrayer->pos.y + sin(pPrayer->rot.y) *s_aCamera.fDistance;         //目的の値
		s_aCamera.posRDest.z = pPrayer->pos.z + cosf(pPrayer->rot.y - D3DX_PI) *10.0f;
											 
		s_aCamera.posVDest.x = pPrayer->pos.x - sinf(s_aCamera.rot.y)*s_aCamera.fDistance;          //目的の値
		s_aCamera.posVDest.z = pPrayer->pos.z - cosf(s_aCamera.rot.y)*s_aCamera.fDistance;

		s_aCamera.posR.x += (s_aCamera.posRDest.x - s_aCamera.posR.x) * 0.1f;	
		//s_aCamera.posR.y += (s_aCamera.posRDest.y - s_aCamera.posR.y) * 0.1f;
		s_aCamera.posR.z += (s_aCamera.posRDest.z - s_aCamera.posR.z) * 0.1f;
												 						  
		s_aCamera.posV.x += (s_aCamera.posVDest.x - s_aCamera.posV.x) * 0.1f;
		//s_aCamera.pos.y += (s_aCamera.posRDest.y - s_aCamera.posR.y) * 0.1f;
		s_aCamera.posV.z += (s_aCamera.posVDest.z - s_aCamera.posV.z) * 0.1f;
	}
	

	//正規化
	if (s_aCamera.rot.y > D3DX_PI)
	{
		s_aCamera.rot.y -= D3DX_PI*2;
	}
	if (s_aCamera.rot.y < -D3DX_PI)
	{
		s_aCamera.rot.y += D3DX_PI*2;
	}

	//正規化
	if (s_aCamera.rot.x > D3DX_PI )
	{				  
		s_aCamera.rot.x -= D3DX_PI*2;
	}				  
	if (s_aCamera.rot.x < -D3DX_PI)
	{				  
		s_aCamera.rot.x += D3DX_PI*2;
	}

}

//----------------------------
//描画処理
//----------------------------
void SetCamera(void)
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();//デバイスのポインタ

	//ビューマトリックスを初期化
	D3DXMatrixIdentity(&s_aCamera.MtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&s_aCamera.MtxView,
		&s_aCamera.posV,
		&s_aCamera.posR,
		&s_aCamera.vecU);

	//適用
	pDevice->SetTransform(D3DTS_VIEW, &s_aCamera.MtxView);


	//プロジェクションマトリックスを初期化
	D3DXMatrixIdentity(&s_aCamera.MtxProje);

	//プロジェクションマトリックス作成
	D3DXMatrixPerspectiveFovLH(&s_aCamera.MtxProje,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//適用
	pDevice->SetTransform(D3DTS_PROJECTION, &s_aCamera.MtxProje);
}

//----------------------------
//ゲット処理
//----------------------------
CAMERA *GetCamera(void)
{
	return &s_aCamera;
}