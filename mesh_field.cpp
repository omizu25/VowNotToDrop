//===================================================
//
// ���b�V���̏���
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "mesh_field.h"
#include "application.h"
#include "renderer.h"
#include "object3D.h"

//=======================
// �R���X�g���N�^
//=======================
CMeshField::CMeshField() : CMeshField(PRIORITY_3D)
{
}
CMeshField::CMeshField(EPriority nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_VtxPos[nMaxVtx] = {};						//���_�̈ʒu
	m_Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʖ@���x�N�g���i�[�p
	m_VtxNor[nMaxVtx] = {};						//���_�̖@���x�N�g���i�[�p
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	m_nNumDivision = 0;		//�|���S���̕�����
	m_nCntVtx = 0;			//���_�̕�����
	m_nNumVtx = 0;			//���_��
	m_nNumPolygon = 0;		//�|���S����
	m_nNumIndex = 0;		//�C���f�b�N�X��
	m_fMaxWidth = 0.0f;		//���b�V���t�B�[���h�̍ő啝
	m_fMeshWidth = 0.0f;	//���b�V���t�B�[���h�̕�
	m_fTexSize = 0.0f;		//�e�N�X�`���̕����T�C�Y

	m_pVtxBuff = nullptr;	//���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = nullptr;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
}

//=======================
// �f�X�g���N�^
//=======================
CMeshField::~CMeshField()
{
	assert(m_pVtxBuff == nullptr);
	assert(m_pIdxBuff == nullptr);
}

//=======================
// ������
//=======================
void CMeshField::Init()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	//----------------------------------
	// ���b�V�����\��������̐ݒ�
	//----------------------------------
	m_nNumDivision = 12;				//�|���S���̕�����
	m_nCntVtx = m_nNumDivision + 1;		//���_�̕�����
	m_nNumVtx = (m_nNumDivision + 1) * (m_nNumDivision + 1);							//���_��
	m_nNumPolygon = m_nNumDivision * m_nNumDivision * 2 + (m_nNumDivision - 1) * 4;		//�|���S����
	m_nNumIndex = (m_nNumDivision + 1) * 2 * m_nNumDivision + (m_nNumDivision - 1) * 2;	//�C���f�b�N�X��
	m_fMaxWidth = 1200.0f;								//���b�V���t�B�[���h�̍ő啝
	m_fMeshWidth = (m_fMaxWidth / m_nNumDivision);		//���b�V���t�B�[���h�̕�
	m_fTexSize = (1.0f / m_nNumDivision);				//�e�N�X�`���̕����T�C�Y


	//----------------------------------
	// ���_�o�b�t�@�̐���
	//----------------------------------
	pDevice->CreateVertexBuffer(sizeof(CObject3D::VERTEX) * m_nNumVtx,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								CObject3D::FVF_VERTEX,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	//----------------------------------
	// �C���f�b�N�X�o�b�t�@�̐���
	//----------------------------------
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								D3DFMT_INDEX16,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&m_pIdxBuff,
								NULL);

	CObject3D::VERTEX* pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//----------------------------------
	// ���_���̐ݒ�
	//----------------------------------
	for (int z = 0; z < m_nCntVtx; z++)
	{
		for (int x = 0; x < m_nCntVtx; x++)
		{
			//���_���W�̐ݒ�
			{
				D3DXVECTOR3 vtxPos(-(m_fMaxWidth / 2) + (m_fMeshWidth * x), 0.0f, (m_fMaxWidth / 2) - (m_fMeshWidth * z));
				pVtx[x + (z * (m_nCntVtx))].pos = vtxPos;
			}

			//�e���_�̖@���̐ݒ�(���x�N�g���̑傫���͕K��1�ɂ���K�v������)
			pVtx[x + (z * (m_nCntVtx))].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[x + (z * (m_nCntVtx))].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[x + (z * (m_nCntVtx))].tex = D3DXVECTOR2(0.0f + m_fTexSize * x, 0.0f + m_fTexSize * z);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//----------------------------------
	// �C���f�b�N�X�̐ݒ�
	//----------------------------------
	int nCnt = 0;

	for (int Z = 0; Z < m_nNumDivision; Z++)
	{
		for (int X = 0; X < m_nCntVtx; X++)
		{
			//�C���f�b�N�X�o�b�t�@�̐ݒ�
			pIdx[nCnt] = (WORD(X + Z * (m_nCntVtx)+(m_nCntVtx)));
			pIdx[nCnt + 1] = (WORD(X + Z * (m_nCntVtx)));

			nCnt += 2;

			//�k�ރ|���S���̒ǉ�
			if (X == m_nNumDivision)
			{
				pIdx[nCnt] = (WORD)(X + Z * m_nCntVtx);
				pIdx[nCnt + 1] = (WORD)((Z + 2) * m_nCntVtx);

				nCnt += 2;
			}
		}
	}

	pVtx += m_nNumVtx;
	pIdx += m_nNumIndex;

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//=======================
// �I��
//=======================
void CMeshField::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//=======================
// �X�V
//=======================
void CMeshField::Update()
{

}

//=======================
// �`��
//=======================
void CMeshField::Draw()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	//------------------------------------
	// �}�g���b�N�X
	//------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//------------------------------------
	// ���_
	//------------------------------------
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject3D::VERTEX));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(CObject3D::FVF_VERTEX);

	//------------------------------------
	// �e�N�X�`��
	//------------------------------------
	//�e�N�X�`���̎擾
	CTexture *pTexture = CApplication::GetInstance()->GetTexture();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->Get(m_texture));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
									0,
									0,
									m_nNumVtx,	//���_��
									0,
									m_nNumPolygon);	//�`�悷��v���~�e�B�u��

	//�e�N�X�`���̃��Z�b�g
	pDevice->SetTexture(0, NULL);
}

//=======================
// ����
//=======================
CMeshField* CMeshField::Create(CTexture::ELabel texture)
{
	CMeshField *pMeshField = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pMeshField = new CMeshField;	//����

	if (pMeshField != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pMeshField->m_texture = texture;

		//������
		pMeshField->Init();
	}

	return pMeshField;
}


//===========================
// �������ƕ��̐ݒ�
//===========================
void CMeshField::SetMeshSize(int nDivision, float fWidth)
{
	m_nNumDivision = nDivision;	//�|���S���̕������̐ݒ�
	m_fMaxWidth = fWidth;		//���b�V���t�B�[���h�̍ő啝�̐ݒ�

	//----------------------------
	// ���b�V���̏��̍Đݒ�
	//----------------------------
	m_nCntVtx = m_nNumDivision + 1;		//���_�̕�����
	m_nNumVtx = (m_nNumDivision + 1) * (m_nNumDivision + 1);							//���_��
	m_nNumPolygon = m_nNumDivision * m_nNumDivision * 2 + (m_nNumDivision - 1) * 4;		//�|���S����
	m_nNumIndex = (m_nNumDivision + 1) * 2 * m_nNumDivision + (m_nNumDivision - 1) * 2;	//�C���f�b�N�X��
	m_fMeshWidth = (m_fMaxWidth / m_nNumDivision);		//���b�V���t�B�[���h�̕�
	m_fTexSize = (1.0f / m_nNumDivision);				//�e�N�X�`���̕����T�C�Y
}

//===========================
// �e�N�X�`���̐ݒ�
//===========================
void CMeshField::SetTexture(CTexture::ELabel texture)
{
	m_texture = texture;
}