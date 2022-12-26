//=========================================
//
// �X�R�A����
// Auther�F�y���m��
//
//=========================================
#ifndef _SCORE_H_		// ���̃}�N����`������ĂȂ�������
#define _SCORE_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include "object2D.h"
#include "number.h"

#define MAX_DIGITS		(2)			// �X�R�A�̌���
#define MAX_RANK		(5)			//�\�����郉���L���O�̍ő吔

//=========================================
// �X�R�A�N���X���`
//=========================================
class CScore
{
public:
	CScore();							//�R���X�g���N�^
	virtual ~CScore() ;			//�f�X�g���N�^

	//����������
	void Init() ;

	//�X�V����
	void Update(void) ;

	//�`�揈��
	void Draw(void) ;

	//�I������
	void Uninit(void) ;

	//�N���G�C�g����
	static CScore* Create(const D3DXVECTOR3 &pos);

	//�X�R�A�̉��Z
	void Addpos() { m_nScore++; };
	void SetDomino();

	//�X�R�A�̐ݒ�
	void Set();
	void SetCor(D3DXCOLOR col);
	void SetScore(int Score) { m_nScore = Score; };
	int GetScore() { return m_nScore; };
	static void AddFrag() { m_bAddflag = true; };

	//void Ranking();

private:
	D3DXVECTOR3 m_pos;					// ���W
	CNumber*	m_pNumber[MAX_DIGITS];	// �i���o�[
	int			m_nScore;				// �X�R�A
	int			m_nRankUpdate;			//�X�V�����NNo.
	int			m_nTimerRanking;		//�����L���O��ʕ\���^�C�}�[
	float		m_fPtnrank;				//�v���C���[�_��
	int			m_nCntrank;				//�_�ł̃J�E���g�p
	static bool	m_bAddflag;				//���Z�t���O

};

#endif
