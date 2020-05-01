#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include "RandomHelpers.h"
#include "Trampoline.h"
#include "StageSettings.h"


extern bool RNGStages;
extern bool GetBackRing;
extern uint32_t TotalCount;
extern bool ChaoSpawn;
extern bool isPlayerInWaterSlide;
extern char GetCustomLayout;

extern char TimeSecCopy;
extern char TimeMinCopy;
extern char TimeFrameCopy;
extern int RingCopy;
extern bool LimitCustomFlag;

extern bool RandCongratsDone;
bool IceCapCutsceneSkip = false;
extern ObjectMaster* CurAI;
bool isCheckpointUsed = false;
extern ObjectMaster* TriggerOBJ;
extern ObjectMaster* TriggerHS;
extern ObjectMaster* ChaoTP;
ObjectMaster* CurrentCart = nullptr;
extern bool isZeroActive;
extern bool CasinoTails;


//While load result: "fix" game crash. (There is probably a better way to do this.), restore most of the value to 0 to avoid any conflict.
void DisableTimeStuff() {

	if (GameMode != GameModes_Trial && GameMode != GameModes_Mission && RNGStages)
		GameMode = GameModes_Adventure_Field; //fix game crash

	if (SelectedCharacter == 6) //Fix Super Sonic Story giving sonic layout
		LastStoryFlag = 1;
	else
		LastStoryFlag = 0;

	TimeThing = 0;

	if (CurrentLevel == LevelIDs_SandHill)
	{
		ResetValueWhileLevelResult();
		if (GameMode != GameModes_Trial && GameMode != GameModes_Mission && RNGStages)
			AddCustomFlag(); //Add a flag for story progression.
	}
	ringsPB += Rings; //total Rings credit stat

	if (!Race && CurrentCharacter == Characters_Tails)
		SetTailsRaceVictory();

	ObjectMaster* play1 = GetCharacterObject(0);
	ObjectMaster* play2 = GetCharacterObject(1);

	if (!Race && isAIAllowed && isAIActive && CurrentLevel != LevelIDs_TwinklePark) //Move AI to player 1 if we are not racing.
	{
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

			if (CurrentAI == Characters_Tails || play1->Data1->CharID == Characters_Tails)
			{
				SetTailsRaceVictory(); //Fix Tails AI victory animation
			}
			ForcePlayerAction(1, 19); //Force AI to Victory pose
			dword_3B2A304 = 0;
		}
	}

	if (Race && CurrentCharacter != Characters_Tails)
	{
		SetTailsRaceVictory();
		Tails_CheckRaceResult();
	}


	Race = false;
	return;
}

void ReleaseScoreTexture() {

	ResetValueWhileLevelResult();
	if (GameMode != GameModes_Trial && GameMode != GameModes_Mission && RNGStages)
		AddCustomFlag(); //Add a flag for story progression.

	njReleaseTexture(&SCORE_RESULT_TEXLIST);
}


void SetResultsCamera()
{
	switch (GetCharacter0ID())
	{
	case Characters_Sonic:
	case Characters_Tails:
		sub_469300((int*)0x919BF4, 3, 720);
		break;
	case Characters_Knuckles:
		sub_469300((int*)0x91A848, 3, 720);
		break;
	case Characters_Amy:
		sub_469300((int*)0x9196D0, 3, 720);
		break;
	case Characters_Gamma:
		sub_469300((int*)0x91A248, 3, 720);
		break;
	}
}


