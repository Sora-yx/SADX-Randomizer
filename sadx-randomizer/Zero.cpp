#include "stdafx.h"
#include "Utils.h"
#include "Zero.h"
#include "RandomHelpers.h"


void DisableTime_Zero() {

	ControlEnabled = 0;
	TimeThing = 0;

}

void __cdecl Zero_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	WriteCall((void*)0x5872ed, DisableTime_Zero); //Prevent character from hiting Zero again once it's defeated.

	//Sonic
	helperFunctions.ReplaceFile("system\\SETZEROS.bin", "system\\levels\\Zero\\Sonic-Zero.bin");
	helperFunctions.RegisterStartPosition(Characters_Sonic, Zero_StartPositions[0]);

	//Tails
	helperFunctions.ReplaceFile("system\\SETZEROM.bin", "system\\levels\\Zero\\Tails-Zero.bin");
	helperFunctions.RegisterStartPosition(Characters_Tails, Zero_StartPositions[0]);

	//Knuckles
	helperFunctions.ReplaceFile("system\\SETZEROK.bin", "system\\levels\\Zero\\Knux-Zero.bin");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Zero_StartPositions[0]);

	//Amy
	helperFunctions.ReplaceFile("system\\SETZEROA.bin", "system\\levels\\Zero\\Amy-Zero.bin");
	helperFunctions.RegisterStartPosition(Characters_Amy, Zero_StartPositions[0]);

	//Big
	helperFunctions.ReplaceFile("system\\SETZEROB.bin", "system\\levels\\Zero\\Big-Zero.bin");
	helperFunctions.RegisterStartPosition(Characters_Big, Zero_StartPositions[0]);
	//Gamma
	helperFunctions.ReplaceFile("system\\SETZEROE.bin", "system\\levels\\Zero\\Gamma-Zero.bin");
	helperFunctions.RegisterStartPosition(Characters_Gamma, Zero_StartPositions[0]);

}

