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

	enum DLGSTATE {
		DLG_UP,
		DLG_DOWN,
		DLG_CHANGE,
		DLG_END
	};

	struct BrockType
	{
		COLOR color;
		int height;
	}table_[XSIZE][ZSIZE];

	struct DistList
	{
		float hitDist;
		int hitX;
		int hitZ;
	}distlist_;

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

	void Dlg_Up_Update(XMVECTOR vMouseFront, XMVECTOR vMouseBack);

	void Dlg_Down_Update(XMVECTOR vMouseFront, XMVECTOR vMouseBack);

	void Dlg_Change_Update(XMVECTOR vMouseFront, XMVECTOR vMouseBack);

private:
	int hModel_[MAX_COLOR];

	DLGSTATE mode_;	//0:上げる　1:下げる　2:種類を変える
	COLOR select_; //種類

	//その座標の位置のタイプ
};