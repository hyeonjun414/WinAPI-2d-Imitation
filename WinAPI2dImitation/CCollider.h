#pragma once

class CGameObject;

class CCollider
{
	friend class CGameObject;

private:
	static UINT	g_iNextID; // 충돌체 생성시 ID값을 지정할 변수

	CGameObject* m_pOwner; // 해당 콜라이더를 소유하는 오브젝트

	Vec2	m_vOffsetPos;	// 오브젝트에서의 상대적인 위치 -> 기준점은 오브젝트의 중심이다.
	Vec2	m_vFinalPos;	// 충돌체의 최종 위치
	Vec2	m_vScale;		// 충돌체의 크기 정보

	UINT	m_uiID;			// 충돌체의 고유한 ID

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

