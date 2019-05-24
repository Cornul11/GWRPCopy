#if defined _chatbox_included
	#endinput
#endif
#define _chatbox_included

#define MAX_CHATBOX			(1)
#define MAX_CHATBOX_STR		(24)
#define MAX_CHATBOX_LINES	(10)
#define INVALID_CHATBOX_ID	(-1)

#define ValidChatBox<%0>		((%0>=0&&%0<MAX_CHATBOX)&&MaxChatBoxs>0)
#define ValidChatBoxLine<%0>	(%0>=0&&%0<MAX_CHATBOX_LINES)
#define swap(%0,%1)				%0^=%1,%1^=%0,%0^=%1

forward ChatBox_Create(textcolor, mb=153, lb=731, rb=731, ub=731, db=731);
forward ChatBox_Clear(chatboxid);
forward ChatBox_Destroy(chatboxid);
forward ChatBox_ShowForAll(chatboxid);
forward ChatBox_HideForAll(chatboxid);
forward ChatBox_ShowForPlayer(chatboxid, playerid);
forward ChatBox_HideForPlayer(chatboxid, playerid);
forward ChatBox_Send(chatboxid, color, const text[]);
forward ChatBox_SetLine(chatboxid, line, color, const text[]);

enum e_ChatBox {
	Text:Main_Box,
	Text:Border_Left,
	Text:Border_Right,
	Text:Border_Up,
	Text:Border_Down,
	e_TextColor[MAX_CHATBOX_LINES],
	Text:e_TextId[MAX_CHATBOX_LINES],
	e_TextShow[MAX_PLAYERS]
}
static
	MaxChatBoxs,
	ChatBox[MAX_CHATBOX][e_ChatBox],
	ChatBox_Lines[MAX_CHATBOX][MAX_CHATBOX_LINES][MAX_CHATBOX_STR]
;

