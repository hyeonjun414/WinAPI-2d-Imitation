#include "framework.h"
#include "CStartScene.h"
#include "CTextObject.h"
#include "CImageObject.h"
#include "CSound.h"

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

CSound* pSound;

void CStartScene::Update()
{
	// 스페이스바를 누르면 게임 시작
	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP)
	{
 		CHANGESCENE(SCENE_TYPE::STAGE_01);
	}
	if (KEYCHECK(KEY::ESC) == KEY_STATE::TAP)
	{
		CHANGESCENE(SCENE_TYPE::TOOL);
	}
	if (KEYCHECK(KEY::Z) == KEY_STATE::TAP)
	{
		
		SINGLE(CSoundManager)->AddSound(L"DingDing", L"sound\\dingding.wav", false);

	}
	if (KEYCHECK(KEY::X) == KEY_STATE::TAP)
	{
		//pSound->Play();
		SINGLE(CSoundManager)->Play(L"DingDing");
	}
}

void CStartScene::Enter()
{

	CGameObject* obj = new CTextObject(L"스페이스바를 누르면 게임이 시작됩니다.", OBJ_TYPE::TEXT);
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
