#include "stdafx.h"
#include "Utils.h"
#include "Chaos4.h"
#include "RandomHelpers.h"
#include "Trampoline.h"

ObjectFunc(Chaos4_Delete, 0x552750);


//Trampoline Chaos4_LoadWithTarget_T(0x552bb0, 0x552bb7, Chaos4_LoadWithTarget_R);

void Chaos4_LoadWithTarget_R(ObjectMaster* Chaos4) {

	if (CurrentCharacter == Characters_Gamma)
	{
		ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
		Chaos4 = LoadObject((LoadObj)(3), 1, Chaos4_Main);
		obj->Data1->LoopData = (Loop*)Chaos4;
		obj->Data1->Scale.x = 30;
		return;
	}
	else
	{
		Chaos4 = LoadObject((LoadObj)(3), 1, Chaos4_Main);
		Chaos4->DeleteSub = Chaos4_Delete;
		//ObjectFunc(origin, Chaos4_LoadWithTarget_T.Target());
		//origin(Chaos4);
		return;
	}
}

void __cdecl Chaos4_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data;
	WriteData<2>((void*)0x5525f9, 0x90); //Reduce Chaos 4 HP for everyone.


	for (int i = 4; i < 8; i++)
		helperFunctions.RegisterStartPosition(i, Chaos4_StartPositions[0]);
}