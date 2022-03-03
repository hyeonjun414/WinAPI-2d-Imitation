#include "framework.h"
#include "CCamera.h"
#include "CGameObject.h"

CCamera::CCamera() :
	m_pTargetObj(nullptr),
	m_fTime(0.2f),
	m_vCamSize(WINSIZEX, WINSIZEY)
{
}

CCamera::~CCamera()
{
}

void CCamera::CalDiff()
{

	m_fFlowTime += DT;
	if (m_fFlowTime > m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
		if (vLookDir.x != 0 && vLookDir.y != 0)
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * DT;
		}
	}

	

	Vec2 vResolution = Vec2(WINSIZEX, WINSIZEY);
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter; // �߽ɰ��� ���̰�
	m_vPrevLookAt = m_vCurLookAt;
}

void CCamera::Init()
{
	m_vLookAt = Vec2(WINSIZEX / 2, WINSIZEY / 2);
	m_vPrevLookAt = m_vLookAt;
	m_vCurLookAt = m_vLookAt;
}

void CCamera::Update()
{
	// Ÿ���� �ִٸ�
	if (m_pTargetObj)
	{
		if (!m_pTargetObj->GetActive())
			m_pTargetObj = nullptr;
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
			m_vLookAt -= Vec2(0.f, +200.f);
		}

	}
	else
	{
		if (KEYCHECK(KEY::UP) == KEY_STATE::HOLD)
			m_vLookAt.y -= 500.f * DT;
		if (KEYCHECK(KEY::DOWN) == KEY_STATE::HOLD)
			m_vLookAt.y += 500.f * DT;
		if (KEYCHECK(KEY::LEFT) == KEY_STATE::HOLD)
			m_vLookAt.x -= 500.f * DT;
		if (KEYCHECK(KEY::RIGHT) == KEY_STATE::HOLD)
			m_vLookAt.x += 500.f * DT;
	}

	// ȭ�� �߾���ǥ��  ī�޶� LookAt ��ǥ���� ���̰� ���
	CalDiff();
}

bool CCamera::CheckBoundary()
{
	if (m_vLookAt.x - m_vCamSize.x / 2 <= 0 || m_vLookAt.x + m_vCamSize.x / 2 >= 1920 ||
		m_vLookAt.y - m_vCamSize.y / 2 <= 0 || m_vLookAt.y + m_vCamSize.y / 2 >= 1080)
	{
		return true;
	}
	return false;
}
