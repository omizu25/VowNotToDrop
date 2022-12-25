//=============================================================================
//
// ���͏��� [input.cpp]
// Author1 : KOZUNA HIROHITO
// input.h���Q�Ƃ𐄏�
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "inputkeyboard.h"

//*************************************************************************************
//�R���X�g���N�^
//*************************************************************************************
CInputKeyboard::CInputKeyboard()
{
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
	m_pDevKeyboard = nullptr;
}

//*************************************************************************************
//�f�X�g���N�^
//*************************************************************************************
CInputKeyboard::~CInputKeyboard()
{
}

//*************************************************************************************
//������
//*************************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	
	//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevKeyboard->Acquire();

	return S_OK;
}

//*************************************************************************************
//�I������
//*************************************************************************************
void CInputKeyboard::Uninit(void)
{
	//���̓f�o�C�X�i�L�[�{�[�h�j�̕���
	if (m_pDevKeyboard != NULL)
	{
		m_pDevKeyboard->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}
}

//*************************************************************************************
//�X�V����
//*************************************************************************************
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏��
	int nCntKey;
	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = ~m_aKeyState[nCntKey] & aKeyState[nCntKey];	 // �L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyStateRelease[nCntKey] = m_aKeyState[nCntKey] & ~aKeyState[nCntKey];	 // �L�[�{�[�h�̃����[�X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];		// �L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();			//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//�L�[�{�[�h�v���X����
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�g���K�[����
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�����[�X����
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//�L�[�{�[�h�S�L�[�v���X����
bool CInputKeyboard::GetAllPress(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetPress(nCntKey))
		{
			return true;
		}
	}
	return false;
}
//�L�[�{�[�h�S�L�[�g���K�[����
bool CInputKeyboard::GetAllTrigger(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetTrigger(nCntKey))
		{
			return true;
		}
	}
	return false;
}

//�L�[�{�[�h�S�L�[�����[�X����
bool CInputKeyboard::GetAllRelease(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if (GetRelease(nCntKey))
		{
			return true;
		}
	}
	return false;
}
