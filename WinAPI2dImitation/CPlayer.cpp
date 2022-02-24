#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(OBJ_TYPE objGroup) :
	CGameObject(objGroup),
	m_pTex(nullptr)
{
	m_pTex = new CTexture;

	wstring strFilePath = SINGLE(CPathManager)->GetContentPath();
	strFilePath += L"texture\\monster01.bmp";

	m_pTex->Load(strFilePath);
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

	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP)
		CreateMissile();
}

void CPlayer::Render(HDC hDC)
{
	if (nullptr != m_pTex)
	{
		int iWidth = (int)m_pTex->Width();
		int iHeight = (int)m_pTex->Height();

		//BitBlt(hDC,
		//	m_vec2Pos.x - (float)(iWidth / 2),
		//	m_vec2Pos.y - (float)(iHeight / 2),
		//	iWidth, iHeight,
		//	m_pTex->GetDC(),
		//	0, 0, SRCCOPY);

		TransparentBlt(hDC,
			m_vec2Pos.x - (float)(iWidth / 2),
			m_vec2Pos.y - (float)(iHeight / 2),
			iWidth, iHeight,
			m_pTex->GetDC(),
			0, 0, iWidth, iHeight,
			RGB(255, 0, 255));
	}
	else
	{
		// 움직이는 사각형 출력
		Rectangle(hDC,
			m_vec2Pos.x - m_vec2Scale.x/2,
			m_vec2Pos.y - m_vec2Scale.y/2,
			m_vec2Pos.x + m_vec2Scale.x/2,
			m_vec2Pos.y + m_vec2Scale.y/2);
	}

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
