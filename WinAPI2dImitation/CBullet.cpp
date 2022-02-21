#include "framework.h"
#include "CBullet.h"

CBullet::CBullet()
{
}

CBullet::CBullet(OBJ_GROUP objGroup, Vec2 pos, Vec2 size, Vec2 speed)
{
	m_enumObjGroup = objGroup;
	m_bIsActive = true;

	m_vec2Pos = pos;
	m_vec2Scale = size;
	m_vec2fSpeed = speed;
}

CBullet::~CBullet()
{
}

void CBullet::Update()
{
	m_vec2Pos.x += m_vec2fSpeed.x * 300 * DT;
	m_vec2Pos.y += m_vec2fSpeed.y * 300 * DT;

	if (m_vec2Pos.x < -200 || m_vec2Pos.x > WINSIZEX + 200 ||
		m_vec2Pos.y < -200 || m_vec2Pos.y > WINSIZEY + 200)
		m_bIsActive = false;
}

void CBullet::Render(HDC hdc)
{
	Rectangle(hdc,
		m_vec2Pos.x - m_vec2Scale.x,
		m_vec2Pos.y - m_vec2Scale.y,
		m_vec2Pos.x + m_vec2Scale.x,
		m_vec2Pos.y + m_vec2Scale.y);
}
