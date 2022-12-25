//**************************************************
// 
// menu.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "menu.h"
#include "object2D.h"
#include "utility.h"
#include "input.h"
#include "application.h"
#include "sound.h"
#include "fade.h"

//==================================================
// ��`
//==================================================
namespace
{
const float CHANGE_SPEED = 0.025f;	// ���l�̕ύX���x
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CMenu* CMenu::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int num, float interval)
{
	CMenu* pMenu = new CMenu;

	if (pMenu == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pMenu->Init();

	// �ݒ�
	pMenu->Set(pos, size, num, interval);

	return pMenu;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CMenu::CMenu() :CObject(CObject::PRIORITY_SYSTEM),
	m_pOption(nullptr),
	m_pFrame(nullptr),
	m_pCursor(nullptr),
	m_index(0),
	m_num(0),
	m_time(0),
	m_alpha(0.0f)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMenu::~CMenu()
{
	assert(m_pOption == nullptr);
	assert(m_pFrame == nullptr);
	assert(m_pCursor == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CMenu::Init()
{
	m_pOption = nullptr;
	m_pFrame = nullptr;
	m_pCursor = nullptr;
	m_index = 0;
	m_num = 0;
	m_time = 0;
	m_alpha = CHANGE_SPEED;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CMenu::Uninit()
{
	if (m_pOption != nullptr)
	{// null�`�F�b�N
		for (int i = 0; i < m_index; i++)
		{
			if (m_pOption[i] != nullptr)
			{// null�`�F�b�N
				m_pOption[i]->Uninit();
				m_pOption[i] = nullptr;
			}
		}

		delete[] m_pOption;
		m_pOption = nullptr;
	}
	
	if (m_pFrame != nullptr)
	{// null�`�F�b�N
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pCursor != nullptr)
	{// null�`�F�b�N
		m_pCursor->Uninit();
		m_pCursor = nullptr;
	}

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CMenu::Update()
{
	// ����
	Input();

	// ���l�̕ύX
	Alpha();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CMenu::Draw()
{
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
int CMenu::Select()
{
	CFade::EState state = CApplication::GetInstance()->GetFade()->GetState();

	if (state != CFade::STATE_NONE)
	{// �t�F�[�h���Ă���
		return -1;
	}

	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_DECISION))
	{// ����L�[�������ꂽ
		m_alpha = 0.1f;

		// SE
		CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_Enter);

		return m_index;
	}

	return -1;
}

//--------------------------------------------------
// �J�[�\���̐ݒ�
//--------------------------------------------------
void CMenu::SetCursor(const D3DXVECTOR3& size, float interval)
{
	if (m_pCursor != nullptr)
	{// null�`�F�b�N
		return;
	}

	// ����
	m_pCursor = CObject2D::Create();

	D3DXVECTOR3 pos = m_pOption[m_index]->GetPos();
	pos.x -= ((size.x * 0.5f) + (m_pOption[m_index]->GetSize().x * 0.5f) + interval);

	// �ʒu�̐ݒ�
	m_pCursor->SetPos(pos);

	// �T�C�Y�̐ݒ�
	m_pCursor->SetSize(size);

	// �e�N�X�`���̐ݒ�
	m_pCursor->SetTexture(CTexture::LABEL_Cursor);
}

//--------------------------------------------------
// �t���[���̐ݒ�
//--------------------------------------------------
void CMenu::SetFrame(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col)
{
	// �`��ݒ�
	m_pFrame->SetDraw(true);

	// �ʒu�̐ݒ�
	m_pFrame->SetPos(pos);

	// �T�C�Y�̐ݒ�
	m_pFrame->SetSize(size);

	// �F�̐ݒ�
	m_pFrame->SetCol(col);
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CMenu::SetTexture(int idx, CTexture::ELabel label)
{
	if (idx == -1)
	{// �w��̒l
		m_pFrame->SetTexture(label);
		return;
	}

	assert(idx >= 0 && idx < m_num);

	if (m_pOption[idx] == nullptr)
	{// null�`�F�b�N
		return;
	}
	
	// �e�N�X�`���̐ݒ�
	m_pOption[idx]->SetTexture(label);
}

//--------------------------------------------------
// �T�C�Y�̐ݒ�
//--------------------------------------------------
void CMenu::SetSize(int idx, const D3DXVECTOR3& size)
{
	assert(idx >= 0 && idx < m_num);

	if (m_pOption[idx] == nullptr)
	{// null�`�F�b�N
		return;
	}

	int index = 0;
	float width = 0.0f;

	for (int i = 0; i < m_num; i++)
	{
		if (m_pOption[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		if (m_pOption[i]->GetSize().x >= width)
		{// ���̑I�����ȏ�̒���
			width = m_pOption[i]->GetSize().x;
			index = i;
		}
	}
	
	width *= 0.5f;

	D3DXVECTOR3 pos = m_pOption[idx]->GetPos();
	pos.x = m_pOption[index]->GetPos().x - width;
	pos.x += size.x * 0.5f;

	// �ʒu�̐ݒ�
	m_pOption[idx]->SetPos(pos);

	// �T�C�Y�̐ݒ�
	m_pOption[idx]->SetSize(size);
}

//--------------------------------------------------
// �I������Ă���ԍ��̎擾
//--------------------------------------------------
int CMenu::GetSelectIdx()
{
	return m_index;
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CMenu::Set(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int num, float interval)
{
	m_num = num;

	if (m_num == 0)
	{// ��������Ȃ�
		m_num = 1;
	}

	// �g�̍쐬
	m_pFrame = CObject2D::Create();

	// �`��ݒ�
	m_pFrame->SetDraw(false);

	// �I�����̐���
	m_pOption = new CObject2D*[m_num];

	if (m_pOption == nullptr)
	{// null�`�F�b�N
		assert(false);
		return;
	}

	D3DXVECTOR3 optionPos = pos;
	optionPos.y -= ((m_num - 1) * ((size.y * 0.5f) + (interval * 0.5f)));

	for (int i = 0; i < m_num; i++)
	{
		// �I�����̍쐬
		m_pOption[i] = CObject2D::Create();

		// �ʒu�̐ݒ�
		m_pOption[i]->SetPos(optionPos);

		// �T�C�Y�̐ݒ�
		m_pOption[i]->SetSize(size);

		optionPos.y += size.y + interval;
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CMenu::Input()
{
	if (m_num == 1)
	{// �I�����������
		return;
	}

	if (m_alpha != CHANGE_SPEED)
	{// ���肳��Ă���
		return;
	}

	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_UP))
	{// ��L�[�������ꂽ
		Add(-1);
	}
	if (pInput->Trigger(KEY_DOWN))
	{// ���L�[�������ꂽ
		Add(1);
	}
}

//--------------------------------------------------
// ���l
//--------------------------------------------------
void CMenu::Alpha()
{
	m_time++;

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, m_alpha) * 0.7f);

	// �F�̐ݒ�
	m_pOption[m_index]->SetCol(col);
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CMenu::Add(int add)
{
	// �F�̐ݒ�
	m_pOption[m_index]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_index = ((m_index + add) + m_num) % m_num;
	assert(m_index >= 0 && m_index < m_num);

	m_time = 0;

	if (m_pCursor != nullptr)
	{// null�`�F�b�N
		D3DXVECTOR3 pos = m_pCursor->GetPos();
		pos.y = m_pOption[m_index]->GetPos().y;

		// �ʒu�̐ݒ�
		m_pCursor->SetPos(pos);
	}

	// SE
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_Select);
}
