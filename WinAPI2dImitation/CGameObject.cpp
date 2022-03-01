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

CGameObject::CGameObject(const CGameObject& _origin):
	m_strName(_origin.m_strName),
	m_enumObjType(_origin.m_enumObjType),
	m_bIsActive(true),
	m_bIsGravity(_origin.m_bIsGravity),
	m_vec2Pos(_origin.m_vec2Pos),
	m_vec2Scale(_origin.m_vec2Scale),
	m_pTex(_origin.m_pTex)
{
	m_pCollider = new CCollider(*_origin.m_pCollider);
	m_pCollider->m_pOwner = this;
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
	{
		if(SINGLE(CGameManager)->GetDebugMode())
			m_pCollider->Render(_hDC);
	}
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
