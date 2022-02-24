#pragma once
class CGameObject
{
protected:
	OBJ_TYPE		m_enumObjType;	// ������Ʈ Ÿ��
	bool			m_bIsActive;	// Ȱ��ȭ ����
	bool			m_bIsGravity;	// �߷� ���� ����

	Vec2			m_vec2Pos;		// ��ġ
	Vec2			m_vec2Scale;	// ũ��

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

