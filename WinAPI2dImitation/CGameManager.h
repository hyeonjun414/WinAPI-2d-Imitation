#pragma once

#include "CGameObject.h"

class CGameManager
{
	SINGLETON(CGameManager);
private:
	CGameObject* m_pPlayer;

public:
	void			SetPlayer(CGameObject* player);
	CGameObject*	GetPlayer();

	void			Init();
};

