#include "stdafx.h"
#include "Utils.h"
#include "Chaos2.h"
#include "RandomHelpers.h"


void __cdecl Chaos2_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data


	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, Chaos2_StartPositions[0]);

	//Tails
	helperFunctions.RegisterStartPosition(Characters_Tails, Chaos2_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Chaos2_StartPositions[0]);


	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, Chaos2_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, Chaos2_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, Chaos2_StartPositions[0]);

}