//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
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
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CGame::CGame()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CGame::Init()
{
	// ����
	CObstacle::Create();

	//���b�V���t�B�[���h�̐���
	CMeshField::Create(CTexture::LAVEL_TATAMI_NOLINE);

	m_pScore = CScore::Create(D3DXVECTOR3(640.0f, 310.0f, 0.0f));
	m_pScore->SetScore(0);
}

//--------------------------------------------------
// �I��
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
// �X�V
//--------------------------------------------------
void CGame::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_PAUSE))
	{// P�L�[�������ꂽ
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
// �`��
//--------------------------------------------------
void CGame::Draw()
{
	m_pScore->Draw();
}
