#pragma once
#include "CScene.h"
class CInGameScene :
    public CScene
{
public:
    CInGameScene();
    CInGameScene(wstring sceneName, SCENE_TYPE sceneType);
    ~CInGameScene();

    virtual void Enter();
    virtual void Exit();
};

