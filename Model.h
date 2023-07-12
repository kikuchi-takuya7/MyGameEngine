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

//���������Ǘ�����N���X
class Model : public GameObject
{
    int hModel_;
public:
    //�R���X�g���N�^
    Model(GameObject* parent);

    //�f�X�g���N�^
    ~Model();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    int Load(string fileName);
};