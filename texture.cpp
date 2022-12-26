//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "texture.h"
#include "application.h"

//==================================================
// ��`
//==================================================
namespace
{
const string FILE_PATH[] =
{// �e�N�X�`���̃p�X
	"data/TEXTURE/effect.png",				// �G�t�F�N�g
	"data/TEXTURE/Cursor.png",				// �J�[�\��
	"data/TEXTURE/PressEnter.png",			// �v���X�G���^�[
	"data/TEXTURE/TitleLogo.png",			// �^�C�g�����S
	"data/TEXTURE/Result.png",				// ���U���g
	"data/TEXTURE/Tatami.png",				// ��
	"data/TEXTURE/Tatami_NoLine.png",		// ��(������)
	"data/TEXTURE/PlayStart.png",			// �V�Y�J�n
	"data/TEXTURE/Tutorial.png",			// �B�������I
	"data/TEXTURE/Count.png",				// �u������񐔁@��v
	"data/TEXTURE/Explanation.png",			// �������(����)
	"data/TEXTURE/Explanation_Icon.png"	,	// �������(�A�C�R��)
	"data/TEXTURE/Number.png",				// ��(������)
	"data/TEXTURE/Number_Secret.png",		// �i���o�[�铽�p
	"data/TEXTURE/Ranking.png",				// ��񂫂�
	"data/TEXTURE/Restart.png",				// ����������
	"data/TEXTURE/ReturnToTitle.png",		// �����Ƃ��
	"data/TEXTURE/RankingBG002.png",		// �����L���O�w�i
	"data/TEXTURE/Title_Hackson.png",		// �^�C�g���w�i
	"data/TEXTURE/Frame_Japan.png",			// �a���t���[��
};
}

static_assert(sizeof(FILE_PATH) / sizeof(FILE_PATH[0]) == CTexture::LABEL_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture()
{
	memset(m_pTexture, 0, sizeof(m_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// �ǂݍ���
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		FILE_PATH[label].c_str(),
		&m_pTexture[label]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// �j��
		Release((ELabel)i);
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pTexture[label] != nullptr)
	{// �e�N�X�`���̉��
		m_pTexture[label]->Release();
		m_pTexture[label] = nullptr;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::Get(ELabel label)
{
	if (label == LABEL_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(label > LABEL_NONE && label < LABEL_MAX);

	// �ǂݍ���
	Load(label);

	return m_pTexture[label];
}
