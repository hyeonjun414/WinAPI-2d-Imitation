#include "framework.h"
#include "CMonster.h"
#include "CTexture.h"
#include "CCollider.h"

CMonster::CMonster()
{
}

CMonster::CMonster(OBJ_TYPE _objType) :
    CGameObject(_objType)
{
    SetScale(Vec2(83, 83));
    m_fVelocity = 100;
    m_fDistance = 100;
    m_bIsUpDir = true;
    m_strName = L"Monster";
    m_pTex = SINGLE(CResourceManager)->LoadTexture(L"Monster2", L"\\texture\\monster02.bmp");

    CreateCollider();
    m_pCollider->SetScale(GetScale());
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
    if (nullptr != m_pTex)
    {
        TextureRender(_hDC);
    }
    else
    {
        Rectangle(_hDC,
            (int)(m_vRenderPos.x - m_vec2Scale.x / 2),
            (int)(m_vRenderPos.y - m_vec2Scale.y / 2),
            (int)(m_vRenderPos.x + m_vec2Scale.x / 2),
            (int)(m_vRenderPos.y + m_vec2Scale.y / 2));
    }


    ComponentRender(_hDC);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetName() == L"Missile_Player")
    {
        LOG(L"몬스터가 미사일에 충돌");
        DeleteObject(this);
    }
}