stock ChatBox_Create(textcolor, mb=153, lb=731, rb=731, ub=731, db=731) {
	if(MaxChatBoxs < MAX_CHATBOX) {
		new chatboxid = MaxChatBoxs++;
		ChatBox[chatboxid][Main_Box] = TextDrawCreate(620.000000, 140.000000, "_");
		TextDrawBackgroundColor(ChatBox[chatboxid][Main_Box], 255);
		TextDrawFont(ChatBox[chatboxid][Main_Box], 1);
		TextDrawLetterSize(ChatBox[chatboxid][Main_Box], 0.529999, 16.200025);
		TextDrawColor(ChatBox[chatboxid][Main_Box], 34);
		TextDrawSetOutline(ChatBox[chatboxid][Main_Box], 0);
		TextDrawSetProportional(ChatBox[chatboxid][Main_Box], 1);
		TextDrawSetShadow(ChatBox[chatboxid][Main_Box], 1);
		TextDrawUseBox(ChatBox[chatboxid][Main_Box], 1);
		TextDrawBoxColor(ChatBox[chatboxid][Main_Box], mb);
		TextDrawTextSize(ChatBox[chatboxid][Main_Box], 466.000000, 0.000000);
		
		ChatBox[chatboxid][Border_Left] = TextDrawCreate(470.000000, 140.000000, "_");
		TextDrawBackgroundColor(ChatBox[chatboxid][Border_Left], 255);
		TextDrawFont(ChatBox[chatboxid][Border_Left], 1);
		TextDrawLetterSize(ChatBox[chatboxid][Border_Left], 0.529999, 16.200025);
		TextDrawColor(ChatBox[chatboxid][Border_Left], -16776961);
		TextDrawSetOutline(ChatBox[chatboxid][Border_Left], 0);
		TextDrawSetProportional(ChatBox[chatboxid][Border_Left], 1);
		TextDrawSetShadow(ChatBox[chatboxid][Border_Left], 1);
		TextDrawUseBox(ChatBox[chatboxid][Border_Left], 1);
		TextDrawBoxColor(ChatBox[chatboxid][Border_Left], lb);
		TextDrawTextSize(ChatBox[chatboxid][Border_Left], 466.000000, 0.000000);
		
		ChatBox[chatboxid][Border_Right] = TextDrawCreate(620.000000, 140.000000, "_");
		TextDrawBackgroundColor(ChatBox[chatboxid][Border_Right], 255);
		TextDrawFont(ChatBox[chatboxid][Border_Right], 1);
		TextDrawLetterSize(ChatBox[chatboxid][Border_Right], 0.529999, 16.200025);
		TextDrawColor(ChatBox[chatboxid][Border_Right], 34);
		TextDrawSetOutline(ChatBox[chatboxid][Border_Right], 0);
		TextDrawSetProportional(ChatBox[chatboxid][Border_Right], 1);
		TextDrawSetShadow(ChatBox[chatboxid][Border_Right], 1);
		TextDrawUseBox(ChatBox[chatboxid][Border_Right], 1);
		TextDrawBoxColor(ChatBox[chatboxid][Border_Right], rb);
		TextDrawTextSize(ChatBox[chatboxid][Border_Right], 615.000000, 0.000000);
		
		ChatBox[chatboxid][Border_Up] = TextDrawCreate(620.000000, 140.000000, "_");
		TextDrawBackgroundColor(ChatBox[chatboxid][Border_Up], 255);
		TextDrawFont(ChatBox[chatboxid][Border_Up], 1);
		TextDrawLetterSize(ChatBox[chatboxid][Border_Up], 0.529999, -0.199999);
		TextDrawColor(ChatBox[chatboxid][Border_Up], 34);
		TextDrawSetOutline(ChatBox[chatboxid][Border_Up], 0);
		TextDrawSetProportional(ChatBox[chatboxid][Border_Up], 1);
		TextDrawSetShadow(ChatBox[chatboxid][Border_Up], 1);
		TextDrawUseBox(ChatBox[chatboxid][Border_Up], 1);
		TextDrawBoxColor(ChatBox[chatboxid][Border_Up], ub);
		TextDrawTextSize(ChatBox[chatboxid][Border_Up], 466.000000, 0.000000);
		
		ChatBox[chatboxid][Border_Down] = TextDrawCreate(620.000000, 287.000000, "_");
		TextDrawBackgroundColor(ChatBox[chatboxid][Border_Down], 255);
		TextDrawFont(ChatBox[chatboxid][Border_Down], 1);
		TextDrawLetterSize(ChatBox[chatboxid][Border_Down], 0.529999, -0.199999);
		TextDrawColor(ChatBox[chatboxid][Border_Down], 34);
		TextDrawSetOutline(ChatBox[chatboxid][Border_Down], 0);
		TextDrawSetProportional(ChatBox[chatboxid][Border_Down], 1);
		TextDrawSetShadow(ChatBox[chatboxid][Border_Down], 1);
		TextDrawUseBox(ChatBox[chatboxid][Border_Down], 1);
		TextDrawBoxColor(ChatBox[chatboxid][Border_Down], db);
		TextDrawTextSize(ChatBox[chatboxid][Border_Down], 466.000000, 0.000000);

		for(new Float:offset=145.0, line; line < MAX_CHATBOX_LINES; line++, offset+=13.0) {
			strmid(ChatBox_Lines[chatboxid][line], "_", 0, 1, MAX_CHATBOX_STR);
			ChatBox[chatboxid][e_TextId][line] = TextDrawCreate(545.000000, offset, ChatBox_Lines[chatboxid][line]);
			TextDrawAlignment(ChatBox[chatboxid][e_TextId][line], 2);
			TextDrawBackgroundColor(ChatBox[chatboxid][e_TextId][line], 255);
			TextDrawFont(ChatBox[chatboxid][e_TextId][line], 3);
			TextDrawLetterSize(ChatBox[chatboxid][e_TextId][line], 0.379999, 1.399999);
			TextDrawColor(ChatBox[chatboxid][e_TextId][line], textcolor);
			TextDrawSetOutline(ChatBox[chatboxid][e_TextId][line], 0);
			TextDrawSetProportional(ChatBox[chatboxid][e_TextId][line], 1);
			TextDrawSetShadow(ChatBox[chatboxid][e_TextId][line], 1);
		}
		return chatboxid;
	}
	return INVALID_CHATBOX_ID;
}

