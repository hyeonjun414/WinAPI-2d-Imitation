#include "framework.h"
#include "CScene.h"

CScene::CScene()
{
	m_strName = L"";
}

CScene::~CScene()
{
	// 장면이 사라질때 장면에 동적할당으로 추가된 오브젝트를 메모리 해제시켜준다.
	for (int i = 0; i < (int)OBJ_GROUP::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			delete m_vecObjectList[i][j];
		}
	}
}

void CScene::Update()
{
	for (int i = 0; i < (int)OBJ_GROUP::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			m_vecObjectList[i][j]->Update();
		}
	}
}

void CScene::Render(HDC hdc)
{
	for (int i = 0; i < (int)OBJ_GROUP::SIZE; i++)
	{
		for (int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			m_vecObjectList[i][j]->Render(hdc);
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
