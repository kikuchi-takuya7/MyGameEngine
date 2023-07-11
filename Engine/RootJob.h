#pragma once
#include "GameObject.h"

class RootJob :
    public GameObject
{
public:
    RootJob();
    RootJob(GameObject* parent, const string& name);
    ~RootJob();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

