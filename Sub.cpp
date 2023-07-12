#include "Sub.h"
#include "Engine/Fbx.h"

//�R���X�g���N�^
Sub::Sub(GameObject* parent)
    :GameObject(parent, "Sub"), pFbx_(nullptr)
{
}

//�f�X�g���N�^
Sub::~Sub()
{
}

//������
void Sub::Initialize()
{
    pFbx_ = new Fbx;
	pFbx_->Load("Assets/oden.fbx");
	transform_.scale_ = XMFLOAT3(0.5f,0.5f,0.5f);
}

//�X�V
void Sub::Update()
{
	transform_.rotate_.y--;
	transform_.rotate_.z++;
	static int i = 0;
	i++;
	if (i >= 60) {
		KillMe();
	}
}

//�`��
void Sub::Draw()
{
	pFbx_->Draw(this->transform_);
}

//�J��
void Sub::Release()
{
	pFbx_->Release();
	delete pFbx_;
}