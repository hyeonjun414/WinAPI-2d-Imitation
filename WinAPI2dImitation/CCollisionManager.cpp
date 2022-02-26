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
				// 현재 씬에서 충돌처리를 수행할 오브젝트를 가져온다.
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
	// 배열을 전부 0으로 초기화
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
	// 현재 씬 가져옴.
	CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();

	const vector<CGameObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CGameObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (int i = 0; i < (int)vecLeft.size(); i++)
	{
		// 왼쪽 오브젝트가 충돌체가 없을 경우 다음,
		if (nullptr == vecLeft[i]->GetCollider()) 
			continue;

		for (int j = 0; j < (int)vecRight.size(); j++)
		{
			// 오른쪽 오브젝트가 충돌체가 없을 경우 다음,
			// 자기 자신과의 충돌을 방지
			// 만약 왼쪽 오브젝트와 오른쪽 오브젝트가 같은 주소를 가리키면
			if (nullptr == vecRight[j]->GetCollider() ||
				vecLeft[i] == vecRight[j])
				continue;

			// 두 오브젝트가 충돌했는지 확인,
			// 키 상태와 마찬가지로 이전 프레임의 충돌정보가 필요하다.
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
