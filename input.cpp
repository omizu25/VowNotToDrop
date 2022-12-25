//=============================================================================
//
// ���͏��� [input.cpp]
// Author1 : KOZUNA HIROHITO
// Author2 : YUDA KAITO
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "input.h"
#include "DirectInput.h"
#include "inputkeyboard.h"
#include "inputjoypad.h"

//-----------------------------------------------------------------------------
//�ÓI�����o�ϐ��錾
//-----------------------------------------------------------------------------
CInput *CInput::m_pInput = nullptr;	// ���̃N���X�̏��

//-----------------------------------------------------------------------------
//�R���X�g���N�^
//-----------------------------------------------------------------------------
CInput::CInput()
{
	m_pKeyboard = nullptr;	// �L�[�{�[�h�̏��
	m_pJoyPad = nullptr;	// �W���C�p�b�h�̏��
}

//-----------------------------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------------------------
CInput::~CInput()
{
}

//-----------------------------------------------------------------------------
//������
//-----------------------------------------------------------------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(CDirectInput::Create(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�̐���
	m_pKeyboard = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�W���C�p�b�h�̐���
	m_pJoyPad = new CInputJoyPad;

	//�W���C�p�b�h�̏���������
	if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//*************************************************************************************
//�I������
//*************************************************************************************
void CInput::Uninit()
{
	//�L�[�{�[�h�̔j��
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//�W���C�p�b�h�̔j��
	if (m_pJoyPad != nullptr)
	{
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	CDirectInput::Break();

	//���Ȕj��
	if (m_pInput != nullptr)
	{
		delete m_pInput;
		m_pInput = nullptr;
	}
}

//*************************************************************************************
//�X�V����
//*************************************************************************************
void CInput::Update()
{
	//�L�[�{�[�h�̍X�V
	m_pKeyboard->Update();
	//�W���C�p�b�h�̍X�V
	m_pJoyPad->Update();
}

//*************************************************************************************
//�C���v�b�g�̐���
//*************************************************************************************
CInput *CInput::Create()
{
	//Input�̎��Ȑ���
	m_pInput = new CInput;
	return m_pInput;
}

//*************************************************************************************
// �S�f�o�C�X�̓��͂��m�F
//*************************************************************************************
bool CInput::KeyChackAll(STAN_DART_INPUT_KEY key, int type)
{
	// Standart
	auto Standart = [this, type](STAN_DART_INPUT_KEY a)
	{
		switch (type)
		{
		case 1:
			return Press(a);
			break;
		case 2:
			return Trigger(a);
			break;
		case 3:
			return Release(a);
			break;
		default:
			break;
		}
		return false;
	};

	// keyboard
	auto Keyboard = [this, type](int a)
	{
		switch (type)
		{
		case 1:
			return Press(a);
			break;
		case 2:
			return Trigger(a);
			break;
		case 3:
			return Release(a);
			break;
		default:
			break;
		}
		return false;
	};

	// Joupad
	auto Joypad = [this, type](DirectJoypad a)
	{
		switch (type)
		{
		case 1:
			return Press(a);
			break;
		case 2:
			return Trigger(a);
			break;
		case 3:
			return Release(a);
			break;
		default:
			break;
		}
		return false;
	};

	switch (key)
	{
	case KEY_UP:
		return Keyboard(DIK_W) || Keyboard(DIK_UP) || Joypad(JOYPAD_UP);
		break;
	case KEY_DOWN:
		return Keyboard(DIK_S) || Keyboard(DIK_DOWN) || Joypad(JOYPAD_DOWN);
		break;
	case KEY_LEFT:
		return Keyboard(DIK_A) || Keyboard(DIK_LEFT) || Joypad(JOYPAD_LEFT);
		break;
	case KEY_RIGHT:
		return Keyboard(DIK_D) || Keyboard(DIK_RIGHT) || Joypad(JOYPAD_RIGHT);
		break;
	case KEY_DECISION:
		return Keyboard(DIK_RETURN) || Joypad(JOYPAD_A);
		break;
	case KEY_SHOT:
		return Keyboard(DIK_SPACE) || Joypad(JOYPAD_R1);
		break;
	case KEY_BACK:
		return Keyboard(DIK_BACKSPACE) || Keyboard(DIK_B) || Joypad(JOYPAD_BACK) || Joypad(JOYPAD_B);
		break;
	case KEY_SHIFT:
		return Keyboard(DIK_RSHIFT) || Keyboard(DIK_LSHIFT) || Joypad(JOYPAD_L1);
		break;
	case KEY_MOVE:
		return Standart(KEY_UP) || Standart(KEY_DOWN) || Standart(KEY_LEFT) || Standart(KEY_RIGHT);
		break;
	case KEY_PAUSE:
		return Keyboard(DIK_P) || Joypad(JOYPAD_START);
		break;
	default:
		break;
	}

	// �\�肳��ĂȂ��L�[���Ă΂ꂽ
	assert(false);
	return false;
}

//*************************************************************************************
// �w�肵���f�o�C�X�̓��͂��m�F
//*************************************************************************************
bool CInput::KeyChackNum(STAN_DART_INPUT_KEY key, int type, int nNum)
{
	// Standart
	auto Standart = [this, type](STAN_DART_INPUT_KEY key, int num)
	{
		switch (type)
		{
		case 1:
			return Press(key, num);
			break;
		case 2:
			return Trigger(key, num);
			break;
		case 3:
			return Release(key, num);
			break;
		default:
			break;
		}
		return false;
	};

	// keyboard
	auto Keyboard = [this, type](int key)
	{
		switch (type)
		{
		case 1:
			return Press(key);
			break;
		case 2:
			return Trigger(key);
			break;
		case 3:
			return Release(key);
			break;
		default:
			break;
		}
		return false;
	};

	// Joupad
	auto Joypad = [this, type](DirectJoypad key, int num)
	{
		switch (type)
		{
		case 1:
			return Press(key, num);
			break;
		case 2:
			return Trigger(key, num);
			break;
		case 3:
			return Release(key, num);
			break;
		default:
			break;
		}
		return false;
	};

	switch (key)
	{
	case KEY_UP:
		return nNum == -1 ? Keyboard(DIK_W) || Keyboard(DIK_UP) : Joypad(JOYPAD_UP, nNum);
		break;
	case KEY_DOWN:
		return nNum == -1 ? Keyboard(DIK_S) || Keyboard(DIK_DOWN) : Joypad(JOYPAD_DOWN, nNum);
		break;
	case KEY_LEFT:
		return nNum == -1 ? Keyboard(DIK_A) || Keyboard(DIK_LEFT) : Joypad(JOYPAD_LEFT, nNum);
		break;
	case KEY_RIGHT:
		return nNum == -1 ? Keyboard(DIK_D) || Keyboard(DIK_RIGHT) : Joypad(JOYPAD_RIGHT, nNum);
		break;
	case KEY_MOVE_UP:
		return nNum == -1 ? Keyboard(DIK_W) : Joypad(JOYPAD_UP, nNum);
		break;
	case KEY_MOVE_DOWN:
		return nNum == -1 ? Keyboard(DIK_S) : Joypad(JOYPAD_DOWN, nNum);
		break;
	case KEY_MOVE_LEFT:
		return nNum == -1 ? Keyboard(DIK_A) : Joypad(JOYPAD_LEFT, nNum);
		break;
	case KEY_MOVE_RIGHT:
		return nNum == -1 ? Keyboard(DIK_D) : Joypad(JOYPAD_RIGHT, nNum);
		break;
	case KEY_SHOT_UP:
		return nNum == -1 ? Keyboard(DIK_UP) : Joypad(JOYPAD_Y, nNum);
		break;
	case KEY_SHOT_DOWN:
		return nNum == -1 ? Keyboard(DIK_DOWN) : Joypad(JOYPAD_A, nNum);
		break;
	case KEY_SHOT_LEFT:
		return nNum == -1 ? Keyboard(DIK_LEFT) : Joypad(JOYPAD_X, nNum);
		break;
	case KEY_SHOT_RIGHT:
		return nNum == -1 ? Keyboard(DIK_RIGHT) : Joypad(JOYPAD_B, nNum);
		break;
	case KEY_DECISION:
		return nNum == -1 ? Keyboard(DIK_RETURN) : Joypad(JOYPAD_A, nNum);
		break;
	case KEY_SHOT:
		return nNum == -1 ? Keyboard(DIK_SPACE) : Joypad(JOYPAD_R1, nNum);
		break;
	case KEY_BACK:
		return nNum == -1 ? Keyboard(DIK_BACKSPACE) || Keyboard(DIK_B) : Joypad(JOYPAD_BACK, nNum) || Joypad(JOYPAD_B, nNum);
		break;
	case KEY_MOVE:
		return Standart(KEY_UP, nNum) || Standart(KEY_DOWN, nNum) || Standart(KEY_LEFT, nNum) || Standart(KEY_RIGHT, nNum);
		break;
	case KEY_PAUSE:
		return nNum == -1 ? Keyboard(DIK_P) : Joypad(JOYPAD_START, nNum) || Joypad(JOYPAD_HOME, nNum);
		break;
	default:
		break;
	}

	// �\�肳��ĂȂ��L�[���Ă΂ꂽ
	assert(false);
	return false;
}

//*************************************************************************************
// ���͂����f�o�C�X�̔ԍ����擾 (Press)
//*************************************************************************************
std::vector<int> CInput::PressDevice(STAN_DART_INPUT_KEY key)
{
	std::vector<int> inputedDeviceIndex;

	// �L�[�{�[�h���͂̒���
	if (Release(key, -1))
	{
		inputedDeviceIndex.push_back(-1);
	}

	// JoyPad���͂̒���
	for (int i = 0;i < m_pJoyPad->GetJoyPadNumMax();i++)
	{
		if (Release(key, i))
		{
			inputedDeviceIndex.push_back(i);
		}
	}
	
	return inputedDeviceIndex;
}

//*************************************************************************************
// ���͂����f�o�C�X�̔ԍ����擾 (Trigger)
//*************************************************************************************
std::vector<int> CInput::TriggerDevice(STAN_DART_INPUT_KEY key)
{
	std::vector<int> inputedDeviceIndex;

	// �L�[�{�[�h���͂̒���
	if (Trigger(key, -1))
	{
		inputedDeviceIndex.push_back(-1);
	}

	// JoyPad���͂̒���
	for (int i = 0; i < m_pJoyPad->GetJoyPadNumMax(); i++)
	{
		if (Trigger(key, i))
		{
			inputedDeviceIndex.push_back(i);
		}
	}

	return inputedDeviceIndex;
}

//*************************************************************************************
// ���͂����f�o�C�X�̔ԍ����擾 (Release)
//*************************************************************************************
std::vector<int> CInput::ReleaseDevice(STAN_DART_INPUT_KEY key)
{
	std::vector<int> inputedDeviceIndex;

	// �L�[�{�[�h���͂̒���
	if (Release(key, -1))
	{
		inputedDeviceIndex.push_back(-1);
	}

	// JoyPad���͂̒���
	for (int i = 0; i < m_pJoyPad->GetJoyPadNumMax(); i++)
	{
		if (Release(key, i))
		{
			inputedDeviceIndex.push_back(i);
		}
	}

	return inputedDeviceIndex;
}

//*************************************************************************************
//�v���X����(�L�[�{�[�h)
//*************************************************************************************
bool CInput::Press(int nKey)
{
	return m_pKeyboard->GetPress(nKey);
}

//*************************************************************************************
//�g���K�[����(�L�[�{�[�h)
//*************************************************************************************
bool CInput::Trigger(int nkey)
{
	return m_pKeyboard->GetTrigger(nkey);
}

//*************************************************************************************
//�����[�X����(�L�[�{�[�h)
//*************************************************************************************
bool CInput::Release(int nkey)
{
	return m_pKeyboard->GetRelease(nkey);
}

bool CInput::Press(DirectJoypad key)
{
	return m_pJoyPad->GetPressAll(key);
}

bool CInput::Trigger(DirectJoypad key)
{
	return m_pJoyPad->GetTriggerAll(key);
}

bool CInput::Release(DirectJoypad key)
{
	return m_pJoyPad->GetReleaseAll(key);
}

//*************************************************************************************
//�v���X����(�W���C�p�b�h)
//*************************************************************************************
bool CInput::Press(DirectJoypad key, int nNum)
{
	return m_pJoyPad->GetPress(key, nNum);
}

//*************************************************************************************
//�g���K�[����(�W���C�p�b�h)
//*************************************************************************************
bool CInput::Trigger(DirectJoypad key, int nNum)
{
	return m_pJoyPad->GetTrigger(key, nNum);
}

//*************************************************************************************
//�����[�X����(�W���C�p�b�h)
//*************************************************************************************
bool CInput::Release(DirectJoypad key, int nNum)
{
	return m_pJoyPad->GetRelease(key, nNum);
}

//*************************************************************************************
//�\���L�[�̃x�N�g��
//*************************************************************************************
D3DXVECTOR3 CInput::VectorMoveKey()
{
	D3DXVECTOR3 VectorMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_pJoyPad->GetJoyPadNumMax() == 0)
	{
		return VectorMove;
	}
	int nCheck = m_pJoyPad->GetCross();

	if (nCheck > 360 || nCheck < 0)
	{//�\���L�[�̊p�x���w��O��������O��Ԃ�
		return VectorMove;
	}

	float fRot = D3DXToRadian(nCheck);

	VectorMove.x = sinf(fRot);
	VectorMove.y = -cosf(fRot);

	//�����P�̃x�N�g���ϊ�
	D3DXVec3Normalize(&VectorMove, &VectorMove);

	return VectorMove;
}

//*************************************************************************************
//�W���C�X�e�B�b�N�̃x�N�g��
//*************************************************************************************
D3DXVECTOR3 CInput::VectorMoveJoyStick(int nNum, bool bleftandright)
{
	D3DXVECTOR3 VectorMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_pJoyPad->GetJoyPadNumMax() == 0)
	{
		return VectorMove;
	}

	VectorMove = m_pJoyPad->GetJoyStickData(nNum, bleftandright);
	//�����P�̃x�N�g���ϊ�
	D3DXVec3Normalize(&VectorMove, &VectorMove);
	return VectorMove;
}

int CInput::GetAcceptJoyPadCount()
{
	return m_pJoyPad->GetJoyPadNumMax();
}
