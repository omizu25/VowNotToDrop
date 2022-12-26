//**************************************************
// 
// ranking.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RANKING_H_	//���̃}�N����`������ĂȂ�������
#define _RANKING_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

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
class CRanking : public CMode
{
	/* ��` */
public:

	/* �������o�֐��� */
public:
	CRanking();				// �f�t�H���g�R���X�g���N�^
	~CRanking() override;	// �f�X�g���N�^

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

#endif // !_RANKING_H_