stock ChatBox_Destroy(chatboxid) {
	MaxChatBoxs--;
	TextDrawHideForAll(ChatBox[chatboxid][Main_Box]), TextDrawDestroy(ChatBox[chatboxid][Main_Box]);
	TextDrawHideForAll(ChatBox[chatboxid][Border_Left]), TextDrawDestroy(ChatBox[chatboxid][Border_Left]);
	TextDrawHideForAll(ChatBox[chatboxid][Border_Right]), TextDrawDestroy(ChatBox[chatboxid][Border_Right]);
	TextDrawHideForAll(ChatBox[chatboxid][Border_Up]), TextDrawDestroy(ChatBox[chatboxid][Border_Up]);
	TextDrawHideForAll(ChatBox[chatboxid][Border_Down]), TextDrawDestroy(ChatBox[chatboxid][Border_Down]);
	for(new line; line < MAX_CHATBOX_LINES; line++) {
		swap(ChatBox[chatboxid][e_TextColor][line], ChatBox[chatboxid][e_TextColor][MaxChatBoxs]);
		strmid(ChatBox_Lines[chatboxid][line], ChatBox_Lines[chatboxid][MaxChatBoxs], 0, strlen(ChatBox_Lines[chatboxid][MaxChatBoxs]), MAX_CHATBOX_STR);
		TextDrawHideForAll(ChatBox[chatboxid][e_TextId][line]), TextDrawDestroy(ChatBox[chatboxid][e_TextId][line]);
	}
	swap(ChatBox[chatboxid][Main_Box], ChatBox[MaxChatBoxs][Main_Box]);
	swap(ChatBox[chatboxid][Border_Left], ChatBox[MaxChatBoxs][Border_Left]);
	swap(ChatBox[chatboxid][Border_Right], ChatBox[MaxChatBoxs][Border_Right]);
	swap(ChatBox[chatboxid][Border_Up], ChatBox[MaxChatBoxs][Border_Up]);
	swap(ChatBox[chatboxid][Border_Down], ChatBox[MaxChatBoxs][Border_Down]);
	foreach(new playerid : Player) {
		ChatBox[chatboxid][e_TextShow][playerid] = 0;
	}
	return 1;
}

stock ChatBox_ShowForAll(chatboxid) {
	if(ValidChatBox<chatboxid>) {
		TextDrawShowForAll(ChatBox[chatboxid][Main_Box]);
		TextDrawShowForAll(ChatBox[chatboxid][Border_Left]);
		TextDrawShowForAll(ChatBox[chatboxid][Border_Right]);
		TextDrawShowForAll(ChatBox[chatboxid][Border_Up]);
		TextDrawShowForAll(ChatBox[chatboxid][Border_Down]);
		for(new line; line < MAX_CHATBOX_LINES; line++) {
			TextDrawShowForAll(ChatBox[chatboxid][e_TextId][line]);
		}
		foreach(new playerid : Player) {
			ChatBox[chatboxid][e_TextShow][playerid] = 1;
		}
	}
	return 1;
}

stock ChatBox_HideForAll(chatboxid) {
	if(ValidChatBox<chatboxid>) {
		TextDrawHideForAll(ChatBox[chatboxid][Main_Box]);
		TextDrawHideForAll(ChatBox[chatboxid][Border_Left]);
		TextDrawHideForAll(ChatBox[chatboxid][Border_Right]);
		TextDrawHideForAll(ChatBox[chatboxid][Border_Up]);
		TextDrawHideForAll(ChatBox[chatboxid][Border_Down]);
		for(new line; line < MAX_CHATBOX_LINES; line++) {
			TextDrawHideForAll(ChatBox[chatboxid][e_TextId][line]);
		}
		foreach(new playerid : Player) {
			ChatBox[chatboxid][e_TextShow][playerid] = 0;
		}
	}
	return 1
}

stock ChatBox_ShowForPlayer(chatboxid, playerid) {
	if(ValidChatBox<chatboxid>) {
		ChatBox[chatboxid][e_TextShow][playerid] = 1;
		TextDrawShowForPlayer(playerid, ChatBox[chatboxid][Main_Box]);
		TextDrawShowForPlayer(playerid, ChatBox[chatboxid][Border_Left]);
		TextDrawShowForPlayer(playerid, ChatBox[chatboxid][Border_Right]);
		TextDrawShowForPlayer(playerid, ChatBox[chatboxid][Border_Up]);
		TextDrawShowForPlayer(playerid, ChatBox[chatboxid][Border_Down]);
		for(new line; line < MAX_CHATBOX_LINES; line++) {
			TextDrawShowForPlayer(playerid, ChatBox[chatboxid][e_TextId][line]);
		}
	}
	return 1;
}

stock ChatBox_HideForPlayer(chatboxid, playerid) {
	if(ValidChatBox<chatboxid>) {
		ChatBox[chatboxid][e_TextShow][playerid] = 0;
		TextDrawHideForPlayer(playerid, ChatBox[chatboxid][Main_Box]);
		TextDrawHideForPlayer(playerid, ChatBox[chatboxid][Border_Left]);
		TextDrawHideForPlayer(playerid, ChatBox[chatboxid][Border_Right]);
		TextDrawHideForPlayer(playerid, ChatBox[chatboxid][Border_Up]);
		TextDrawHideForPlayer(playerid, ChatBox[chatboxid][Border_Down]);
		for(new line; line < MAX_CHATBOX_LINES; line++) {
			TextDrawHideForPlayer(playerid, ChatBox[chatboxid][e_TextId][line]);
		}
	}
	return 1;
}

