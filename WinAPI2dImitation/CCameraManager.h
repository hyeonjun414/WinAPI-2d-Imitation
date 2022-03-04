#pragma once

class CGameObject;

class CCameraManager
{
	SINGLETON(CCameraManager)
private:
	Vec2			m_vCamSize;			// ī�޶��� �ػ�


	Vec2			m_vLookAt;			// ī�޶� �����ִ� ȭ���� �߽��� ��ġ
	Vec2			m_vCurLookAt;		// ���� �����Ӱ� ���� �������� ���� ��ġ
	Vec2			m_vPrevLookAt;		// ī�޶� ���� ���� ������ ��ġ

	CGameObject*	m_pTargetObj;		// ���� ���� �ִ� ������Ʈ
	Vec2			m_vDiff;			// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���̰�

	float			m_fTime = 1.f;			// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float			m_fFlowTime;			// ���� �ð�
	float			m_fSpeed;				// Ÿ���� ���󰡴� �ӵ�
	float			m_fPreSpeed;			// Ÿ���� ���󰡴� �ӵ�
	float			m_fAccel;				// Ÿ���� ���󰡴� ��ӵ�
	float			m_fAccelRate = 10.f;			// ���� ��ġ

	void CalDiff();

public:
	void Init();
	void Update();

	void	SetLookAt(Vec2 _vLook);
	void	SetTarget(CGameObject* _pTarget)	{ m_pTargetObj = _pTarget; }
	Vec2	GetLookAt()							{ return m_vCurLookAt; }
	Vec2	GetRenderPos(Vec2 _vObjPos)			{ return _vObjPos - m_vDiff; }
	Vec2	GetRealPos(Vec2 _vRenderPos)		{ return _vRenderPos + m_vDiff; }

	bool CheckBoundary();
};

