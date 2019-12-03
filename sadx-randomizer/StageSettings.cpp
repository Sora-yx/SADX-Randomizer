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

void Set_Zero() {
	//Zero Stuff
	WriteCall((void*)0x61d169, LoadZero); //Call Zero when not Amy at Twinkle Park.
	WriteCall((void*)0x59a119, LoadZero); //Call Zero when not Amy at Hot Shelter.
	WriteCall((void*)0x5ae104, LoadZero); //Call Zero when not Amy at Final Egg.
	WriteData<6>((void*)0x4d3f4a, 0x90); //Make Zero spawn for every character.

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
	PlayVoice(5001);

	if (GetCustomLayout == 3 || GetCustomLayout == 2)
	{
		if (CurrentLevel == LevelIDs_TwinklePark)
			return;

		StopMusic();
		GetBackRing = true;

		GameMode = GameModes_Adventure_Field; //GameMode = 5
		GameState = 0xb; //Will teleport the player at the beginning of the level without losing lives or rings.
	}
	

}

void BackRing2() { //Frog //Emerald

	if (GetCustomLayout == 3 || GetCustomLayout == 2)
	{
		if (CurrentLevel == LevelIDs_TwinklePark)
			return;

		PlayVoice(5001);
		StopMusic();

		GetBackRing = true;
		GameMode = GameModes_Adventure_Field; //GameMode = 5
		GameState = 0xb; //Will teleport the player at the beginning of the level without losing lives or rings.
		

		PlayVoice(5001);
		StopMusic();
		short sVar1;
		sVar1 = ScreenFade_RunActive();

		GameMode = GameModes_Adventure_Field;
		GameState = 0xb;
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



