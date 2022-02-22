#pragma once

// 전방 선언 : 해당 클래스의 포인터 변수를 사용할 수 있게해준다. -> 데이터의 크기만 알려줌.
// 1. 헤더파일이 여러번 호출되어 #pragma once 선언부를 확인 불가한 문제 해결
// 2. 컴파일 속도를 줄임.
class CGameObject;

class CScene
{
protected:
	vector<CGameObject*>	m_vecObjectList[(int)OBJ_TYPE::SIZE]; // 게임 오브젝트를 그룹별로 저장할 벡터
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

