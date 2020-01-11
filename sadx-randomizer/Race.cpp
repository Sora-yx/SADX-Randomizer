#include "stdafx.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include "data\CharactersSettings.h"
#include "Utils.h"


extern int SonicCD;
extern bool Mission;
int CDSong = 0;
int AIRace = -1;
extern bool isAIActive;
extern int levelCount;
bool Race = false;
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
		
		if (CurrentLevel != LevelIDs_SpeedHighway)
		{
			AIRace = randomizedSets[levelCount].ai_race;

			if (AIRace == CurrentCharacter) //prevent crash
			{
				if (CurrentCharacter == Characters_Sonic)
					AIRace = Characters_Tails;
				else
					AIRace = Characters_Sonic;
			}
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
				LoadObject(LoadObj_Data1, 8, MRace_EggMobile_TexlistManager);
				LoadTailsOpponent(CurrentCharacter, 1, CurrentLevel);
			}
			break;
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



void SongRace_Init()
{
	WriteCall((void*)0x61caad, PlayRace_Music); 

	if (SonicCD == 0) //pick a random song depending
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
			help.ReplaceFile("system\\sounddata\\bgm\\wma\\casino2.wma", "system\\songs\\jp_cd_stardust-speedway-bad-future.wma");
		}
		else
		{
			if (SonicCD == 1)//if Sonic CD USA Soundtrack version
			{
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\songs\\us_cd_stardust_speedway_bad_future.wma");
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\songs\\us_cd_stardust_speedway_bad_future.wma");
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\casino2.wma", "system\\songs\\us_cd_stardust_speedway_bad_future.wma");
			}
		}
		break;
	case 1:
		if (SonicCD == 0) //if GensJP Soundtrack version
		{
			help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\songs\\jp_Gens_Stardust Speedway.wma");
			help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\songs\\jp_Gens_Stardust Speedway.wma");
			help.ReplaceFile("system\\sounddata\\bgm\\wma\\casino2.wma", "system\\songs\\jp_Gens_Stardust Speedway.wma");
		}
		else
		{
			if (SonicCD == 1)//if Gens USA Soundtrack version
			{
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\songs\\US_Gens_Stardust Speedway.wma");
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\songs\\US_Gens_Stardust Speedway.wma");
				help.ReplaceFile("system\\sounddata\\bgm\\wma\\casino2.wma", "system\\songs\\US_Gens_Stardust Speedway.wma");
			}
		}
		break;
	case 2: //if Mania Soundtrack Version
		help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\songs\\mania_stardust_speedway-Boss.wma");
		help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\songs\\mania_stardust_speedway-Boss.wma");
		help.ReplaceFile("system\\sounddata\\bgm\\wma\\casino2.wma", "system\\songs\\mania_stardust_speedway-Boss.wma");
		break;
	}


}

void PlayRace_Music() {

	switch (CurrentLevel)
	{
	case LevelIDs_WindyValley:
		return PlayMusic_R(MusicIDs_WindyValleyWindyHill);
		break;
	case LevelIDs_Casinopolis:
		return PlayMusic_R(MusicIDs_CasinopolisDilapidatedWay);
		break;
	case LevelIDs_SkyDeck:
		return PlayMusic_R(MusicIDs_SkyDeckSkydeckAGoGo);
		break;
	}

	return PlayMusic((MusicIDs)CurrentSong);
}

void Reset_OriginalMusic() {

	//Restore original songs
	help.ReplaceFile("system\\sounddata\\bgm\\wma\\wndyvly3.wma", "system\\sounddata\\bgm\\wma\\wndyvly3.wma");
	help.ReplaceFile("system\\sounddata\\bgm\\wma\\skydeck1.wma", "system\\sounddata\\bgm\\wma\\skydeck1.wma");
	help.ReplaceFile("system\\sounddata\\bgm\\wma\\casino2.wma", "system\\sounddata\\bgm\\wma\\casino2.wma");

	if (RNGMusic)
		WriteCall((void*)0x61caad, RandomMusic);
	else
		WriteCall((void*)0x61caad, PlayMusic);
}
