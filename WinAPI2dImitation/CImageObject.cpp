#include "framework.h"
#include "CImageObject.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CGameObject.h"

CImageObject::CImageObject()
{
}

CImageObject::CImageObject(OBJ_TYPE _objGroup) :
	CGameObject(_objGroup)
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

	Vec2 pos = m_bRenderStyle ? m_vRenderPos : m_vec2Pos;

	TransparentBlt(_hDC,
		(int)(pos.x - (iWidth / 2)),
		(int)(pos.y - (iHeight / 2) - m_vec2Scale.y / 2),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, SRCCOPY);

	//Vec2 vCameraPos = SINGLE(CCameraManager)->GetLookAt();

	//TransparentBlt(_hDC,
	//	(int)(m_vRenderPos.x - (float)(iWidth / 2)) + vCameraPos.x - WINSIZEX / 2,
	//	(int)(m_vRenderPos.y - (float)(iHeight / 2)) + vCameraPos.y - WINSIZEY / 2,
	//	WINSIZEX,
	//	WINSIZEY,
	//	m_pTex->GetDC(),
	//	vCameraPos.x - WINSIZEX / 2,
	//	vCameraPos.y - WINSIZEY / 2,
	//	WINSIZEX,
	//	WINSIZEY,
	//	RGB(255, 0, 255));

}
