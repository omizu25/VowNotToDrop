//**************************************************
// 
// result.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RESULT_H_	//このマクロ定義がされてなかったら
#define _RESULT_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CMenu;
class CRanking;

//==================================================
// クラス
//==================================================
class CResult : public CMode
{
	/* 定義 */
public:

	/* ↓メンバ関数↓ */
public:
	CResult();				// デフォルトコンストラクタ
	~CResult() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	/* ↓メンバ変数↓ */
private:
	void Input();	// 入力

	/* メンバ変数 */
private:
	CMenu* m_pMenu;	// メニューの情報
	CRanking* m_pRanking;
};

#endif // !_RESULT_H_
