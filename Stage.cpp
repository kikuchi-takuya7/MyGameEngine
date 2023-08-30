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
			table_[x][z].color = WATER;
			table_[x][z].height = 0;
			
		}
	}

	SetBlockHeght(5, 5, 3);
	
}

//�X�V
void Stage::Update()
{
	
}

//�`��
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

//�J��
void Stage::Release()
{
}

void Stage::SetBlock(int _x, int _z, COLOR _type)
{
	table_[_x][_z].color = _type;
	//�ꎟ���z��œ񎟌��z���\������Ȃ�
	//table_[_x * XSIZE +_z] = _type;
	//�|���Z�����ɂ��邩��Ax���W���O�̎���XSIZE���O�ɂȂ�z���W�������K�p�����Bx��2�Ƃ��Ȃ�30����ƂȂ�3�s�ڂ��炢�ɓ���
}

void Stage::SetBlockHeght(int _x, int _z, int _height)
{
	table_[_x][_z].height = _height;
}
