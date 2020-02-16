#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include "RandomHelpers.h"
#include "Trampoline.h"
#include "StageSettings.h"


int RingCopy = 0; //Backring
char TimeSecCopy = 0;
char TimeMinCopy = 0;
char TimeFrameCopy = 0;
bool GetBackRing = false;
extern char GetCustomLayout;
extern bool ChaoSpawn;



//back ring Model and Display Stuff
extern NJS_MODEL_SADX model_0;

extern NJS_OBJECT object_GoalRing;

extern NJS_TEXNAME GoalRingTexNames[4];

extern NJS_TEXLIST GoalRingTextures;

FunctionPointer(void, sub_408530, (NJS_OBJECT*), 0x408530);

void BackRingObj_Display(ObjectMaster* obj) {
	if (!MissedFrames) {
		njSetTexture(&GoalRingTextures);
		njPushMatrix(nullptr);
		njTranslateV(nullptr, &obj->Data1->Position);
		int yrot = obj->Data1->Rotation.y;
		if (yrot)
			njRotateY(nullptr, yrot);		
		sub_408530(&object_GoalRing);
	
		njPopMatrix(1);
	}
}

//ran every UNpaused frame
void BackRingObj_Main(ObjectMaster* obj) {

	if (!ClipSetObject(obj)) { //delete the object if we're too far away

		EntityData1* v1 = obj->Data1;
		LoadPVM("textures\\GOALRING", &GoalRingTextures);

		//Hit
		if (IsPlayerInsideSphere(&v1->Position, 42) && obj->Data1->Action == 0)
		{
			if (CurrentLevelLayout >= Mission2_100Rings)
			{
				GetBackRing = true;
				RingCopy = Rings;
				TimeSecCopy = TimeSeconds;
				TimeMinCopy = TimeMinutes;
				TimeFrameCopy = TimeFrames;
				PlayVoice_R(5001); //back ring hit SFX
				ObjectMaster* play1 = GetCharacterObject(0);
				play1->Data1->Action = 0;
				play1->Data1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);

				if (++obj->Data1->Index == 3)
				{
					Delete_Cart();
					ScreenFade_Timer = 50;
					short sVar1;
					sVar1 = ScreenFade_RunActive();
					ChaoSpawn = false;
					GameState = 0xc;
					obj->Data1->Action = 1;

					return;
				}
			}
			else
			{
				LoadLevelResults();
				obj->Data1->Action = 1;
				return;
			}

		}

		BackRingObj_Display(obj); //run the display on unpaused frames
	}
}


Trampoline Capsule_Load_T(0x46b170, 0x46b177, CheckLoadCapsule_r);

//Replace the capsule according to the character and the mission.
void __cdecl CheckLoadCapsule_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation)
	{
		switch (CurrentCharacter)
		{
		case Characters_Amy:
			a1->Data1->Position.y += 37;
			a1->MainSub = Balloon_Main;
			Balloon_Main(a1);
			return;
			break;
		case Characters_Big:
			if (Race && CurrentLevel == LevelIDs_SkyDeck) //Force capsule here because this game is funny and let you win early if froggy spawns here for no reason.
			{
				ObjectFunc(origin, Capsule_Load_T.Target());
				origin(a1);
			}
			else
			{
				LoadPVM("big_kaeru", &big_kaeru_TEXLIST);
				a1->Data1->Position.y += 20;
				a1->MainSub = OFrog;
				OFrog(a1);
			}
			return;
			break;
		}
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		a1->Data1->Rotation.z = 15000;
		a1->Data1->Position.y += 38;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		a1->Data1->Rotation.x = 0xC000;

		return;
	}

	//call original function (Capsule.)
	ObjectFunc(origin, Capsule_Load_T.Target());
	origin(a1);
}

Trampoline Froggy_Load_T(0x4fa320, 0x4fa325, CheckLoadFroggy_r);
//Check the current mission and replace Froggy with Back Ring.
void __cdecl CheckLoadFroggy_r(ObjectMaster* a1) {

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		a1->Data1->Rotation.z = 15000;
		a1->Data1->Position.y += 28;
		a1->Data1->Rotation.x = 0xC000;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		return;
	}

	if (CurrentLevelLayout <= Mission1_Variation)
	{
		ObjectFunc(origin, Froggy_Load_T.Target());
		origin(a1);
	}
}

Trampoline Balloon_Load_T(0x7a21c0, 0x7a21c6, CheckLoadBalloon_r);
//Check the current mission and replace Balloon with Back Ring.
void __cdecl CheckLoadBalloon_r(ObjectMaster* a1) {

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		a1->Data1->Rotation.z = 15000;
		a1->Data1->Position.y += 0;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		a1->Data1->Rotation.x = 0xC000;
		return;
	}

	if (CurrentLevelLayout <= Mission1_Variation)
	{
		ObjectFunc(origin, Balloon_Load_T.Target());
		origin(a1);
	}
}

