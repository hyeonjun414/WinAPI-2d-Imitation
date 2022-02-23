#pragma once
#include "CGameObject.h"
class CMissile :
    public CGameObject
{
private:
    // Theta : cos, sin에 적용될 각도
    // PI / 2 = 90도, PI / 4 = 45도
    float   m_fTheta;       // 총알 이동 방향
    Vec2    m_vDir;          // 방향성 정보
    float   m_fVelocity;    // 총알 속도

public:
    CMissile();
    CMissile(OBJ_TYPE objType, float fTheta);
    CMissile(OBJ_TYPE objType, Vec2 pos, Vec2 size, Vec2 speed);
    virtual ~CMissile();

    virtual void Init();
    virtual void Update();
    virtual void Render(HDC hDC);
    

    void    SetDir(float fTheta);
    void    SetDir(Vec2 vec);
    float   GetDir();
};

