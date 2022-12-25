//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "title.h"
#include "menu.h"
#include "application.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTitle::CTitle() :
	m_pMenu(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTitle::~CTitle()
{
	assert(m_pMenu == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTitle::Init()
{
	{// �w�i
		CObject3D* pObj = CObject3D::Create();

		D3DXVECTOR3 size = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f);

		// �T�C�Y�̐ݒ�
		pObj->SetSize(size);

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LABEL_NONE);
	}

	{// �^�C�g�����S
		CObject2D* pObj = CObject2D::Create();

		// �ʒu�̐ݒ�
		pObj->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, 250.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		pObj->SetSize(D3DXVECTOR3(600.0f, 300.0f, 0.0f));

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LABEL_TitleLogo);
	}

	{// ���j���[
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.75f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(450.0f, 100.0f, 0.0f);

		// ����
		m_pMenu = CMenu::Create(pos, size, 1, 50.0f);

		// �g�̐ݒ�
		m_pMenu->SetFrame(pos, D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, 200.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

		// �J�[�\���̐ݒ�
		m_pMenu->SetCursor(D3DXVECTOR3(100.0f, 50.0f, 0.0f), 20.0f);

		// �e�N�X�`���̐ݒ�
		m_pMenu->SetTexture(0, CTexture::LABEL_PressEnter);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTitle::Uninit()
{
	if (m_pMenu != nullptr)
	{// null�`�F�b�N
		m_pMenu = nullptr;
	}

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTitle::Update()
{
	// ����
	Input();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CTitle::Draw()
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CTitle::Input()
{
	int select = m_pMenu->Select();

	if (select == -1)
	{// ���͂���Ă��Ȃ�
		return;
	}

	// ���[�h�̕ύX
	CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_GAME);
}
