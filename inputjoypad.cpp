//=============================================================================
//
// ���͏��� [inputjoypad.cpp]
// Author1 : KOZUNA HIROHITO
// input.h���Q�Ƃ𐄏�
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "inputjoypad.h"

//*************************************************************************************
//�R���X�g���N�^
//*************************************************************************************
CInputJoyPad::CInputJoyPad()
{
	ZeroMemory(&m_JoyPadData, sizeof(m_JoyPadData));
	m_nJoyNumCnt = 0;
	m_AllOldKey = DirectJoypad::JOYPAD_MAX;
}

//*************************************************************************************
//�f�X�g���N�^
//*************************************************************************************
CInputJoyPad::~CInputJoyPad()
{
}

//�f�o�C�X��񋓂��ăf�o�C�X���쐬���Ă����R�[���o�b�N�֐�
BOOL CALLBACK CInputJoyPad::EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
{
	HRESULT hr;

	CInputJoyPad *pThis = (CInputJoyPad*)pContext;
	LPDIRECTINPUTDEVICE8 pInputDevice = pThis->GetInputDevice();

	if (pInputDevice != nullptr)
	{
		return E_FAIL;
	}

	hr = m_pInput->CreateDevice(pdidInstance->guidInstance, &pInputDevice, NULL);

	if (FAILED(hr))
	{
		return E_FAIL;
	}
	
	pThis->SetInputDevice(pInputDevice);

	//���̃f�o�C�X�𒲂ׂ�Ƃ���DIENUM_CONTINUE�ŏ��̈��݂̂̏ꍇ��DIENUM_STOP
	return DIENUM_CONTINUE;
}

//�f�o�C�X�ɑ΂��ăX�e�B�b�N�͈͓̔����w��
BOOL CALLBACK CInputJoyPad::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	LPDIRECTINPUTDEVICE8 pInputDevice = (LPDIRECTINPUTDEVICE8)pContext;
	// ���͔͈͂̃Z�b�g
	DIPROPRANGE diprg;
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.lMax = 1000;
	diprg.lMin = -1000;

	// X��
	diprg.diph.dwObj = DIJOFS_X;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// Y��
	diprg.diph.dwObj = DIJOFS_Y;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// Z��
	diprg.diph.dwObj = DIJOFS_Z;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// RX��
	diprg.diph.dwObj = DIJOFS_RX;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// RY��
	diprg.diph.dwObj = DIJOFS_RY;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// RZ��
	diprg.diph.dwObj = DIJOFS_RZ;
	pInputDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
	return DIENUM_CONTINUE;
}

//*************************************************************************************
//������
//*************************************************************************************
HRESULT CInputJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	
	// �f�o�C�X�̗�
	if (FAILED(m_pInput->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		EnumJoysticksCallback,
		this,
		DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (m_JoyPadData[nCnt].pInputDevice == nullptr)
		{
			continue;
		}

		// �f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
		HRESULT hr = m_JoyPadData[nCnt].pInputDevice->SetDataFormat(&c_dfDIJoystick);

		if (FAILED(hr))
		{
			return E_FAIL;
		}

		// �������[�h�̐ݒ�
		if (FAILED(m_JoyPadData[nCnt].pInputDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			return E_FAIL;
		}

		//�f�o�C�X�ɑ΂��ď\���L�[�͈͓̔����w��
		if (FAILED(m_JoyPadData[nCnt].pInputDevice->EnumObjects(EnumAxesCallback,
			m_JoyPadData[nCnt].pInputDevice,
			DIDFT_AXIS)))
		{
			return E_FAIL;
		}

	}
	return S_OK;
}

//*************************************************************************************
//�I������
//*************************************************************************************
void CInputJoyPad::Uninit(void)
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		//���̓f�o�C�X�̕���
		if (m_JoyPadData[nCnt].pInputDevice != nullptr)
		{
			m_JoyPadData[nCnt].pInputDevice->Unacquire();
			m_JoyPadData[nCnt].pInputDevice->Release();
			m_JoyPadData[nCnt].pInputDevice = nullptr;
		}
	}
}

//*************************************************************************************
//�X�V����
//*************************************************************************************
void CInputJoyPad::Update(void)
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (m_JoyPadData[nCnt].pInputDevice == nullptr)
		{
			continue;
		}
		HRESULT hr;
		//�f�o�C�X����f�[�^���擾�ł��邱�Ƃ��m�F���A�m�F�ł��Ȃ������ꍇ�ɂ̓A�N�Z�X�����擾
		hr = m_JoyPadData[nCnt].pInputDevice->Poll();
		if (FAILED(hr))
		{
			hr = m_JoyPadData[nCnt].pInputDevice->Acquire();
			while (hr == DIERR_INPUTLOST)
			{
				hr = m_JoyPadData[nCnt].pInputDevice->Acquire();
			}
		}

		DIJOYSTATE JoyKey;
		//�R���g���[���[�̏�Ԃ��擾
		if (SUCCEEDED(m_JoyPadData[nCnt].pInputDevice->GetDeviceState(sizeof(DIJOYSTATE), &JoyKey)))
		{
			for (int nButtons = 0; nButtons < MAX_JOY_KEY; nButtons++)
			{
				m_JoyPadData[nCnt].aKeyStateTrigger.rgbButtons[nButtons] = ~m_JoyPadData[nCnt].aKeyState.rgbButtons[nButtons] & JoyKey.rgbButtons[nButtons]; //�g���K�[����ۑ�
				m_JoyPadData[nCnt].aKeyStateRelease.rgbButtons[nButtons] = m_JoyPadData[nCnt].aKeyState.rgbButtons[nButtons] & ~JoyKey.rgbButtons[nButtons]; //�g���K�[����ۑ�
			}
			m_JoyPadData[nCnt].aKeyState = JoyKey;//�v���X�����̕ۊ�
			m_JoyPadData[nCnt].nCrossPressRot = (int)(m_JoyPadData[nCnt].aKeyState.rgdwPOV[0] / 100.0f);//�W���C�p�b�h�̏\���L�[�̉�����Ă������
		}
	}
}