void __cdecl sub_461560()
{
	CharObj2* v3; // eax@20

	switch (CurrentLevel)
	{
	case LevelIDs_SpeedHighway:
		if (GetRaceWinnerPlayer() == 1)
		{
			SetResultsCamera();
			ResultVoiceFix();
			Load_DelayedSound_BGM(MusicIDs_RoundClear);
		}
		else
			Load_DelayedSound_Voice(225);
		if (GameMode != GameModes_Trial || byte_3B2A2F1 != 1)
			LoadObject(LoadObj_Data1, 3, sub_47D300);
		break;
	case LevelIDs_WindyValley:
	case LevelIDs_SkyDeck:
	case LevelIDs_IceCap:
	case LevelIDs_Casinopolis:
		if (sub_46A820())
		{
			if (sub_46A7F0() == 1)
				SetOpponentRaceVictory();
			else
				SetTailsRaceVictory();
		}
		if (GetRaceWinnerPlayer() == 1)
		{
			SetResultsCamera();
			ResultVoiceFix();
			Load_DelayedSound_BGM(MusicIDs_RoundClear);
		}
		else
			Load_DelayedSound_SFX(214);
		if (GameMode != GameModes_Trial || byte_3B2A2F1 != 1)
			LoadObject(LoadObj_Data1, 3, sub_47D300);
		break;
	default:
		SetTailsRaceVictory();
		if (CurrentLevel == LevelIDs_SandHill)
		{
			v3 = GetCharObj2(0);
			v3->PhysicsData.CollisionSize = 9;
			v3->PhysicsData.YOff = 4.5f;
		}
		SetResultsCamera();
		ResultVoiceFix();
		Load_DelayedSound_BGM(MusicIDs_RoundClear);
		break;
	}
}

void __cdecl sub_4141F0(ObjectMaster* obj)
{
	EntityData1* v1 = GetCharacterObject(0)->Data1;
	if (EntityData1Ptrs[1] && sub_46A820() && sub_46A7F0() == 1)
		v1 = EntityData1Ptrs[1];
	if (v1->Status & 3)
	{
		ForcePlayerAction(0, 19);
		switch (CurrentCharacter)
		{
		case Characters_Tails:
			sub_461560();
			break;
		case Characters_Gamma:
			if (GetCharacter0ID() == Characters_Gamma)
			{
				sub_469300((int*)0x91A248, 3, 720);
				switch (CurrentLevel)
				{
				case LevelIDs_EmeraldCoast:
					if (CurrentAct == 2 && CurrentMission == 5 || CurrentAct == 0 && CurrentMission == 1)
						Load_DelayedSound_Voice(1772);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_HotShelter:
					if (CurrentAct == 2 && CurrentMission == Mission1)
						Load_DelayedSound_Voice(1773);
					if (CurrentAct == 0 && CurrentMission == 5 && CurrentStageVersion == BigHS)
						Load_DelayedSound_Voice(1772);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_TwinklePark:
					if (CurrentAct == 1 && CurrentLevelLayout < 2 && CurrentStageVersion == BigTP)
						Load_DelayedSound_Voice(1772);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_RedMountain:
					if (CurrentAct == 1 && CurrentMission == Mission1_Variation)
						Load_DelayedSound_Voice(1774);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_WindyValley:
					if (CurrentAct == 0 & CurrentMission == Mission1_Variation)
						Load_DelayedSound_Voice(1775);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_IceCap:
					if (CurrentAct == 3 && CurrentMission == 5)
						Load_DelayedSound_Voice(1772);
					else
						Load_DelayedSound_Voice(1770);
					break;
				default:
					Load_DelayedSound_Voice(1770);
					break;
				}
			}
			else
			{
				SetResultsCamera();
				ResultVoiceFix();
			}
			break;
		default:
			SetResultsCamera();
			ResultVoiceFix();
			break;
		}
		sub_457D00();
		LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
		Load_DelayedSound_BGM(MusicIDs_RoundClear);
		CheckThingButThenDeleteObject(obj);
	}
}



