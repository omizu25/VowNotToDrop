//**************************************************
// 
// obstacle.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "obstacle.h"
#include "application.h"
#include "utility.h"
#include "player.h"
#include "input.h"

//==================================================
// ��`
//==================================================
namespace
{
const CFileXManager::ELabel MODEL_PATH = CFileXManager::LABEL_NeedleBall;	// �t�@�C���p�X
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	CObstacle* pObstacle = new CObstacle;

	if (pObstacle == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pObstacle->Init();

	// �ʒu�̐ݒ�
	pObstacle->SetPos(pos);

	// �ړ��ʂ̐ݒ�
	pObstacle->SetMove(move);

	return pObstacle;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CObstacle::CObstacle() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObstacle::~CObstacle()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CObstacle::Init()
{
	m_move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	// ������
	CModel::Init();

	// �g�p���郂�f���̐ݒ�
	CModel::SetLabel(MODEL_PATH);

	// �N�H�[�^�j�I���̐ݒ�
	CModel::SetIsQuaternion(true);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CObstacle::Uninit()
{
	// �I��
	CModel::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CObstacle::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CModel::GetPos();

	pos += m_move;

	// �ʒu�̐ݒ�
	CModel::SetPos(pos);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(KEY_LEFT))
	{// ��
		Shield(D3DXVECTOR3(-50.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(KEY_RIGHT))
	{// �E
		Shield(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	}
	else if (pInput->Press(KEY_DOWN))
	{// ��
		Shield(D3DXVECTOR3(0.0f, 0.0f, -50.0f));
	}

	if (!InRange(&pos, D3DXVECTOR3(10.0f, 0.0f, 10.0f)))
	{// �͈͓��ɓ�����
		CPlayer::AddKill(m_move);
		CObject::SetRelease();
	}

	if (InRange(&pos, D3DXVECTOR3(550.0f, 0.0f, 550.0f)))
	{// �͈͊O�ɏo��
		CObject::SetRelease();
	}

	// �X�V
	CModel::Update();

	// �N�H�[�^�j�I���̐ݒ�
	CModel::SetQuaternion(m_move);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CObstacle::Draw()
{
	// �`��
	CModel::Draw();
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CObstacle::SetMove(const D3DXVECTOR3& move)
{
	m_move = move;
}

//--------------------------------------------------
// �ړ��ʂ̎擾
//--------------------------------------------------
const D3DXVECTOR3& CObstacle::GetMove() const
{
	return m_move;
}

//--------------------------------------------------
// �V�[���h
//--------------------------------------------------
void CObstacle::Shield(const D3DXVECTOR3& pos)
{
	if (CollisionCircle(CModel::GetPos(), 10.0f, pos, 10.0f))
	{// ��������
		m_move = m_move * -5.0f;
		m_move.y = 10.0f;
	}
}
