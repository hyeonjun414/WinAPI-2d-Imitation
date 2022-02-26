#include "framework.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CMonster.h"

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

void CInGameScene::Enter()
{
	CGameObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	obj->SetScale(Vec2(50, 50));
	AddObject(obj);

	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1100, WINSIZEY / 2));
	obj->Init();
	AddObject(obj);

	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MONSTER);
}

void CInGameScene::Exit()
{
	ClearObject();

	// 기존의 충돌 그릅을 해제시켜야한다.
	SINGLE(CCollisionManager)->Reset();
}
