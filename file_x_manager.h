//**************************************************
// 
// file_x_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _FILE_X_MANAGER_H_	//このマクロ定義がされてなかったら
#define _FILE_X_MANAGER_H_	//２重インクルード防止のマクロ定義

//==================================================
// 前方宣言
//==================================================
class CFileX;

//==================================================
// クラス
//==================================================
class CFileXManager
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,	// 使用しない
		LABEL_Hummar = 0,	// ハンマー
		LABEL_WoodBox,		// 木箱
		LABEL_Fish_Tail,	// 魚の尻尾
		LABEL_Fish_Body,	// 魚の身体
		LABEL_Angel_Body,				// 天使の体
		LABEL_Angel_Head,				// 天使の頭
		LABEL_Angel_RightArmTop,		// 天使の右腕上
		LABEL_Angel_RightArmBottom,		// 天使の右腕下
		LABEL_Angel_RightHand,			// 天使の右手
		LABEL_Angel_LeftArmTop,			// 天使の左腕上
		LABEL_Angel_LeftArmBottom,		// 天使の左腕下
		LABEL_Angel_LeftHand,			// 天使の左手
		LABEL_Angel_RightFootTop,		// 天使の右足上
		LABEL_Angel_RightFootBottom,	// 天使の右足下
		LABEL_Angel_RightFoot,			// 天使の右足
		LABEL_Angel_LeftFootTop,		// 天使の左足上
		LABEL_Angel_LeftFootBottom,		// 天使の左足下
		LABEL_Angel_LeftFoot,			// 天使の左足
		LABEL_Terutreu_Rope,			// てるてるの縄
		LABEL_Terutreu_Head,			// てるてるの頭
		LABEL_Terutreu_Body,			// てるてるの体
		LABEL_Terutreu_Right_ear,		// てるてるの右耳
		LABEL_Terutreu_Left_ear,		// てるてるの左耳
		LABEL_Terutreu_Angel_ring,		// てるてるの天使の輪
		LABEL_Terutreu_Angel_wing,		// てるてるの天使の羽
		LABEL_Terutreu_Devil_wing,		// てるてるの悪魔の羽
		LABEL_Terutreu_Morning_koko,	// てるてるの朝ココ
		LABEL_MAX
	};

	/* ↓メンバ関数↓ */
public:
	CFileXManager();	// デフォルトコンストラクタ
	~CFileXManager();	// デストラクタ

public:
	void LoadAll();						// 全ての読み込み
	void Load(ELabel label);			// 指定の読み込み
	void Load(const string& str);		// 指定の読み込み
	void ReleaseAll();					// 全ての破棄
	void Release(ELabel label);			// 指定の破棄
	void Release(const string& str);	// 指定の破棄
	CFileX* Get(ELabel label);			// 情報の取得
	CFileX* Get(const string& str);		// 情報の取得
	const string& Change(ELabel label);	// 変換
	ELabel Change(const string& str);	// 変換

	/* ↓メンバ変数↓ */
private:
	CFileX* m_pFileX[LABEL_MAX];	// Xファイルの情報
};

#endif // !_FILE_X_MANAGER_H_
