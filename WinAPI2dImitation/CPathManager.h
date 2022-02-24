#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

private:
	wchar_t		m_strContentPath[255]; // ������ ��ü�� ��� ���� ���� 255���ڷ� ���ѵǾ�����.

public:
	void Init();
	const wchar_t* GetContentPath() { return m_strContentPath; }
};

