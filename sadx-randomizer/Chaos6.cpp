#include "stdafx.h"
#include "Chaos6.h"

#define AddSet(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\sets\\" B ".bin")


int Chaos6_ReturnCharacter() { 

	if (CurrentCharacter == Characters_Sonic && CurrentAct == 0 || CurrentCharacter == Characters_Knuckles && CurrentAct == 1 || CurrentCharacter == Characters_Big && Vanilla && CurrentAct == 0)
		return (unsigned int)GetCurrentCharacterID();

	if (CurrentAct != 1)
	{
		CurrentStageVersion = SonicVersion;
		return (unsigned int)Characters_Sonic;
	}
	else
	{
		CurrentStageVersion = KnucklesVersion;
		return (unsigned int)Characters_Knuckles;
	}
}


void __cdecl Chaos6_Init(const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	//Chaos6_t = new Trampoline((int)Chaos6_Main, (int)Chaos6_Main + 0x8, Chaos6_Main_R);


	if (!isKHMod) {
		//trick the game to make it think we are playing Sonic or Knuckles, Fix Chaos 6 Behavior, make the bombs spawn When not Sonic / Knuckles.
		WriteCall((void*)0x55a17d, Chaos6_ReturnCharacter);
		WriteCall((void*)0x557a5f, Chaos6_ReturnCharacter);
		WriteCall((void*)0x557b32, Chaos6_ReturnCharacter);
		WriteCall((void*)0x5598e5, Chaos6_ReturnCharacter);
		WriteCall((void*)0x5592df, Chaos6_ReturnCharacter);
		WriteCall((void*)0x5594c8, Chaos6_ReturnCharacter);
		WriteCall((void*)0x55a580, Chaos6_ReturnCharacter);
		WriteCall((void*)0x559d3a, Chaos6_ReturnCharacter);  //Display Chaos 6 life gauge while using anoter character than what the game expects, and fix camera issue.
	}
	

	for (int i = 0; i < 8; i++) {
		helperFunctions.RegisterStartPosition(i, Chaos6_StartPositions[0]);
		helperFunctions.RegisterStartPosition(i, Chaos6_StartPositions_K[0]);
	}
	
	helperFunctions.ReplaceFile("system\\SET1801S.bin", "system\\sets\\SET1801S.bin");
	helperFunctions.ReplaceFile("system\\SET1801S_DC.bin", "system\\sets\\SET1801S_DC.bin");
	helperFunctions.ReplaceFile("system\\SET1801K_DC.bin", "system\\sets\\SET1801K_DC.bin");

}