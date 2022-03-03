#pragma once

class CScene;

class CSceneManager
{
	friend class CEventManager;

	SINGLETON(CSceneManager);

private:
	CScene*		m_arrScene[(int)SCENE_TYPE::SIZE];	// 만들어진 모든 씬을 관리.
	CScene*		m_pCurScene;	// 현재 활성화된 장면을 결정함.

	void		ChangeScene(SCENE_TYPE _sceneType);


public:
	
	void		Update();
	void		Render(HDC _hDC);

	void		Init();


	CScene*		GetCurScene();


};

