#include "stdafx.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include "data\CharactersSettings.h"
#include "Utils.h"



extern int SonicCD;
extern bool Mission;
int CDSong = 0;
extern int CustomLayout;


HelperFunctions extern help;


void Race_Init() {
	//Sonic/Eggman Race Stuff
	WriteData<1>((void*)0x47d947, 0x84); ///Load Race AI for any character and prevent Tails to race.
	WriteData<5>((void*)0x60ffab, 0x90); //Prevent Eggman AI from spawning during SH
	WriteData<5>((void*)0x415965, 0x90); //Prevent the game to load Race AI.

	WriteData<1>((void*)0x47DA01, 0x4); //prevent Casinopolis Race

	WriteCall((void*)0x4616d5, FixVictoryTailsVoice); //Prevent Tails's victory voice to play... when not Tails, lol.
	WriteCall((void*)0x4615b3, FixVictoryTailsVoice); //same
	WriteCall((void*)0x461639, FixVictoryTailsVoice);  //same

	WriteCall((void*)0x47d961, IsFastSonicAI_R); //call Fast Sonic during Custom Sonic Races.

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
