#pragma once
#include "CGameObject.h"
class CPlayer :
    public CGameObject
{
public :
    CPlayer();
    CPlayer(OBJ_TYPE objGroup);
    ~CPlayer();

    virtual void Update();
    virtual void Render(HDC hDC);
};

