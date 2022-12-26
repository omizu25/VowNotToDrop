//======================================================
//
// �V�[���h�̏���
// Author : Sato Teruto
//
//======================================================

//--------------------------
// �C���N���[�h
//--------------------------
#include "shield.h"
#include "input.h"
#include "utility.h"

//==================================================
// ��`
//==================================================
namespace
{
const float STD_SPEED = 15.0f;	// �ړ���
const float POP_POS_Y = -150.0f;	// �o����Y�̈ʒu
const D3DXVECTOR3 POP_POS[] =
{// �o���̈ʒu
	D3DXVECTOR3(-150.0f, POP_POS_Y, 0.0f),
	D3DXVECTOR3(150.0f, POP_POS_Y, 0.0f),
	D3DXVECTOR3(0.0f, POP_POS_Y, -150.0f),
};
const D3DXVECTOR3 POP_ROT[] =
{// �o���̈ʒu
	D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),
};
const int POP_MAX = sizeof(POP_POS) / sizeof(POP_POS[0]);	// �o���ʒu�̍ő吔
}

//================================
// �R���X�g���N�^
//================================
CShield::CShield()
{

}

//================================
// �f�X�g���N�^
//================================
CShield::~CShield()
{

}

//================================
// ������
//================================
void CShield::Init()
{
	CModel::Init();
}

//================================
// �I��
//================================
void CShield::Uninit()
{
	CModel::Uninit();
}

//================================
// �X�V
//================================
void CShield::Update()
{
	CInput* pInput = CInput::GetKey();

	if (m_index == 0)
	{
		if (pInput->Press(KEY_LEFT))
		{// ��
			// �ʒu�̎擾
			D3DXVECTOR3 pos = CModel::GetPos();

			Homing(&pos, pos, D3DXVECTOR3(m_defaultPos.x, 0.0f, m_defaultPos.z), STD_SPEED);

			// �ʒu�̐ݒ�
			CModel::SetPos(pos);
		}
		else
		{
			// �ʒu�̎擾
			D3DXVECTOR3 pos = CModel::GetPos();

			Homing(&pos, pos, m_defaultPos, STD_SPEED);

			// �ʒu�̐ݒ�
			CModel::SetPos(pos);
		}
	}
	else if (m_index == 1)
	{
		if (pInput->Press(KEY_RIGHT))
		{// �E
		 // �ʒu�̎擾
			D3DXVECTOR3 pos = CModel::GetPos();

			Homing(&pos, pos, D3DXVECTOR3(m_defaultPos.x, 0.0f, m_defaultPos.z), STD_SPEED);

			// �ʒu�̐ݒ�
			CModel::SetPos(pos);
		}
		else
		{
			// �ʒu�̎擾
			D3DXVECTOR3 pos = CModel::GetPos();

			Homing(&pos, pos, m_defaultPos, STD_SPEED);

			// �ʒu�̐ݒ�
			CModel::SetPos(pos);
		}
	}
	else if (m_index == 2)
	{
		if (pInput->Press(KEY_DOWN))
		{// ��
		 // �ʒu�̎擾
			D3DXVECTOR3 pos = CModel::GetPos();

			Homing(&pos, pos, D3DXVECTOR3(m_defaultPos.x, 0.0f, m_defaultPos.z), STD_SPEED);

			// �ʒu�̐ݒ�
			CModel::SetPos(pos);
		}
		else
		{
			// �ʒu�̎擾
			D3DXVECTOR3 pos = CModel::GetPos();

			Homing(&pos, pos, m_defaultPos, STD_SPEED);

			// �ʒu�̐ݒ�
			CModel::SetPos(pos);
		}
	}

	CModel::Update();
}

//================================
// �`��
//================================
void CShield::Draw()
{
	CModel::Draw();
}

//================================
// ����
//================================
void CShield::CreateAll()
{
	for (int i = 0; i < POP_MAX; i++)
	{
		CShield::Create(POP_POS[i], POP_ROT[i], i);
	}
}

//================================
// ����
//================================
CShield* CShield::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int index)
{
	CShield *pShield = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pShield = new CShield;	//����

	if (pShield != nullptr)
	{//NULL�`�F�b�N
		//������
		pShield->Init();

		//�����o�ϐ��ɑ��
		pShield->m_defaultPos = pos;	//�����ʒu
		pShield->m_rot = rot;			//����
		pShield->m_index = index;
		pShield->SetLabel(CFileXManager::LABEL_BAMBOO);	//���f��

		pShield->SetPos(pos);
		pShield->SetRot(rot);
		
	}

	return pShield;
}