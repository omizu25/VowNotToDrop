//**************************************************
// 
// file_x.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _FILE_X_H_	//���̃}�N����`������ĂȂ�������
#define _FILE_X_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"

//==================================================
// �N���X
//==================================================
class CFileX
{
	/* ����`�� */
public:
	
	/* ���ÓI�����o�֐��� */
public:
	static CFileX* Create(const string& str);	// ����

	/* �������o�֐��� */
public:
	CFileX();	// �f�t�H���g�R���X�g���N�^
	~CFileX();	// �f�X�g���N�^

public: 
	void Init();	// ������
	void Uninit();	// �I��

public:
	LPDIRECT3DTEXTURE9* GetTexture();		// �e�N�X�`���̎擾
	LPD3DXMESH GetMesh();					// ���b�V�����̎擾
	LPD3DXBUFFER GetBuffMat();				// �}�e���A�����̎擾
	DWORD GetNumMat();						// �}�e���A�����̐��̎擾
	const D3DXVECTOR3& GetSize() const;		// �T�C�Y�̎擾
	const D3DXVECTOR3& GetVtxMin() const;	// �ŏ��l�̎擾
	const D3DXVECTOR3& GetVtxMax() const;	// �ő�l�̎擾

private:
	void Load(const string& str);	// �ǂݍ���

	/* �������o�ϐ��� */
private:
	LPDIRECT3DTEXTURE9* m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPD3DXMESH m_pMesh;				// ���b�V�����̃|�C���^
	LPD3DXBUFFER m_pBuffMat;		// �}�e���A�����̃|�C���^
	DWORD m_numMat;					// �}�e���A�����̐�
	D3DXVECTOR3 m_size;				// �T�C�Y
	D3DXVECTOR3 m_vtxMin;			// �ŏ��l
	D3DXVECTOR3 m_vtxMax;			// �ő�l
};

#endif // !_FILE_X_H_
