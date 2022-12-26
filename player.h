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
	static const int MAX_PLAYER = 3;	// �v���C���[�̍ő吔

	/* ���ÓI�����o�ϐ��� */
private:
	static CPlayer* m_pPlayer[MAX_PLAYER];	// �v���C���[
	static int m_killCount;	// �L���J�E���g

	/* ���ÓI�����o�֐��� */
public:
	static void CreateAll();	// �S�Ă̐���
	static CPlayer* Create(int index, float posDest);	// ����
	static void AddKill(const D3DXVECTOR3& move);	// �L���J�E���g�̉��Z

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
	void SetMove(const D3DXVECTOR3& move);	// �ړ��ʂ̐ݒ�
	const D3DXVECTOR3& GetMove() const;		// �ړ��ʂ̎擾

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
	int m_index;		// �ԍ�
	float m_posDest;	// �ړI�̈ʒu
};

#endif // !_OBSTACLE_H_
