#include "framework.h"
#include "CGameObject.h"
#include "CCollider.h"

CGameObject::CGameObject()
{
	m_bIsActive = true;
	m_enumObjType = OBJ_TYPE::DEFAULT;
}

CGameObject::CGameObject(OBJ_TYPE _objGroup)
{
	m_bIsActive = true;
	m_enumObjType = _objGroup;
	m_pCollider = nullptr;
}

CGameObject::~CGameObject()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
}

void CGameObject::FinalUpdate()
{
	if (nullptr != m_pCollider)
		m_pCollider->FinalUpdate();
}

void CGameObject::ComponentRender(HDC _hDC)
{
	if (nullptr != m_pCollider)
		m_pCollider->Render(_hDC);
}



void CGameObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;


}
#pragma endregion
