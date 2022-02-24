#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager():
	m_strContentPath{}
{
}

CPathManager::~CPathManager()
{
}

void CPathManager::Init()
{
	// content������ �������ϰ� ���� ������ ��ġ�Ѵ�.
	// ������ ����� ����� ������� bin ������ �����Ѿ� �Ѵ�.
	// ��, ���� ������ �ö� �ٽ� bin ������ ����.

	GetCurrentDirectory(255, m_strContentPath); // ���� ��θ� �޾ƿ´�.

	
	int iLen = wcslen(m_strContentPath);

	// ���������� �̵�
	for (int i = iLen -1; 0 <= i; i--)
	{
		if ('\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = '\0';
			break;
		}
	}
	// �ʿ� ��� �߰�
	wcscat_s(m_strContentPath, 255, L"\\bin\\content\\");

	//SetWindowText(hWnd, m_strContentPath);
}
