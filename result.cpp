//**************************************************
// 
// result.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "result.h"
#include "input.h"
#include "application.h"
#include "instancing.h"
#include "fade.h"
#include "mode.h"
#include "mesh_field.h"
#include "domino.h"
#include "menu.h"
#include "result.h"
#include "sound.h"
#include "object3D.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CResult::CResult()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CResult::Init()
{
	{// �w�i
		m_pObj = CObject3D::Create();

		D3DXVECTOR3 size = D3DXVECTOR3(26000.0f, 0.0f, 1800.0f);
		m_pObj->SetPos(D3DXVECTOR3(320.0f, 0.0f, 0.0f));

		// �T�C�Y�̐ݒ�
		m_pObj->SetSize(size);

		// �e�N�X�`���̐ݒ�
		m_pObj->SetTexture(CTexture::LAVEL_TATAMI);
	}

	//�a���t���[��
	CObject2D* pFrame = CObject2D::Create();

	D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f);

	// �ʒu�̐ݒ�
	pFrame->SetPos(pos);

	//�T�C�Y�̐ݒ�
	pFrame->SetSize(size);

	//�e�N�X�`���̐ݒ�
	pFrame->SetTexture(CTexture::LABEL_Frame_Japan);

	CDomino::CreateAll();

	//�Ȃ̍Đ�
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_Result);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CResult::Uninit()
{
	//�Ȃ̒�~
	CApplication::GetInstance()->GetSound()->Stop();

	// ���
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CResult::Update()
{
	CDomino::AddMove();

	D3DXVECTOR3 pos = m_pObj->GetPos();

	pos.x += CDomino::GetMove();

	m_pObj->SetPos(pos);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CResult::Draw()
{
}
