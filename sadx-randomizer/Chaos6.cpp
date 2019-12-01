#include "stdafx.h"
#include "Utils.h"
#include "Chaos6.h"
#include "RandomHelpers.h"


void __cdecl Chaos6_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteData<1>((void*)0x5598f0, 0x00); //makes the bomb spawns for every character. (if ivar == 0)
	WriteData<1>((void*)0x5598f1, 0x0075); //makes the bomb spawns for every character part 2. (convert JZ to JNZ this is important.)
	WriteData<1>((void*)0x55a189, 0x0075); //Force Chaos to act like if you were playing Sonic or Knuckles. (attack, pattern etc.)
	WriteData<5>((void*)0x559d3a, 0x90); //Display Chaos 6 life gauge while using a wrong character and fix camera issue.

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