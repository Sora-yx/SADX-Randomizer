#include "stdafx.h"
#include "Chaos0.h"

TaskHook Chaos0_t((intptr_t)Chaos0_Main);

void Chaos0_Main_R(ObjectMaster* obj) {

	EntityData1* data1 = obj->Data1;
	Check_AllocateObjectData2(obj, data1);

	Chaos0_t.Original((task*)obj);
}


void __cdecl Chaos0_Init(const HelperFunctions& helperFunctions)
{
	Chaos0_t.Hook((TaskFuncPtr)Chaos0_Main_R);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos0_StartPositions[0]);
}