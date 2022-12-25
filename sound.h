//**************************************************
//
// sound.h
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SOUND_H_	//���̃}�N����`������ĂȂ�������
#define _SOUND_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �N���X
//==================================================
class CSound
{
	/* ����`�� */
public:
	enum ELabel
	{
		LABEL_NONE = -1,
		LABEL_BGM_Title = 0,	// �^�C�g��
		LABEL_BGM_Game,			// �Q�[��
		LABEL_BGM_Result,		// ���U���g
		LABEL_SE_Enter,			// ����
		LABEL_SE_Select,		// �I��
		LABEL_MAX,
	};

	/* �������o�֐��� */
public:
	CSound();	// �f�t�H���g�R���X�g���N�^
	~CSound();	// �f�X�g���N�^

public:
	HRESULT Init(HWND hWnd);	// ������
	void Uninit();				// �I��
	HRESULT Play(ELabel sound);	// �Đ�
	void Stop(ELabel label);	// �w�肵����~
	void Stop();				// �S�Ă̒�~

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// �`�����N�̃`�F�b�N
	HRESULT LoadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// �`�����N�f�[�^�̓ǂݍ���

	/* �������o�ϐ��� */
private: 
	IXAudio2* m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;		// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_pSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_pDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_sizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif // !_SOUND_H_
