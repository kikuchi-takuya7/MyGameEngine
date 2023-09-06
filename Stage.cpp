#include "Stage.h"
#include "Engine/Model.h"
#include "resource.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"


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
	//モデルデータのロード
	for (int i = 0; i < MAX_COLOR; i++) {
		hModel_[i] = Model::Load(fname_Base + modelname[i]);
		assert(hModel_[i] >= 0);
	}

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			table_[x][z].color = WATER;
			table_[x][z].height = 0;
			
		}
	}

	SetBlockHeght(5, 5, 3);
	
}

//更新
void Stage::Update()
{
	float w = (float)(Direct3D::scrWidth/2.0f);
	float h = (float)(Direct3D::scrHeight/2.0f);
	float offsetX = 0;
	float offsetY = 0;
	float minZ = 0;
	float maxZ = 1;

	XMMATRIX vp =
	{
		w                ,0                ,0           ,0,
		0                ,-h                ,0           ,0,
		0                ,0                ,maxZ-minZ   ,0,
		offsetX + w      ,offsetY + h      ,minZ        ,1
	};

	//ビューポート
	XMMATRIX invVP =
	//プロジェクション変換
	XMMATRIX invProj =
	//びゅー変換
	XMMATRIX invView =
	XMFLOAT3 mouesPosFront = GetMousePos();
	mousePosFront.z = 0.0;
	XMFLOAT3 mousePosBack = ごにょごおのよ
	MosuePosBack.z = 1.0f;

	//1,mousePosFrontをベクトルに変換
	//2. 1にinvVP,invPrj,invViewをかける
	//3,mousePosBackをベクトルに変換
	//4,3にinvVP,invPrj,invVeewをかける
	//5,2から4に向かってレイを打つ（とりあえず）
	//6 レイが当たったらブレークポイント
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
		mode_ = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		return TRUE;
	}

	/*case WM_COMMAND:
		mode_ = SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		return TRUE;*/
	}
	return FALSE;
}