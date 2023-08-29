#include "Stage.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"),hModel_{-1,-1,-1,-1,-1}
{
}

//������
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
	//���f���f�[�^�̃��[�h
	for (int i = 0; i < MAX_COLOR; i++) {
		hModel_[i] = Model::Load(fname_Base + modelname[i]);
		assert(hModel_[i] >= 0);
	}

	for (int x = 0; x < XSIZE; x++) {
		for (int z = 0; z < ZSIZE; z++) {
			if (x < 1) {
				table_[x][z] = WATER;
			}
			else {
				table_[x][z] = rand() % 5;
			}
			
		}
	}
	
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{

	for (int x = 0; x < 15; x++) {
		for (int z = 0; z < 15; z++) {

			int type = table_[x][z];

			Transform blockTrans;
			blockTrans.position_.z = z;
			blockTrans.position_.x = x;
			Model::SetTransform(hModel_[type], blockTrans);
			Model::Draw(hModel_[type]);
		}
	}
	
}

//�J��
void Stage::Release()
{
}
