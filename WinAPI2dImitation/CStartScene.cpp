#include "framework.h"
#include "CStartScene.h"
#include "CTextObject.h"
#include "CImageObject.h"

CStartScene::CStartScene()
{
	m_strName = L"";
	m_enumSceneType = SCENE_TYPE::NONE;
}

CStartScene::CStartScene(wstring _sceneName, SCENE_TYPE _sceneType):
	CScene(_sceneName, _sceneType)
{
}

CStartScene::~CStartScene()
{
}

void CStartScene::Update()
{
	// �����̽��ٸ� ������ ���� ����
	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP)
	{
 		CHANGESCENE(SCENE_TYPE::STAGE_01);
	}
}

void CStartScene::Enter()
{

	CGameObject* obj = new CTextObject(L"�����̽��ٸ� ������ ������ ���۵˴ϴ�.", OBJ_TYPE::TEXT);
	obj->SetPos(Vec2(WINSIZEX / 2 - 150, WINSIZEY / 2 + 150));
	CREATEOBJECT(obj);
	obj = new CImageObject(OBJ_TYPE::IMAGE);
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2 - 200));
	obj->Init();
	CREATEOBJECT(obj);

}

void CStartScene::Exit()
{
	ClearObject();
}
