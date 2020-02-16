#include "stdafx.h"
#include "Utils.h"
#include "Chaos0.h"
#include "RandomHelpers.h"
#include "Trampoline.h"

ObjectMaster* chaos0 = nullptr;

void Chaos0_LoadWithTarget(ObjectMaster* Chaos0Obj) {

	Chaos0_Main(Chaos0Obj);
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	obj->Data1->LoopData = (Loop*)Chaos0_Main;
	obj->Data1->Scale.x = 20;
}


void __cdecl Chaos0_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, Chaos0_StartPositions[0]);

	//Tails
	helperFunctions.RegisterStartPosition(Characters_Tails, Chaos0_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Chaos0_StartPositions[0]);

	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, Chaos0_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, Chaos0_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, Chaos0_StartPositions[0]);
}