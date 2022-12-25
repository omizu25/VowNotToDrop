//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "object.h"
#include "texture.h"
#include "camera.h"
#include "mode.h"
#include "fade.h"
#include "instancing.h"

//==================================================
// ��`
//==================================================
namespace
{
const bool FULL_SCREEN = false;	// �t���X�N���[���ɂ��邩�ǂ���
const CMode::EMode START_MODE = CMode::MODE_TITLE;	// �ŏ��̃��[�h
}

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CApplication* CApplication::m_pApplication = nullptr;

//--------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------
CApplication* CApplication::GetInstance()
{
	if (m_pApplication == nullptr)
	{// null�`�F�b�N
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CApplication::CApplication() :
	m_pRenderer(nullptr),
	m_pSound(nullptr),
	m_pTexture(nullptr),
	m_pInstancing(nullptr),
	m_pMode(nullptr),
	m_pFade(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pFade == nullptr);
	assert(m_pMode == nullptr);
	assert(m_pInstancing == nullptr);
	assert(m_pTexture == nullptr);
	assert(m_pSound == nullptr);
	assert(m_pRenderer == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	{// �����_���[
		m_pRenderer = new CRenderer;

		// null�`�F�b�N
		assert(m_pRenderer != nullptr);

		if (FAILED(m_pRenderer->Init(hWnd, !FULL_SCREEN)))
		{// ������
			return S_FALSE;
		}
	}

	{// ����
		CInput::Create();

		if (FAILED(CInput::GetKey()->Init(hInstance, hWnd)))
		{// ������
			return E_FAIL;
		}
	}

	{// �T�E���h
		m_pSound = new CSound;

		// null�`�F�b�N
		assert(m_pSound != nullptr);

		if (FAILED(m_pSound->Init(hWnd)))
		{// ������
			return S_FALSE;
		}
	}

	{// �e�N�X�`��
		m_pTexture = new CTexture;

		// null�`�F�b�N
		assert(m_pTexture != nullptr);
	}

	{// �C���X�^���V���O
		m_pInstancing = new CInstancing;

		// null�`�F�b�N
		assert(m_pInstancing != nullptr);

		// ������
		m_pInstancing->Init();
	}

	{// �t�F�[�h
		m_pFade = CFade::Create();

		// null�`�F�b�N
		assert(m_pFade != nullptr);

		// ������
		m_pFade->Init();
	}

	m_mode = START_MODE;

	// ���[�h�̐ݒ�
	m_pFade->ChangeMode(m_mode);

	// �����_���̏�����
	srand((unsigned int)time(NULL));

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CApplication::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll();

	m_pMode = nullptr;

	if (m_pFade != nullptr)
	{// null�`�F�b�N
		m_pFade->Uninit();
		m_pFade = nullptr;
	}

	if (m_pInstancing != nullptr)
	{// null�`�F�b�N
		m_pInstancing->Uninit();
		delete m_pInstancing;
		m_pInstancing = nullptr;
	}

	if (m_pTexture != nullptr)
	{// null�`�F�b�N
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pSound != nullptr)
	{// null�`�F�b�N
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	// ���͏����̏I��
	CInput::GetKey()->Uninit();

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CApplication::Update()
{
	// ���͏����̍X�V
	CInput::GetKey()->Update();

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �X�V
		m_pRenderer->Update();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �`�揈��
		m_pRenderer->Draw();
	}
}

//--------------------------------------------------
// ���[�h�̐ݒ�
//--------------------------------------------------
void CApplication::SetMode(CMode::EMode mode)
{
	m_mode = mode;

	// �S�Ẳ��
	CObject::ReleaseAll();

	// ���[�h�̐���
	m_pMode = CMode::Create(mode);
}

//--------------------------------------------------
// �f�o�C�X�̎擾
//--------------------------------------------------
LPDIRECT3DDEVICE9 CApplication::GetDevice()
{
	return m_pRenderer->GetDevice();
}

//--------------------------------------------------
// �����_���[�̎擾
//--------------------------------------------------
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//--------------------------------------------------
// �T�E���h�̎擾
//--------------------------------------------------
CSound* CApplication::GetSound()
{
	return m_pSound;
}

//--------------------------------------------------
// �e�N�X�`���̎擾
//--------------------------------------------------
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// �C���X�^���V���O�̎擾
//--------------------------------------------------
CInstancing* CApplication::GetInstancing()
{
	return m_pInstancing;
}

//--------------------------------------------------
// ���[�h�̎擾
//--------------------------------------------------
CMode* CApplication::GetMode()
{
	return m_pMode;
}

//--------------------------------------------------
// �t�F�[�h�̎擾
//--------------------------------------------------
CFade* CApplication::GetFade()
{
	return m_pFade;
}
