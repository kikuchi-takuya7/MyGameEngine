#pragma once
#include "Engine/GameObject.h"

class Fbx;

//���������Ǘ�����N���X
class Sub : public GameObject
{
public:
    //�R���X�g���N�^
    Sub(GameObject* parent);

    //�f�X�g���N�^
    ~Sub();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

private:
    
    Fbx* pFbx_;
};