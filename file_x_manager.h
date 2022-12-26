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
		LABEL_NONE = -1,		// �g�p���Ȃ�
		LABEL_NeedleBall = 0,	// �S��
		LABEL_Daruma_Head,		// �_���}�̓�
		LABEL_Daruma_Body,		// �_���}�̐g��
		LABEL_WING,				// �H��
		LABEL_HUMMER,			// �n���}�[
		LABEL_BAMBOO,			// �叼
		LABEL_Hagoita,			// �H�q��
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
