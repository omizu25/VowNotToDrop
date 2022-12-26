//=========================================
//
// �����L���O����
// Auther�FArita Meigen
//
//=========================================
#ifndef _RANKING_UI_H_		// ���̃}�N����`������ĂȂ�������
#define _RANKING_UI_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include "object2D.h"

class CScore;

#define FLASH_INTER		(20)		//�_�ł̊Ԋu


//=========================================
// �X�R�A�N���X���`
//=========================================
class CRankingUI
{
public:
	CRankingUI();							//�R���X�g���N�^
	virtual ~CRankingUI() ;				//�f�X�g���N�^

	
	HRESULT Init() ;	//������
	void Update() ;		//�X�V
	void Uninit() ;		//�I��

	//�N���G�C�g����
	static CRankingUI* Create();

	void Save();
	void Load();
	void Ranking();

	//�Z�b�^�[
	static void SetCurrentScore(int Time);

private:
	static const int nMaxRank = 5;
	D3DXVECTOR3 m_pos;					// ���W
	static int	m_Score;				// 
	int			m_nRankUpdate;			//�X�V�����NNo.
	CScore*		m_apScore[nMaxRank];	// �X�R�A�̍ő吔
	int			m_nflashcnt;			//�_�ŗp
	int			m_nflashing;			//�_�ŗp



};

#endif

