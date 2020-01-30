#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include "RandomHelpers.h"
#include "Trampoline.h"
#include "GameObject.h"


extern char SwapDelay;
extern bool RNGStages;

extern unsigned int TotalCount;
extern bool ChaoSpawn;
extern bool isPlayerInWaterSlide;
extern char GetCustomLayout;
bool GetBackRing = false;
int RingCopy = 0; //Backring
extern bool RandCongratsDone;
bool IceCapCutsceneSkip = false;
extern ObjectMaster* CurAI;

//While load result: "fix" game crash. (There is probably a better way to do this.), restore most of the value to 0 to avoid any conflict.
void DisableTimeStuff() {
	if (GameMode != 9 && GameMode != 10)
	{
		GameMode = GameModes_Adventure_Field; //fix game crash
	}

	if (SelectedCharacter == 6) //Fix Super Sonic Story giving sonic layout
		LastStoryFlag = 1;
	else
		LastStoryFlag = 0;

	TimeThing = 0;

	ResetValueWhileLevelResult();
	ringsPB += Rings; //total Rings credit stat

	if (CurrentCharacter != Characters_Tails)
		ResultVoiceFix();

	if (CurrentCharacter == Characters_Tails && !Race)
		SetTailsRaceVictory();

	if (!Race && isAIAllowed && isAIActive && CurrentLevel != LevelIDs_TwinklePark) //Move AI to player 1 if we are not racing.
	{
		ObjectMaster* play1 = GetCharacterObject(0);
		ObjectMaster* play2 = GetCharacterObject(1);

		if (play2 != nullptr && play1 != nullptr)
		{
			if (CurrentCharacter != Characters_Amy)
			{
				play2->Data1->Position.x = play1->Data1->Position.x - 7;
				play2->Data1->Position.y = play1->Data1->Position.y;
				play2->Data1->Position.z = play1->Data1->Position.z + 5;
				play2->Data1->Rotation.y = play1->Data1->Rotation.y;
			}
			else
			{
				DeleteObject_(TailsAI_ptr); //prevent crash as Amy.
			}

			play1->Data1->CharID;

			if (CurrentAI == Characters_Tails && isAIActive == true || play1->Data1->CharID == Characters_Tails && (isAIActive == true || !Race))
			{
				SetTailsRaceVictory(); //Fix Tails AI victory animation
			}
			ForcePlayerAction(1, 19); //Force AI to Victory pose
			dword_3B2A304 = 0;
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
			SetTailsRaceVictory();
			Tails_CheckRaceResult();
		}
	}

	if (CurrentLevel != LevelIDs_TwinkleCircuit && GameMode != GameModes_Mission)
		AddCustomFlag(); //credits check

	Race = false;
	return;
}


void ResetValueWhileLevelResult() {

	SonicRand = 0;
	KnuxCheck = 0;
	KnuxCheck2 = 0; //fix trial crash
	ChaoSpawn = false;
	GetBackRing = false;
	isPlayerInWaterSlide = false;

	RestoreRNGValueKnuckles();

	if (CurrentLevel == LevelIDs_PerfectChaos && CurrentCharacter != Characters_Sonic)
		CharObj2Ptrs[0]->Powerups &= Powerups_Invincibility;

	return;
}

void fixTCCart() {
	WriteData<1>((void*)0x798306, 0x85); //Restore original Functions
	WriteData<1>((void*)0x7983c4, 0x7C);

	return;
}

void HotShelterSecretSwitch() { //used for Big Hot Shelter when not Big for secret path.
	if (SecretWaterSwitch == 3 && FirstHotShelterSwitch == 1)
	{
		SomethingAboutHotShelterSwitch = 1;
	}

	return;
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

	if (CurrentLevel == LevelIDs_FinalEgg && CustomLayout != 1) //don't load Zero if Sonic Layout
		return;

	static const PVMEntry EGGROBPVM = { "EGGROB", &EGGROB_TEXLIST };
	LoadPVM("EGGROB", &EGGROB_TEXLIST);
	CheckLoadZero();
}

void Set_Zero() {
	//Zero Stuff
	WriteCall((void*)0x61d169, LoadZero); //Call Zero when not Amy at Twinkle Park.
	WriteCall((void*)0x59a119, LoadZero); //Call Zero when not Amy at Hot Shelter.
	WriteCall((void*)0x5ae104, LoadZero); //Call Zero when not Amy at Final Egg.
	WriteData<6>((void*)0x4d3f4a, 0x90); //Make Zero spawn for every character.
}

ObjectMaster* CurrentCart = nullptr;

