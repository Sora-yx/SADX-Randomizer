#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include "RandomHelpers.h"
#include "Trampoline.h"
#include "StageSettings.h"


//Back Ring Main Page, this is where the current goal of the stage is swapped with back ring, froggy, balloon etc. depending on the character.
//This is also where the race result are checked if the player 1 lose.

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


bool isBackRingTextureLoaded = false;

//return the current back ring rotation needed for a good display IG
Sint32 GetBackRing_Rotation() {

	Sint32 Yrot = 0;
	int CurAct = CurrentAct;
	
	switch (CurrentLevel)
	{
	case LevelIDs_EmeraldCoast:
		if (CurrentAct == 1)
			Yrot = 19000;
		if (CurAct == 2)
			Yrot = 0; 
		break;
	case LevelIDs_WindyValley:
		if (CurAct == 2)
			Yrot = 0x8000;
		break;
	case LevelIDs_Casinopolis:
		if (CurAct == 0)
			Yrot = 0x8000;
		if (CurAct == 1)
			Yrot = 0x8000;
		break;
	case LevelIDs_IceCap:
		if (CurAct == 3)
			Yrot = 20000;
		if (CurAct == 2)
			Yrot = 10000;
		break;
	case LevelIDs_TwinklePark:
		if (CurAct == 1 && !TPAmyVersion && !TPBigVersion)
			Yrot = 0;
		if (CurAct == 1 && TPBigVersion && !TPAmyVersion)
			Yrot = 20000;
		if (CurAct == 1 && !TPBigVersion && TPAmyVersion)
			Yrot = 10000;
		break;
	case LevelIDs_SpeedHighway:
		if (CurAct == 0)
			Yrot = 15000;
		if (CurAct == 2)
			Yrot = 0x8000;
		break;
	case LevelIDs_RedMountain:
		if (CurAct == 1)
			Yrot = 10000;
		if (CurAct == 2)
			Yrot = 0x8000;
		break;
	case LevelIDs_SkyDeck:
		if (CurAct == 0)
			Yrot = 0x8000;
		if (CurAct == 2)
			Yrot = 18000;
		break;
	case LevelIDs_LostWorld:
		if (CurAct == 1)
			Yrot = 0x8000;
		if (CurAct == 2)
			Yrot = 17000;
		break;
	case LevelIDs_FinalEgg:
		if (CurAct == 2)
		{
			if (!FEGammaVersion) //Sonic Version
				Yrot = 0x8000;
			else //Gamma Version
				Yrot = 0x8000;
		}
		if (CurAct == 0 && FEAmyVersion)
			Yrot = 17000;
		break;
	case LevelIDs_HotShelter:
		if (CurAct == 2)
			Yrot = 17000;
		if (CurAct == 1 && HSAmyVersion)
			Yrot = 17000;
		if (CurAct == 0 && HSBigVersion)
			Yrot = 18000;
		break;
	}

	return Yrot;
}

void BackRingObj_Display(ObjectMaster* obj) {
	if (!MissedFrames && isBackRingTextureLoaded) {
		njSetTexture(&GoalRingTextures);
		njPushMatrix(nullptr);
		njTranslateV(nullptr, &obj->Data1->Position);
		int yrot = obj->Data1->Rotation.y;
		yrot = GetBackRing_Rotation();
		if (yrot)
			njRotateY(nullptr, yrot);

		sub_408530(&object_GoalRing);
		njPopMatrix(1);
	}
}

extern ObjectMaster* AIRaceOBJ;
void ChaoObj_Delete(ObjectMaster* a1);

