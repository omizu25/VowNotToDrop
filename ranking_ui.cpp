//=========================================
//
// �����L���O����
// Auther�FArita Meigen
//
//=========================================

//------------------------
// �C���N���[�h
//------------------------
#include "ranking_ui.h"
#include "input.h"
#include <math.h>
#include "application.h"
#include "renderer.h"
#include <string>
#include "Score.h"
#include <vector>
#include <algorithm>

//------------------------
// �ÓI�����o�ϐ��錾
//------------------------
int	CRankingUI::m_Score;					// ����

//=========================================
//�R���X�g���N�^
//=========================================
CRankingUI::CRankingUI()
{

}

//=========================================
//�f�X�g���N�^
//=========================================
CRankingUI::~CRankingUI()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
HRESULT CRankingUI::Init()
{
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		m_apScore[nCnt] = CScore::Create(D3DXVECTOR3(550.0f, 650.0f - 109.0f*nCnt, 0.0f));
	}
	m_nflashing = 0;
	m_nflashcnt = 0;
	Load();
	Ranking();
	Save();

	return S_OK;
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CRankingUI::Update()
{

	if (m_nRankUpdate!=-1)
	{
		//�F�̐ݒ�
		m_apScore[m_nRankUpdate]->SetCor(D3DXCOLOR(1.0f, 0.0f, 0.0f, (float)m_nflashing));
		m_nflashcnt++;
		if (m_nflashcnt %FLASH_INTER ==0)
		{
			m_nflashing = m_nflashing^1;
		}
	}
	for (int i = 0; i < MAX_RANK; i++)
	{
		m_apScore[i]->Update();
	}
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CRankingUI::Uninit()
{
	for (int i = 0; i < MAX_RANK; i++)
	{
		if (m_apScore[i] != nullptr)
		{
			m_apScore[i]->Uninit();
			m_apScore[i] = nullptr;
		}
	}
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CRankingUI* CRankingUI::Create()
{
	CRankingUI* pRanking = nullptr;

	pRanking = new CRankingUI;

	if (pRanking != nullptr)
	{
		pRanking->Init();
	}

	return pRanking;
}

//=========================================
// �ŐV�̃X�R�A���擾
//=========================================
void CRankingUI::SetCurrentScore(int Time)
{
	m_Score = Time;
}

//=========================================
// �ۑ�
//=========================================
void CRankingUI::Save()
{
	FILE*fp = fopen("data\\TEXT\\Ranking.txt", "w");		//�t�@�C���ǂݍ���
	const int lenLine = 1024;							//1�P��̍ő吔
	for (int i = 0; i < MAX_RANK; i++)
	{
		if (fp != NULL)
		{
			fprintf(fp, "%d\n", m_apScore[i]->GetScore());	//�ǂݍ��񂾕������Ƃɐݒ肷��
		}
	}

	fclose(fp);
}

//=========================================
// �ǂݍ���
//=========================================
void CRankingUI::Load()
{
	FILE*fp = fopen("data\\TEXT\\Ranking.txt", "r");		//�t�@�C���ǂݍ���
	const int lenLine = 1024;							//1�P��̍ő吔
	int nrScore = 0;									//�ǂݍ��ݗp�̕�����

	for (int i = 0; i < MAX_RANK; i++)
	{//�����L���O�̓ǂݍ���
		if (fp != NULL)
		{
			fscanf(fp, "%d", &nrScore);			//�ǂݍ��񂾕������Ƃɐݒ肷��
			m_apScore[i]->SetScore(nrScore);		//�ݒ�
		}
	}

	fclose(fp);
}

//=========================================
// �����L���O�̕��ёւ�
//=========================================
void CRankingUI::Ranking()
{
	//�����N�O�ɂ��Ă���
	m_nRankUpdate = -1;
	if (m_Score >= m_apScore[0]->GetScore())
	{//�ŉ��ʂƔ�r
		m_apScore[0]->SetScore(m_Score);

		//�����ɕ��ѕς���
		std::vector<int> rank = { m_apScore[0]->GetScore(), m_apScore[1]->GetScore(), m_apScore[2]->GetScore(),
			m_apScore[3]->GetScore(), m_apScore[4]->GetScore() };
		std::sort(rank.begin(), rank.end());
		for (int i = 0; i < MAX_RANK; i++)
		{//���ѕς��������
			m_apScore[i]->SetScore(rank[i]);
			if (m_Score == rank[i])
			{
				m_nRankUpdate = i;
			}
		}
	}
}