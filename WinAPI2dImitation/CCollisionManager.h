#pragma once

class CCollider;

union COLLIDER_ID
{
	struct {
		UINT leftId;
		UINT rightId;
	};
	ULONGLONG ID;
};


class CCollisionManager
{
	SINGLETON(CCollisionManager);
private:
	map<ULONGLONG, bool> m_mapColInfo; // 충돌체 간의 이전 프레임 충돌 정보
	UINT	m_arrCheck[(UINT)OBJ_TYPE::SIZE];

public:
	void	Init();
	void	Update();
	void	CheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);
	void	UnCheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);
	void	Reset();

private:
	void	CollisionGroupUpdate(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);
	bool	IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

