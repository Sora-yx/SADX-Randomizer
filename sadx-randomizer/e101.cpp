#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"
#include "Trampoline.h"

extern int CurrentAI;

PVMEntry E101ObjectTextures[] = {
	{ "E102_EFF_TEXLIST", (TexList*)0x91C570 },
	{ 0 }
};

void __cdecl E101Objects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	//TexLists_Obj[LevelIDs_E101] = E101ObjectTextures;
}

/*
void Load_E101_R(ObjectMaster* obj);
Trampoline Load_E101_t(0x568090, 0x568097, Load_E101_R);

void Load_E101_R(ObjectMaster* obj) {

	EntityData1* data1;

	ObjectMaster* toto = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity_RegularChara);
	//ObjectMaster* e101 = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, E101_Main);
	toto->Data1->LoopData = (Loop*)obj;
	toto->Data1->Scale.x = 20;

	ObjectFunc(origin, Load_E101_t.Target());
	origin(obj);
	return;
}

*/



void __cdecl E101_Init(const char* path, const HelperFunctions& helperFunctions)
{

}