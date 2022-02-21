#pragma once
class CGameObject
{
protected:
	OBJ_GROUP		m_enumObjGroup;
	bool			m_bIsActive;

	Vec2			m_vec2Pos;
	Vec2			m_vec2Scale;


public:
	CGameObject();
	CGameObject(OBJ_GROUP objGroup);
	~CGameObject();

	void			SetActive(bool active);
	void			SetPos(Vec2 pos);
	void			SetScale(Vec2 scale);

	OBJ_GROUP		GetObjGroup();
	bool			GetActive();
	Vec2			GetPos();
	Vec2			GetScale();

	virtual void	Update();
	virtual void	Render(HDC hdc);
};

