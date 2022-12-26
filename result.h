//**************************************************
// 
// result.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RESULT_H_	//���̃}�N����`������ĂȂ�������
#define _RESULT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// �O���錾
//==================================================
class CMenu;
class CRankingUI;

//==================================================
// �N���X
//==================================================
class CResult : public CMode
{
	/* ��` */
public:

	/* �������o�֐��� */
public:
	CResult();				// �f�t�H���g�R���X�g���N�^
	~CResult() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

	/* �������o�ϐ��� */
private:
	void Input();	// ����

	/* �����o�ϐ� */
private:
	CMenu* m_pMenu;	// ���j���[�̏��
	CRankingUI* m_pRanking;
};

#endif // !_RESULT_H_
