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
	// 장면이 사라질때 장면에 동적할당으로 추가된 오브젝트를 메모리 해제시켜준다.
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			delete m_vecObjectList[i][j];
			m_vecObjectList[i][j] = nullptr;
		}
	}
}

void CScene::Update()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			m_vecObjectList[i][j]->Update();
		}
	}
}

void CScene::Render(HDC hDC)
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			m_vecObjectList[i][j]->Render(hDC);
		}
	}
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
