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
#include "utility.h"

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
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move)
{
	CObstacle* pObstacle = new CObstacle;

	if (pObstacle == nullptr)
	{// nullチェック
		assert(false);
		return nullptr;
	}

	// 初期化
	pObstacle->Init();

	// 位置の設定
	pObstacle->SetPos(pos);

	// 移動量の設定
	pObstacle->SetMove(move);

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
	// 位置の取得
	D3DXVECTOR3 pos = CModel::GetPos();

	pos += m_move;

	// 位置の設定
	CModel::SetPos(pos);

	if (InRange(&pos, D3DXVECTOR3(550.0f, 0.0f, 550.0f)))
	{// 範囲外に出た
		CObject::SetRelease();
	}

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

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CObstacle::SetMove(const D3DXVECTOR3& move)
{
	m_move = move;
}

//--------------------------------------------------
// 移動量の取得
//--------------------------------------------------
const D3DXVECTOR3& CObstacle::GetMove() const
{
	return m_move;
}