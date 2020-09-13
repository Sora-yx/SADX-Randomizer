#include "stdafx.h"
#include "SD.h"

#define AddCam(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" C ".bin")



void Cam_SkyDeck() {

	if (CurrentStageVersion == TailsVersion && CurrentAct == 0 && Race)
		LoadCamFile(0, "0603"); //Tails Camera
	else
		LoadCamFile(0, "0600"); //Sonic Camera
	
	
	LoadCamFile(1, "0601");

	if (CurrentAct == 2 && (CurrentStageVersion == KnucklesVersion))
		LoadCamFile(2, "0604"); //Knuckles Version
	else
		LoadCamFile(2, "0600"); //Knuckles Version

}


void SkyDeck_Layout() {


	CurrentStageVersion = TailsVersion;
	//CurrentMission = 0;

	if (CurrentAct == 2)
		CurrentStageVersion = KnucklesVersion;


	switch (CurrentStageVersion)
	{
	case SonicVersion:
	default:
		CurrentStageVersion = SonicVersion;
		break;
	case TailsVersion:
		if (CurrentMission < Mission2_100Rings) {
			Race = true;
			SelectBarRace();
		}
		break;
	case KnucklesVersion:
		if (CurrentMission < Mission2_100Rings)
			SetRNGKnuckles();
		break;

	}



	return;
}

//Don't change the gravity if knuckles layout.
int Switch_Gravity() {

	if (CurrentCharacter == Characters_Knuckles && CurrentStageVersion == SonicVersion)
		return (unsigned)Characters_Sonic; //Make the gravity work for Knuckles

	if (CurrentStageVersion == KnucklesVersion)
		return (unsigned)Characters_Knuckles; 

	return GetCharacterID(0);
}

//Allow Gamma to target the Sky Deck cannon
//Load a targetable item on the cannon to destroy it.
void SkyDeckCannon_LoadWithTarget(ObjectMaster* SDCanonnObj) {
	int iVar1;

	iVar1 = ClipSetObject(SDCanonnObj);
	if (iVar1 == 0) {
		SDCannon(SDCanonnObj);
	}
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	
	obj->Data1->LoopData = (Loop*)SDCanonnObj;
	obj->Data1->Scale.x = 20;

	return;
}

//Allow Gamma to target the Sky Deck cannon

void SkyDeckCannonS1_LoadWithTarget(ObjectMaster* SDCanonnObj) {
	int iVar1;

	iVar1 = ClipSetObject(SDCanonnObj);
	if (iVar1 == 0) {
		SDCannonS1(SDCanonnObj);
	}
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);

	obj->Data1->LoopData = (Loop*)SDCanonnObj;
	obj->Data1->Scale.x = 20;

	return;
}

void SkyDeckCannonS2_LoadWithTarget(ObjectMaster* SDCanonnObj) {
	int iVar1;

	iVar1 = ClipSetObject(SDCanonnObj);
	if (iVar1 == 0) {
		SDCannonS2(SDCanonnObj);
	}
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);

	obj->Data1->LoopData = (Loop*)SDCanonnObj;
	obj->Data1->Scale.x = 20;

	return;
}

void FixTailsVictorySD() {

	//Prevent AI to make Tails lose when hiting the capsule if we aren't racing.

	if (CurrentCharacter == Characters_Tails && !Race)
		SetTailsRaceVictory();
	else
		SetOpponentRaceVictory();

	return;
}


//Prevent Big to grab and drop the lever, Although, there is probably a nicer way to do this by editing Big's grab function.
Trampoline Olever_t(0x5f1d20, 0x5f1d28, Olever_r);

void Olever_r(ObjectMaster* obj) {

	
	ObjectMaster* P1 = GetCharacterObject(0);
	int curAction = P1->Data1->Action;

	if (P1 != nullptr && P1->Data1->CharID == Characters_Big && curAction == 15 && CurrentLevel == LevelIDs_SkyDeck)
	{
		P1->Data1->Action = 120; //Forcing an action which doesn't exist will block the character, this will prevent Big to grab the lever.
		P1->Data1->Action = 1;
		P1->Data1->Status &= 0x100u; //remove the holding item status
		obj->Data1->Action = 1;
		obj->Data1->Status = 1600;
		obj->Data1->field_A = 538;
		return;
	}

	obj->Data1->Action = obj->Data1->Action;
	ObjectFunc(origin, Olever_t.Target());
	origin(obj);
}



