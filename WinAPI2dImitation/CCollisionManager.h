#pragma once

class CCollider;

class CCollisionManager
{
	SINGLETON(CCollisionManager);
private:
	bool	m_arrCheck[(UINT)OBJ_TYPE::SIZE][(UINT)OBJ_TYPE::SIZE];

public:
	void	Init();
	void	Update();
	void	CheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);
	void	Reset();

private:
	void	CollisionGroupUpdate(OBJ_TYPE _eLeft, OBJ_TYPE _eRight);
	bool	IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

