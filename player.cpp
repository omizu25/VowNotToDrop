//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "player.h"
#include "application.h"
#include "utility.h"

//==================================================
// ��`
//==================================================
namespace
{
const float POS_Y[CPlayer::MAX_PLAYER] =
{
	30.0f,
	20.0f,
	10.0f,
};
}
//==================================================
// �ÓI�����o�ϐ�
//==================================================
CPlayer* CPlayer::m_pPlayer[CPlayer::MAX_PLAYER] = {};
int CPlayer::m_killCount = 0;

//--------------------------------------------------
// ����
//--------------------------------------------------
void CPlayer::CreateAll()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		m_pPlayer[i] = CPlayer::Create(i, POS_Y[i]);

		if (i == 0)
		{
			m_pPlayer[i]->SetLabel(CFileXManager::LABEL_Daruma_Head);
		}
		else
		{
			m_pPlayer[i]->SetLabel(CFileXManager::LABEL_Daruma_Body);
		}
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CPlayer* CPlayer::Create(int index, float posDest)
{
	CPlayer* pPlayer = new CPlayer;

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pPlayer->Init();

	pPlayer->m_index = index;

	// �ړI�̈ʒu�̐ݒ�
	pPlayer->m_posDest = posDest;

	// �ʒu�̐ݒ�
	pPlayer->SetPos(D3DXVECTOR3(0.0f, posDest, 0.0f));

	return pPlayer;
}

//--------------------------------------------------
// �c�@�̌��Z
//--------------------------------------------------
void CPlayer::AddKill(const D3DXVECTOR3& move)
{
	if (m_killCount >= MAX_PLAYER)
	{
		return;
	}

	m_killCount++;
	m_pPlayer[MAX_PLAYER - m_killCount]->SetMove(move);
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CPlayer::CPlayer() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_index(0),
	m_posDest(0.0f)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CPlayer::Init()
{
	m_move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_posDest = 0.0f;
	m_index = 0;

	// ������
	CModel::Init();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CPlayer::Uninit()
{
	// �I��
	CModel::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CPlayer::Update()
{
	int index = m_index + m_killCount;

	if (index >= MAX_PLAYER)
	{
		// �����̎擾
		D3DXVECTOR3 rot = CModel::GetRot();

		rot.x += -D3DX_PI * 0.25f;
		rot.y += -D3DX_PI * 0.25f;

		// �����̐ݒ�
		CModel::SetRot(rot);

		// �ʒu�̎擾
		D3DXVECTOR3 pos = CModel::GetPos();

		pos += m_move;

		// �ʒu�̐ݒ�
		CModel::SetPos(pos);
		
		if (InRange(&pos, D3DXVECTOR3(550.0f, 0.0f, 550.0f)))
		{// �͈͊O�ɏo��
			CObject::SetRelease();
		}
	}

	m_posDest = POS_Y[index];

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CModel::GetPos();

	Homing(&pos, pos, D3DXVECTOR3(0.0f, m_posDest, 0.0f), 1.0f);

	// �ʒu�̐ݒ�
	CModel::SetPos(pos);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CPlayer::Draw()
{
	// �`��
	CModel::Draw();
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CPlayer::SetMove(const D3DXVECTOR3& move)
{
	m_move = move;
	m_move *= 5.0f;
	m_move.y = 10.0f;
}

//--------------------------------------------------
// �ړ��ʂ̎擾
//--------------------------------------------------
const D3DXVECTOR3& CPlayer::GetMove() const
{
	return m_move;
}
