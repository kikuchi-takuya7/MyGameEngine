#include "Sub.h"
#include "Engine/Fbx.h"

//コンストラクタ
Sub::Sub(GameObject* parent)
    :GameObject(parent, "Sub"), pFbx_(nullptr)
{
}

//デストラクタ
Sub::~Sub()
{
}

//初期化
void Sub::Initialize()
{
    pFbx_ = new Fbx;
	pFbx_->Load("Assets/oden.fbx");
	this->transform_.position_.x = -3.0f;
	this->transform_.position_.y = 0.0f;
	this->transform_.position_.z = 0.0f;
	transform_.scale_ = XMFLOAT3(0.5f,0.5f,0.5f);
}

//更新
void Sub::Update()
{
	//transform_.rotate_.y--;
	static int i = 0;
	i++;
	if (i >= 60) {
	//	KillMe();
	}
}

//描画
void Sub::Draw()
{
	pFbx_->Draw(this->transform_);
}

//開放
void Sub::Release()
{
	pFbx_->Release();
	delete pFbx_;
}