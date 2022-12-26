//**************************************************
// 
// object3D.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "object3D.h"
#include "application.h"

//==================================================
// ��`
//==================================================
namespace
{
const int NUM_VERTEX = 4;		// ���_�̐�
const int NUM_POLYGON = 2;		// �|���S���̐�
const float STD_SIZE = 100.0f;	// ��̃T�C�Y
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CObject3D* CObject3D::Create()
{
	CObject3D* pObject3D = new CObject3D;

	if (pObject3D == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pObject3D->Init();

	// �T�C�Y�̐ݒ�
	pObject3D->SetSize(D3DXVECTOR3(STD_SIZE, 0.0f, STD_SIZE));

	return pObject3D;
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CObject3D::CObject3D(CObject::EPriority prio) : CObject(prio),
	m_pVtxBuff(nullptr),
	m_texture(CTexture::LABEL_NONE),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
{
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObject3D::~CObject3D()
{
	assert(m_pVtxBuff == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CObject3D::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_texture = CTexture::LABEL_NONE;

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX* pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CObject3D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CObject3D::Update()
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CObject3D::Draw()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX);

	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->Get(m_texture));

	D3DXMATRIX mtxTrans, mtxRot;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`�悷��ŏ��̒��_�C���f�b�N�X
		NUM_POLYGON);			// �v���~�e�B�u(�|���S��)��

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void CObject3D::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CObject3D::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// �T�C�Y�̐ݒ�
//--------------------------------------------------
void CObject3D::SetSize(const D3DXVECTOR3& size)
{
	m_size = size;

	VERTEX* pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float width = m_size.x * 0.5f;
	float height = m_size.y * 0.5f;
	float depth = m_size.z * 0.5f;

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-width, +height, +depth);
	pVtx[1].pos = D3DXVECTOR3(+width, +height, +depth);
	pVtx[2].pos = D3DXVECTOR3(-width, -height, -depth);
	pVtx[3].pos = D3DXVECTOR3(+width, -height, -depth);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �T�C�Y�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CObject3D::GetSize() const
{
	return m_size;
}

//--------------------------------------------------
// �����̐ݒ�
//--------------------------------------------------
void CObject3D::SetRot(const D3DXVECTOR3& rot)
{
	m_rot = rot;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
const D3DXVECTOR3& CObject3D::GetRot() const
{
	return m_rot;
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void CObject3D::SetCol(const D3DXCOLOR& col)
{
	m_col = col;

	VERTEX* pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
const D3DXCOLOR& CObject3D::GetCol() const
{
	return m_col;
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CObject3D::SetTexture(CTexture::ELabel texture)
{
	m_texture = texture;
}

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
//--------------------------------------------------
void CObject3D::SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2& v)
{
	VERTEX* pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(u.x, v.x);
	pVtx[1].tex = D3DXVECTOR2(u.y, v.x);
	pVtx[2].tex = D3DXVECTOR2(u.x, v.y);
	pVtx[3].tex = D3DXVECTOR2(u.y, v.y);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
