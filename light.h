//**************************************************
// 
// light.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _LIGHT_H_	//���̃}�N����`������ĂȂ�������
#define _LIGHT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �N���X
//==================================================
class CLight
{
	/* ����`�� */
private:
	static const int MAX_LIGHT = 3;	// ���C�g�̍ő�l

	/* ���ÓI�����o�֐��� */
public:
	static CLight** CreateAll();	// �S�Ă̐���
	static void ReleaseAll();		// �S�Ẳ��
	static CLight* Get(int num);	// �擾

private:
	static CLight* Create(int index, D3DLIGHTTYPE type, const D3DXCOLOR& col, const D3DXVECTOR3& vec);	// ����

		/* ���ÓI�����o�ϐ��� */
private:
	static CLight* m_pLight[MAX_LIGHT];	// ���C�g�̏��

	/* �������o�֐��� */
public:
	CLight();	// �f�t�H���g�R���X�g���N�^
	~CLight();	// �f�X�g���N�^

public:
	void Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Set(int index, D3DLIGHTTYPE type, const D3DXCOLOR& col, const D3DXVECTOR3& vec);	// �ݒ�
	D3DXVECTOR3 GetDir();	// �����̎擾

	/* �������o�ϐ��� */
private:
	D3DLIGHT9 m_light;	// ���C�g�̏��
};

#endif // !_LIGHT_H_
