#pragma once

// ���� ���� : �ش� Ŭ������ ������ ������ ����� �� �ְ����ش�. -> �������� ũ�⸸ �˷���.
// 1. ��������� ������ ȣ��Ǿ� #pragma once ����θ� Ȯ�� �Ұ��� ���� �ذ�
// 2. ������ �ӵ��� ����.
// �� : class CGameObject;

class CScene
{
	
	vector<CGameObject*>	m_vecObjectList[(int)OBJ_GROUP::SIZE]; // ���� ������Ʈ�� �׷캰�� ������ ����
	wstring					m_strName;

public:
	CScene();
	~CScene();

	virtual void Update();
	virtual void Render(HDC hdc);

	void	SetName(const wstring& strName);
	wstring GetName();

	void AddObject(CGameObject* pObj);
};

