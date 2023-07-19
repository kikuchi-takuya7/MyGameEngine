#include "PlayScene.h"
#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"


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

	if (Input::IsKeyDown(DIK_RETURN)) {

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}

}

//�`��
void PlayScene::Draw()
{
	
}

//�J��
void PlayScene::Release()
{
	
}