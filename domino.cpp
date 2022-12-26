//**************************************************
// 
// domino.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "domino.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "fade.h"
#include "mode.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//==================================================
// �ÓI�����o�ϐ�
//==================================================
float CDomino::m_move = 0.0f;
int CDomino::m_count = 0;

//--------------------------------------------------
// ����
//--------------------------------------------------
int CDomino::GetCount()
{
	return m_count;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CDomino::SetCount(int score)
{
	m_count = score;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CDomino::AddCount()
{
	m_count++;

	if (m_count >= 99)
	{
		m_count = 99;
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CDomino::AddMove()
{
	m_move += -0.1f;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CDomino::CreateAll()
{
	m_move = 0.0f;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, -120.0f);
	for (int i = 0; i < m_count; i++)
	{
		// ����
		CDomino::Create(pos);

		pos.x += 50.0f;
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CDomino* CDomino::Create(const D3DXVECTOR3& pos)
{
	CDomino* pDomino = new CDomino;

	if (pDomino == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pDomino->Init();

	// �ʒu�̐ݒ�
	pDomino->SetPos(pos);

	return pDomino;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CDomino::CDomino()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CDomino::~CDomino()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CDomino::Init()
{
	// ������
	CModel::Init();

	// �����̐ݒ�
	CModel::SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f ,0.0f));

	// �g�p���郂�f���̐ݒ�
	CModel::SetLabel(CFileXManager::LABEL_Hagoita);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CDomino::Uninit()
{
	// �I��
	CModel::Uninit();

	m_count--;

	if (m_count <= 0)
	{
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(CMode::MODE_RANKING);
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CDomino::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CModel::GetPos();

	pos.x += m_move;

	// �ʒu�̐ݒ�
	CModel::SetPos(pos);

	if (pos.x <= -1000.0f)
	{// �͈͊O�ɏo��
		CObject::SetRelease();
	}

	if (pos.x <= 10.0f + (m_move * -1.0f))
	{
		// �ʒu�̎擾
		D3DXVECTOR3 rot = CModel::GetRot();

		rot.x += (m_move * -1.0f) * 0.01f;

		// �p�x�̐��K��
		NormalizeAngle(&rot.x);

		if (rot.x >= D3DX_PI * 0.35f)
		{
			rot.x = D3DX_PI * 0.35f;
		}

		// �ʒu�̐ݒ�
		CModel::SetRot(rot);
	}

	// �X�V
	CModel::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CDomino::Draw()
{
	// �`��
	CModel::Draw();
}
