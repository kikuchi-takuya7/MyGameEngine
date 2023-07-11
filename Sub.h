#pragma once
#include "Engine/GameObject.h"

class Fbx;

//◆◆◆を管理するクラス
class Sub : public GameObject
{
public:
    //コンストラクタ
    Sub(GameObject* parent);

    //デストラクタ
    ~Sub();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

private:
    
    Fbx* pFbx_;
};