void __cdecl SkyDeck_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	WriteCall((void*)0x422dd8, SkyDeck_Layout); 
	WriteCall((void*)0x5ecc7b, Switch_Gravity); 
	WriteJump((void*)0x5f8530, SkyDeckCannon_LoadWithTarget);	
	WriteJump((void*)0x5f9760, SkyDeckCannonS1_LoadWithTarget);
	WriteJump((void*)0x5f8e50, SkyDeckCannonS2_LoadWithTarget);
	
	WriteCall((void*)0x461614, FixTailsVictorySD);
	SDObjects_Init(path, helperFunctions);

	AddLevelLayout("Sky Deck\\", "SD0", helperFunctions);
	AddLevelLayout("Sky Deck\\", "SD1", helperFunctions);
	AddLevelLayout("Sky Deck\\", "SD2", helperFunctions);
	AddLevelLayout("Sky Deck\\", "SDM", helperFunctions);
	AddLevelLayout("Sky Deck\\", "SDK", helperFunctions);

	AddCam("C0600");
	AddCam("C0601");
	AddCam("C0602");
	AddCam("C0603");
	AddCam("C0604");
}

ObjectListEntry SkyDeckObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 4, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 14, 3, 1, 1000000, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "O R_H" } /* "O R_H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "O R_HS" } /* "O R_HS" */,
	{ 14, 3, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "O R_V" } /* "O R_V" */,
	{ 14, 3, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "O R_VS" } /* "O R_VS" */,
	{ 2, 2, 1, 1960000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5FD840, "CANNON_B" } /* "CANNON_B" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5FCCC0, "CANNON_S" } /* "CANNON_S" */,
	{ 6, 3, 9, 3240000, 0, (ObjectFuncPtr)0x5FC620, "CANNON_H" } /* "CANNON_H" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5FB980, "TALAP_0" } /* "TALAP_0" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0740, "EDGE_0" } /* "EDGE_0" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0750, "BRANCH_L" } /* "BRANCH_L" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0760, "BRANCH_S" } /* "BRANCH_S" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5FB210, "CONNECT_0" } /* "CONNECT_0" */,
	{ 7, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0AB0, "TOP_0" } /* "TOP_0" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5FAA70, "TALAP_1" } /* "TALAP_1" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5FA7F0, "CYL_0" } /* "CYL_0" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5FA570, "EDGE_1" } /* "EDGE_1" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F9C90, "CYL_1" } /* "CYL_1" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F9A10, "CYL_2" } /* "CYL_2" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0770, "POLE_S" } /* "POLE_S" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0780, "POLE_L" } /* "POLE_L" */,
	{ 7, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F09B0, "CYL_S" } /* "CYL_S" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0790, "BASE_L" } /* "BASE_L" */,
	{ 6, 3, 9, 640000, 0, (ObjectFuncPtr)0x5F0FB0, "HANG_A" } /* "HANG_A" */,
	{ 6, 3, 9, 640000, 0, (ObjectFuncPtr)0x51F680, "HANG_B" } /* "HANG_B" */,
	{ 6, 3, 9, 640000, 0, (ObjectFuncPtr)0x5F0040, "HANG_C" } /* "HANG_C" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F07A0, "REST_6" } /* "REST_6" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F07B0, "REST_45" } /* "REST_45" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F08B0, "REST_9" } /* "REST_9" */,
	{ 2, 3, 8, 0, 0, (ObjectFuncPtr)0x5F0B30, "RADDER" } /* "RADDER" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F07C0, "BLOCK_0" } /* "BLOCK_0" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F07D0, "BLOCK_1" } /* "BLOCK_1" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F07E0, "BLOCK_2" } /* "BLOCK_2" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F07F0, "BLOCK_3" } /* "BLOCK_3" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0800, "BLOCK_4" } /* "BLOCK_4" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0810, "BLOCK_5" } /* "BLOCK_5" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0820, "COVER" } /* "COVER" */,
	{ 6, 3, 9, 250000, 0, (ObjectFuncPtr)0x5F0830, "SCREW" } /* "SCREW" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F0840, "LAUNCHER" } /* "LAUNCHER" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0850, "BLOCK_6" } /* "BLOCK_6" */,
	{ 6, 3, 9, 1440000, 0, (ObjectFuncPtr)0x5F0860, "BLOCK_7" } /* "BLOCK_7" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5F9760, "CANNON_S1" } /* "CANNON_S1" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5F8E50, "CANNON_S2" } /* "CANNON_S2" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5F8530, "CANNON_M" } /* "CANNON_M" */,
	{ 7, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5F0A40, "TANK_H" } /* "TANK_H" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5F08A0, "TOWER_I" } /* "TOWER_I" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5F0CC0, "DUCT_0" } /* "DUCT_0" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5F08C0, "COLD FAN" } /* "COLD FAN" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5EFD90, "FENCE_L" } /* "FENCE_L" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5EFDE0, "FENCE_M" } /* "FENCE_M" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5EFE30, "FENCE_S" } /* "FENCE_S" */,
	{ 6, 3, 9, 722500, 0, (ObjectFuncPtr)0x5F0870, "RAIL_L" } /* "RAIL_L" */,
	{ 6, 3, 9, 722500, 0, (ObjectFuncPtr)0x5F0880, "RAIL_S" } /* "RAIL_S" */,
	{ 6, 3, 1, 722500, 0, (ObjectFuncPtr)0x5F0890, "LANTERN" } /* "LANTERN" */,
	{ 6, 3, 1, 722500, 0, (ObjectFuncPtr)0x5F0900, "CTRLTOWER" } /* "CTRLTOWER" */,
	{ 6, 3, 9, 722500, 0, (ObjectFuncPtr)0x5F1080, "FLAP01" } /* "FLAP01" */,
	{ 6, 3, 9, 722500, 0, (ObjectFuncPtr)0x5F10B0, "FLAP02" } /* "FLAP02" */,
	{ 6, 3, 1, 722500, 0, (ObjectFuncPtr)0x5F0910, "SCOPE" } /* "SCOPE" */,
	{ 2, 3, 9, 722500, 0, (ObjectFuncPtr)0x5F0E60, "UNTEI" } /* "UNTEI" */,
	{ 6, 3, 9, 722500, 0, (ObjectFuncPtr)0x5F0920, "EDGE" } /* "EDGE" */,
	{ 2, 3, 9, 250000, 0, (ObjectFuncPtr)0x5F0930, "LA" } /* "LA" */,
	{ 2, 3, 9, 250000, 0, (ObjectFuncPtr)0x5F0940, "LB" } /* "LB" */,
	{ 6, 3, 9, 250000, 0, (ObjectFuncPtr)0x5F0950, "LC" } /* "LC" */,
	{ 6, 3, 9, 250000, 0, (ObjectFuncPtr)0x5F0960, "STOP" } /* "STOP" */,
	{ 2, 3, 9, 9000000, 0, (ObjectFuncPtr)0x5F08D0, "CARRIER" } /* "CARRIER" */,
	{ 2, 3, 9, 9000000, 0, (ObjectFuncPtr)0x5F08E0, "CARRIER2" } /* "CARRIER2" */,
	{ 2, 3, 9, 9000000, 0, (ObjectFuncPtr)0x5F08F0, "CARRIER3" } /* "CARRIER3" */,
	{ 2, 3, 9, 64000000, 0, (ObjectFuncPtr)0x5F0970, "S_WING" } /* "S_WING" */,
	{ 2, 3, 9, 64000000, 0, (ObjectFuncPtr)0x5F0980, "S_MAP" } /* "S_MAP" */,
	{ 2, 3, 9, 64000000, 0, (ObjectFuncPtr)0x5F0990, "S_OBJ" } /* "S_OBJ" */,
	{ 2, 3, 9, 64000000, 0, (ObjectFuncPtr)0x5F09A0, "S_ENG" } /* "S_ENG" */,
	{ 7, 3, 1, 250000, 0, (ObjectFuncPtr)0x5EFB00, "HANGPOLE" } /* "HANGPOLE" */,
	{ 6, 3, 1, 250000, 0, (ObjectFuncPtr)0x5EF9D0, "NEXT ACT" } /* "NEXT ACT" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4AA620, "E ACLIFT" } /* "E ACLIFT" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0DF0, "SPINA A" } /* "SPINA A" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0F40, "SPINA B" } /* "SPINA B" */,
	{ 2, 3, 5, 160000, 0, (ObjectFuncPtr)0x4AF500, "E UNI B" } /* "E UNI B" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5F7530, "O CON" } /* "O CON" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5F76A0, "O D CON" } /* "O D CON" */,
	{ 2, 3, 1, 3996001, 0, (ObjectFuncPtr)0x5F7150, "O CHAMBR" } /* "O CHAMBR" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F6130, "O RANE A" } /* "O RANE A" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F6190, "O RANE B" } /* "O RANE B" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F61F0, "O RANE C" } /* "O RANE C" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F6250, "O RANE D" } /* "O RANE D" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F62B0, "O RANE E" } /* "O RANE E" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F6310, "O RANE F" } /* "O RANE F" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F6370, "O ANA A" } /* "O ANA A" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F63D0, "O ANA B" } /* "O ANA B" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5F5C70, "O SKY EV" } /* "O SKY EV" */,
	{ 7, 3, 1, 25000000, 0, (ObjectFuncPtr)0x5F2070, "O LEVER" } /* "O LEVER" */,
	{ 10, 3, 1, 90000, 0, (ObjectFuncPtr)0x5F4830, "O ROBO A" } /* "O ROBO A" */,
	{ 10, 3, 1, 90000, 0, (ObjectFuncPtr)0x5F4D70, "O ROBO B" } /* "O ROBO B" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x5F5330, "O BUKET" } /* "O BUKET" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x5F5530, "O BOX" } /* "O BOX" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x5F56E0, "O UEKI" } /* "O UEKI" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5F43C0, "O ESCALATOR" } /* "O ESCALATOR" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5F4180, "O MEKA" } /* "O MEKA" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5F4240, "O TUTU" } /* "O TUTU" */,
	{ 2, 3, 1, 3240000, 0, (ObjectFuncPtr)0x5F40A0, "CANNON_H2" } /* "CANNON_H2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4B0DF0, "SPINA A" } /* "SPINA A" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4B0F40, "SPINA B" } /* "SPINA B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4B1090, "SPINA C" } /* "SPINA C" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4AF190, "E UNI A" } /* "E UNI A" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4AF500, "E UNI B" } /* "E UNI B" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5F00E0, "TRAIL" } /* "TRAIL" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5F3280, "SND_ENG" } /* "SND_ENG" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5F1060, "T_COLLI" } /* "T_COLLI" */,
	{ 6, 3, 1, 998001, 0, (ObjectFuncPtr)0x5F3200, "O_CRANE" } /* "O_CRANE" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F26C0, "O_VENT" } /* "O_VENT" */,
	{ 2, 6, 1, 1440000, 0, (ObjectFuncPtr)0x5F27A0, "O_DECAL" } /* "O_DECAL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5EF2B0, "W_WALL" } /* "W_WALL" */,
	{ 15, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ItemBoxAir" } /* "O ItemBoxAir" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A9140, "O KN HINT" } /* "O KN HINT" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINT" } /* "O HINT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5F02B0, "HOMING" } /* "HOMING" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x5F2860, "O_SIGNAL" } /* "O_SIGNAL" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" }, /* "O FROG" */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};

