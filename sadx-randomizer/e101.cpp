#include "stdafx.h"
#include "Utils.h"
#include "E101.h"

Trampoline* E101_Main_t;
Trampoline* MK2Main_t;


void E101_Main_R(ObjectMaster* obj) {

	EntityData1* data1 = obj->Data1;
	EntityData1* p1 = EntityData1Ptrs[0];

	if (GetCollidingEntityA(data1) && p1->Status & Status_Attack && p1->CharID != Characters_Gamma)
	{
		data1->Status |= Status_Hurt;
		if (p1->CharID < Characters_Gamma)
			EnemyBounceThing(0, 0, 2, 0);
	}

	ObjectFunc(origin, E101_Main_t->Target());
	origin(obj);
}


int timerMK2 = 0;
void MK2_Main_R(ObjectMaster* obj) {

	EntityData1* data1 = obj->Data1;
	EntityData1* p1 = EntityData1Ptrs[0];

	if (GetCollidingEntityA(data1) && p1->Status & Status_Attack && p1->CharID != Characters_Gamma)
	{
		data1->Status |= Status_Hurt;
		timerMK2 = 0; //failsafe
		if (p1->CharID < Characters_Gamma)
			EnemyBounceThing(0, 0, 2, 0);
	}

	if (data1->NextAction == 6 && data1->Action == 6)
	{
		if (++timerMK2 == 140)
		{
			data1->NextAction++;
			timerMK2 = 0;
		}
	}

	ObjectFunc(origin, MK2Main_t->Target());
	origin(obj);
}



void __cdecl E101_Init(const char* path, const HelperFunctions& helperFunctions)
{
	WriteData<1>((int*)0x56BBF4, 160); //prevent MK2 to move to the next phase, we will manually do it to give more time to the player to react for non gamma characters.

	E101_Main_t = new Trampoline((int)E101_Main, (int)E101_Main + 0x5, E101_Main_R);
	MK2Main_t = new Trampoline((int)MK2_Main, (int)MK2_Main + 0x5, MK2_Main_R);

	for (int i = 0; i < 8; i++) {
		helperFunctions.RegisterStartPosition(i, E101_StartPositions[0]);
		helperFunctions.RegisterStartPosition(i, E101R_StartPositions[0]);
	}

	helperFunctions.ReplaceFile("system\\SETE101RS.bin", "system\\sets\\SETE101RS.bin");
	helperFunctions.ReplaceFile("system\\SETE101S.bin", "system\\sets\\SETE101S.bin");
}