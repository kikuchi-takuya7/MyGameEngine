#include "PlayScene.h"
#include "Player.h"
#include "Engine/Fbx.h"


//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{

	GameObject* pPlayer = Instantiate<Player>(this);
}

//�X�V
void PlayScene::Update()
{
	transform_.rotate_.y++;
}

//�`��
void PlayScene::Draw()
{
	
}

//�J��
void PlayScene::Release()
{
	
}