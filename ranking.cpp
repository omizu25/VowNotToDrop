//**************************************************
// 
// ranking.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "ranking.h"
#include "menu.h"
#include "application.h"
#include "instancing.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"
#include "ranking_ui.h"
#include "sound.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CRanking::CRanking() :
	m_pMenu(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CRanking::~CRanking()
{
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CRanking::Init()
{
	{// �^�C�g�����S
		CObject2D* pObj = CObject2D::Create();

		// �ʒu�̐ݒ�
		pObj->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT*0.5f, 0.0f));

		// �T�C�Y�̐ݒ�
		pObj->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LABEL_RankingBG002);
	}

	{// ���j���[
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.8f, (float)CApplication::SCREEN_HEIGHT * 0.3f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(450.0f, 100.0f, 0.0f);

		// ����
		m_pMenu = CMenu::Create(pos, size, 2, 50.0f);

		// �J�[�\���̐ݒ�
		m_pMenu->SetCursor(D3DXVECTOR3(100.0f, 50.0f, 0.0f), 20.0f);

		// �e�N�X�`���̐ݒ�
		m_pMenu->SetTexture(0, CTexture::LABEL_Restart);
		m_pMenu->SetTexture(1, CTexture::LABEL_ReturnToTitle);
	}
	m_pRanking= CRankingUI::Create();

	//�Ȃ̍Đ�
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Result);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CRanking::Uninit()
{
	//�Ȃ̒�~
	CApplication::GetInstance()->GetSound()->Stop();

	if (m_pMenu != nullptr)
	{// null�`�F�b�N
		m_pMenu = nullptr;
	}
	if (m_pRanking != nullptr)
	{
		m_pRanking->Uninit();
		m_pRanking = nullptr;
	}

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CRanking::Update()
{
	// ����
	Input();

	m_pRanking->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CRanking::Draw()
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CRanking::Input()
{
	int select = m_pMenu->Select();

	if (select == -1)
	{// ���͂���Ă��Ȃ�
		return;
	}

	if (select == 0)
	{
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_GAME);
	}
	else
	{
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_TITLE);
	}
	
}
