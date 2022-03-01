#include "framework.h"
#include "CMissile.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CScene.h"

CMissile::CMissile()
{
}

CMissile::CMissile(OBJ_TYPE _objType, float _fTheta):
    CGameObject(_objType)
{
    m_fTheta = _fTheta;
    SetDir(_fTheta);
    m_vec2Scale = Vec2(12.5f, 12.5f);
    m_vSpeed = Vec2(500, 500);
    m_vVelocity = Vec2(0, 0);

    // 텍스쳐 불러오기
    m_pTex = SINGLE(CResourceManager)->LoadTexture(L"BulletTex", L"texture\\Bullet.bmp");

    CreateCollider();
    m_pCollider->SetScale(Vec2(12.5, 12.5));
}

CMissile::CMissile(OBJ_TYPE _objType, Vec2 _vDir):
    CGameObject(_objType)
{
    m_vDir = _vDir;
    m_vec2Scale = Vec2(12.5f, 12.5f);
    m_vSpeed = Vec2(500, 500);
    m_vVelocity = Vec2(0, 0);

    // 텍스쳐 불러오기
    m_pTex = SINGLE(CResourceManager)->LoadTexture(L"BulletTex2", L"texture\\bullet2.bmp");

    CreateCollider();
    m_pCollider->SetScale(Vec2(12.5, 12.5));
}

CMissile::CMissile(const CMissile& _origin) :
    CGameObject(_origin),
    m_fTheta(_origin.m_fTheta),
    m_vDir(_origin.m_vDir),
    m_vSpeed(_origin.m_vSpeed),
    m_vVelocity(_origin.m_vVelocity)

{
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

    if (SINGLE(CGameManager)->GetPlayer()->GetAlive())
    {
        m_vec2Pos.x += m_vDir.x * m_vSpeed.x * DT;
        m_vec2Pos.y += m_vDir.y * m_vSpeed.y * DT - m_vVelocity.y * DT;
        // y좌표는 윈도우 좌표계로 반대로 간다.

        if (m_vec2Pos.x < -500 || m_vec2Pos.y < -500 ||
            m_vec2Pos.x > WINSIZEX + 500 || m_vec2Pos.y > WINSIZEY + 500)
            DeleteObject(this);
    }


}

void CMissile::Render(HDC _hDC)
{
    if (nullptr != m_pTex)
    {
        TextureRender(_hDC);
    }
    else
    {
        Ellipse(_hDC,
            (int)(m_vec2Pos.x - m_vec2Scale.x),
            (int)(m_vec2Pos.y - m_vec2Scale.y),
            (int)(m_vec2Pos.x + m_vec2Scale.x),
            (int)(m_vec2Pos.y + m_vec2Scale.y));
    }

    ComponentRender(_hDC);
}

void CMissile::SetDir(float _fTheta)
{
    m_fTheta = _fTheta;
    m_vDir = Vec2(cosf(_fTheta), -sinf(_fTheta));
    m_vDir.Normalize();
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
    CGameObject* pOtherObj = _pOther->GetObj();
    if (pOtherObj->GetName() == L"Monster")
    {
        LOG(L"미사일 충돌");
        DeleteObject(this);
    }
}

