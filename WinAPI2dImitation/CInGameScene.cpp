#include "framework.h"
#include "CInGameScene.h"
#include "CPlayer.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::CInGameScene(wstring sceneName, SCENE_TYPE sceneType) :
	CScene(sceneName, sceneType)
{
}


CInGameScene::~CInGameScene()
{
}

void CInGameScene::Enter()
{
	CGameObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	obj->SetScale(Vec2(50, 50));

	AddObject(obj);
}

void CInGameScene::Exit()
{
}