void __cdecl LoadLevelResults_r()
{
	NJS_VECTOR a1; // [sp+0h] [bp-18h]@12
	NJS_VECTOR a2; // [sp+Ch] [bp-Ch]@12

	DisableController(0);
	PauseEnabled = 0;
	if (Race && RaceWinnerPlayer == 2 && GameMode < 9)
	{
		GameMode = GameModes_Adventure_ActionStg; //fix Softlock race
		TimeThing = 0;
	}
	else
	{
		DisableTimeStuff();
	}
	if (GameMode == GameModes_Mission)
		sub_5919E0();
	if (CurrentCharacter != Characters_Tails && GetCharacter0ID() == Characters_Tails)
		SetTailsRaceVictory();
	switch (CurrentCharacter)
	{
	case Characters_Tails:
		if (GetRaceWinnerPlayer() == 1)
			LoadObject((LoadObj)0, 3, sub_4141F0);
		else
		{
			ForcePlayerAction(0, 19);
			sub_461560();
			sub_457D00();
			LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
		}
		break;
	case Characters_Knuckles:
		ForcePlayerAction(0, 19);
		sub_457D00();
		LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
		SoundManager_Delete2();
		if ((CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel != LevelIDs_SandHill) || GetCharacter0ID() != Characters_Knuckles)
		{
			SetResultsCamera();
			Load_DelayedSound_SFX(0x5a8);
		}
		else
		{
			sub_469300((int*)0x91A848, 3, 720);
			Load_DelayedSound_SFX(0x5a5);
		}
		Load_DelayedSound_BGM(MusicIDs_RoundClear);
		break;
	case Characters_Amy:
		if (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel != LevelIDs_SandHill || CurrentLevelLayout >= 2)
			LoadObject((LoadObj)0, 3, sub_4141F0);
		else
		{
			ForcePlayerAction(0, 19);
			sub_457D00();
			LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
			SoundManager_Delete2();
			if (GetCharacter0ID() == Characters_Amy)
				Load_DelayedSound_Voice(1733);
			else
				ResultVoiceFix();
			Load_DelayedSound_BGM(MusicIDs_RoundClear);
		}
		break;
	case Characters_Big:
		ForcePlayerAction(0, 19);
		a2.x = -36.072899f;
		a2.y = 5.7132001f;
		a2.z = -1.5176001f;
		sub_43EC90(EntityData1Ptrs[0], &a2);
		a1 = EntityData1Ptrs[0]->CollisionInfo->CollisionArray->origin;
		stru_3B2C6DC = a1;
		njSubVector(&a1, &a2);
		stru_3B2C6D0 = a1;
		sub_437D20(sub_464B00, 1, 2);
		sub_457D00();
		LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
		if ((CurrentAct | (CurrentLevel << 8)) < LevelAndActIDs_Chaos0)
			SoundManager_Delete2();
		ResultVoiceFix();
		Load_DelayedSound_BGM(MusicIDs_RoundClear);
		break;
	default:
		LoadObject((LoadObj)0, 3, sub_4141F0);
		SoundManager_Delete2();
		break;
	}
}

void DeleteTriggerObject() {

	TriggerOBJHS_Delete();
	TriggerCasinoChao_Delete();
}


void RestorePuzzleBoxVanillaThing() {
	//Restore the Amy Check for puzzle box.
	WriteData<1>((void*)0x442249, 0xF);
	WriteData<1>((void*)0x44224A, 0x85);
	WriteData<1>((void*)0x44224B, 0xB3);
	WriteData<1>((void*)0x44224C, 0x0);
	WriteData<1>((void*)0x44224D, 0x0);
	WriteData<1>((void*)0x44224E, 0x0);
	return;
}

void ResetValueWhileLevelResult() {
	isZeroActive = false;
	LimitCustomFlag = false;
	isCheckpointUsed = false;
	isGameOver = false;
	SonicRand = 0;
	KnuxCheck = 0;
	KnuxCheck2 = 0; //fix trial crash
	ChaoSpawn = false;
	GetBackRing = false;
	TreasureHunting = false;
	CurrentStageVersion = Normal;
	isPlayerInWaterSlide = false;
	CasinoTails = false;
	isKnucklesVersion = false;
	isTailsVersion = false;
	isCheckpointUsed = false;

	RestoreRNGValueKnuckles();
	RestorePuzzleBoxVanillaThing();

	if (CurrentLevel == LevelIDs_PerfectChaos && CurrentCharacter != Characters_Sonic)
		CharObj2Ptrs[0]->Powerups &= Powerups_Invincibility;

	if (CurrentLevel != 0)
	{
		DeleteTriggerObject();
		DeleteObject_(ChaoTP);
		Delete_Cart();
		Chao_DeleteFiles();
	}
	fixTCCart();

	return;
}

void fixTCCart() {
	WriteData<1>((void*)0x798306, 0x85); //Restore original Functions
	WriteData<1>((void*)0x7983c4, 0x7C);

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

	if (CurrentLevel == LevelIDs_FinalEgg && CurrentStageVersion != AmyFE || CurrentLevel == LevelIDs_TwinklePark && !CurrentStageVersion != AmyTP) //don't load Zero if Sonic Layout
		return;

	isZeroActive = true;
	LoadPVM("EGGROB", &EGGROB_TEXLIST);
	CheckLoadZero();
}

