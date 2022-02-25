#pragma once

class CCollider;

class CGameObject
{
protected:
	OBJ_TYPE		m_enumObjType;	// ������Ʈ Ÿ��
	bool			m_bIsActive;	// Ȱ��ȭ ����
	bool			m_bIsGravity;	// �߷� ���� ����

	Vec2			m_vec2Pos;		// ��ġ
	Vec2			m_vec2Scale;	// ũ��

	CCollider*		m_pCollider;

public:
	CGameObject();
	CGameObject(OBJ_TYPE _bjGroup);
	virtual ~CGameObject();

	virtual void	Init() = 0;
	virtual void	Update() = 0;
	virtual void	Render(HDC _hDC) = 0;

	virtual void	FinalUpdate() final;	// ������Ʈ�� ���� ������ ������Ʈ�� �ֻ��� Ŭ�������� �Ǵ��Ѵ�.
	virtual void	ComponentRender(HDC _hDC) final; // ������Ʈ�� �ִ� ��� ���� Ŭ�������� ������ Render���� ȣ���Ѵ�.

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

