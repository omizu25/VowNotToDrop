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
#include "obstacle_manager.h"
#include "message.h"
#include "player.h"
#include "shield.h"
#include "Score.h"
#include "ranking_ui.h"
#include "domino.h"
#include "sound.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//==================================================
// 静的メンバ変数
//==================================================
CScore* CGame::m_pScore=nullptr;

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
	//メッセージの表示
	{
		D3DXVECTOR3 pos(640.0f, 360.0f, 0.0f);
		CMessage::Create(pos, 800.0f, 500.0f);
	}

	{// 背景
		CObject3D* pObj = CObject3D::Create();

		D3DXVECTOR3 size = D3DXVECTOR3(1800.0f, 0.0f, 1800.0f);

		// サイズの設定
		pObj->SetSize(size);

		// テクスチャの設定
		pObj->SetTexture(CTexture::LAVEL_TATAMI);
	}

	//メッシュフィールドの生成
	//CMeshField::Create(CTexture::LAVEL_TATAMI_NOLINE);

	// 障害物の生成
	CObstacleManager::Create();	// プレイヤーの生成

	//盾の生成
	CShield::CreateAll();

	CPlayer::CreateAll();

	CDomino::SetCount(0);

	//回数カウント(文言)
	CObject2D* pCount = CObject2D::Create();
	pCount->SetPos(D3DXVECTOR3(300.0f, 650.0f, 0.0f));
	pCount->SetSize(D3DXVECTOR3(550.0f, 100.0f, 0.0f));
	pCount->SetTexture(CTexture::LAVEL_Count);

	//スコア
	m_pScore = CScore::Create(pCount->GetPos() + D3DXVECTOR3(150.0f, 0.0f, 0.0f));
	m_pScore->SetScore(0);

	//操作説明(文言)
	CObject2D* pTutorial =  CObject2D::Create();
	pTutorial->SetPos(D3DXVECTOR3(1050.0f, 550.0f, 0.0f));
	pTutorial->SetSize(D3DXVECTOR3(400.0f, 100.0f, 0.0f));
	pTutorial->SetTexture(CTexture::LABEL_Explanation);

	//操作説明(アイコン)
	CObject2D* pIcon = CObject2D::Create();
	pIcon->SetPos(pTutorial->GetPos() + D3DXVECTOR3(0.0f, 100.0f, 0.0f));
	pIcon->SetSize(D3DXVECTOR3(400.0f, 100.0f, 0.0f));
	pIcon->SetTexture(CTexture::LABEL_Explanation_Icon);

	//曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Game);}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	//曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		m_pScore = nullptr;
	}

	// 解放
	Release();
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
		if (CDomino::GetCount() == 0)
		{
			CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_RANKING);
		}
		else
		{
			CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_RESULT);
		}
	}

	if (pInput->Trigger(KEY_SHOT))
	{
		if (m_pScore != nullptr)
		{
			m_pScore->Addpos();
		}
		CDomino::AddCount();
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Update();
		CRankingUI::SetCurrentScore(m_pScore->GetScore());
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
	m_pScore->Draw();
}
