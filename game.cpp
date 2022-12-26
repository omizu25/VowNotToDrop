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
	//メッセージの表示
	{
		D3DXVECTOR3 pos(640.0f, 360.0f, 0.0f);
		CMessage::Create(pos, 800.0f, 500.0f);
	}

	//メッシュフィールドの生成
	CMeshField::Create(CTexture::LAVEL_TATAMI_NOLINE);

	// 障害物の生成
	CObstacleManager::Create();	// プレイヤーの生成
	CPlayer::CreateAll();}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_PAUSE))
	{// Pキーが押された
		CPlayer::AddKill();
		//CEffect::Explosion(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	
	if (pInput->Trigger(KEY_BACK))
	{
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RESULT);
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
}
