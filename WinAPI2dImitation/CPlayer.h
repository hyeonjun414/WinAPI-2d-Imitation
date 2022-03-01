#pragma once
#include "CGameObject.h"

class CPlayer :
    public CGameObject
{
private:
    bool            m_bIsAlive; // 플레이어가 살아있는지

public :
    CPlayer();
    CPlayer(OBJ_TYPE _objGroup);
    CPlayer(const CPlayer& _origin);
    virtual ~CPlayer();
    CLONE(CPlayer)

    //CPlayer* Clone() { return new CPlayer(*this); }
    virtual void    Init();
    virtual void    Update();
    virtual void    Render(HDC _hDC);

    void            SetAlive(bool _alive)   { m_bIsAlive = _alive; }
    bool            GetAlive()              { return m_bIsAlive; }

    void            CreateMissile();

    virtual void	OnCollision(CCollider* _pOther) {};
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther) {};
};