Trampoline CasinoEmerald_Load_T(0x5dd0a0, 0x5dd0a6, CheckLoadCasinoEmerald_r);

//Check the current mission and replace the capsule with a different object.
void __cdecl CheckLoadCasinoEmerald_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation)
	{
		switch (CurrentCharacter)
		{
		case Characters_Amy:
			a1->Data1->Position.y += 37;
			a1->MainSub = Balloon_Main;
			Balloon_Main(a1);
			return;
			break;
		case Characters_Big:
			LoadPVM("big_kaeru", &big_kaeru_TEXLIST);
			a1->Data1->Position.y += 20;
			a1->MainSub = OFrog;
			OFrog(a1);
			return;
			break;
		}
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		a1->Data1->Rotation.z = 15000;
		a1->Data1->Position.y += 32;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		a1->Data1->Rotation.x = 0xC000;

		return;
	}

	//call original function (Emerald.)
	ObjectFunc(origin, CasinoEmerald_Load_T.Target());
	origin(a1);
}

Trampoline WVEmerald_Load_T(0x4df3b0, 0x4df3b6, CheckLoadWVEmerald_r);

//Check the current mission and replace the capsule with a different object.
void __cdecl CheckLoadWVEmerald_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation)
	{
		switch (CurrentCharacter)
		{
		case Characters_Amy:
			a1->Data1->Position.y += 37;
			a1->MainSub = Balloon_Main;
			Balloon_Main(a1);
			return;
			break;
		case Characters_Big:
			LoadPVM("big_kaeru", &big_kaeru_TEXLIST);
			a1->Data1->Position.y += 20;
			a1->MainSub = OFrog;
			OFrog(a1);
			return;
			break;
		}
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		a1->Data1->Rotation.z = 15000;
		a1->Data1->Position.y += 32;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		a1->Data1->Rotation.x = 0xC000;

		return;
	}

	//call original function (Emerald.)
	ObjectFunc(origin, WVEmerald_Load_T.Target());
	origin(a1);
}

Trampoline ICEmerald_Load_T(0x4ecfa0, 0x4ecfa6, CheckLoadICEmerald_r);

//Check the current mission and replace the capsule with a different object.
void __cdecl CheckLoadICEmerald_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation)
	{
		switch (CurrentCharacter)
		{
		case Characters_Amy:
			a1->Data1->Position.y += 37;
			a1->MainSub = Balloon_Main;
			Balloon_Main(a1);
			return;
			break;
		case Characters_Big:
			LoadPVM("big_kaeru", &big_kaeru_TEXLIST);
			a1->Data1->Position.y += 20;
			a1->MainSub = OFrog;
			OFrog(a1);
			return;
			break;
		}
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		a1->Data1->Rotation.z = 15000;
		a1->Data1->Position.y += 32;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		a1->Data1->Rotation.x = 0xC000;

		return;
	}

	//call original function (Emerald.)
	ObjectFunc(origin, ICEmerald_Load_T.Target());
	origin(a1);
}

void Set_BackRing() {
	//WriteCall((void*)0x414859, ResetTime_R); //prevent the game to reset the timer if you hit the back ring.
	//WriteCall((void*)0x44ee0a, ResetTime_R2); //prevent the game to reset the timer if you hit the back ring.
	//WriteCall((void*)0x44ee0f, GetRings_R); //prevent the game to reset the rings
	//WriteCall((void*)0x416f41, Set0Rings_R); //prevent the game to reset the rings	
	//WriteCall((void*)0x417a30, Set0Rings_R); //prevent the game to reset the rings

	WriteData((ObjectFuncPtr*)0x4FA050, CheckLoadCapsule_r); // crashed plane in Emerald Coast
	WriteData((ObjectFuncPtr*)0x4DF3F0, CheckLoadCapsule_r); // Chaos Emerald in Windy Valley
	WriteData((ObjectFuncPtr*)0x5DD0E0, CheckLoadCapsule_r); // Chaos Emerald in Casinopolis
	WriteData((ObjectFuncPtr*)0x4ECFE0, CheckLoadCapsule_r); // Chaos Emerald in Ice Cap
	WriteData((ObjectFuncPtr*)0x7B0DD3, CheckLoadCapsule_r); // ending of Lost World
	WriteData((ObjectFuncPtr*)0x5B2523, CheckLoadCapsule_r); // ending of Final Egg

}