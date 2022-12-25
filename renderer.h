//**************************************************
// 
// renderer.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RENDERER_H_	//���̃}�N����`������ĂȂ�������
#define _RENDERER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �O���錾
//==================================================
class CCamera;

//==================================================
// �N���X
//==================================================
class CRenderer
{
	/* ����`�� */
public:

	/* �������o�֐��� */
public:
	CRenderer();	// �f�t�H���g�R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^

public:
	HRESULT Init(HWND hWnd, bool bWindow);	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

public:
	LPDIRECT3DDEVICE9 GetDevice();	// �f�o�C�X�̎擾
	CCamera* GetCamera();			// �J�����̎擾

private:
#ifdef _DEBUG
	void DrawFPS();	// FPS�\��
#endif // _DEBUG

	/* �������o�ϐ��� */
private:
#ifdef _DEBUG
	LPD3DXFONT m_pFont;	// �t�H���g
#endif // _DEBUG

	LPDIRECT3D9 m_pD3D;				// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Device�I�u�W�F�N�g
	CCamera* m_pCamera;	// �J�����̏��
};

#endif // !_RENDERER_H_
