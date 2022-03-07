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
	m_bIsFloor = false;
	m_bIsJumping = false;
	m_bIsRight = true;


	// 텍스쳐 불러오기
	//m_pTex = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\monster01.bmp");
	SetScale(Vec2(90, 90));
	// Collider 만들기
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(0, -5));
	m_pCollider->SetScale(Vec2(GetScale().x/2, 10));

	// 애니메이터 만들기
	CTexture* m_pTexture = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\skul_Animation.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Player_Idle_Right", m_pTexture, Vec2(1.f, 1.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.15f, 8);
	GetAnimator()->CreateAnimation(L"Player_Idle_Left", m_pTexture, Vec2(1.f, 92.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.15f, 8);
	GetAnimator()->CreateAnimation(L"Player_Move_Right", m_pTexture, Vec2(1.f, 183.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"Player_Move_Left", m_pTexture, Vec2(1.f, 274.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"Player_Jump_Right", m_pTexture, Vec2(1.f, 365.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.1f, 2);
	GetAnimator()->CreateAnimation(L"Player_Jump_Left", m_pTexture, Vec2(183.f, 365.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.1f, 2);
	GetAnimator()->CreateAnimation(L"Player_Fall_Right", m_pTexture, Vec2(1.f, 456.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"Player_Fall_Left", m_pTexture, Vec2(183.f, 456.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"Player_Fall2_Right", m_pTexture, Vec2(1.f, 547.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"Player_Fall2_Left", m_pTexture, Vec2(274.f, 547.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.2f, 3);

	GetAnimator()->Play(L"Player_Idle_Right", true);

	// 애니메이터의 모든 애니메이션의 오프셋을 조절한다.
	m_pAnimator->SetAllAnimOffset();

}

CPlayer::~CPlayer()
{
	delete m_pAnimator;
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	if (m_bIsGravity && !m_bIsFloor) m_vVelocity.y -= 700 * DT;
	m_vec2Pos.y += -m_vVelocity.y * DT;
	
	if (m_vVelocity.y > 0)
	{
		m_bIsJumping = true;
		if (m_bIsRight)
			GetAnimator()->Play(L"Player_Jump_Right", true);
		else
			GetAnimator()->Play(L"Player_Jump_Left", true);
	}
	else
	{
		if (m_vVelocity.y < -1)
		{
			if (m_bIsRight)
				GetAnimator()->Play(L"Player_Fall_Right", true);
			else
				GetAnimator()->Play(L"Player_Fall_Left", true);
		}
		if(m_vVelocity.y < -200)
		{
			if (m_bIsRight)
				GetAnimator()->Play(L"Player_Fall2_Right", true);
			else
				GetAnimator()->Play(L"Player_Fall2_Left", true);
		}
		m_bIsJumping = false;
	}
	if (KEYCHECK(KEY::A) == KEY_STATE::HOLD)
	{
		// 왼쪽
		m_vec2Pos.x -= 300 * DT;
		m_bIsRight = false;
		if (m_bIsFloor && !m_bIsJumping)
			GetAnimator()->Play(L"Player_Move_Left", true);
	}
	if (KEYCHECK(KEY::A) == KEY_STATE::AWAY)
	{
		m_bIsRight = false;
		if (m_bIsFloor && !m_bIsJumping)
			GetAnimator()->Play(L"Player_Idle_Left", true);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::HOLD)
	{
		// 오른쪽
		m_vec2Pos.x += 300 * DT;
		m_bIsRight = true;
		if(m_bIsFloor && !m_bIsJumping)
			GetAnimator()->Play(L"Player_Move_Right", true);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::AWAY)
	{
		m_bIsRight = true;
		if (m_bIsFloor && !m_bIsJumping)
			GetAnimator()->Play(L"Player_Idle_Right", true);
	}

	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP && m_bIsFloor)
	{
		m_vVelocity.y += 500;

	}

	GetAnimator()->Update();
}

void CPlayer::Render(HDC _hDC)
{
	ComponentRender(_hDC);
}

void CPlayer::CreateMissile()
{
	CMissile* pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(0));
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2+ pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(false);
	pMissile->SetScale(m_vec2Scale);
	pMissile->GetCollider()->SetOffsetPos(Vec2(0, -m_vec2Scale.y / 2));
	CREATEOBJECT(pMissile);
}

void CPlayer::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Wall" ) 
	{
		if (m_vec2Pos.x < _pOther->GetFinalPos().x)
			m_vec2Pos.x = _pOther->GetFinalPos().x - _pOther->GetScale().x / 2 - m_pCollider->GetScale().x / 2;
		else
			m_vec2Pos.x = _pOther->GetFinalPos().x + _pOther->GetScale().x/2 + m_pCollider->GetScale().x / 2;
	}
}
 
void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Floor" && !m_bIsJumping)
	{
		m_vVelocity.y = 0;
		{
			m_vec2Pos.y = _pOther->GetFinalPos().y - _pOther->GetScale().y / 2 + 1;
			m_bIsFloor = true;
			if (m_bIsRight)
				GetAnimator()->Play(L"Player_Idle_Right", true);
			else
				GetAnimator()->Play(L"Player_Idle_Left", true);
		}
	}
	if (_pOther->GetObj()->GetName() == L"Monster")
	{
		m_vVelocity.y = 300;
	}

}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetName() == L"Floor")
	{
		m_bIsFloor = false;
	}
}
