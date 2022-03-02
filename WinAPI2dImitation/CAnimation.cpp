#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CGameObject.h"

CAnimation::CAnimation():
	m_pAnimator(nullptr),
	m_iCurFrame(0),
	m_fFlowTime(0.f),
	m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update()
{
	// 렉이 걸려서 DT가 급격히 쌓이면 프레임이 빠르게 진행될 수 있다.
	// 이를 해결하려면 누적된 Dt값을 1이하로 만들어 다음 프레임으로 한번에 건너뛰도록 반복문으로 처리할것.
	if (m_bFinish) return;

	m_fFlowTime += DT;
	if (m_fFlowTime > m_vecFrame[m_iCurFrame].fFrameTime)
	{
		++m_iCurFrame;

		if (m_vecFrame.size() <= m_iCurFrame)
		{
			m_iCurFrame = -1;
			m_bFinish = true;
			m_fFlowTime = 0.f;
			return;
		}
		m_fFlowTime -= m_vecFrame[m_iCurFrame].fFrameTime;
	}
}

void CAnimation::Render(HDC _hDC)
{
	if (m_bFinish) return;

	CGameObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetRenderPos();

	vPos += m_vecFrame[m_iCurFrame].vOffset;

	TransparentBlt(_hDC,
		(int)(vPos.x - m_vecFrame[m_iCurFrame].vSliceSize.x / 2.f), // 좌상단 위치 찾기
		(int)(vPos.y - m_vecFrame[m_iCurFrame].vSliceSize.y / 2.f), 
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.x), // 프레임 크기만큼 출력
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.y),
		m_pTex->GetDC(),
		(int)(m_vecFrame[m_iCurFrame].vLT.x), // 해당 텍스쳐내에서 잘라내기를 시작할 좌상단 좌표
		(int)(m_vecFrame[m_iCurFrame].vLT.y),
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.x), // 잘라낼 크기
		(int)(m_vecFrame[m_iCurFrame].vSliceSize.y),
		RGB(255,0,255));
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fFrameTime, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrame frame = {};
	for (int i = 0; i < _iFrameCount; i++)
	{
		frame.fFrameTime = _fFrameTime;
		frame.vSliceSize = _vSliceSize;
		frame.vLT = _vLeftTop + _vStep * i; // 프레임 별 좌상단

		m_vecFrame.push_back(frame);
	}
}
