//========================================================
//�X�R�A��ʂ̏���
//========================================================
#include "number.h"

//=========================================
//�R���X�g���N�^
//=========================================
CNumber::CNumber()
{
}

//=========================================
//�f�X�g���N�^
//=========================================
CNumber::~CNumber()
{

}

//=========================================
//�I�u�W�F�N�g�̏���������
//=========================================
void CNumber::Init()
{
	// �I�u�W�F�N�g�̏�����
	CObject2D::Init();

	//�T�C�Y�̐ݒ�
	CObject2D::SetSize(D3DXVECTOR3(50.0f, 80.0f,0.0f));

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::LABEL_Number);
}

//=========================================
//�I�u�W�F�N�g�̍X�V����
//=========================================
void CNumber::Update()
{
}

//=========================================
//�I�u�W�F�N�g�̏I������
//=========================================
void CNumber::Uninit()
{
	CObject2D::Uninit();
}

//=========================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================
void CNumber::Draw()
{
	CObject2D::Draw();
}

//=========================================
//�I�u�W�F�N�g�̃N���G�C�g
//=========================================
CNumber* CNumber::Create(const D3DXVECTOR3 &pos)
{
	CNumber* pCNumber = nullptr;

	pCNumber = new CNumber;

	if (pCNumber != nullptr)
	{
		pCNumber->Init();
		pCNumber->SetPos(pos);
	}

	return pCNumber;
}

//========================================================
//�����̐ݒ菈��
//========================================================
void CNumber::Set(int nDigits)
{
	float PatternSize = 1.0f / 10.0f;
	SetVtxTex(D3DXVECTOR2(nDigits * PatternSize,nDigits * PatternSize+PatternSize),D3DXVECTOR2(0.0f,1.0f));
}
