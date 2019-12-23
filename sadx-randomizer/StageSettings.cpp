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
extern bool isAIAllowed;
extern bool isAIActive;
extern bool Race;
extern int CurrentAI;
extern int GetCustomLayout;
bool GetBackRing = false;
int RingCopy = 0; //Backring

//Credits stats
extern int ringsPB;
extern int animalPB;
extern int killPB;
extern int hurtsPB;
extern int deathsPB;
extern int JumpCount;
extern int TotalDeathsPB;
extern int TotalHurtsPB;

//While load result: "fix" game crash. (There is probably a better way to do this.), restore most of the value to 0 to avoid any conflict.
void DisableTimeStuff() {


	if (GameMode != 9 && RNGStages == true)
	{
		GameMode = GameModes_Adventure_Field; //fix game crash
	}

	if (SelectedCharacter == 6) //Fix Super Sonic Story giving sonic layout
		LastStoryFlag = 1;
	else
		LastStoryFlag = 0;

	TimeThing = 0;
	SonicRand = 0;
	ringsPB += Rings; //total Rings credit stat
	TotalDeathsPB += deathsPB; //total Death credit stat
	TotalHurtsPB += hurtsPB; //total Death credit stat
	GetBackRing = false;

	if (CurrentCharacter != Characters_Tails)
		ResultVoiceFix();

	if (CurrentLevel != LevelIDs_TwinkleCircuit)
		AddCustomFlag(); //credits check

	if (CurrentCharacter == Characters_Tails && (CurrentLevel == LevelIDs_WindyValley || CurrentLevel == LevelIDs_IceCap || CurrentLevel == LevelIDs_Casinopolis || CurrentLevel == LevelIDs_SkyDeck))
		SetTailsRaceVictory();

	if (!Race && isAIAllowed && isAIActive && CurrentLevel != LevelIDs_TwinklePark && CurrentCharacter != Characters_Amy) //Move AI to player 1 if we are not racing.
	{
		ObjectMaster* play1 = GetCharacterObject(0);
		ObjectMaster* play2 = GetCharacterObject(1);

		if (play2 != nullptr && play1 != nullptr)
		{
			play2->Data1->Position.x = play1->Data1->Position.x - 7;
			play2->Data1->Position.y = play1->Data1->Position.y;
			play2->Data1->Position.z = play1->Data1->Position.z + 5;
			play2->Data1->Rotation.y = play1->Data1->Rotation.y;

			play1->Data1->CharID;


			if (CurrentAI == Characters_Tails && isAIActive == true || play1->Data1->CharID == Characters_Tails && isAIActive == true)
			{
				SetTailsRaceVictory(); //Fix Tails AI victory animation
			}
			ForcePlayerAction(1, 19); //Force AI to Victory pose
			dword_3B2A304 = 0;
		}

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
				if (CurrentLevel == LevelIDs_WindyValley || CurrentLevel == LevelIDs_Casinopolis)
					SetTailsRaceVictory();

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


	if (CurrentLevel == LevelIDs_FinalEgg && CurrentCharacter != Characters_Sonic && CustomLayout != 1) //don't load Zero if Sonic Layout
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

	if (SelectedCharacter == 6) //Fix Super Sonic Story giving sonic layout
		LastStoryFlag = 1;
	else
		LastStoryFlag = 0;

	CustomFlag++;
	GameMode = GameModes_Adventure_Field;
	Rings = 0;
	PauseQuitThing2();
	ScreenFade_Start();
	GameState = 0x11;
}



void FixRollerCoaster() {

	ObjectMaster* obj = GetCharacterObject(0);
	EntityData1* ent;
	ent = obj->Data1;
	obj->Data1->Action = 28; //force the character to leave the RC
}


void ResetTime_R() { //Used for Back Ring, restore player's rings.

	RingCopy = Rings;

	if (GetBackRing)
		if (GetCustomLayout == 3 || GetCustomLayout == 2)
		{
			Rings = RingCopy;
			return;
		}

	ResetTime();
}



void BackRing() { //swap capsule

	SetTextureToCommon();

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

void BackRing2() { //swap Frog/Emerald etc.

	if (GetCustomLayout == 3 || GetCustomLayout == 2)
	{
		if (CurrentLevel == LevelIDs_TwinklePark)
			return;

		StopMusic();

		GetBackRing = true;
		GameMode = GameModes_Adventure_Field; //GameMode = 5
		GameState = 0xb; //Will teleport the player at the beginning of the level without losing lives or rings.
		
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

	if (CurrentCharacter >= 2)
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


void DeathsStat() {
	//Hook used when you lose a live
	deathsPB++;
	GiveLives(0xffffffff);
}

void HurtsStat() {
	//Hook used when you lose your rings
	hurtsPB++;
	Set0Rings();
}


void KillStat() {

	killPB++;
	GetCharacterID(0);

}
	
void AnimalStat() {

	animalPB++;
	PlaySound(0x1c, 0, 0, 0);
}


void HookStats_Inits() {

	WriteCall((void*)0x45072d, HurtsStat);
	WriteCall((void*)0x416e7d, DeathsStat); //Trial Mode
	WriteCall((void*)0x417a1f, DeathsStat); //Adventure Mode
	//WriteJump((void*)0x43bfd8, JumpStat); //doesn't work for now
	WriteCall((void*)0x4d88ca, KillStat);
	WriteCall((void*)0x4d7977, AnimalStat);

}
