#pragma once
class CGameObject
{
protected:
	OBJ_TYPE		m_enumObjType;
	bool			m_bIsActive;

	Vec2			m_vec2Pos;
	Vec2			m_vec2Scale;
	Vec2			m_vec2fSpeed;

public:
	CGameObject();
	CGameObject(OBJ_TYPE objGroup);
	~CGameObject();

	void			SetActive(bool active);
	void			SetPos(Vec2 pos);
	void			SetScale(Vec2 scale);

	OBJ_TYPE		GetObjGroup();
	bool			GetActive();
	Vec2			GetPos();
	Vec2			GetScale();

	virtual void	Init() = 0;
	virtual void	Update() = 0;
	virtual void	Render(HDC hDC) = 0;

	
};

