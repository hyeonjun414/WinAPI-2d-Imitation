#pragma once
#include "CGameObject.h"

class CTexture;

class CImageObject :
    public CGameObject
{
private :
    CTexture* m_pTex;

public:
    CImageObject();
    CImageObject(OBJ_TYPE objGroup);
    ~CImageObject();


    virtual void Init();
    virtual void Update();
    virtual void Render(HDC hDC);
    
};

