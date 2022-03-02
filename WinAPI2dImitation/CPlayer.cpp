#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(OBJ_TYPE _objGroup) :
	CGameObject(_objGroup)
{
	// 텍스쳐 불러오기
	//m_pTex = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\monster01.bmp");

	// Collider 만들기
	CreateCollider();
	//m_pCollider->SetOffsetPos(Vec2(0, 20));
	m_pCollider->SetScale(Vec2(50, 50));

	// 애니메이터 만들기
	CTexture* m_pTexture = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\Animation_Player.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Player_Idle", m_pTexture, Vec2(0.f, 0.f), Vec2(70.f, 70.f), Vec2(70.f, 0.f), 0.2f, 2);

	GetAnimator()->Play(L"Player_Idle", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"Player_Idle");
	pAnim->GetFrame(0).vOffset = Vec2(0.f, -20.f);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	if (KEYCHECK(KEY::A) == KEY_STATE::HOLD)
	{
		// 왼쪽
		m_vec2Pos.x -= 300 * DT;
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::HOLD)
	{
		// 오른쪽
		m_vec2Pos.x += 300 * DT;
	}
	if (KEYCHECK(KEY::W) == KEY_STATE::HOLD)
	{
		// 위쪽
		m_vec2Pos.y -= 300 * DT;
	}
	if (KEYCHECK(KEY::S) == KEY_STATE::HOLD)
	{
		// 아래쪽
		m_vec2Pos.y += 300 * DT;
	}

	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP)
		CreateMissile();

	GetAnimator()->Update();
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
			(int)(m_vRenderPos.x - m_vec2Scale.x/2),
			(int)(m_vRenderPos.y - m_vec2Scale.y/2),
			(int)(m_vRenderPos.x + m_vec2Scale.x/2),
			(int)(m_vRenderPos.y + m_vec2Scale.y/2));
	}

	ComponentRender(_hDC);
}

void CPlayer::CreateMissile()
{

	CMissile* pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(0));
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2+ pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(false);
	CreateObject(pMissile);

	//CMissile* pMissile1 = pMissile->Clone();
	//pMissile1->SetDir(DEG(20));
	//CreateObject(pMissile1);

	//CMissile* pMissile2 = pMissile->Clone();
	//pMissile2->SetDir(DEG(30));
	//CreateObject(pMissile2);

	//CMissile* pMissile3 = pMissile->Clone();
	//pMissile3->SetDir(DEG(40));
	//CreateObject(pMissile3);

	//CMissile* pMissile4 = pMissile->Clone();
	//pMissile4->SetDir(DEG(50));
	//CreateObject(pMissile4);

	//CMissile* pMissile5 = pMissile->Clone();
	//pMissile5->SetDir(DEG(60));
	//CreateObject(pMissile5);
}
