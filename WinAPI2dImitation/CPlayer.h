#pragma once
#include "CGameObject.h"

class CTexture;

class CPlayer :
    public CGameObject
{
public :
    CPlayer();
    CPlayer(OBJ_TYPE _objGroup);
    virtual ~CPlayer();
    CLONE(CPlayer)

    virtual void    Init();
    virtual void    Update();
    virtual void    Render(HDC _hDC);

    void            CreateMissile();

};

