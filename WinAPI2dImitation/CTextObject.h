#pragma once
#include "CGameObject.h"
class CTextObject :
    public CGameObject
{
    wstring     m_strText;

public:
    CTextObject();
    CTextObject(wstring _strText, OBJ_TYPE _objGroup);
    ~CTextObject();
    CLONE(CTextObject)

    virtual void    Init();
    virtual void    Update();
    virtual void    Render(HDC _hDC);

    
};

