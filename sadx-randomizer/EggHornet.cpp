#include "stdafx.h"
#include "Utils.h"
#include "data\EggHornet.h"
#include "RandomHelpers.h"

void EggHornet_LoadWithTarget() {
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	ObjectMaster* egghornet = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 1, EggHornet_Main);
	obj->Data1->LoopData = (Loop*)egghornet;
	obj->Data1->Scale.x = 20;

	FunctionPointer(void, sub_571B60, (ObjectMaster * obj), 0x571B60);
	sub_571B60(egghornet);
	egghornet->MainSub = EggHornet_Main;
	egghornet->DisplaySub = (ObjectFuncPtr)0x571F20;
	//egghornet->DeleteSub = (ObjectFuncPtr)0x571FE0; //make the game crash lol
}

void GammaTarget_Init() {
	if (CurrentCharacter == Characters_Gamma)
	{
		WriteJump((void*)0x572230, EggHornet_LoadWithTarget);

	}

	return LoadCamFile(0, "0000");
}

void __cdecl EggHornet_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, EH_StartPositions[0]);

	//Tails
	helperFunctions.RegisterStartPosition(Characters_Tails, EH_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EH_StartPositions[0]);

	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, EH_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, EH_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, EH_StartPositions[0]);
}