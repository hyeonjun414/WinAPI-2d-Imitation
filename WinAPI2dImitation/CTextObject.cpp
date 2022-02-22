#include "framework.h"
#include "CTextObject.h"

CTextObject::CTextObject()
{
}

CTextObject::CTextObject(wstring strText, OBJ_TYPE objGroup) :
	CGameObject(objGroup)
{
	m_strText = strText;
}

CTextObject::~CTextObject()
{
}

void CTextObject::Update()
{
}

void CTextObject::Render(HDC hDC)
{
	const int size = m_strText.size();
	WCHAR str[50];
	swprintf_s(str, L"%s", m_strText.c_str());
	TextOutW(hDC, m_vec2Pos.x, m_vec2Pos.y, str, m_strText.size());
}
