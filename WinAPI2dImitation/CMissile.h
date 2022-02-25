#pragma once
#include "CGameObject.h"

class CTexture;

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

