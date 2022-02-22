#pragma once
#include "CScene.h"
class CInGameScene :
    public CScene
{
    int stageNum = 5;
public:
    CInGameScene();
    CInGameScene(wstring sceneName, SCENE_TYPE sceneType);
    ~CInGameScene();

    virtual void Update();
    virtual void Render(HDC hDC);

    virtual void Enter();
    virtual void Exit();
};


