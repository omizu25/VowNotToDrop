//**************************************************
// 
// mode.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODE_H_	//���̃}�N����`������ĂȂ�������
#define _MODE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"

//==================================================
// �N���X
//==================================================
class CMode : public CObject
{
	/* ��` */
public:
	enum EMode
	{
		MODE_NONE = -1,
		MODE_TITLE = 0,	// �^�C�g��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_RANKING,	// �����L���O
		MODE_MAX
	};

	/* �ÓI�����o�ϐ� */
public:
	static CMode* Create(EMode mode);	// ����

	/* �������o�֐��� */
public:
	CMode();			// �R���X�g���N�^
	~CMode() override;	// �f�X�g���N�^
	
public:
	virtual void Init() override = 0;	// ������
	virtual void Uninit() override = 0;	// �I��
	virtual void Update() override = 0;	// �X�V
	virtual void Draw() override = 0;	// �`��
	
	/* �������o�ϐ��� */
private:
};

#endif // !_MODE_H_
