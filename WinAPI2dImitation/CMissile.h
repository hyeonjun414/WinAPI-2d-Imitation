#pragma once
#include "CGameObject.h"
class CMissile :
    public CGameObject
{
private:
    // Theta : cos, sin�� ����� ����
    // PI / 2 = 90��, PI / 4 = 45��
    float   m_fTheta;           // �Ѿ� �̵� ����
    Vec2    m_vDir;             // ���⼺ ����
    Vec2    m_vSpeed;           // �Ѿ� �ӵ�
    Vec2    m_vVelocity;       // �Ѿ� ���ӵ�
    

public:
    CMissile();
    CMissile(OBJ_TYPE objType, float fTheta);
    ~CMissile();

    virtual void Init();
    virtual void Update();
    virtual void Render(HDC hDC);
    

    void    SetDir(float fTheta);
    float   GetDir();
};

