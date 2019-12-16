#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"

extern int CustomLayout;
int GetCustomLayout;
extern bool Race;

HelperFunctions help;

NJS_TEXNAME Missions[10];
int CurrentMission = 0; //the current mission, if it's 1 then we load a lost chao in Chao.cpp

void Set_MusicVoices() {

	extern bool RNGVoices;
	extern bool RNGMusic;

	//if Random Voice option
	if (RNGVoices)
	{
		WriteCall((void*)0x42571d, RandomVoice);
	}

	//if Random Music option
	if (RNGMusic)
	{
		WriteCall((void*)0x425699, RandomMusic); //hook PlayMusic (Stages...)
		WriteCall((void*)0x51b94a, RandomMusic); //hook playmusic (Hub World part 1)
		WriteCall((void*)0x62ec81, RandomMusic); //hook playmusic (Hub World, bosses part 2) 

		WriteCall((void*)0x441dd8, RandomMusic); //hook speed shoes sound
		WriteCall((void*)0x4d6daf, RandomMusic); //hook invincibility music

		WriteCall((void*)0x59a4ba, RandomMusic); //hook hot shelter music.
		WriteCall((void*)0x59a215, RandomMusic); //hook hot shelter music part 2.
		WriteCall((void*)0x59a258, RandomMusic); //hook hot shelter music part 3
		WriteCall((void*)0x59a239, RandomMusic); //hook hot shelter music part 4
		WriteCall((void*)0x59a107, RandomMusic); //hook hot shelter music part 5
		WriteCall((void*)0x59a157, RandomMusic); //hook hot shelter music part 6
		WriteCall((void*)0x59a177, RandomMusic); //hook hot shelter music part 7
		WriteCall((void*)0x59a197, RandomMusic); //hook hot shelter music part 8

		WriteCall((void*)0x5adda7, RandomMusic); //Final Egg Song
		WriteCall((void*)0x5ae144, RandomMusic); //Final Egg Song act 2
		WriteCall((void*)0x5adf85, RandomMusic); //Final Egg Song act 3

		WriteCall((void*)0x79e4e8, RandomMusic); //Sand Hill
		WriteCall((void*)0x54a60d, RandomMusic); //Chaos 2
	}
}

int CheckMissionRequirements_r() {

	GetCustomLayout = CustomLayout;

	if (CurrentLevel > 14)
		return 0;

		if (GetCustomLayout == 2) //100 Rings check
			return (int)(99 < (short)Rings);
			
		if (GetCustomLayout == 3) //Lost Chao
			return 1;

		return 1;

}

void LoadStageMissionImage_r() {

	GetCustomLayout = 0;
	CurrentMission = 0;

	if (GetLevelType == 0) { //do the mission check here
		//0 = capsule, 1 = Lost Chao, 2 = Emeralds Knux, 3 = Beat Sonic, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails
		if (CurrentLevel > 14 && CurrentLevel < 40)
			return;

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


		if (CurrentCharacter == Characters_Big && GetCustomLayout == 0)
			if (CurrentLevel == LevelIDs_HotShelter && CurrentAct == 2)
				CurrentMission = 0;
			else
				CurrentMission = 5;

		if (CurrentCharacter == Characters_Amy && GetCustomLayout == 0)
			CurrentMission = 10;
	

		if (GetCustomLayout == 2 && !Race) //100 Rings
			CurrentMission = 8;

		if (GetCustomLayout == 3 && !Race) //Lost Chao
			CurrentMission = 1;
	

		if (Race && CurrentLevel == LevelIDs_SkyDeck)
			CurrentMission = 3;


		if (CurrentLevel == LevelIDs_SpeedHighway)
			if (Race)
				CurrentMission = 7;

		if (CurrentLevel == LevelIDs_HotShelter)
			if (CustomLayout == 1)
				if (CurrentCharacter == Characters_Amy)
					CurrentMission = 10;
				else
					CurrentMission = 0;

				
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

	//helperFunctions.ReplaceFile("system\\ENDBG_SONIC_0.PVM", "system\\textures\\ENDBG_RANDOMIZER_0.pvmx"); //background credits
	help.ReplaceFile("system\\sounddata\\bgm\\wma\\nights_k.wma", "system\\songs\\RandoStats.mp3"); //Introduce Stage Load Sound

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4000.wma", "system\\voices\\SonicHereWeGo.wma"); //Introduce Sonic Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4001.wma", "system\\voices\\TailsLeaveItToMe.wma"); //Introduce Tails Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4002.wma", "system\\voices\\KnuxGotIt.wma"); //Introduce Knux Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4003.wma", "system\\voices\\AmyHereWeGo.wma"); //Introduce Amy Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4005.wma", "system\\voices\\EggmanSwap.wma"); //Introduce Amy Switch

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4010.wma", "system\\voices\\BigVictory.wma"); //Add Big Victory Stage voice
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4011.wma", "system\\voices\\BigWouhou.wma"); //Add Big Victory Boss / other voice
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4012.wma", "system\\voices\\EggmanYosh.wma"); //Add Eggman Victory voice

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\5000.wma", "system\\voices\\Bounce.wma"); //Introduce Sonic bounce sfx

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\5001.wma", "system\\voices\\BackRingHit.wma"); //Back Ring SFX

	//help.ReplaceFile("system\\CON_REGULAR.pvm", "system\\textures\\CON_REGULAR_E.PVMX"); //Test


}

void TitleCard_Init() {

	WriteJump(j_LoadTitleCardTexture, LoadTitleCardTexture_r);
	WriteJump(j_DisplayTitleCard, DisplayTitleCard_r);
	WriteJump(LoadStageMissionImage, LoadStageMissionImage_r);
	WriteCall((void*)0x4284ac, StageMissionImage_result);
	WriteCall((int*)0x4284cd, CheckMissionRequirements_r);
}

void Set_BackRing() {

	WriteCall((void*)0x414859, ResetTime_R); //prevent the game to reset the timer if you hit the back ring.

	//capsule
	WriteCall((void*)0x46adc2, BackRing);

	//Ballon
	WriteCall((void*)0x7a1e25, BackRing);

	//Frog
	WriteCall((void*)0x4fa2e8, BackRing2);

	//EC + LW
	WriteCall((void*)0x5b24d8, BackRing2);

	//WV back ring
	WriteCall((void*)0x04df349, BackRing2);
	WriteCall((void*)0x4df383, BackRing2);
	WriteCall((void*)0x4df395, BackRing2);

	//Casino back ring
	WriteCall((void*)0x5dd051, BackRing2);
	WriteCall((void*)0x5dd07e, BackRing2);
	WriteCall((void*)0x5dd08d, BackRing2);

	//Ice Cap back ring
	WriteCall((void*)0x4ecf61, BackRing2);
	WriteCall((void*)0x4ecf85, BackRing2);
	WriteCall((void*)0x4ecf94, BackRing2);
}

