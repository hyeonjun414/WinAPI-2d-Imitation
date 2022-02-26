
#include "framework.h"
#include "CCore.h"
#include "CScene.h"
#include "CGameObject.h"

CCore::CCore():
	m_hDC(0),
	m_hBMP(0),
	m_hMemDC(0),
	m_arrBrush{},
	m_arrPen{}
{
}
CCore::~CCore()
{
	// ���� DC ����
	ReleaseDC(hWnd, m_hDC);

	// ������۸��� DC�� ��Ʈ���� ����
	DeleteDC(m_hMemDC);
	DeleteObject(m_hBMP);

	for (int i = 0; i < (UINT)PEN_TYPE::SIZE; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::Update()
{
	// ������ ������ ����
	
	// �Ŵ��� Ŭ���� ������Ʈ ( Ÿ��, Ű, ���, �浹 )
	SINGLE(CTimeManager)->Update();
	SINGLE(CKeyManager)->Update();
	SINGLE(CSceneManager)->Update();
	SINGLE(CCollisionManager)->Update();

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
	SINGLE(CSceneManager)->Render(m_hMemDC);

	// ������ ������ ���� �׷��ִ� �۾�
	// FPS ���
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::GetInst()->GetFPS());
	TextOutW(m_hMemDC, WINSIZEX - 60, 10, strFPS, 5);

	// m_hMemDC�� ��� �׸� ������ m_hDC�� �ѹ��� �ٽ� �׸�.
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CCore::Init()
{
	// Core�� �ʱ�ȭ ����

	// ���� ����� ��, �귯�� ����
	CreateBrushPen();

	// �Ŵ��� Ŭ���� �ʱ�ȭ ( Ÿ��, Ű, ���, ���, �浹 )
	SINGLE(CTimeManager)->Init();
	SINGLE(CKeyManager)->Init();
	SINGLE(CPathManager)->Init();
	SINGLE(CSceneManager)->Init();
	SINGLE(CCollisionManager)->Init();

	// �ھ��� ������ DC �Ҵ�
	m_hDC = GetDC(hWnd);
	
	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBMP = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	// ��Ʈ���� ���� DC�� �Ҵ�
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBMP);
	DeleteObject(hOldBit);

}
