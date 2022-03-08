#include "framework.h"
#include "CUIManager.h"
#include "CScene.h"
#include "CUI.h"

CUIManager::CUIManager()
{

}
CUIManager::~CUIManager()
{

}
void CUIManager::Update()
{
	CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
	const vector<CGameObject*>& vecUI = pCurScene->GetGroupObject(OBJ_TYPE::UI);

	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];

		pUI = GetTargetUI(pUI);

		if(nullptr != pUI)
		{
			pUI->MouseOn();
			if (KEYCHECK(KEY::LBTN) == KEY_STATE::HOLD)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if(KEYCHECK(KEY::LBTN) == KEY_STATE::AWAY)
			{
				pUI->MouseLbtnUp();
				if (pUI->m_bLbtnDown) // 눌리고 있는 상황
				{
					pUI->MouseLbtnClick();
				}
				pUI->m_bLbtnDown = false;
			}
		}
	}
}

CUI* CUIManager::GetTargetUI(CUI* _pParentUI)
{
	// 클릭하는 UI의 최하단 UI를 부르도록 하는 함수 -> 순회하여 탐색해야함.
	list<CUI*> queue;
	vector<CUI*>	vecNoneTarget;

	CUI* pTargerUI = nullptr;
	queue.push_back(_pParentUI); // 부모를 우선 탐색

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargerUI)
			{
				vecNoneTarget.push_back(pTargerUI);
			}
			pTargerUI = pUI;
		}
		else
		{
			// 애초에 마우스가 안올라갔던 UI도 논타겟으로 설정
			vecNoneTarget.push_back(pUI);
		}
		const vector<CUI*> vecChild = pUI->GetChild();
		for (size_t i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// 논타겟 UI는  마우스가 안올라간것으로 설정
	if (KEYCHECK(KEY::LBTN) == KEY_STATE::AWAY)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); i++)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargerUI;
}

CUI* CUIManager::GetFocusedUI()
{
	return nullptr;
}
