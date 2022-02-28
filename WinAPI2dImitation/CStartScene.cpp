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
 		ChangeScene(SCENE_TYPE::STAGE_01);
	}
}

void CStartScene::Enter()
{

	CGameObject* obj = new CTextObject(L"�����̽��ٸ� ������ ������ ���۵˴ϴ�.", OBJ_TYPE::TEXT);
	obj->SetPos(Vec2(WINSIZEX / 2 - 150, WINSIZEY / 2 + 150));
	AddObject(obj);
	obj = new CImageObject(OBJ_TYPE::IMAGE);
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2 - 200));
	obj->Init();
	AddObject(obj);

}

void CStartScene::Exit()
{
	ClearObject();
}
