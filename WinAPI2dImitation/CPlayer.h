#pragma once
#include "CGameObject.h"
class CPlayer :
    public CGameObject
{
public :
    CPlayer();
    CPlayer(OBJ_TYPE objGroup);
    virtual ~CPlayer();

    virtual void Init();
    virtual void Update();
    virtual void Render(HDC hDC);

    void CreateMissile();
};

