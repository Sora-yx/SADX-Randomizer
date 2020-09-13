#include "stdafx.h"

#define AddSet(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\sets\\" B ".bin")


void __cdecl HedgehogHammer_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	WriteCall((void*)0x626a34, HedgehogHammerTrick);
	WriteCall((void*)0x624b00, HedgehogHammerTrick);
	WriteCall((void*)0x62519c, HedgehogHammerTrick);

	WriteData<1>((char*)0x62662F, 0x06);
	WriteCall((void*)0x626744, HedgehogHammerResult);


	AddSet("SET0000S", "HH");
}

int HedgehogHammerTrick() {
	
	//trick the game to make it think we are playing Amy.
	return Characters_Amy;
}

bool LimitCustomFlag = false;

void HedgehogHammerResult() {

	if (!LimitCustomFlag) //prevent the game to call this several times.
	{
		if (SelectedCharacter == 6) //Fix Super Sonic Story giving sonic layout
			LastStoryFlag = 1;
		else
			LastStoryFlag = 0;

		Rings = 0;
		CustomFlag++;
		GameMode = GameModes_Adventure_Field;
		GameState = 0x5;
		LimitCustomFlag = true;
	}
	
	return;
}