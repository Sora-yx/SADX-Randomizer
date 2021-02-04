#include "stdafx.h"
#include "Utils.h"
#include "E101.h"

extern int CurrentAI;


void __cdecl E101Objects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	//TexLists_Obj[LevelIDs_E101] = E101ObjectTextures;
}

void Load_E101R_R(ObjectMaster* obj);
Trampoline Load_E101R_t(0x56c0b0, 0x56c0b0 + 0x5, Load_E101R_R);

void Load_E101R_R(ObjectMaster* obj) {


	obj->Data1 = obj->Data1;

	ObjectFunc(origin, Load_E101R_t.Target());
	origin(obj);





}

VoidFunc(CheckDmg, 0x566cd0);
void Load_E101_R(ObjectMaster* obj);
Trampoline Load_E101_t((int)E101_Main, (int)E101_Main +0x5, Load_E101_R);

void Load_E101_R(ObjectMaster* obj) {

	EntityData1* data1;
	obj->Data1->Action = obj->Data1->Action;

	if (obj->Data1->Action == 0)
		LoadPVM("E102_EFF", &E102_EFF_TEXLIST);

	if (IsPlayerInsideSphere(&obj->Data1->Position, 10))
	{
			obj->Data1->Action = 5;
			obj->Data1->Status = 9;
	}

	//ObjectMaster* toto = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity_RegularChara);
	//ObjectMaster* e101 = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, E101_Main);
	//toto->Data1->LoopData = (Loop*)obj;
	//toto->Data1->Scale.x = 20;

	ObjectFunc(origin, Load_E101_t.Target());
	origin(obj);
	return;
}


void __cdecl E101_Init(const char* path, const HelperFunctions& helperFunctions)
{

	for (int i = 0; i < 8; i++) {
		helperFunctions.RegisterStartPosition(i, E101_StartPositions[0]);
		helperFunctions.RegisterStartPosition(i, E101R_StartPositions[0]);

	}
}