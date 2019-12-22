#include "stdafx.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include "data\CharactersSettings.h"
#include "Utils.h"



extern int SonicCD;
extern bool Mission;
int CDSong = 0;
int AIRace = -1;
extern int CustomLayout;
bool Race = false;
extern bool isAIActive;
extern int levelCount;
extern bool isRaceAIRandom;

extern ObjectFuncPtr charfuncs[];
HelperFunctions extern help;

void AIRaceLoad_R() {

	LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[AIRace]);
}


void CheckRace() {

	if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big)
	{
		Race = false;
		return;
	}
	else
	{
		MetalSonicRace_Init();
	
		if (isRaceAIRandom && CurrentLevel != LevelIDs_SpeedHighway)
			AIRace = randomizedSets[levelCount].ai_race;
		else
		{
			if (!CurrentCharacter && CurrentLevel != LevelIDs_SpeedHighway)
				AIRace = Characters_Tails;
			else
				AIRace = Characters_Sonic;
		}

		switch (CurrentLevel)
		{
		case LevelIDs_WindyValley:
			if (CustomLayout == 1 && CurrentAct == 2)
			{
				isAIActive = false;
				AICourse = Levels2P_WindyValley;
				Race = true;
				LoadTailsOpponent(CurrentCharacter, 1, CurrentLevel);
			}
			break;
		case LevelIDs_SpeedHighway:
			if (CustomLayout == 1 && CurrentAct == 0)
			{
				isAIActive = false;
				Race = true;
				AICourse = Levels2P_SpeedHighway;
				LoadObject((LoadObj)(LoadObj_UnknownB | LoadObj_Data1), 0, Eggman2PAI); 
				LoadObject(LoadObj_Data1, 8, MRace_EggMobile_TexlistManager);
			}
		case LevelIDs_SkyDeck:
			if (CustomLayout == 1 && CurrentAct == 0)
			{
				isAIActive = false;
				Race = true;
				AICourse = Levels2P_SkyDeck;
				LoadTailsOpponent(CurrentCharacter, 1, CurrentLevel);
			}
			break;
		case LevelIDs_Casinopolis:
			if (CustomLayout < 2 && CurrentAct == 1)
			{
				isAIActive = false;
				AICourse = Levels2P_Casinopolis;
				Race = true;
				LoadTailsOpponent(CurrentCharacter, 1, CurrentLevel);
			}
			break;
		}

		return;

	}
}


void Race_Init() {
	//Sonic/Eggman Race Stuff
	WriteData<1>((void*)0x47d947, 0x84); ///Load Race AI for any character and prevent Tails to race.
	WriteData<5>((void*)0x60ffab, 0x90); //Prevent Eggman AI from spawning during SH
	WriteData<5>((void*)0x415965, 0x90); //Prevent the game to load Race AI. (we will manually call it.)

	WriteCall((void*)0x4616d5, FixVictoryTailsVoice); //Prevent Tails's victory voice to play... when not Tails, lol.
	WriteCall((void*)0x4615b3, FixVictoryTailsVoice); //same
	WriteCall((void*)0x461639, FixVictoryTailsVoice);  //same
	
	WriteCall((void*)0x47da24, AIRaceLoad_R);  //Swap Sonic Race AI Random. (any character)


}

void MetalSonicRace_Init()
{
	//help.ReplaceFile("system\\WINDY_BACK3.pvm", "system\\textures\\final-rush-bg.pvmx"); //swap WV background by final rush one

	if (SonicCD == 0)
	{
		CDSong = rand() % 3;
	}
	else
	{
		if (SonicCD == 1)
		{
			CDSong = rand() % 2;
		}
	}

	switch (CDSong)
	{
	case 0:
		if (SonicCD == 0) //if Sonic CD JP Soundtrack version
		{
			help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\songs\\jp_cd_stardust-speedway-bad-future.wma");
			help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\songs\\jp_cd_stardust-speedway-bad-future.wma");
			
		}
		else
		{
			if (SonicCD == 1)//if Sonic CD USA Soundtrack version
			{
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\songs\\us_cd_stardust_speedway_bad_future.wma");
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\songs\\us_cd_stardust_speedway_bad_future.wma");
			}
		}
		break;
	case 1:
		if (SonicCD == 0) //if GensJP Soundtrack version
		{
			help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\songs\\jp_Gens_Stardust Speedway.wma");
			help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\songs\\jp_Gens_Stardust Speedway.wma");
		}
		else
		{
			if (SonicCD == 1)//if Gens USA Soundtrack version
			{
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\songs\\US_Gens_Stardust Speedway.wma");
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\songs\\US_Gens_Stardust Speedway.wma");
			}
		}
		break;
	case 2: //if Mania Soundtrack Version
		help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\songs\\mania_stardust_speedway-Boss.wma");
		help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\songs\\mania_stardust_speedway-Boss.wma");
		break;
	}
}

