#include "stdafx.h"
#include "Utils.h"
#include "Chaos6.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include "Trampoline.h"
#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Chaos 6\\" B ".bin")

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

int Chaos6_ReturnCharacter() { 

	if (CurrentCharacter == Characters_Sonic && CurrentAct == 0 || CurrentCharacter == Characters_Knuckles && CurrentAct == 1 || CurrentCharacter == Characters_Big && Vanilla && CurrentAct == 0)
		return GetCurrentCharacterID();

	if (CurrentAct != 1)
		return (unsigned int)Characters_Sonic;
	else
		return (unsigned int)Characters_Knuckles;
}


void __cdecl Chaos6_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	//trick the game to make it think we are playing Sonic or Knuckles, Fix Chaos 6 Behavior, make the bombs spawn When not Sonic / Knuckles.
	WriteCall((void*)0x55a17d, Chaos6_ReturnCharacter);
	WriteCall((void*)0x557a5f, Chaos6_ReturnCharacter);
	WriteCall((void*)0x557b32, Chaos6_ReturnCharacter);
	WriteCall((void*)0x5598e5, Chaos6_ReturnCharacter);
	WriteCall((void*)0x5592df, Chaos6_ReturnCharacter);
	WriteCall((void*)0x5594c8, Chaos6_ReturnCharacter);
	WriteCall((void*)0x55a580, Chaos6_ReturnCharacter);
	WriteCall((void*)0x559d3a, Chaos6_ReturnCharacter);  //Display Chaos 6 life gauge while using anoter character than what the game expects, and fix camera issue.
	
	//Sonic
	ReplaceSET("SET1800S", "Sonic-Chaos6-S");
	ReplaceSET("SET1801S", "Sonic-Chaos6-K");
	helperFunctions.RegisterStartPosition(Characters_Sonic, Chaos6_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, Chaos6_StartPositions_K[0]);

	//Tails
	ReplaceSET("SET1800M", "Tails-Chaos6-S");
	ReplaceSET("SET1801M", "Tails-Chaos6-K");
	helperFunctions.RegisterStartPosition(Characters_Tails, Chaos6_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, Chaos6_StartPositions_K[0]);

	//Knuckles
	ReplaceSET("SET1800K", "Knux-Chaos6-S");
	ReplaceSET("SET1801K", "Knux-Chaos6-K");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Chaos6_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Chaos6_StartPositions_K[0]);

	//Amy
	ReplaceSET("SET1800A", "Amy-Chaos6-S");
	ReplaceSET("SET1801A", "Amy-Chaos6-K");
	helperFunctions.RegisterStartPosition(Characters_Amy, Chaos6_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, Chaos6_StartPositions_K[0]);

	//Big
	ReplaceSET("SET1800B", "Big-Chaos6-S");
	ReplaceSET("SET1801B", "Big-Chaos6-K");
	helperFunctions.RegisterStartPosition(Characters_Big, Chaos6_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, Chaos6_StartPositions_K[0]);

	//Gamma
	ReplaceSET("SET1800E", "Gamma-Chaos6-S");
	ReplaceSET("SET1801E", "Gamma-Chaos6-K");
	helperFunctions.RegisterStartPosition(Characters_Gamma, Chaos6_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, Chaos6_StartPositions_K[0]);
}