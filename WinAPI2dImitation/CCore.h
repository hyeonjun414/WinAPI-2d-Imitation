#pragma once
class CCore
{
	SINGLETON(CCore);

private:
	HDC m_hDC;
	
	HBITMAP m_hBMP;
	HDC		m_hMemDC;

public :
	void Update(); // ���� ������Ʈ
	void Render(); // ���� �׸���

	void Init();
};

