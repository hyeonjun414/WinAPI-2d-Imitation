#pragma once

class CGameObject;

class CCollider
{
	friend class CGameObject;

private:
	static UINT	g_iNextID; // �浹ü ������ ID���� ������ ����

	CGameObject* m_pOwner; // �ش� �ݶ��̴��� �����ϴ� ������Ʈ

	Vec2	m_vOffsetPos;	// ������Ʈ������ ������� ��ġ -> �������� ������Ʈ�� �߽��̴�.
	Vec2	m_vFinalPos;	// �浹ü�� ���� ��ġ
	Vec2	m_vScale;		// �浹ü�� ũ�� ����

	UINT	m_uiID;			// �浹ü�� ������ ID

public:
	CCollider();
	~CCollider();

	void FinalUpdate();
	void Render(HDC _hDC);

	void SetOffsetPos(Vec2 _vPos)	{ m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale)		{ m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale()		{ return m_vScale; }
};

