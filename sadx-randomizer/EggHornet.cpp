#include "stdafx.h"
#include "data\EggHornet.h"

Trampoline* EggHornet_t;

void EggHornet_Main_R(ObjectMaster* obj) {

	EntityData1* data1 = obj->Data1;
	Check_AllocateObjectData2(obj, data1);

	ObjectFunc(origin, EggHornet_t->Target());
	origin(obj);
}


void __cdecl EggHornet_Init(const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	EggHornet_t = new Trampoline((int)EggHornet_Main, (int)EggHornet_Main + 0x7, EggHornet_Main_R);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, EH_StartPositions[0]);
}