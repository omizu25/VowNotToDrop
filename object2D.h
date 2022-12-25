//**************************************************
// 
// object2D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT2D_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include "texture.h"

//==================================================
// �N���X
//==================================================
class CObject2D : public CObject
{
	/* ����`�� */
public:

	/* ���ÓI�����o�֐��� */
public:
	static CObject2D* Create();	// ����

	/* �������o�֐��� */
public:
//	CObject2D() = delete;	// �f�t�H���g�R���X�g���N�^
	explicit CObject2D(CObject::EPriority prio = CObject::PRIORITY_2D);	// �R���X�g���N�^
	~CObject2D() override;	// �f�X�g���N�^

public: 
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	void SetPos(const D3DXVECTOR3& pos);		// �ʒu�̐ݒ�
	const D3DXVECTOR3& GetPos() const;			// �ʒu�̎擾
	void SetSize(const D3DXVECTOR3& size);		// �T�C�Y�̐ݒ�
	const D3DXVECTOR3& GetSize() const;			// �T�C�Y�̎擾
	void SetCol(const D3DXCOLOR& col);			// �F�̐ݒ�
	const D3DXCOLOR& GetCol() const;			// �F�̎擾
	void SetRot(float rot);						// �����̐ݒ�
	const float GetRot() const;					// �����̎擾
	void SetDraw(bool draw);					// �`�悷�邩�ǂ����̐ݒ�
	bool GetDraw();								// �`�悷�邩�ǂ����̎擾
	void SetTexture(CTexture::ELabel texture);	// �e�N�X�`���̐ݒ�
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2& v);	// �e�N�X�`�����W�̐ݒ�

private:
	void SetVtxPos();	// ���_���̐ݒ�

	/* �������o�ϐ��� */
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	CTexture::ELabel m_texture;	// �e�N�X�`���̗񋓌^
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_size;	// �T�C�Y
	D3DXCOLOR m_col;	// �F
	float m_rot;		// ����
	bool m_draw;		// �`�悷�邩�ǂ���
};

#endif // !_OBJECT2D_H_
