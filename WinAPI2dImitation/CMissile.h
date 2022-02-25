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
    Vec2    m_vVelocity;       // 총알 가속도

    CTexture* m_pTex;
    

public:
    CMissile();
    CMissile(OBJ_TYPE _objType, float _fTheta);
    ~CMissile();

    virtual void    Init();
    virtual void    Update();
    virtual void    Render(HDC _hDC);
    

    void            SetDir(float _fTheta)   { m_fTheta = _fTheta; }
    float           GetDir()                { return m_fTheta; }
};

