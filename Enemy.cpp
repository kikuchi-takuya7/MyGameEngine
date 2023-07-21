#include "Enemy.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/SphereCollider.h"


//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), pFbx_(nullptr)
{

}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{
    pFbx_ = new Fbx;
    pFbx_->Load("Assets/oden.fbx");
    transform_.position_.z = 20.0f;

    SphereCollider* col = new SphereCollider(1.0f);
    AddCollider(col);
}

//�X�V
void Enemy::Update()
{
    
}

//�`��
void Enemy::Draw()
{
    pFbx_->Draw(this->transform_);
}

//�J��
void Enemy::Release()
{
    pFbx_->Release();
    delete pFbx_;
}