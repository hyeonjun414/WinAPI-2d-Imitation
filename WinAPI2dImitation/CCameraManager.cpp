#include "framework.h"
#include "CCameraManager.h"
#include "CGameObject.h"

CCameraManager::CCameraManager()
{
	m_vLookAt = Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_vCamSize = Vec2(1280.f, 720.f);
	m_vWorldSize = Vec2(1280.f, 720.f);
	m_vCurLookAt = m_vLookAt;
	m_vPrevLookAt = m_vLookAt;
	m_pTargetObj = nullptr;
	m_fFlowTime = m_fTime;
	m_fSpeed = 500;
	m_fPreSpeed = m_fSpeed;
	m_fAccel = 0;
}

CCameraManager::~CCameraManager()
{
}

void CCameraManager::CalDiff()
{
	// 방향 벡터를 구함
	Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

	// 아직 도착못했을때 이동
	if (vLookDir.Length() > 1)
	{
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * DT;
	}

	// 월드 크기를 고려해 카메라 이동 반경을 제어한다.
	CheckBoundary();

	// 화면의 중앙 좌표를 가져옴
	Vec2 vCenter = Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;

	m_fSpeed += m_fAccel * m_fAccelRate * DT;

}

void CCameraManager::Init()
{
}

void CCameraManager::Update()
{
	// 타켓이 있다면
	if (m_pTargetObj)
	{
		if (!m_pTargetObj->GetActive())
			m_pTargetObj = nullptr;
		else
			SetLookAt(m_pTargetObj->GetPos());//+ Vec2(0.f, -200.f));
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

	// 화면 중앙좌표와  카메라 LookAt 좌표간의 차이값 계산
	CalDiff();
}

void CCameraManager::SetLookAt(Vec2 _vLook)
{
	m_vLookAt = _vLook;
	float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();

	if(nullptr != m_pTargetObj)
		m_fSpeed = fMoveDist / m_fTime * 2;
	//else
	//	m_fSpeed = 0;
	m_fAccel = fMoveDist / m_fTime;

	m_fFlowTime = 0.f;
}

void CCameraManager::CheckBoundary()
{
	if (m_vCurLookAt.x - m_vCamSize.x / 2 < 0)
	{
		m_vCurLookAt.x = m_vCamSize.x / 2;
	}
	if (m_vCurLookAt.x + m_vCamSize.x / 2 > m_vWorldSize.x)
	{
		m_vCurLookAt.x = m_vWorldSize.x - m_vCamSize.x / 2;
	} 
	if (m_vCurLookAt.y - m_vCamSize.y / 2 < 0)
	{
		m_vCurLookAt.y = m_vCamSize.y / 2;
	} 
	if (m_vCurLookAt.y + m_vCamSize.y / 2 > m_vWorldSize.y)
	{
		m_vCurLookAt.y = m_vWorldSize.y - m_vCamSize.y / 2;
	}
}

void CCameraManager::Scroll(Vec2 vec, float velocity)
{
	m_vLookAt +=  vec * velocity * DT;
	m_vCurLookAt +=  vec * velocity * DT;

	Vec2 vCenter = Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_vDiff = m_vCurLookAt - vCenter;
}