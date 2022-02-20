#include "framework.h"
#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::CBullet(fPoint pos, fPoint size, fPoint speed)
{
	m_bIsActive = true;
	m_fptPos = pos;
	m_fptScale = size;
	m_fSpeed = speed;
}

CBullet::~CBullet()
{
}

void CBullet::update()
{
	m_fptPos.x += m_fSpeed.x *300* DT;
	m_fptPos.y += m_fSpeed.y *300* DT;

	if (m_fptPos.x < -200 || m_fptPos.x > WINSIZEX + 200 ||
		m_fptPos.y < -200 || m_fptPos.y > WINSIZEY + 200)
		m_bIsActive = false;
}

void CBullet::render(HDC hdc)
{
	Rectangle(hdc,
		m_fptPos.x - m_fptScale.x,
		m_fptPos.y - m_fptScale.y,
		m_fptPos.x + m_fptScale.x,
		m_fptPos.y + m_fptScale.y);
}
