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

	UINT m_iTileX;
	UINT m_iTileY;

public:
	CScene();
	CScene(wstring _sceneName, SCENE_TYPE _sceneType);
	virtual ~CScene();

	virtual void	Update();
	virtual void	FinalUpdate();
	virtual void	Render(HDC _hDC);

	virtual void	Enter() = 0;
	virtual void	Exit() = 0;

	void			SetName(const wstring& _strName){ m_strName = _strName; }
	wstring			GetName()						{ return m_strName; }

	UINT			GetTileX()						{	return m_iTileX;}
	UINT			GetTileY()						{	return m_iTileY;}


	void			AddObject(CGameObject* _pObj);
	void			EraseObject(CGameObject* _pObj);
	void			DeleteGroup(OBJ_TYPE _group);
	const vector<CGameObject*>& GetGroupObject(OBJ_TYPE _eType)
	{
		return m_vecObjectList[(UINT)_eType];
	};
	vector<CGameObject*>& GetUIGroup()
	{
		return m_vecObjectList[(UINT)OBJ_TYPE::UI];
	};

	void CreateTile(UINT _xSize, UINT _ySize);
	void LoadTile(const wstring& _strPath);
	void RenderTile(HDC _hDC);

protected:
	void			ClearObject();
};

