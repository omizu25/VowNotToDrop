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
CObstacle* CObstacle::Create()
{
	CObstacle* pObstacle = new CObstacle;

	if (pObstacle == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pObstacle->Init();

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

	// �ʒu�̐ݒ�
	CModel::SetPos(D3DXVECTOR3(0.0f, 10.0f, 0.0f));

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
	D3DXVECTOR3 pos = CModel::GetPos();
	pos += m_move;
CModel::SetPos(pos);

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
