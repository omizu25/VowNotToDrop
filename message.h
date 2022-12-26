//===================================================
//
// ���b�Z�[�W�w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _MESSAGE_H_
#define _MESSAGE_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object2d.h"

//================================
// ���b�Z�[�W�N���X
//================================
class CMessage : public CObject2D
{
public:
	CMessage();				//�R���X�g���N�^
	~CMessage() override;	//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static CMessage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//------------------
	// �萔
	//------------------
	static const int nDeathTime = 120;

	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXCOLOR m_col;	//�F
	int m_nCntTime;		//���ԃJ�E���g
	float m_fWidth;		//��
	float m_fHeight;	//����
};

#endif