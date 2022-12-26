//**************************************************
// 
// obstacle.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBSTACLE_H_	//このマクロ定義がされてなかったら
#define _OBSTACLE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "model.h"

//==================================================
// クラス
//==================================================
class CObstacle : public CModel
{
	/* ↓定義↓ */
public:
	
	/* ↓静的メンバ関数↓ */
public:
	static CObstacle* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CObstacle();			// デフォルトコンストラクタ
	~CObstacle() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
};

#endif // !_OBSTACLE_H_
