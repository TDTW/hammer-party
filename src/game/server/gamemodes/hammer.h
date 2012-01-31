/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_GAMEMODES_HP_H
#define GAME_SERVER_GAMEMODES_HP_H
#include <game/server/gamecontroller.h>

class CGameControllerHP : public IGameController
{
public:
	CGameControllerHP(class CGameContext *pGameServer);
	virtual void OnCharacterSpawn(class CCharacter *pChr);
	virtual bool OnEntity(int Index, vec2 Pos);
	virtual void Tick();
};
#endif
