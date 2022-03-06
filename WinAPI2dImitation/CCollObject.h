#pragma once
#include "CGameObject.h"
class CCollObject :
    public CGameObject
{
public:
    CCollObject();
    CCollObject(OBJ_TYPE _objType);
    virtual ~CCollObject();
    CLONE(CCollObject)

    virtual void    Update();
    virtual void    Render(HDC _hDC);
    virtual void    Init();

};

