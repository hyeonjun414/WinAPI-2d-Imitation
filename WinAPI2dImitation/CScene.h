#pragma once

// ���� ���� : �ش� Ŭ������ ������ ������ ����� �� �ְ����ش�. -> �������� ũ�⸸ �˷���.
// 1. ��������� ������ ȣ��Ǿ� #pragma once ����θ� Ȯ�� �Ұ��� ���� �ذ�
// 2. ������ �ӵ��� ����.
class CGameObject;

class CScene
{
protected:
	vector<CGameObject*>	m_vecObjectList[(int)OBJ_TYPE::SIZE]; // ���� ������Ʈ�� �׷캰�� ������ ����
	wstring					m_strName;
	SCENE_TYPE				m_enumSceneType;

public:
	CScene();
	CScene(wstring sceneName, SCENE_TYPE sceneType);
	virtual ~CScene();

	virtual void Update();
	virtual void Render(HDC hDC);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	void	SetName(const wstring& strName);
	wstring GetName();

	void AddObject(CGameObject* pObj);

protected:
	void ClearObject();
};

