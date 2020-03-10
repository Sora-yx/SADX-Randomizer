#include "stdafx.h"
#include "Utils.h"
#include "EggWalker.h"
#include "RandomHelpers.h"
#include "Trampoline.h"


//Trampoline Egg walker's Foot animation object to load it with an object gamma can target
Trampoline  Obj2_LoadWithTarget_T(0x5768e0, 0x5768e5, Obj2_LoadWithTarget_R);
void Obj2_LoadWithTarget_R(ObjectMaster* obj) {

	ObjectMaster* Target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntitySmallOBJ);
	Target->Data1->LoopData = (Loop*)obj;
	Target->Data1->Scale.x = 10;

	ObjectFunc(origin, Obj2_LoadWithTarget_T.Target());
	origin(obj);

	return;
}

//Same
Trampoline  Obj_LoadWithTarget_T(0x576a90, 0x576a95, Obj_LoadWithTarget_R);

void Obj_LoadWithTarget_R(ObjectMaster* obj) {

	ObjectMaster* Target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntitySmallOBJ);
	Target->Data1->LoopData = (Loop*)obj;
	Target->Data1->Scale.x = 10;

	ObjectFunc(origin, Obj_LoadWithTarget_T.Target());
	origin(obj);

	return;
}

//Trampoline Egg walker to load it with an object gamma can target
Trampoline EggWalker_LoadWithTarget_T(0x576780, 0x576787, EggWalker_LoadWithTarget_R);

void EggWalker_LoadWithTarget_R() {

	ObjectMaster* Egg;

	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
	Egg = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 1, EggWalker_Main);
	obj->Data1->LoopData = (Loop*)Egg;
	obj->Data1->Scale.x = 7;

	if (Egg != (ObjectMaster*)0x0) {
		Egg->MainSub = EggWalker_Main;
		Egg->DisplaySub = (ObjectFuncPtr)0x576490;
	}

	return;
}

void EggWalker_HP() {

	if (isCriticalMode)
		Life_Max = 7;
	else
		Life_Max = 5;

}

void EggWalker_DisplayHP() {

	if (isCriticalMode)
		BossHP_Stuff(600, 0x18, 7);
	else
		BossHP_Stuff(600, 0x18, 5);
}

void EggWalker_Music() {


	switch (CurrentCharacter)
	{
	case Characters_Sonic:
	case Characters_Amy:
		PlayVoice_R(6020);
		break;
	case Characters_Gamma:
		PlayVoice_R(1184);
		break;
	default:
		PlayVoice_R(813);
		break;
	}

	return PlayMusic_R(MusicIDs_jingle_5);
}


void __cdecl EggWalker_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, EW_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EW_StartPositions[0]);

	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, EW_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, EW_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, EW_StartPositions[0]);
}