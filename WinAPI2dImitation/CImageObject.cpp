#include "framework.h"
#include "CImageObject.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CGameObject.h"

CImageObject::CImageObject():
	m_bRenderStyle(false)
{
}

CImageObject::CImageObject(OBJ_TYPE _objGroup) :
	CGameObject(_objGroup),
	m_bRenderStyle(false)
{
}

CImageObject::CImageObject(OBJ_TYPE _objGroup, wstring _strTexName, wstring _strTexPath, bool _renderStyle):
	CGameObject(_objGroup)
{
	m_pTex = SINGLE(CResourceManager)->LoadTexture(_strTexName, _strTexPath);
	m_bRenderStyle = _renderStyle;
}

CImageObject::~CImageObject()
{
}

void CImageObject::Init()
{
}

void CImageObject::Update()
{
}

void CImageObject::Render(HDC _hDC)
{ 
	
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 pos = m_bRenderStyle ? m_vRenderPos : m_vPos;
	Vec2 vCameraPos = SINGLE(CCameraManager)->GetLookAt();

	Vec2 StartPos;
	StartPos.x = vCameraPos.x - WINSIZEX / 2 <= 0 ? 0 : vCameraPos.x - WINSIZEX / 2;
	StartPos.y = vCameraPos.y - WINSIZEY / 2 <= 0 ? 0 : vCameraPos.y - WINSIZEX / 2;
	if (m_bRenderStyle)
	{
		TransparentBlt(_hDC,
			(int)(pos.x - (float)(iWidth / 2)) + vCameraPos.x - WINSIZEX / 2,
			(int)(pos.y - (float)(iHeight / 2)) + vCameraPos.y - WINSIZEY / 2,
			WINSIZEX,
			WINSIZEY,
			m_pTex->GetDC(),
			StartPos.x,
			StartPos.y,
			WINSIZEX,
			WINSIZEY,
			RGB(255, 0, 255));
	}
	else
	{
		BitBlt(_hDC,
			(int)(pos.x - (iWidth / 2)),
			(int)(pos.y - (iHeight / 2) - m_vScale.y / 2),
			iWidth, iHeight,
			m_pTex->GetDC(),
			0, 0,
			SRCCOPY);
	}
	
}
