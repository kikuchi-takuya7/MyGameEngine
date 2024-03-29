#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include <fstream>
#include <iostream>

//const LPCSTR fileName = "Assets/無題.map";

//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),hModel_{-1,-1,-1,-1,-1},fileName_{"新規フォルダ.bin"}
{
}

//初期化
void Stage::Initialize()
{

	srand(time(NULL));

	string modelname[] = {
		"BoxDefault.fbx",
		"BoxBrick.fbx",
		"BoxGrass.fbx",
		"BoxSand.fbx",
		"BoxWater.fbx"
	};

	string fname_Base = "assets/";


	//セーブは高さ種類高さ種類で行く

	//モデルデータのロード
	for (int i = 0; i < MAX_COLOR; i++) {
		hModel_[i] = Model::Load(fname_Base + modelname[i]);
		assert(hModel_[i] >= 0);
	}

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			table_[x][z].color = DEFAULT;
			table_[x][z].height = 0;
			
		}
	}

	Load();
	//SetBlockHeght(5, 5, 3);
	
}

//更新
void Stage::Update()
{


	if (!Input::IsMouseButtonDown(0))
		return;


	int changeX = 0;
	int	changeZ = 0;
	bool isHit = false;

	CheckHitRay(isHit, changeX, changeZ);

	switch (mode_)
	{
	case DLG_UP:

		if (isHit && table_[changeX][changeZ].height < 5) {//5以上いかないように
			Dlg_Up_Update(changeX, changeZ);
		}
			
		break;

	case DLG_DOWN:

		if (isHit && table_[changeX][changeZ].height > 0) {//０以下にならないように
			Dlg_Down_Update(changeX, changeZ);
		}
			
		break;

	case DLG_CHANGE:
		if (isHit) {
			Dlg_Change_Update(changeX, changeZ);
		}
			
		break;

	case DLG_END:
		break;
	default:
		break;
	}
	
}

//描画
void Stage::Draw()
{

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			for (int y = 0; y < table_[x][z].height + 1; y++) {
				int type = table_[x][z].color;
				
				Transform blockTrans;
				blockTrans.position_.z = z;
				blockTrans.position_.x = x;
				blockTrans.position_.y = y;
				Model::SetTransform(hModel_[type], blockTrans);
				Model::Draw(hModel_[type]);
				
			}
		}
	}
	
}

//開放
void Stage::Release()
{
}

void Stage::SetBlock(int _x, int _z, COLOR _type)
{
	table_[_x][_z].color = _type;
	//一次元配列で二次元配列を表現するなら
	//table_[_x * XSIZE +_z] = _type;
	//掛け算から先にするから、x座標が０の時はXSIZEも０になりz座標だけが適用される。xが2とかなら30からとなり3行目ぐらいに入る
}

void Stage::SetBlockHeght(int _x, int _z, int _height)
{
	table_[_x][_z].height = _height;
}

//CALLBACKを消すことによってただのメンバ関数にする
BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		//ダイアログができたとき
	case WM_INITDIALOG: {
		//ラジオボタンの初期化
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);

		const char* modelname[] = {
		"デフォルト",
		"石",
		"草",
		"砂",
		"水"
		};
		//コンボボックスの初期化
		for (int i = 0; i < 5; i++) {
			SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)modelname[i]);
		}

		mode_ = (DLGSTATE)SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);

		return TRUE;
	}

	case WM_COMMAND:

		switch (LOWORD(wp)) 
		{
		case IDC_BACK:
			BackUpLoad();
			return TRUE;
			break;
		case IDC_FORWARD:
			RedoLoad();
			return TRUE;
			break;
		}

		if (IsDlgButtonChecked(hDlg, IDC_RADIO_UP)) {
			mode_ = DLG_UP;
			return TRUE;
		}
		if (IsDlgButtonChecked(hDlg, IDC_RADIO_DOWN)) {
			mode_ = DLG_DOWN;
			return TRUE;
		}
		if (IsDlgButtonChecked(hDlg, IDC_RADIO_CHANGE)) {
			select_ = (COLOR)SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			mode_ = DLG_CHANGE;
			return TRUE;
		}

		return TRUE;
	}
	return FALSE;
}

void Stage::Dlg_Up_Update(int _changeX, int _changeZ)
{
	ClearRedo();
	BackUpSave(_changeX,_changeZ);
	table_[_changeX][_changeZ].height++;

}

void Stage::Dlg_Down_Update(int _changeX, int _changeZ)
{
	ClearRedo();
	BackUpSave(_changeX, _changeZ);
	table_[_changeX][_changeZ].height--;

}

void Stage::Dlg_Change_Update(int _changeX, int _changeZ)
{
	ClearRedo();
	BackUpSave(_changeX, _changeZ);
	table_[_changeX][_changeZ].color = select_;
	
}

