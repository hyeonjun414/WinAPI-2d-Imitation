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

CGameObject g_Player(fPoint(WINSIZEX/2, WINSIZEY/2), fPoint(20,20));
vector<CBullet> g_vecBullet;
int stageNum = 5;

void CCore::update()
{
	// 게임의 정보를 갱신
	
	// 매니저 클래스 업데이트 ( 타임, 키 )
	CTimeManager::GetInst()->Update();
	CKeyManager::GetInst()->Update();

	scene.Update();

	// 해당 키가 눌렸는지 확인한다.
	// 비트별로 다양한 정보를 전달한다. 첫번째는 눌렸는지에 대한 정보
	// 1000 0000 0000 0000
	if (g_Player.GetActive() == false && (GetAsyncKeyState('R') & 0x8000))
	{
		g_Player.SetActive(true);
		g_Player.SetPos(fPoint(WINSIZEX / 2, WINSIZEY / 2));
		g_Player.SetScale(fPoint(20, 20));
		CTimeManager::getInst()->SetPlayTime(0);
		stageNum = 5;
		g_vecBullet.clear();
		return;
	}

	// 플레이어 루틴
	if (g_Player.GetActive())
	{
		g_Player.update();

		// 1초마다 돌아오면 플레이어를 겨냥하는 총알을 생성
		if (CTimeManager::getInst()->GetIsSec())
		{
			stageNum++;
			srand((unsigned int)time(NULL));

			for (int i = 0; i < stageNum / 5; i++)
			{
				float x, y;
				while (true)
				{

					// 범위는 x = -100 ~ 1380;
					//		  y = -100 ~ 820;
					x = rand() % (WINSIZEX + 200) - 100;
					y = rand() % (WINSIZEY + 200) - 100;

					//x가 영역에 있지만 y가 영역에 없을때나,
					//y가 영역에 있지만 x가 영역에 없을때 탈출
					if ((!(0 < x && x < WINSIZEX) && (0 < y && y < WINSIZEY)) ||
						((0 < x && x < WINSIZEX) && !(0 < y && y < WINSIZEY)))
						break;
				}
				float speedX = g_Player.GetPos().x - x;
				float speedY = g_Player.GetPos().y - y;
				float normalize = sqrt(pow(speedX, 2) + pow(speedY, 2));

				speedX /= normalize;
				speedY /= normalize;

				CBullet bullet(fPoint(x, y), fPoint(10, 10), fPoint(speedX, speedY));
				g_vecBullet.push_back(bullet);
			}


		}
		vector<CBullet>::iterator iter;
		for (iter = g_vecBullet.begin(); iter != g_vecBullet.end();)
		{
			if (iter->GetActive())
			{
				iter->update();
				
				// 플레이어의 영역과 총알의 영역이 겹치면
				fPoint bulletPos = iter->GetPos();
				fPoint bulletScale = iter->GetScale();
				if (bulletPos.x + bulletScale.x > g_Player.GetPos().x - g_Player.GetScale().x &&
					bulletPos.x - bulletScale.x < g_Player.GetPos().x + g_Player.GetScale().x &&
					bulletPos.y + bulletScale.x > g_Player.GetPos().y - g_Player.GetScale().y &&
					bulletPos.y - bulletScale.y < g_Player.GetPos().y + g_Player.GetScale().y)
				{
					g_Player.SetActive(false);
				}
				iter++;
			}
			else
			{
				iter = g_vecBullet.erase(iter);
			}
		}

		// 시간 출력
		WCHAR strSEC[7];
		swprintf_s(strSEC, L"%5d초", CTimeManager::getInst()->GetPlayTime());
		TextOutW(m_hDC, WINSIZEX / 2, 10, strSEC, 6);

		// 스테이지 출력
		WCHAR strStage[8];
		swprintf_s(strStage, L"STAGE %d", stageNum/5);
		TextOutW(m_hDC, WINSIZEX / 2, 30, strStage, 7);

	}
	else
	{
		TextOutW(m_hDC, WINSIZEX / 2, 100, L"GAME OVER!", 10);
		TextOutW(m_hDC, WINSIZEX / 2, 120, L"재시작 : R", 7);
	}
		

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

	g_Player.render(m_hMemDC);

	for (int i = 0; i < g_vecBullet.size(); i++)
		g_vecBullet[i].render(m_hMemDC);

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
	obj->SetScale(Vec2(50, 50));

	scene.AddObject(obj);
}
