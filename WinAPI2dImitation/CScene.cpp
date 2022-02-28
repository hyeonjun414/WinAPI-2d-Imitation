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
	// 장면이 사라질때 장면에 동적할당으로 추가된 오브젝트를 메모리 해제시켜준다.
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
		// 렌더부분에서 활성화 여부를 체크해서 벡터의 크기를 조절한다.
		// 메모리해제는 이벤트매니저에서 진행하기 때문에 별도를 메모리해제는 해주지 않아도 된다.
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
