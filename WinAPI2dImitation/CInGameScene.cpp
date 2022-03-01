#include "framework.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CGameManager.h"
#include "CImageObject.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::CInGameScene(wstring _sceneName, SCENE_TYPE _sceneType) :
	CScene(_sceneName, _sceneType)
{
}
CInGameScene::~CInGameScene()
{
}

void CInGameScene::Update()
{
	CScene::Update();

	CGameManager::GetInst()->SetPlayer((CPlayer*)m_vecObjectList[(int)OBJ_TYPE::PLAYER][0]);
	CPlayer* player = CGameManager::GetInst()->GetPlayer();

	if (player->GetAlive() == false && KEYCHECK(KEY::R) == KEY_STATE::TAP)
	{
		GameReset();
		return;
	}

	if (player->GetAlive())
	{

		// 1초마다 돌아오면 플레이어를 겨냥하는 총알을 생성
		if (CTimeManager::GetInst()->GetIsSec())
		{
			m_iStageTime++;
			srand((unsigned int)time(NULL));

			for (int i = 0; i < m_iStageTime / 5; i++)
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
				float dirX = player->GetPos().x - x;
				float dirY = player->GetPos().y - y;
				Vec2 dirVec = Vec2(dirX, dirY).Normalize();

				CMissile* bullet = new CMissile(OBJ_TYPE::MISSILE, dirVec);
				bullet->SetPos(Vec2(x, y));
				bullet->SetGravity(false);
				bullet->SetName(L"Missile");
				CreateObject(bullet);
			}
		}
	}
}

void CInGameScene::Render(HDC hDC)
{
	CScene::Render(hDC);

	CPlayer* player = (CPlayer*)m_vecObjectList[(int)OBJ_TYPE::PLAYER][0];
	if (player->GetAlive())
	{
		// 시간 출력
		WCHAR strSEC[7];
		swprintf_s(strSEC, L"%5d초", CTimeManager::GetInst()->GetPlayTime());
		TextOutW(hDC, WINSIZEX / 2, 10, strSEC, 6);

		// 스테이지 출력
		WCHAR strStage[9];
		swprintf_s(strStage, L"STAGE %2d", m_iStageTime / 5);
		TextOutW(hDC, WINSIZEX / 2, 30, strStage, 8);
	}
	else
	{
		TextOutW(hDC, WINSIZEX / 2, 100, L"GAME OVER!", 10);
		TextOutW(hDC, WINSIZEX / 2, 120, L"재시작 : R", 7);
	}
}

void CInGameScene::Enter()
{
	m_iStageTime = 5;

	CPlayer* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	obj->SetScale(Vec2(20, 20));
	SINGLE(CGameManager)->SetPlayer(obj);
	AddObject(obj);


	CGameObject* ImageObj = new CImageObject(OBJ_TYPE::IMAGE, L"texture\\scene01_bg.bmp");
	ImageObj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	AddObject(ImageObj);

	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::MISSILE, OBJ_TYPE::PLAYER);
}

void CInGameScene::Exit()
{
	ClearObject();

	// 기존의 충돌 그릅을 해제시켜야한다.
	SINGLE(CCollisionManager)->Reset();
}
