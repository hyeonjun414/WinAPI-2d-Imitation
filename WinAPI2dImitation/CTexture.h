#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    HDC         m_hDC;              
    HBITMAP     m_hBit;
    BITMAP      m_bmpInfo;


public:
    CTexture();
    ~CTexture();

    void Load(const wstring& _strFilePath);

    UINT Width() { return m_bmpInfo.bmWidth; }
    UINT Height() { return m_bmpInfo.bmHeight; }

    HDC GetDC() { return m_hDC; }
};

