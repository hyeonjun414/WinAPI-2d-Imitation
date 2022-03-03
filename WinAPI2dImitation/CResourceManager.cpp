#include "framework.h"
#include "CResourceManager.h"

#include "CTexture.h"

CResourceManager::CResourceManager()
{

}
CResourceManager::~CResourceManager()
{
	Safe_Delete_Map(m_mapTex);
}

CTexture* CResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// �ؽ��ĸ� ���� Ž���غ��� �ִٸ� �ش� �ؽ��ĸ� ��ȯ�Ѵ�.
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex) return pTex;

	// �ҷ��� �ؽ��İ� ���ٸ� �ҷ����� ������ �����ϰ� �ش� �ؽ��ĸ� ��ȯ�Ѵ�.

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
