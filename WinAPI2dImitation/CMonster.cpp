#include "framework.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(OBJ_TYPE _objType) :
    CGameObject(_objType)
{
    SetScale(Vec2(100, 100));
    m_fVelocity = 100;
    m_fDistance = 100;
    m_bIsUpDir = true;

    CreateCollider();
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
    SetCenterPos(m_vec2Pos);
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
void CMonster::Render(HDC _hDC)
{
    Rectangle(_hDC,
        (int)(m_vec2Pos.x - m_vec2Scale.x),
        (int)(m_vec2Pos.y - m_vec2Scale.y),
        (int)(m_vec2Pos.x + m_vec2Scale.x),
        (int)(m_vec2Pos.y + m_vec2Scale.y));
}



