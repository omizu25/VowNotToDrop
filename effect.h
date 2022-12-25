//**************************************************
// 
// effect.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_H_	//���̃}�N����`������ĂȂ�������
#define _EFFECT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// ��`
//==================================================
class CEffect
{
	/* ��` */
public:
	static const int MAX_EFFECT = 30000;	// �G�t�F�N�g�̍ő吔

	/* ���ÓI�����o�֐��� */
public:
	static CEffect* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col);	// ����
	static void ReleaseAll();		// �S�Ẳ��
	static void UpdateAll();		// �S�Ă̍X�V
	static int GetNumAll();			// �����̎擾
	static CEffect** GetEffect();	// �G�t�F�N�g�̏��̎擾
	static void Explosion(const D3DXVECTOR3& pos);	// ����

	/* ���ÓI�����o�ϐ��� */
private:
	static CEffect* m_pEffect[MAX_EFFECT];	// �G�t�F�N�g�̏��
	static int m_numAll;	// ����

	/* �������o�֐��� */
public:
	CEffect();	// �f�t�H���g�R���X�g���N�^
	~CEffect();	// �f�X�g���N�^

public:
	void Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V

private:
	void Release();	// ���

public:
	const D3DXVECTOR3& GetPos() const;	// �ʒu�̎擾
	const D3DXCOLOR& GetCol() const;	// �F�̎擾
	const D3DXVECTOR3& GetMove() const;	// �ړ��ʂ̎擾
	const D3DXVECTOR2& GetSize() const;	// �T�C�Y�̎擾

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR2 m_size;	// �T�C�Y
	D3DXCOLOR m_col;	// �F
	int m_life;			// ����
	int m_index;		// �ԍ�
};

#endif // !_EFFECT_H_
