#include "framework.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CTexture.h"

CGameObject::CGameObject()
{
	m_bIsActive = true;
	m_enumObjType = OBJ_TYPE::DEFAULT;
}

CGameObject::CGameObject(OBJ_TYPE _objGroup):
	m_pTex(nullptr),
	m_pCollider(nullptr)
{
	m_bIsActive = true;
	m_enumObjType = _objGroup;
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



void CGameObject::TextureRender(HDC _hDC)
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

void CGameObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}
