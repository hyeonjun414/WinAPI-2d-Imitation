#include "framework.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(OBJ_TYPE objGroup) :
	CGameObject(objGroup)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	if (KEYCHECK(KEY::LEFT) == KEY_STATE::HOLD)
	{
		// ����
		m_vec2Pos.x -= 300 * DT;
	}
	if (KEYCHECK(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		// ������
		m_vec2Pos.x += 300 * DT;
	}
	if (KEYCHECK(KEY::UP) == KEY_STATE::HOLD)
	{
		// ����
		m_vec2Pos.y -= 300 * DT;
	}
	if (KEYCHECK(KEY::DOWN) == KEY_STATE::HOLD)
	{
		// �Ʒ���
		m_vec2Pos.y += 300 * DT;
	}
}

void CPlayer::Render(HDC hDC)
{
	// �����̴� �簢�� ���
	Rectangle(hDC,
		m_vec2Pos.x - m_vec2Scale.x,
		m_vec2Pos.y - m_vec2Scale.y,
		m_vec2Pos.x + m_vec2Scale.x,
		m_vec2Pos.y + m_vec2Scale.y);
}
