#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"

extern int CurrentAI;

PVMEntry E101ObjectTextures[] = {
	{ "E102_EFF_TEXLIST", (TexList*)0x91C570 },
	{ 0 }
};

void __cdecl E101Objects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	//TexLists_Obj[LevelIDs_E101] = E101ObjectTextures;
}


void E101Target()
{

	/*ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	ObjectMaster* e101 = LoadObject((LoadObj)(2), 2, E101_Main);
	*/

	

	return LoadE101();

}

void __cdecl E101_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//E101Objects_Init(path, helperFunctions);
}