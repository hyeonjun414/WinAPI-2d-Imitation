#pragma once
#include "CGameObject.h"

class CTexture;

class CMissile :
    public CGameObject
{
private:
    // Theta : cos, sin에 적용될 각도
    // PI / 2 = 90도, PI / 4 = 45도
    float   m_fTheta;           // 총알 이동 방향
    Vec2    m_vDir;             // 방향성 정보
    Vec2    m_vSpeed;           // 총알 속도
    Vec2    m_vVelocity;        // 총알 가속도
    Vec2    m_vMoveDist;        // 이동거리
    Vec2    m_vMaxDist;         // 최대 이동거리

public:
    CMissile();
    CMissile(OBJ_TYPE _objType, float _fTheta);
    CMissile(const CMissile& _origin); // 복사 생성자
    ~CMissile();
    CLONE(CMissile)

    virtual void    Init();
    virtual void    Update();
    virtual void    Render(HDC _hDC);
    
    void            SetDir(float _fTheta);
    float           GetDir()                { return m_fTheta; }

    virtual void	OnCollision(CCollider* _pOther) {}
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther) {};

};

