//=============================================================================
//
// ���͏��� [directinput.h]
// Author1 : KOZUNA HIROHITO
//
//=============================================================================

#ifndef _DIRECTINPUT_H_		//���̃}�N����`������Ȃ�������
#define _DIRECTINPUT_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
// ���C�u�����[�t�@�C���̃����N
//----------------------------------------------------------------------------
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v(�L�[�{�[�h)
#pragma comment(lib,"dxguid.lib")//DirectX�R���|�[�l���g�Ɏg�p

//----------------------------------------------------------------------------
// include
//----------------------------------------------------------------------------
#include <Windows.h>
#include <d3dx9.h>
#define	 DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���΍��p�}�N��(���̈ʒu���瓮�����Ȃ�)
#include <dinput.h>						//���͏����ɕK�v

//----------------------------------------------------------------------------
// �N���X��`
//----------------------------------------------------------------------------
class CDirectInput
{
public:
	CDirectInput();
	virtual ~CDirectInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd) = 0;	// �h����p�̏�����
	virtual void Uninit(void) = 0;								// �h����p�̏I������
	virtual void Update(void) = 0;								// �h����p�̍X�V����

	static HRESULT Create(HINSTANCE hInstance, HWND hWnd);		// DirectInput�I�u�W�F�N�g�̐���
	static void Break(void);									// DirectInput�I�u�W�F�N�g�̔j��

protected:
	static LPDIRECTINPUT8 m_pInput;	// DirectInput�I�u�W�F�N�g�ւ̃|�C���^

private:

};
#endif