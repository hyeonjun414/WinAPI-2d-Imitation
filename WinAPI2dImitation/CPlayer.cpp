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
	// �ؽ��� �ҷ�����
	//m_pTex = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\monster01.bmp");
	SetScale(Vec2(70.f, 70.f));
	// Collider �����
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(0, -m_vec2Scale.y / 2));
	m_pCollider->SetScale(Vec2(50, 50));

	// �ִϸ����� �����
	CTexture* m_pTexture = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\Animation_Player.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Player_Idle_Left", m_pTexture, Vec2(0.f, 0.f), Vec2(70.f, 70.f),
									Vec2(70.f, 0.f), 0.2f, 2);
	GetAnimator()->CreateAnimation(L"Player_Idle_Right", m_pTexture, Vec2(0.f, 70.f), Vec2(70.f, 70.f),
									Vec2(70.f, 0.f), 0.2f, 2);
	GetAnimator()->CreateAnimation(L"Player_Move_Left", m_pTexture, Vec2(0.f, 140.f), Vec2(70.f, 70.f),
									Vec2(70.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"Player_Move_Right", m_pTexture, Vec2(0.f, 210.f), Vec2(70.f, 70.f),
									Vec2(70.f, 0.f), 0.2f, 3);

	GetAnimator()->Play(L"Player_Idle_Right", true);

	// �ִϸ������� ��� �ִϸ��̼��� �������� �����Ѵ�.
	m_pAnimator->SetAllAnimOffset();

	// Ư�� �����Ӹ� ���� ( �̵� �ִϸ��̼� ) 
	CAnimation* anim = GetAnimator()->FindAnimation(L"Player_Move_Left");
	anim->GetFrame(1).vOffset += Vec2(0.f, -10.f);

	anim = GetAnimator()->FindAnimation(L"Player_Move_Right");
	anim->GetFrame(1).vOffset += Vec2(0.f, -10.f);
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
	if (m_bIsGravity) m_vVelocity.y -= 1;
	m_vec2Pos.y += -m_vVelocity.y * DT;
	if (m_vec2Pos.y >= 910)
	{
		m_vec2Pos.y = 910;
		m_vVelocity.y = 0;
	}
	

	if (KEYCHECK(KEY::A) == KEY_STATE::HOLD)
	{
		// ����
		m_vec2Pos.x -= 300 * DT;
		GetAnimator()->Play(L"Player_Move_Left", true);
	}
	if (KEYCHECK(KEY::A) == KEY_STATE::AWAY)
	{
		GetAnimator()->Play(L"Player_Idle_Left", true);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::HOLD)
	{
		// ������
		m_vec2Pos.x += 300 * DT;
		GetAnimator()->Play(L"Player_Move_Right", true);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::AWAY)
	{
		GetAnimator()->Play(L"Player_Idle_Right", true);
	}
	if (KEYCHECK(KEY::W) == KEY_STATE::TAP)
	{
		// ����
		//m_vec2Pos.y -= 300 * DT;
		m_vVelocity.y += 300;
	}

	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP)
		CreateMissile();

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
