#include "stdafx.h"
#include "Utils.h"
#include "data\EggHornet.h"
#include "RandomHelpers.h"


void __cdecl EggHornet_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	//Sonic
	helperFunctions.RegisterStartPosition(Characters_Sonic, EH_StartPositions[0]);


	//Tails
	helperFunctions.RegisterStartPosition(Characters_Tails, EH_StartPositions[0]);

	//Knuckles
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EH_StartPositions[0]);


	//Amy
	helperFunctions.RegisterStartPosition(Characters_Amy, EH_StartPositions[0]);

	//Big
	helperFunctions.RegisterStartPosition(Characters_Big, EH_StartPositions[0]);
	//Gamma
	helperFunctions.RegisterStartPosition(Characters_Gamma, EH_StartPositions[0]);

}