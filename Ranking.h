//=========================================
//
// �����L���O����
// Auther�FArita Meigen
//
//=========================================
#ifndef _RANKING_H_		// ���̃}�N����`������ĂȂ�������
#define _RANKING_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include "object2D.h"

class CScore;

#define MAX_DIGITS		(8)			// �X�R�A�̌���
#define MAX_RANK		(5)			//�\�����郉���L���O�̍ő吔

//=========================================
// �X�R�A�N���X���`
//=========================================
class CRanking
{
public:
	CRanking();							//�R���X�g���N�^
	virtual ~CRanking() ;				//�f�X�g���N�^

	
	HRESULT Init() ;	//������
	void Update() ;		//�X�V
	void Uninit() ;		//�I��

	//�N���G�C�g����
	static CRanking* Create();

	void Save();
	void Load();
	void Ranking();

	//�Z�b�^�[
	static void SetCurrentScore(int Time);

private:
	D3DXVECTOR3 m_pos;					// ���W
	static int	m_Score;				// 
	int			m_nRankUpdate;			//�X�V�����NNo.
	CScore*		m_apScore[MAX_RANK];	// �X�R�A�̍ő吔
	int			m_nflashcnt;			//�_�ŗp
	int			m_nflashing;			//�_�ŗp



};

#endif

