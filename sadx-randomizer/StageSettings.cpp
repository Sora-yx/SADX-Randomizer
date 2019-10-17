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
extern bool isRandDone;
extern int CurrentAI;

//While load result: Avoid getting the same character twice in a row, "fix" game crash. (There is probably a better way to do this.)
void DisableTimeStuff() {


	if (GameMode != 9 && RNGStages == true)
	{
		GameMode = GameModes_Adventure_Field; //fix game crash
	}

	TimeThing = 0;
	SonicRand = 0;
	isRandDone = false;
	ResultVoiceFix();
	Credits_CanSkip = 1;

	AddCustomFlag(); //credits check

	if (!Race && isAIAllowed && isAIActive) //Move AI to player 1 if we are not racing.
	{
		ObjectMaster* play1 = GetCharacterObject(0);
		ObjectMaster* play2 = GetCharacterObject(1);

		play2->Data1->Position.x = play1->Data1->Position.x - 7;
		play2->Data1->Position.y = play1->Data1->Position.y;
		play2->Data1->Position.z = play1->Data1->Position.z + 5;
		play2->Data1->Rotation.y = play1->Data1->Rotation.y;

			if (CurrentAI == Characters_Tails)
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

	//are we racing against AI
	if (CurrentLevel == LevelIDs_SpeedHighway && CurrentAct == 0)
	{
		if (CurrentCharacter == Characters_Sonic || CustomLayout != 0)
		{
			Tails_CheckRaceResult();
			Race = false;
			return;
		}
	}
	else
	{
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
	{
		PressedSwitches_Reset();
	}
	else
	{
		if (CurrentLevel == LevelIDs_FinalEgg)
		{
			camerahax_b();
			RNGDoor = rand() % 5;
		}
		else
		{
			if (CurrentLevel == LevelIDs_TwinklePark)
			{
				SetCameraControlEnabled(1);

			}
		}
	}
	if (CurrentCharacter == Characters_Amy)
	{
		return;
	}
	else
	{
		static const PVMEntry EGGROBPVM = { "EGGROB", &EGGROB_TEXLIST };
		LoadPVM("EGGROB", &EGGROB_TEXLIST);
		CheckLoadZero();
	}
}


void TwinkleCircuitResult() {

	CustomFlag++;
	GameMode = GameModes_Adventure_Field;
	ScreenFade_Start();
	GameState = 0x11;
}


//Eggman AI Speed Highway
void LoadEggmanAI() {

	if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big)
	{
		return;
	}

	if (CurrentLevel == 4 && CurrentAct == 0)
	{
		if (CurrentCharacter == Characters_Sonic || CustomLayout != 0)
		{
			RaceWinnerPlayer = 0;
			FastSonicAI = IsFastSonicAI();
			AICourse = 0;
			AICourse = Levels2P_SpeedHighway;
			LoadObject((LoadObj)(LoadObj_UnknownB | LoadObj_Data1), 0, Eggman2PAI);
			LoadObject(LoadObj_Data1, 8, MRace_EggMobile_TexlistManager);
			return;
		}
	}
}


void CheckRace() {

	if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big)
	{
		RaceWinnerPlayer = 1;
		Race = false;
		return;
	}
	else
	{
		
		switch (CurrentLevel)
		{
		case LevelIDs_WindyValley:
			if (CustomLayout == 4 && CurrentAct == 2)
			{
				LoadTailsOpponent(CurrentCharacter, 1, CurrentLevel);
				Race = true;
				
			}
			break;
		case LevelIDs_SkyDeck:
			if (CustomLayout == 3 && CurrentAct == 0)
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
			{
				return FastSonicAI = 1;

			}
			break;
		case LevelIDs_SkyDeck:
			if (CustomLayout == 3 && CurrentAct == 0)
			{
				return FastSonicAI = 1;
			}
			break;

		default:
			return FastSonicAI = 0;
			break;
		}
	}

	return FastSonicAI = 0;

}

void CheckRings() {

	if (GameMode == 4 && Rings == 100 && CustomLayout != 0)
	{
		LoadLevelResults();
	}

}

void CheckChao() {

	if (GameMode == 4 && Rings == 100)
	{
		LoadLevelResults();
	}

}

void FixRollerCoaster() {

	ObjectMaster* obj = GetCharacterObject(0);
	EntityData1* ent;
	ent = obj->Data1;
	obj->Data1->Action = 28; //force the character to leave the RC

}




void SHAct2Position() {

	if (CurrentCharacter != Characters_Sonic)
	{
		PositionPlayer(0, 10, -10000, 10);
	}
	else
	{
		ForcePlayerAction(0, 0x2b);
	}
	
}



