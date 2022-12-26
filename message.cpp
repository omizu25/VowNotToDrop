//===================================================
//
// ���b�Z�[�W�̏���
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "message.h"
#include "renderer.h"

//=======================
// �R���X�g���N�^
//=======================
CMessage::CMessage() : CObject2D(CObject::PRIORITY_2D)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	m_nCntTime = 0;		//���ԃJ�E���g
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
}

//=======================
// �f�X�g���N�^
//=======================
CMessage::~CMessage()
{

}

//=======================
// ������
//=======================
void CMessage::Init()
{
	CObject2D::Init();

	//�I�u�W�F�N�g���̐ݒ�
	CObject2D::SetPos(m_pos);
	CObject2D::SetSize(D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f));
	CObject2D::SetTexture(CTexture::LAVEL_Tutorial);
}

//=======================
// �I��
//=======================
void CMessage::Uninit()
{
	CObject2D::Uninit();
}

//=======================
// �X�V
//=======================
void CMessage::Update()
{
	CObject2D::Update();

	//�J�E���g�̉��Z
	m_nCntTime++;

	//-------------------
	// ���X�ɓ����ɂ���
	//-------------------
	if (m_nCntTime >= 120)
	{
		m_col.a -= 0.05f;
		CObject2D::SetCol(m_col);
	}

	//-------------------
	// ���S�ɓ����ɂȂ���
	//-------------------
	if (m_col.a <= 0.0f)
	{
		CObject::SetRelease();
	}
}

//=======================
// �`��
//=======================
void CMessage::Draw()
{
	CObject2D::Draw();
}

//=======================
// ����
// �����F�ʒu�A���A����
//=======================
CMessage *CMessage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CMessage *pMessage = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pMessage = new CMessage;	//����

	if (pMessage != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pMessage->m_pos = pos;
		pMessage->m_fWidth = fWidth;
		pMessage->m_fHeight = fHeight;

		//������
		pMessage->Init();
	}

	return pMessage;
}