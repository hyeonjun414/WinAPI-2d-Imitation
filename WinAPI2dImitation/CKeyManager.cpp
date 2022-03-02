#include "framework.h"
#include "CKeyManager.h"

// ���� Ű���� �˾ƾ��Ѵ�. -> ������ Ű �ε����� ������ ��ġ.
int g_arrVK[(int)KEY::SIZE] = 
{
	VK_UP,		//	UP,
	VK_DOWN,	//	DOWN,
	VK_LEFT,	//	LEFT,
	VK_RIGHT,	//	RIGHT,
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','Z','X','C','V','B',
	VK_MENU,	//	ALT,
	VK_CONTROL,	//	LSHIFT,
	VK_LSHIFT,	//	CTRL,
	VK_SPACE,	//	SPACE,
	VK_RETURN,	//	ENTER,
	VK_ESCAPE,	//	ESC,

	VK_LBUTTON, //	LBTN,
	VK_RBUTTON, //  RBTN,

	//	LAST
};


CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::Init()
{
	// Ű �Ŵ��� �ʱ�ȭ
	
	// �켱 ���Ϳ� Ű ������ �ʱ�ȭ ������Ѵ�.
	// LAST�� KEY INDEX�� ���� �ֱ� ������ �ݺ��ؾ��ϴ� Ƚ���� ����� �� �ִ�. ==> size()
	for (int i = 0; i < (int)KEY::SIZE; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyManager::Update()
{
	// ���� ���õ� �����찡 ���� �������ΰ��� Ȯ���Ѵ�.
	HWND curWnd = GetFocus();

	// ���� �����찡 ���õ��� ���� ���¸� ���
	if (hWnd != curWnd)
	{
		// ��ü Ű�� �ȴ��� ���·� ������ش�.
		for (int i = 0; i < (int)KEY::SIZE; i++)
		{
			// �ȴ��� ���·� ���鶧 ������ ���� Ű�� ���� ó���� �����Ѵ�.
			if (m_vecKey[i].bPrevPush)
				// ������ �����־��ٸ� AWAY��
				m_vecKey[i].eState = KEY_STATE::AWAY;

			else
				// �ȴ����־��ٸ� �ƿ� ���������� ����
				m_vecKey[i].eState = KEY_STATE::NONE;

			m_vecKey[i].bPrevPush = false;
		}
		// AWAY�� ���°� ��ȯ�� Ű�� ���� ������Ʈ�� NONE���� ��ȯ�ȴ�.

		return;
	}

	// ���� �����찡 ��Ŀ�� �Ǿ�������

	// ��� Ű�� ���� Ȯ���� �����Ѵ�.
	for (int i = 0; i < (int)KEY::SIZE; i++)
	{
		// Ű�� ���ȴ��� ����Ű �迭�� ���鼭 Ȯ��
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
		{
			// �������� �����־��ٸ� �ش� Ű�� ���¸� 
			if (m_vecKey[i].bPrevPush)
			{
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			// �ȴ��� �־��ٸ�
			else
			{
				m_vecKey[i].eState = KEY_STATE::TAP;
			}
			m_vecKey[i].bPrevPush = true;
		}
		// Ű�� �ȴ��ȴ�
		else
		{
			// �������� �����־��ٸ�
			if (m_vecKey[i].bPrevPush)
				// ������ �����־��ٸ� AWAY��
				m_vecKey[i].eState = KEY_STATE::AWAY;

			else
				// �ȴ����־��ٸ� �ƿ� ���������� ����
				m_vecKey[i].eState = KEY_STATE::NONE;

			m_vecKey[i].bPrevPush = false;

		}

		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(hWnd, &ptPos);
		if (ptPos.x < 0 || ptPos.x > WINSIZEX ||
			ptPos.y < 0 || ptPos.y > WINSIZEY)
		{
			m_vCurMousePos = Vec2(WINSIZEX / 2, WINSIZEY / 2);
		}
		else
		{
			m_vCurMousePos = Vec2(ptPos.x, ptPos.y);
		}
	}
}
