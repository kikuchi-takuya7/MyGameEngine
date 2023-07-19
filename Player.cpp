#include "Player.h"
#include "Sub.h"
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
	
	GameObject* pSub = Instantiate<Sub>(this);
	pSub->SetPosition(XMFLOAT3(-2, 1, 0));
	pSub->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
	GameObject* pSub2 = Instantiate<Sub>(this);
	pSub2->SetTransform(pSub->GetTransform());
	pSub2->SetPosition(XMFLOAT3(2, 1, 0));
	//pSub2->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
}

//�X�V
void Player::Update()
{
	transform_.rotate_.y += 1;

	static int i = 0;
	i++;
	if (i >= 120) {
		//KillMe();
	}
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