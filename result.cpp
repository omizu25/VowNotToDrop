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
		CObject3D* pObj = CObject3D::Create();

		D3DXVECTOR3 size = D3DXVECTOR3(1800.0f, 0.0f, 1800.0f);

		// �T�C�Y�̐ݒ�
		pObj->SetSize(size);

		// �e�N�X�`���̐ݒ�
		pObj->SetTexture(CTexture::LAVEL_TATAMI);
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
	Input();

	CDomino::AddMove();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CResult::Draw()
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CResult::Input()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_BACK))
	{// P�L�[�������ꂽ
		// ���[�h�̕ύX
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RANKING);
	}
}
