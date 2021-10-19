#include "stdafx.h"
#include "Chaos0.h"

Trampoline* Chaos0_t;

void Chaos0_Main_R(ObjectMaster* obj) {

	EntityData1* data1 = obj->Data1;
	task* tsk = (task*)obj;
	EntityData1* data = (EntityData1*)tsk->mwp;
	NJS_POINT3 v15;
	ObjectMaster* chaos = obj;
	chaoswk* cwk = (chaoswk*)obj->UnknownB_ptr;


	if (CurrentCharacter == Characters_Gamma) {
		if (obj)
		{
			if (data1->Action == 0)
			{
				AllocateObjectData2(chaos, data1);
				ObjectData2_SetStartPosition(obj->Data1, (ObjectData2*)obj->Data2);
			}
		}

		if (cwk) {

			if (cwk->bwk.action == 11)
			{
				E102KillCursor((ObjectMaster*)obj);
			}
		}
	}

	ObjectFunc(origin, Chaos0_t->Target());
	origin(obj);
}


void __cdecl Chaos0_Init(const HelperFunctions& helperFunctions)
{
	Chaos0_t = new Trampoline((int)Chaos0_Main, (int)Chaos0_Main + 0x7, Chaos0_Main_R);


	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos0_StartPositions[0]);
}