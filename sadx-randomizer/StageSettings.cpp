#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include "RandomHelpers.h"
#include "Trampoline.h"
#include "StageSettings.h"

extern uint32_t TotalCount;
extern bool ChaoSpawn;
extern char GetCustomLayout;
bool isCheckpointUsed = false;
extern char TimeSecCopy;
extern char TimeMinCopy;
extern char TimeFrameCopy;
extern int RingCopy;
bool isZeroActive;


void LoadLevelFiles_R() {

	if (CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_HotShelter)
	{
		CurrentMission = randomizedSets[levelCount].SA2Mission;
		CurrentStageVersion = randomizedSets[levelCount].Layout;
	}

	return LoadLevelFiles();
}

void DeleteTriggerObject() {

	TriggerOBJHS_Delete();
	TriggerCasinoChao_Delete();
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

	if (CurrentLevel == LevelIDs_FinalEgg && CurrentStageVersion != AmyVersion || CurrentLevel == LevelIDs_TwinklePark && !CurrentStageVersion != AmyVersion) //don't load Zero if Sonic Layout
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


void EmeraldRadar_R() {

	if (CurrentStageVersion == KnucklesVersion)
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
	
	if (CurrentStageVersion == KnucklesVersion)
		return Characters_Knuckles;
	else
		return CurrentCharacter;
}

//Set Emerald RNG when not Knuckles

void SetRNGKnuckles() {

	if (CurrentStageVersion == KnucklesVersion && CurrentCharacter != Characters_Knuckles)
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
	if (!isCheckpointUsed && CurrentLevel != LevelIDs_LostWorld && CurrentLevel != LevelIDs_SkyDeck && (CurrentStageVersion == KnucklesVersion || CurrentStageVersion != AmyVersion))
		isCheckpointUsed = true;

	return njColorBlendingMode(0, 8);
}


//Use "Load AnimalPickup" function to fix the start position when getting a variation of a character/stage. Not using StartRegisterPosition, as it's not dynamic and already used for a different layout.
//Also used to call different Stuff.

void FixLayout_StartPosition_R() {

	if (!isCheckpointUsed || GetBackRing && CurrentMission >= 2) //don't change player position if a CP has been grabbed.
	{
		ObjectMaster* Play1 = GetCharacterObject(0);
		switch (CurrentLevel)
		{
		case LevelIDs_LostWorld:
			if (CurrentAct == 1 && (CurrentStageVersion == KnucklesVersion || isKnucklesVersion))
				PositionPlayer(0, 7482, -2622, 908);
			break;
		case LevelIDs_SpeedHighway:
			if (CurrentAct == 2 && (CurrentStageVersion == KnucklesVersion || isKnucklesVersion))
				PositionPlayer(0, -230, 150, -1740);
			break;
		case LevelIDs_SkyDeck:
			if (CurrentAct == 2 && (CurrentStageVersion == KnucklesVersion || isKnucklesVersion))
				PositionPlayer(0, 674, 207, 12);
			break;
		case LevelIDs_WindyValley: //Gamma version
			if (CurrentAct == 0 && CurrentStageVersion == GammaVersion)
				PositionPlayer(0, -10, -102, -10);
			if (CurrentAct == 2 && (Race || isTailsVersion))
				PositionPlayer(0, 1093, -158, -1254);
			break;
		case LevelIDs_TwinklePark: //Amy version
			if (CurrentAct == 1 && CurrentStageVersion == AmyVersion)
				PositionPlayer(0, 723, 70, -358);
			if (CurrentAct == 1 && CurrentStageVersion == BigVersion)
				PositionPlayer(0, 230, 80, -538);
			break;
		case LevelIDs_IceCap: //Race
			if (CurrentAct == 2 && CurrentCharacter <= Characters_Tails)
				PositionPlayer(0, 120, 375, -40);
			break;
		case LevelIDs_FinalEgg: //Gamma version
			if (CurrentAct == 2 && CurrentStageVersion == GammaVersion)
				PositionPlayer(0, 46.5, -3240.6, -224.5);
			break;
		}
	}

	
	if (GetBackRing && CurrentMission >= Mission2_100Rings)
	{
		Rings = RingCopy;
		TimeSeconds = TimeSecCopy;
		TimeMinutes = TimeMinCopy;
		TimeFrames = TimeFrameCopy;
		if (CurrentStageVersion == AmyVersion && CurrentLevel == LevelIDs_FinalEgg || isTailsVersion || CurrentStageVersion == TailsVersion && CurrentLevel == LevelIDs_SpeedHighway)
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

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 2 && CurrentMission == Mission3_LostChao)
		LoadChaoTPTrigger();

	if (CurrentLevel == LevelIDs_SandHill && CurrentCharacter > Characters_Tails)
		LoadRemoveCart();
}


void Stages_Management() {

	WriteCall((void*)0x4152c9, LoadLevelFiles_R);
	WriteCall((void*)0x415308, LoadLevelFiles_R);

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

