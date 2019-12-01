#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include "RandomHelpers.h"
#include "Trampoline.h"

HelperFunctions extern help;

extern bool RNGStages;

extern int CustomFlag;
extern int TotalCount;
extern int CustomLayout;
bool Race = false;
extern bool isAIAllowed;
extern bool isAIActive;
extern int CurrentAI;
extern int GetCustomLayout;
bool GetBackRing = false;

//While load result: "fix" game crash. (There is probably a better way to do this.), restore most of the value to 0 to avoid any conflict.
void DisableTimeStuff() {


	if (GameMode != 9 && RNGStages == true)
	{
		GameMode = GameModes_Adventure_Field; //fix game crash
	}

	TimeThing = 0;
	SonicRand = 0;

	if (CurrentCharacter != Characters_Tails)
		ResultVoiceFix();

	Credits_CanSkip = 1;

	AddCustomFlag(); //credits check

	if (!Race && isAIAllowed && isAIActive && CurrentLevel != LevelIDs_TwinklePark && CurrentCharacter != Characters_Amy) //Move AI to player 1 if we are not racing.
	{
		ObjectMaster* play1 = GetCharacterObject(0);
		ObjectMaster* play2 = GetCharacterObject(1);

		play2->Data1->Position.x = play1->Data1->Position.x - 7;
		play2->Data1->Position.y = play1->Data1->Position.y;
		play2->Data1->Position.z = play1->Data1->Position.z + 5;
		play2->Data1->Rotation.y = play1->Data1->Rotation.y;

			if (CurrentAI == Characters_Tails && isAIActive == true)
			{
				SetTailsRaceVictory(); //Fix Tails AI victory animation
			}

			ForcePlayerAction(1, 19); //Force AI to Victory pose
			dword_3B2A304 = 0;
			
			if (CurrentLevel != LevelIDs_SpeedHighway)
			{
				return;
			}
	}

		if (Race)
		{
			if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big)
			{
				Race = false;
				return; //they don't race
			}
			else
			{
				Tails_CheckRaceResult();
				Race = false;
				return;
			}
		}
	

	Race = false;
	return;
}



void HotShelterSecretSwitch() { //used for Big Hot Shelter as a wrong character for secret path.

	if (SecretWaterSwitch == 3 && FirstHotShelterSwitch == 1)
	{
		SomethingAboutHotShelterSwitch = 1;
	}

}


void HotShelterHandle() {

	ObjectMaster* obj = GetCharacterObject(0);
	EntityData1* ent;
	ent = obj->Data1;

	if (ControllerPointers[0]->PressedButtons & Buttons_B || ControllerPointers[0]->PressedButtons & Buttons_X)
	{
		EnemyBounceThing(0x0, 0, 1.50, 8.50);
		CharObj2Ptrs[0]->AnimationThing.Index = 1;
		ForcePlayerAction(0, 24);
	}

	else
	{
		ent->Rotation.y = 129;
		switch (obj->Data1->CharID)
		{
		case Characters_Sonic:
			obj->Data1->Action = 20;
			CharObj2Ptrs[0]->AnimationThing.Index = 54;
			break;
		case Characters_Tails:
			obj->Data1->Action = 18;
			CharObj2Ptrs[0]->AnimationThing.Index = 79;
			break;
		case Characters_Knuckles:
			obj->Data1->Action = 29;
			CharObj2Ptrs[0]->AnimationThing.Index = 86;
			break;
		case Characters_Big:
			obj->Data1->Action = 17;
			CharObj2Ptrs[0]->AnimationThing.Index = 54;
			break;
		case Characters_Gamma:
			obj->Data1->Action = 14;
			CharObj2Ptrs[0]->AnimationThing.Index = 42;
			break;
		}
	}
}

void LoadZero() {


	if (CurrentLevel == LevelIDs_HotShelter)
		PressedSwitches_Reset();
	

	if (CurrentLevel == LevelIDs_FinalEgg)
		{
			camerahax_b();
			RNGDoor = rand() % 5;
		}

	if (CurrentLevel == LevelIDs_TwinklePark)
		SetCameraControlEnabled(1);


	if (CurrentLevel == LevelIDs_FinalEgg && CurrentCharacter != Characters_Sonic && CustomLayout == 0) //don't load Zero if Sonic Layout
		return;

	if (CurrentCharacter != Characters_Amy)
	{
		static const PVMEntry EGGROBPVM = { "EGGROB", &EGGROB_TEXLIST };
		LoadPVM("EGGROB", &EGGROB_TEXLIST);
		CheckLoadZero();
	}
	
}


void TwinkleCircuitResult() {

	CustomFlag++;
	GameMode = GameModes_Adventure_Field;
	Rings = 0;
	ScreenFade_Start();
	GameState = 0x11;
}



void CheckRace() {

	if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big)
	{
		Race = false;
		return;
	}
	else
	{
		switch (CurrentLevel)
		{
		case LevelIDs_SpeedHighway:
			if (CustomLayout == 1 && CurrentAct == 0)
			{
				AICourse = Levels2P_SpeedHighway;
				//LoadObject((LoadObj)(LoadObj_UnknownB | LoadObj_Data1), 0, Eggman2PAI);     //already called somewhere
				LoadObject(LoadObj_Data1, 8, MRace_EggMobile_TexlistManager);
				Race = true;
			}
		case LevelIDs_SkyDeck:
			if (CustomLayout == 1 && CurrentAct == 0)
			{
				LoadTailsOpponent(CurrentCharacter, 1, CurrentLevel);
				Race = true;
			}
			break;
		}

		return;

	}
}

