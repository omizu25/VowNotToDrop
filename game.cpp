//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "game.h"
#include "input.h"
#include "effect.h"
#include "application.h"
#include "fade.h"
#include "mode.h"
#include "object3D.h"
#include "obstacle.h"
#include "mesh_field.h"
#include "obstacle_manager.h"
#include "message.h"
#include "player.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CGame::CGame()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CGame::Init()
{
	//���b�Z�[�W�̕\��
	{
		D3DXVECTOR3 pos(640.0f, 360.0f, 0.0f);
		CMessage::Create(pos, 800.0f, 500.0f);
	}

	//���b�V���t�B�[���h�̐���
	CMeshField::Create(CTexture::LAVEL_TATAMI_NOLINE);

	// ��Q���̐���
	CObstacleManager::Create();	// �v���C���[�̐���
	CPlayer::CreateAll();}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CGame::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(KEY_PAUSE))
	{// P�L�[�������ꂽ
		CPlayer::AddKill();
		//CEffect::Explosion(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	
	if (pInput->Trigger(KEY_BACK))
	{
		CApplication::GetInstance()->GetFade()->ChangeMode(EMode::MODE_RESULT);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CGame::Draw()
{
}
