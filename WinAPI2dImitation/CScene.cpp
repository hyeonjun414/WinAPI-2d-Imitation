#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"

CScene::CScene()
{
	m_strName = L"";
	m_enumSceneType = SCENE_TYPE::NONE;
}

CScene::CScene(wstring _sceneName, SCENE_TYPE _sceneType)
{
	m_strName = _sceneName;
	m_enumSceneType = _sceneType;
}

CScene::~CScene()
{
	// ����� ������� ��鿡 �����Ҵ����� �߰��� ������Ʈ�� �޸� ���������ش�.
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		vector<CGameObject*>::iterator iter = m_vecObjectList[i].begin();
		for (; iter != m_vecObjectList[i].end(); iter++)
		{
			delete* iter;
		}
	}
}

void CScene::Update()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		for (unsigned int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			if(m_vecObjectList[i][j]->GetActive())
				m_vecObjectList[i][j]->Update();
		}
	}
}

void CScene::FinalUpdate()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		for (unsigned int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			m_vecObjectList[i][j]->FinalUpdate();
		}
	}
}

void CScene::Render(HDC _hDC)
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		// �����κп��� Ȱ��ȭ ���θ� üũ�ؼ� ������ ũ�⸦ �����Ѵ�.
		// �޸������� �̺�Ʈ�Ŵ������� �����ϱ� ������ ������ �޸������� ������ �ʾƵ� �ȴ�.
		vector<CGameObject*>::iterator iter = m_vecObjectList[i].begin();
		for (; iter != m_vecObjectList[i].end();)
		{
			if ((*iter)->GetActive())
			{
				(*iter)->Render(_hDC);
				++iter;
			}
			else
			{
				iter = m_vecObjectList[i].erase(iter);
			}
		}
	}
}

void CScene::AddObject(CGameObject* _pObj)
{
	m_vecObjectList[(int)_pObj->GetObjGroup()].push_back(_pObj);
}

void CScene::EraseObject(CGameObject* _pObj)
{
	vector<CGameObject*>::iterator iter = m_vecObjectList[(int)_pObj->GetObjGroup()].begin();

	for (; iter != m_vecObjectList[(int)_pObj->GetObjGroup()].end();)
	{
		if (*iter == _pObj)
		{
			iter = m_vecObjectList[(int)_pObj->GetObjGroup()].erase(iter);
			delete _pObj;
			break;
		}
		else
		{
			iter++;
		}
	}

}

void CScene::ClearObject()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		Safe_Delete_Vec(m_vecObjectList[i]);
	}
}
