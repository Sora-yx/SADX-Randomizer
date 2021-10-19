#include "stdafx.h"
#include "Chaos2.h"

Trampoline* Chaos2_t;

void Chaos2_Main_R(ObjectMaster* obj) {

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

			if (cwk->bwk.action == 2)
			{
				E102KillCursor((ObjectMaster*)obj);
			}
		}
	}

	ObjectFunc(origin, Chaos2_t->Target());
	origin(obj);
}

void __cdecl Chaos2_Init(const HelperFunctions& helperFunctions)
{
	Chaos2_t = new Trampoline((int)Chaos2_Main, (int)Chaos2_Main + 0x6, Chaos2_Main_R);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos2_StartPositions[0]);

}