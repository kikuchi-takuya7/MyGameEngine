#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"

const LPCSTR fileName = "MapSave";

//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),hModel_{-1,-1,-1,-1,-1}
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

		if (isHit && table_[changeX][changeZ].height < 5) {
			Dlg_Up_Update(changeX, changeZ);
		}
			
		break;

	case DLG_DOWN:

		if (isHit && table_[changeX][changeZ].height > 0) {
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
			Transform blockTrans;
			blockTrans.position_.z = z;
			blockTrans.position_.x = x;

			for (int y = 0; y < table_[x][z].height + 1; y++) {
				int type = table_[x][z].color;
				
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

		if (IsDlgButtonChecked(hDlg, ID_MENU_NEW)) {

		}
		else if (IsDlgButtonChecked(hDlg, ID_MENU_OPEN)) {

		}
		else if (IsDlgButtonChecked(hDlg, ID_MENU_SAVE)) {
			Save();
		}

		if (IsDlgButtonChecked(hDlg, IDC_RADIO_UP)) {
			mode_ = DLG_UP;
			return TRUE;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_RADIO_DOWN)) {
			mode_ = DLG_DOWN;
			return TRUE;
		}
		else if (IsDlgButtonChecked(hDlg, IDC_RADIO_CHANGE)) {
			mode_ = DLG_CHANGE;
			//return TRUE;
		}

		

		select_ = (COLOR)SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_GETCURSEL, 0, 0);

		return TRUE;
	}
	return FALSE;
}

void Stage::Dlg_Up_Update(int _changeX, int _changeZ)
{
	table_[_changeX][_changeZ].height++;

}

void Stage::Dlg_Down_Update(int _changeX, int _changeZ)
{
	table_[_changeX][_changeZ].height--;

}

void Stage::Dlg_Change_Update(int _changeX, int _changeZ)
{
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

				//わざわざisHitを作ってるのは
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
	HANDLE hFile;        //ファイルのハンドル
	hFile = CreateFile(
		fileName,                 //ファイル名
		GENERIC_WRITE,           //アクセスモード（書き込み用）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		CREATE_ALWAYS ,           //作成方法
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL);                  //拡張属性（なし）

	if (hFile == INVALID_HANDLE_VALUE) {//失敗したとき
		PostQuitMessage(0);
		return;
	}

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {

			string str = std::to_string(table_[x][z].height) + "," + std::to_string(table_[x][z].color) + ",";
			//string str = std::to_string(table_[x][z].color);

			DWORD dwBytes = 0;  //書き込み位置
			WriteFile(
				hFile,                   //ファイルハンドル
				str.c_str(),                  //保存するデータ（文字列）
				(DWORD)strlen(str.c_str()),   //書き込む文字数
				&dwBytes,                //書き込んだサイズを入れる変数
				NULL);                   //オーバーラップド構造体（今回は使わない）

		}
	}
	
	CloseHandle(hFile);

}

void Stage::Load()
{
	HANDLE hFile;        //ファイルのハンドル
	hFile = CreateFile(
		fileName,                 //ファイル名
		GENERIC_READ,           //アクセスモード（書き込み用）
		0,                      //共有（なし）
		NULL,                   //セキュリティ属性（継承しない）
		OPEN_ALWAYS,           //作成方法
		FILE_ATTRIBUTE_NORMAL,  //属性とフラグ（設定なし）
		NULL);                  //拡張属性（なし）

	if (hFile == INVALID_HANDLE_VALUE) {//失敗したとき
		PostQuitMessage(0);
		return;
	}

	//先にファイルの中身を全部読み込んでからコンマの処理
			//ファイルのサイズを取得
	DWORD fileSize = GetFileSize(hFile, NULL);

	//ファイルのサイズ分メモリを確保
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //読み込み位置

	ReadFile(
		hFile,     //ファイルハンドル
		data,      //データを入れる変数
		fileSize,  //読み込むサイズ
		&dwBytes,  //読み込んだサイズ
		NULL);     //オーバーラップド構造体（今回は使わない）

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {

			string result;
			while (data[dwBytes] != ',' || data[dwBytes] != '\n') {
				result += data[dwBytes];
				dwBytes++;
			}

			table_[x][z].height = atoi(result.c_str());

			result.erase();
			while (data[dwBytes] != ',' || data[dwBytes] != '\n') {
				result += data[dwBytes];
				dwBytes++;
			}

			table_[x][z].color = (COLOR)atoi(result.c_str());

		}
	}
}
