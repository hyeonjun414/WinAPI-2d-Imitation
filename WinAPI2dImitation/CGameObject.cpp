#include "framework.h"
#include "CGameObject.h"

CGameObject::CGameObject()
{
	m_bIsActive = true;
	m_enumObjType = OBJ_TYPE::DEFAULT;
}

CGameObject::CGameObject(OBJ_TYPE objGroup)
{
	m_bIsActive = true;
	m_enumObjType = objGroup;
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

OBJ_TYPE CGameObject::GetObjGroup()
{
	return m_enumObjType;
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
