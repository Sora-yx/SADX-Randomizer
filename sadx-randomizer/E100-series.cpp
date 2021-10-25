#include "stdafx.h"

Trampoline* E104_t;
Trampoline* E103_t;

void CheckAndHurtE100Bosses(ObjectMaster* obj) {
	EntityData1* data1 = obj->Data1;
	EntityData1* p1 = EntityData1Ptrs[0];

	if (data1->Action > 0 && p1->CharID != Characters_Gamma) {
		if (GetCollidingEntityA(data1) && (p1->Status & Status_Attack || p1->CharID == Characters_Tails && p1->Action == 20))
		{
			data1->Status |= Status_Hurt;
		}
	}
}

void FixNonGammaSoftLock(ObjectMaster* obj) {
	EntityData1* data1 = obj->Data1;
	EntityData1* p1 = EntityData1Ptrs[0];

	if (data1->NextAction == 2 && data1->Action == 0)
	{
		if (++data1->InvulnerableTime == 380) //FailSafe, because as non gamma character you can softlock, funny game lol
			signed_char_ccsi_mode = 1; //force the event to continue
	}
}


void E105Enemy_Main_R(ObjectMaster* obj) {

	if (CurrentMission >= Mission2_100Rings) {
		CheckThingButThenDeleteObject(obj);
		return;
	}

	E105Enemy_Load(obj);
}


void E104Enemy_Main_R(ObjectMaster* obj) {


	if (CurrentLevel == LevelIDs_RedMountain && CurrentMission > 0)
	{
		Check_Display_BackRing_Common(obj);
		return;
	}

	FixNonGammaSoftLock(obj);
	CheckAndHurtE100Bosses(obj);

	ObjectFunc(origin, E104_t->Target());
	origin(obj);
}


void E103Enemy_Main_R(ObjectMaster* obj) {

	EntityData1* data1 = obj->Data1;
	EntityData1* p1 = EntityData1Ptrs[0];

	if (CurrentLevel == LevelIDs_WindyValley && CurrentMission > 0)
	{
		Check_Display_BackRing_Common(obj);
		return;
	}

	FixNonGammaSoftLock(obj);
	CheckAndHurtE100Bosses(obj);

	ObjectFunc(origin, E103_t->Target());
	origin(obj);
}


void init_E100Series() {
	E103_t = new Trampoline ((int)E103_Main, (int)E103_Main + 0x7, E103Enemy_Main_R);
	E104_t = new Trampoline ((int)E104_Main, (int)E104_Main + 0x7, E104Enemy_Main_R);
}