void Stage::CheckHitRay(bool &_isHit, int &_changeX, int &_changeZ)
{
	float w = (float)(Direct3D::scrWidth / 2.0f);
	float h = (float)(Direct3D::scrHeight / 2.0f);
	float offsetX = 0;
	float offsetY = 0;
	float minZ = 0;
	float maxZ = 1;

	//ビューポート作成
	XMMATRIX vp =
	{
		w                ,0                ,0           ,0,
		0                ,-h               ,0           ,0,
		0                ,0                ,maxZ - minZ ,0,
		offsetX + w      ,offsetY + h      ,minZ        ,1
	};

	//ビューポートを逆行列に
	XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
	//プロジェクション変換
	XMMATRIX invProj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
	//びゅー変換
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());
	XMVECTOR mousePosVec = Input::GetMousePosition();
	XMFLOAT3 mousePosFront;
	XMStoreFloat3(&mousePosFront, mousePosVec);
	mousePosFront.z = 0.0;
	XMVECTOR mouseVec = Input::GetMousePosition();
	XMFLOAT3 mousePosBack;
	XMStoreFloat3(&mousePosBack, mouseVec);
	mousePosBack.z = 1.0f;

	//1,mousePosFrontをベクトルに変換
	XMVECTOR vMouseFront = XMLoadFloat3(&mousePosFront);
	//2. 1にinvVP,invPrj,invViewをかける
	vMouseFront = XMVector3TransformCoord(vMouseFront, invVP * invProj * invView);
	//3,mousePosBackをベクトルに変換
	XMVECTOR vMouseBack = XMLoadFloat3(&mousePosBack);
	//4,3にinvVP,invPrj,invVeewをかける
	vMouseBack = XMVector3TransformCoord(vMouseBack, invVP * invProj * invView);
	//5,2から4に向かってレイを打つ（とりあえず）

	float minDist = 9999;
	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			for (int y = 0; y < table_[x][z].height + 1; y++) {

				RAYCASTDATA data;
				data.hit = false;
				XMStoreFloat4(&data.start, vMouseFront);
				XMStoreFloat4(&data.dir, vMouseBack - vMouseFront);
				Transform trans;
				trans.position_.x = x;
				trans.position_.y = y;
				trans.position_.z = z;
				Model::SetTransform(hModel_[0], trans);

				Model::RayCast(hModel_[0], data);

				//わざわざisHitを作ってるのはfor文の最後のdata.hitがfalseだった時でも問題なくするため
				if (data.hit) {
					if (minDist > data.dist) {
						minDist = data.dist;
						_changeX = x;
						_changeZ = z;
					}
					_isHit = true;
				}
			}
		}
	}
}

void Stage::Save()
{

	//「ファイルを保存」ダイアログの設定
	OPENFILENAME ofn = InitOpenFileName();                         	//名前をつけて保存ダイアログの設定用構造体


	//「ファイルを保存」ダイアログ
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return;

	std::ofstream ofs(fileName_, std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
		std::cerr << "ファイルオープンに失敗" << std::endl;
		std::exit(1);
	}

	SaveTheTable(ofs);

	ofs.close();

}

void Stage::NameSave()
{
	//char fileName[MAX_PATH] = "無題.map";  //ファイル名を入れる変数

	//「ファイルを保存」ダイアログの設定
	OPENFILENAME ofn = InitOpenFileName();                         	//名前をつけて保存ダイアログの設定用構造体


	//「ファイルを保存」ダイアログ
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return;

	std::ofstream ofs(fileName_, std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
		std::cerr << "ファイルオープンに失敗" << std::endl;
		std::exit(1);
	}

	SaveTheTable(ofs);
	ofs.close();
}

void Stage::Load()
{
	//「ファイルを保存」ダイアログの設定
	OPENFILENAME ofn;//名前をつけて保存ダイアログの設定用構造体
	ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
	ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
	ofn.lpstrFilter = TEXT("バイナリデータ(*.bin)\0*.bin\0")
		TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
	ofn.lpstrFile = fileName_;               	//ファイル名
	ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
	ofn.Flags = OFN_FILEMUSTEXIST;   		//フラグ（同名ファイルが存在したら上書き確認）
	ofn.lpstrDefExt = "map";                  	//デフォルト拡張子

	//「ファイルを保存」ダイアログ
	BOOL selFile;
	selFile = GetOpenFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return;


	std::ifstream ifs(fileName_, std::ios_base::in | std::ios_base::binary);

	if (!ifs) {
		std::cerr << "ファイルオープンに失敗" << std::endl;
		std::exit(1);
	}

	LoadTheTable(ifs);
	
	ifs.close();
}

