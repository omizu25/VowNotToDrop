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
#include "Score.h"
#include "domino.h"
#include "shield.h"

//==================================================
// ��`
//==================================================
namespace
{
const CFileXManager::ELabel MODEL_PATH = CFileXManager::LABEL_WING;	// �t�@�C���p�X
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& rot)
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

	// �����̐ݒ�
	pObstacle->SetRot(rot);

	return pObstacle;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CObstacle::CObstacle() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_collision(false)
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
	m_collision = false;

	// ������
	CModel::Init();

	// �g�p���郂�f���̐ݒ�
	CModel::SetLabel(MODEL_PATH);
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

	// �����̎擾
	D3DXVECTOR3 rot = CModel::GetRot();

	if (m_collision)
	{// ��������
		rot.x += -D3DX_PI * 0.25f;
		rot.y += -D3DX_PI * 0.25f;

		// �p�x�̐��K��
		NormalizeAngle(&rot.x);
		NormalizeAngle(&rot.y);

	}
	else
	{
		rot.z += -D3DX_PI * 0.1f;

		// �p�x�̐��K��
		NormalizeAngle(&rot.z);
	}

	// �����̐ݒ�
	CModel::SetRot(rot);

	if (!m_collision)
	{// �������ĂȂ�
		CInput* pInput = CInput::GetKey();

		int nPopNumber;
		for (int i = 0; i < 3; i++)
		{
			nPopNumber = CShield::GetNumPop(i);

			switch (nPopNumber)
			{
			case 0:
				if (pInput->Press(KEY_LEFT))
				{// ��
					Shield(D3DXVECTOR3(-150.0f, 0.0f, 100.0f));
				}
				break;

			case 1:
				if (pInput->Press(KEY_RIGHT) && nPopNumber == 1)
				{// �E
					Shield(D3DXVECTOR3(150.0f, 0.0f, 100.0f));
				}
				break;

			case 2:
				if (pInput->Press(KEY_DOWN) && nPopNumber == 2)
				{// ��
					Shield(D3DXVECTOR3(0.0f, 0.0f, -50.0f));
				}
				break;

			default:
				break;
			}
		}

		if (!InRange(&pos, D3DXVECTOR3(20.0f, 0.0f, 110.0f)))
		{// �v���C���[�ɓ�������
			CPlayer::AddKill(m_move);
			CObject::SetRelease();
		}
	}

	if (InRange(&pos, D3DXVECTOR3(650.0f, 0.0f, 650.0f)))
	{// �͈͊O�ɏo��
		CObject::SetRelease();
	}

	// �X�V
	CModel::Update();
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
	if (CollisionCircle(CModel::GetPos(), 0.0f, pos, 50.0f))
	{// �叼�ɓ�������
		m_move = m_move * -5.0f;
		m_move.y = 10.0f;
		m_collision = true;
		CScore::AddFrag();
		CDomino::AddCount();
	}
}
