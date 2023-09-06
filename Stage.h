#pragma once
#include "Engine/GameObject.h"
#include <Windows.h>

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

	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

private:
	int hModel_[MAX_COLOR];

	int mode_;	//0:上げる　1:下げる　2:種類を変える
	int select_; //種類

	//その座標の位置のタイプ
};