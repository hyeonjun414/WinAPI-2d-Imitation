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
    CImageObject(OBJ_TYPE _objGroup);
    virtual ~CImageObject();
    CLONE(CImageObject)

    virtual void    Init();
    virtual void    Update();
    virtual void    Render(HDC _hDC);
    
};

