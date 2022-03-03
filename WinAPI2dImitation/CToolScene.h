#pragma once
#include "CScene.h"
class CToolScene :
    public CScene
{
public:
    CToolScene();
    CToolScene(wstring _sceneName, SCENE_TYPE _sceneType);
    ~CToolScene();

    virtual void Enter();
    virtual void Exit();
};

