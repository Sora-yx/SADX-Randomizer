#include "stdafx.h"
#include "FE.h"

void FinalEgg_Layout() 
{

	if (CurrentStageVersion != AmyVersion && CurrentStageVersion != GammaVersion)
		CurrentStageVersion = SonicVersion;

	if (CurrentAct == 2)
		CurrentStageVersion = GammaVersion;
}


void __cdecl FinalEggObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_FinalEgg * 8 + 0] = &FinalEggObjectList;
	ObjLists[LevelIDs_FinalEgg * 8 + 2] = &FinalEggObjectList;
}

void __cdecl FinalEgg_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Initiliaze data

	WriteCall((void*)0x422fe3, FinalEgg_Layout); //FE random layout
	FinalEggObjects_Init(path, helperFunctions);

	AddLevelLayout("Final Egg\\", "FE0", helperFunctions);
	AddLevelLayout("Final Egg\\", "FE1", helperFunctions);
	AddLevelLayout("Final Egg\\", "FE2", helperFunctions);
	AddLevelLayout("Final Egg\\", "FEA", helperFunctions);
	AddLevelLayout("Final Egg\\", "FEG", helperFunctions);

	AddCam("C1000");
	AddCam("C1001");
	AddCam("C1002");
	AddCam("C1003");
	AddCam("C1004");
}