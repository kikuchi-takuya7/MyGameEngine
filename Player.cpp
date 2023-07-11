#include "Player.h"
#include "Engine/Fbx.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), pFbx_(nullptr)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Assets/oden.fbx");
	this->transform_.position_.x = 0.0f;
	this->transform_.position_.y = 0.0f;
	this->transform_.position_.z = 0.0f;
}

//�X�V
void Player::Update()
{
	transform_.rotate_.y += 1;
}

//�`��
void Player::Draw()
{
	pFbx_->Draw(this->transform_);
}

//�J��
void Player::Release()
{
	pFbx_->Release();
	delete pFbx_;
}