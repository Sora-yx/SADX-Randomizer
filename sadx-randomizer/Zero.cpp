#include "stdafx.h"
#include "Zero.h"

Trampoline* ZeroBoss_t;

void DisableTime_Zero() {
	ControlEnabled = 0;
	TimeThing = 0;
}

void Zero_r(ObjectMaster* obj) {

	EntityData1* data1 = obj->Data1;
	task* tsk = (task*)obj;
	task* tsk2;
	EntityData1* data = (EntityData1*)tsk->mwp;
	NJS_POINT3 v15;
	ObjectMaster* chaos = obj;
	chaoswk* cwk = (chaoswk*)obj->UnknownB_ptr;

	if (obj)
	{
		if (data1->Action == 0)
		{
			AllocateObjectData2(chaos, data1);
		}
	}

	if (cwk) {

		if (cwk->bwk.action == 11)
		{
			tsk2 = GetE102BeamTaskPTR((task*)tsk->mwp[1].work.l);
			if (tsk)
			{
				v15.x = tsk->twp->pos.x;
				v15.y = tsk->twp->pos.y;
				v15.z = tsk->twp->pos.z;
			}
			else
			{
				v15 = { 0.0, 0.0, 0.0 };
			}
			//dsPlay_oneshot(155, 0, 0, 0);
			E102Hit(&v15, -15.0);
			E102KillCursor((task*)obj);
		}
	}

	ObjectFunc(origin, ZeroBoss_t->Target());
	origin(obj);

}


void __cdecl Zero_Init(const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteCall((void*)0x5872ed, DisableTime_Zero); //Prevent character from hiting Zero again once its defeated.

	ZeroBoss_t = new Trampoline((int)ZeroBoss_Main, (int)ZeroBoss_Main + 0x5, Zero_r);

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Zero_StartPositions[0]);

	//Sonic

	helperFunctions.ReplaceFile("system\\SETZEROS.bin", "system\\sets\\SETZEROS.bin");
	helperFunctions.ReplaceFile("system\\SETZEROS_DC.bin", "system\\sets\\SETZEROS.bin");
}