//**************************************************
// 
// utility.cpp
// Author  : katsuki mizuki
// Author  : Yuda Kaito
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "utility.h"
#include "application.h"

//--------------------------------------------------
// �p�x�̐��K��
//--------------------------------------------------
void NormalizeAngle(float* pAngle)
{
	if (*pAngle >= D3DX_PI)
	{// 3.14���傫��
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{// -3.14��菬����
		*pAngle += D3DX_PI * 2.0f;
	}
}

//--------------------------------------------------
// �z�[�~���O
//--------------------------------------------------
bool Homing(D3DXVECTOR3* pPosOut, const D3DXVECTOR3& posNow, const D3DXVECTOR3& posDest, float fSpeed)
{
	D3DXVECTOR3 vecDiff = posDest - posNow;

	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength <= fSpeed)
	{// ������蒷������������
		*pPosOut = posDest;
		return true;
	}
	else
	{// ������蒷�����傫����
		*pPosOut = posNow + ((vecDiff / fLength) * fSpeed);
		return false;
	}
}

//--------------------------------------------------
// �����_�̃����_��
//--------------------------------------------------
float FloatRandom(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// �����̃����_��
//--------------------------------------------------
int IntRandom(int nMax, int nMin)
{
	return (int)((rand() / (float)RAND_MAX) * (nMax - nMin)) + nMin;
}

//--------------------------------------------------
// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float SinCurve(int nTime, float fCycle)
{
	return  (sinf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float CosCurve(int nTime, float fCycle)
{
	return  (cosf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// �J�[�u�̒l���A���Ă���
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin)
{
	return (fCurve * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// �͈͓�
//--------------------------------------------------
bool InRange(D3DXVECTOR3* pPos, const D3DXVECTOR3& range)
{
	bool out = false;

	if (pPos->x >= range.x)
	{// �E�̕�
		pPos->x = range.x;
		out = true;
	}
	else if (pPos->x <= -range.x)
	{// ���̕�
		pPos->x = -range.x;
		out = true;
	}

	if (pPos->z >= range.z)
	{// ��̕�
		pPos->z = range.z;
		out = true;
	}
	else if (pPos->z <= -range.z)
	{// ���̕�
		pPos->z = -range.z;
		out = true;
	}

	return out;
}

//--------------------------------------------------
// �͈͓��Ŕ���
//--------------------------------------------------
bool InRangeReflect(D3DXVECTOR3* pPos, D3DXVECTOR3* pMove, const D3DXVECTOR3& range)
{
	bool out = false;

	if (pPos->x >= range.x)
	{// �E�̕�
		pPos->x = range.x;
		pMove->x *= -1.0f;
		out = true;
	}
	else if (pPos->x <= -range.x)
	{// ���̕�
		pPos->x = -range.x;
		pMove->x *= -1.0f;
		out = true;
	}

	if (pPos->z >= range.z)
	{// ��̕�
		pPos->z = range.z;
		pMove->z *= -1.0f;
		out = true;
	}
	else if (pPos->z <= -range.z)
	{// ���̕�
		pPos->z = -range.z;
		pMove->z *= -1.0f;
		out = true;
	}

	return out;
}

//--------------------------------------------------
// �~�̓����蔻��
//--------------------------------------------------
bool CollisionCircle(const D3DXVECTOR3& pos1, float radius1, const D3DXVECTOR3& pos2, float radius2)
{
	// �Q�̕��̂̔��a���m�̘a
	float radius = radius1 + radius2;

	// X�̍���
	float diffX = pos1.x - pos2.x;

	// Y�̍���
	float diffY = pos1.z - pos2.z;

	// ���݂̂Q�_�̋���
	float length = sqrtf((diffX * diffX) + (diffY * diffY));

	if (radius >= length)
	{// �Q�̕��̂̔��a���m�̘a��茻�݂̂Q�_�̋��������������ǂ���
		// ��������
		return true;
	}

	// �������ĂȂ�
	return false;
}

//--------------------------------------------------
// �G���A�̓����蔻��
//--------------------------------------------------
bool CollisionArea(const D3DXVECTOR3& pos1, float radius1, D3DXVECTOR3* pPos2, float radius2)
{
	// �Q�̕��̂̔��a���m�̘a
	float radius = radius1 + radius2;

	// X�̍���
	float diffX = pos1.x - pPos2->x;

	// Y�̍���
	float diffY = pos1.z - pPos2->z;

	// ���݂̂Q�_�̋���
	float length = sqrtf((diffX * diffX) + (diffY * diffY));

	if (radius >= length)
	{// �Q�̕��̂̔��a���m�̘a��茻�݂̂Q�_�̋��������������ǂ���
		float rot = atan2f(diffX, diffY);
		pPos2->x = pos1.x - (sinf(rot) * radius);
		pPos2->z = pos1.z - (cosf(rot) * radius);

		// ��������
		return true;
	}

	// �������ĂȂ�
	return false;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
int Digit(int number)
{
	if (number == 0)
	{
		return 1;
	}

	return (int)log10f((float)number) + 1;
}

//--------------------------------------------------
// 2D�x�N�g���̊O��
//--------------------------------------------------
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return (v1->x * v2->z) - (v1->z * v2->x);
}

//--------------------------------------------------
// 2D�x�N�g���̓���
//--------------------------------------------------
float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return (v1->x * v2->x) + (v1->z * v2->z);
}
