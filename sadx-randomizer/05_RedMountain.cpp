#include "stdafx.h"
#include "RM.h"

void FixRMLava() {
	if (CurrentStageVersion == GammaVersion)
		WriteData<1>((void*)0x6027cb, 0x75); //fix Red Mountain Lava for everyone
	else
		WriteData<1>((void*)0x6027cb, 0x74); //restore original

	return;
}

void RedMountain_Layout() {

	if (CurrentStageVersion != KnucklesVersion && CurrentStageVersion != GammaVersion)
		CurrentStageVersion = SonicVersion;

	if (CurrentAct == 1)
		CurrentStageVersion = GammaVersion;

	if (CurrentAct == 2)
	{
		CurrentStageVersion = KnucklesVersion;
	}

	FixRMLava(); //Adjust Lava level depending on Sonic / Gamma Layout.
	return;
}


void __cdecl RMObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist and fix killplane
	for (uint8_t i = 0; i < 3; i++) {
		ObjLists[LevelIDs_RedMountain * 8 + i] = &RedMountainObjectList;
	}

	RedMountainDeathZones[0] = RedMountain1DeathZones;
	RedMountainDeathZones[2] = RedMountain3DeathZones;
	return;
}

void RM_MovePlayerToEndPosition() {

	if (CurrentLevel == LevelIDs_RedMountain && CurrentAct == 1 && CurrentStageVersion == GammaVersion) {

		for (int i = 0; i < 8; i++) {

			if (CurrentCharacter > Characters_Tails)
				break;

			if (playertwp[i]) 
			{
				warped = true;
				CharColliOff(playertwp[i]);
				PositionPlayer(i, -397.69, 1039.52, 3101.33);
			}
		}
	}

	LoadLevelResults();
}

void __cdecl RedMountain_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	WriteData<5>((int*)0x601595, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain act 2.
	WriteData<1>((char*)0x608A1A, 0x08); //Allow the Trapdoor to open when Knuckles.
	WriteData<1>((char*)0x606bba, 0x08); //Fix the rock bridge
	WriteData<1>((char*)0x60405f, 0x74); //Allow everyone to destroy the rocks in RM. (Gamma layout.)
	WriteData<1>((char*)0x60405e, 0x08); //Allow everyone to destroy the rocks in RM. part 2 (Gamma layout.)
	WriteData<1>((char*)0x6027c5, 0x08); //Fix Red Mountain Lava (Gamma layout.)

	//Allow Tails to do Red Mountain
	WriteData<5>((int*)0x601570, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain Act 1.
	WriteData<5>((int*)0x6008b1, 0x90); //Fix Red Mountain Act 2 music as Tails.

	WriteCall((void*)0x422d68, RedMountain_Layout); //RM random act
	WriteCall((void*)0x6053B3, RM_MovePlayerToEndPosition);

	RMObjects_Init(path, helperFunctions);

	AddLevelLayout("Red Mountain\\", "RM0", helperFunctions);
	AddLevelLayout("Red Mountain\\", "RM1", helperFunctions);
	AddLevelLayout("Red Mountain\\", "RM2", helperFunctions);
	AddLevelLayout("Red Mountain\\", "RM3", helperFunctions);
	AddLevelLayout("Red Mountain\\", "RMG", helperFunctions);

	AddCam("C0500");
	AddCam("C0501");
	AddCam("C0502");
	AddCam("C0503");
	return;
}