void Load_Cart_R() {
	ObjectMaster* play1 = GetCharacterObject(0);

	if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		if (play1 != nullptr && play1->Data1->CharID <= 2)
			return;

	Delete_Cart();

	LoadPVM("OBJ_SHAREOBJ", &OBJ_SHAREOBJ_TEXLIST);
	CurrentCart = LoadObject((LoadObj)(15), 3, Cart_Main);

	if (CurrentCart)
	{
		CurrentCart->Data1->Scale.y = 1; //Cart will spawn empty.

		switch (CurrentCharacter)
		{
		case Characters_Gamma:
			CurrentCart->Data1->Scale.x = 0;
			CurrentCart->Data1->Scale.z = 2;
			break;
		case Characters_Big:
			CurrentCart->Data1->Scale.x = 2;
			CurrentCart->Data1->Scale.z = 1;
			break;
		default:
			CurrentCart->Data1->Scale.z = 0;
			break;
		}

		switch (CurrentLevel)
		{
		case LevelIDs_SandHill:
			CurrentCart->Data1->Position = play1->Data1->Position;
			CurrentCart->Data1->Rotation.y = 30300;
			break;
		default:
			CurrentCart->Data1->Position = play1->Data1->Position;
			break;
		}
	}
}

void Delete_Cart()
{
	if (CurrentCart != nullptr)
		DeleteObject_(CurrentCart);

	CurrentCart = nullptr;

	ForcePlayerAction(0, 28);

	if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
			ForcePlayerAction(0, 0x18);
}

void FixRestart_Cart() //Prevent the game to crash if you restart while being in a custom cart.
{
	if (CurrentLevel == LevelIDs_IceCap)
	{
		if (CurrentCart != nullptr)
			DeleteObjectMaster(CurrentCart);

		CurrentCart = nullptr;
		ForcePlayerAction(0, 28);
	}

	return; DisableControl();
}

/*
void ICAct3CutsceneSkip() {
	ObjectMaster* GetChara = GetCharacterObject(0);

	if (GetChara != nullptr && GetChara->Data1->CharID > 2)
	{
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		{
			TimeThing = 1;
			EnableController(0);
			PlayMusic(MusicIDs_icecap3);
			IceCapCutsceneSkip = true;

			if (CurrentCharacter != Characters_Sonic && CurrentCharacter != Characters_Tails)
			{
				LoadPVM("SUPERSONIC", &SUPERSONIC_TEXLIST);
				CharObj2Ptrs[0]->Upgrades |= Upgrades_SuperSonic;
				LoadObject((LoadObj)2, 2, Sonic_SuperAura_Load);
				LoadObject((LoadObj)8, 2, Sonic_SuperPhysics_Load);
			}
		}
	}

	return;
}*/

void ICAct3Position() {
	ObjectMaster* GetChara = GetCharacterObject(0);

	if (GetChara != nullptr && GetChara->Data1->CharID > 2)
	{
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		{
			TimeThing = 1;
			EnableController(0);
			PlayMusic(MusicIDs_icecap3);
			return PositionPlayer(0, -6674, -10025.23926, -1776);
		}
	}

	return;
}

void EmeraldRadar_R() {

	if (CustomLayout == 4 && CurrentLevel <= LevelIDs_Casinopolis)
	{
		LoadPVM("KNU_EFF", &KNU_EFF_TEXLIST);
		LoadObject((LoadObj)2, 6, EmeraldRadarHud_Load_Load);
		if (CurrentCharacter != Characters_Knuckles)
			KnuxCheck2 = 0; //fix Trial Mode Crash
	}

	return;
}

//Add rings every Checkpoint for cart speed.
void AddRingSandHill() {
	PlaySound(0x15, 0, 0, 0);

	if (CurrentLevel == LevelIDs_SandHill && CurrentCharacter > 2)
		AddRings(10);

	return;
}

void TwinkleCircuitResult() {
	TCQuit = 1;
	DisablePause();
	ScreenFade_Timer = 0;
	ScreenFade_Alpha = 0xff;

	if (SelectedCharacter == 6) //Fix Super Sonic Story giving sonic layout
		LastStoryFlag = 1;
	else
		LastStoryFlag = 0;

	CustomFlag++;
	GameMode = GameModes_Adventure_Field;
	Rings = 0;
	DeleteAllObjects();
	PauseQuitThing2();
	GameState = 0x5;
}

void FixRollerCoaster() {
	ObjectMaster* obj = GetCharacterObject(0);
	EntityData1* ent;
	ent = obj->Data1;
	obj->Data1->Action = 28; //force the character to leave the RC
}

