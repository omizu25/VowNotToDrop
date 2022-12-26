//=========================================
//
// �X�R�A�̏���
// Auther�F�y���m��
//
//=========================================
#ifndef _NUMBER_H_		// ���̃}�N����`������ĂȂ�������
#define _NUMBER_H_		// ��d�C���N�\���[�h�h�~�̃}�N����`

#include "object2D.h"

//=========================================
// �}�N����`
//=========================================
#define MAX_SCORE		(2)			// �X�R�A�̍ő吔
#define MAX_VERTEX		(4)			// ���_�̍ő吔

//=========================================
// �X�R�A�N���X���`
//=========================================
class CNumber :public CObject2D
{
public:
	CNumber();			//�R���X�g���N�^
	virtual ~CNumber() override;			//�f�X�g���N�^

	//����������
	void Init() override;
	//�X�V����
	void Update(void) override;
	//�`�揈��
	void Draw(void) override;
	//�I������
	void Uninit(void) override;
	//�N���G�C�g����
	static CNumber* Create(const D3DXVECTOR3 &pos);
	//static void Add(int nNumScore, int nValue);

	//�X�R�A�̐ݒ�
	void Set(int nDigits);

private:
	int m_Score;			//�X�R�A�̒l
	int m_Digit;
};

#endif