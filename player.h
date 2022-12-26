//**************************************************
// 
// player.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PLAYER_H_	//このマクロ定義がされてなかったら
#define _PLAYER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "model.h"

//==================================================
// クラス
//==================================================
class CPlayer : public CModel
{
	/* ↓定義↓ */
public:

	/* ↓静的メンバ変数↓ */
private:
	static int m_killCount;	// キルカウント

	/* ↓静的メンバ関数↓ */
public:
	static void CreateAll();	// 全ての生成
	static CPlayer* Create(int index, float posDest);	// 生成
	static void AddKill();	// キルカウントの加算

	/* ↓メンバ関数↓ */
public:
	CPlayer();				// デフォルトコンストラクタ
	~CPlayer() override;	// デストラクタ

public: 
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:

	/* ↓メンバ変数↓ */
private:
	int m_index;	// 番号
	float m_posDest;	// 目的の位置
};

#endif // !_OBSTACLE_H_