int AmyCartImprovement() {
	if (CurrentCharacter == Characters_Amy) //trick the game to make it think we are playing Sonic.
		return Characters_Sonic;
	else
		return CurrentCharacter;

}

int KnuxRadar() {  //trick the game to make it think we are playing Knuckles
	
	if (CustomLayout == 4)
		return Characters_Knuckles;
	else
		return CurrentCharacter;
}

//Set Emerald RNG when not Knuckles

void SetRNGKnuckles() {

	if (CurrentLevel >= LevelIDs_SpeedHighway && CurrentLevel <= LevelIDs_Casinopolis)
	{
		if (CustomLayout == 4)
		{
			WriteData<1>((void*)0x416F06, 0x08);
			WriteData<1>((void*)0x4153E1, 0x08);
			WriteData<1>((void*)0x416f08, 0x74);
			WriteData<1>((void*)0x4153e3, 0x74);
		}
	}
}

//restore original values
void RestoreRNGValueKnuckles() {

	WriteData<1>((void*)0x416F06, 0x03);
	WriteData<1>((void*)0x4153E1, 0x03);
	WriteData<1>((void*)0x416f08, 0x75);
	WriteData<1>((void*)0x4153e3, 0x75);

}

void ResetTime_R() { //Used for Back Ring, restore player's rings.
	RingCopy = Rings;

	if (GetBackRing)
		if (GetCustomLayout == 3 || GetCustomLayout == 2)
		{
			Rings = RingCopy;
			ChaoSpawn = false;
			return;
		}

	return ResetTime();
}

void BackRing() { //swap capsule
	SetTextureToCommon();

	SwapDelay = 0;
	if (GetCustomLayout == 3 || GetCustomLayout == 2)
	{
		if (CurrentLevel == LevelIDs_TwinklePark)
			return;


		GetBackRing = true;
		PlayVoice_R(5001); //back ring hit SFX

		ScreenFade_Timer = 50;
		short sVar1;
		sVar1 = ScreenFade_RunActive();
		ChaoSpawn = false;
		GameMode = GameModes_Adventure_Field;

		if (SwapDelay == 150)
		{
			GameState = 0xb;
			return;
		}


	}

}

void BackRing2() { //swap Frog/Emerald etc.
	SwapDelay = 0;
	if (GetCustomLayout == 3 || GetCustomLayout == 2)
	{
		if (CurrentLevel == LevelIDs_TwinklePark)
			return;


		GetBackRing = true;
		PlayVoice_R(5001); //back ring hit SFX
		ScreenFade_Timer = 50;
		short sVar1;
		sVar1 = ScreenFade_RunActive();
		ChaoSpawn = false;
		GameMode = GameModes_Adventure_Field;

		if (SwapDelay == 150)
		{
			GameState = 0xb;
			return;
		}
		
		
	}
	else
	{
		return LoadLevelResults();
	}
}

void SHAct2Position() {
	if (CurrentCharacter != Characters_Sonic)
		return PositionPlayer(0, 10, -10000, 10);
	else
		return ForcePlayerAction(0, 0x2b);
}

void preventCutscene() {
	switch (CurrentLevel)
	{
	case LevelIDs_RedMountain:
		if (CurrentCharacter == Characters_Sonic || Characters_Tails)
			return;
		break;
	case LevelIDs_EmeraldCoast:
		if (CurrentCharacter == Characters_Tails)
			return;
	case LevelIDs_HotShelter:
		if (CurrentCharacter == Characters_Amy && CurrentAct == 1)
			return;
		break;
	}

	return GetLevelCutscene();
}

void DeathsStat() {
	//Hook used when you lose a live
	deathsPB++;
	return GiveLives(0xffffffff);
}

void HurtsStat() {
	//Hook used when you lose your rings
	hurtsPB++;
	return Set0Rings();
}

void KillStat() {
	killPB++;
	GetCharacterID(0);
	return;
}

void AnimalStat() {
	animalPB++;
	PlaySound(0x1c, 0, 0, 0);
	return;
}

void HookStats_Inits() {
	WriteCall((void*)0x45072d, HurtsStat);
	WriteCall((void*)0x416e7d, DeathsStat); //Trial Mode
	WriteCall((void*)0x417a1f, DeathsStat); //Adventure Mode
	//WriteJump((void*)0x43bfd8, JumpStat); //doesn't work for now
	WriteCall((void*)0x4d88ca, KillStat);
	WriteCall((void*)0x4d7977, AnimalStat);
}