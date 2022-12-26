//**************************************************
// 
// model.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODEL_H_	//���̃}�N����`������ĂȂ�������
#define _MODEL_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include "file_x_manager.h"

//==================================================
// �N���X
//==================================================
class CModel : public CObject
{
	/* ����`�� */
public:
	
	/* ���ÓI�����o�֐��� */
public:
	static CModel* Create(CFileXManager::ELabel label);	// ����

	/* �������o�֐��� */
public:
	CModel();			// �f�t�H���g�R���X�g���N�^
	~CModel() override;	// �f�X�g���N�^

public: 
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	void SetPos(const D3DXVECTOR3& pos);			// �ʒu�̐ݒ�
	const D3DXVECTOR3& GetPos() const;				// �ʒu�̎擾
	void SetRot(const D3DXVECTOR3& rot);			// �����̐ݒ�
	const D3DXVECTOR3& GetRot() const;				// �����̎擾
	void SetLabel(CFileXManager::ELabel label);		// �g�p���郂�f���̐ݒ�
	CFileXManager::ELabel SetLabel();				// �g�p���郂�f���̎擾
	void SetQuaternion(const D3DXVECTOR3& move);	// �N�H�[�^�j�I���̐ݒ�
	void SetIsQuaternion(bool quaternion);			// �N�H�[�^�j�I�����g�p���邩�ǂ����̐ݒ�

private:
	void ShadowDraw(D3DXMATRIX mtxWorld);	// �e�̕`��

	/* �������o�ϐ��� */
private:
	D3DXQUATERNION m_quaternion;	// �N�H�[�^�j�I��
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_rot;				// ����
	CFileXManager::ELabel m_label;	// �g�p���郂�f��
	bool m_isQuaternion;	// �N�H�[�^�j�I�����g�p���邩�ǂ���
};

#endif // !_MODEL_H_
