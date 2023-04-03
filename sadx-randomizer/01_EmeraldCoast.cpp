#include "stdafx.h"
#include "EC.h"

void EC_Layout() 
{

	if (CurrentAct != 2 && CurrentStageVersion != GammaVersion)
		CurrentStageVersion = SonicVersion;

	if (CurrentAct == 2)
		CurrentStageVersion = BigVersion;

	return;
}

void __cdecl ECObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist

	for (uint8_t i = 0; i < 3; i++)
		ObjLists[LevelIDs_EmeraldCoast * 8 + i] = &EmeraldCoastObjectList;

	return;
}


void __cdecl EmeraldCoast_Init(const char* path, const HelperFunctions& helperFunctions)
{
	ECObjects_Init(path, helperFunctions);

	//Initiliaze data
	WriteData<5>((int*)0x4f6afa, 0x90); //Prevent the game to start the cutscene as Tails.
	WriteData<1>((char*)0x427FCA, 0x08); //Fix EC HUD display for Tails.

	WriteCall((void*)0x422bbc, EC_Layout);

	AddLevelLayout("Emerald Coast\\", "EC0", helperFunctions);
	AddLevelLayout("Emerald Coast\\", "EC1", helperFunctions);
	AddLevelLayout("Emerald Coast\\", "EC2", helperFunctions);
	AddLevelLayout("Emerald Coast\\", "ECE", helperFunctions);

	AddCam("C0100");
	AddCam("C0101");
	AddCam("C0102");
	AddCam("C0103");
	return;
}