#include "stdafx.h"
#include "Utils.h"
#include "data\EggHornet.h"
#include "RandomHelpers.h"
#include "Trampoline.h"





void EggHornet_LoadWithTarget() {

	ObjectMaster* egghornet;

	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	egghornet = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 1, EggHornet_Main);
	obj->Data1->LoopData = (Loop*)egghornet;
	obj->Data1->Scale.x = 20;

	if (egghornet != (ObjectMaster*)0x0) {
		FunctionPointer(void, sub_571B60, (ObjectMaster * obj), 0x571B60);
		sub_571B60(egghornet);
		egghornet->MainSub = EggHornet_Main;
		egghornet->DisplaySub = (ObjectFuncPtr)0x571F20;
		if (CurrentCharacter != Characters_Gamma) //make the game crash for Gamma lol
		{
			egghornet->DeleteSub = (ObjectFuncPtr)0x571fe0;
		}
	}

	return;
}





void __cdecl EggHornet_Init(const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteJump((void*)0x572230, EggHornet_LoadWithTarget);
	WriteData<5>((void*)0x572836, 0x90);
	WriteData<5>((void*)0x571ffa, 0x90);
	WriteData<5>((void*)0x571fed, 0x90);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, EH_StartPositions[0]);
}