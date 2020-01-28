#include "stdafx.h"
#include "Utils.h"
#include "Chaos6.h"
#include "RandomHelpers.h"
#include "Trampoline.h"


void Chaos6_LoadWithTarget() {
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	obj->Data1->LoopData = (Loop*)LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, Chaos6_Main);
}

void IceBomb_Load_r(ObjectMaster* obj);
Trampoline IceBomb_Load_t(0x55CA20, 0x55CA26, IceBomb_Load_r);

void IceBomb_Load_r(ObjectMaster* obj) {
	ObjectFunc(original, IceBomb_Load_t.Target());
	original(obj);

	ObjectMaster* target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	target->Data1->LoopData = (Loop*)obj;
	target->Data1->CharID = 1;
}

void __cdecl Chaos6_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteData<1>((void*)0x5598f0, 0x00); //makes the bomb spawns for every character. (if ivar == 0)
	WriteData<1>((void*)0x5598f1, 0x0075); //makes the bomb spawns for every character part 2. (convert JZ to JNZ this is important.)
	WriteData<1>((void*)0x55a189, 0x0075); //Force Chaos to act like if you were playing Sonic or Knuckles. (attack, pattern etc.)
	WriteData<5>((void*)0x559d3a, 0x90); //Display Chaos 6 life gauge while using anoter character than what the game expects, and fix camera issue.

	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, Chaos6_StartPositions[0]);

	//Tails
	helperFunctions.RegisterStartPosition(Characters_Tails, Chaos6_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Chaos6_StartPositions[0]);

	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, Chaos6_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, Chaos6_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, Chaos6_StartPositions[0]);

}