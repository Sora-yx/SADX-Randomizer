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
extern char TimeSecCopy;
extern char TimeMinCopy;
extern char TimeFrameCopy;
extern int RingCopy;
bool isZeroActive;


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

	if (CurrentLevel == LevelIDs_FinalEgg && CurrentStageVersion != AmyVersion || CurrentLevel == LevelIDs_TwinklePark && CurrentStageVersion != AmyVersion) //don't load Zero if Sonic Layout
		return;

	isZeroActive = true;
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
	WriteData<2>((void*)0x4212c9, 0x90); //Load Zero Texture for any character.
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
	njReleaseTexture(&KNU_EFF_TEXLIST);
	WriteData<1>((void*)0x416F06, 0x03);
	WriteData<1>((void*)0x4153E1, 0x03);
	WriteData<1>((void*)0x416f08, 0x75);
	WriteData<1>((void*)0x4153e3, 0x75);

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

		if (CurrentLevel == LevelIDs_Zero && boss->Data1->Action == 9)
			return;

		if (!boss || !boss->Data1) {
			CheckThingButThenDeleteObject(obj);
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
			CheckThingButThenDeleteObject(obj);

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



void preventCutscene() {

	switch (CurrentLevel)
	{
	case LevelIDs_RedMountain:
		if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
			return;
		break;
	case LevelIDs_EmeraldCoast:
		if (CurrentCharacter == Characters_Tails)
			return;
		break;
	case LevelIDs_HotShelter:
		if (CurrentCharacter == Characters_Amy && CurrentAct == 1)
			return;
		break;
	}

	return GetLevelCutscene();
}


SetLevelPosition PlayerStartPosition[52]{

	{ AmyVersion, LevelAndActIDs_HedgehogHammer, { -55, 0, -31 }, 0 },
	{ SonicVersion, LevelAndActIDs_EmeraldCoast1, { -9, 16, 4 }, 0x6000},
	{ SonicVersion, LevelAndActIDs_EmeraldCoast2, { -986.5f, 1145, -2856 }, 0x4000 },
	{ BigVersion, LevelAndActIDs_EmeraldCoast3, { 6090, 30, 1000 }, 0 },
	{ GammaVersion, LevelAndActIDs_WindyValley1, { -10, -102, -10 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley1, { 42, 380, -20 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley2, { 1096, 205, -1251 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley3, { -2000, 1770, -985 }, 0x4000 },
	{ TailsVersion, LevelAndActIDs_WindyValley3, { 1093, -158, -1254 }, 0 },
	{ SonicVersion, LevelAndActIDs_TwinklePark1, { -2000, 1770, -985 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, { 520, 975, 1620 }, 0xC000 },
	{ AmyVersion, LevelAndActIDs_TwinklePark2, { 723, 70, -358 }, 0xC000 },
	{ BigVersion, LevelAndActIDs_TwinklePark2, { 230, 80, -538 }, 0xC000 },
	{ AmyVersion, LevelAndActIDs_TwinklePark3, { 75, 0, -390 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway1, { -673, -10, 5 }, 0 },
	{ TailsVersion, LevelAndActIDs_SpeedHighway1, { -673, -10, 5 }, 0 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway2, { -50, 42, 0 }, 0 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway3, { 72, 26, 192 }, 0xC000 },
	{ KnucklesVersion, LevelAndActIDs_SpeedHighway3, { -230, 150, -1740 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_RedMountain1, { 18, 36, 636 }, 0 },
	{ SonicVersion, LevelAndActIDs_RedMountain2, { -78, 831, 1919 }, 0 },
	{ GammaVersion, LevelAndActIDs_RedMountain2, { -78, 831, 1919 }, 0 },
	{ KnucklesVersion, LevelAndActIDs_RedMountain3, { -3147, 764, -1358 }, 0xFFFFC000 },
	{ SonicVersion, LevelAndActIDs_SkyDeck1, {0, -387.625, 379.5}, 270},
	{ TailsVersion, LevelAndActIDs_SkyDeck1, {0, -387.625, 379.5}, 270},
	{ SonicVersion, LevelAndActIDs_SkyDeck2, { 327, -74, 2535 }, 0 },
	{ SonicVersion, LevelAndActIDs_SkyDeck3, { -696, -86, 135 }, 0 },
	{ KnucklesVersion, LevelAndActIDs_SkyDeck3, { 674, 207, 12 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_LostWorld1, { -264, 73, -168 }, 0 },
	{ SonicVersion, LevelAndActIDs_LostWorld2, { 220, 73, -1423 }, 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_LostWorld2, { 7482, -2622, 908 }, 0 },
	{ SonicVersion, LevelAndActIDs_LostWorld3,  { 270, 10, 0 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap1, { 1580, 84, 1074 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap2, { 1060, 336, 280 }, 0 },
	{ SonicVersion, LevelAndActIDs_IceCap3, { 120, 375, -40 }, 0x8800 },
	{ TailsVersion, LevelAndActIDs_IceCap3, { 120, 375, -40 }, 0x8800 },
	{ BigVersion, LevelAndActIDs_IceCap4, { 1260, 224, -38 }, 0 },
	{ SonicVersion, LevelAndActIDs_Casinopolis1, 0, { 0 }, 0 },
	{ KnucklesVersion, LevelAndActIDs_Casinopolis1, 361, 380, -40, 0x8000 },
	{ SonicVersion, LevelAndActIDs_Casinopolis2, { 19, -1695, 2850 }, 0 },
	{ TailsVersion, LevelAndActIDs_Casinopolis2, { 19, -1695, 2850 }, 0 },
	{ SonicVersion, LevelAndActIDs_Casinopolis3, { 137, 35, 64 }, 0 },
	{ SonicVersion, LevelAndActIDs_Casinopolis4, { -430, -205, 100 }, 0 },
	{ SonicVersion, LevelAndActIDs_FinalEgg1, { 170, -165, 490 }, 0 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, 2945.652344, 5589.605469, -2211.165039, -1.681558157E-44 + 0x4000 },
	{ SonicVersion, LevelAndActIDs_FinalEgg2, { 1060, 595, -383 }, 0xC000 },
	{ SonicVersion, LevelAndActIDs_FinalEgg3, { 1071.7f, 240, -518 }, 0x8000 },
	{ GammaVersion, LevelAndActIDs_FinalEgg3, 1939, -3174.049561, -128, 0x8000 }, 
	{ AmyVersion, LevelAndActIDs_HotShelter1, 716.4085693, 677.8605957, -2952.347412, -1.681558157E-44 + 0xC000 },
	{ BigVersion, LevelAndActIDs_HotShelter1, -278.8718262, 80, -499.0888367, 0x8000 }, 
	{ AmyVersion, LevelAndActIDs_HotShelter2, 716.4085693, 677.8605957, -2952.347412, -1.681558157E-44 + 0xC000 }, 
	{ GammaVersion, LevelAndActIDs_HotShelter3, 2.01, 3221, -3136, 0x8000 },
};



Trampoline MovePlayerToStartPoint_T((int)MovePlayerToStartPoint, (int)MovePlayerToStartPoint + 0x5, MovePlayerToStartPoint_R);

void MovePlayerToStartPoint_R(EntityData1* data) {

	uint16_t levelact = (((short)CurrentLevel) << 8) | CurrentAct;

	if (GetBackRing && CurrentMission >= Mission2_100Rings)
	{
		Rings = RingCopy;
		TimeSeconds = TimeSecCopy;
		TimeMinutes = TimeMinCopy;
		TimeFrames = TimeFrameCopy;
		if (CurrentStageVersion == AmyVersion && CurrentLevel == LevelIDs_FinalEgg || isTailsVersion || CurrentStageVersion == TailsVersion && CurrentLevel == LevelIDs_SpeedHighway)
			Lives++;
		ResetRestartData();
		ResetGravity();
		GameMode = GameModes_Adventure_ActionStg;
		GetBackRing = false;
	}

	if (GameMode != 9 && GameMode != 10 && CurrentLevel < LevelIDs_StationSquare && CurrentLevel > LevelIDs_Past)
		GameMode = GameModes_Adventure_ActionStg; //force gamemode to 4 to fix the restart.

	FixRestart_Stuff();

	if (RestartLevel.Frame == 0 || GetBackRing && CurrentMission >= 2) //don't change player position if a CP has been grabbed.
	{
		for (uint8_t i = 0; i < LengthOfArray(PlayerStartPosition); i++)
		{
			if (levelact == PlayerStartPosition[i].LevelID && CurrentStageVersion == PlayerStartPosition[i].version)
			{
				EntityData1Ptrs[0]->Position = PlayerStartPosition[i].Position;
				EntityData1Ptrs[0]->Rotation.y = PlayerStartPosition[i].YRot;
				return;
			}
		}
	}


	FunctionPointer(void, original, (EntityData1 * PlayerPos), MovePlayerToStartPoint_T.Target());
	return original(data);	
}



void Stages_Management() {

	WriteJump(LoadLevelResults, LoadLevelResults_r); 
	WriteCall((void*)0x42af59, ReleaseScoreTexture);

	Set_Zero();
	WriteCall((void*)0x413c9c, preventCutscene); //Prevent cutscene from playing after completing a stage (fix AI / Super Sonic crashes.)
	Set_BackRing();
	Race_Init();
	//WriteCall((void*)0x415a3d, FixLayout_StartPosition_R); //Fix start position with different stage character version.

	//WriteCall((void*)0x4bac10, FixRestartCheckPoint); //Fix checkpoint after editing player position.
	WriteCall((void*)0x4169e1, FixRestart_Stuff); //Delete Cart properly after a game over.
	WriteCall((void*)0x41676b, FixRestart_Stuff); 
}

