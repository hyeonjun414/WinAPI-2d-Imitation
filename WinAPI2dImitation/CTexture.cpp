#include "framework.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_hDC = 0;
	m_hBMP = 0;
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBMP);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// ��Ʈ�� ���·� �������� ������� �⺻������ �����´�(�̹�����ŭ)
	m_hBMP = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP,
			  0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBMP); // ����� �ҷ����� ���� ��� ���� �߻�

	// ��Ʈ�ʰ� ������ DC
	m_hDC = CreateCompatibleDC(SINGLE(CCore)->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPervBit = (HBITMAP)SelectObject(m_hDC, m_hBMP);
	DeleteObject(hPervBit);

	// ���� ���� ����
	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);

}
