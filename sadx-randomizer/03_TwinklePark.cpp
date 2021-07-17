#include "stdafx.h"
#include "TP.h"


void TwinklePark_Layout() {

	if (CurrentStageVersion != AmyVersion && CurrentStageVersion != BigVersion)
		CurrentStageVersion = SonicVersion;

	if (CurrentAct == 1 && CurrentStageVersion != BigVersion)
		CurrentStageVersion = AmyVersion;

	if (CurrentCharacter >= Characters_Gamma)
	{
		WriteData<1>((void*)0x798306, 0x84);
		WriteData<1>((void*)0x7983c4, 0x7F);
	}

	fixTCCart();
	return;
}

void FixRollerCoaster() {

	if (EntityData1Ptrs[0])
		EntityData1Ptrs[0]->Action = 28; //force the character to leave the RC
}

void FixRCCharacterAction() {
	if (!CharObj2Ptrs[0])
		return;

	ForcePlayerAction(0, 18);

	PlaySound(0x4d, 0, 0, 0);
	return;
}


void __cdecl TPObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_TwinklePark * 8 + 1] = &TwinkleParkObjectList;
	return;
}

void __cdecl TwinklePark_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteData<5>((int*)0x61cb77, 0x90); //Fix Twinkle Park Act 2 crash when not Sonic-Amy-Big
	WriteData<1>((char*)0x61cf97, 0x08); //Allow everyone to use Amy Twinkle Park transition part 1
	WriteData<1>((int*)0x61cf99, 0x84); //Allow everyone to use Amy Twinkle Park transition part 2
	WriteData<1>((int*)0x61dd72, 0x85); //Make Rollercoaster works when not Sonic.
	
	WriteCall((void*)0x61dd82, FixRCCharacterAction); 
	WriteCall((void*)0x61dde8, FixRollerCoaster); //Fix leaving RC when not Sonic.

	WriteCall((void*)0x422c92, TwinklePark_Layout); //TP random layout

	TPObjects_Init(path, helperFunctions);

	AddLevelLayout("Twinkle Park\\", "TP0", helperFunctions);
	AddLevelLayout("Twinkle Park\\", "TP1", helperFunctions);
	AddLevelLayout("Twinkle Park\\", "TP2", helperFunctions);
	AddLevelLayout("Twinkle Park\\", "TPA", helperFunctions);
	AddLevelLayout("Twinkle Park\\", "TPB", helperFunctions);

	AddCam("C0300");
	AddCam("C0301");
	AddCam("C0302");
	AddCam("C0303");
	AddCam("C0304");
	return;
}