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
	// 씬 매니저가 가지고 있는 모든 씬을 지워준다.
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
	// Scene 생성 -> 모든 장면은 사전에 생성한다.
	m_arrScene[(int)SCENE_TYPE::START] = new CStartScene(L"StartScene", SCENE_TYPE::START);
	m_arrScene[(int)SCENE_TYPE::STAGE_01] = new CInGameScene(L"STAGE 01", SCENE_TYPE::STAGE_01);
	m_arrScene[(int)SCENE_TYPE::TOOL] = new CToolScene(L"ToolScene", SCENE_TYPE::TOOL);

	m_pCurScene = m_arrScene[(int)SCENE_TYPE::START];
	m_pCurScene->Enter();

}

void CSceneManager::ChangeScene(SCENE_TYPE _sceneType)
{
	// 만약 기존 씬이랑 같은 씬으로 바꾸려고 한다면
	m_pCurScene->Exit();						// 기존 씬의 마무리
	m_pCurScene = m_arrScene[(int)_sceneType];	// 씬 전환
	m_pCurScene->Enter();						// 새로운 씬의 시작
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
