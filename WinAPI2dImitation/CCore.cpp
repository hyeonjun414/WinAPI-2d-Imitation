
#include "framework.h"
#include "CCore.h"
#include "CScene.h"
#include "CGameObject.h"

CCore::CCore()
{
	m_hBMP = 0;
	m_hMemDC = 0;
}
CCore::~CCore()
{
	// ���� DC ����
	ReleaseDC(hWnd, m_hDC);

	// ������۸��� DC�� ��Ʈ���� ����
	DeleteDC(m_hMemDC);
	DeleteObject(m_hBMP);
}

void CCore::Update()
{
	// ������ ������ ����
	
	// �Ŵ��� Ŭ���� ������Ʈ ( Ÿ��, Ű, ��� )
	CTimeManager::GetInst()->Update();
	CKeyManager::GetInst()->Update();
	CSceneManager::GetInst()->Update();



	// ������ ������ ���� �׷��ִ� �۾�
	// FPS ���
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::GetInst()->GetFPS());
	TextOutW(m_hDC, WINSIZEX - 60, 10, strFPS, 5);
}


void CCore::Render()
{
	// ȭ�� Clear
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// �Ŵ��� Ŭ���� ���� ( ��� )
	CSceneManager::GetInst()->Render(m_hMemDC);

	// m_hMemDC�� ��� �׸� ������ m_hDC�� �ѹ��� �ٽ� �׸�.
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CCore::Init()
{
	// Core�� �ʱ�ȭ ����

	// �Ŵ��� Ŭ���� �ʱ�ȭ ( Ÿ��, Ű, ��� )
	CTimeManager::GetInst()->Init();
	CKeyManager::GetInst()->Init();
	CSceneManager::GetInst()->Init();

	// �ھ��� ������ DC �Ҵ�
	m_hDC = GetDC(hWnd);
	
	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBMP = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	// ��Ʈ���� ���� DC�� �Ҵ�
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBMP);
	DeleteObject(hOldBit);

}
