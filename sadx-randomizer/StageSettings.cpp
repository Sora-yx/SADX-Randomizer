#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include "RandomHelpers.h"
#include "Trampoline.h"
#include "StageSettings.h"


extern bool FEGammaVersion;
extern bool RNGStages;
extern bool GetBackRing;
extern unsigned int TotalCount;
extern bool ChaoSpawn;
extern bool isPlayerInWaterSlide;
extern char GetCustomLayout;


extern bool RandCongratsDone;
bool IceCapCutsceneSkip = false;
extern ObjectMaster* CurAI;
bool isCheckpointUsed = false;
extern ObjectMaster* TriggerOBJ;
extern ObjectMaster* TriggerHS;
extern ObjectMaster* ChaoTP;
ObjectMaster* CurrentCart = nullptr;

//While load result: "fix" game crash. (There is probably a better way to do this.), restore most of the value to 0 to avoid any conflict.
void DisableTimeStuff() {

	if (GameMode != GameModes_Trial && GameMode != GameModes_Mission && RNGStages)
		AddCustomFlag(); //Add a flag for story progression.

	if (GameMode != GameModes_Trial)
		GameMode = GameModes_Adventure_Field; //fix game crash

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


	Race = false;
	return;
}


void ResetValueWhileLevelResult() {

	isCheckpointUsed = false;
	SonicRand = 0;
	KnuxCheck = 0;
	KnuxCheck2 = 0; //fix trial crash
	ChaoSpawn = false;
	GetBackRing = false;
	TreasureHunting = false;
	isPlayerInWaterSlide = false;
	TPAmyVersion = false;
	FEGammaVersion = false;
	isCheckpointUsed = false;

	RestoreRNGValueKnuckles();

	if (CurrentLevel == LevelIDs_PerfectChaos && CurrentCharacter != Characters_Sonic)
		CharObj2Ptrs[0]->Powerups &= Powerups_Invincibility;

	DeleteObject_(TriggerOBJ);
	TriggerOBJHS_Delete();
	DeleteObject_(ChaoTP);
	Delete_Cart();
	fixTCCart();

	return;
}

void fixTCCart() {
	WriteData<1>((void*)0x798306, 0x85); //Restore original Functions
	WriteData<1>((void*)0x7983c4, 0x7C);
	FlagAutoPilotCart = 0;

	return;
}



void LoadZero() {
	if (CurrentLevel == LevelIDs_HotShelter)
		PressedSwitches_Reset();

	if (CurrentLevel == LevelIDs_FinalEgg && CurrentAct == 0)
	{
		camerahax_b();
		RNGDoor = rand() % 5;
	}

	if (CurrentLevel == LevelIDs_TwinklePark)
		SetCameraControlEnabled(1);

	if (CurrentLevel == LevelIDs_FinalEgg && CurrentLevelLayout != 1 || CurrentLevel == LevelIDs_TwinklePark && !TPAmyVersion) //don't load Zero if Sonic Layout
		return;

	static const PVMEntry EGGROBPVM = { "EGGROB", &EGGROB_TEXLIST };
	LoadPVM("EGGROB", &EGGROB_TEXLIST);
	CheckLoadZero();
}

void Set_Zero() {
	//Zero Stuff
	WriteCall((void*)0x61d169, LoadZero); //Call Zero at Twinkle Park.
	WriteCall((void*)0x59a119, LoadZero); //Call Zero at Hot Shelter.
	WriteCall((void*)0x5ae104, LoadZero); //Call Zero at Final Egg.
	WriteData<6>((void*)0x4d3f4a, 0x90); //Make Zero spawn for every character.
}



