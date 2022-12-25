//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include "effect.h"
#include "application.h"
#include "instancing.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CObject::m_numAll = 0;
CObject* CObject::m_pTop[PRIORITY_MAX] = {};
CObject* CObject::m_pCurrent[PRIORITY_MAX] = {};

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CObject::ReleaseAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		if (i == PRIORITY_EFFECT)
		{// �G�t�F�N�g
			CEffect::ReleaseAll();
			continue;
		}

		CObject* pObj = m_pTop[i];

		if (pObj == nullptr || i == PRIORITY_FADE)
		{// null�`�F�b�N
			continue;
		}

		while (true)
		{
			CObject* pObjNext = pObj->m_pNext;

			// �I��
			pObj->Uninit();

			pObj = pObjNext;

			if (pObj == nullptr)
			{// �Ō�܂ŗ���
				break;
			}
		}
	}
}

//--------------------------------------------------
// �S�Ă̍X�V
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		if (i == PRIORITY_EFFECT)
		{// �G�t�F�N�g
			CEffect::UpdateAll();
			continue;
		}

		CObject* pObj = m_pTop[i];

		if (pObj == nullptr)
		{// null�`�F�b�N
			continue;
		}

		while (true)
		{
			if (!pObj->m_release)
			{// ������Ȃ�
				pObj->Update();
			}

			pObj = pObj->m_pNext;

			if (pObj == nullptr)
			{// �Ō�܂ŗ���
				break;
			}
		}

		pObj = m_pTop[i];

		while (true)
		{
			CObject* pObjNext = pObj->m_pNext;

			if (pObj->m_release)
			{// �������
				pObj->Release();
			}

			pObj = pObjNext;

			if (pObj == nullptr)
			{// �Ō�܂ŗ���
				break;
			}
		}
	}
}

//--------------------------------------------------
// �S�Ă̕`��
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		if (i == PRIORITY_EFFECT)
		{// �G�t�F�N�g
			CApplication::GetInstance()->GetInstancing()->Draw();
			continue;
		}

		CObject* pObj = m_pTop[i];

		if (pObj == nullptr)
		{// null�`�F�b�N
			continue;
		}

		while (true)
		{
			if (!pObj->m_release)
			{// ������Ȃ�
				pObj->Draw();
			}

			pObj = pObj->m_pNext;

			if (pObj == nullptr)
			{// �Ō�܂ŗ���
				break;
			}
		}
	}
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
int CObject::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CObject::CObject(EPriority priority) :
	m_pPrev(nullptr),
	m_pNext(nullptr),
	m_priority(priority),
	m_release(false)
{
	if (m_pTop[priority] == nullptr)
	{// �N�����Ȃ�
		assert(m_pCurrent[priority] == nullptr);

		m_pTop[priority] = this;
		m_pCurrent[priority] = this;
	}
	else
	{
		m_pPrev = m_pCurrent[priority];
		m_pCurrent[priority]->m_pNext = this;
		m_pCurrent[priority] = this;
	}

	m_numAll++;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObject::~CObject()
{
	assert(m_pPrev == nullptr);
	assert(m_pNext == nullptr);

	m_numAll--;
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CObject::Release()
{
	if (this == nullptr)
	{// null�`�F�b�N
		return;
	}
	else if (m_pPrev == nullptr && m_pNext == nullptr)
	{// �����������Ȃ�
		assert(m_pTop[m_priority] == this);
		assert(m_pCurrent[m_priority] == this);

		m_pTop[m_priority] = nullptr;
		m_pCurrent[m_priority] = nullptr;
	}
	else if (m_pPrev == nullptr)
	{// �擪
		assert(m_pTop[m_priority] == this);

		m_pTop[m_priority] = m_pNext;
		m_pTop[m_priority]->m_pPrev = nullptr;
	}
	else if (m_pNext == nullptr)
	{// �Ō��
		assert(m_pCurrent[m_priority] == this);

		m_pCurrent[m_priority] = m_pPrev;
		m_pCurrent[m_priority]->m_pNext = nullptr;
	}
	else
	{// ����
		assert(m_pTop[m_priority] != this);
		assert(m_pCurrent[m_priority] != this);

		m_pPrev->m_pNext = m_pNext;
		m_pNext->m_pPrev = m_pPrev;
	}

	m_pPrev = nullptr;
	m_pNext = nullptr;

	delete this;
}

//--------------------------------------------------
// �������
//--------------------------------------------------
void CObject::SetRelease()
{
	m_release = true;
}

//--------------------------------------------------
// ������邩�ǂ����̎擾
//--------------------------------------------------
bool CObject::GetRelease()
{
	return m_release;
}
