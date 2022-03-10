#include "framework.h"
#include "CResourceManager.h"

#include "CTexture.h"
#include "CSound.h"
CResourceManager::CResourceManager():
	m_mapTex{},
	m_mapSound{}
{

}
CResourceManager::~CResourceManager()
{
	Safe_Delete_Map(m_mapTex);
	Safe_Delete_Map(m_mapSound);
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
	map<wstring, CResource*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end()) return nullptr;


	return (CTexture*)iter->second;
}

CSound* CResourceManager::LoadSound(const wstring& _strKey, const wstring _strRelativePath)
{
	// 텍스쳐를 먼저 탐색해보고 있다면 해당 텍스쳐를 반환한다.
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound) return pSound;

	// 불러온 텍스쳐가 없다면 불러오는 과정을 진행하고 해당 텍스쳐를 반환한다.

	wstring strFilePath = SINGLE(CPathManager)->GetContextRelativePath();
	strFilePath += _strRelativePath;

	pSound = new CSound;
	pSound->Load(strFilePath);
	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}

CSound* CResourceManager::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end()) return nullptr;


	return (CSound*)iter->second;
}
