#include "framework.h"
#include "CMissile.h"

CMissile::CMissile()
{
}

CMissile::CMissile(OBJ_TYPE objType, float fTheta):
    CGameObject(objType)
{
    m_fTheta = fTheta;
    m_vDir = Vec2(cosf(fTheta), -sinf(fTheta));
    m_vDir.Normalize();
    m_vec2Scale = Vec2(10, 10);
    m_fVelocity = 500;
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
}

void CMissile::Update()
{

    m_vec2Pos.x += m_vDir.x * m_fVelocity * DT;
    m_vec2Pos.y += m_vDir.y * m_fVelocity * DT; // y��ǥ�� ������ ��ǥ��� �ݴ�� ����.

}

void CMissile::Render(HDC hDC)
{
    // �����̴� �簢�� ���
    Ellipse(hDC,
        m_vec2Pos.x - m_vec2Scale.x,
        m_vec2Pos.y - m_vec2Scale.y,
        m_vec2Pos.x + m_vec2Scale.x,
        m_vec2Pos.y + m_vec2Scale.y);
}

void CMissile::SetDir(float fTheta)
{
    m_fTheta = fTheta;
}

float CMissile::GetDir()
{
    return m_fTheta;
}

