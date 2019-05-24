#if defined _cgz_included
	#endinput
#endif
#define _cgz_included


/**
	@author 	MacMailler
	@version 	0.1
*/


#define MAX_BORDERS (4)
#define MAX_CIRCLED_GANG_ZONES (100)


forward createCircledGangZone(Float:minx, Float:miny, Float:maxx, Float:maxy, Float:border_size = 2.0);
forward destroyCircledGangZone(zoneid);
forward showCircledGangZoneForAll(zoneid, color_zone, color_border = 0x000000AA);
forward hideCircledGangZoneForAll(zoneid);
forward showCircledGangZoneForPlayer(playerid, zoneid, color_zone, color_border = 0x000000AA);
forward hideCircledGangZoneForPlayer(playerid, zoneid);
forward flashCircledGangZoneForAll(zoneid, flash_color, bool:fash_border = false);
forward stopFlashCircledGangZoneForAll(zoneid);
forward flashCircledGangZoneForPlayer(playerid, zoneid, flash_color, bool:fash_border = false);
//forward stopFlashCircledGangZoneForPlayer(playerid, zoneid);


enum e_CircledGZInfo {
	CircleZone,
	CricleBorder[MAX_BORDERS]
}
static CircledGZInfo[MAX_CIRCLED_GANG_ZONES][e_CircledGZInfo];
static TotalCircledGZs;


stock createCircledGangZone(Float:minx, Float:miny, Float:maxx, Float:maxy, Float:border_size = 2.0) {
	new zoneid = INVALID_GANG_ZONE;
	
	if(++TotalCircledGZs < sizeof CircledGZInfo) {
		zoneid = TotalCircledGZs;
		CircledGZInfo[zoneid][CircleZone] = GangZoneCreate(minx, miny, maxx, maxy);
		CircledGZInfo[zoneid][CricleBorder][0] = GangZoneCreate(minx, miny - border_size, maxx, miny);
		CircledGZInfo[zoneid][CricleBorder][1] = GangZoneCreate(minx, maxy, maxx, maxy + border_size);
		CircledGZInfo[zoneid][CricleBorder][2] = GangZoneCreate(minx, miny, minx - border_size, maxy);
		CircledGZInfo[zoneid][CricleBorder][3] = GangZoneCreate(maxx, miny, maxx + border_size, maxy);
	}
	
	return zoneid;
}

stock destroyCircledGangZone(zoneid) {
	if(0 <= zoneid <= TotalCircledGZs) {
		GangZoneDestroy(CircledGZInfo[zoneid][CircleZone]);
		for(new i; i < MAX_BORDERS; GangZoneDestroy(CircledGZInfo[zoneid][CricleBorder][i]), i++) {}
		
		CircledGZInfo[zoneid][CircleZone] = CircledGZInfo[--TotalCircledGZs][CircleZone];
		for(new i; i < MAX_BORDERS; CircledGZInfo[zoneid][CricleBorder][i] = CircledGZInfo[TotalCircledGZs][CircleZone], i++) {}
	}
	return 1;
}

stock showCircledGangZoneForAll(zoneid, color_zone, color_border = 0x000000AA) {
	if(0 <= zoneid <= TotalCircledGZs) {
		GangZoneShowForAll(CircledGZInfo[zoneid][CircleZone], color_zone);
		for(new i; i < MAX_BORDERS; GangZoneShowForAll(CircledGZInfo[zoneid][CricleBorder][i], color_border), i++) {}
	}
	return 1;
}

stock hideCircledGangZoneForAll(zoneid) {
	if(0 <= zoneid <= TotalCircledGZs) {
		GangZoneHideForAll(CircledGZInfo[zoneid][CircleZone]);
		for(new i; i < MAX_BORDERS; GangZoneHideForAll(CircledGZInfo[zoneid][CricleBorder][i]), i++) {}
	}
	return 1;
}

stock showCircledGangZoneForPlayer(playerid, zoneid, color_zone, color_border = 0x000000AA) {
	if(0 <= playerid < MAX_PLAYERS) {
		if(0 <= zoneid <= TotalCircledGZs) {
			GangZoneShowForPlayer(playerid, CircledGZInfo[zoneid][CircleZone], color_zone);
			for(new i; i < MAX_BORDERS; GangZoneShowForPlayer(playerid, CircledGZInfo[zoneid][CricleBorder][i], color_border), i++) {}
		}
	}
	return 1;
}

stock hideCircledGangZoneForPlayer(playerid, zoneid) {
	if(0 <= playerid < MAX_PLAYERS) {
		if(0 <= zoneid <= TotalCircledGZs) {
			GangZoneHideForPlayer(playerid, CircledGZInfo[zoneid][CircleZone], color_zone);
			for(new i; i < MAX_BORDERS; GangZoneHideForPlayer(playerid, CircledGZInfo[zoneid][CricleBorder][i], color_border), i++) {}
		}
	}
	return 1;
}

stock flashCircledGangZoneForAll(zoneid, flash_color, bool:fash_border = false) {
	if(0 <= zoneid <= TotalCircledGZs) {
		GangZoneFlashForAll(CircledGZInfo[zoneid][CircleZone], flash_color);
		if(fash_border) {
			for(new i; i < MAX_BORDERS; GangZoneFlashForAll(CircledGZInfo[zoneid][CricleBorder][i], flash_color), i++) {}
		}
	}
	return 1;
}

stock flashCircledGangZoneForPlayer(playerid, zoneid, flash_color, bool:fash_border = false) {
	if(0 <= playerid < MAX_PLAYERS) {
		if(0 <= zoneid <= TotalCircledGZs) {
			GangZoneFlashForPlayer(playerid, CircledGZInfo[zoneid][CircleZone], flash_color);
			if(fash_border) {
				for(new i; i < MAX_BORDERS; GangZoneHideForPlayer(playerid, CircledGZInfo[zoneid][CricleBorder][i], flash_color), i++) {}
			}
		}
	}
	return 1;
}

stock stopFalshCircledGangZoneForAll(zoneid) {
	if(0 <= zoneid <= TotalCircledGZs) {
		GangZoneStopFlashForAll(CircledGZInfo[zoneid][CircleZone]);
		for(new i; i < MAX_BORDERS; GangZoneStopFlashForAll(CircledGZInfo[zoneid][CricleBorder][i]), i++) {}
	}
	return 1;
}
/*
stock stopFalshCircledGangZoneForPlayer(playerid, zoneid) {
	if(0 <= playerid < MAX_PLAYERS) {
		if(0 <= zoneid <= TotalCircledGZs) {
			GangZoneStopFlashForPlayer(playerid, CircledGZInfo[zoneid][CircleZone]);
			for(new i; i < MAX_BORDERS; GangZoneStopFlashForPlayer(playerid, CircledGZInfo[zoneid][CricleBorder][i]), i++) {}
		}
	}
	return 1;
}*/