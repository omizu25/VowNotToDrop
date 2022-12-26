//**************************************************
// 
// file_x_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "file_x_manager.h"
#include "file_x.h"

//==================================================
// 定義
//==================================================
namespace
{
const string FILE_PATH[] =
{// テクスチャのパス
	"data/MODEL/Hammer.x",		// ハンマー
	"data/MODEL/WoodBox.x",		// 木箱
	"data/MODEL/Fish_Tail.x",	// 魚の尻尾
	"data/MODEL/Fish_Body.x",	// 魚の体
	"data/MODEL/Angel/Body.x",				// 天使の体
	"data/MODEL/Angel/Head.x",				// 天使の頭
	"data/MODEL/Angel/RightArmTop.x",		// 天使の右腕上
	"data/MODEL/Angel/RightArmBottom.x",	// 天使の右腕下
	"data/MODEL/Angel/RightHand.x",			// 天使の右手
	"data/MODEL/Angel/LeftArmTop.x",		// 天使の左腕上
	"data/MODEL/Angel/LeftArmBottom.x",		// 天使の左腕下
	"data/MODEL/Angel/LeftHand.x",			// 天使の左手
	"data/MODEL/Angel/RightFootTop.x",		// 天使の右足上
	"data/MODEL/Angel/RightFootBottom.x",	// 天使の右足下
	"data/MODEL/Angel/RightFoot.x",			// 天使の右足
	"data/MODEL/Angel/LeftFootTop.x",		// 天使の左足上
	"data/MODEL/Angel/LeftFootBottom.x",	// 天使の左足下
	"data/MODEL/Angel/LeftFoot.x",			// 天使の左足
	"data/MODEL/Angel/Rope.x",				// てるてるの縄
	"data/MODEL/Angel/Head.x",				// てるてるの頭
	"data/MODEL/Angel/Body.x",				// てるてるの体
	"data/MODEL/Angel/Right_ear.x",			// てるてるの右耳
	"data/MODEL/Angel/Left_ear.x",			// てるてるの左耳
	"data/MODEL/Angel/Angel_ring.x",		// てるてるの天使の輪
	"data/MODEL/Angel/Angel_wing.x",		// てるてるの天使の羽
	"data/MODEL/Angel/Devil_wing.x",		// てるてるの悪魔の羽
	"data/MODEL/Angel/Morning_koko.x",		// てるてるの朝ココ
};
}

static_assert(sizeof(FILE_PATH) / sizeof(FILE_PATH[0]) == CFileXManager::LABEL_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CFileXManager::CFileXManager()
{
	for (int i = 0; i < LABEL_MAX; i++)
	{
		m_pFileX[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CFileXManager::~CFileXManager()
{
	for (int i = 0; i < LABEL_MAX; i++)
	{
		assert(m_pFileX[i] == nullptr);
	}
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CFileXManager::LoadAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// 読み込み
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CFileXManager::Load(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// Xファイルの読み込みがされている
		return;
	}

	// 生成
	m_pFileX[label] = CFileX::Create(FILE_PATH[label]);
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CFileXManager::Load(const string& str)
{
	// 変換
	ELabel label = Change(str);

	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// Xファイルの読み込みがされている
		return;
	}

	// 生成
	m_pFileX[label] = CFileX::Create(FILE_PATH[label]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CFileXManager::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		// 解放
		Release((ELabel)i);
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CFileXManager::Release(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// Xファイルの情報の解放
		m_pFileX[label]->Uninit();
		m_pFileX[label] = nullptr;
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CFileXManager::Release(const string& str)
{
	// 変換
	ELabel label = Change(str);

	assert(label > LABEL_NONE && label < LABEL_MAX);

	if (m_pFileX[label] != nullptr)
	{// Xファイルの情報の解放
		m_pFileX[label]->Uninit();
		delete m_pFileX[label];
		m_pFileX[label] = nullptr;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
CFileX* CFileXManager::Get(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	// 読み込み
	Load(label);

	return m_pFileX[label];
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
CFileX* CFileXManager::Get(const string& str)
{
	// 変換
	ELabel label = Change(str);

	assert(label > LABEL_NONE && label < LABEL_MAX);

	// 読み込み
	Load(label);

	return m_pFileX[label];
}

//--------------------------------------------------
// 変換
//--------------------------------------------------
const string& CFileXManager::Change(ELabel label)
{
	assert(label > LABEL_NONE && label < LABEL_MAX);

	return FILE_PATH[label];
}

//--------------------------------------------------
// 変換
//--------------------------------------------------
CFileXManager::ELabel CFileXManager::Change(const string& str)
{
	for (int i = 0; i < LABEL_MAX; i++)
	{
		if (FILE_PATH[i] == str)
		{// パスと同じ
			return (ELabel)i;
		}
	}

	return LABEL_NONE;
}
