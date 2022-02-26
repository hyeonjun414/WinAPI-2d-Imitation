#include "framework.h"
#include "CCollider.h"
#include "CGameObject.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider():
	m_pOwner(nullptr),
	m_uiID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	// 충돌체가 Object의 위치를 따라가도록 만든다.
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
