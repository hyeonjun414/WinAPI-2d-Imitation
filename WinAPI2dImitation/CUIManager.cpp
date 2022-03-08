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
				if (pUI->m_bLbtnDown) // ������ �ִ� ��Ȳ
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
	// Ŭ���ϴ� UI�� ���ϴ� UI�� �θ����� �ϴ� �Լ� -> ��ȸ�Ͽ� Ž���ؾ���.
	list<CUI*> queue;
	vector<CUI*>	vecNoneTarget;

	CUI* pTargerUI = nullptr;
	queue.push_back(_pParentUI); // �θ� �켱 Ž��

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
			// ���ʿ� ���콺�� �ȿö󰬴� UI�� ��Ÿ������ ����
			vecNoneTarget.push_back(pUI);
		}
		const vector<CUI*> vecChild = pUI->GetChild();
		for (size_t i = 0; i < vecChild.size(); i++)
		{
			queue.push_back(vecChild[i]);
		}
	}

	// ��Ÿ�� UI��  ���콺�� �ȿö󰣰����� ����
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