int IsFastSonicAI_R(void) {

	if (Race)
	{
		switch (CurrentLevel)
		{
		case LevelIDs_WindyValley:
			if (CustomLayout == 4 && CurrentAct == 2)
				return FastSonicAI = 1;
			break;
		case LevelIDs_SkyDeck:
			if (CustomLayout == 3 && CurrentAct == 0)
				return FastSonicAI = 1;
			break;

		default:
			return FastSonicAI = 0;
			break;
		}
	}

	return FastSonicAI = 0;

}


void FixRollerCoaster() {

	ObjectMaster* obj = GetCharacterObject(0);
	EntityData1* ent;
	ent = obj->Data1;
	obj->Data1->Action = 28; //force the character to leave the RC

}


void ResetTime_R() {

	if (GetBackRing)
		if (GetCustomLayout == 3 || GetCustomLayout == 2)
			return;

	ResetTime();
	
}

void BackRing() { //capsule

	
	SetTextureToCommon();


	if (GetCustomLayout == 3 || GetCustomLayout == 2)
	{
		if (CurrentLevel == LevelIDs_TwinklePark)
			return;

		StopMusic();
		GetBackRing = true;

		GameMode = GameModes_Adventure_Field; //GameMode = 5
		GameState = 0xb; //Will teleport the player at the beginning of the level without losing lives or rings.
		//TimeThing

	}
	

}

void BackRing2() { //Frog //Emerald

	if (GetCustomLayout == 3 || GetCustomLayout == 2)
	{
		if (CurrentLevel == LevelIDs_TwinklePark)
			return;

		StopMusic();
		short sVar1;
		sVar1 = ScreenFade_RunActive();

		GameMode = GameModes_Adventure_Field;
		GameState = 0xb;

		/*ObjectMaster* play1 = GetCharacterObject(0); //teleport player


		switch (CurrentLevel)
		{
		case LevelIDs_EmeraldCoast:
			if (CurrentAct == 1)
			{
				PlayMusic(MusicIDs_EmeraldCoastWindyAndRipply);
				play1->Data1->Position.x = -986.5;
				play1->Data1->Position.y = 1145;
				play1->Data1->Position.z = -2856;
			}
			break;
		case LevelIDs_WindyValley:
			if (CurrentAct == 2)
			{
				PlayMusic(MusicIDs_WindyValleyTheAir);
				play1->Data1->Position.x = 1068.41;
				play1->Data1->Position.y = -335;
				play1->Data1->Position.z = -1232;
				play1->Data1->Rotation.y = 26978;
			}
			break;
		case LevelIDs_Casinopolis:
			if (CurrentAct == 0)
			{
				PlayMusic(MusicIDs_casino1);
				play1->Data1->Position.x = 0;
				play1->Data1->Position.y = 0;
				play1->Data1->Position.z = 0;
			}
			else
			{
				PlayMusic(MusicIDs_casino2);
				play1->Data1->Position.x = 19;
				play1->Data1->Position.y = -1695;
				play1->Data1->Position.z = 2850;
			}
			break;
		case LevelIDs_IceCap:
			if (CurrentAct == 2)
			{
				PlayMusic(MusicIDs_icecap2);
				play1->Data1->Position.x = 1060;
				play1->Data1->Position.y = 336;
				play1->Data1->Position.z = 280;
			}
			break;
		case LevelIDs_TwinklePark:
			/*	PlayMusic(MusicIDs_TwinkleParkPleasureCastle); //Doesn't work for now
				play1->Data1->Position.x = 520;
				play1->Data1->Position.y = 975;
				play1->Data1->Position.z = 1620;
			break;
		case LevelIDs_SpeedHighway:
			if (CurrentAct == 2)
			{
				PlayMusic(MusicIDs_SpeedHighwaySpeedHighway);
				play1->Data1->Position.x = 72;
				play1->Data1->Position.y = 26;
				play1->Data1->Position.z = 192;
			}
			break;
		case LevelIDs_RedMountain:
			if (CurrentAct == 1)
			{
				PlayMusic(MusicIDs_RedMountainMtRedASymbolOfThrill);
				play1->Data1->Position.x = -78;
				play1->Data1->Position.y = 831;
				play1->Data1->Position.z = 1919;
			}
			break;
		case LevelIDs_SkyDeck:
			if (CurrentAct == 2)
			{
				PlayMusic(MusicIDs_SkyDeckGeneralOffensive);
				play1->Data1->Position.x = -696;
				play1->Data1->Position.y = -86;
				play1->Data1->Position.z = 135;
			}
			break;
		}*/
	}
	else
		LoadLevelResults();

}



void SHAct2Position() {

	if (CurrentCharacter != Characters_Sonic)
		PositionPlayer(0, 10, -10000, 10);
	else
		ForcePlayerAction(0, 0x2b);
	
}


void ICAct3Position() {

	SetTextureToLevelObj();

	if (CurrentCharacter > 2)
	{
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		{
			TimeThing = 1;
			PlaySound(0xde, 0, 0, 0);
			EnableController(0);
			PlayMusic(MusicIDs_icecap3);
			PositionPlayer(0, -6674, -8167, -1776);
		}
	}

	return;
}



