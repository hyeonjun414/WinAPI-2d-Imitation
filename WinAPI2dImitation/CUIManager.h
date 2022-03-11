#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager)
private:
	CUI*	m_pFocusedUI;

public:
	void	Update();
	void	SetFocusedUI(CUI* _pUI);

private:
	CUI*	GetTargetUI(CUI* _pParentUI);
	CUI*	GetFocusedUI();
};

