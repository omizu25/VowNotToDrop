//**************************************************
// 
// result.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "result.h"
#include "input.h"
#include "application.h"
#include "instancing.h"
#include "fade.h"
#include "mode.h"
#include "mesh_field.h"
#include "domino.h"
#include "menu.h"
#include "result.h"
#include "sound.h"

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CResult::CResult()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CResult::Init()
{
	//メッシュフィールドの生成
	CMeshField::Create(CTexture::LAVEL_TATAMI_NOLINE);

	CDomino::CreateAll();

	//曲の再生
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Result);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CResult::Uninit()
{
	//曲の停止
	CApplication::GetInstance()->GetSound()->Stop();

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CResult::Update()
{
	Input();

	CDomino::AddMove();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CResult::Draw()
{
}

//--------------------------------------------------
// 入力
//--------------------------------------------------
void CResult::Input()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_BACK))
	{// Pキーが押された
		// モードの変更
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RANKING);
	}
}
