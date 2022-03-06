#pragma once
#include "CGameObject.h"

class CTexture;

class CImageObject :
    public CGameObject
{
private:
    bool                m_bRenderStyle;
public:
    CImageObject();
    CImageObject(OBJ_TYPE _objGroup);
    CImageObject(OBJ_TYPE _objGroup, wstring _strTexName, wstring _strTexPath , bool _renderStyle);
    virtual ~CImageObject();
    CLONE(CImageObject)

    virtual void    Init();
    virtual void    Update();
    virtual void    Render(HDC _hDC);


};

