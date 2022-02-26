#include "framework.h"
#include "CCollisionManager.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager():
	m_arrCheck{}
{
}
CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Init()
{
	Reset();
}

void CCollisionManager::Update()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::SIZE; i++)
	{
		for (int j = 0; j < (UINT)OBJ_TYPE::SIZE; j++)
		{
			if (m_arrCheck[i][j] || m_arrCheck[j][i])
			{
				// ���� ������ �浹ó���� ������ ������Ʈ�� �����´�.
				CollisionGroupUpdate((OBJ_TYPE)i, (OBJ_TYPE)j);
			}
		}
	}
}

void CCollisionManager::CheckGroup(OBJ_TYPE _eLeft, OBJ_TYPE _eRight)
{
	m_arrCheck[(UINT)_eLeft][(UINT)_eRight] = true;
	m_arrCheck[(UINT)_eRight][(UINT)_eLeft] = true;
}

void CCollisionManager::Reset()
{
	// �迭�� ���� 0���� �ʱ�ȭ
	for (int i = 0; i < (UINT)OBJ_TYPE::SIZE; i++)
	{
		for (int j = 0; j < (UINT)OBJ_TYPE::SIZE; j++)
		{
			m_arrCheck[i][j] = false;
		}
	}
}

void CCollisionManager::CollisionGroupUpdate(OBJ_TYPE _eLeft, OBJ_TYPE _eRight)
{
	// ���� �� ������.
	CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();

	const vector<CGameObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CGameObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (int i = 0; i < (int)vecLeft.size(); i++)
	{
		// ���� ������Ʈ�� �浹ü�� ���� ��� ����,
		if (nullptr == vecLeft[i]->GetCollider()) 
			continue;

		for (int j = 0; j < (int)vecRight.size(); j++)
		{
			// ������ ������Ʈ�� �浹ü�� ���� ��� ����,
			// �ڱ� �ڽŰ��� �浹�� ����
			// ���� ���� ������Ʈ�� ������ ������Ʈ�� ���� �ּҸ� ����Ű��
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j])
				continue;

			// �� ������Ʈ�� �浹�ߴ��� Ȯ��,
			// Ű ���¿� ���������� ���� �������� �浹������ �ʿ��ϴ�.
			if (IsCollision(vecLeft[i]->GetCollider(),
							vecRight[j]->GetCollider()))
			{

			}
			else
			{

			}

		}
	}
}

bool CCollisionManager::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	return false;
}
