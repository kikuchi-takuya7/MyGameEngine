#include "PlayScene.h"
#include "Player.h"
#include "Engine/Fbx.h"


//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{

	GameObject* pPlayer = Instantiate<Player>(this);
}

//更新
void PlayScene::Update()
{
	transform_.rotate_.y++;
}

//描画
void PlayScene::Draw()
{
	
}

//開放
void PlayScene::Release()
{
	
}