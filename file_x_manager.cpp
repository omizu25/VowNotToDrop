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
	"data/MODEL/NeedleBall.x",	// �S��
	"data/MODEL/Daruma_Head.x",	// �_���}�̓�
	"data/MODEL/Daruma_Body.x",	// �_���}�̐g��
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
