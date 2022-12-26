//**************************************************
// 
// obstacle.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "obstacle.h"
#include "application.h"

//==================================================
// 定義
//==================================================
namespace
{
const CFileXManager::ELabel MODEL_PATH = CFileXManager::LABEL_NeedleBall;	// ファイルパス
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CObstacle* CObstacle::Create()
{
	CObstacle* pObstacle = new CObstacle;

	if (pObstacle == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pObstacle->Init();

	return pObstacle;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CObstacle::CObstacle() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObstacle::~CObstacle()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CObstacle::Init()
{
	m_move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	// 初期化
	CModel::Init();

	// 位置の設定
	CModel::SetPos(D3DXVECTOR3(0.0f, 10.0f, 0.0f));

	// 使用するモデルの設定
	CModel::SetLabel(MODEL_PATH);

	// クォータニオンの設定
	CModel::SetIsQuaternion(true);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CObstacle::Uninit()
{
	// 終了
	CModel::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CObstacle::Update()
{
	D3DXVECTOR3 pos = CModel::GetPos();
	pos += m_move;
CModel::SetPos(pos);

	// 更新
	CModel::Update();

	// クォータニオンの設定
	CModel::SetQuaternion(m_move);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CObstacle::Draw()
{
	// 描画
	CModel::Draw();
}
