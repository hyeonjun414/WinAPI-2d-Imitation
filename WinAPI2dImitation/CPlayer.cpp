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
	m_pTex(nullptr)
{
	// 텍스쳐 불러오기
	m_pTex = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\monster01.bmp");

	// Collider 만들기
	CreateCollider();

	m_pCollider->SetScale(Vec2(100, 100));
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
}

void CPlayer::Update()
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

	if (KEYCHECK(KEY::SPACE) == KEY_STATE::HOLD)
		CreateMissile();
}

void CPlayer::Render(HDC _hDC)
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
	CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();

	CMissile* pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(0));
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2+ pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(true);
	pCurScene->AddObject(pMissile);

	pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(45));
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2 + pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(true);
	pCurScene->AddObject(pMissile);

	pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(-45));
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2 + pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(true);
	pCurScene->AddObject(pMissile);

	pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(15));
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2 + pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(true);
	pCurScene->AddObject(pMissile);

	pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(60));
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2 + pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(true);
	pCurScene->AddObject(pMissile);

	pMissile = new CMissile(OBJ_TYPE::MISSILE, DEG(90));
	pMissile->SetPos(Vec2(m_vec2Pos.x + m_vec2Scale.x/2 + pMissile->GetScale().x, m_vec2Pos.y));
	pMissile->SetGravity(true);
	pCurScene->AddObject(pMissile);
}
