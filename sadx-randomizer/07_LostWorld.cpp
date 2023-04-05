#include "stdafx.h"
#include "LW.h"

void LW_Layout() {

	if (CurrentStageVersion != KnucklesVersion && CurrentAct != 1)
		CurrentStageVersion = SonicVersion;
	else
	{
		CurrentStageVersion = KnucklesVersion;
	}

}

bool isPlayerInWaterSlide = false;

void FixLWWaterSlide() {

	if (CurrentLevel == LevelIDs_LostWorld && CurrentAct == 1 && CurrentMissionCard == RingsCard)
		isPlayerInWaterSlide = true;

	if (EntityData1Ptrs[0]->CharID == Characters_Sonic)
		return ForcePlayerAction(0, 0x17);

	return;
}

void FixLWWaterSlide2() {

	if (CurrentLevel == LevelIDs_LostWorld && CurrentAct == 1 && CurrentMissionCard == RingsCard)
		isPlayerInWaterSlide = false;

	return ForcePlayerAction(0, 0x18);
}

int FixLWMusic() {
	if (CurrentStageVersion == KnucklesVersion)
		return Characters_Knuckles;
	else
		return 8;
}


void __cdecl LWObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_LostWorld * 8 + 1] = &LostWorldObjectList;
	ObjLists[LevelIDs_LostWorld * 8 + 2] = &LostWorldObjectList;
	return;
}


void __cdecl LostWorld_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteCall((void*)0x5e16c2, FixLWMusic); //Fix Lost World Act 2 music as Knuckles.

	WriteCall((void*)0x422e43, LW_Layout);
	
	WriteCall((void*)0x5e3408, FixLWWaterSlide2);
	WriteCall((void*)0x5e37fa, FixLWWaterSlide);
	
	LWObjects_Init(path, helperFunctions);

	AddLevelLayout("Lost World\\", "LW0", helperFunctions);
	AddLevelLayout("Lost World\\", "LW1", helperFunctions);
	AddLevelLayout("Lost World\\", "LW2", helperFunctions);
	AddLevelLayout("Lost World\\", "LWK", helperFunctions);

	AddCam("C0700");
	AddCam("C0701");
	AddCam("C0702");
	AddCam("C0703");
	return;
}