//**************************************************
// 
// file_x_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "file_x_manager.h"
#include "file_x.h"

//==================================================
// ��`
//==================================================
namespace
{
const string FILE_PATH[] =
{// �e�N�X�`���̃p�X
	"data/MODEL/Hammer.x",		// �n���}�[
	"data/MODEL/WoodBox.x",		// �ؔ�
	"data/MODEL/Fish_Tail.x",	// ���̐K��
	"data/MODEL/Fish_Body.x",	// ���̑�
	"data/MODEL/Angel/Body.x",				// �V�g�̑�
	"data/MODEL/Angel/Head.x",				// �V�g�̓�
	"data/MODEL/Angel/RightArmTop.x",		// �V�g�̉E�r��
	"data/MODEL/Angel/RightArmBottom.x",	// �V�g�̉E�r��
	"data/MODEL/Angel/RightHand.x",			// �V�g�̉E��
	"data/MODEL/Angel/LeftArmTop.x",		// �V�g�̍��r��
	"data/MODEL/Angel/LeftArmBottom.x",		// �V�g�̍��r��
	"data/MODEL/Angel/LeftHand.x",			// �V�g�̍���
	"data/MODEL/Angel/RightFootTop.x",		// �V�g�̉E����
	"data/MODEL/Angel/RightFootBottom.x",	// �V�g�̉E����
	"data/MODEL/Angel/RightFoot.x",			// �V�g�̉E��
	"data/MODEL/Angel/LeftFootTop.x",		// �V�g�̍�����
	"data/MODEL/Angel/LeftFootBottom.x",	// �V�g�̍�����
	"data/MODEL/Angel/LeftFoot.x",			// �V�g�̍���
	"data/MODEL/Angel/Rope.x",				// �Ă�Ă�̓�
	"data/MODEL/Angel/Head.x",				// �Ă�Ă�̓�
	"data/MODEL/Angel/Body.x",				// �Ă�Ă�̑�
	"data/MODEL/Angel/Right_ear.x",			// �Ă�Ă�̉E��
	"data/MODEL/Angel/Left_ear.x",			// �Ă�Ă�̍���
	"data/MODEL/Angel/Angel_ring.x",		// �Ă�Ă�̓V�g�̗�
	"data/MODEL/Angel/Angel_wing.x",		// �Ă�Ă�̓V�g�̉H
	"data/MODEL/Angel/Devil_wing.x",		// �Ă�Ă�̈����̉H
	"data/MODEL/Angel/Morning_koko.x",		// �Ă�Ă�̒��R�R
};
}

static_assert(sizeof(FILE_PATH) / sizeof(FILE_PATH[0]) == CFileXManager::LABEL_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CFileXManager::CFileXManager()
{
	for (int i = 0; i < LABEL_MAX; i++)
	{
		m_pFileX[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CFileXManager::~CFileXManager()
{
	for (int i = 0; i < LABEL_MAX; i++)
	{
		assert(m_pFileX[i] == nullptr);
	}
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CFileXManager::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// �ǂݍ���
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CFileXManager::Load(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// X�t�@�C���̓ǂݍ��݂�����Ă���
		return;
	}

	// ����
	m_pFileX[label] = CFileX::Create(FILE_PATH[label]);
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CFileXManager::Load(const string& str)
{
	// �ϊ�
	ELabel label = Change(str);

	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// X�t�@�C���̓ǂݍ��݂�����Ă���
		return;
	}

	// ����
	m_pFileX[label] = CFileX::Create(FILE_PATH[label]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CFileXManager::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// ���
		Release((ELabel)i);
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CFileXManager::Release(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// X�t�@�C���̏��̉��
		m_pFileX[label]->Uninit();
		m_pFileX[label] = nullptr;
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CFileXManager::Release(const string& str)
{
	// �ϊ�
	ELabel label = Change(str);

	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// X�t�@�C���̏��̉��
		m_pFileX[label]->Uninit();
		delete m_pFileX[label];
		m_pFileX[label] = nullptr;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
CFileX* CFileXManager::Get(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	// �ǂݍ���
	Load(label);

	return m_pFileX[label];
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
CFileX* CFileXManager::Get(const string& str)
{
	// �ϊ�
	ELabel label = Change(str);

	assert(label > LABEL_NONE && label < LABEL_MAX);

	// �ǂݍ���
	Load(label);

	return m_pFileX[label];
}

//--------------------------------------------------
// �ϊ�
//--------------------------------------------------
const string& CFileXManager::Change(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	return FILE_PATH[label];
}

//--------------------------------------------------
// �ϊ�
//--------------------------------------------------
CFileXManager::ELabel CFileXManager::Change(const string& str)
{
	for (int i = 0; i < LABEL_MAX; i++)
	{
		if (FILE_PATH[i] == str)
		{// �p�X�Ɠ���
			return (ELabel)i;
		}
	}

	return LABEL_NONE;
}
