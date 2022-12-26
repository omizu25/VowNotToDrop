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
#include "Score.h"
#include "domino.h"
#include "shield.h"

//==================================================
// 定義
//==================================================
namespace
{
const CFileXManager::ELabel MODEL_PATH = CFileXManager::LABEL_WING;	// ファイルパス
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& rot)
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

	// 向きの設定
	pObstacle->SetRot(rot);

	return pObstacle;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CObstacle::CObstacle() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_collision(false)
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
	m_collision = false;

	// 初期化
	CModel::Init();

	// 使用するモデルの設定
	CModel::SetLabel(MODEL_PATH);
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

	// 向きの取得
	D3DXVECTOR3 rot = CModel::GetRot();

	if (m_collision)
	{// 当たった
		rot.x += -D3DX_PI * 0.25f;
		rot.y += -D3DX_PI * 0.25f;

		// 角度の正規化
		NormalizeAngle(&rot.x);
		NormalizeAngle(&rot.y);

	}
	else
	{
		rot.z += -D3DX_PI * 0.1f;

		// 角度の正規化
		NormalizeAngle(&rot.z);
	}

	// 向きの設定
	CModel::SetRot(rot);

	if (!m_collision)
	{// 当たってない
		CInput* pInput = CInput::GetKey();

		int nPopNumber;
		for (int i = 0; i < 3; i++)
		{
			nPopNumber = CShield::GetNumPop(i);

			switch (nPopNumber)
			{
			case 0:
				if (pInput->Press(KEY_LEFT))
				{// 左
					Shield(D3DXVECTOR3(-150.0f, 0.0f, 100.0f));
				}
				break;

			case 1:
				if (pInput->Press(KEY_RIGHT) && nPopNumber == 1)
				{// 右
					Shield(D3DXVECTOR3(150.0f, 0.0f, 100.0f));
				}
				break;

			case 2:
				if (pInput->Press(KEY_DOWN) && nPopNumber == 2)
				{// 下
					Shield(D3DXVECTOR3(0.0f, 0.0f, -50.0f));
				}
				break;

			default:
				break;
			}
		}

		if (!InRange(&pos, D3DXVECTOR3(20.0f, 0.0f, 110.0f)))
		{// プレイヤーに当たった
			CPlayer::AddKill(m_move);
			CObject::SetRelease();
		}
	}

	if (InRange(&pos, D3DXVECTOR3(650.0f, 0.0f, 650.0f)))
	{// 範囲外に出た
		CObject::SetRelease();
	}

	// 更新
	CModel::Update();
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
	if (CollisionCircle(CModel::GetPos(), 0.0f, pos, 50.0f))
	{// 門松に当たった
		m_move = m_move * -5.0f;
		m_move.y = 10.0f;
		m_collision = true;
		CScore::AddFrag();
		CDomino::AddCount();
	}
}
