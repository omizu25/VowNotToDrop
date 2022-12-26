//**************************************************
// 
// domino.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "domino.h"
#include "application.h"
#include "utility.h"
#include "input.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//==================================================
// 静的メンバ変数
//==================================================
float CDomino::m_move = 0.0f;
int CDomino::m_count = 0;

//--------------------------------------------------
// 生成
//--------------------------------------------------
int CDomino::GetCount()
{
	return m_count;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CDomino::SetCount(int score)
{
	m_count = score;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CDomino::AddCount()
{
	m_count++;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CDomino::AddMove()
{
	m_move += -0.1f;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CDomino::CreateAll()
{
	m_move = 0.0f;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, -120.0f);

	for (int i = 0; i < m_count; i++)
	{
		// 生成
		CDomino::Create(pos);

		pos.x += 50.0f;
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CDomino* CDomino::Create(const D3DXVECTOR3& pos)
{
	CDomino* pDomino = new CDomino;

	if (pDomino == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pDomino->Init();

	// 位置の設定
	pDomino->SetPos(pos);

	return pDomino;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CDomino::CDomino()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CDomino::~CDomino()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CDomino::Init()
{
	// 初期化
	CModel::Init();

	// 向きの設定
	CModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f ,0.0f));

	// 使用するモデルの設定
	CModel::SetLabel(CFileXManager::LABEL_Hagoita);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CDomino::Uninit()
{
	// 終了
	CModel::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CDomino::Update()
{
	// 位置の取得
	D3DXVECTOR3 pos = CModel::GetPos();

	pos.x += m_move;

	// 位置の設定
	CModel::SetPos(pos);

	if (pos.x <= -1000.0f)
	{// 範囲外に出た
		CObject::SetRelease();
	}

	if (pos.x <= 10.0f + (m_move * -1.0f))
	{
		// 位置の取得
		D3DXVECTOR3 rot = CModel::GetRot();

		rot.x += (m_move * -1.0f) * 0.01f;

		// 角度の正規化
		NormalizeAngle(&rot.x);

		if (rot.x >= D3DX_PI * 0.35f)
		{
			rot.x = D3DX_PI * 0.35f;
		}

		// 位置の設定
		CModel::SetRot(rot);
	}

	// 更新
	CModel::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CDomino::Draw()
{
	// 描画
	CModel::Draw();
}
