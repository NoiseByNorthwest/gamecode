/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "g_local.h"


extern gentity_t	*neutralObelisk;

static void Team_Pos_create_neutral_obelisk( gentity_t *target ) {
	gitem_t			*it;
	if (neutralObelisk) {
		return;
	}
	it = BG_FindItem("Neutral Flag");
	neutralObelisk = G_Spawn();
	VectorCopy( target->r.currentOrigin, neutralObelisk->s.origin );
	neutralObelisk->classname = it->classname;
	G_SpawnItem(neutralObelisk, it);
	FinishSpawningItem(neutralObelisk );
	Team_SetFlagStatus( TEAM_FREE, FLAG_ATBASE );
}

void Team_SpawnPosFlag( void ) {
	gentity_t	*ent = NULL;
	if (neutralObelisk) {
		return;
	}
	//First see if there is a white falg
	ent = SelectRandomEntity("team_CTF_neutralflag");
	if (!ent) {
		//If not pick a random domination point
		ent = SelectRandomEntity("domination_point");
	}
	if (!ent) {
		//Else pick a random deathmatch point
		ent = SelectRandomEntity("info_player_deathmatch");
	}
	if (!ent) {
		//If nothing found just use the first entity.
		ent = &g_entities[0];
	}
	Team_Pos_create_neutral_obelisk(ent);
}

int Team_TouchPossessionFlag (gentity_t *other) {
	gclient_t *cl = other->client;
	cl->ps.powerups[PW_NEUTRALFLAG] = INT_MAX; // flags never expire
	cl->pers.teamState.flagsince = level.time;
	return -1;
}