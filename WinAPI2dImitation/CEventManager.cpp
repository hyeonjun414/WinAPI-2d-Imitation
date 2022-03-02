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
		// lParam : ������Ʈ �ּ�
		// wParam : ������Ʈ �׷�
		CGameObject* pObj = (CGameObject*)_event.lParam;
		SINGLE(CSceneManager)->GetCurScene()->AddObject(pObj);
		break;
	}
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// ������Ʈ�� Dead���·� �����ϰ�
		// ���� ���� ������Ʈ���� ��Ƶд�.
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
		Logger::debug(L"����");
		delete m_vecDead[i];
	}

	m_vecDead.clear();

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}
	// �̺�Ʈ�� ��� ó���ϰ� �ʱ�ȭ
	m_vecEvent.clear();
}
