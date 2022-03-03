#pragma once

class CGameObject;

class CEventManager
{
	SINGLETON(CEventManager);
private:
	vector<tEvent> m_vecEvent;
	vector<CGameObject*> m_vecDead; // ���� ���� ������Ʈ�� ��Ƶд�.

	void Excute(const tEvent& _event);

public:
	void Update();

	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

	void EventCreateObject(CGameObject* _pObj);
	void EventDeleteObject(CGameObject* _pObj);
	void EventChangeScene(SCENE_TYPE _eSceneType);
};

