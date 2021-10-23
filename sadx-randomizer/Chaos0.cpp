#include "stdafx.h"
#include "Chaos0.h"

Trampoline* Chaos0_t;

void Chaos0_Main_R(ObjectMaster* obj) {

	EntityData1* data1 = obj->Data1;
	Check_AllocateObjectData2(obj, data1);

	ObjectFunc(origin, Chaos0_t->Target());
	origin(obj);
}


void __cdecl Chaos0_Init(const HelperFunctions& helperFunctions)
{
	Chaos0_t = new Trampoline((int)Chaos0_Main, (int)Chaos0_Main + 0x7, Chaos0_Main_R);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos0_StartPositions[0]);
}