//�v���X����
bool CInputJoyPad::GetPress(DirectJoypad eKey,int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (eKey > JOYPAD_HOME)
	{
		return GetCrossPress(eKey, nNum);
	}
	return (m_JoyPadData[nNum].aKeyState.rgbButtons[eKey] & 0x80) ? true : false;
}

//�g���K�[����
bool CInputJoyPad::GetTrigger(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (eKey > JOYPAD_HOME)
	{
		return GetCrossTrigger(eKey, nNum);
	}

	return (m_JoyPadData[nNum].aKeyStateTrigger.rgbButtons[eKey] & 0x80) ? true : false;
}

// �����[�X����
bool CInputJoyPad::GetRelease(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (eKey > JOYPAD_HOME)
	{
		return GetCrossRelease(eKey, nNum);
	}

	return (m_JoyPadData[nNum].aKeyStateRelease.rgbButtons[eKey] & 0x80) ? true : false;
}

//�\���L�[�v���X����
bool CInputJoyPad::GetCrossPress(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	switch (eKey)
	{
	case JOYPAD_UP:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_UP
			|| m_JoyPadData[nNum].aKeyState.lY <= -700
			|| m_JoyPadData[nNum].aKeyState.lRz <= -700)
		{
			return true;
		}
		break;
	case JOYPAD_DOWN:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_DOWN
			|| m_JoyPadData[nNum].aKeyState.lY >= 700
			|| m_JoyPadData[nNum].aKeyState.lRz >= 700)
		{
			return true;
		}
		break;
	case JOYPAD_LEFT:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_LEFT
			|| m_JoyPadData[nNum].aKeyState.lX <= -700
			|| m_JoyPadData[nNum].aKeyState.lZ <= -700)
		{
			return true;
		}
		break;
	case JOYPAD_RIGHT:
		if (m_JoyPadData[nNum].aKeyState.rgdwPOV[0] == JOYKEY_DIRECT_CROSS::JOYKEY_CROSS_RIGHT
			|| m_JoyPadData[nNum].aKeyState.lX >= 700
			|| m_JoyPadData[nNum].aKeyState.lZ >= 700)
		{
			return true;
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}

//�\���L�[�g���K�[����
bool CInputJoyPad::GetCrossTrigger(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (m_JoyPadData[nNum].aOldKey != eKey
		&& GetCrossPress(eKey, nNum))
	{
		m_JoyPadData[nNum].aOldKey = eKey;
		return true;
	}
	else if (m_JoyPadData[nNum].aOldKey == eKey
		&& GetCrossPress(eKey, nNum))
	{
		return false;
	}

	m_JoyPadData[nNum].aOldKey = DirectJoypad::JOYPAD_MAX;
	return false;
}

//�\���L�[�����[�X����
bool CInputJoyPad::GetCrossRelease(DirectJoypad eKey, int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	if (m_JoyPadData[nNum].aOldKey != eKey && !GetCrossPress(eKey, nNum))
	{
		return false;
	}

	else if (m_JoyPadData[nNum].aOldKey == eKey && !GetCrossPress(eKey, nNum))
	{
		m_JoyPadData[nNum].aOldKey = eKey;
		return true;
	}

	m_JoyPadData[nNum].aOldKey = DirectJoypad::JOYPAD_MAX;
	return false;
}

//�I�[���v���X����	�i�L�[�w�肠��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetPressAll(DirectJoypad eKey)
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (GetPress(eKey, nCnt))
		{
			return true;
		}
	}
	return false;
}

//�I�[���g���K�[�����i�L�[�w�肠��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetTriggerAll(DirectJoypad eKey)
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (GetPress(eKey, nCnt) && m_AllOldKey == JOYPAD_MAX)
		{
			m_AllOldKey = eKey;
			return true;
		}
	}

	if (GetPressAll())
	{//�N�����L�[�������Ă�����
		return false;
	}

	m_AllOldKey = JOYPAD_MAX;
	return false;
}

