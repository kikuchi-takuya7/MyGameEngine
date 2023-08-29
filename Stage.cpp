#include "Stage.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_(-1)
{
}

//������
void Stage::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("assets/BoxDefault.fbx");
	assert(hModel_ >= 0);

	
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
	Transform blockTrans;

	for (int x = 0; x < 15; x++) {
		for (int z = 0; z < 15; z++) {
			blockTrans.position_.z = z;
			blockTrans.position_.x = x;
			Model::SetTransform(hModel_, blockTrans);
			Model::Draw(hModel_);
		}
	}
	
}

//�J��
void Stage::Release()
{
}