//======================================================
//
// �V�[���h�w�b�_�[
// Author : Sato Teruto
//
//======================================================
#ifndef _SHIELD_H_
#define _SHIELD_H_	//��d�C���N���[�h�h�~

//-----------------------------
// �C���N���[�h
//-----------------------------
#include "model.h"

//================================
// �V�[���h�N���X�̒�`
//================================
class CShield : public CModel
{
public:
	CShield();		//�R���X�g���N�^
	~CShield();		//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static void CreateAll();
	static CShield* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int index);

private:
	void Move(int index);		//�ړ�
	void ResetMove(int index);	//�ړ����Z�b�g

private:
	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_defaultPos;	//�����ʒu
	D3DXVECTOR3 m_rot;			//����
	int m_index;				//�ԍ�

	//------------------
	// �ÓI�����o�ϐ�
	//------------------
	static bool bPop[3];	//�o�����
};

#endif