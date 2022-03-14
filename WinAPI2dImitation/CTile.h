#pragma once
#include "CGameObject.h"

class CTexture;

class CTile :
    public CGameObject
{
private:
    
    int         m_iIdx;     // 자신이 몇번째 타일인지
    bool        m_bIsColl;  // 충돌체가 있는지

    CTexture* m_pTex;

public:
    const static int SIZE_TILE = 32;

    CTile(OBJ_TYPE _eObjType = OBJ_TYPE::TILE);
    virtual ~CTile();
    CLONE(CTile);

    virtual void Init();
    virtual void Update();
    virtual void Render(HDC _hDC);

    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

    void SetColl(bool _flag)            { m_bIsColl = _flag; }
    void SetTexture(CTexture* _pTex)    { m_pTex = _pTex; }
    void SetImgIdx(UINT _idx)           { m_iIdx = _idx; }
};

