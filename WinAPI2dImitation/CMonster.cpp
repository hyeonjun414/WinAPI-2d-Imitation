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
    SetScale(Vec2(70, 60));
    m_vVelocity = Vec2(100.f, 0.f);
    m_fDistance = 150;
    m_bIsRight = true;
    m_bIsFloor = false;
    m_bIsErase = false;
    m_strName = L"Monster";

    CreateCollider();
    m_pCollider->SetScale(Vec2(50.f,50.f));
    m_pCollider->SetOffsetPos(Vec2(0.f, -25.f));


    CTexture* m_pTex = SINGLE(CResourceManager)->LoadTexture(L"Monster", L"texture\\monster_animation.bmp");
    CreateAnimator();
    GetAnimator()->CreateAnimation(L"Monster_Idle_Left", m_pTex, Vec2(0.f, 0.f), Vec2(70.f, 70.f),
        Vec2(70, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"Monster_Idle_Right", m_pTex, Vec2(0.f, 70.f), Vec2(70.f, 70.f),
        Vec2(70, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"Monster_Move_Left", m_pTex, Vec2(0.f,140.f), Vec2(70.f, 70.f),
        Vec2(70, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"Monster_Move_Right", m_pTex, Vec2(0.f, 210.f), Vec2(70.f, 70.f),
        Vec2(70, 0.f), 0.5f, 2);
    GetAnimator()->CreateAnimation(L"Monster_Hit_Left", m_pTex, Vec2(140.f, 0.f), Vec2(70.f, 70.f),
        Vec2(70, 0.f), 2.f, 1);
    GetAnimator()->CreateAnimation(L"Monster_Hit_Right", m_pTex, Vec2(140.f, 70.f), Vec2(70.f, 70.f),
        Vec2(70, 0.f), 2.f, 1);

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

CMonster::CMonster(const CMonster& _origin) :
    CGameObject(_origin)
{
    SetScale(Vec2(70, 60));
    m_vVelocity = Vec2(100.f, 0.f);
    m_fDistance = 150;
    m_bIsRight = true;
    m_bIsFloor = false;
    m_bIsErase = false;
    m_strName = L"Monster";
}

CMonster::~CMonster()
{
    delete m_pAnimator;
}



void CMonster::Init()
{
    SetCenterPos(m_vPos);
}

void CMonster::Update()
{
    if (m_bIsGravity && !m_bIsFloor) m_vVelocity.y -= 500 * DT;
    m_vPos.y += -m_vVelocity.y * DT;

    if (m_bIsRight)
    {
        m_vPos.x += m_vVelocity.x * DT;
        if (m_vPos.x > m_vec2CenterPos.x + m_fDistance)
        {
            GetAnimator()->Play(L"Monster_Move_Left", true);
            m_bIsRight = !m_bIsRight;
        }
    }
    else
    {
        m_vPos.x -= m_vVelocity.x * DT;
        if (m_vPos.x < m_vec2CenterPos.x - m_fDistance)
        {
            GetAnimator()->Play(L"Monster_Move_Right", true);
            m_bIsRight = !m_bIsRight;
        }

    }

    GetAnimator()->Update();

    if (m_bIsErase)
        DelayEraseObject(SINGLE(CTimeManager)->GetPlayTime());
}
void CMonster::Render(HDC _hDC)
{
    ComponentRender(_hDC);
}
void CMonster::OnCollision(CCollider* _pOther)
{
    if (_pOther->GetObj()->GetName() == L"Wall")
    {
        if (m_vPos.x < _pOther->GetFinalPos().x)
            m_vPos.x = _pOther->GetFinalPos().x - _pOther->GetScale().x / 2 - m_pCollider->GetScale().x / 2;
        else
            m_vPos.x = _pOther->GetFinalPos().x + _pOther->GetScale().x / 2 + m_pCollider->GetScale().x / 2;
    }
}
void CMonster::OnCollisionEnter(CCollider* _pOther)
{
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetName() == L"Player" &&
       _pOther->GetFinalPos().y < m_pCollider->GetFinalPos().y)
    {
        m_bIsErase = true;
        m_vVelocity = 0;
        if (m_bIsRight)
            GetAnimator()->Play(L"Monster_Hit_Right", false);
        else
            GetAnimator()->Play(L"Monster_Hit_Left", false);
        m_iTime = SINGLE(CTimeManager)->GetPlayTime();
    }
    if (pOtherObj->GetName() == L"Floor")
    {
        m_vVelocity.y = 0;
        m_vPos.y = _pOther->GetOffsetPos().y - _pOther->GetScale().y / 2 +1;
        m_bIsFloor = true;
    }
}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
    if (_pOther->GetObj()->GetName() == L"Floor")
    {
        m_bIsFloor = false;
    }
}

void CMonster::DelayEraseObject(int _iDalayTime)
{
    if (m_iTime + 2 <= _iDalayTime)
    {
        DELETEOBJECT(this);
    }
}





