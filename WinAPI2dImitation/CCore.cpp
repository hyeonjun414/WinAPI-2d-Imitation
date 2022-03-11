
#include "framework.h"
#include "CCore.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CTexture.h"

CCore::CCore() :
	m_hDC(0),
	m_arrBrush{},
	m_arrPen{},
	m_bDebugMode(false)
{
}
CCore::~CCore()
{
	// ���� DC ����
	ReleaseDC(hWnd, m_hDC);

	for (int i = 0; i < (UINT)PEN_TYPE::SIZE; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CCore::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CCore::Update()
{
	// ������ ������ ����
	
	// �Ŵ��� Ŭ���� ������Ʈ ( �̺�Ʈ, Ÿ��, Ű, ����, ���, �浹, ī�޶�, UI )
	SINGLE(CEventManager)->Update();

	SINGLE(CTimeManager)->Update();
	SINGLE(CKeyManager)->Update();
	SINGLE(CSoundManager)->Update();

	SINGLE(CSceneManager)->Update();
	SINGLE(CCollisionManager)->Update();
	SINGLE(CCameraManager)->Update();
	SINGLE(CUIManager)->Update();
	

	if (KEYCHECK(KEY::CTRL) == KEY_STATE::TAP)
	{
		m_bDebugMode = !m_bDebugMode;
	}
}


void CCore::Render()
{
	// ȭ�� Clear
	Rectangle(m_pMemTex->GetDC(), -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// �Ŵ��� Ŭ���� ���� ( ���, ī�޶� )
	SINGLE(CSceneManager)->Render(m_pMemTex->GetDC());
	SINGLE(CCameraManager)->Render(m_pMemTex->GetDC());

	// ������ ������ ���� �׷��ִ� �۾�
	// FPS ���
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::GetInst()->GetFPS());
	TextOutW(m_pMemTex->GetDC(), WINSIZEX - 60, 10, strFPS, 5);

	// m_hMemDC�� ��� �׸� ������ m_hDC�� �ѹ��� �ٽ� �׸�.
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	
}

void CCore::Init()
{
	// Core�� �ʱ�ȭ ����

	// ���� ����� ��, �귯�� ����
	CreateBrushPen();

	// �ھ��� ������ DC �Ҵ�
	m_hDC = GetDC(hWnd);

	// �Ŵ��� Ŭ���� �ʱ�ȭ ( Ÿ��, Ű, ���, ����, ���, �浹, ī�޶� )
	SINGLE(CTimeManager)->Init();
	SINGLE(CKeyManager)->Init();
	SINGLE(CPathManager)->Init();
	SINGLE(CSoundManager)->Init();
	SINGLE(CSceneManager)->Init();
	SINGLE(CCollisionManager)->Init();
	SINGLE(CCameraManager)->Init();
	
	
	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_pMemTex = SINGLE(CResourceManager)->CreateTexture(L"CoreTex", WINSIZEX, WINSIZEY);

}
