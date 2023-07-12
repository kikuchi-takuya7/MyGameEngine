#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Engine/Transform.h"
#include <string>
#include <vector>

using std::vector;
using std::string;

namespace Model{
    struct ModelData
    {
        vector<Fbx*> pFbx_;
        vector<Transform> pTransform_;
        vector<string> pString_;
    };
}

//◆◆◆を管理するクラス
class Model : public GameObject
{
    int hModel_;
public:
    //コンストラクタ
    Model(GameObject* parent);

    //デストラクタ
    ~Model();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    int Load(string fileName);
};