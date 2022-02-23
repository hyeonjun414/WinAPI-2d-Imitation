#pragma once
#include "CGameObject.h"
class CMonster :
    public CGameObject
{
    Vec2    m_vec2CenterPos;
    float   m_fVelocity;
    float   m_fDistance;
    bool    m_bIsUpDir;

public:
    CMonster();
    CMonster(OBJ_TYPE objType);
    virtual ~CMonster();

    virtual void Update();
    virtual void Render(HDC hDC);
    virtual void Init();

    void SetCenterPos(Vec2 vec);
    Vec2 GetCenterPos();
};