void Load_Cart_R() {
	ObjectMaster* play1 = GetCharacterObject(0);

	if (CurrentLevel == LevelIDs_TwinkleCircuit)
		return;

	if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		if (CurrentCharacter <= Characters_Tails)
			return;

	Delete_Cart();
	FlagAutoPilotCart = 0; //fix that bullshit Twinkle Circuit thing.
	LoadPVM("OBJ_SHAREOBJ", &OBJ_SHAREOBJ_TEXLIST);
	CurrentCart = LoadObject((LoadObj)(15), 3, Cart_Main);

	if (CurrentCart)
	{
		CurrentCart->Data1->Scale.y = 1; //Cart will spawn empty.

		switch (CurrentCharacter) //Set Color and Size depending on character
		{
		case Characters_Gamma:
			CurrentCart->Data1->Scale.x = BlackColor;
			CurrentCart->Data1->Scale.z = 2;
			break;
		case Characters_Big:
			CurrentCart->Data1->Scale.x = GreenColor;
			CurrentCart->Data1->Scale.z = 1;
			break;
		case Characters_Tails:
			CurrentCart->Data1->Scale.x = OrangeColor;
			CurrentCart->Data1->Scale.z = 0;
			break;
		case Characters_Knuckles:
			CurrentCart->Data1->Scale.x = RedColor;
			CurrentCart->Data1->Scale.z = 0;
			break;
		case Characters_Amy:
			CurrentCart->Data1->Scale.x = PurpleColor;
			CurrentCart->Data1->Scale.z = 0;
			break;
		default:
			CurrentCart->Data1->Scale.x = BlueColor;
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

		CurrentCart->field_30 = 59731468;
		CurrentCart->Data1->Unknown = 10;
		CurrentCart->DeleteSub = LevelItem_Delete; //TEST

		//SetData is not initialized even if it's in the list, so we need to manually assign the cart to it.
		SETObjData* cartSETData = new SETObjData();
		CurrentCart->SETData.SETData = cartSETData;

		//Set the data used in Twinkle Park/Twinkle Circuit (should fixes bug hopefully.)
		CurrentCart->SETData.SETData->LoadCount = 1;
		CurrentCart->SETData.SETData->f1 = 0;
		CurrentCart->SETData.SETData->Flags -32767;
		CurrentCart->SETData.SETData->Distance = 4000100.00;

		SETEntry* cartSETEntry = new SETEntry();
		CurrentCart->SETData.SETData->SETEntry = cartSETEntry;

		CurrentCart->SETData.SETData->SETEntry->ObjectType = 15;
		CurrentCart->SETData.SETData->SETEntry->YRotation = -9841;
		CurrentCart->SETData.SETData->SETEntry->Properties.x = 1.00000000;
		CurrentCart->SETData.SETData->SETEntry->Properties.y = 1.00000000;
		CurrentCart->SETData.SETData->SETEntry->Properties.z = 0.000000000;
	}
}


void Cart_Main_r(ObjectMaster* obj);
Trampoline Cart_Main_t(0x79A9E0, 0x79A9E5, Cart_Main_r);
void Cart_Main_r(ObjectMaster* obj) {
	obj->Data1->Action = obj->Data1->Action;

	ObjectFunc(origin, Cart_Main_t.Target());
	origin(obj);
}


void Delete_Cart()
{

	if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
			ForcePlayerAction(0, 0x18);

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0)
		return;

	if (CurrentCart != nullptr)
		DeleteObject_(CurrentCart);
	else
		return;

	ObjectMaster* P1 = GetCharacterObject(0);
	if (P1 != nullptr)
	{
		P1->Data1->InvulnerableTime = 0;
		if (++P1->Data1->InvulnerableTime == 1 && P1->Data1->Action >= 42) //wait 1 frame before removing the cart, this fix Knuckles Action.
			ForcePlayerAction(0, 28);
	}

	FlagAutoPilotCart = 0;
	CurrentCart = nullptr;
}

