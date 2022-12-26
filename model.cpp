//**************************************************
// 
// model.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "model.h"
#include "application.h"
#include "file_x_manager.h"
#include "file_x.h"
#include "light.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CModel* CModel::Create(CFileXManager::ELabel label)
{
	CModel* pModel = new CModel;

	if (pModel == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pModel->Init();

	// �g�p���郂�f���̐ݒ�
	pModel->SetLabel(label);

	return pModel;
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CModel::CModel() : CObject(CObject::PRIORITY_3D),
	m_quaternion(D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f)),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_label(CFileXManager::LABEL_NONE),
	m_isQuaternion(false)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CModel::~CModel()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CModel::Init()
{
	m_quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_label = CFileXManager::LABEL_NONE;
	m_isQuaternion = false;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CModel::Uninit()
{
	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CModel::Update()
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CModel::Draw()
{
	if (m_label == CFileXManager::LABEL_NONE)
	{// �g�p���Ȃ�
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	D3DXMATRIX mtxWorld, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	if (m_isQuaternion)
	{// �N�H�[�^�j�I�����g�p����
		// �N�H�[�^�j�I���̎g�p���������𔽉f
		D3DXMatrixRotationQuaternion(&mtxRot, &m_quaternion);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	}
	else
	{
		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	}

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// �e�̕`��
	ShadowDraw(mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	D3DMATERIAL9 matDef;	// ���݂̃}�e���A���ۑ��p
	
	// ���݂̃}�e���A���ێ�
	pDevice->GetMaterial(&matDef);

	// X�t�@�C���̏��̎擾
	CFileX* pObj = CApplication::GetInstance()->GetFileXManager()->Get(m_label);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pObj->GetBuffMat()->GetBufferPointer();

	for (int i = 0; i < (int)pObj->GetNumMat(); i++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[i].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pObj->GetTexture()[i]);

		// ���f���p�[�c�̕`��
		pObj->GetMesh()->DrawSubset(i);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void CModel::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CModel::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// �����̐ݒ�
//--------------------------------------------------
void CModel::SetRot(const D3DXVECTOR3& rot)
{
	m_rot = rot;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
const D3DXVECTOR3& CModel::GetRot() const
{
	return m_rot;
}

//--------------------------------------------------
// �g�p���郂�f���̐ݒ�
//--------------------------------------------------
void CModel::SetLabel(CFileXManager::ELabel label)
{
	m_label = label;
}

//--------------------------------------------------
// �g�p���郂�f���̎擾
//--------------------------------------------------
CFileXManager::ELabel CModel::SetLabel()
{
	return m_label;
}

//--------------------------------------------------
// �N�H�[�^�j�I���̐ݒ�
//--------------------------------------------------
void CModel::SetQuaternion(const D3DXVECTOR3& move)
{
	if (!m_isQuaternion)
	{// �N�H�[�^�j�I�����g�p���Ȃ�
		return;
	}

	D3DXVECTOR3 axis;	// ��]��
	D3DXVECTOR3 inverseVec = -move;	// �ړ��ʂ𔽑΂ɂ���
	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �O�ςŉ�]�����Z�o
	D3DXVec3Cross(&axis, &inverseVec, &vecY);

	// �N�H�[�^�j�I���̌v�Z
	D3DXQUATERNION quaternion;

	// ��]���Ɖ�]�p�x���w��
	D3DXQuaternionRotationAxis(&quaternion, &axis, 0.05f);

	// �N�H�[�^�j�I����K�p
	m_quaternion *= quaternion;

	// �N�H�[�^�j�I���̐��K��
	D3DXQuaternionNormalize(&m_quaternion, &m_quaternion);
}

//--------------------------------------------------
// �N�H�[�^�j�I�����g�p���邩�ǂ����̐ݒ�
//--------------------------------------------------
void CModel::SetIsQuaternion(bool quaternion)
{
	m_isQuaternion = quaternion;
}

//--------------------------------------------------
// �e�̕`��
//--------------------------------------------------
void CModel::ShadowDraw(D3DXMATRIX mtxWorld)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	D3DXMATRIX mtxShadow;
	
	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	D3DXVECTOR3 light = CLight::Get(0)->GetDir();
	D3DXVECTOR4 vecLight = D3DXVECTOR4(-light, 0.0f);

	D3DXVECTOR3	pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXPLANE planeField;

	// �@���ƕ��ʂ̂P�_���畽�ʂ��쐬
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	// ���C�g�ƕ��ʂ���e�s����쐬
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// �e�̃}�g���b�N�X�𔽉f
	D3DXMatrixMultiply(&mtxShadow, &mtxShadow, &mtxWorld);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	// X�t�@�C���̏��̎擾
	CFileX* pFileX = CApplication::GetInstance()->GetFileXManager()->Get(m_label);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pFileX->GetBuffMat()->GetBufferPointer();
	D3DMATERIAL9 matD3D = pMat->MatD3D;

	// �F�����F�ɕύX
	matD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	matD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// �}�e���A���̐ݒ�
	pDevice->SetMaterial(&matD3D);

	for (int i = 0; i < (int)pFileX->GetNumMat(); i++)
	{
		// ���f���p�[�c�̕`��
		pFileX->GetMesh()->DrawSubset(i);
	}
}
