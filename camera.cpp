//**************************************************
// 
// camera.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "camera.h"
#include "application.h"
#include "game.h"
#include "utility.h"

//==================================================
// 定義
//==================================================
namespace
{
const D3DXVECTOR3 STD_POS_V = D3DXVECTOR3(0.0f, 500.0f, -350.0f);	// 基準の視点の位置
const float MAX_NEAR = 10.0f;		// ニアの最大値
const float MAX_FAR = 2500.0f;		// ファーの最大値
const float FIELD_OF_VIEW = D3DXToRadian(45.0f);	// 視野角

// アスペクト比
const float ASPECT_RATIO = (float)CApplication::SCREEN_WIDTH / (float)CApplication::SCREEN_HEIGHT;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CCamera::CCamera() :
	m_posV(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posR(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	memset(m_mtxProj, 0, sizeof(m_mtxProj));
	memset(m_mtxView, 0, sizeof(m_mtxView));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CCamera::~CCamera()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CCamera::Init()
{
	m_posV = STD_POS_V;
	m_posR = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 固定
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CCamera::Uninit()
{	
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CCamera::Update()
{
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CCamera::Set()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// ビューの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューの作成
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションの初期化
	D3DXMatrixIdentity(&m_mtxProj);

	// プロジェクションの作成
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProj,
		FIELD_OF_VIEW,
		ASPECT_RATIO,
		MAX_NEAR,
		MAX_FAR);

	// プロジェクションの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void CCamera::SetPos(const D3DXVECTOR3& pos)
{
	m_posV = pos;
}

//--------------------------------------------------
// 位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CCamera::GetPos() const
{
	return m_posV;
}

//--------------------------------------------------
// プロジェクションの取得
//--------------------------------------------------
const D3DXMATRIX& CCamera::GetProj() const
{
	return m_mtxProj;
}

//--------------------------------------------------
// ビューの取得
//--------------------------------------------------
const D3DXMATRIX& CCamera::GetView() const
{
	return m_mtxView;
}
