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
#include "obstacle_manager.h"
#include "message.h"
#include "player.h"
#include "shield.h"
#include "Score.h"
#include "ranking_ui.h"
#include "domino.h"
#include "sound.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CScore* CGame::m_pScore=nullptr;

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
	//���b�Z�[�W�̕\��
	{
		D3DXVECTOR3 pos(640.0f, 360.0f, 0.0f);
		CMessage::Create(pos, 800.0f, 500.0f);
	}

	{// �w�i
		CObject3D* pObj = CObject3D::Create();

		D3DXVECTOR3 size = D3DXVECTOR3(1800.0f, 0.0f, 1800.0f);

		// �T�C�Y�̐ݒ�
		pObj->SetSize(size);

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LAVEL_TATAMI);
	}

	//���b�V���t�B�[���h�̐���
	//CMeshField::Create(CTexture::LAVEL_TATAMI_NOLINE);

	// ��Q���̐���
	CObstacleManager::Create();	// �v���C���[�̐���
	CPlayer::CreateAll();

	//���̐���
	CShield::CreateAll();

	CDomino::SetCount(0);

	m_pScore = CScore::Create(D3DXVECTOR3(670.0f, 50.0f, 0.0f));
	m_pScore->SetScore(0);

	//�Ȃ̍Đ�
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Game);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
	//�Ȃ̒�~
	CApplication::GetInstance()->GetSound()->Stop();

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
		CDomino::AddCount();
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Update();
		CRankingUI::SetCurrentScore(m_pScore->GetScore());
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CGame::Draw()
{
	m_pScore->Draw();
}