void Stage::NewCreate()
{
	OPENFILENAME ofn = InitOpenFileName();//名前をつけて保存ダイアログの設定用構造体
	
	//「ファイルを保存」ダイアログ
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//キャンセルしたら中断
	if (selFile == FALSE) return;

	std::ofstream ofs(fileName_, std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
		std::cerr << "ファイルオープンに失敗" << std::endl;
		std::exit(1);
	}

	//新規ファイルの初期化
	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			table_[x][z].color = DEFAULT;
			table_[x][z].height = 0;

		}
	}

	SaveTheTable(ofs);

	ofs.close();

	NowFileLoad();
}

void Stage::NowFileLoad()
{
	std::ofstream ofs(fileName_, std::ios_base::out | std::ios_base::binary);

	if (!ofs) {
		std::cerr << "ファイルオープンに失敗" << std::endl;
		std::exit(1);
	}

	SaveTheTable(ofs);

	ofs.close();
}

void Stage::SaveTheTable(std::ofstream& _ofs)
{
	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {

			_ofs.write((const char*)&table_[x][z].height, sizeof(int));
			_ofs.write((const char*)&table_[x][z].color, sizeof(int));
		}
	}
}

void Stage::LoadTheTable(std::ifstream& _ifs)
{

	//読込サイズを調べる。
	//ifs.seekg(0, std::ios_base::end);//読み込み位置を一番最後に
	//long long int size = ifs.tellg();//現在の読み込み位置を取得（一番最後だからファイルサイズになるはず）
	//ifs.seekg(0);

	/*char* data = new char[size];
	ifs.read(data, size);*/

	DWORD nowBytes = 0;

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {

			string result = "";
			//std::decを使えば10新数に変えてくれるからそれつかえ
			//char型にいったん入れて

#if 0
			//csvで読み込めるようにしたコードの名残
			//

			for (int i = 0; i < sizeof(int); i++) {//dwbyteの中に読み込んだサイズが入ってるからよくないね
				result += data[nowBytes];
				nowBytes++;//次のバイト文字をターゲッティング
			}

			nowBytes++;//コンマの部分を飛ばす

			table_[x][z].height = stoi(result, 0, 2);

			result.erase();

			for (int i = 0; i < sizeof(int); i++) {
				result += data[nowBytes];
				nowBytes++;
			}

			nowBytes++;

			table_[x][z].color = (COLOR)stoi(result, 0, 2);
#else
			//ifs.read(data, sizeof(int));

			//dataに値が入らないおかしいよ
			int cSize = sizeof(int);

			_ifs.read((char*)&table_[x][z].height, cSize);
			_ifs.read((char*)&table_[x][z].color, cSize);


			//result = data;
			//nowBytes++;//コンマの部分を飛ばす

			//table_[x][z].height = stoi(result, nullptr, 2);

			//result.erase();

			//nowBytes++;
			//result = data;

			//table_[x][z].color = (COLOR)stoi(result, nullptr, 2);

#endif
		}
	}
}

OPENFILENAME Stage::InitOpenFileName()
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));            	//構造体初期化
	ofn.lStructSize = sizeof(OPENFILENAME);   	//構造体のサイズ
	ofn.lpstrFilter = TEXT("バイナリデータ(*.bin)\0*.bin\0")
					  TEXT("すべてのファイル(*.*)\0*.*\0\0");     //─┘
	ofn.lpstrFile = fileName_;               	//ファイル名
	ofn.nMaxFile = MAX_PATH;               	//パスの最大文字数
	ofn.Flags = OFN_OVERWRITEPROMPT;   		//フラグ（同名ファイルが存在したら上書き確認）
	ofn.lpstrDefExt = "map";                  	//デフォルト拡張子

	return ofn;
}

void Stage::BackUpSave(int _x, int _z)
{
	BackUpData backUp = BackUpData(_x, _z, table_[_x][_z].height, table_[_x][_z].color);
	backUp_.push(backUp);
}

void Stage::BackUpLoad()
{
	//何もないならリターン
	if (backUp_.empty())
		return;

	//やり直す用のデータを保存して、一つ戻してpopする
	BackUpData b = backUp_.top();
	backUp_.pop();

	RedoSave(b.x, b.z);

	table_[b.x][b.z].color = b.color;
	table_[b.x][b.z].height = b.height;
}



void Stage::RedoSave(int _x, int _z)
{
	BackUpData redo = BackUpData(_x, _z, table_[_x][_z].height, table_[_x][_z].color);
	redo_.push(redo);
}

void Stage::RedoLoad()
{

	if (redo_.empty())
		return;

	BackUpData b = redo_.top();
	redo_.pop();

	BackUpSave(b.x, b.z);

	table_[b.x][b.z].color = b.color;
	table_[b.x][b.z].height = b.height;
	
}

void Stage::ClearRedo()
{
	while (!redo_.empty())
	{
		redo_.pop();
	}
}
