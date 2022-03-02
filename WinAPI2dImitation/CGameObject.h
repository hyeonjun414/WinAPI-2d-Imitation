#pragma once

class CCollider;
class CTexture;
class CAnimator;

class CGameObject
{
protected:
	wstring			m_strName;		// ������Ʈ �̸�

	OBJ_TYPE		m_enumObjType;	// ������Ʈ Ÿ��
	bool			m_bIsActive;	// Ȱ��ȭ ����
	bool			m_bIsGravity;	// �߷� ���� ����

	Vec2			m_vec2Pos;		// ��ġ
	Vec2			m_vRenderPos;	// ȭ��� �����ġ
	Vec2			m_vec2Scale;	// ũ��

	CTexture*		m_pTex;
	CCollider*		m_pCollider;
	CAnimator*		m_pAnimator;

public:
	CGameObject();
	CGameObject(OBJ_TYPE _bjGroup);
	CGameObject(const CGameObject& _origin); // ���� ������
	virtual ~CGameObject();

	virtual void	Init() = 0;
	virtual void	Update() = 0;
	virtual void	Render(HDC _hDC) = 0;

	virtual void	FinalUpdate() final;	// ������Ʈ�� ���� ������ ������Ʈ�� �ֻ��� Ŭ�������� �Ǵ��Ѵ�.
	virtual void	ComponentRender(HDC _hDC) final; // ������Ʈ�� �ִ� ��� ���� Ŭ�������� ������ Render���� ȣ���Ѵ�.

	void			SetName(const wstring& _strName)	{ m_strName = _strName; }
	void			SetObjGroup(OBJ_TYPE _eObjType)		{ m_enumObjType = _eObjType; }
	void			SetActive(bool _active)				{ m_bIsActive = _active; }
	void			SetGravity(bool _active)			{ m_bIsGravity = _active; }
	void			SetPos(Vec2 _pos)					{ m_vec2Pos = _pos; }
	void			SetScale(Vec2 _scale)				{ m_vec2Scale = _scale; }

	const wstring&	GetName()		{ return m_strName; }
	OBJ_TYPE		GetObjGroup()	{ return m_enumObjType; }
	bool			GetActive()		{ return m_bIsActive; }
	bool			GetGravity()	{ return m_bIsGravity; }
	Vec2			GetPos()		{ return m_vec2Pos; }
	Vec2			GetRenderPos()	{ return m_vRenderPos; }
	Vec2			GetScale()		{ return m_vec2Scale; }
	CCollider*		GetCollider()	{ return m_pCollider; }
	CAnimator*		GetAnimator()	{ return m_pAnimator; }
	
	// Component
	void			TextureRender(HDC _hDC);
	void			CreateCollider();
	void			CreateAnimator();


	virtual void	OnCollision(CCollider* _pOther) {};
	virtual void	OnCollisionEnter(CCollider* _pOther) {};
	virtual void	OnCollisionExit(CCollider* _pOther) {};

	virtual CGameObject* Clone() = 0;


	
};