void FixRestart_Stuff() //Prevent the game to crash if you restart while being in a custom cart.
{

	ObjectMaster* P1 = GetCharacterObject(0);

	if (CurrentCart != nullptr)
	{
		DeleteObject_(CurrentCart);
	}

	FlagAutoPilotCart = 0;
	CurrentCart = nullptr;

	if (P1 != nullptr)
		CharObj2Ptrs[0]->Powerups &= Powerups_Invincibility;

		DeleteObject_(TriggerOBJ);
		TriggerOBJHS_Delete();
		DeleteObject_(ChaoTP);
		Delete_Cart();
		fixTCCart();

	return DisableControl();
}

void EmeraldRadar_R() {

	if (TreasureHunting)
	{
		LoadPVM("KNU_EFF", &KNU_EFF_TEXLIST);
		LoadObject((LoadObj)2, 6, EmeraldRadarHud_Load_Load);

		if (CurrentCharacter != Characters_Knuckles)
		{
			KnuxCheck2 = 0; //fix Trial Mode Crash

			switch (CurrentLevel)
			{
			case LevelIDs_RedMountain:
				if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37) //If diggable emeralds, rand again.
				{
					do {
						Knuckles_SetRNG();
					} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37); 
				}
				break;
			case LevelIDs_LostWorld:
				if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 36) //If diggable emeralds, rand again.
				{
					do {
						Knuckles_SetRNG();
					} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37);
				}
				break;
			case LevelIDs_SkyDeck:
				if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 35) //If diggable emeralds, rand again.
				{
					do {
						Knuckles_SetRNG();
					} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 35);
				}
				break;
			}
		}
	}

	return;
}

int KnuxRadarEmeraldCheck() {  //trick the game to make it think we are playing Knuckles
	
	if (TreasureHunting)
		return Characters_Knuckles;
	else
		return CurrentCharacter;
}

//Set Emerald RNG when not Knuckles

void SetRNGKnuckles() {

	if (TreasureHunting && CurrentCharacter != Characters_Knuckles)
	{
		WriteData<1>((void*)0x416F06, 0x08);
		WriteData<1>((void*)0x4153E1, 0x08);
		WriteData<1>((void*)0x416f08, 0x74);
		WriteData<1>((void*)0x4153e3, 0x74);
	}
	
}

//restore original values
void RestoreRNGValueKnuckles() {

	WriteData<1>((void*)0x416F06, 0x03);
	WriteData<1>((void*)0x4153E1, 0x03);
	WriteData<1>((void*)0x416f08, 0x75);
	WriteData<1>((void*)0x4153e3, 0x75);
}

/*Trampoline PlayEmeraldGrabVoice_T(0x474f50, 0x474f55, PlayEmeraldGrabVoice_R);
//Play Custom voice when grabbing an emerald when not Knuckles.
void PlayEmeraldGrabVoice_R(ObjectMaster* a1) {

	ObjectMaster* CurChar = GetCharacterObject(0);
	if (CurChar != nullptr)
	{
		switch (CurChar->Data1->CharID)
		{
		case Characters_Sonic:
			if (KnuxCheck == 1)
				PlayVoice_R(1826);
			if (KnuxCheck == 2)
				PlayVoice_R(315);
			break;
		case Characters_Tails:
			if (KnuxCheck == 1)
				PlayVoice_R(1812);
			if (KnuxCheck == 2)
				PlayVoice_R(1456);
			break;
		case Characters_Amy:
			if (KnuxCheck == 1)
				PlayVoice_R(5020);
			if (KnuxCheck == 2)
				PlayVoice_R(1737);
			break;
		case Characters_Gamma:
			if (KnuxCheck == 1 || KnuxCheck == 2)
				PlayVoice_R(5023);
			break;
		case Characters_Big:
			if (KnuxCheck == 1)
				PlayVoice_R(5021);
			if (KnuxCheck == 2)
				PlayVoice_R(5022);
			break;
		}
	}

	ObjectFunc(origin, PlayEmeraldGrabVoice_T.Target());
	origin(a1);
}*/


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


void GammaBossesFixes() {

	if (CurrentCharacter == Characters_Gamma && CurrentLevel == LevelIDs_EggHornet)
		WriteJump((void*)0x572230, EggHornet_LoadWithTarget);

	return LoadCamFile(0, "0000");
}


