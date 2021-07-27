#include "stdafx.h"
#include "SH.h"

void SpeedHighway_Layout() {

	/*CurrentStageVersion = TailsVersion;
	CurrentMission = Mission3_LostChao;*/

	if (CurrentAct == 2)
		CurrentStageVersion = KnucklesVersion;

	switch (CurrentStageVersion)
	{
	case SonicVersion:
	default:
		if (CurrentStageVersion != TailsVersion)
			CurrentStageVersion = SonicVersion;
		break;
	case KnucklesVersion:
		SetRNGKnuckles();
		break;
	}

	return;
}

void SHAct2Position() {
	if (CurrentCharacter != Characters_Sonic)
		return PositionPlayer(0, 10, -10000, 10);
	else
		return ForcePlayerAction(0, 0x2b);
}

void CheckEggmanRaceWinner() {

	if (CurrentCharacter == Characters_Tails || !Race)
		LoadLevelResults_r();

	if (CurrentCharacter != Characters_Tails && Race)
	{
		if (CurrentLevel == LevelIDs_SpeedHighway && CurrentAct == 0 && RaceWinnerPlayer == 2)
			SetAIRaceWin();
	}
}


void __cdecl SHObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_SpeedHighway * 8 + 0] = &SpeedHighwayObjectList;
	ObjLists[LevelIDs_SpeedHighway * 8 + 2] = &SpeedHighwayObjectList;
	return;
}


void __cdecl SpeedHighway_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	WriteData<6>((int*)0x61006a, 0x90); // Allow Speed Highway act 2 for every characters.
	WriteCall((void*)0x610272, SHAct2Position); //teleport player during SH act 2.

	WriteCall((void*)0x422cfd, SpeedHighway_Layout); //SH random layout
	WriteJump((void*)0x47d527, CheckEggmanRaceWinner);

	SHObjects_Init(path, helperFunctions);

	AddLevelLayout("Speed Highway\\", "SH0", helperFunctions);
	AddLevelLayout("Speed Highway\\", "SH1", helperFunctions);
	AddLevelLayout("Speed Highway\\", "SH2", helperFunctions);
	AddLevelLayout("Speed Highway\\", "SHM", helperFunctions);
	AddLevelLayout("Speed Highway\\", "SHK", helperFunctions);

	AddCam("C0400");
	AddCam("C0401");
	AddCam("C0402");
	AddCam("C0403");
	AddCam("C0404");
	return;
}