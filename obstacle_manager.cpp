//**************************************************
// 
// obstacle_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "obstacle_manager.h"
#include "obstacle.h"

//==================================================
// ��`
//==================================================
namespace
{
const int MIN_INTERVAL = 5;		// �Ԋu�̍ŏ��l
const int MAX_INTERVAL = 120;	// �Ԋu�̍ő�l
const int POP_INTERVAL = 4;		// �o���̍ő吔
const float POP_POS_Y = 10.0f;	// �o����Y�̈ʒu
const D3DXVECTOR3 POP_POS[] =
{// �o���̈ʒu
	D3DXVECTOR3(-600.0f, POP_POS_Y, 100.0f),
	D3DXVECTOR3(   0.0f, POP_POS_Y, -500.0f),
	D3DXVECTOR3( 600.0f, POP_POS_Y, 100.0f),
};
const D3DXVECTOR3 MOVE[] =
{// �o���̈ʒu
	D3DXVECTOR3( 6.0f, 0.0f, 0.0f),
	D3DXVECTOR3( 0.0f, 0.0f, 6.0f),
	D3DXVECTOR3(-6.0f, 0.0f, 0.0f),
};
const D3DXVECTOR3 POP_ROT[] =
{// �o���̈ʒu
	D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
	D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
	D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
};
const int POP_MAX = sizeof(POP_POS) / sizeof(POP_POS[0]);	// �o���ʒu�̍ő吔
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CObstacleManager* CObstacleManager::Create()
{
	CObstacleManager* pManager = nullptr;

	pManager = new CObstacleManager;

	if (pManager != nullptr)
	{// null�`�F�b�N
		// ������
		pManager->Init();
	}

	return pManager;
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CObstacleManager::CObstacleManager() : CObject(CObject::PRIORITY_SYSTEM),
	m_time(0),
	m_pop(0),
	m_interval(0),
	m_move(0.0f)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObstacleManager::~CObstacleManager()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CObstacleManager::Init()
{
	m_time = 0;
	m_interval = MAX_INTERVAL;
	m_move = 1.0f;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CObstacleManager::Uninit()
{
	// �j��
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CObstacleManager::Update()
{
	m_time++;

	// �Q�[��
	Game();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CObstacleManager::Draw()
{
}

//--------------------------------------------------
// �Q�[��
//--------------------------------------------------
void CObstacleManager::Game()
{
	if (m_time % m_interval == 0)
	{// ���Ԋu
		int random = rand() % POP_MAX;

		// ����
		CObstacle::Create(POP_POS[random], MOVE[random] * m_move, POP_ROT[random]);

		if (m_pop >= POP_INTERVAL)
		{// �ő吔���z����
			
		}

		m_pop++;

		if (m_pop >= POP_INTERVAL)
		{// �ő吔���z����
			m_move += 0.05f;

			m_interval -= 10;

			if (m_interval <= MIN_INTERVAL)
			{// �ŏ��l�ȉ�
				m_interval = MIN_INTERVAL;
			}

			m_pop = 0;
		}
	}
}
