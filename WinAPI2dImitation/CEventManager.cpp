#include "framework.h"
#include "CEventManager.h"
#include "CScene.h"
#include "CGameObject.h"

CEventManager::CEventManager()
{}
CEventManager::~CEventManager()
{}

void CEventManager::Excute(const tEvent& _event)
{
	switch (_event.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : 오브젝트 주소
		// wParam : 오브젝트 그룹
		CGameObject* pObj = (CGameObject*)_event.lParam;
		SINGLE(CSceneManager)->GetCurScene()->AddObject(pObj);
		break;
	}
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// 오브젝트를 Dead상태로 변경하고
		// 삭제 예정 오브젝트들을 모아둔다.
		CGameObject* pObj = (CGameObject*)_event.lParam;
		if (!pObj->GetActive()) break;
		pObj->SetActive(false);
		m_vecDead.push_back(pObj);
		break;
	}
	case EVENT_TYPE::SCENE_CHANGE:
	{
		SINGLE(CSceneManager)->ChangeScene((SCENE_TYPE)_event.lParam);
		break;
	}

	}
}

void CEventManager::Update()
{
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		Logger::debug(L"실행");
		delete m_vecDead[i];
	}

	m_vecDead.clear();

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}
	// 이벤트를 모두 처리하고 초기화
	m_vecEvent.clear();
}
