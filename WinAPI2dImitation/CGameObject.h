#pragma once

class CCollider;

class CGameObject
{
protected:
	OBJ_TYPE		m_enumObjType;	// 오브젝트 타입
	bool			m_bIsActive;	// 활성화 여부
	bool			m_bIsGravity;	// 중력 적용 여부

	Vec2			m_vec2Pos;		// 위치
	Vec2			m_vec2Scale;	// 크기

	CCollider*		m_pCollider;

public:
	CGameObject();
	CGameObject(OBJ_TYPE _bjGroup);
	virtual ~CGameObject();

	virtual void	Init() = 0;
	virtual void	Update() = 0;
	virtual void	Render(HDC _hDC) = 0;

	virtual void	FinalUpdate() final;	// 컴포넌트의 실행 유무는 오브젝트의 최상위 클래스에서 판단한다.
	virtual void	ComponentRender(HDC _hDC) final; // 컴포넌트가 있는 경우 하위 클래스에서 구현된 Render에서 호출한다.

	void			SetActive(bool _active)		{ m_bIsActive = _active; }
	void			SetGravity(bool _active)	{ m_bIsGravity = _active; }
	void			SetPos(Vec2 _pos)			{ m_vec2Pos = _pos; }
	void			SetScale(Vec2 _scale)		{ m_vec2Scale = _scale; }

	OBJ_TYPE		GetObjGroup()	{ return m_enumObjType; }
	bool			GetActive()		{ return m_bIsActive; }
	bool			GetGravity()	{ return m_bIsGravity; }
	Vec2			GetPos()		{ return m_vec2Pos; }
	Vec2			GetScale()		{ return m_vec2Scale; }
	
	// Component
	void			CreateCollider();



	
};

