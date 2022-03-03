#pragma once

class CGameObject;

class CCamera
{
	SINGLETON(CCamera)
private:
	Vec2			m_vCamSize;		// 카메라의 해상도


	Vec2			m_vLookAt;		// 카메라가 보고있는 화면의 중심의 위치
	Vec2			m_vCurLookAt;	// 이전 프레임과 현재 프레임의 보정 위치
	Vec2			m_vPrevLookAt;	// 카메라가 보는 이전 프레임 위치

	CGameObject*	m_pTargetObj;	// 현재 보고 있는 오브젝트
	Vec2			m_vDiff;		// 해상도 중심위치와, 카메라 LookAt 간의 차이값

	float			m_fTime;		// 타겟을 따라가는데 걸리는 시간
	float			m_fSpeed;		// 화면 이동속도
	float			m_fFlowTime;	// 누적 시간

	void CalDiff();

public:
	void Init();
	void Update();

	void	SetLookAt(Vec2 _vLook)			
	{
		m_vLookAt = _vLook;
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fFlowTime = 0.f;
	}
	void	SetTarget(CGameObject* _pTarget)	{ m_pTargetObj = _pTarget; }
	Vec2	GetLookAt()							{ return m_vCurLookAt; }
	Vec2	GetRenderPos(Vec2 _vObjPos)			{ return _vObjPos - m_vDiff; }
	Vec2	GetRealPos(Vec2 _vRenderPos)		{ return _vRenderPos + m_vDiff; }

	bool CheckBoundary();
};

