//**************************************************
// 
// fade.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "fade.h"
#include "application.h"

//==================================================
// ��`
//==================================================
namespace
{
const float FADE_SPEED = 0.05f;	// �t�F�[�h�̑��x
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CFade* CFade::Create()
{
	CFade* pFade = new CFade;

	if (pFade == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pFade->Init();

	return pFade;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CFade::CFade() : CObject2D(CObject::PRIORITY_FADE),
	m_mode(CMode::MODE_NONE),
	m_state(STATE_NONE)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CFade::~CFade()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CFade::Init()
{
	// ������
	CObject2D::Init();

	D3DXVECTOR3 vec = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f);

	// �ʒu�̐ݒ�
	CObject2D::SetPos(vec * 0.5f);

	// �T�C�Y�̐ݒ�
	CObject2D::SetSize(vec);

	// �F�̐ݒ�
	CObject2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	m_mode = CMode::MODE_NONE;
	m_state = STATE_NONE;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CFade::Uninit()
{
	// �I��
	CObject2D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CFade::Update()
{
	switch (m_state)
	{
	case STATE_NONE:
		/* �����Ȃ� */
		break;

	case STATE_IN:
		In();
		break;

	case STATE_OUT:
		Out();
		break;

	case STATE_MAX:
	default:
		assert(false);
		break;
	}

	// �X�V
	CObject2D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CFade::Draw()
{
	// �`��
	CObject2D::Draw();
}

//--------------------------------------------------
// ���[�h�̕ύX
//--------------------------------------------------
void CFade::ChangeMode(CMode::EMode nextMode)
{
	if (m_state != STATE_NONE)
	{// �t�F�[�h�����Ă���
		return;
	}

	// ������
	Init();

	m_mode = nextMode;
	m_state = STATE_IN;
}

//--------------------------------------------------
// ��Ԃ̎擾
//--------------------------------------------------
CFade::EState CFade::GetState()
{
	return m_state;
}

//--------------------------------------------------
// �C��
//--------------------------------------------------
void CFade::In()
{
	// �F�̎擾
	D3DXCOLOR col = CObject2D::GetCol();

	col.a += FADE_SPEED;

	if (col >= 1.0f)
	{// �w��̒l�ȏ�
		col.a = 1.0F;
		m_state = STATE_OUT;
		
		// ���[�h�̐ݒ�
		CApplication::GetInstance()->SetMode(m_mode);
	}

	// �F�̐ݒ�
	CObject2D::SetCol(col);
}

//--------------------------------------------------
// �A�E�g
//--------------------------------------------------
void CFade::Out()
{
	// �F�̎擾
	D3DXCOLOR col = CObject2D::GetCol();

	col.a += -FADE_SPEED;

	if (col <= 0.0f)
	{// �w��̒l�ȉ�
		col.a = 0.0F;
		m_state = STATE_NONE;
	}

	// �F�̐ݒ�
	CObject2D::SetCol(col);
}
