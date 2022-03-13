#include "framework.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CImageObject.h"
#include "CTexture.h"

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
	//CGameObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	//obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	//obj->SetScale(Vec2(50, 50));
	//obj->SetGravity(true);
	//CREATEOBJECT(obj);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(1920.f, 1080.f));
	//SINGLE(CCameraManager)->SetTarget(obj);

	CGameObject* obj = new CMonster(OBJ_TYPE::MONSTER);
	obj->SetPos(Vec2(1100, WINSIZEY / 2));
	obj->Init();
	obj->SetGravity(true);
	CREATEOBJECT(obj);

	CImageObject* BgObj = new CImageObject(OBJ_TYPE::IMAGE,
		L"InGameSceneBG",
		L"texture\\scene02_bg.bmp");
	BgObj->GetTexture()->Width();
	BgObj->SetPos(Vec2((float)(BgObj->GetTexture()->Width() / 2), (float)(BgObj->GetTexture()->Height() / 2)));
	CREATEOBJECT(BgObj);


	//SINGLE(CCameraManager)->SetLookAt(Vec2(WINSIZEX / 2, WINSIZEY / 2 + 300));
	//SINGLE(CCameraManager)->SetLookAt(Vec2(0, 0));
	

	// � ������Ʈ �׷쳢�� �浹�Ұ����� �̸� ����
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::MISSILE, OBJ_TYPE::MONSTER);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MONSTER);
}

void CInGameScene::Exit()
{
	ClearObject();

	// ������ �浹 �׸��� �������Ѿ��Ѵ�.
	SINGLE(CCollisionManager)->Reset();
}
