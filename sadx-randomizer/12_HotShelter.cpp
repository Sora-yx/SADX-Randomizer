#include "stdafx.h"
#include "HS.h"

void HotShelter_Layout() 
{
	if (CurrentMission == Mission3_LostChao && CurrentStageVersion == BigVersion) 
	{

		if (SA2M2)
			CurrentMission = Mission2_100Rings;
		else
			CurrentMission = SADX_Mission;
	}

	if (CurrentStageVersion != BigVersion && CurrentStageVersion != GammaVersion)
		CurrentStageVersion = AmyVersion;

	if (CurrentAct == 2)
		CurrentStageVersion = GammaVersion;

	CheckAndSet_HotShelterLayoutFeatures();
}

void HotShelterSecretSwitch() { //used for Big Hot Shelter when not Big for secret path.

	if (CurrentStageVersion != BigVersion || CurrentLevel != LevelIDs_HotShelter)
		return;

	if (SecretWaterSwitch == 3 && FirstHotShelterSwitch == 1)
		SomethingAboutHotShelterSwitch = 1;

}

void CheckAndSet_HotShelterLayoutFeatures() {

	if (CurrentStageVersion == BigVersion) //Big Layout
	{
		//Make Big Hot Shelter stuff (secret door etc.) work for everyone.
		 //open the door when you activate the switch. (if < 8)
		WriteData<1>((int*)0x5aaf14, 0x9C); //Open the door for everyone. (from SETZ to SETL: if < 8)
		WriteData<1>((int*)0x59a3bc, 0x74); //makes the second switch working for everyone.
		WriteData<1>((int*)0x59a125, 0x08);
		WriteData<1>((int*)0x59a126, 0x74);
	}
	else
	{
		//Restore Big Hot Shelter functions to Vanilla so it will fix HS act 1 and 2 when Amy layout.
		WriteData<1>((int*)0x5aaf14, 0x94);
		WriteData<1>((int*)0x59a3bc, 0x75);
		WriteData<1>((int*)0x59a125, 0x07);
		WriteData<1>((int*)0x59a126, 0x75);
		WriteData<6>((int*)0x442249, 0x90); //Fix Puzzle Box drop
	}
}


void __cdecl HSObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist

	ObjLists[LevelIDs_HotShelter * 8 + 0] = &HotShelter1ObjectList;
	ObjLists[LevelIDs_HotShelter * 8 + 1] = &HotShelter2ObjectList;
	ObjLists[LevelIDs_HotShelter * 8 + 2] = &HotShelter3ObjectList;

	HotShelterDeathZones[2] = HotShelter3DeathZones;
}

void __cdecl HotShelter_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteData<5>((int*)0x42300b, 0x90);
	WriteData<5>((int*)0x42301a, 0x90);
	WriteData<5>((int*)0x423029, 0x90);
	WriteData<5>((int*)0x423038, 0x90);
	WriteData<5>((int*)0x423044, 0x90);
	WriteData<5>((int*)0x423053, 0x90);
	WriteData<5>((int*)0x423062, 0x90);

	WriteCall((void*)0x423071, HotShelter_Layout); //HS Custom Layout
	WriteData<1>((char*)0x5aaf12, 0x08); //Big HS Stuff
	WriteData<1>((char*)0x59a3bb, 0x08);

	HSObjects_Init(path, helperFunctions);

	AddLevelLayout("Hot Shelter\\", "HS0", helperFunctions);
	AddLevelLayout("Hot Shelter\\", "HS1", helperFunctions);
	AddLevelLayout("Hot Shelter\\", "HS2", helperFunctions);
	AddLevelLayout("Hot Shelter\\", "HSB", helperFunctions);

	AddCam("C1200");
	AddCam("C1201");
	AddCam("C1202");
	AddCam("C1203");
}