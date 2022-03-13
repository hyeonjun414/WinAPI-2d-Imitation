#include "framework.h"
#include "CUI.h"

CUI::CUI(OBJ_TYPE _eType):
	CGameObject(_eType),
	m_pParentUI(nullptr),
	m_bCameraAffected(false),
	m_bMouseOn(false),
	m_bLbtnDown(false)

{
	SetPos(Vec2(100, 100));
	SetScale(Vec2(100, 100));
}

CUI::CUI(const CUI& _origin):
	CGameObject(_origin),
	m_pParentUI(nullptr),
	m_bCameraAffected(_origin.m_bCameraAffected),
	m_bMouseOn(false),
	m_bLbtnDown(false)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); i++)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

CUI* CUI::Clone()
{
	return new CUI(*this);
}

void CUI::Init()
{
}

void CUI::Update()
{
	UpdateChild();
}

void CUI::FinalUpdate()
{
	CGameObject::FinalUpdate();

	m_vFinalPos = GetPos();

	// 부모 UI오브젝트가 있을떄
	if (m_pParentUI)
	{
		// 현재 UI오브젝트 위치에 부모 오브젝트 위치를 더해준다.
		Vec2 vParentPos = m_pParentUI->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	MouseOnCheck();
	
	FinalUpdateChild();
}

void CUI::Render(HDC _hDC)
{
	Vec2 vPos = m_vFinalPos;
	Vec2 vScale = m_vScale;

	if (m_bCameraAffected)
	{
		vPos = SINGLE(CCameraManager)->GetRenderPos(vPos);
	}
	if (m_bLbtnDown)
	{
		SelectGDI green(_hDC, PEN_TYPE::GREEN);
		Rectangle(_hDC,
			(int)(vPos.x),
			(int)(vPos.y),
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_hDC,
			(int)(vPos.x),
			(int)(vPos.y),
			(int)(vPos.x + vScale.x),
			(int)(vPos.y + vScale.y));
	}


	RenderChild(_hDC);
}

void CUI::UpdateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->Update();
	}
}

void CUI::FinalUpdateChild()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->FinalUpdate();
	}
}

void CUI::RenderChild(HDC _hDC)
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->Render(_hDC);
	}
}

void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClick()
{
}

void CUI::SetCameraAffected(bool _bAffect)
{
	m_bCameraAffected = _bAffect;
	for (size_t i = 0; i < m_vecChildUI.size(); i++)
	{
		m_vecChildUI[i]->SetCameraAffected(_bAffect);
	}
}

void CUI::AddChild(CUI* _pUI)
{
	m_vecChildUI.push_back(_pUI);
	_pUI->m_pParentUI = this;
	_pUI->SetCameraAffected(this->m_bCameraAffected);
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = SINGLE(CKeyManager)->GetMousePos();
	Vec2 vScale = GetScale();

	if (m_bCameraAffected)
	{
		vMousePos = SINGLE(CCameraManager)->GetRenderPos(vMousePos);
	}
	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x &&
		m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}
