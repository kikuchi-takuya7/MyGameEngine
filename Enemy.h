#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

//テストシーンを管理するクラス
class Enemy : public GameObject
{
	Fbx* pFbx_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);
	~Enemy();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};