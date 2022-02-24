#include "framework.h"
#include "CImageObject.h"
#include "CTexture.h"

CImageObject::CImageObject() :
	m_pTex(nullptr)
{
}

CImageObject::CImageObject(OBJ_TYPE objGroup) :
	CGameObject(objGroup),
	m_pTex(nullptr)
{
	m_pTex = new CTexture;

	wstring strFilePath = SINGLE(CPathManager)->GetContentPath();
	strFilePath += L"texture\\a.bmp";

	m_pTex->Load(strFilePath);
}

CImageObject::~CImageObject()
{
	if(nullptr != m_pTex)
		delete m_pTex;
}

void CImageObject::Init()
{
}

void CImageObject::Update()
{
}

void CImageObject::Render(HDC hDC)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	BitBlt(hDC,
		m_vec2Pos.x - (float)(iWidth / 2),
		m_vec2Pos.y - (float)(iHeight / 2),
		iWidth, iHeight,
		m_pTex->GetDC(),
		0, 0, SRCCOPY);
}
