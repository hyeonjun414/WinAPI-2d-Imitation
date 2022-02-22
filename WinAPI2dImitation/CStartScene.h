#pragma once
#include "CScene.h"
class CStartScene :
    public CScene
{
public:
    CStartScene();
    CStartScene(wstring sceneName, SCENE_TYPE sceneType);
    ~CStartScene();

    virtual void Update();

    virtual void Enter();
    virtual void Exit();
};

