#pragma once
#include "Engine/GameObject.h"

namespace {
	const int XSIZE{ 15 };
	const int ZSIZE{ 15 };
	enum COLOR {
		DEFAULT,
		BRINK,
		GRASS,
		SAND,
		WATER,
		MAX_COLOR
	};
}

//■■シーンを管理するクラス
class Stage : public GameObject
{
public:

	void SetBlock(int _x, int _z, COLOR _type);

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

private:
	int hModel_[MAX_COLOR];
	int table_[XSIZE][ZSIZE];

};