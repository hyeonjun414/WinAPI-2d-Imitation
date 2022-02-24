#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

private:
	wchar_t		m_strContentPath[255]; // 윈도우 자체에 경로 글자 수가 255글자로 제한되어있음.

public:
	void Init();
	const wchar_t* GetContentPath() { return m_strContentPath; }
};

