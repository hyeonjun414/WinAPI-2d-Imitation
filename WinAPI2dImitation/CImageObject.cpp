#include "framework.h"
#include "CImageObject.h"
#include "CTexture.h"

CImageObject::CImageObject()
{
}

CImageObject::CImageObject(OBJ_TYPE _objGroup) :
	CGameObject(_objGroup)
{
	m_pTex = SINGLE(CResourceManager)->LoadTexture(L"TitleImage", L"texture\\a.bmp");

}

CImageObject::CImageObject(OBJ_TYPE _objGroup, wstring _strTexName, wstring _strTexPath):
	CGameObject(_objGroup)
{
	m_pTex = SINGLE(CResourceManager)->LoadTexture(_strTexName, _strTexPath);
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

	BitBlt(_hDC,
		(int)(m_vRenderPos.x - (float)(iWidth / 2)),
		(int)(m_vRenderPos.y - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, SRCCOPY);
}
