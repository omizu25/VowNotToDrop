//**************************************************
// 
// player.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PLAYER_H_	//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "model.h"

//==================================================
// �N���X
//==================================================
class CPlayer : public CModel
{
	/* ����`�� */
public:

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_killCount;	// �L���J�E���g

	/* ���ÓI�����o�֐��� */
public:
	static void CreateAll();	// �S�Ă̐���
	static CPlayer* Create(int index, float posDest);	// ����
	static void AddKill();	// �L���J�E���g�̉��Z

	/* �������o�֐��� */
public:
	CPlayer();				// �f�t�H���g�R���X�g���N�^
	~CPlayer() override;	// �f�X�g���N�^

public: 
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:

	/* �������o�ϐ��� */
private:
	int m_index;	// �ԍ�
	float m_posDest;	// �ړI�̈ʒu
};

#endif // !_OBSTACLE_H_
