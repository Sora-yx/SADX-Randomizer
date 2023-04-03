#include "stdafx.h"
#include "data\EggHornet.h"

TaskHook EggHornet_t((intptr_t)EggHornet_Main);

void EggHornet_Main_R(task* tp) {

	ObjectMaster* obj = (ObjectMaster*)tp;
	EntityData1* data1 = obj->Data1;
	Check_AllocateObjectData2(obj, data1);

	EggHornet_t.Original(tp);
}


void __cdecl EggHornet_Init(const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	EggHornet_t.Hook(EggHornet_Main_R);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, EH_StartPositions[0]);
}