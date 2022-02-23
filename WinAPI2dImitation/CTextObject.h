#pragma once
#include "CGameObject.h"
class CTextObject :
    public CGameObject
{
    wstring     m_strText;

public:
    CTextObject();
    CTextObject(wstring strText, OBJ_TYPE objGroup);
    ~CTextObject();

    virtual void Init();
    virtual void Update();
    virtual void Render(HDC hDC);
};

