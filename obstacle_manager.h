//**************************************************
// 
// obstacle_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBSTACLE_MANAGER_H_	// ���̃}�N����`������ĂȂ�������
#define _OBSTACLE_MANAGER_H_	// ��d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"

//==================================================
// �N���X
//==================================================
class CObstacleManager : public CObject
{
	/* ����`�� */
private:
	
	/* ���ÓI�����o�֐��� */
public:
	static CObstacleManager* Create();	// ����

	/* �������o�֐��� */
public:
	CObstacleManager();				// �f�t�H���g�R���X�g���N�^
	~CObstacleManager() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void Game();	// �Q�[��

	/* �������o�ϐ��� */
private:
	int m_time;		// ����
	int m_pop;		// �o����
	int m_interval;	// �Ԋu
	float m_move;	// �ړ���
};

#endif // !_OBSTACLE_MANAGER_H_
