#include "framework.h"
#include "CStartScene.h"
#include "CTextObject.h"

CStartScene::CStartScene()
{
	m_strName = L"";
	m_enumSceneType = SCENE_TYPE::NONE;
}

CStartScene::CStartScene(wstring sceneName, SCENE_TYPE sceneType):
	CScene(sceneName, sceneType)
{
}

CStartScene::~CStartScene()
{
}

void CStartScene::Update()
{
	// 스페이스바를 누르면 게임 시작
	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP)
	{
		CSceneManager::GetInst()->ChangeScene(SCENE_TYPE::STAGE_01);
	}
}

void CStartScene::Enter()
{
	CGameObject* obj = new CTextObject(L"스페이스바를 누르면 게임이 시작됩니다.", OBJ_TYPE::TEXT);
	obj->SetPos(Vec2(WINSIZEX / 2 - 150, WINSIZEY / 2 + 150));

	AddObject(obj);
}

void CStartScene::Exit()
{
	ClearObject();
}
