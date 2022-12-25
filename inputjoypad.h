//=============================================================================
//
// ���͏��� [directjoypad.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUTJOYPAD_H_		//���̃}�N����`������Ȃ�������
#define _INPUTJOYPAD_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "DirectInput.h"
#include "inputkeydata.h"

//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInputJoyPad : public CDirectInput
{

private:
	static const int MAX_JOY_KEY = 32;		// �W���C�p�b�h�̎g���ĂȂ��L�[���܂߂��ő吔
	static const int JOYPAD_DATA_MAX = 4;	// �����ڑ��\�ő吔

	//�W���C�p�b�h�̂ЂƂɕK�v�ȏ��̍\����
	struct SJoyPad
	{
		LPDIRECTINPUTDEVICE8 pInputDevice;	// ���̓f�o�C�X�ւ̃|�C���^
		DIJOYSTATE aKeyState;				// �W���C�p�b�h�̃v���X���
		DIJOYSTATE aKeyStateTrigger;		// �W���C�p�b�h�̃g���K�[���
		DIJOYSTATE aKeyStateRelease;		// �W���C�p�b�h�̃����[�X���
		DirectJoypad aOldKey;				// �O�񉟂��ꂽ�L�[�̎��
		int nCrossPressRot;					// �W���C�p�b�h�̏\���L�[�̉�����Ă������
	};

public:
	CInputJoyPad();
	~CInputJoyPad()override;
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;	// �W���C�p�b�h�̏�����
	void Uninit(void) override;								// �W���C�p�b�h�̏I������
	void Update(void) override;								// �W���C�p�b�h�̍X�V����

	//���̓f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECTINPUTDEVICE8 GetInputDevice() { return m_JoyPadData[m_nJoyNumCnt].pInputDevice; }
	LPDIRECTINPUTDEVICE8 GetInputDevice(int nNum) { return m_JoyPadData[nNum].pInputDevice; }

	//���̓f�o�C�X�ւ̃|�C���^�̐ݒ�
	void SetInputDevice(LPDIRECTINPUTDEVICE8 pInputDeviceint) { m_JoyPadData[m_nJoyNumCnt].pInputDevice = pInputDeviceint; m_nJoyNumCnt++;}

	//���ݐڑ�����Ă���W���C�p�b�h�̐��̎擾
	int GetJoyPadNumMax() { return m_nJoyNumCnt; }

	//*�ڑ����m�F���ɍs���R�[���o�b�N�֐�
	//�f�o�C�X���m�F�ł�������𐶐�����R�[���o�b�N�֐�
	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);
	//�m�F���o�����W���C�p�b�h�̃X�e�B�b�N�̌X���̒l�̕��ݒ�
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
	//*

	bool GetPress(DirectJoypad eKey, int nNum);			// �v���X����
	bool GetTrigger(DirectJoypad eKey, int nNum);		// �g���K�[����
	bool GetRelease(DirectJoypad eKey, int nNum);		// �����[�X����
	bool GetCrossPress(DirectJoypad eKey, int nNum);	// �\���L�[�v���X����
	bool GetCrossTrigger(DirectJoypad eKey, int nNum);	// �\���L�[�g���K�[����
	bool GetCrossRelease(DirectJoypad eKey, int nNum);	// �\���L�[�����[�X����
	bool GetPressAll(DirectJoypad eKey);				// �I�[���v���X����		�i�L�[�w�肠��A�v���C���[�w��Ȃ��j
	bool GetTriggerAll(DirectJoypad eKey);				// �I�[���g���K�[����	�i�L�[�w�肠��A�v���C���[�w��Ȃ��j
	bool GetReleaseAll(DirectJoypad eKey);				// �I�[�������[�X����	�i�L�[�w�肠��A�v���C���[�w��Ȃ��j
	bool GetPressAll(int nNum);							// �I�[���v���X����		�i�L�[�w��Ȃ��A�v���C���[�w�肠��j
	bool GetTriggerAll(int nNum);						// �I�[���g���K�[����	�i�L�[�w��Ȃ��A�v���C���[�w�肠��j
	bool GetReleaseAll(int nNum);						// �I�[�������[�X����	�i�L�[�w��Ȃ��A�v���C���[�w�肠��j
	bool GetPressAll();									// �I�[���v���X����		�i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
	bool GetTriggerAll();								// �I�[���g���K�[����	�i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j
	bool GetReleaseAll();								// �I�[�������[�X����	�i�L�[�w��Ȃ��A�v���C���[�w��Ȃ��j

	D3DXVECTOR3 GetJoyStickData(int nNum, bool bleftandright = false);			//�W���C�X�e�B�b�N�̌X���l��Ԃ�(true  = �E�Afalse = ��)
	int GetCross(int nNum = 0) { return m_JoyPadData[nNum].nCrossPressRot; }	//�W���C�p�b�h�̏\���L�[�̉�����Ă������(��@45���Ȃ�)

private:
	SJoyPad m_JoyPadData[JOYPAD_DATA_MAX];		//�W���C�p�b�h�̂ЂƂɕK�v�ȏ��̍\����
	DirectJoypad m_AllOldKey;					//�S�W���C�p�b�h���ʂ̑O�񂳂ꂽ�L�[
	int m_nJoyNumCnt;							//���ݐڑ��̐ڑ���
};
#endif