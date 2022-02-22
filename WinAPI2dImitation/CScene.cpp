#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"

CScene::CScene()
{
	m_strName = L"";
	m_enumSceneType = SCENE_TYPE::NONE;
}

CScene::CScene(wstring sceneName, SCENE_TYPE sceneType)
{
	m_strName = sceneName;
	m_enumSceneType = sceneType;
}

CScene::~CScene()
{
	// ����� ������� ��鿡 �����Ҵ����� �߰��� ������Ʈ�� �޸� ���������ش�.
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			delete m_vecObjectList[i][j];
			m_vecObjectList[i][j] = nullptr;
		}
	}
}

vector<CBullet> g_vecBullet;
int stageNum = 5;

void CScene::Update()
{
	// �÷��̾� Ž��
	CGameObject* player = m_vecObjectList[(int)OBJ_GROUP::PLAYER][0];

	if (player->GetActive() == false && (GetAsyncKeyState('R') & 0x8000))
	{
		player->SetActive(true);
		player->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
		player->SetScale(Vec2(20, 20));
		CTimeManager::GetInst()->SetPlayTime(0);
		stageNum = 5;
		g_vecBullet.clear();
		return;
	}

	if (player->GetActive())
	{

		// 1�ʸ��� ���ƿ��� �÷��̾ �ܳ��ϴ� �Ѿ��� ����
		if (CTimeManager::GetInst()->GetIsSec())
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
				float speedX = player->GetPos().x - x;
				float speedY = player->GetPos().y - y;
				float normalize = sqrt(pow(speedX, 2) + pow(speedY, 2));

				speedX /= normalize;
				speedY /= normalize;

				CBullet bullet(OBJ_GROUP::BULLET, Vec2(x, y), Vec2(10, 10), Vec2(speedX, speedY));
				g_vecBullet.push_back(bullet);
			}


		}
		vector<CBullet>::iterator iter;
		for (iter = g_vecBullet.begin(); iter != g_vecBullet.end();)
		{
			if (iter->GetActive())
			{
				iter->Update();

				// �÷��̾��� ������ �Ѿ��� ������ ��ġ��
				Vec2 bulletPos = iter->GetPos();
				Vec2 bulletScale = iter->GetScale();
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
				iter = g_vecBullet.erase(iter);
			}
		}
	}

	for (int i = 0; i < (int)OBJ_GROUP::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			m_vecObjectList[i][j]->Update();
		}
	}
}

void CScene::Render(HDC hDC)
{
	// �÷��̾� Ž��
	CGameObject* player = m_vecObjectList[(int)OBJ_GROUP::PLAYER][0];

	for (int i = 0; i < (int)OBJ_GROUP::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			m_vecObjectList[i][j]->Render(hDC);
		}
	}

	if (player->GetActive())
	{
		// �ð� ���
		WCHAR strSEC[7];
		swprintf_s(strSEC, L"%5d��", CTimeManager::GetInst()->GetPlayTime());
		TextOutW(hdc, WINSIZEX / 2, 10, strSEC, 6);

		// �������� ���
		WCHAR strStage[8];
		swprintf_s(strStage, L"STAGE %d", stageNum / 5);
		TextOutW(hdc, WINSIZEX / 2, 30, strStage, 7);
	}
	else
	{
		TextOutW(hdc, WINSIZEX / 2, 100, L"GAME OVER!", 10);
		TextOutW(hdc, WINSIZEX / 2, 120, L"����� : R", 7);
	}
	for (int i = 0; i < g_vecBullet.size(); i++)
		g_vecBullet[i].Render(hdc);
}

void CScene::SetName(const wstring& strName)
{
	m_strName = strName;
}

wstring CScene::GetName()
{
	return m_strName;
}

void CScene::AddObject(CGameObject* pObj)
{
	m_vecObjectList[(int)pObj->GetObjGroup()].push_back(pObj);
}

void CScene::ClearObject()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			delete m_vecObjectList[i][j];
			m_vecObjectList[i][j] = nullptr;
		}
	}
}
