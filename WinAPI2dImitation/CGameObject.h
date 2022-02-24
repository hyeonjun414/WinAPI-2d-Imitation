#pragma once
class CGameObject
{
protected:
	OBJ_TYPE		m_enumObjType;	// 오브젝트 타입
	bool			m_bIsActive;	// 활성화 여부
	bool			m_bIsGravity;	// 중력 적용 여부

	Vec2			m_vec2Pos;		// 위치
	Vec2			m_vec2Scale;	// 크기

public:
	CGameObject();
	CGameObject(OBJ_TYPE objGroup);
	~CGameObject();

	void			SetActive(bool active);
	void			SetGravity(bool active);
	void			SetPos(Vec2 pos);
	void			SetScale(Vec2 scale);

	OBJ_TYPE		GetObjGroup();
	bool			GetActive();
	bool			GetGravity();
	Vec2			GetPos();
	Vec2			GetScale();
	

	virtual void	Init() = 0;
	virtual void	Update() = 0;
	virtual void	Render(HDC hDC) = 0;

	
};

