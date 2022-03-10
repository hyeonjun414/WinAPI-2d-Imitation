#pragma once
class CTexture;
class CResource;
class CSound;

class CResourceManager
{
	SINGLETON(CResourceManager)
private:
	// ���ڿ��� ���� ��ġ�ϴ� ���ҽ��� ã�ƿ��� ���� ������ش�.
	map<wstring, CResource*>		m_mapTex;
	map<wstring, CSound*>			m_mapSound;

public:
	CTexture*	LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture*	FindTexture(const wstring& _strKey);

	CSound*		LoadSound(const wstring& _strKey, const wstring _strRelativePath);
	CSound*		FindSound(const wstring& _strKey);

};

                     