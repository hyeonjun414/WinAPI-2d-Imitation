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
    Vec2    m_vVelocity;        // �Ѿ� ���ӵ�
    Vec2    m_vMoveDist;        // �̵��Ÿ�
    Vec2    m_vMaxDist;         // �ִ� �̵��Ÿ�

public:
    CMissile();
    CMissile(OBJ_TYPE _objType, float _fTheta);
    CMissile(const CMissile& _origin); // ���� ������
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

