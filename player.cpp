//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "player.h"
#include "application.h"
#include "utility.h"

//==================================================
// 定義
//==================================================
namespace
{
const float POS_Y[CPlayer::MAX_PLAYER] =
{
	30.0f,
	20.0f,
	10.0f,
};
}
//==================================================
// 静的メンバ変数
//==================================================
CPlayer* CPlayer::m_pPlayer[CPlayer::MAX_PLAYER] = {};
int CPlayer::m_killCount = 0;

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CPlayer::CreateAll()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		m_pPlayer[i] = CPlayer::Create(i, POS_Y[i]);

		if (i == 0)
		{
			m_pPlayer[i]->SetLabel(CFileXManager::LABEL_Daruma_Head);
		}
		else
		{
			m_pPlayer[i]->SetLabel(CFileXManager::LABEL_Daruma_Body);
		}
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CPlayer* CPlayer::Create(int index, float posDest)
{
	CPlayer* pPlayer = new CPlayer;

	if (pPlayer == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pPlayer->Init();

	pPlayer->m_index = index;

	// 目的の位置の設定
	pPlayer->m_posDest = posDest;

	// 位置の設定
	pPlayer->SetPos(D3DXVECTOR3(0.0f, posDest, 0.0f));

	return pPlayer;
}

//--------------------------------------------------
// 残機の減算
//--------------------------------------------------
void CPlayer::AddKill(const D3DXVECTOR3& move)
{
	if (m_killCount >= MAX_PLAYER)
	{
		return;
	}

	m_killCount++;
	m_pPlayer[MAX_PLAYER - m_killCount]->SetMove(move);
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CPlayer::CPlayer() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_index(0),
	m_posDest(0.0f)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CPlayer::Init()
{
	m_move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_posDest = 0.0f;
	m_index = 0;

	// 初期化
	CModel::Init();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CPlayer::Uninit()
{
	// 終了
	CModel::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CPlayer::Update()
{
	int index = m_index + m_killCount;

	if (index >= MAX_PLAYER)
	{
		// 向きの取得
		D3DXVECTOR3 rot = CModel::GetRot();

		rot.x += -D3DX_PI * 0.25f;
		rot.y += -D3DX_PI * 0.25f;

		// 向きの設定
		CModel::SetRot(rot);

		// 位置の取得
		D3DXVECTOR3 pos = CModel::GetPos();

		pos += m_move;

		// 位置の設定
		CModel::SetPos(pos);
		
		if (InRange(&pos, D3DXVECTOR3(550.0f, 0.0f, 550.0f)))
		{// 範囲外に出た
			CObject::SetRelease();
		}
	}

	m_posDest = POS_Y[index];

	// 位置の取得
	D3DXVECTOR3 pos = CModel::GetPos();

	Homing(&pos, pos, D3DXVECTOR3(0.0f, m_posDest, 0.0f), 1.0f);

	// 位置の設定
	CModel::SetPos(pos);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CPlayer::Draw()
{
	// 描画
	CModel::Draw();
}

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CPlayer::SetMove(const D3DXVECTOR3& move)
{
	m_move = move;
	m_move *= 5.0f;
	m_move.y = 10.0f;
}

//--------------------------------------------------
// 移動量の取得
//--------------------------------------------------
const D3DXVECTOR3& CPlayer::GetMove() const
{
	return m_move;
}