//ran every UNpaused frame
void BackRingObj_Main(ObjectMaster* obj) {

	if (!ClipSetObject(obj)) { //delete the object if we're too far away
		ObjectMaster* play1 = GetCharacterObject(0);
		ObjectMaster* play2 = GetCharacterObject(1);
		EntityData1* v1 = obj->Data1;

		LoadPVM("textures\\BACKRING", &GoalRingTextures);
		obj->Data1->Rotation.x = -1000;
		obj->Data1->Rotation.z = -1000;
		obj->Data1->Rotation.y = -1000;
		isBackRingTextureLoaded = true;

			if (IsPlayerInsideSphere(&v1->Position, 42) && obj->Data1->Action == 0)
			{
				if (CurrentLevelLayout == Mission2_100Rings && Rings < 100 || CurrentLevelLayout == Mission3_LostChao)
				{
					isBackRingTextureLoaded = false;
					GetBackRing = true;
					DisableControl();
					DisablePause();
					RingCopy = Rings;
					TimeSecCopy = TimeSeconds;
					TimeMinCopy = TimeMinutes;
					TimeFrameCopy = TimeFrames;
					PlayVoice_R(5001); //back ring hit SFX
					play1->Data1->Action = 0;
					play1->Data1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);

					if (++obj->Data1->Index == 2)
					{
						Delete_Cart();
						DisablePause();
						ScreenFade_Timer = 50;
						short sVar1;
						sVar1 = ScreenFade_RunActive();

						ChaoSpawn = false;
						switch (CurrentLevel)
						{
						case LevelIDs_HotShelter:
							if (CurrentAct == 2)
							{
								ChaoObj_Delete(obj);
								GameState = 24; //fix gamma hot shelter crash
							}
							else
							{
								GameMode = GameModes_Adventure_Field;
								GameState = 0xb;
							}
							break;
						case LevelIDs_FinalEgg:
							if (CurrentAct == 0)
							{
								GameState = 0xc; //fix Final Egg position
							}
							else
							{
								GameMode = GameModes_Adventure_Field;
								GameState = 0xB;
							}
							break;
						default:
							if (isTailsVersion || SHTailsVersion)
								GameState = 0xc;
							else
							{
								GameMode = GameModes_Adventure_Field;
								GameState = 0xB;
							}
							break;
						}

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
		a1->Data1->Position.y += 38;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		return;
	}

	if (Race && !isAIActive && CurrentLevelLayout <= Mission1_Variation)
		RaceResultCheck(a1);

	//call original function (Capsule.)
	ObjectFunc(origin, Capsule_Load_T.Target());
	origin(a1);
}

void Check_DisplayBackRing_Big(ObjectMaster* a1) {

	ObjectMaster* play1 = GetCharacterObject(0);
	EntityData1* v1 = a1->Data1;

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		a1->Data1->Position.y += 28;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;
		return;
	}

	if (Race && !isAIActive && CurrentLevelLayout <= Mission1_Variation)
	{
		RaceResultCheck(a1);
		return;
	}
}

void Check_DisplayBackRing_Amy(ObjectMaster* a1) {

	ObjectMaster* play1 = GetCharacterObject(0);
	EntityData1* v1 = a1->Data1;

	if (CurrentLevelLayout >= Mission2_100Rings)
	{

		a1->Data1->Position.y += 0;
		a1->DisplaySub = BackRingObj_Display;
		a1->MainSub = BackRingObj_Main;

		return;
	}

	if (Race && !isAIActive && CurrentLevelLayout <= Mission1_Variation)
	{
		RaceResultCheck(a1);
		return;
	}
}

void Check_Display_Frog_Balloon(ObjectMaster* a1) {

		switch (CurrentCharacter)
		{
		case Characters_Amy:
			a1->Data1->Position.y += 37;
			a1->MainSub = Balloon_Main;
			Balloon_Main(a1);
			break;
		case Characters_Big:
			LoadPVM("big_kaeru", &big_kaeru_TEXLIST);
			a1->Data1->Position.y += 20;
			a1->MainSub = OFrog;
			OFrog(a1);
			break;
		}

	if (Race && !isAIActive && CurrentLevelLayout <= Mission1_Variation)
		RaceResultCheck(a1);
}


void Check_Display_BackRing_Common(ObjectMaster* a1) {

	a1->Data1->Position.y += 36;
	a1->DisplaySub = BackRingObj_Display;
	a1->MainSub = BackRingObj_Main;
}

Trampoline Froggy_Load_T(0x4fa320, 0x4fa325, CheckLoadFroggy_r);
//Check the current mission and replace Froggy with Back Ring.
void __cdecl CheckLoadFroggy_r(ObjectMaster* a1) {

	Check_DisplayBackRing_Big(a1);

	if (CurrentLevelLayout <= Mission1_Variation)
	{
		ObjectFunc(origin, Froggy_Load_T.Target());
		origin(a1);
	}
}

Trampoline Balloon_Load_T(0x7a21c0, 0x7a21c6, CheckLoadBalloon_r);
//Check the current mission and replace Balloon with Back Ring.
void __cdecl CheckLoadBalloon_r(ObjectMaster* a1) {

	Check_DisplayBackRing_Amy(a1);

	if (CurrentLevelLayout <= Mission1_Variation)
	{
		ObjectFunc(origin, Balloon_Load_T.Target());
		origin(a1);
	}
}

Trampoline CasinoEmerald_Load_T(0x5dd0a0, 0x5dd0a6, CheckLoadCasinoEmerald_r);

//Check the current mission and replace the capsule with a different object.
void __cdecl CheckLoadCasinoEmerald_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	if (Race && !isAIActive && CurrentLevelLayout <= Mission1_Variation)
		RaceResultCheck(a1);

	//call original function (Emerald.)
	ObjectFunc(origin, CasinoEmerald_Load_T.Target());
	origin(a1);
}

