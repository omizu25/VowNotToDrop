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
	static CObstacle* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& rot);	// ����

	/* �������o�֐��� */
public:
	CObstacle();			// �f�t�H���g�R���X�g���N�^
	~CObstacle() override;	// �f�X�g���N�^

public: 
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	void SetMove(const D3DXVECTOR3& move);	// �ړ��ʂ̐ݒ�
	const D3DXVECTOR3& GetMove() const;		// �ړ��ʂ̎擾

private:
	void Shield(const D3DXVECTOR3& pos);	// �V�[���h�Ƃ̔���

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
	bool m_collision;	// �����蔻��
};

#endif // !_OBSTACLE_H_
