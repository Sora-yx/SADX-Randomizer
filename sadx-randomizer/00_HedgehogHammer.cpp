#include "stdafx.h"

int HedgehogHammerTrick() {
	return Characters_Amy;
}

bool LimitCustomFlag = false;

VoidFunc(sub_6265C0, 0x6265C0);
void HedgehogHammerResult() {

	if (GameMode != GameModes_Trial && RNGStages) 
	{

		if (SelectedCharacter == 6) //Fix Super Sonic Story giving sonic layout
			LastStoryFlag = 1;
		else
			LastStoryFlag = 0;

		if (!LimitCustomFlag) {
			Rings = 0;
			CustomFlag++;
			GameMode = GameModes_Adventure_Field;
			GameState = 0x5;
			LimitCustomFlag = true;
		}
	}
	else {
		sub_6265C0();
	}

	return;
}

void __cdecl HedgehogHammer_Init(const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	// 
	//trick the game to make it thinks we are playing Amy
	WriteCall((void*)0x626a34, HedgehogHammerTrick);
	WriteCall((void*)0x624b00, HedgehogHammerTrick);
	WriteCall((void*)0x62519c, HedgehogHammerTrick);

	//force the game to chain level after finishing the sub game
	WriteCall((void*)0x626B28, HedgehogHammerResult);

	AddSet("SET0000S", "HH");

	AddSet("SET0000S_DC", "HH");
}