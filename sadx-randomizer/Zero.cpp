#include "stdafx.h"
#include "Zero.h"


CollisionData colZ = { 0, 0, 0x77, 0, 0x800400, {0, 0, 0}, { 6.0, 6.0, 0.0 }, 0, 0 };
Trampoline ZeroHead_t((int)Zero_HeadOpen, (int)Zero_HeadOpen + 0x5, ZeroHead_R);

void ZeroHead_R(ObjectMaster* obj) {

	if (!BossHP) 
		return;

	ObjectFunc(original, ZeroHead_t.Target());
	original(obj);
}


void TargetableSMALLEntity(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1;

	if (data->Action == 0) {
		AllocateObjectData2(obj, obj->Data1);

		//if the scale is specified, temporary set the collision scale to it.
		if (data->Scale.x) {
			colZ.scale.x = data->Scale.x;
			Collision_Init(obj, &colZ, 1, 2u);
			colZ.scale.x = 6;
		}
		else {
			Collision_Init(obj, &colZ, 1, 2u);
		}

		data->Action = 1;
	}
	else {
		ObjectMaster* boss = (ObjectMaster*)obj->Data1->LoopData;

		if (!boss || !boss->Data1) {
			CheckThingButThenDeleteObject(obj);
			return;
		}

		if (EntityData1Ptrs[0]->CharID != Characters_Gamma)
			return;

		data->Position = boss->Data1->Position;
		data->Position.y += 15;


		if (OhNoImDead(obj->Data1, (ObjectData2*)obj->Data2))
		{
			if (boss->Data1->Action >= 8)
				Zero_Damage(boss);

			CheckThingButThenDeleteObject(obj);

			//if it is set, don't reload the target object
			if (data->CharID == 1 || !BossHP)
				return;

			ObjectMaster* target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableSMALLEntity);
			target->Data1->LoopData = (Loop*)boss;
		}
		else
		{
			AddToCollisionList(data);
		}
		
	}
}


void DisableTime_Zero() {
	ControlEnabled = 0;
	TimeThing = 0;
}

Trampoline ZeroBoss_Main_t((int)ZeroBoss_Main, (int)ZeroBoss_Main + 0x5, Load_ZeroMain_WithTarget);

void Load_ZeroMain_WithTarget(ObjectMaster* obj) {

	obj->Data1->Action = obj->Data1->Action;
	if (obj != nullptr && obj->Data1->Action <= 3)
	{
		ObjectMaster* a1 = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableSMALLEntity);
		a1->Data1->LoopData = (Loop*)obj;
		a1->Data1->Scale.x = 8;
		obj->Data1->Action = obj->Data1->Action;
	}

	ObjectFunc(original, ZeroBoss_Main_t.Target());
	original(obj);
}


void __cdecl Zero_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteCall((void*)0x5872ed, DisableTime_Zero); //Prevent character from hiting Zero again once its defeated.

	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Zero_StartPositions[0]);

	//Sonic

	helperFunctions.ReplaceFile("system\\SETZEROS.bin", "system\\levels\\SETZEROS.bin");
}