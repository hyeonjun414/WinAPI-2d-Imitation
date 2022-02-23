#include "framework.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CGameManager.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::CInGameScene(wstring sceneName, SCENE_TYPE sceneType) :
	CScene(sceneName, sceneType)
{
}
CInGameScene::~CInGameScene()
{
}

void CInGameScene::Update()
{
	CScene::Update();

	CGameManager::GetInst()->SetPlayer(m_vecObjectList[(int)OBJ_TYPE::PLAYER][0]);
	CGameObject* player = CGameManager::GetInst()->GetPlayer();

	if (player->GetActive() == false && KEYCHECK(KEY::R) == KEY_STATE::TAP)
	{
		player->SetActive(true);
		player->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
		player->SetScale(Vec2(20, 20));
		CTimeManager::GetInst()->SetPlayTime(0);
		stageNum = 5;
		m_vecObjectList[(int)OBJ_TYPE::BULLET].clear();
		return;
	}

	if (player->GetActive())
	{

		// 1초마다 돌아오면 플레이어를 겨냥하는 총알을 생성
		if (CTimeManager::GetInst()->GetIsSec())
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
				float speedX = player->GetPos().x - x;
				float speedY = player->GetPos().y - y;
				float normalize = sqrt(pow(speedX, 2) + pow(speedY, 2));

				speedX /= normalize;
				speedY /= normalize;

				CGameObject* bullet = new CBullet(OBJ_TYPE::BULLET, Vec2(x, y), Vec2(10, 10), Vec2(speedX, speedY));
				m_vecObjectList[(int)OBJ_TYPE::BULLET].push_back(bullet);
			}
		}
		vector<CGameObject*>::iterator iter;
		for (iter = m_vecObjectList[(int)OBJ_TYPE::BULLET].begin(); iter != m_vecObjectList[(int)OBJ_TYPE::BULLET].end();)
		{
			(*iter)->GetActive();
			if ((*iter)->GetActive())
			{
				(*iter)->Update();

				// 플레이어의 영역과 총알의 영역이 겹치면
				Vec2 bulletPos = (*iter)->GetPos();
				Vec2 bulletScale = (*iter)->GetScale();
				if (bulletPos.x + bulletScale.x > player->GetPos().x - player->GetScale().x &&
					bulletPos.x - bulletScale.x < player->GetPos().x + player->GetScale().x &&
					bulletPos.y + bulletScale.x > player->GetPos().y - player->GetScale().y &&
					bulletPos.y - bulletScale.y < player->GetPos().y + player->GetScale().y)
				{
					player->SetActive(false);
				}
				iter++;
			}
			else
			{
				iter = m_vecObjectList[(int)OBJ_TYPE::BULLET].erase(iter);
			}
		}
	}
}

void CInGameScene::Render(HDC hDC)
{
	CScene::Render(hDC);

	CGameObject* player = m_vecObjectList[(int)OBJ_TYPE::PLAYER][0];
	if (player->GetActive())
	{
		// 시간 출력
		WCHAR strSEC[7];
		swprintf_s(strSEC, L"%5d초", CTimeManager::GetInst()->GetPlayTime());
		TextOutW(hDC, WINSIZEX / 2, 10, strSEC, 6);

		// 스테이지 출력
		WCHAR strStage[8];
		swprintf_s(strStage, L"STAGE %d", stageNum / 5);
		TextOutW(hDC, WINSIZEX / 2, 30, strStage, 7);
	}
	else
	{
		TextOutW(hDC, WINSIZEX / 2, 100, L"GAME OVER!", 10);
		TextOutW(hDC, WINSIZEX / 2, 120, L"재시작 : R", 7);
	}
}

void CInGameScene::Enter()
{
	CGameObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	obj->SetScale(Vec2(20, 20));

	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1100, WINSIZEY / 2));
	obj->Init();
	AddObject(obj);
}

void CInGameScene::Exit()
{
	ClearObject();
}
