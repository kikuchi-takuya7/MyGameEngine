#include "Player.h"
#include "Engine/Fbx.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), pFbx_(nullptr)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Assets/oden.fbx");
	this->transform_.position_.x = 0.0f;
	this->transform_.position_.y = 0.0f;
	this->transform_.position_.z = 0.0f;
}

//更新
void Player::Update()
{
	transform_.rotate_.y += 1;
}

//描画
void Player::Draw()
{
	pFbx_->Draw(this->transform_);
}

//開放
void Player::Release()
{
	pFbx_->Release();
	delete pFbx_;
}