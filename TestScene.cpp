#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"


//�R���X�g���N�^
TestScene::TestScene(GameObject* parent)
    :GameObject(parent, "TestScene")
{

}

//�f�X�g���N�^
TestScene::~TestScene()
{
}

//������
void TestScene::Initialize()
{
    
}

//�X�V
void TestScene::Update()
{
    if (Input::IsKeyDown(DIK_RETURN)) {

        SceneManager* pSceneManager = (SceneManager* )FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_PLAY);
    }
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}