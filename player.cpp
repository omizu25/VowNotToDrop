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
const int MAX_PLAYER = 3;
const float POS_Y[MAX_PLAYER] =
{
	30.0f,
	20.0f,
	10.0f,
};
}
//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CPlayer::m_killCount = 0;

//--------------------------------------------------
// ����
//--------------------------------------------------
void CPlayer::CreateAll()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		CPlayer* pPlayer = CPlayer::Create(i, POS_Y[i]);

		if (i == 0)
		{
			pPlayer->SetLabel(CFileXManager::LABEL_Daruma_Head);
		}
		else
		{
			pPlayer->SetLabel(CFileXManager::LABEL_Daruma_Body);
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
void CPlayer::AddKill()
{
	m_killCount++;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CPlayer::CPlayer() :
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
		CObject::SetRelease();
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
