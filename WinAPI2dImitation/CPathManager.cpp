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
	// content폴더는 실행파일과 같은 폴더에 위치한다.
	// 하지만 디버그 릴리즈에 관계없이 bin 폴더를 가리켜야 한다.
	// 즉, 상위 폴더로 올라가 다시 bin 폴더로 들어간다.

	GetCurrentDirectory(255, m_strContentPath); // 현재 경로를 받아온다.

	
	int iLen = wcslen(m_strContentPath);

	// 상위폴더로 이동
	for (int i = iLen -1; 0 <= i; i--)
	{
		if ('\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = '\0';
			break;
		}
	}
	// 필요 경로 추가
	wcscat_s(m_strContentPath, 255, L"\\bin\\content\\");

	//SetWindowText(hWnd, m_strContentPath);
}