//�I�[�������[�X����	�i�L�[�w�肠��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetReleaseAll(DirectJoypad eKey)
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (GetRelease(eKey, nCnt) && m_AllOldKey == JOYPAD_MAX)
		{
			m_AllOldKey = eKey;
			return true;
		}
	}

	if (GetReleaseAll())
	{//�N�����L�[�������Ă�����
		return false;
	}

	m_AllOldKey = JOYPAD_MAX;
	return false;
}

//�I�[���v���X����	�i�L�[�w��Ȃ��A�v���C���[�w�肠��j
bool CInputJoyPad::GetPressAll(int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	for (int nCntKey = 0; nCntKey < JOYPAD_MAX; nCntKey++)
	{
		if (GetPress((DirectJoypad)nCntKey, nNum))
		{
			return true;
		}
	}
	return false;
}

//�I�[���g���K�[�����i�L�[�w��Ȃ��A�v���C���[�w�肠��j
bool CInputJoyPad::GetTriggerAll(int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}
	
	for (int nCntKey = 0; nCntKey < JOYPAD_MAX; nCntKey++)
	{
		if (GetPress((DirectJoypad)nCntKey,nNum) && m_JoyPadData[nNum].aOldKey != nCntKey)
		{
			m_JoyPadData[nNum].aOldKey = (DirectJoypad)nCntKey;
			return true;
		}
		else if (GetPress((DirectJoypad)nCntKey, nNum) && m_JoyPadData[nNum].aOldKey == nCntKey)
		{
			return false;
		}
	}

	m_JoyPadData[nNum].aOldKey = JOYPAD_MAX;
	return false;
}

//�I�[�������[�X�����i�L�[�w��Ȃ��A�v���C���[�w�肠��j
bool CInputJoyPad::GetReleaseAll(int nNum)
{
	if (m_JoyPadData[nNum].pInputDevice == nullptr)
	{
		return false;
	}

	for (int nCntKey = 0; nCntKey < JOYPAD_MAX; nCntKey++)
	{
		if (GetRelease((DirectJoypad)nCntKey, nNum) && m_JoyPadData[nNum].aOldKey != nCntKey)
		{
			m_JoyPadData[nNum].aOldKey = (DirectJoypad)nCntKey;
			return true;
		}
		else if (GetRelease((DirectJoypad)nCntKey, nNum) && m_JoyPadData[nNum].aOldKey == nCntKey)
		{
			return false;
		}
	}

	m_JoyPadData[nNum].aOldKey = JOYPAD_MAX;
	return false;
}

//�I�[���v���X����	�i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetPressAll()
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (m_JoyPadData[nCnt].pInputDevice == nullptr)
		{
			return false;
		}

		if (GetPressAll(nCnt))
		{
			return true;
		}
	}
	return false;
}

//�I�[���g���K�[�����i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetTriggerAll()
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (m_JoyPadData[nCnt].pInputDevice == nullptr)
		{
			continue;
		}

		for (int nCntKey = 0; nCntKey < JOYPAD_MAX; nCntKey++)
		{
			if (GetPress((DirectJoypad)nCntKey, nCnt))
			{
				if (m_AllOldKey != nCntKey)
				{
					m_AllOldKey = (DirectJoypad)nCntKey;
					return true;
				}
				else if (m_AllOldKey == nCntKey)
				{
					return false;
				}				
			}
		}
	}

	m_AllOldKey = DirectJoypad::JOYPAD_MAX;
	return false;
}

//�I�[�������[�X�����i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
bool CInputJoyPad::GetReleaseAll()
{
	for (int nCnt = 0; nCnt < JOYPAD_DATA_MAX; nCnt++)
	{
		if (m_JoyPadData[nCnt].pInputDevice == nullptr)
		{
			continue;
		}

		for (int nCntKey = 0; nCntKey < JOYPAD_MAX; nCntKey++)
		{
			if (GetRelease((DirectJoypad)nCntKey, nCnt))
			{
				if (m_AllOldKey != nCntKey)
				{
					m_AllOldKey = (DirectJoypad)nCntKey;
					return true;
				}
				else if (m_AllOldKey == nCntKey)
				{
					return false;
				}
			}
		}
	}

	m_AllOldKey = DirectJoypad::JOYPAD_MAX;
	return false;
}

//�W���C�X�e�B�b�N�̒l��Ԃ�
D3DXVECTOR3 CInputJoyPad::GetJoyStickData(int nNum,bool bleftandright)
{
	if (bleftandright)
	{//�X�e�B�b�N�̉E��(true  = �E�Afalse = ��)
		if (m_JoyPadData[nNum].aKeyState.lRz != 0
			|| m_JoyPadData[nNum].aKeyState.lZ != 0)
		{
			return D3DXVECTOR3((float)m_JoyPadData[nNum].aKeyState.lZ, (float)m_JoyPadData[nNum].aKeyState.lRz, 0.0f);
		}

		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}


	if (m_JoyPadData[nNum].aKeyState.lY != 0 
		|| m_JoyPadData[nNum].aKeyState.lX != 0)
	{
		return D3DXVECTOR3((float)m_JoyPadData[nNum].aKeyState.lX, (float)m_JoyPadData[nNum].aKeyState.lY,0.0f);
	}
	
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}