stock ChatBox_Send(chatboxid, color, const text[]) {
	if(ValidChatBox<chatboxid>) {
		for(new line; line < MAX_CHATBOX_LINES; line++) {
			TextDrawHideForAll(ChatBox[chatboxid][e_TextId][line]);
			if(line < MAX_CHATBOX_LINES-1) {
				swap(ChatBox[chatboxid][e_TextId][line], ChatBox[chatboxid][e_TextId][line+1]);
				swap(ChatBox[chatboxid][e_TextColor][line], ChatBox[chatboxid][e_TextColor][line+1]);
				strmid(ChatBox_Lines[chatboxid][line], ChatBox_Lines[chatboxid][line+1], 0, strlen(ChatBox_Lines[chatboxid][line+1]), MAX_CHATBOX_STR);
			}
		}
		ChatBox[chatboxid][e_TextColor][MAX_CHATBOX_LINES-1] = color;
		strmid(ChatBox_Lines[chatboxid][MAX_CHATBOX_LINES-1], text, 0, strlen(text), MAX_CHATBOX_STR);
		TextDrawColor(ChatBox[chatboxid][e_TextId][MAX_CHATBOX_LINES-1], color);
		TextDrawSetString(ChatBox[chatboxid][e_TextId][MAX_CHATBOX_LINES-1], ChatBox_Lines[chatboxid][MAX_CHATBOX_LINES-1]);
		foreach(new playerid : Player) {
			if(ChatBox[chatboxid][e_TextShow][playerid]) {
				for(new line; line < MAX_CHATBOX_LINES; line++) {
					TextDrawShowForPlayer(playerid, ChatBox[chatboxid][e_TextId][line]);
				}
			}
		}
	}
	return 1;
}

stock ChatBox_SetLine(chatboxid, line, color, const text[]) {
	if(ValidChatBox<chatboxid>) {
		if(ValidChatBoxLine<line>) {
			ChatBox[chatboxid][e_TextColor][line] = color;
			strmid(ChatBox_Lines[chatboxid][line], text, 0, strlen(text), MAX_CHATBOX_STR);
			TextDrawColor(ChatBox[chatboxid][e_TextId][line], ChatBox[chatboxid][e_TextColor][line]);
			TextDrawSetString(ChatBox[chatboxid][e_TextId]line], ChatBox_Lines[chatboxid][line]);
		}
	}
	return 1;
}

stock ChatBox_Clear(chatboxid) {
	if(ValidChatBox<chatboxid>) {
		for(new line; line < MAX_CHATBOX_LINES; line++) {
			ChatBox[chatboxid][e_TextColor][line] = -1;
			strmid(ChatBox_Lines[chatboxid][line], "_", 0, 1, MAX_CHATBOX_STR);
			TextDrawSetString(ChatBox[chatboxid][e_TextId][line], ChatBox_Lines[chatboxid][line]);
		}
	}
	return 1;
}

stock ChatBox_Aligment(chatboxid, alignid) {
	if(align >= 0 && align <= 4) {
		for(new line; line < MAX_CHATBOX_LINES; line++) {
			TextDrawAlignment(ChatBox[chatboxid][e_TextId][line], align);
		}
	}
	return 1;
}

stock ChatBox_Font(chatboxid, fontid) {
	
}


stock TextDrawConvertText(dest[]) {
	static const encode[256 char] = { 
		66051,67438087,134810123,202182159,269554195,336926231,404298267,471670303, 
		539042339,606414375,673799467,741158447,808530483,875902519,943274555,1010646591, 
		1078018627,1145390663,1212762699,1280134735,1347506771,1414878807,1482250843,1549622879, 
		1616994915,1684366951,1751738987,1819111023,1886483059,1953855095,2021227131,2088599167, 
		-2138996093,-2071624057,-2004252021,-1936879985,-1869507949,-1802135913,-1734763877,-1667391841, 
		-1600019805,-1532647769,1168747179,-1397903697,-1330531661,-1263159625,1706670779,-1128415553, 
		1098943362,-2092596088,-2054796409,1296584588,1346604889,-2124904051,-1903521647,-1835821931, 
		1637327513,-1704617057,-1667404898,-1347522653,1885578873,-1736925020,-1516132440,-1448432724
	}; 
	for(new i = strlen(dest)-1; i != -1; i--) {
		if(dest[i] < 256) {
			dest[i] = encode{dest[i]};
		}
	}
}