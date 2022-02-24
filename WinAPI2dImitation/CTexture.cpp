#include "framework.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_hDC = 0;
	m_hBit = 0;
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// 비트맵 형태로 가져오며 사이즈는 기본값으로 가져온다(이미지만큼)
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP,
			  0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBit); // 제대로 불러오지 못한 경우 오류 발생

	// 비트맵과 연결할 DC
	m_hDC = CreateCompatibleDC(SINGLE(CCore)->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPervBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPervBit);

	// 가로 세로 길이
	GetObject(m_hBit, sizeof(BITMAP), &m_bmpInfo);

}
