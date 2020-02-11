#include "stdafx.h"
#include "Utils.h"
#include "SandHill.h"
#include "RandomHelpers.h"

int GetCurrentCharacterSD() {

	if (CurrentCharacter > Characters_Tails)
	{
		WriteData<1>((void*)0x798306, 0x84);
		WriteData<1>((void*)0x7983c4, 0x7F);
	}
	else
	{
		fixTCCart();
	}

	return GetCurrentCharacterID();

}

//Add rings every Checkpoint for cart speed.
void AddRingSandHill() {
	PlaySound(0x15, 0, 0, 0);

	if (CurrentLevel == LevelIDs_SandHill && CurrentCharacter > Characters_Tails)
		AddRings(10);

	return;
}


void __cdecl SandHill_Init(const char* path, const HelperFunctions& helperFunctions)
{

	WriteCall((void*)0x423717, GetCurrentCharacterSD);
	WriteCall((void*)0x5981d8, AddRingSandHill);
	WriteCall((void*)0x423720, GetCurrentCharacterSD);

	//Sonic
	helperFunctions.ReplaceFile("system\\SETSBOARD00S.bin", "system\\levels\\Sand Hill\\Sonic-SD.bin");

	helperFunctions.ReplaceFile("system\\CAMSBOARD00S.BIN", "system\\cam\\CAMSBOARD00S.BIN");

	//Tails
	helperFunctions.ReplaceFile("system\\SETSBOARD00M.bin", "system\\levels\\Sand Hill\\Tails-SD.bin");

	helperFunctions.ReplaceFile("system\\CAMSBOARD00M.BIN", "system\\cam\\CAMSBOARD00M.BIN");

	//Knuckles
	helperFunctions.ReplaceFile("system\\SETSBOARD00K.bin", "system\\levels\\Sand Hill\\Knux-SD.bin");

	helperFunctions.RegisterStartPosition(Characters_Knuckles, SandHill_StartPositions[0]);
	helperFunctions.ReplaceFile("system\\CAMSBOARD00K.BIN", "system\\cam\\CAMSBOARD00K.BIN");

	//Amy
	helperFunctions.ReplaceFile("system\\SETSBOARD00A.bin", "system\\levels\\Sand Hill\\Amy-SD.bin");
	helperFunctions.RegisterStartPosition(Characters_Amy, SandHill_StartPositions[0]);

	helperFunctions.ReplaceFile("system\\CAMSBOARD00A.BIN", "system\\cam\\CAMSBOARD00A.BIN");

	//Big
	helperFunctions.ReplaceFile("system\\SETSBOARD00B.bin", "system\\levels\\Sand Hill\\Big-SD.bin");
	helperFunctions.RegisterStartPosition(Characters_Big, SandHill_StartPositions[0]);

	helperFunctions.ReplaceFile("system\\CAMSBOARD00B.BIN", "system\\cam\\CAMSBOARD00B.BIN");

	//Gamma
	helperFunctions.ReplaceFile("system\\SETSBOARD00E.bin", "system\\levels\\Sand Hill\\Gamma-SD.bin");
	helperFunctions.RegisterStartPosition(Characters_Gamma, SandHill_StartPositions[0]);

	helperFunctions.ReplaceFile("system\\CAMSBOARD00E.BIN", "system\\cam\\CAMSBOARD00E.BIN");
}