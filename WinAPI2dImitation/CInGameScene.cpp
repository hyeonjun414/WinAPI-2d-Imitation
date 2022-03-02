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

void CInGameScene::Update()
{
	CScene::Update();

	if (KEYCHECK(KEY::LBTN) == KEY_STATE::TAP)
	{
		Vec2 vLookAt = SINGLE(CKeyManager)->GetMousePos();
		vLookAt = SINGLE(CCamera)->GetRealPos(vLookAt);
		SINGLE(CCamera)->SetLookAt(vLookAt);
	}
}

void CInGameScene::Enter()
{
	CGameObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	obj->SetScale(Vec2(50, 50));
	AddObject(obj);

	//SINGLE(CCamera)->SetTarget(obj);


	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1100, WINSIZEY / 2));
	obj->Init();
	AddObject(obj);	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1100, WINSIZEY / 2));
	obj->Init();
	AddObject(obj);	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1100, WINSIZEY / 2));
	obj->Init();
	AddObject(obj);	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1100, WINSIZEY / 2));
	obj->Init();
	AddObject(obj);	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1100, WINSIZEY / 2));
	obj->Init();
	AddObject(obj);

	
	SINGLE(CCamera)->SetLookAt(Vec2(WINSIZEX / 2, WINSIZEY / 2));

	// � ������Ʈ �׷쳢�� �浹�Ұ����� �̸� ����
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::MISSILE, OBJ_TYPE::MONSTER);
}

void CInGameScene::Exit()
{
	ClearObject();

	// ������ �浹 �׸��� �������Ѿ��Ѵ�.
	SINGLE(CCollisionManager)->Reset();
}
