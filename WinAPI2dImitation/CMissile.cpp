#include "framework.h"
#include "CMissile.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CScene.h"
CMissile::CMissile()
{
}

CMissile::CMissile(OBJ_TYPE _objType, float _fTheta):
    CGameObject(_objType),
    m_pTex(nullptr)
{
    m_fTheta = _fTheta;
    m_vDir = Vec2(cosf(_fTheta), -sinf(_fTheta));
    m_vDir.Normalize();
    m_vec2Scale = Vec2(12.5f, 12.5f);
    m_vSpeed = Vec2(500, 500);
    m_vVelocity = Vec2(0, 0);

    // 텍스쳐 불러오기
    m_pTex = SINGLE(CResourceManager)->LoadTexture(L"BulletTex", L"texture\\Bullet.bmp");

    CreateCollider();
    m_pCollider->SetScale(Vec2(12.5, 12.5));
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

    if (m_vec2Pos.x < -100 || m_vec2Pos.y < -100 ||
        m_vec2Pos.x > WINSIZEX + 100 || m_vec2Pos.y > WINSIZEY + 100)
        m_bIsActive = !m_bIsActive;

    if (!m_bIsActive)
        SINGLE(CSceneManager)->GetCurScene()->EraseObject(this);
}

void CMissile::Render(HDC _hDC)
{
    if (nullptr != m_pTex)
    {
        int iWidth = (int)m_pTex->Width();
        int iHeight = (int)m_pTex->Height();

        TransparentBlt(_hDC,
            (int)(m_vec2Pos.x - (iWidth / 2)),
            (int)(m_vec2Pos.y - (iHeight / 2)),
            iWidth, iHeight,
            m_pTex->GetDC(),
            0, 0, iWidth, iHeight,
            RGB(255, 0, 255));
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