void FixZeroSound() {

	if (CurrentCharacter != Characters_Amy && CurrentLevel != LevelIDs_Zero)
		return;
	else
		PlaySound(0x324, 0x0, 0, 0x0);
}

void FixZeroSound2() {

	if (CurrentCharacter != Characters_Amy && CurrentLevel != LevelIDs_Zero)
		return;
	else
		PlaySound(0x322, 0x0, 0, 0x0);
}

void FixZeroSound3() {

	if (CurrentCharacter != Characters_Amy && CurrentLevel != LevelIDs_Zero)
		return;
	else
		PlaySound(0x332, 0x0, 0, 0x0);
}



void Set_Zero() {
	//Zero Stuff
	WriteCall((void*)0x61d169, LoadZero); //Call Zero at Twinkle Park.
	WriteCall((void*)0x59a119, LoadZero); //Call Zero at Hot Shelter.
	WriteCall((void*)0x5ae104, LoadZero); //Call Zero at Final Egg.
	WriteCall((void*)0x4d2d12, FixZeroSound); 
	WriteCall((void*)0x4d31ce, FixZeroSound);
	WriteCall((void*)0x4d218c, FixZeroSound3);

	WriteData<5>((void*)0x4d380d, 0x90); //Remove a special Zero Sound.
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
	if (!CurrentCart)
	{
		SwapDelay = 0;
		FlagAutoPilotCart = 0; //fix that bullshit Twinkle Circuit thing.
		LoadPVM("OBJ_SHAREOBJ", &OBJ_SHAREOBJ_TEXLIST);
		CurrentCart = LoadObject((LoadObj)(15), 3, Cart_Main);
	}

	if (CurrentCart)
	{
		CurrentCart->Data1->Scale.y = 1; //Cart will spawn empty.

		switch (CurrentCharacter) //Set Color and Size depending on character
		{
		case Characters_Gamma:
			CurrentCart->Data1->Scale.x = 3;
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


void Delete_Cart()
{

	if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
			ForcePlayerAction(0, 0x18);

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0)
		return;

	FlagAutoPilotCart = 1;
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

	CurrentCart = nullptr;
}

void FixRestart_Stuff() //Prevent the game to crash if you restart while being in a custom cart, also reset other stuff.
{
	DisableTimeThing();
	DisableControl();

	ObjectMaster* P1 = GetCharacterObject(0);

	if (CurrentCart != nullptr)
		DeleteObject_(CurrentCart);

	FlagAutoPilotCart = 0;
	CurrentCart = nullptr;

	if (P1 != nullptr)
		CharObj2Ptrs[0]->Powerups &= Powerups_Invincibility;

	DeleteTriggerObject();
	DeleteObject_(ChaoTP);
	Delete_Cart();

	return;
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
			case LevelIDs_SpeedHighway:
				if (CurrentCharacter == Characters_Gamma && KnuxEmerald2 >= 48 && KnuxEmerald2 <= 53) //Gamma cannot break the trash.
				{
					do {
						Knuckles_SetRNG();
					} while (KnuxEmerald2 >= 48 && KnuxEmerald2 <= 53);
				}
				break;
			case LevelIDs_RedMountain:
				if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37) //If diggable emeralds, rand again.
				{
					do {
						Knuckles_SetRNG();
					} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37); 
				}
				break;
			case LevelIDs_LostWorld:
				if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37) //If diggable emeralds, rand again.
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

	return;
}

//restore original values
void RestoreRNGValueKnuckles() {

	WriteData<1>((void*)0x416F06, 0x03);
	WriteData<1>((void*)0x4153E1, 0x03);
	WriteData<1>((void*)0x416f08, 0x75);
	WriteData<1>((void*)0x4153e3, 0x75);

	return;
}

bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius) {
	return GetDistance(center, pos) <= radius;
}

int IsPlayerInsideSphere_(NJS_VECTOR* center, float radius) {
	for (uint8_t player = 0; player < 8; ++player) {
		if (!EntityData1Ptrs[player]) continue;

		NJS_VECTOR* pos = &EntityData1Ptrs[player]->Position;
		if (IsPointInsideSphere(center, pos, radius)) {
			return player + 1;
		}
	}

	return 0;
}

