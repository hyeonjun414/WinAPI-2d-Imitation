#pragma once
#include "CGameObject.h"

class CTexture;

class CPlayer :
    public CGameObject
{
private:
    Vec2    m_vVelocity;
    bool    m_bIsFloor;
    bool    m_bIsJumping;
    bool    m_bIsRight;
    int     m_iCollCount;
public :
    CPlayer();
    CPlayer(OBJ_TYPE _objGroup);
    virtual ~CPlayer();
    CLONE(CPlayer)

    virtual void    Init();
    virtual void    Update();
    virtual void    Render(HDC _hDC);


    virtual void	OnCollision(CCollider* _pOther) ;
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther);
};

