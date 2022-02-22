#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);

private:
	CScene*		m_arrScene[(int)SCENE_TYPE::SIZE];	// ������� ��� ���� ����.
	CScene*		m_pCurScene;	// ���� Ȱ��ȭ�� ����� ������.

public:
	
	void Update();
	void Render(HDC hdc);

	void Init();

	void ChangeScene(SCENE_TYPE sceneType);


};

