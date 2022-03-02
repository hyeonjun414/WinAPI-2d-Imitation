#pragma once
#include "CGameObject.h"

class CTexture;

class CMonster :
    public CGameObject
{
    Vec2        m_vec2CenterPos;
    float       m_fVelocity;
    float       m_fDistance;
    bool        m_bIsUpDir;

public:
    CMonster();
    CMonster(OBJ_TYPE _objType);
    virtual ~CMonster();
    CLONE(CMonster)

    virtual void    Update();
    virtual void    Render(HDC _hDC);
    virtual void    Init();

    void            SetCenterPos(Vec2 _vec) { m_vec2CenterPos = _vec; }
    Vec2            GetCenterPos()          { return m_vec2CenterPos; }

    virtual void	OnCollision(CCollider* _pOther) {}
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther) {};
};

