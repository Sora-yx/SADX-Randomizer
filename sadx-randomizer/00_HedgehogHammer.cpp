#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Hedgehog Hammer\\" B ".bin")



void __cdecl HedgehogHammer_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	
	WriteCall((void*)0x626a34, HedgehogHammerTrick);
	WriteCall((void*)0x624b00, HedgehogHammerTrick);
	WriteCall((void*)0x62519c, HedgehogHammerTrick);

	WriteData<1>((void*)0x62662F, 0x06);
	WriteCall((void*)0x626744, HedgehogHammerResult);

	//Sonic
	ReplaceSET("SET0000S", "Sonic-HH");
	//Tails
	ReplaceSET("SET0000M", "Tails-HH");
	//Knuckles
	ReplaceSET("SET0000K", "Knux-HH");
	//Amy
	ReplaceSET("SET0000A", "Amy-HH");
	//Big
	ReplaceSET("SET0000B", "Big-HH");
	//Gamma
	ReplaceSET("SET0000E", "Gamma-HH");
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