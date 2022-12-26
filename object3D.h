//**************************************************
// 
// object3D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT3D_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT3D_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include "texture.h"

//==================================================
// �N���X
//==================================================
class CObject3D : public CObject
{
	/* ����`�� */
public:
	struct VERTEX
	{// ���_�f�[�^
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	};

	// ���_�t�H�[�}�b�g
	static const DWORD FVF_VERTEX = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	/* ���ÓI�����o�֐��� */
public:
	static CObject3D* Create();	// ����

	/* �������o�֐��� */
public:
//	CObject3D() = delete;	// �f�t�H���g�R���X�g���N�^
	explicit CObject3D(CObject::EPriority prio = CObject::PRIORITY_3D);	// �R���X�g���N�^
	~CObject3D() override;	// �f�X�g���N�^

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
	void SetRot(const D3DXVECTOR3& rot);		// �����̐ݒ�
	const D3DXVECTOR3& GetRot() const;			// �����̎擾
	void SetCol(const D3DXCOLOR& col);			// �F�̐ݒ�
	const D3DXCOLOR& GetCol() const;			// �F�̎擾
	void SetTexture(CTexture::ELabel texture);	// �e�N�X�`���̐ݒ�
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2& v);	// �e�N�X�`�����W�̐ݒ�

	/* �������o�ϐ��� */
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	CTexture::ELabel m_texture;	// �e�N�X�`���̗񋓌^
	D3DXVECTOR3 m_size;	// �T�C�Y
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXCOLOR m_col;	// �F
};

#endif // !_OBJECT3D_H_
