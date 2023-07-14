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
        Fbx* pFbx_;
        Transform transform_;
        string fileName_;
    };

    int Load(std::string _fileName);

    void SetTransform(int _hModel, Transform _t);

    void Draw(int _hModel);

    void Release();

    void AllRelease();
}
