#include "stdafx.h"
#include "E101.h"

TaskHook E101_Main_t((intptr_t)E101_Main);
TaskHook MK2Main_t((intptr_t)MK2_Main);

void E101_Main_R(task* tp) {

	EntityData1* data1 = (EntityData1*)tp->twp;  
	EntityData1* p1 = EntityData1Ptrs[0];

	if (!data1 || !p1)
		return;

	if (GetCollidingEntityA(data1) && p1->Status & Status_Attack && p1->CharID != Characters_Gamma)
	{
		data1->Status |= Status_Hurt;
	}

	E101_Main_t.Original(tp);
}


int timerMK2 = 0;
void MK2_Main_R(task* tp) 
{

	EntityData1* data1 = (EntityData1*)tp->twp;
	EntityData1* p1 = EntityData1Ptrs[0];

	if (GetCollidingEntityA(data1) && p1->Status & Status_Attack && p1->CharID != Characters_Gamma)
	{
		data1->Status |= Status_Hurt;
		timerMK2 = 0; //failsafe
	}

	if (data1->NextAction == 6 && data1->Action == 6)
	{
		if (++timerMK2 == 140)
		{
			data1->NextAction++;
			timerMK2 = 0;
		}
	}

	MK2Main_t.Original(tp);
}


void __cdecl E101_Init(const HelperFunctions& helperFunctions)
{
	WriteData<16>((int*)0x5672AE, 0x90); //fix AI breaking the fight

	if (!isKHMod) 
	{
		E101_Main_t.Hook(E101_Main_R);
		MK2Main_t.Hook(MK2_Main_R);
		WriteData<1>((int*)0x56BBF4, 160); //prevent MK2 to move to the next phase, we will manually do it to give more time to the player to react for non gamma characters.
	}

	for (int i = 0; i < 8; i++) 
	{
		helperFunctions.RegisterStartPosition(i, E101_StartPositions[0]);
		helperFunctions.RegisterStartPosition(i, E101R_StartPositions[0]);
	}

	helperFunctions.ReplaceFile("system\\SETE101RS.bin", "system\\sets\\SETE101RS.bin");
	helperFunctions.ReplaceFile("system\\SETE101S.bin", "system\\sets\\SETE101S.bin");

	//just in case
	helperFunctions.ReplaceFile("system\\SETE101RS_DC.bin", "system\\sets\\SETE101RS.bin");
	helperFunctions.ReplaceFile("system\\SETE101S_DC.bin", "system\\sets\\SETE101S.bin");
}