//========================================================
//�X�R�A��ʂ̏���
//========================================================
#include "Score.h"
#include "input.h"
#include <math.h>
#include "application.h"
#include "renderer.h"
#include<string>

//=========================================
//�ÓI�����o�ϐ�
//=========================================
bool CScore::m_bAddflag = false;

//=========================================
//�R���X�g���N�^
//=========================================
CScore::CScore()
{
}

//=========================================
//�f�X�g���N�^
//=========================================
CScore::~CScore()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
void CScore::Init()
{
	//// �e�N�X�`���̐ݒ�
	//CObject2D::SetTexture(CTexture::TEXTURE_NONE);

	for (int nCnt = 0; nCnt < MAX_DIGITS; nCnt++)
	{
		m_pNumber[nCnt] = CNumber::Create(D3DXVECTOR3(m_pos.x - 50.0f * nCnt, m_pos.y, m_pos.z));
	}

	// �N���A�^�C����\��
	Set();
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CScore::Update()
{
	if (m_bAddflag == true)
	{
		Addpos();
		m_bAddflag = false;
	}
	Set();
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CScore::Uninit()
{
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CScore::Draw()
{
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CScore* CScore::Create(const D3DXVECTOR3 &pos)
{
	CScore* pCScore = nullptr;

	pCScore = new CScore;

	if (pCScore != nullptr)
	{
		pCScore->m_pos = pos;
		pCScore->Init();
	}

	return pCScore;
}

//=========================================
// �X�R�A�̐ݒ菈��
//=========================================
void CScore::Set()
{
	int aPosTexU[MAX_DIGITS];		//�e���̐������i�[

	for (int nCnt = 0; nCnt < MAX_DIGITS; nCnt++)
	{
		// 2����
		if (nCnt == 1)
		{// ��
		 // (m_Score % 10^X+1) / 10^X
			aPosTexU[nCnt] = (m_nScore/10) % 10;
			m_pNumber[nCnt]->Set(aPosTexU[nCnt]);
		}
		// 1���ځA0�����N���Ă��܂��̂Ł��Ɠ����ɏ����ł��Ȃ��E�E�E
		else if (nCnt == 0)
		{
			// (m_Score % 10^X+1) / 10^X
			aPosTexU[nCnt] = m_nScore%10;
			m_pNumber[nCnt]->Set(aPosTexU[nCnt]);
		}
	}
}

//=========================================
// �X�R�A�̐F�ݒ�
//=========================================
void CScore::SetCor(D3DXCOLOR col)
{
	for (int i = 0; i < MAX_DIGITS; i++)
	{
		m_pNumber[i]->SetCol(col);
	}
}
