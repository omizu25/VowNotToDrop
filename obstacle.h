//**************************************************
// 
// obstacle.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBSTACLE_H_	//���̃}�N����`������ĂȂ�������
#define _OBSTACLE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "model.h"

//==================================================
// �N���X
//==================================================
class CObstacle : public CModel
{
	/* ����`�� */
public:
	
	/* ���ÓI�����o�֐��� */
public:
	static CObstacle* Create();	// ����

	/* �������o�֐��� */
public:
	CObstacle();			// �f�t�H���g�R���X�g���N�^
	~CObstacle() override;	// �f�X�g���N�^

public: 
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
};

#endif // !_OBSTACLE_H_
