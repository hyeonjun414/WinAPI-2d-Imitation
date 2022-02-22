#include "framework.h"
#include "CGameManager.h"

CGameManager::CGameManager()
{

}
CGameManager::~CGameManager()
{

}

void CGameManager::SetPlayer(CGameObject* player)
{
    m_pPlayer = player;
}

CGameObject* CGameManager::GetPlayer()
{
    return m_pPlayer;
}

void CGameManager::Init()
{
    m_pPlayer = nullptr;
}
