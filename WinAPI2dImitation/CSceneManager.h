#pragma once

class CScene;

class CSceneManager
{
	friend class CEventManager;

	SINGLETON(CSceneManager);

private:
	CScene*		m_arrScene[(int)SCENE_TYPE::SIZE];	// ������� ��� ���� ����.
	CScene*		m_pCurScene;	// ���� Ȱ��ȭ�� ����� ������.

	void		ChangeScene(SCENE_TYPE _sceneType);


public:
	
	void		Update();
	void		Render(HDC _hDC);

	void		Init();


	CScene*		GetCurScene();


};

