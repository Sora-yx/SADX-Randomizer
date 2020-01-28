#include "stdafx.h"
#include "Utils.h"
#include "Chaos0.h"
#include "RandomHelpers.h"
#include "Trampoline.h"

ObjectMaster* chaos0 = nullptr;

void Chaos0_LoadWithTarget() {
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	chaos0 = LoadObject((LoadObj)(3), 2, Chaos0_Main);
	chaos0->MainSub = Chaos0_Main;
	chaos0->DisplaySub = (ObjectFuncPtr)0x548360;
	//chaos0->DeleteSub = (ObjectFuncPtr)0x5481d0;
	
	obj->Data1->LoopData = (Loop*)chaos0;
	obj->Data1->Scale.x = 20;
	DeleteObject_(chaos0);
	return;
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