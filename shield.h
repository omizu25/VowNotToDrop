//======================================================
//
// シールドヘッダー
// Author : Sato Teruto
//
//======================================================
#ifndef _SHIELD_H_
#define _SHIELD_H_	//二重インクルード防止

//-----------------------------
// インクルード
//-----------------------------
#include "model.h"

//================================
// シールドクラスの定義
//================================
class CShield : public CModel
{
public:
	CShield();		//コンストラクタ
	~CShield();		//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//------------------
	// 静的メンバ関数
	//------------------
	static CShield* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_defaultPos;	//初期位置
	D3DXVECTOR3 m_rot;			//向き
};

#endif