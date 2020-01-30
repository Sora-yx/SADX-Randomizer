#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"
#define AddVoices(A, B) helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\" A ".wma", "system\\voices\\" B ".adx")

char GetCustomLayout;
NJS_TEXNAME MissionsText[18];
int CurrentMission = 0; //the current mission, if it's 1 then we load a lost chao in Chao.cpp
HelperFunctions help;


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
		WriteCall((void*)0x59a197, RandomMusic); //hook hot shelter music part 8 xd

		WriteCall((void*)0x5adda7, RandomMusic); //Final Egg Song
		WriteCall((void*)0x5ae144, RandomMusic); //Final Egg Song act 2
		WriteCall((void*)0x5addd7, RandomMusic); //Final Egg Song act 2 part 2
		WriteCall((void*)0x5adf85, RandomMusic); //Final Egg Song act 3

		WriteCall((void*)0x79e4e8, RandomMusic); //Sand Hill
		WriteCall((void*)0x54a60d, RandomMusic); //Chaos 2
		WriteCall((void*)0x5578ad, RandomMusic); //Chaos 6
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
		//0 = capsule, 1 = Lost Chao, 2 = Emeralds Knux, 3 = Beat Sonic, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails, 10 = Zero, 11+ Race

		if (CurrentLevel > 14 && CurrentLevel < 40)
			return;
		if (CurrentLevel == LevelIDs_TwinkleCircuit)
			return;

		GetCustomLayout = CustomLayout;

		if (CurrentLevel == LevelIDs_EmeraldCoast && CurrentAct == 2 || CurrentLevel == LevelIDs_EmeraldCoast && CurrentAct == 0 && CustomLayout == 1)
			CurrentMission = 5;

		if (CurrentLevel == LevelIDs_LostWorld && CustomLayout == 0)
			CurrentMission = 6;

		if (CurrentLevel == LevelIDs_FinalEgg)
		{
			if (CustomLayout == 1 && CurrentCharacter != Characters_Amy)
				CurrentMission = 0;
			else
				CurrentMission = 4;

			if (CurrentCharacter == Characters_Amy)
				CurrentMission = 10;
		}

		if (CurrentCharacter == Characters_Big && GetCustomLayout == 0)
		{
			if (CurrentLevel == LevelIDs_HotShelter && CurrentAct == 2)
				CurrentMission = 0;
			else if (CurrentLevel == LevelIDs_FinalEgg)
				CurrentMission = 0;
			else
				CurrentMission = 5;
		}

		if (Race && (CurrentLevel == LevelIDs_SkyDeck || CurrentLevel == LevelIDs_Casinopolis || CurrentLevel == LevelIDs_IceCap && CurrentAct == 2 || CurrentLevel == LevelIDs_WindyValley && CurrentAct == 2))
		{
			switch (AIRace)
			{
			case Characters_Eggman:
				CurrentMission = 16;
				break;
			case Characters_Tails:
				CurrentMission = 11;
				break;
			case Characters_Knuckles:
				CurrentMission = 12;
				break;
			case Characters_Tikal:
				CurrentMission = 17;
				break;
			case Characters_Amy:
				CurrentMission = 13;
				break;
			case Characters_Gamma:
				CurrentMission = 15;
				break;
			case Characters_Big:
				CurrentMission = 14;
				break;
			default:
				CurrentMission = 3;
				break;
			}
		}

		if (GetCustomLayout == 4)
			CurrentMission = 2;

		if (CurrentCharacter == Characters_Amy && (GetCustomLayout == 0 || GetCustomLayout == 1 && CurrentLevel == LevelIDs_RedMountain))
			CurrentMission = 10;

		if (GetCustomLayout == 2 && !Race) //100 Rings
			CurrentMission = 8;

		if (GetCustomLayout == 3 && !Race) //Lost Chao
			CurrentMission = 1;

		if (CurrentLevel == LevelIDs_SpeedHighway)
			if (Race)
				CurrentMission = 7;

		if (CurrentLevel == LevelIDs_HotShelter)
		{
			if (CustomLayout == 1 && CurrentAct == 0)
				CurrentMission = 5;
		}

		if (CurrentLevel == LevelIDs_IceCap)
		{
			if (CurrentAct == 3)
				CurrentMission = 5;
		}

		StageMissionTexlist.textures = MissionsText;
		StageMissionTexlist.nbTexture = LengthOfArray(MissionsText);
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
		//0 = capsule, 1 = Lost Chao, 2 = Beat Sonic, 3 = Emeralds Knux, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails, 10 = Fast Tails Race

		GetCustomLayout = CustomLayout;

		if (CurrentLevel > 14)
			return;

		StageMissionTexlist.textures = MissionsText;
		StageMissionTexlist.nbTexture = LengthOfArray(MissionsText);
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

	if (CurrentLevel == 0 || CurrentLevel > 14 && CurrentLevel < 35) {
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
	help = helperFunctions;
	//Initiliaze data

	HedgehogHammer_Init(path, helperFunctions);
	EmeraldCoast_Init(path, helperFunctions);
	WindyValley_Init(path, helperFunctions);
	Casino_Init(path, helperFunctions);
	IceCap_Init(path, helperFunctions);
	TwinklePark_Init(path, helperFunctions);
	SpeedHighway_Init(path, helperFunctions);
	RedMountain_Init(path, helperFunctions);
	SkyDeck_Init(path, helperFunctions);
	LostWorld_Init(path, helperFunctions);
	FinalEgg_Init(path, helperFunctions);
	HotShelter_Init(path, helperFunctions);

	//Boss
	Chaos0_Init(path, helperFunctions);
	Chaos2_Init(path, helperFunctions);
	Chaos6_Init(path, helperFunctions);
	EggHornet_Init(path, helperFunctions);
	EggWalker_Init(path, helperFunctions);
	EggViper_Init(path, helperFunctions);
	Zero_Init(path, helperFunctions);
	//E101_Init(path, helperFunctions);

	helperFunctions.ReplaceFile("system\\AVA_GTITLE0_E.PVM", "system\\textures\\AVA_GTITLE0_E.PVM"); //replace title screen
	helperFunctions.ReplaceFile("system\\sounddata\\bgm\\wma\\nights_k.wma", "system\\songs\\RandoStats.mp3"); //Custom rando stats song

	AddVoices("4000", "SonicHereWeGo"); //Introduce Sonic Switch
	AddVoices("4001", "TailsLeaveItToMe"); //Introduce Tails Switch
	AddVoices("4002", "KnuxGotIt"); //Introduce Knux Switch
	AddVoices("4003", "AmyHereWeGo"); //Introduce Amy Switch
	AddVoices("4005", "EggmanSwap"); //Introduce Eggman Switch

	AddVoices("4010", "BigVictory"); //Add Big Victory Stage voice
	AddVoices("4011", "BigWouhou"); //Add Big Victory Boss / other voice
	AddVoices("4012", "EggmanYosh"); //Add Eggman Victory voice

	AddVoices("5000", "Bounce"); //Introduce Sonic bounce sfx

	helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\5001.wma", "system\\voices\\systemBackRingHit.wma"); //Back Ring SFX
	AddVoices("5002", "ChaoCry1");
	AddVoices("5003", "ChaoCry2");

	AddVoices("5010", "Congratulations_Sonic");
	AddVoices("5011.", "Congratulations_Tails");
	AddVoices("5012", "sCongratulations_Knux");
	AddVoices("5013", "Congratulations_Amy");

	AddVoices("6000", "RadarBlink");
	AddVoices("6001", "KnuxEmeraldGet");
	AddVoices("6002", "TikalHint");

	//help.ReplaceFile("system\\CON_REGULAR.pvm", "system\\textures\\CON_REGULAR_E.PVMX"); //Test
	helperFunctions.ReplaceFile("system\\SETMCART03S.BIN", "system\\TCAct3.BIN"); //TC act 4 fix
	helperFunctions.ReplaceFile("system\\SETMCART03E.BIN", "system\\TCAct3.BIN");
	WriteCall((void*)0x44B0A4, CheckDeleteAnimThing); //test

	//Random Title Card + Missions
	TitleCard_Init();

	//Back Rings for M2 & M3
	Set_BackRing();

	WriteData<2>((void*)0x641232, 0x90); //allow to skip credits.
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