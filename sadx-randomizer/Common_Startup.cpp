#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"

extern int CustomLayout;
int GetCustomLayout;
extern bool Race;

HelperFunctions help;

NJS_TEXNAME Missions[10];
int CurrentMission = 0; //the current mission, if it's 1 then we load a lost chao in Chao.cpp

void LoadStageMissionImage_r() {

	if (GetLevelType == 0) { //do the mission check here
		//0 = capsule, 1 = Lost Chao, 2 = Emeralds Knux, 3 = Beat Sonic, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails
		if (CurrentLevel > 14 && CurrentLevel < 40)
			return;

		//GetCustomLayout = 0;
		GetCustomLayout = CustomLayout;

		if (CurrentLevel == LevelIDs_TwinkleCircuit)
			return;


		if (CurrentLevel == LevelIDs_EmeraldCoast && CurrentAct == 2)
			CurrentMission = 5;

		if (CurrentLevel == LevelIDs_LostWorld && CustomLayout == 0)
			CurrentMission = 6;

		if (CurrentLevel == LevelIDs_FinalEgg)
			if (CurrentCharacter == Characters_Amy)
				CurrentMission = 10;
			else
				CurrentMission = 4;

		if (CurrentLevel == LevelIDs_SpeedHighway)
			if (Race)
				CurrentMission = 7;
			else
				CurrentMission = 0;



		if (CurrentCharacter == Characters_Big && (GetCustomLayout != 8 && GetCustomLayout != 3))
			CurrentMission = 5;

		if (CurrentCharacter == Characters_Amy && (GetCustomLayout != 8 && GetCustomLayout != 3))
			CurrentMission = 10;
	

		if (CurrentLevel == LevelIDs_SkyDeck)
		{
			if (Race)
				CurrentMission = 3;
			else
			{
				if (GetCustomLayout == 1) //100 Rings
					CurrentMission = 8;

				if (GetCustomLayout == 2) //Lost Chao
					CurrentMission = 1;

				if (GetCustomLayout == 0) //Normal
					CurrentMission = 0;
			}
		}

		if (GetCustomLayout == 2) //100 Rings
			CurrentMission = 8;

		if (GetCustomLayout == 3) //Lost Chao
			CurrentMission = 1;
				

		StageMissionTexlist.textures = Missions;
		StageMissionTexlist.nbTexture = LengthOfArray(Missions);
		LoadPVM("textures\\Missions", &StageMissionTexlist);
		MissionSpriteAnim.texid = CurrentMission;

		ObjectMaster* obj = LoadObject(LoadObj_Data1, 6, (ObjectFuncPtr)0x457B60);
		obj->Data1->InvulnerableTime = 120;
		obj->Data1->Position.x = 320.0;
		obj->Data1->Position.y = 360.0;
		obj->DeleteSub = FreeStageMissionImage;
	}
}

void StageMissionImage_result() {

	if (GetLevelType == 0) { //do the mission check here
		//0 = capsule, 1 = Lost Chao, 2 = Beat Sonic, 3 = Emeralds Knux, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails
	

		GetCustomLayout = CustomLayout;
		
		if (CurrentLevel > 14)
			return;

		StageMissionTexlist.textures = Missions;
		StageMissionTexlist.nbTexture = LengthOfArray(Missions);
		LoadPVM("textures\\Missions", &StageMissionTexlist);
		MissionSpriteAnim.texid = CurrentMission;

		ObjectMaster* obj = LoadObject(LoadObj_Data1, 6, (ObjectFuncPtr)0x457B60);
		obj->Data1->InvulnerableTime = 120;
		obj->Data1->Position.x = 320.0;
		obj->Data1->Position.y = 240.0;
		obj->DeleteSub = FreeStageMissionImage;
	}
}

int DisplayTitleCard_r() {
	if (GetLevelType == 0) {
		return DisplayTitleCard();
	}
	else {
		if (++TitleCardCounter > TitleCardDispTime) return 1;
	}

	return 0;
}

int LoadTitleCardTexture_r(int minDispTime) {
	SoundManager_Delete2();
	dword_03b28114 = 0;
	ScreenTextureVer();
	SetFrameRateMode(1, 1);
	SetDefaultAlphaBlend();
	DisableFog();
	SetGlobalPoint2Col_Colors(0xff000000, 0xff000000, 0xff000000);
	Direct3D_SetNearFarPlanes(-1.0, -3000.0);
	TitleCardStuff = 2;
	TitleCardStuff2 = 0;

	if (CurrentLevel > 14 && CurrentLevel < 35) {
		GetLevelType = 1;
	}
	else {
		GetLevelType = 0;

		TitleCardDispTime = 180;
		if (minDispTime) {
			TitleCardDispTime = minDispTime;
		}

		LoadPVM("textures\\RandomTitleCard", &CurrentCardTexture);
		CurrentCardTexturePtr = &CurrentCardTexture;
	}

	return 1;
}

void __cdecl Startup_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	help = helperFunctions; //so we can use it everywhere

	helperFunctions.ReplaceFile("system\\AVA_GTITLE0_E.PVM", "system\\textures\\AVA_GTITLE0_E.PVM"); //replace title screen
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\3000.wma", "system\\voices\\SuperSonicTransformation.wma"); //Introduce Super Sonic voice transformation
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\3001.wma", "system\\voices\\LoadAura.wma"); //Introduce Super Sonic Aura Sound.
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\2053.wma", "system\\voices\\StageLoad.wma"); //Introduce Stage Load Sound

	helperFunctions.ReplaceFile("system\\ENDBG_SONIC_0.PVM", "system\\textures\\ENDBG_RANDOMIZER_0.pvmx"); //background credits

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4000.wma", "system\\voices\\SonicHereWeGo.wma"); //Introduce Sonic Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4001.wma", "system\\voices\\TailsLeaveItToMe.wma"); //Introduce Tails Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4002.wma", "system\\voices\\KnuxGotIt.wma"); //Introduce Knux Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4003.wma", "system\\voices\\AmyHereWeGo.wma"); //Introduce Amy Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4005.wma", "system\\voices\\EggmanSwap.wma"); //Introduce Amy Switch

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4010.wma", "system\\voices\\BigVictory.wma"); //Add Big Victory Stage voice
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4011.wma", "system\\voices\\BigWouhou.wma"); //Add Big Victory Boss / other voice
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4012.wma", "system\\voices\\EggmanYosh.wma"); //Add Eggman Victory voice

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\5000.wma", "system\\voices\\Bounce.wma"); //Introduce Sonic bounce sfx

	//help.ReplaceFile("system\\CON_REGULAR.pvm", "system\\textures\\CON_REGULAR_E.PVMX"); //Test


}