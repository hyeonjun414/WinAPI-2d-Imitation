#include "framework.h"
#include "CMonster.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CMonster::CMonster():
    m_bIsRight(false),
    m_fDistance(0)
{
}

CMonster::CMonster(OBJ_TYPE _objType) :
    CGameObject(_objType)
{
    SetScale(Vec2(83, 83));
    m_vVelocity = Vec2(100.f, 0.f);
    m_fDistance = 150;
    m_bIsRight = true;
    m_strName = L"Monster";

    CreateCollider();
    m_pCollider->SetScale(GetScale());
    m_pCollider->SetOffsetPos(Vec2(0.f, -m_vec2Scale.y / 2));


    CTexture* m_pTex = SINGLE(CResourceManager)->LoadTexture(L"Monster", L"texture\\Animation_Monster.bmp");
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"Monster_Idle_Left", m_pTex, Vec2(0.f, 0.f), Vec2(98.f, 104.f),
        Vec2(110.f, 0.f), 0.5f, 3);
    GetAnimator()->CreateAnimation(L"Monster_Idle_Right", m_pTex, Vec2(0.f, 105.f), Vec2(98.f, 104.f),
        Vec2(110.f, 0.f), 0.5f, 3);
    GetAnimator()->CreateAnimation(L"Monster_Move_Left", m_pTex, Vec2(0.f, 210.f), Vec2(120.f, 109.f),
        Vec2(125.f, 0.f), 0.5f, 4);
    GetAnimator()->CreateAnimation(L"Monster_Move_Right", m_pTex, Vec2(0.f, 320.f), Vec2(120.f, 109.f),
        Vec2(125.f, 0.f), 0.5f, 4);

    if (m_bIsRight)
    {
        GetAnimator()->Play(L"Monster_Move_Right", true);
    }
    else
    {
        GetAnimator()->Play(L"Monster_Move_Left", true);
    }

    m_pAnimator->SetAllAnimOffset();

}

CMonster::~CMonster()
{
    delete m_pAnimator;
}


void CMonster::Init()
{
    SetCenterPos(m_vec2Pos);
}

void CMonster::Update()
{
    if (m_bIsGravity) m_vVelocity.y -= 1;
    m_vec2Pos.y += -m_vVelocity.y * DT;
    if (m_vec2Pos.y >= 910)
    {
        m_vec2Pos.y = 910;
        m_vVelocity.y = 0;
    }

    if (m_bIsRight)
    {
        m_vec2Pos.x += m_vVelocity.x * DT;
        if (m_vec2Pos.x > m_vec2CenterPos.x + m_fDistance)
        {
            GetAnimator()->Play(L"Monster_Move_Left", true);
            m_bIsRight = !m_bIsRight;
        }
    }
    else
    {
        m_vec2Pos.x -= m_vVelocity.x * DT;
        if (m_vec2Pos.x < m_vec2CenterPos.x - m_fDistance)
        {
            GetAnimator()->Play(L"Monster_Move_Right", true);
            m_bIsRight = !m_bIsRight;
        }

    }

    GetAnimator()->Update();
}
void CMonster::Render(HDC _hDC)
{
    ComponentRender(_hDC);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetName() == L"Missile_Player")
    {
        DELETEOBJECT(this);
    }
}




