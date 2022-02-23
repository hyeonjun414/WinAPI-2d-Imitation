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

CMissile::CMissile(OBJ_TYPE objType, Vec2 pos, Vec2 size, Vec2 dirVec):
    CGameObject(objType)
{
    m_fTheta = 0;
    m_fVelocity = 300;

    m_vec2Pos = pos;
    m_vec2Scale = size;
    m_vDir = dirVec;
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
}

void CMissile::Update()
{
    if (CGameManager::GetInst()->GetPlayer()->GetActive())
    {
        m_vec2Pos.x += m_vDir.x * m_fVelocity * DT;
        m_vec2Pos.y += m_vDir.y * m_fVelocity * DT;

        if (m_vec2Pos.x < -200 || m_vec2Pos.x > WINSIZEX + 200 ||
            m_vec2Pos.y < -200 || m_vec2Pos.y > WINSIZEY + 200)
            m_bIsActive = false;
    }
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

void CMissile::SetDir(Vec2 vec)
{
}

float CMissile::GetDir()
{
    return m_fTheta;
}

