#pragma once
#include "CGameObject.h"
class CBullet :
    public CGameObject
{

public:
    CBullet();
    CBullet(OBJ_TYPE objType, Vec2 pos, Vec2 size, Vec2 speed);
    ~CBullet();

    void Update() override;
    void Render(HDC hdc) override;
};

