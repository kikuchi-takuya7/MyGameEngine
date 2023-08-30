#include "Stage.h"
#include "Engine/Model.h"

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
