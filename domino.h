//**************************************************
// 
// domino.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _DOMINO_H_	//���̃}�N����`������ĂȂ�������
#define _DOMINO_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "model.h"

//==================================================
// �N���X
//==================================================
class CDomino : public CModel
{
	/* ����`�� */
public:

	/* ���ÓI�����o�֐��� */
private:
	static float m_move;	// �ړ���
	static int m_count;		// �J�E���g

	/* ���ÓI�����o�֐��� */
public:
	static int GetCount();	// �擾
	static void SetCount(int score);	// �ݒ�
	static void AddCount();	// ���Z
	static float GetMove();
	static void AddMove();		// ���x�̉��Z
	static void CreateAll();	// �S�Ă̐���
	static CDomino* Create(const D3DXVECTOR3& pos);	// ����

	/* �������o�֐��� */
public:
	CDomino();				// �f�t�H���g�R���X�g���N�^
	~CDomino() override;	// �f�X�g���N�^

public: 
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

	/* �������o�ϐ��� */
private:
};

#endif // !_DOMINO_H_
