#include "framework.h"
#include "function.h"
#include "CGameObject.h"
// 전역함수
void CreateObject(CGameObject* _pObj)
{
	tEvent even = {};
	even.eEvent = EVENT_TYPE::CREATE_OBJECT;
	even.lParam = (DWORD_PTR)_pObj;

	SINGLE(CEventManager)->AddEvent(even);
}

void DeleteObject(CGameObject* _pObj)
{
	tEvent even = {};
	even.eEvent = EVENT_TYPE::DELETE_OBJECT;
	even.lParam = (DWORD_PTR)_pObj;

	SINGLE(CEventManager)->AddEvent(even);
}

void ChangeScene(SCENE_TYPE _eSceneType)
{
	tEvent even = {};
	even.eEvent = EVENT_TYPE::SCENE_CHANGE;
	even.lParam = (DWORD_PTR)_eSceneType;

	SINGLE(CEventManager)->AddEvent(even);
}
