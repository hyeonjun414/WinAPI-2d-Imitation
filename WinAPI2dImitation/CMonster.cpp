#include "framework.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(OBJ_TYPE objType) :
    CGameObject(objType)
{
    SetScale(Vec2(100, 100));
    m_fVelocity = 100;
    m_fDistance = 100;
    m_bIsUpDir = true;
}

CMonster::~CMonster()
{
}

void CMonster::Update()
{
    if (m_bIsUpDir)
    {
        m_vec2Pos.y -= m_fVelocity * DT;
         if (m_vec2Pos.y < m_vec2CenterPos.y - m_fDistance) m_bIsUpDir = !m_bIsUpDir;
    }
    else
    {
        m_vec2Pos.y += m_fVelocity * DT;
        if (m_vec2Pos.y > m_vec2CenterPos.y + m_fDistance) m_bIsUpDir = !m_bIsUpDir;
    }
}
void CMonster::Render(HDC hDC)
{
    Rectangle(hDC,
        m_vec2Pos.x - m_vec2Scale.x,
        m_vec2Pos.y - m_vec2Scale.y,
        m_vec2Pos.x + m_vec2Scale.x,
        m_vec2Pos.y + m_vec2Scale.y);
}

void CMonster::SetCenterPos(Vec2 vec)
{
    m_vec2CenterPos = vec;
}

void CMonster::Init()
{
    SetCenterPos(m_vec2Pos);
}

Vec2 CMonster::GetCenterPos()
{
    return m_vec2CenterPos;
}


