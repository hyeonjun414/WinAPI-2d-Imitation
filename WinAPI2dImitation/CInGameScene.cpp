#include "framework.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CImageObject.h"
#include "CTexture.h"
#include "CCollObject.h"
#include "CCollider.h"

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
		vLookAt = SINGLE(CCameraManager)->GetRealPos(vLookAt);
		SINGLE(CCameraManager)->SetLookAt(vLookAt);
	}
}

void CInGameScene::Enter()
{
	CGameObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetName(L"Player");
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	obj->SetScale(Vec2(50, 50));
	obj->SetGravity(true);
	CREATEOBJECT(obj);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(3200.f, 1600.f));
	SINGLE(CCameraManager)->SetTarget(obj);
	
	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(900, WINSIZEY / 2));
	obj->Init();
	obj->SetGravity(true);
	CREATEOBJECT(obj);

	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1440, WINSIZEY / 2));
	obj->Init();
	obj->SetGravity(true);
	CREATEOBJECT(obj);

	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1440, 1200));
	obj->Init();
	obj->SetGravity(true);
	CREATEOBJECT(obj);

	obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1800, WINSIZEY / 2));
	obj->Init();
	obj->SetGravity(true);
	CREATEOBJECT(obj);

	CImageObject* BgObj = new CImageObject(OBJ_TYPE::IMAGE,
		L"InGameSceneBG",
		L"texture\\background.bmp", false);
	BgObj->SetPos(Vec2((float)(BgObj->GetTexture()->Width() / 2), (float)(BgObj->GetTexture()->Height() / 2)));
	CREATEOBJECT(BgObj);

	BgObj = new CImageObject(OBJ_TYPE::IMAGE,
		L"InGameSceneTile",
		L"texture\\map1.bmp", true);
	BgObj->SetPos(Vec2((float)(BgObj->GetTexture()->Width() / 2), (float)(BgObj->GetTexture()->Height() / 2)));
	CREATEOBJECT(BgObj);

	obj = new CCollObject(OBJ_TYPE::Floor);
	obj->SetName(L"Floor");
	obj->CreateCollider();
	obj->GetCollider()->SetOffsetPos(Vec2(560, 1030));
	obj->GetCollider()->SetScale(Vec2(1115, 10));
	CREATEOBJECT(obj);

	obj = new CCollObject(OBJ_TYPE::Floor);
	obj->SetName(L"Floor");
	obj->CreateCollider();
	obj->GetCollider()->SetOffsetPos(Vec2(2500, 1030));
	obj->GetCollider()->SetScale(Vec2(1460, 10));
	CREATEOBJECT(obj);

	obj = new CCollObject(OBJ_TYPE::Floor);
	obj->SetName(L"Floor");
	obj->CreateCollider();
	obj->GetCollider()->SetOffsetPos(Vec2(1440, 1220));
	obj->GetCollider()->SetScale(Vec2(660, 10));
	CREATEOBJECT(obj);

	obj = new CCollObject(OBJ_TYPE::Floor);
	obj->SetName(L"Floor");
	obj->CreateCollider();
	obj->GetCollider()->SetOffsetPos(Vec2(1440, 870));
	obj->GetCollider()->SetScale(Vec2(370, 10));
	CREATEOBJECT(obj);

	obj = new CCollObject(OBJ_TYPE::Floor);
	obj->SetName(L"Floor");
	obj->CreateCollider();
	obj->GetCollider()->SetOffsetPos(Vec2(1714, 1095));
	obj->GetCollider()->SetScale(Vec2(100, 10));
	CREATEOBJECT(obj);
	obj = new CCollObject(OBJ_TYPE::Floor);
	obj->SetName(L"Floor");
	obj->CreateCollider();
	obj->GetCollider()->SetOffsetPos(Vec2(1165, 1095));
	obj->GetCollider()->SetScale(Vec2(100, 10));
	CREATEOBJECT(obj);

	obj = new CCollObject(OBJ_TYPE::Wall);
	obj->SetName(L"Wall");
	obj->CreateCollider();
	obj->GetCollider()->SetOffsetPos(Vec2(1110, 1300));
	obj->GetCollider()->SetScale(Vec2(10, 540));
	CREATEOBJECT(obj);
	obj = new CCollObject(OBJ_TYPE::Wall);
	obj->SetName(L"Wall");
	obj->CreateCollider();
	obj->GetCollider()->SetOffsetPos(Vec2(1770, 1300));
	obj->GetCollider()->SetScale(Vec2(10, 540));
	CREATEOBJECT(obj);

	

	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::MISSILE, OBJ_TYPE::MONSTER);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MONSTER);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::Floor);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::MONSTER, OBJ_TYPE::Floor);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::Wall);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::MONSTER, OBJ_TYPE::Wall);
}

void CInGameScene::Exit()
{
	ClearObject();

	// 기존의 충돌 그릅을 해제시켜야한다.
	SINGLE(CCollisionManager)->Reset();
}
