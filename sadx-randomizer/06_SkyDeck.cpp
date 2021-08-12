#include "stdafx.h"
#include "SD.h"

void SkyDeck_Layout() {

	/*CurrentMission = 0;
	CurrentStageVersion = TailsVersion;*/

	if (CurrentAct == 2)
		CurrentStageVersion = KnucklesVersion;
	else {
		if (CurrentStageVersion != TailsVersion)
			CurrentStageVersion = SonicVersion;
	}

	if (CurrentMission == Mission3_LostChao && CurrentStageVersion != KnucklesVersion)
		CurrentMission = Mission2_100Rings;

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


	int curAction = EntityData1Ptrs[0]->Action;

	if (EntityData1Ptrs[0]->CharID == Characters_Big && curAction == 15 && CurrentLevel == LevelIDs_SkyDeck)
	{
		EntityData1Ptrs[0]->Action = 120; //Forcing an action which doesn't exist will block the character, this will prevent Big to grab the lever.
		EntityData1Ptrs[0]->Action = 1;
		EntityData1Ptrs[0]->Status &= 0x100u; //remove the holding item status
		obj->Data1->Action = 1;
		obj->Data1->Status = 1600;
		obj->Data1->field_A = 538;
		return;
	}

	obj->Data1->Action = obj->Data1->Action;
	ObjectFunc(origin, Olever_t.Target());
	origin(obj);
}


void __cdecl SDObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist

	ObjLists[LevelIDs_SkyDeck * 8 + 2] = &SkyDeckObjectList;
	SkyDeckDeathZones[0] = SkyDeck1DeathZones; //Sky Deck death zone redirection
	SkyDeckDeathZones[1] = SkyDeck2DeathZones;

	return;
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
	return;
}