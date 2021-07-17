#include "stdafx.h"
#include "WV.h"

void FixTailsVictoryWV() {

	//Prevent AI to make Tails lose when hiting the capsule if we aren't racing.

	if (CurrentCharacter == Characters_Tails && !Race)
		SetTailsRaceVictory();
	else
		SetOpponentRaceVictory();

	return;
}

void WindyValley_Layout() {

	if (CurrentAct == 2)
		CurrentStageVersion = TailsVersion;

	if (CurrentMission == Mission3_LostChao && (CurrentStageVersion == TailsVersion || CurrentStageVersion == GammaVersion))
	{
		CurrentMission = Mission2_100Rings;
	}

	if (CurrentStageVersion != GammaVersion && CurrentStageVersion != TailsVersion)
		CurrentStageVersion = SonicVersion;

	return;
}


void __cdecl WVObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_WindyValley * 8 + 0] = &WindyValleyObjectList;
	ObjLists[LevelIDs_WindyValley * 8 + 2] = &WindyValleyObjectList;
}

void __cdecl WindyValley_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	
	WVObjects_Init(path, helperFunctions);
	WriteCall((void*)0x422c27, WindyValley_Layout); //WV
	WriteCall((void*)0x4df390, FixTailsVictoryWV);

	//Sonic
	AddLevelLayout("Windy Valley\\", "WV0", helperFunctions);
	AddLevelLayout("Windy Valley\\", "WV1", helperFunctions);
	AddLevelLayout("Windy Valley\\", "WV2", helperFunctions);
	AddLevelLayout("Windy Valley\\", "WVG", helperFunctions);
	AddLevelLayout("Windy Valley\\", "WVM", helperFunctions);

	AddCam("C0200");
	AddCam("C0201");
	AddCam("C0202");
	AddCam("C0203");
	AddCam("C0204");
	return;
}
