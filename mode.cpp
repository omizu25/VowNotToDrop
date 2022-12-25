//**************************************************
// 
// mode.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"
#include "title.h"
#include "game.h"
#include "result.h"

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CMode* CMode::Create(EMode mode)
{
	CMode* pMode = nullptr;

	switch (mode)
	{
	case CMode::MODE_TITLE:
		pMode = new CTitle;
		break;

	case CMode::MODE_GAME:
		pMode = new CGame;
		break;

	case CMode::MODE_RESULT:
		pMode = new CResult;
		break;

	case CMode::MODE_MAX:
	case CMode::MODE_NONE:
	default:
		assert(false);
		break;
	}

	if (pMode == nullptr)
	{// null�`�F�b�N
		assert(false);
		return nullptr;
	}

	// ������
	pMode->Init();

	return pMode;
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CMode::CMode() : CObject(CObject::PRIORITY_SYSTEM)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMode::~CMode()
{
}
