#include "PlayScene.h"
#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"


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

	if (Input::IsKeyDown(DIK_RETURN)) {

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}

}

//描画
void PlayScene::Draw()
{
	
}

//開放
void PlayScene::Release()
{
	
}