#pragma once
#include "CGameObject.h"
class CBullet :
    public CGameObject
{

public:
    CBullet();
    CBullet(fPoint pos, fPoint size, fPoint speed);
    ~CBullet();

    void update();
    void render(HDC hdc);
};

