//**************************************************
// 
// file_x_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _FILE_X_MANAGER_H_	//���̃}�N����`������ĂȂ�������
#define _FILE_X_MANAGER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �O���錾
//==================================================
class CFileX;

//==================================================
// �N���X
//==================================================
class CFileXManager
{
	/* ����`�� */
public:
	enum ELabel
	{
		LABEL_NONE = -1,	// �g�p���Ȃ�
		LABEL_Hummar = 0,	// �n���}�[
		LABEL_WoodBox,		// �ؔ�
		LABEL_Fish_Tail,	// ���̐K��
		LABEL_Fish_Body,	// ���̐g��
		LABEL_Angel_Body,				// �V�g�̑�
		LABEL_Angel_Head,				// �V�g�̓�
		LABEL_Angel_RightArmTop,		// �V�g�̉E�r��
		LABEL_Angel_RightArmBottom,		// �V�g�̉E�r��
		LABEL_Angel_RightHand,			// �V�g�̉E��
		LABEL_Angel_LeftArmTop,			// �V�g�̍��r��
		LABEL_Angel_LeftArmBottom,		// �V�g�̍��r��
		LABEL_Angel_LeftHand,			// �V�g�̍���
		LABEL_Angel_RightFootTop,		// �V�g�̉E����
		LABEL_Angel_RightFootBottom,	// �V�g�̉E����
		LABEL_Angel_RightFoot,			// �V�g�̉E��
		LABEL_Angel_LeftFootTop,		// �V�g�̍�����
		LABEL_Angel_LeftFootBottom,		// �V�g�̍�����
		LABEL_Angel_LeftFoot,			// �V�g�̍���
		LABEL_Terutreu_Rope,			// �Ă�Ă�̓�
		LABEL_Terutreu_Head,			// �Ă�Ă�̓�
		LABEL_Terutreu_Body,			// �Ă�Ă�̑�
		LABEL_Terutreu_Right_ear,		// �Ă�Ă�̉E��
		LABEL_Terutreu_Left_ear,		// �Ă�Ă�̍���
		LABEL_Terutreu_Angel_ring,		// �Ă�Ă�̓V�g�̗�
		LABEL_Terutreu_Angel_wing,		// �Ă�Ă�̓V�g�̉H
		LABEL_Terutreu_Devil_wing,		// �Ă�Ă�̈����̉H
		LABEL_Terutreu_Morning_koko,	// �Ă�Ă�̒��R�R
		LABEL_MAX
	};

	/* �������o�֐��� */
public:
	CFileXManager();	// �f�t�H���g�R���X�g���N�^
	~CFileXManager();	// �f�X�g���N�^

public:
	void LoadAll();						// �S�Ă̓ǂݍ���
	void Load(ELabel label);			// �w��̓ǂݍ���
	void Load(const string& str);		// �w��̓ǂݍ���
	void ReleaseAll();					// �S�Ă̔j��
	void Release(ELabel label);			// �w��̔j��
	void Release(const string& str);	// �w��̔j��
	CFileX* Get(ELabel label);			// ���̎擾
	CFileX* Get(const string& str);		// ���̎擾
	const string& Change(ELabel label);	// �ϊ�
	ELabel Change(const string& str);	// �ϊ�

	/* �������o�ϐ��� */
private:
	CFileX* m_pFileX[LABEL_MAX];	// X�t�@�C���̏��
};

#endif // !_FILE_X_MANAGER_H_
