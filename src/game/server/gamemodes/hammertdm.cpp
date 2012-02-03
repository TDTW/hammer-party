/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "hammertdm.h"
#include "../gamecontext.h"
#include <engine/shared/config.h>
#include <game/generated/protocol.h>
#include <game/mapitems.h>


CGameControllerHPT::CGameControllerHPT(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_pGameType = "HParty";
	m_GameFlags = GAMEFLAG_TEAMS;
}

void CGameControllerHPT::Tick()
{
	IGameController::Tick();
}

void CGameControllerHPT::OnCharacterSpawn(class CCharacter *pChr)
{
	// default health
	pChr->IncreaseHealth(10);

	// give default weapons
	pChr->GiveWeapon(WEAPON_HAMMER, -1);
}

bool CGameControllerHPT::OnEntity(int Index, vec2 Pos)
{
	int Type = -1;
	int SubType = 0;

	switch(Index)
	{
		case ENTITY_SPAWN:
		case ENTITY_SPAWN_RED:
		case ENTITY_SPAWN_BLUE:
			IGameController::OnEntity(Index, Pos);
		break;
	}
	return false;		
}

int CGameControllerHPT::OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon)
{
	IGameController::OnCharacterDeath(pVictim, pKiller, Weapon);


	if(Weapon != WEAPON_GAME)
	{
		// do team scoring
		if(pKiller == pVictim->GetPlayer() || pKiller->GetTeam() == pVictim->GetPlayer()->GetTeam())
			m_aTeamscore[pKiller->GetTeam()&1]--; // klant arschel
		else
			m_aTeamscore[pKiller->GetTeam()&1]++; // good shit
	}

	pVictim->GetPlayer()->m_RespawnTick = max(pVictim->GetPlayer()->m_RespawnTick, Server()->Tick()+Server()->TickSpeed()*g_Config.m_SvRespawnDelayTDM);

	return 0;
}

void CGameControllerHPT::Snap(int SnappingClient)
{
	IGameController::Snap(SnappingClient);

	CNetObj_GameData *pGameDataObj = (CNetObj_GameData *)Server()->SnapNewItem(NETOBJTYPE_GAMEDATA, 0, sizeof(CNetObj_GameData));
	if(!pGameDataObj)
		return;

	pGameDataObj->m_TeamscoreRed = m_aTeamscore[TEAM_RED];
	pGameDataObj->m_TeamscoreBlue = m_aTeamscore[TEAM_BLUE];

	pGameDataObj->m_FlagCarrierRed = 0;
	pGameDataObj->m_FlagCarrierBlue = 0;
}
