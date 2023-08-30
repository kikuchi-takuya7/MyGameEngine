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

	struct BrockType
	{
		COLOR color;
		int height;
	}table_[XSIZE][ZSIZE];

}



//■■シーンを管理するクラス
class Stage : public GameObject
{
public:

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

	//ブロックのセット
	void SetBlock(int _x, int _z, COLOR _type);

	void SetBlockHeght(int _x, int _z, int _height);

private:
	int hModel_[MAX_COLOR];

	//その座標の位置のタイプ
	
	

};