Trampoline WVEmerald_Load_T(0x4df3b0, 0x4df3b6, CheckLoadWVEmerald_r);

//Check the current mission and replace the capsule with a different object.
void __cdecl CheckLoadWVEmerald_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	if (Race && !isAIActive && CurrentLevelLayout <= Mission1_Variation)
		RaceResultCheck(a1);

	//call original function (Emerald.)
	ObjectFunc(origin, WVEmerald_Load_T.Target());
	origin(a1);
}

Trampoline ICEmerald_Load_T(0x4ecfa0, 0x4ecfa6, CheckLoadICEmerald_r);

//Check the current mission and replace the capsule with a different object.
void __cdecl CheckLoadICEmerald_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	if (Race && !isAIActive && CurrentLevelLayout <= Mission1_Variation)
		RaceResultCheck(a1);

	//call original function (Emerald.)
	ObjectFunc(origin, ICEmerald_Load_T.Target());
	origin(a1);
}


Trampoline CheckLoadTailsPlaneEC_t(0x4f9fb0, 0x4f9fb6, CheckLoadTailsPlaneEC_r);

void __cdecl CheckLoadTailsPlaneEC_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	//call original function
	ObjectFunc(origin, CheckLoadTailsPlaneEC_t.Target());
	origin(a1);
}

Trampoline CheckLWTrigger_t(0x7b0da0, 0x7b0da6, CheckLWTrigger_r);

void __cdecl CheckLWTrigger_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	//call original function
	ObjectFunc(origin, CheckLWTrigger_t.Target());
	origin(a1);
}

Trampoline CheckFETrigger_t(0x5b24f0, 0x5b24f6, CheckFETrigger_r);

void __cdecl CheckFETrigger_r(ObjectMaster* a1) {

	if (CurrentLevelLayout <= Mission1_Variation && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big))
	{
		Check_Display_Frog_Balloon(a1);
		return;
	}

	if (CurrentLevelLayout >= Mission2_100Rings)
	{
		Check_Display_BackRing_Common(a1);
		return;
	}

	//call original function
	ObjectFunc(origin, CheckFETrigger_t.Target());
	origin(a1);
}

void Set_BackRing() {

	WriteData((ObjectFuncPtr*)0x4FA050, CheckLoadCapsule_r); // crashed plane in Emerald Coast
	WriteData((ObjectFuncPtr*)0x4DF3F0, CheckLoadCapsule_r); // Chaos Emerald in Windy Valley
	WriteData((ObjectFuncPtr*)0x5DD0E0, CheckLoadCapsule_r); // Chaos Emerald in Casinopolis
	WriteData((ObjectFuncPtr*)0x4ECFE0, CheckLoadCapsule_r); // Chaos Emerald in Ice Cap
	WriteData((ObjectFuncPtr*)0x7B0DD3, CheckLoadCapsule_r); // ending of Lost World
	WriteData((ObjectFuncPtr*)0x5B2523, CheckLoadCapsule_r); // ending of Final Egg
}