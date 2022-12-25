//**************************************************
// 
// menu.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MENU_H_	//���̃}�N����`������ĂȂ�������
#define _MENU_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include "texture.h"

//==================================================
// �O���錾
//==================================================
class CObject2D;

//==================================================
// ��`
//==================================================
class CMenu : public CObject
{
	/* ����`�� */
public:
	
	/* ���ÓI�����o�֐��� */
public:
	//--------------------------------------------------
	// ����
	// pos / �ʒu
	// size / �T�C�Y
	// num / �I�����̐�
	// interval / �Ԋu
	// cursor / �J�[�\�����g�����ǂ���
	//--------------------------------------------------
	static CMenu* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int num, float interval);

	/* �������o�֐��� */
public:
	CMenu();			// �f�t�H���g�R���X�g���N�^
	~CMenu() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	int Select();	// �I��
	void SetCursor(const D3DXVECTOR3& size, float interval);	// �J�[�\���̐ݒ�
	void SetFrame(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col);	// �g�̐ݒ�
	void SetTexture(int idx, CTexture::ELabel label);	// �e�N�X�`���̐ݒ�
	void SetSize(int idx, const D3DXVECTOR3& size);		// �T�C�Y�̐ݒ�
	int GetSelectIdx();	// �I������Ă���ԍ��̎擾

private:
	void Set(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int num, float interval);	// �ݒ�
	void Input();		// ����
	void Alpha();		// ���l
	void Add(int add);	// ���Z

	/* �������o�ϐ��� */
private:
	CObject2D** m_pOption;	// �I����
	CObject2D* m_pFrame;	// �g
	CObject2D* m_pCursor;	// �J�[�\��
	int m_index;	// �I������Ă���ԍ�
	int m_num;		// �I�����̐�
	int m_time;		// �^�C��
	float m_alpha;	// ���l
};

#endif // !_MENU_H_
