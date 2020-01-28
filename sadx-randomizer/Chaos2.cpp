#include "stdafx.h"
#include "Utils.h"
#include "Chaos2.h"
#include "RandomHelpers.h"

void Chaos2_LoadWithTarget() {
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	obj->Data1->LoopData = (Loop*)LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, Chaos2_Main);
}


void __cdecl Chaos2_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	//Sonic
	helperFunctions.ReplaceFile("system\\SET1600S.BIN", "system\\levels\\Chaos 2\\Sonic-Chaos2.bin");
	helperFunctions.RegisterStartPosition(Characters_Sonic, Chaos2_StartPositions[0]);

	//Tails
	helperFunctions.ReplaceFile("system\\SET1600M.BIN", "system\\levels\\Chaos 2\\Tails-Chaos2.bin");
	helperFunctions.RegisterStartPosition(Characters_Tails, Chaos2_StartPositions[0]);

	//Knuckles
	helperFunctions.ReplaceFile("system\\SET1600K.BIN", "system\\levels\\Chaos 2\\Knux-Chaos2.bin");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Chaos2_StartPositions[0]);

	//Amy
	helperFunctions.ReplaceFile("system\\SET1600A.BIN", "system\\levels\\Chaos 2\\Amy-Chaos2.bin");
	helperFunctions.RegisterStartPosition(Characters_Amy, Chaos2_StartPositions[0]);

	//Big
	helperFunctions.ReplaceFile("system\\SET1600B.BIN", "system\\levels\\Chaos 2\\Big-Chaos2.bin");
	helperFunctions.RegisterStartPosition(Characters_Big, Chaos2_StartPositions[0]);

	//Gamma
	helperFunctions.ReplaceFile("system\\SET1600E.BIN", "system\\levels\\Chaos 2\\Gamma-Chaos2.bin");
	helperFunctions.RegisterStartPosition(Characters_Gamma, Chaos2_StartPositions[0]);
}