#include "framework.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	m_bIsActive = true;
}

CGameObject::CGameObject(fPoint pos, fPoint scale)
{
	m_bIsActive = true;
	m_fptPos = pos;
	m_fptScale = scale;
}

CGameObject::~CGameObject()
{
}

void CGameObject::SetActive(bool active)
{
	m_bIsActive = active;
}

void CGameObject::SetPos(fPoint pos)
{
	m_fptPos = pos;
}

void CGameObject::SetScale(fPoint scale)
{
	m_fptScale = scale;
}

bool CGameObject::GetActive()
{
	return m_bIsActive;
}

fPoint CGameObject::GetPos()
{
	return m_fptPos;
}

fPoint CGameObject::GetScale()
{
	return m_fptScale;
}

void CGameObject::update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		// 왼쪽
		m_fptPos.x -= 300 * DT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		// 오른쪽
		m_fptPos.x += 300 * DT;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		// 위쪽
		m_fptPos.y -= 300 * DT;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		// 아래쪽
		m_fptPos.y += 300 * DT;
	}
}

void CGameObject::render(HDC hdc)
{
	// 움직이는 사각형 출력
	Rectangle(hdc,
		m_fptPos.x - m_fptScale.x,
		m_fptPos.y - m_fptScale.y,
		m_fptPos.x + m_fptScale.x,
		m_fptPos.y + m_fptScale.y);
}
