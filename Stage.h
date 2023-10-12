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

	//ダイアログプロシージャ
	BOOL DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

	//各種update関数
	void Dlg_Up_Update(int _changeX, int _changeZ);
	void Dlg_Down_Update(int _changeX, int _changeZ);
	void Dlg_Change_Update(int _changeX, int _changeZ);

	//レイが当たってたらisHitがtrueになって変更される位置のx,zが返される
	void CheckHitRay(bool &_isHit, int &_changeX, int &_changeZ);

	//セーブする
	void Save();

	void NameSave();

	void Load();

	void NewCreate();

	void NowFileLoad();


private:
	int hModel_[MAX_COLOR];

	DLGSTATE mode_;	//0:上げる　1:下げる　2:種類を変える
	COLOR select_; //種類

	char fileName_[MAX_PATH];  //ファイル名を入れる変数

};