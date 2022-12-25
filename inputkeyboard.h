//=============================================================================
//
// ���͏��� [inputkeyboard.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _INPUTKEYBOARD_H_		//���̃}�N����`������Ȃ�������
#define _INPUTKEYBOARD_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "DirectInput.h"
//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInputKeyboard : public CDirectInput
{
private:
	static const int NUM_KEY_MAX = 256;	//�L�[�̍ő吔�i�L�[�{�[�h�j
public:
	CInputKeyboard();
	~CInputKeyboard()override;
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;		// ���͏����S���̏�����
	void Uninit(void)override;									// ���͏����S���̏I������
	void Update(void)override;									// ���͏����S���̍X�V����

	bool GetPress(int nKey);		// �L�[�{�[�h�v���X����
	bool GetTrigger(int nKey);		// �L�[�{�[�h�g���K�[����
	bool GetRelease(int nKey);		// �L�[�{�[�h�����[�X����
	bool GetAllPress(void);			// �L�[�{�[�h�S�L�[�v���X����
	bool GetAllTrigger(void);		// �L�[�{�[�h�S�L�[�g���K�[����
	bool GetAllRelease(void);		// �L�[�{�[�h�S�L�[�����[�X����

private:
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;	// ���̓f�o�C�X�i�L�[�{�[�h�i�R���g���[���[�p�͕ʂɍ��j�j�ւ̃|�C���^
	BYTE m_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X���
};
#endif