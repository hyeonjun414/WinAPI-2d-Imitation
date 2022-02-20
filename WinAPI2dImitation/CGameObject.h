#pragma once
class CGameObject
{
protected:
	bool	m_bIsActive;
	fPoint	m_fptPos;
	fPoint	m_fptScale;
	fPoint	m_fSpeed;

public:
	CGameObject();
	CGameObject(fPoint pos, fPoint scale);
	~CGameObject();

	void	SetActive(bool active);
	void	SetPos(fPoint pos);
	void	SetScale(fPoint scale);

	bool	GetActive();
	fPoint	GetPos();
	fPoint	GetScale();

	void update();
	void render(HDC hdc);
};

