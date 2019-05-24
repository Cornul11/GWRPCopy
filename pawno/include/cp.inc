#if defined _cp_included
	#endinput
#endif
#define _cp_included

#define MAX_CPs				(100)
#define INVALID_DYNAMIC_CP	(-1)

forward OnPlayerCP(playerid, cpid, el);


enum cpInfo {
	cpIcon,
	cpArea
};
static CPInfo[MAX_CPs][cpInfo];
static TotalCPs;


stock CreateLocalCP(Float:x, Float:y, Float:z, world=-1, player=-1, interior=-1, Float:streamdist=300.0) {
	if(TotalCPs < MAX_CPs) {
		new cpid = ++TotalCPs;
		CPInfo[cpid][cpIcon] = CreateDynamicMapIcon(x, y, z, 1, 0xff0000aa, world, interior, player, streamdist);
		CPInfo[cpid][cpArea] = CreateDynamicSphere(x, y, z, 3.0, world, interior, player);
		Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, CPInfo[cpid][cpIcon], E_STREAMER_STYLE, 2);
		return cpid;
	}
	return INVALID_DYNAMIC_CP;
}

stock CreateGlobalCP(Float:x, Float:y, Float:z, world=-1, player=-1, interior=-1) {
	if(TotalCPs < MAX_CPs) {
		new cpid = ++TotalCPs;
		CPInfo[cpid][cpIcon] = CreateDynamicMapIcon(x, y, z, 1, 0xff0000aa, world, interior, player, 1.0);
		CPInfo[cpid][cpArea] = CreateDynamicSphere(x, y, z, 3.0, world, interior, player);
		Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, CPInfo[cpid][cpIcon], E_STREAMER_STYLE, 3);
		Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, CPInfo[cpid][cpIcon], E_STREAMER_STREAM_DISTANCE, 99999.9);
		return cpid;
	}
	return INVALID_DYNAMIC_CP;
}

stock DestroyCP(cpid) {
	if(ValidCP(cpid)) {
		TotalCPs --;
		DestroyDynamicMapIcon(CPInfo[cpid][cpIcon]);
		DestroyDynamicArea(CPInfo[cpid][cpArea]);
		CPInfo[cpid][cpIcon] = CPInfo[TotalCPs][cpIcon];
		CPInfo[cpid][cpArea] = CPInfo[TotalCPs][cpArea];
	}
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, areaid) {
	for(new cpid; cpid < TotalCPs; cpid++) {
		if(CPInfo[cpid][cpArea] == areaid) {
			CallLocalFunction("OnPlayerCP", "iii", playerid, cpid, 1);
			break;
		}
	}
	return CallLocalFunction("OnPlayerEnterDynamicArea", "ii", playerid, areaid);
}

public OnPlayerLeaveDynamicArea(playerid, areaid) {
	for(new cpid; cpid < TotalCPs; cpid++) {
		if(CPInfo[cpid][cpArea] == areaid) {
			CallLocalFunction("OnPlayerCP", "iii", playerid, cpid, 0);
			break;
		}
	}
	return CallLocalFunction("OnPlayerEnterDynamicArea", "ii", playerid, areaid);
}

/// Hooks
#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea cp_OnPlayerEnterDynamicArea
forward cp_OnPlayerEnterDynamicArea(playerid, areaid);


#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea cp_OnPlayerLeaveDynamicArea
forward cp_OnPlayerLeaveDynamicArea(playerid, areaid);