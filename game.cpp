//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "game.h"
#include "input.h"
#include "effect.h"
#include "application.h"
#include "fade.h"
#include "mode.h"
#include "object3D.h"
#include "obstacle.h"
#include "mesh_field.h"
#include "Score.h"
#include "Ranking.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CGame::CGame()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CGame::Init()
{
	// 生成
	CObstacle::Create();

	//メッシュフィールドの生成
	CMeshField::Create(CTexture::LAVEL_TATAMI_NOLINE);

	m_pScore = CScore::Create(D3DXVECTOR3(640.0f, 310.0f, 0.0f));
	m_pScore->SetScore(0);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_PAUSE))
	{// Pキーが押された
		CEffect::Explosion(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	
	if (pInput->Trigger(KEY_BACK))
	{
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RESULT);
	}

	if (pInput->Trigger(KEY_SHOT))
	{
		if (m_pScore != nullptr)
		{
			m_pScore->Addpos();
		}
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Update();
		CRanking::SetCurrentScore(m_pScore->GetScore());
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
	m_pScore->Draw();
}
