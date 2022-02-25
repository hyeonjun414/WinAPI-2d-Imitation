#pragma once

// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű �Է� �̺�Ʈ�� ��������.
//
// 2. Ű �Է� �̺�Ʈ ó��
//	tap, hold, away
//

class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	vector<tKeyInfo>	m_vecKey;

public:
	void				Init();
	void				Update();

	KEY_STATE	GetKeyState(KEY _eKey){ return m_vecKey[(int)_eKey].eState; }
};

