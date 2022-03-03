#include "framework.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CStartScene.h"
#include "CInGameScene.h"
#include "CToolScene.h"

CSceneManager::CSceneManager()
{
	for (int i = 0; i < (int)SCENE_TYPE::SIZE; i++)
		m_arrScene[i] = nullptr;

	m_pCurScene = nullptr;
}
CSceneManager::~CSceneManager()
{
	// �� �Ŵ����� ������ �ִ� ��� ���� �����ش�.
	for (int i = 0; i < (int)SCENE_TYPE::SIZE; i++)
	{
		if(nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneManager::Update()
{
	m_pCurScene->Update();

	m_pCurScene->FinalUpdate();
}

void CSceneManager::Render(HDC hdc)
{
	m_pCurScene->Render(hdc);
}


void CSceneManager::Init()
{
	// Scene ���� -> ��� ����� ������ �����Ѵ�.
	m_arrScene[(int)SCENE_TYPE::START] = new CStartScene(L"StartScene", SCENE_TYPE::START);
	m_arrScene[(int)SCENE_TYPE::STAGE_01] = new CInGameScene(L"STAGE 01", SCENE_TYPE::STAGE_01);
	m_arrScene[(int)SCENE_TYPE::TOOL] = new CToolScene(L"ToolScene", SCENE_TYPE::TOOL);

	m_pCurScene = m_arrScene[(int)SCENE_TYPE::START];
	m_pCurScene->Enter();

}

void CSceneManager::ChangeScene(SCENE_TYPE _sceneType)
{
	// ���� ���� ���̶� ���� ������ �ٲٷ��� �Ѵٸ�
	m_pCurScene->Exit();						// ���� ���� ������
	m_pCurScene = m_arrScene[(int)_sceneType];	// �� ��ȯ
	m_pCurScene->Enter();						// ���ο� ���� ����
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
