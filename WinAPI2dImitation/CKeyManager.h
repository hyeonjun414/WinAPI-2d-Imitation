#pragma once

// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키 입력 이벤트를 가져간다.
//
// 2. 키 입력 이벤트 처리
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

