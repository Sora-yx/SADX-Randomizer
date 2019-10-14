#include "stdafx.h"
#include "Utils.h"
#include "Zero.h"
#include "RandomHelpers.h"


void __cdecl Zero_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, Zero_StartPositions[0]);

	//Tails
	helperFunctions.RegisterStartPosition(Characters_Tails, Zero_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Zero_StartPositions[0]);

	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, Zero_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, Zero_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, Zero_StartPositions[0]);

}

void DisableTime_Zero() {

	ControlEnabled = 0;
	TimeThing = 0;

}