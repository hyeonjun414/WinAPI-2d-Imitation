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
    m_vSpeed = Vec2(500, 500);
    m_vVelocity = Vec2(0, 0);
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
}

void CMissile::Update()
{
    if(m_bIsGravity) m_vVelocity.y -= 1;

    m_vec2Pos.x += m_vDir.x * m_vSpeed.x * DT;
    m_vec2Pos.y += m_vDir.y * m_vSpeed.y * DT - m_vVelocity.y * DT; 
    // y좌표는 윈도우 좌표계로 반대로 간다.
}

void CMissile::Render(HDC hDC)
{
    // 움직이는 사각형 출력
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

