#include "stdafx.h"
#include "Utils.h"
#include "EggWalker.h"
#include "RandomHelpers.h"




void __cdecl EggWalker_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, EW_StartPositions[0]);

	//Tails
	helperFunctions.RegisterStartPosition(Characters_Tails, EW_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EW_StartPositions[0]);

	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, EW_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, EW_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, EW_StartPositions[0]);

}