#pragma once
#include "CGameObject.h"
class CMissile :
    public CGameObject
{
private:
    // Theta : cos, sin�� ����� ����
    // PI / 2 = 90��, PI / 4 = 45��
    float   m_fTheta;       // �Ѿ� �̵� ����
    Vec2    m_vDir;          // ���⼺ ����
    float   m_fVelocity;    // �Ѿ� �ӵ�

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

