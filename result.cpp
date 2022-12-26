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
#include "menu.h"
#include "application.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"
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
CResult::CResult() :
	m_pMenu(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CResult::~CResult()
{
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CResult::Init()
{
	{// 背景
		CObject3D* pObj = CObject3D::Create();

		D3DXVECTOR3 size = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f);

		// サイズの設定
		pObj->SetSize(size);

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_NONE);
	}

	{// タイトルロゴ
		CObject2D* pObj = CObject2D::Create();

		// 位置の設定
		pObj->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, 250.0f, 0.0f));

		// サイズの設定
		pObj->SetSize(D3DXVECTOR3(600.0f, 300.0f, 0.0f));

		// テクスチャの設定
		pObj->SetTexture(CTexture::LABEL_Result);
	}

	{// メニュー
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.75f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(450.0f, 100.0f, 0.0f);

		// 生成
		m_pMenu = CMenu::Create(pos, size, 1, 50.0f);

		// 枠の設定
		m_pMenu->SetFrame(pos, D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, 200.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

		// カーソルの設定
		m_pMenu->SetCursor(D3DXVECTOR3(100.0f, 50.0f, 0.0f), 20.0f);

		// テクスチャの設定
		m_pMenu->SetTexture(0, CTexture::LABEL_PressEnter);
	}
	m_pRanking=CRanking::Create();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CResult::Uninit()
{
	if (m_pMenu != nullptr)
	{// nullチェック
		m_pMenu = nullptr;
	}
	if (m_pRanking != nullptr)
	{
		m_pRanking->Uninit();
		m_pRanking = nullptr;
	}

	// 解放
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CResult::Update()
{
	// 入力
	Input();

	m_pRanking->Update();
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
	int select = m_pMenu->Select();

	if (select == -1)
	{// 入力されていない
		return;
	}

	// モードの変更
	CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_TITLE);
}
