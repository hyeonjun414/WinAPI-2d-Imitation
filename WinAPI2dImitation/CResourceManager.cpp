#include "framework.h"
#include "CResourceManager.h"

#include "CTexture.h"

CResourceManager::CResourceManager()
{

}
CResourceManager::~CResourceManager()
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); iter++)
	{
		delete iter->second;
	}
}

CTexture* CResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 텍스쳐를 먼저 탐색해보고 있다면 해당 텍스쳐를 반환한다.
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) return pTex;

	// 불러온 텍스쳐가 없다면 불러오는 과정을 진행하고 해당 텍스쳐를 반환한다.

	wstring strFilePath = SINGLE(CPathManager)->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResourceManager::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end()) return nullptr;


	return iter->second;
}
