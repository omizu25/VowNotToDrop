//===================================================
//
// ���b�V���w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _MESH_FIELD_H_
#define _MESH_FIELD_H_	//��d�C���N���[�h�h�~

//-------------------------------
// �C���N���[�h
//-------------------------------
#include "object3d.h"
#include "renderer.h"

//================================
// ���b�V���N���X
//================================
class CMeshField : public CObject
{
public:
	CMeshField();
	explicit CMeshField(EPriority nPriority);	//�R���X�g���N�^
	~CMeshField();						//�f�X�g���N�^

	//------------------
	// �����o�֐�
	//------------------
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetMeshSize(int nDivision, float fWidth);	//�ő啝�̐ݒ�
	void SetTexture(CTexture::ELabel texture);		//�e�N�X�`���̐ݒ�

	//------------------
	// �ÓI�����o�֐�
	//------------------
	static CMeshField* Create(CTexture::ELabel texture);

private:
	//------------------
	// �萔
	//------------------
	static const int nMaxVtx = 512;	//���_�̍ő吔

	//------------------
	// �����o�ϐ�
	//------------------
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_VtxPos[nMaxVtx];	//���_�̈ʒu
	D3DXVECTOR3 m_Normal;			//�ʖ@���x�N�g���i�[�p
	D3DXVECTOR3 m_VtxNor[nMaxVtx];	//���_�̖@���x�N�g���i�[�p
	D3DXVECTOR3 m_rot;				//����
	D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X

	/* �� ���b�V�����\�������� */
	int m_nNumDivision;		//�|���S���̕�����
	int m_nCntVtx;			//���_�̕�����
	int m_nNumVtx;			//���_��
	int m_nNumPolygon;		//�|���S����
	int m_nNumIndex;		//�C���f�b�N�X��
	float m_fMaxWidth;		//���b�V���t�B�[���h�̍ő啝
	float m_fMeshWidth;		//���b�V���t�B�[���h�̕�
	float m_fTexSize;		//�e�N�X�`���̕����T�C�Y

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	CTexture::ELabel m_texture;			//�e�N�X�`��
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
};

#endif