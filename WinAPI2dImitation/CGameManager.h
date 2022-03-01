#pragma once

#include "CPlayer.h"

class CGameManager
{
	SINGLETON(CGameManager);
private:
	CPlayer*	m_pPlayer;
	bool		m_DebugMode;

public:
	void			SetPlayer(CPlayer* player) {m_pPlayer = player;}
	void			SetDebugMode() { m_DebugMode = !m_DebugMode; }

	CPlayer*		GetPlayer()		{ return m_pPlayer; }
	bool			GetDebugMode()	{ return m_DebugMode; }
	

	void			Init();
};

