#include "stdafx.h"
#include "Chaos2.h"

Trampoline* Chaos2_t;

void Chaos2_Main_R(ObjectMaster* obj) {

	EntityData1* data1 = obj->Data1;

	Check_AllocateObjectData2(obj, data1);

	ObjectFunc(origin, Chaos2_t->Target());
	origin(obj);
}

void __cdecl Chaos2_Init(const HelperFunctions& helperFunctions)
{
	Chaos2_t = new Trampoline((int)Chaos2_Main, (int)Chaos2_Main + 0x6, Chaos2_Main_R);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos2_StartPositions[0]);

}