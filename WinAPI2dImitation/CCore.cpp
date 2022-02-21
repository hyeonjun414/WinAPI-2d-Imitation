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
	// ���� DC ����
	ReleaseDC(hWnd, m_hDC);

	// ������۸��� DC�� ��Ʈ���� ����
	DeleteDC(m_hMemDC);
	DeleteObject(m_hBMP);
}

CGameObject g_Player(fPoint(WINSIZEX/2, WINSIZEY/2), fPoint(20,20));
vector<CBullet> g_vecBullet;
int stageNum = 5;

void CCore::update()
{
	// ������ ������ ����
	
	// �Ŵ��� Ŭ���� ������Ʈ ( Ÿ��, Ű )
	CTimeManager::GetInst()->Update();
	CKeyManager::GetInst()->Update();

	scene.Update();

	// �ش� Ű�� ���ȴ��� Ȯ���Ѵ�.
	// ��Ʈ���� �پ��� ������ �����Ѵ�. ù��°�� ���ȴ����� ���� ����
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

	// �÷��̾� ��ƾ
	if (g_Player.GetActive())
	{
		g_Player.update();

		// 1�ʸ��� ���ƿ��� �÷��̾ �ܳ��ϴ� �Ѿ��� ����
		if (CTimeManager::getInst()->GetIsSec())
		{
			stageNum++;
			srand((unsigned int)time(NULL));

			for (int i = 0; i < stageNum / 5; i++)
			{
				float x, y;
				while (true)
				{

					// ������ x = -100 ~ 1380;
					//		  y = -100 ~ 820;
					x = rand() % (WINSIZEX + 200) - 100;
					y = rand() % (WINSIZEY + 200) - 100;

					//x�� ������ ������ y�� ������ ��������,
					//y�� ������ ������ x�� ������ ������ Ż��
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
				
				// �÷��̾��� ������ �Ѿ��� ������ ��ġ��
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

		// �ð� ���
		WCHAR strSEC[7];
		swprintf_s(strSEC, L"%5d��", CTimeManager::getInst()->GetPlayTime());
		TextOutW(m_hDC, WINSIZEX / 2, 10, strSEC, 6);

		// �������� ���
		WCHAR strStage[8];
		swprintf_s(strStage, L"STAGE %d", stageNum/5);
		TextOutW(m_hDC, WINSIZEX / 2, 30, strStage, 7);

	}
	else
	{
		TextOutW(m_hDC, WINSIZEX / 2, 100, L"GAME OVER!", 10);
		TextOutW(m_hDC, WINSIZEX / 2, 120, L"����� : R", 7);
	}
		

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

	g_Player.render(m_hMemDC);

	for (int i = 0; i < g_vecBullet.size(); i++)
		g_vecBullet[i].render(m_hMemDC);

	// m_hMemDC�� ��� �׸� ������ m_hDC�� �ѹ��� �ٽ� �׸�.
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_hMemDC, 0, 0, SRCCOPY);
}

void CCore::Init()
{
	// Core�� �ʱ�ȭ ����

	// �Ŵ��� Ŭ���� �ʱ�ȭ ( Ÿ��, Ű )
	CTimeManager::GetInst()->Init();
	CKeyManager::GetInst()->Init();

	// �ھ��� ������ DC �Ҵ�
	m_hDC = GetDC(hWnd);
	
	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBMP = CreateCompatibleBitmap(m_hDC, WINSIZEX, WINSIZEY);
	m_hMemDC = CreateCompatibleDC(m_hDC);

	// ��Ʈ���� ���� DC�� �Ҵ�
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBMP);
	DeleteObject(hOldBit);

	CGameObject* obj = new CGameObject(OBJ_GROUP::PLAYER);
	obj->SetPos(Vec2(WINSIZEX/2, WINSIZEY/2));
	obj->SetScale(Vec2(50, 50));

	scene.AddObject(obj);
}
