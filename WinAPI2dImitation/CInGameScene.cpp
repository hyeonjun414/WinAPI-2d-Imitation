#include "framework.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CGameManager.h"

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

	CGameManager::GetInst()->SetPlayer(m_vecObjectList[(int)OBJ_TYPE::PLAYER][0]);
	CGameObject* player = CGameManager::GetInst()->GetPlayer();

	if (player->GetActive() == false && KEYCHECK(KEY::R) == KEY_STATE::TAP)
	{
		player->SetActive(true);
		player->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
		player->SetScale(Vec2(20, 20));
		CTimeManager::GetInst()->SetPlayTime(0);
		m_iStageTime = 5;
		m_vecObjectList[(int)OBJ_TYPE::BULLET].clear();
		return;
	}

	if (player->GetActive())
	{

		// 1�ʸ��� ���ƿ��� �÷��̾ �ܳ��ϴ� �Ѿ��� ����
		if (CTimeManager::GetInst()->GetIsSec())
		{
			m_iStageTime++;
			srand((unsigned int)time(NULL));

			for (int i = 0; i < m_iStageTime / 5; i++)
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
				float dirX = player->GetPos().x - x;
				float dirY = player->GetPos().y - y;
				Vec2 dirVec = Vec2(dirX, dirY).Normalize();

				CGameObject* bullet = new CMissile(OBJ_TYPE::BULLET, Vec2(x, y), Vec2(10, 10), dirVec);
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

				// �÷��̾��� ������ �Ѿ��� ������ ��ġ��
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
		// �ð� ���
		WCHAR strSEC[7];
		swprintf_s(strSEC, L"%5d��", CTimeManager::GetInst()->GetPlayTime());
		TextOutW(hDC, WINSIZEX / 2, 10, strSEC, 6);

		// �������� ���
		WCHAR strStage[8];
		swprintf_s(strStage, L"STAGE %d", m_iStageTime / 5);
		TextOutW(hDC, WINSIZEX / 2, 30, strStage, 7);
	}
	else
	{
		TextOutW(hDC, WINSIZEX / 2, 100, L"GAME OVER!", 10);
		TextOutW(hDC, WINSIZEX / 2, 120, L"����� : R", 7);
	}
}

void CInGameScene::Enter()
{
	m_iStageTime = 5;

	CGameObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	obj->SetScale(Vec2(20, 20));
	

	AddObject(obj);

	// � ������Ʈ �׷쳢�� �浹�Ұ����� �̸� ����
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::MISSILE, OBJ_TYPE::MONSTER);
}

void CInGameScene::Exit()
{
	ClearObject();

	// ������ �浹 �׸��� �������Ѿ��Ѵ�.
	SINGLE(CCollisionManager)->Reset();
}