int AmyCartImprovement() {
	if (CurrentCharacter == Characters_Amy) //trick the game to make it think we are playing Sonic.
		return Characters_Sonic;
	else
		return CurrentCharacter;
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

void FixRestartCheckPoint() {

	//Check if a CP has been grabbed
	if (!isCheckpointUsed && CurrentLevel != LevelIDs_LostWorld && (TreasureHunting || CurrentLevelLayout == Mission1_Variation || TPAmyVersion))
		isCheckpointUsed = true;

	return njColorBlendingMode(0, 8);
}


//Use "Load AnimalPickup" function to fix the start position when getting a variation of a character/stage. Not using StartRegisterPosition, as it's not dynamic.
void FixLayout_StartPosition_R() {

	if (!isCheckpointUsed) //don't change player position if a CP has been grabbed.
	{
		ObjectMaster* Play1 = GetCharacterObject(0);
		switch (CurrentLevel)
		{
		case LevelIDs_LostWorld:
			if (CurrentAct == 1 && TreasureHunting)
				PositionPlayer(0, 7482, -2622, 908);
			break;
		case LevelIDs_SpeedHighway:
			if (CurrentAct == 2 && TreasureHunting)
				PositionPlayer(0, -230, 150, -1740);
			break;
		case LevelIDs_SkyDeck:
			if (CurrentAct == 2 && TreasureHunting)
				PositionPlayer(0, 674, 207, 12);
			break;
		case LevelIDs_WindyValley: //Gamma version
			if (CurrentAct == 0 && CurrentLevelLayout == Mission1_Variation)
				PositionPlayer(0, -10, -102, -10);
			if (CurrentAct == 2 && Race)
				PositionPlayer(0, 1093, -158, -1254);
			break;
		case LevelIDs_TwinklePark: //Amy version
			if (CurrentAct == 1 && TPAmyVersion && !TPBigVersion)
				PositionPlayer(0, 723, 70, -358);
			if (CurrentAct == 1 && TPBigVersion && !TPAmyVersion)
				PositionPlayer(0, 230, 80, -538);
			break;
		case LevelIDs_FinalEgg: //Gamma version
			if (CurrentAct == 2 && FEGammaVersion)
				PositionPlayer(0, 46.5, -3240.6, -224.5);
			break;
		}
	}

	AnimalPickup_Load_();

	return;
}

void LoadTriggerObject() {

	if (CurrentLevel == LevelIDs_HotShelter && CurrentAct == 0)
		HotShelterSecretSwitch();

	if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 0 && CurrentCharacter == Characters_Big)
		LoadICTrigger();

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 2 && CurrentLevelLayout == Mission3_LostChao)
		LoadChaoTPTrigger();

	if (CurrentLevel == LevelIDs_Casinopolis && CurrentAct == 1 && CurrentLevelLayout == Mission3_LostChao)
		LoadTriggerCasinoChao();

	if (CurrentLevel == LevelIDs_SandHill && CurrentCharacter > Characters_Tails)
		LoadRemoveCart();
}

void Stages_Management() {

	WriteCall((void*)0x415556, DisableTimeStuff); //While result screen: avoid crash and add race result. (really important)
	Set_Zero();
	WriteCall((void*)0x413c9c, preventCutscene); //Prevent cutscene from playing after completing a stage (fix AI / Super Sonic crashes.)
	Set_BackRing();
	Race_Init();
	WriteCall((void*)0x415a3d, FixLayout_StartPosition_R); //Fix start position with different stage character version.
	WriteCall((void*)0x4bac10, FixRestartCheckPoint); //Fix checkpoint after editing player position.
	
	WriteCall((void*)0x4169e1, FixRestart_Stuff); //Delete Cart properly after a game over.
	WriteCall((void*)0x41676b, FixRestart_Stuff); 
}

