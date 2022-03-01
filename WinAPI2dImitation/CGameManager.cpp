#include "framework.h"
#include "CGameManager.h"

CGameManager::CGameManager()
{

}
CGameManager::~CGameManager()
{

}

void CGameManager::Init()
{
    m_pPlayer = nullptr;
    m_DebugMode = false;
}
