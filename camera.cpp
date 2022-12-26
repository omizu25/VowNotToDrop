//**************************************************
// 
// camera.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "camera.h"
#include "application.h"
#include "game.h"
#include "utility.h"
#include "domino.h"

//==================================================
// ��`
//==================================================
namespace
{
const D3DXVECTOR3 STD_POS_V = D3DXVECTOR3(0.0f, 700.0f, -500.0f);	// ��̎��_�̈ʒu
const float MAX_NEAR = 10.0f;		// �j�A�̍ő�l
const float MAX_FAR = 2500.0f;		// �t�@�[�̍ő�l
const float FIELD_OF_VIEW = D3DXToRadian(45.0f);	// ����p

// �A�X�y�N�g��
const float ASPECT_RATIO = (float)CApplication::SCREEN_WIDTH / (float)CApplication::SCREEN_HEIGHT;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CCamera::CCamera() :
	m_posV(D3DXVECTOR3(0.0f, 50.0f, 0.0f)),
	m_posR(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	memset(m_mtxProj, 0, sizeof(m_mtxProj));
	memset(m_mtxView, 0, sizeof(m_mtxView));
	m_fFogValue = 0.0f;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CCamera::~CCamera()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CCamera::Init()
{
	m_posV = STD_POS_V;
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// �Œ�
	m_fFogValue = 0.00005f;
	m_fFogDensity = 0.0f;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CCamera::Uninit()
{	
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CCamera::Update()
{
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CCamera::Set()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// �r���[�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�̍쐬
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// �v���W�F�N�V�����̏�����
	D3DXMatrixIdentity(&m_mtxProj);

	// �v���W�F�N�V�����̍쐬
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProj,
		FIELD_OF_VIEW,
		ASPECT_RATIO,
		MAX_NEAR,
		MAX_FAR);

	// �v���W�F�N�V�����̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);

	//--------------------------------
	// �t�H�O
	//--------------------------------
	//�t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//�t�H�O�J���[�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//�t�H�O���[�h�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);	//���x�w��

	//----------------------------
	// ���x�w�莞�̏���
	//----------------------------
	int nPop = CDomino::GetCount();

	if (CApplication::GetInstance()->GetModeEnum() == CMode::MODE_GAME)
	{
		if (m_fFogDensity <= 0.0022f)
		{
			m_fFogDensity = (m_fFogValue * nPop);		//���x(0.001�ł����Ȃ�^����)
		}
	}
	else
	{
		m_fFogDensity = 0;
	}

	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void CCamera::SetPos(const D3DXVECTOR3& pos)
{
	m_posV = pos;
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CCamera::GetPos() const
{
	return m_posV;
}

//--------------------------------------------------
// �v���W�F�N�V�����̎擾
//--------------------------------------------------
const D3DXMATRIX& CCamera::GetProj() const
{
	return m_mtxProj;
}

//--------------------------------------------------
// �r���[�̎擾
//--------------------------------------------------
const D3DXMATRIX& CCamera::GetView() const
{
	return m_mtxView;
}
