//**************************************************
// 
// fade.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _FADE_H_	//���̃}�N����`������ĂȂ�������
#define _FADE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object2D.h"
#include "mode.h"

//==================================================
// �N���X
//==================================================
class CFade : public CObject2D
{
	/* ��` */
public:
	enum EState
	{
		STATE_NONE = -1,
		STATE_IN = 0,	// �C��
		STATE_OUT,		// �A�E�g
		STATE_MAX
	};

	/* ���ÓI�����o�֐��� */
public:
	static CFade* Create();	// ����

	/* �������o�֐��� */
public:
	CFade();			// �f�t�H���g�R���X�g���N�^
	~CFade() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	void ChangeMode(CMode::EMode nextMode);	// ���[�h�̕ύX
	EState GetState();	// ��Ԃ̎擾

private:
	void In();	// �C��
	void Out();	// �A�E�g

	/* �������o�ϐ��� */
private:
	CMode::EMode m_mode;	// �ύX���郂�[�h
	EState m_state;			// ���
};

#endif // !_FADE_H_
