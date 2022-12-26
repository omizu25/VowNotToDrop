//**************************************************
// 
// file_x.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "file_x.h"
#include "application.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CFileX* CFileX::Create(const string& str)
{
	CFileX* pFileX = new CFileX;

	if (pFileX == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pFileX->Init();

	// �ǂݍ���
	pFileX->Load(str);

	return pFileX;
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CFileX::CFileX() :
	m_pTexture(nullptr),
	m_pMesh(nullptr),
	m_pBuffMat(nullptr),
	m_numMat(0),
	m_size(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMin(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vtxMax(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CFileX::~CFileX()
{
	assert(m_pBuffMat == nullptr);
	assert(m_pMesh == nullptr);
	assert(m_pTexture == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CFileX::Init()
{
	m_pTexture = nullptr;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_numMat = 0;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	m_vtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CFileX::Uninit()
{
	if (m_pBuffMat != nullptr)
	{// �}�e���A�����̔j��
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	if (m_pMesh != nullptr)
	{// ���b�V�����̔j��
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	if (m_pTexture != nullptr)
	{// null�`�F�b�N
		for (int i = 0; i < (int)m_numMat; i++)
		{
			if (m_pTexture[i] != nullptr)
			{// �e�N�X�`���̔j��
				m_pTexture[i]->Release();
				m_pTexture[i] = nullptr;
			}
		}

		delete[] m_pTexture;
		m_pTexture = nullptr;
	}
}

//--------------------------------------------------
// �e�N�X�`���̎擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9* CFileX::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// ���b�V�����̎擾
//--------------------------------------------------
LPD3DXMESH CFileX::GetMesh()
{
	return m_pMesh;
}

//--------------------------------------------------
// �}�e���A�����̎擾
//--------------------------------------------------
LPD3DXBUFFER CFileX::GetBuffMat()
{
	return m_pBuffMat;
}

//--------------------------------------------------
// �}�e���A�����̐��̎擾
//--------------------------------------------------
DWORD CFileX::GetNumMat()
{
	return m_numMat;
}

//--------------------------------------------------
// �T�C�Y�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CFileX::GetSize() const
{
	return m_size;
}

//--------------------------------------------------
// �ŏ��l�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CFileX::GetVtxMin() const
{
	return m_vtxMin;
}

//--------------------------------------------------
// �ő�l�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CFileX::GetVtxMax() const
{
	return m_vtxMax;
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CFileX::Load(const string& str)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		str.c_str(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_numMat,
		&m_pMesh);

	// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// ���b�V���Ɏg�p����Ă���e�N�X�`���p�̔z���p�ӂ���
	m_pTexture = new LPDIRECT3DTEXTURE9[m_numMat];

	// �e���b�V���̃}�e���A�������擾����
	for (int i = 0; i < (int)m_numMat; i++)
	{
		if (pMat[i].pTextureFilename != nullptr)
		{// �}�e���A���Őݒ肳��Ă���e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFileA(pDevice,
				pMat[i].pTextureFilename,
				&m_pTexture[i]);
		}
		else
		{// �e�N�X�`���Ȃ�
			m_pTexture[i] = nullptr;
		}
	}
}
