#include "framework.h"
#include "CCollObject.h"

CCollObject::CCollObject()
{
}

CCollObject::CCollObject(OBJ_TYPE _objType):
	CGameObject(_objType)
{
}

CCollObject::~CCollObject()
{
}

void CCollObject::Update()
{
}

void CCollObject::Render(HDC _hDC)
{
	ComponentRender(_hDC);
}

void CCollObject::Init()
{
}
