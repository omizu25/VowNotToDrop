//**************************************************
// 
// object.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �N���X
//==================================================
class CObject
{
	/* ����`�� */
public:
	enum EPriority
	{
		PRIORITY_NONE = -1,
		PRIORITY_SYSTEM = 0,	// �V�X�e��
		PRIORITY_3D,			// 3D
		PRIORITY_EFFECT,		// �G�t�F�N�g
		PRIORITY_2D,			// 2D
		PRIORITY_FADE,			// �t�F�[�h
		PRIORITY_MAX
	};

	/* ���ÓI�����o�֐��� */
public:
	static void ReleaseAll();	// �S�Ẳ��
	static void UpdateAll();	// �S�Ă̍X�V
	static void DrawAll();		// �S�Ă̕`��
	static int GetNumAll();		// �����̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numAll;	// ����
	static CObject* m_pTop[PRIORITY_MAX];		// �擪
	static CObject* m_pCurrent[PRIORITY_MAX];	// �Ō��

	/* �������o�֐��� */
public:
	CObject() = delete;	// �f�t�H���g�R���X�g���N�^
	explicit CObject(EPriority priority);	// �R���X�g���N�^
	virtual ~CObject();	// �f�X�g���N�^

public:
	virtual void Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��

public:
	void Release();		// ���
	void SetRelease();	// �������
	bool GetRelease();	// ������邩�ǂ����̎擾

	/* �������o�ϐ��� */
private:
	CObject* m_pPrev;		// �O
	CObject* m_pNext;		// ��
	EPriority m_priority;	// �D�揇��
	bool m_release;			// ������邩�ǂ���
};

#endif // !_OBJECT_H_
