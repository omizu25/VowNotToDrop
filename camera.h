//**************************************************
// 
// camera.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CAMERA_H_	// ���̃}�N����`������ĂȂ�������
#define _CAMERA_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �N���X/
//==================================================
class CCamera
{
	/* ����`�� */
public:

	/* �������o�֐��� */
public:
	CCamera();	// �f�t�H���g�R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

public:
	void Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Set();		// �ݒ�
	void SetPos(const D3DXVECTOR3& pos);	// �ʒu�̐ݒ�
	const D3DXVECTOR3& GetPos() const;		// �ʒu�̎擾
	const D3DXMATRIX& GetProj() const;		// �v���W�F�N�V�����̎擾
	const D3DXMATRIX& GetView() const;		// �r���[�̎擾

	/* �������o�ϐ��� */
private:
	D3DXMATRIX m_mtxProj;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;	// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_posV;		// ���_
	D3DXVECTOR3 m_posR;		// �����_
	D3DXVECTOR3 m_vecU;		// ������x�N�g��
};

#endif // !_CAMERA_H_
