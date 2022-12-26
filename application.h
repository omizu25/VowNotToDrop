//**************************************************
// 
// application.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _APPLICATION_H_	//���̃}�N����`������ĂȂ�������
#define _APPLICATION_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// �O���錾
//==================================================
class CRenderer;
class CSound;
class CTexture;
class CFileXManager;
class CInstancing;
class CFade;

//==================================================
// �N���X
//==================================================
class CApplication
{
	/* ����`�� */
public:
	static const int SCREEN_WIDTH = 1280;	// �X�N���[���̕�
	static const int SCREEN_HEIGHT = 720;	// �X�N���[���̍���

	/* ���ÓI�����o�֐��� */
public:
	static CApplication* GetInstance();	// �C���X�^���X�̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static CApplication* m_pApplication;	// �����̃N���X

	/* �������o�֐��� */
private:
	CApplication();		// �f�t�H���g�R���X�g���N�^

public:
	~CApplication();	// �f�X�g���N�^

public:
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

public:
	CMode::EMode GetModeEnum();
	void SetMode(CMode::EMode mode);	// ���[�h�̐ݒ�
	LPDIRECT3DDEVICE9 GetDevice();		// �f�o�C�X�̎擾
	CRenderer* GetRenderer();			// �����_���[�̎擾
	CSound* GetSound();					// �T�E���h�̎擾
	CTexture* GetTexture();				// �e�N�X�`���̎擾
	CFileXManager* GetFileXManager();	// X�t�@�C���̏��̂܂Ƃ܂�̎擾
	CInstancing* GetInstancing();		// �C���X�^���V���O�̎擾
	CMode* GetMode();					// ���[�h�̎擾
	CFade* GetFade();					// �t�F�[�h�̎擾

	/* �������o�ϐ��� */
private:
	CMode::EMode m_mode;			// ���݂̃��[�h
	CRenderer* m_pRenderer;			// �����_���[�̏��
	CSound* m_pSound;				// �T�E���h�̏��
	CTexture* m_pTexture;			// �e�N�X�`���̏��
	CFileXManager* m_pFileXManager;	// X�t�@�C���̏��̂܂Ƃ܂�
	CInstancing* m_pInstancing;		// �C���X�^���V���O�̏��
	CMode* m_pMode;					// ���[�h�̏��
	CFade* m_pFade;					// �t�F�[�h�̏��
};

#endif // !_APPLICATION_H_
