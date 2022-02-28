#pragma once
class CCore
{
	SINGLETON(CCore);

private:
	HDC			m_hDC;
	
	HBITMAP		m_hBMP;
	HDC			m_hMemDC;

	// ���� ����� �׸���� ���� ����
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::SIZE];
	HPEN		m_arrPen[(UINT)PEN_TYPE::SIZE];

	void		CreateBrushPen();

public :
	void		Update(); // ���� ������Ʈ
	void		Render(); // ���� �׸���

	void		Init();
	
	HDC			GetMainDC()						{ return m_hDC; }
	HBRUSH		GetBrush(BRUSH_TYPE _brushType) { return m_arrBrush[(UINT)_brushType]; }
	HPEN		GetPEN(PEN_TYPE _penType)		{ return m_arrPen[(UINT)_penType]; }
};

