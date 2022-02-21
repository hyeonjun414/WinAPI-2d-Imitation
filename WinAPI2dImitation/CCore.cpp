#include "framework.h"
#include "CCore.h"

CScene scene;

CCore::CCore()
{
	m_hBMP = 0;
	m_hMemDC = 0;
}
CCore::~CCore()
{
	// 메인 DC 해제
	ReleaseDC(hWnd, m_hDC);

	// 더블버퍼링용 DC와 비트맵을 해제
	DeleteDC(m_hMemDC);
	DeleteObject(m_hBMP);
}

void CCore::Update()
{
	// 게임의 정보를 갱신
	
	// 매니저 클래스 업데이트 ( 타임, 키 )
	CTimeManager::GetInst()->Update();
	CKeyManager::GetInst()->Update();

	scene.Update();

	// 게임의 정보를 토대로 그려주는 작업
	// FPS 출력
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::GetInst()->GetFPS());
	TextOutW(m_hDC, WINSIZEX - 60, 10, strFPS, 5);
}


void CCore::Render()
{
	// 화면 Clear
	Rectangle(m_hMemDC, -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	scene.Render(m_hMemDC);


	// m_hMemDC에 모아 그린 정보를 m_hDC로 한번에 다시 그림.
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CCore::Init()
{
	// Core의 초기화 과정

	// 매니저 클래스 초기화 ( 타임, 키 )
	CTimeManager::GetInst()->Init();
	CKeyManager::GetInst()->Init();

	// 코어의 변수에 DC 할당
	m_hDC = GetDC(hWnd);
	
	// 더블 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBMP = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	// 비트맵을 만든 DC에 할당
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBMP);
	DeleteObject(hOldBit);

	CGameObject* obj = new CGameObject(OBJ_GROUP::PLAYER);
	obj->SetPos(Vec2(WINSIZEX/2, WINSIZEY/2));
	obj->SetScale(Vec2(20, 20));

	scene.AddObject(obj);
}