PVMEntry SkyDeckObjectTextures[] = {
	{ "OBJ_SKYDECK", (TexList*)0x214BE40 },
	{ "E_AIRCRAFT", (TexList*)0x9620F0 },
	{ "OUM", (TexList*)0x9334EC },
	{ "KUJA", (TexList*)0x93142C },
	{ "MILESRACE", (TexList*)0x91BFC0 },
	{ "SUPI_SUPI", (TexList*)0x96F518 },
	{ "TUBA", (TexList*)0x92F2BC },
	{ "LION", (TexList*)0x944094 },
	{ "AIR_SIGNAL", (TexList*)0x96236C },
	{ "SUKA", (TexList*)0x94789C },
	{ "UNI_A_UNIBODY", (TexList*)0x96CB5C },
	{ "TOGEBALL_TOGEBALL", (TexList*)0x96BC54 },
	{ NULL, (TexList*)0x214B41C },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "common-obj", &SA2_OBJ_TEXLIST },
	{ 0 }
};

ObjectList SkyDeckObjectList = { arraylengthandptrT(SkyDeckObjectList_list, int) };

DataArray(DeathZone*, SkyDeckDeathZones, 0x223082C, 3);

void __cdecl SDObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist

	ObjLists[LevelIDs_SkyDeck * 8 + 2] = &SkyDeckObjectList;
	TexLists_Obj[LevelIDs_SkyDeck] = SkyDeckObjectTextures;
	SkyDeckDeathZones[0] = SkyDeck1DeathZones; //Sky Deck death zone redirection
	SkyDeckDeathZones[1] = SkyDeck2DeathZones;
}