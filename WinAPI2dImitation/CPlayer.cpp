#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(OBJ_TYPE _objGroup) :
	CGameObject(_objGroup),
	m_bIsAlive(true)
{
	// 텍스쳐 불러오기
	m_pTex = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\player.bmp");

	// Collider 만들기
	CreateCollider();

	//m_pCollider->SetOffsetPos(Vec2(0, 20));
	m_pCollider->SetScale(Vec2(50, 50));
}

CPlayer::CPlayer(const CPlayer& _origin):
	CGameObject(_origin),
	m_bIsAlive(true)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	if (m_bIsAlive)
	{
		if (KEYCHECK(KEY::LEFT) == KEY_STATE::HOLD)
		{
			// 왼쪽
			m_vec2Pos.x -= 300 * DT;
		}
		if (KEYCHECK(KEY::RIGHT) == KEY_STATE::HOLD)
		{
			// 오른쪽
			m_vec2Pos.x += 300 * DT;
		}
		if (KEYCHECK(KEY::UP) == KEY_STATE::HOLD)
		{
			// 위쪽
			m_vec2Pos.y -= 300 * DT;
		}
		if (KEYCHECK(KEY::DOWN) == KEY_STATE::HOLD)
		{
			// 아래쪽
			m_vec2Pos.y += 300 * DT;
		}
	}

	//if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP)
	//	CreateMissile();
}

void CPlayer::Render(HDC _hDC)
{
	if (nullptr != m_pTex)
	{
		TextureRender(_hDC);
	}
	else
	{
		// 움직이는 사각형 출력
		Rectangle(_hDC,
			(int)(m_vec2Pos.x - m_vec2Scale.x/2),
			(int)(m_vec2Pos.y - m_vec2Scale.y/2),
			(int)(m_vec2Pos.x + m_vec2Scale.x/2),
			(int)(m_vec2Pos.y + m_vec2Scale.y/2));
	}

	ComponentRender(_hDC);
}

void CPlayer::CreateMissile()
{

	CMissile* pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(10));
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2+ pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(true);
	CreateObject(pMissile);

	CMissile* pMissile1 = pMissile->Clone();
	pMissile1->SetDir(DEG(20));
	CreateObject(pMissile1);

	CMissile* pMissile2 = pMissile->Clone();
	pMissile2->SetDir(DEG(30));
	CreateObject(pMissile2);

	CMissile* pMissile3 = pMissile->Clone();
	pMissile3->SetDir(DEG(40));
	CreateObject(pMissile3);

	CMissile* pMissile4 = pMissile->Clone();
	pMissile4->SetDir(DEG(50));
	CreateObject(pMissile4);

	CMissile* pMissile5 = pMissile->Clone();
	pMissile5->SetDir(DEG(60));
	CreateObject(pMissile5);
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CGameObject* pObj = _pOther->GetObj();
	if (pObj->GetName() == L"Missile")
	{
		LOG(L"플레이어 미사일 충돌");
		PlayerDie(this);
	}
}

