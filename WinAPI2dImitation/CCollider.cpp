#include "framework.h"
#include "CCollider.h"
#include "CGameObject.h"

CCollider::CCollider():
	m_pOwner(nullptr)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	// �浹ü�� Object�� ��ġ�� ���󰡵��� �����.
	m_vFinalPos = m_pOwner->GetPos() + m_vOffsetPos;
}

void CCollider::Render(HDC _hDC)
{
	SelectGDI GDI(_hDC, PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW);

	Rectangle(_hDC,
		(int)(m_vFinalPos.x - m_vScale.x / 2),
		(int)(m_vFinalPos.y - m_vScale.y / 2),
		(int)(m_vFinalPos.x + m_vScale.x / 2),
		(int)(m_vFinalPos.y + m_vScale.y / 2));
}									   
