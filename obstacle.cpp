//**************************************************
// 
// obstacle.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "obstacle.h"
#include "application.h"
#include "utility.h"
#include "player.h"
#include "input.h"

//==================================================
// 定義
//==================================================
namespace
{
const CFileXManager::ELabel MODEL_PATH = CFileXManager::LABEL_NeedleBall;	// ファイルパス
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	CObstacle* pObstacle = new CObstacle;

	if (pObstacle == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pObstacle->Init();

	// 位置の設定
	pObstacle->SetPos(pos);

	// 移動量の設定
	pObstacle->SetMove(move);

	return pObstacle;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CObstacle::CObstacle() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObstacle::~CObstacle()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CObstacle::Init()
{
	m_move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	// 初期化
	CModel::Init();

	// 使用するモデルの設定
	CModel::SetLabel(MODEL_PATH);

	// クォータニオンの設定
	CModel::SetIsQuaternion(true);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CObstacle::Uninit()
{
	// 終了
	CModel::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CObstacle::Update()
{
	// 位置の取得
	D3DXVECTOR3 pos = CModel::GetPos();

	pos += m_move;

	// 位置の設定
	CModel::SetPos(pos);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(KEY_LEFT))
	{// 左
		Shield(D3DXVECTOR3(-50.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(KEY_RIGHT))
	{// 右
		Shield(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(KEY_DOWN))
	{// 下
		Shield(D3DXVECTOR3(0.0f, 0.0f, -50.0f));
	}

	if (!InRange(&pos, D3DXVECTOR3(10.0f, 0.0f, 10.0f)))
	{// 範囲内に入った
		CPlayer::AddKill(m_move);
		CObject::SetRelease();
	}

	if (InRange(&pos, D3DXVECTOR3(550.0f, 0.0f, 550.0f)))
	{// 範囲外に出た
		CObject::SetRelease();
	}

	// 更新
	CModel::Update();

	// クォータニオンの設定
	CModel::SetQuaternion(m_move);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CObstacle::Draw()
{
	// 描画
	CModel::Draw();
}

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CObstacle::SetMove(const D3DXVECTOR3& move)
{
	m_move = move;
}

//--------------------------------------------------
// 移動量の取得
//--------------------------------------------------
const D3DXVECTOR3& CObstacle::GetMove() const
{
	return m_move;
}

//--------------------------------------------------
// シールド
//--------------------------------------------------
void CObstacle::Shield(const D3DXVECTOR3& pos)
{
	if (CollisionCircle(CModel::GetPos(), 10.0f, pos, 10.0f))
	{// 当たった
		m_move = m_move * -5.0f;
		m_move.y = 10.0f;
	}
}