bool IsSpecificPlayerInSphere(NJS_VECTOR* center, float radius, uint8_t player) {
	return IsPlayerInsideSphere_(center, radius) == player + 1;
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




//Create an object so Gamma can hit some specific bosses.
CollisionData col = { 0, 0, 0x77, 0, 0x800400, {0, 0, 0}, { 6.0, 6.0, 0.0 }, 0, 0 };

void TargetableEntity(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1;

	if (data->Action == 0) {
		AllocateObjectData2(obj, obj->Data1);

		//if the scale is specified, temporary set the collision scale to it.
		if (data->Scale.x) {
			col.scale.x = data->Scale.x;
			Collision_Init(obj, &col, 1, 2u);
			col.scale.x = 6;
		}
		else {
			Collision_Init(obj, &col, 1, 2u);
		}

		data->Action = 1;
	}
	else {
		ObjectMaster* boss = (ObjectMaster*)obj->Data1->LoopData;

		if (!boss || !boss->Data1) {
			DeleteObject_(obj);
			return;
		}

		if (EntityData1Ptrs[0]->CharID != Characters_Gamma) 
			return;

		data->Position = boss->Data1->Position;
		if (CurrentLevel != LevelIDs_EggWalker)
			data->Position.y += 10;
		else
			data->Position.y += 45;


		if (OhNoImDead(obj->Data1, (ObjectData2*)obj->Data2))
		{
			DeleteObject_(obj);

			//if it is set, don't reload the target object
			if (data->CharID == 1) 
				return;

			ObjectMaster* target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
			target->Data1->LoopData = (Loop*)boss;
		}
		else
		{
			AddToCollisionList(data);
		}
	}
}

void TargetableEntitySmallOBJ(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1;

	if (data->Action == 0) {
		AllocateObjectData2(obj, obj->Data1);

		//if the scale is specified, temporary set the collision scale to it.
		if (data->Scale.x) {
			col.scale.x = data->Scale.x;
			Collision_Init(obj, &col, 1, 2u);
			col.scale.x = 10;
		}
		else {
			Collision_Init(obj, &col, 1, 2u);
		}

		data->Action = 1;
	}
	else {
		ObjectMaster* boss = (ObjectMaster*)obj->Data1->LoopData;

		if (!boss || !boss->Data1) {
			DeleteObject_(obj);
			return;
		}

		if (EntityData1Ptrs[0]->CharID != Characters_Gamma)
			return;

		data->Position = boss->Data1->Position;
		data->Position.y += 10;


		if (OhNoImDead(obj->Data1, (ObjectData2*)obj->Data2))
		{
			DeleteObject_(obj);

			//if it is set, don't reload the target object
			if (data->CharID == 1)
				return;

			ObjectMaster* target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntitySmallOBJ);
			target->Data1->LoopData = (Loop*)boss;
		}
		else
		{
			AddToCollisionList(data);
		}
	}
}



void TargetableEntity_RegularChara(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1;

	if (data->Action == 0) {
		AllocateObjectData2(obj, obj->Data1);

		//if the scale is specified, temporary set the collision scale to it.
		if (data->Scale.x) {
			col.scale.x = data->Scale.x;
			Collision_Init(obj, &col, 5, 2u);
			col.scale.x = 6;
		}
		else {
			Collision_Init(obj, &col, 5, 2u);
		}

		data->Action = 1;
	}
	else {
		ObjectMaster* boss = (ObjectMaster*)obj->Data1->LoopData;

		if (!boss || !boss->Data1) {
			DeleteObject_(obj);
			return;
		}

		if (EntityData1Ptrs[0]->CharID == Characters_Gamma) 
			return;

		data->Position = boss->Data1->Position;
		//data->Position.y += 10;

		if (OhNoImDead(obj->Data1, (ObjectData2*)obj->Data2))
		{
			DeleteObject_(obj);

			//if it is set, don't reload the target object
			if (data->CharID == 1) 
				return;

			ObjectMaster* target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity_RegularChara);
			target->Data1->LoopData = (Loop*)boss;
		}
		else
		{
			AddToCollisionList(data);
		}
	}
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
	if (!isCheckpointUsed && CurrentLevel != LevelIDs_LostWorld && CurrentLevel != LevelIDs_SkyDeck && (TreasureHunting || CurrentLevelLayout == Mission1_Variation || CurrentStageVersion != AmyTP))
		isCheckpointUsed = true;

	return njColorBlendingMode(0, 8);
}


