#include "framework.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	m_bIsActive = true;
}

CGameObject::CGameObject(OBJ_GROUP objGroup)
{
	m_bIsActive = true;
	m_enumObjGroup = objGroup;
}

CGameObject::~CGameObject()
{
}

#pragma region GET & SET

void CGameObject::SetActive(bool active)
{
	m_bIsActive = active;
}

void CGameObject::SetPos(Vec2 pos)
{
	m_vec2Pos = pos;
}

void CGameObject::SetScale(Vec2 scale)
{
	m_vec2Scale = scale;
}

OBJ_GROUP CGameObject::GetObjGroup()
{
	return m_enumObjGroup;
}

bool CGameObject::GetActive()
{
	return m_bIsActive;
}

Vec2 CGameObject::GetPos()
{
	return m_vec2Pos;
}

Vec2 CGameObject::GetScale()
{
	return m_vec2Scale;
}
#pragma endregion

void CGameObject::Update()
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

void CGameObject::Render(HDC hdc)
{
	// 움직이는 사각형 출력
	Rectangle(hdc,
		m_vec2Pos.x - m_vec2Scale.x,
		m_vec2Pos.y - m_vec2Scale.y,
		m_vec2Pos.x + m_vec2Scale.x,
		m_vec2Pos.y + m_vec2Scale.y);
}
