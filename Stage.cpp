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
			table_[x][z].color = DEFAULT;
			table_[x][z].height = 0;
			
		}
	}

	SetBlockHeght(5, 5, 3);
	
}

//更新
void Stage::Update()
{


	if (!Input::IsMouseButtonDown(0))
		return;

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

	switch (mode_)
	{
	case DLG_UP:
		Dlg_Up_Update(vMouseFront, vMouseBack);
		break;
	case DLG_DOWN:
		Dlg_Down_Update(vMouseFront, vMouseBack);
		break;
	case DLG_CHANGE:
		Dlg_Change_Update(vMouseFront, vMouseBack);
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

void Stage::Dlg_Up_Update(XMVECTOR vMouseFront, XMVECTOR vMouseBack)
{
	int changeX = 0;
	int	changeZ = 0;
	float minDist = 9999.9f;
	bool isHit = false;

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

				if (data.hit) {
					if (minDist > data.dist) {
						minDist = data.dist;
						changeX = x;
						changeZ = z;
					}
					isHit = true;
				}
			}
		}
	}

	if(isHit)
		table_[changeX][changeZ].height++;

}

void Stage::Dlg_Down_Update(XMVECTOR vMouseFront, XMVECTOR vMouseBack)
{
	

	int changeX = 0;
	int	changeZ = 0;
	float minDist = 9999;
	bool isHit = false;

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			for (int y = 0; y < table_[x][z].height; y++) {

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

				if (data.hit) {
					if (minDist > data.dist) {
						minDist = data.dist;
						changeX = x;
						changeZ = z;
					}
					isHit = true;
				}
			}
		}
	}

	if (isHit)
		table_[changeX][changeZ].height--;

}

void Stage::Dlg_Change_Update(XMVECTOR vMouseFront, XMVECTOR vMouseBack)
{
	
	int changeX = 0;
	int	changeZ = 0;
	float minDist = 9999;
	bool isHit = false;
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

				if (data.hit) {
					if (minDist > data.dist) {
						minDist = data.dist;
						changeX = x;
						changeZ = z;
					}
					isHit = true;
				}
			}
		}
	}

	table_[changeX][changeZ].color = select_;
}
