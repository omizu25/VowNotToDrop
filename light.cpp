//**************************************************
// 
// light.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "light.h"
#include "application.h"
#include "utility.h"

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CLight* CLight::m_pLight[MAX_LIGHT] = {};

//--------------------------------------------------
// �S�Ă̐���
//--------------------------------------------------
CLight** CLight::CreateAll()
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	{
		D3DXVECTOR3 vec = D3DXVECTOR3(0.2f, -0.8f, 0.4f);

		// ���C�g�̐���
		m_pLight[0] = CLight::Create(0, D3DLIGHT_DIRECTIONAL, col, vec);
	}

	{
		D3DXVECTOR3 vec = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

		// ���C�g�̐���
		m_pLight[1] = CLight::Create(1, D3DLIGHT_DIRECTIONAL, col, vec);
	}

	{
		D3DXVECTOR3 vec = D3DXVECTOR3(-0.2f, 0.8f, 0.4f);

		// ���C�g�̐���
		m_pLight[2] = CLight::Create(2, D3DLIGHT_DIRECTIONAL, col, vec);
	}

	return m_pLight;
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CLight::ReleaseAll()
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		if (m_pLight[i] != nullptr)
		{// null�`�F�b�N
			// �I��
			m_pLight[i]->Uninit();
			delete m_pLight[i];
			m_pLight[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
CLight* CLight::Get(int num)
{
	assert(num >= 0 && num < MAX_LIGHT);

	return m_pLight[num];
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CLight* CLight::Create(int index, D3DLIGHTTYPE type, const D3DXCOLOR& col, const D3DXVECTOR3& vec)
{
	CLight* pLight = new CLight;

	if (pLight == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pLight->Init();

	// �ݒ�
	pLight->Set(index, type, col, vec);

	return pLight;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CLight::CLight()
{
	memset(&m_light, 0, sizeof(m_light));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CLight::~CLight()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CLight::Init()
{
	memset(&m_light, 0, sizeof(m_light));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CLight::Uninit()
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CLight::Update()
{
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CLight::Set(int index, D3DLIGHTTYPE type, const D3DXCOLOR& col, const D3DXVECTOR3& vec)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	m_light.Type = type;
	m_light.Diffuse = col;

	D3DXVECTOR3 vecDir = vec;	// ���C�g�̕����x�N�g��

	// ���K��
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light.Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(index, &m_light);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(index, true);
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
D3DXVECTOR3 CLight::GetDir()
{
	return (D3DXVECTOR3)m_light.Direction;
}