//Use "Load AnimalPickup" function to fix the start position when getting a variation of a character/stage. Not using StartRegisterPosition, as it's not dynamic and already used for a different layout.
//Also used to call different Stuff.

void FixLayout_StartPosition_R() {

	if (!isCheckpointUsed || GetBackRing && CurrentLevelLayout >= 2) //don't change player position if a CP has been grabbed.
	{
		ObjectMaster* Play1 = GetCharacterObject(0);
		switch (CurrentLevel)
		{
		case LevelIDs_LostWorld:
			if (CurrentAct == 1 && (TreasureHunting || isKnucklesVersion))
				PositionPlayer(0, 7482, -2622, 908);
			break;
		case LevelIDs_SpeedHighway:
			if (CurrentAct == 2 && (TreasureHunting || isKnucklesVersion))
				PositionPlayer(0, -230, 150, -1740);
			break;
		case LevelIDs_SkyDeck:
			if (CurrentAct == 2 && (TreasureHunting || isKnucklesVersion))
				PositionPlayer(0, 674, 207, 12);
			break;
		case LevelIDs_WindyValley: //Gamma version
			if (CurrentAct == 0 && CurrentLevelLayout == Mission1_Variation)
				PositionPlayer(0, -10, -102, -10);
			if (CurrentAct == 2 && (Race || isTailsVersion))
				PositionPlayer(0, 1093, -158, -1254);
			break;
		case LevelIDs_TwinklePark: //Amy version
			if (CurrentAct == 1 && CurrentStageVersion == AmyTP)
				PositionPlayer(0, 723, 70, -358);
			if (CurrentAct == 1 && CurrentStageVersion == BigTP)
				PositionPlayer(0, 230, 80, -538);
			break;
		case LevelIDs_IceCap: //Race
			if (CurrentAct == 2 && CurrentCharacter <= Characters_Tails)
				PositionPlayer(0, 120, 375, -40);
			break;
		case LevelIDs_FinalEgg: //Gamma version
			if (CurrentAct == 2 && CurrentStageVersion == GammaFE)
				PositionPlayer(0, 46.5, -3240.6, -224.5);
			break;
		}
	}

	
	if (GetBackRing && CurrentLevelLayout >= 2)
	{
		Rings = RingCopy;
		TimeSeconds = TimeSecCopy;
		TimeMinutes = TimeMinCopy;
		TimeFrames = TimeFrameCopy;
		if (CurrentStageVersion == AmyFE| isTailsVersion || CurrentStageVersion == TailsSH)
			Lives++;
		GameMode = GameModes_Adventure_ActionStg;
		GetBackRing = false;
	}

	if (GameMode != 9 && GameMode != 10 && CurrentLevel < LevelIDs_StationSquare && CurrentLevel > LevelIDs_Past)
		GameMode = GameModes_Adventure_ActionStg; //force gamemode to 4 to fix the restart.

	FixRestart_Stuff();
	AnimalPickup_Load_();

	return;
}

void LoadTriggerObject() {

	if (CurrentLevel == LevelIDs_HotShelter && CurrentAct == 0)
		HotShelterSecretSwitch();

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 2 && CurrentLevelLayout == Mission3_LostChao)
		LoadChaoTPTrigger();

	if (CurrentLevel == LevelIDs_SandHill && CurrentCharacter > Characters_Tails)
		LoadRemoveCart();
}


void Stages_Management() {

	WriteJump(LoadLevelResults, LoadLevelResults_r); 
	WriteCall((void*)0x42af59, ReleaseScoreTexture);

	Set_Zero();
	WriteCall((void*)0x413c9c, preventCutscene); //Prevent cutscene from playing after completing a stage (fix AI / Super Sonic crashes.)
	Set_BackRing();
	Race_Init();
	WriteCall((void*)0x415a3d, FixLayout_StartPosition_R); //Fix start position with different stage character version.

	WriteCall((void*)0x4bac10, FixRestartCheckPoint); //Fix checkpoint after editing player position.
	WriteCall((void*)0x4169e1, FixRestart_Stuff); //Delete Cart properly after a game over.
	WriteCall((void*)0x41676b, FixRestart_Stuff); 
}

