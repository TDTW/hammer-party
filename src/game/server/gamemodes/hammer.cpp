/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "hammer.h"
#include "../gamecontext.h"
#include <engine/shared/config.h>
#include <game/generated/protocol.h>
#include <game/mapitems.h>


CGameControllerHP::CGameControllerHP(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_pGameType = "HParty";
}

void CGameControllerHP::Tick()
{
	IGameController::Tick();
}

void CGameControllerHP::OnCharacterSpawn(class CCharacter *pChr)
{
	// default health
	pChr->IncreaseHealth(10);

	// give default weapons
	pChr->GiveWeapon(WEAPON_HAMMER, -1);
}

bool CGameControllerHP::OnEntity(int Index, vec2 Pos)
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