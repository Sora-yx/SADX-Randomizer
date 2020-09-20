#include "stdafx.h"
#include <fstream>

bool isZeroActive;


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

	if (CurrentStageVersion == KnucklesVersion && CurrentMission < Mission2_100Rings)
	{
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
	
	if (CurrentStageVersion == KnucklesVersion && CurrentMission < Mission2_100Rings)
		return Characters_Knuckles;

	return 8; //Doesn't exist so the game won't load anything
}

//Set Emerald RNG when not Knuckles

void SetRNGKnuckles() {

	if (CurrentMission < Mission2_100Rings && CurrentStageVersion == KnucklesVersion && CurrentCharacter != Characters_Knuckles)
	{
		LoadPVM("KNU_EFF", &KNU_EFF_TEXLIST);
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

Trampoline KnucklesHint_Main_t((int)KnucklesHint_Main, (int)KnucklesHint_Main + 0x7, KnucklesHintMain_r);

void KnucklesHintMain_r(ObjectMaster* obj) {

	if (CurrentMission < Mission2_100Rings)
	{
		ObjectFunc(origin, KnucklesHint_Main_t.Target());
		origin(obj);
	}

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

	//CustomFlag++;
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

	if (RNGStages) {
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
	}

	return GetLevelCutscene();
}



void Stages_Management() {

	WriteJump(LoadLevelResults, LoadLevelResults_r); 

	Set_Zero();
	WriteCall((void*)0x413c9c, preventCutscene); //Prevent cutscene from playing after completing a stage (fix AI / Super Sonic crashes.)
	Set_BackRing();
	Race_Init();
	WriteCall((void*)0x4169e1, FixRestart_Stuff); //Delete Cart properly after a game over.
	WriteCall((void*)0x41676b, FixRestart_Stuff); 
}

