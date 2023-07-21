#include "Enemy.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/SphereCollider.h"


//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), pFbx_(nullptr)
{

}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
    pFbx_ = new Fbx;
    pFbx_->Load("Assets/oden.fbx");
    transform_.position_.z = 20.0f;

    SphereCollider* col = new SphereCollider(1.0f);
    AddCollider(col);
}

//更新
void Enemy::Update()
{
    
}

//描画
void Enemy::Draw()
{
    pFbx_->Draw(this->transform_);
}

//開放
void Enemy::Release()
{
    pFbx_->Release();
    delete pFbx_;
}