//**************************************************
// 
// precompile.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PRECOMPILE_H_	//���̃}�N����`������ĂȂ�������
#define _PRECOMPILE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

// ��{
#include <Windows.h>
#include <stdio.h>
#include <assert.h>
#include <tchar.h>
#include <time.h>

// �������[���[�N�̃`�F�b�N
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// STL
#include <string>
using namespace std;	// ���O��Ԃ̎w��

// DirectX9
#include <d3dx9.h>

// Input
#define	 DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <xinput.h>

// Sound
#include <xaudio2.h>

#endif // !_PRECOMPILE_H_
