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
CGame::CGame() :
	m_time(0)
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
	m_time = -1;

	//���b�Z�[�W�̕\��
	{
		D3DXVECTOR3 pos(640.0f, 250.0f, 0.0f);
		CMessage::Create(pos, 1200.0f, 300.0f);
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

	//�񐔃J�E���g(����)
	CObject2D* pCount = CObject2D::Create();
	pCount->SetPos(D3DXVECTOR3(1000.0f, 60.0f, 0.0f));
	pCount->SetSize(D3DXVECTOR3(550.0f, 100.0f, 0.0f));
	pCount->SetTexture(CTexture::LAVEL_Count);

	//�X�R�A
	m_pScore = CScore::Create(pCount->GetPos() + D3DXVECTOR3(150.0f, 0.0f, 0.0f));
	m_pScore->SetScore(0);

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	{//�������(�A�C�R��)
		CObject2D* pIcon = CObject2D::Create();

		//�ʒu��ݒ�
		pIcon->SetPos(D3DXVECTOR3(270.0f, 480.0f, 0.0f));

		//�T�C�Y��ݒ�
		pIcon->SetSize(D3DXVECTOR3(550.0f, 150.0f, 0.0f));

		//�e�N�X�`���̐ݒ�
		pIcon->SetTexture(CTexture::LABEL_Explanation_Icon);

		pos = pIcon->GetPos();	//�ʒu���擾
	}

	{//�������(����)
		CObject2D* pTutorial = CObject2D::Create();

		//�ʒu��ݒ�
		pTutorial->SetPos(pos + D3DXVECTOR3(0.0f, 150.0f, 0.0f));

		//�T�C�Y��ݒ�
		pTutorial->SetSize(D3DXVECTOR3(450.0f, 125.0f, 0.0f));

		//�e�N�X�`���̐ݒ�
		pTutorial->SetTexture(CTexture::LABEL_Explanation);
	}

	//�Ȃ̍Đ�
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Game);}

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

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CGame::Update()
{
	if (m_time >= 0)
	{
		m_time++;

		if (m_time >= 60)
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

//--------------------------------------------------
// �Q�[���I��
//--------------------------------------------------
void CGame::EndGame()
{
	m_time = 0;
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int CGame::GetTime()
{
	return m_time;
}