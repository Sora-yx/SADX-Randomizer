#include "stdafx.h"
#include "Utils.h"
#include "Chaos2.h"


void Chaos2_LoadWithTarget() {
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	obj->Data1->LoopData = (Loop*)LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, Chaos2_Main);
}

void __cdecl Chaos2_Init(const char* path, const HelperFunctions& helperFunctions)
{
	for (int i = 0; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos2_StartPositions[0]);

}