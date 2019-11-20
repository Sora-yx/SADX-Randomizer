#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"

//LandTableInfo* ECAct1;

//void __cdecl EmeraldCoast_Init(const char* path, const HelperFunctions& helperFunctions) 

HelperFunctions extern help;
extern int CustomLayout;
extern bool Race;
extern bool Missions;


void SHAct4() {

	CustomLayout = 0;

	CustomLayout = rand() % 2;

	switch (CustomLayout)
	{
	case 0:
		LoadSetFile(0, "SBoard00");
		break;
	case 1:
		LoadSetFile(0, "SBoard02"); //looks like the real layout difference is hardcoded tho
		break;
	}

}


void __cdecl SandHill_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data


	//Sonic
	helperFunctions.ReplaceFile("system\\SETSBOARD00S.bin", "system\\levels\\Sand Hill\\Sonic-SandHill-Act1.bin");
	helperFunctions.ReplaceFile("system\\SETSBOARD02S.bin", "system\\levels\\Sand Hill\\Sonic-SandHill-Act2.bin");

	helperFunctions.ReplaceFile("system\\CAMSBOARD00S.BIN", "system\\cam\\CAMSBOARD00S.BIN");


	//Tails
	helperFunctions.ReplaceFile("system\\SETSBOARD00M.bin", "system\\levels\\Sand Hill\\Tails-SandHill-Act1.bin");
	helperFunctions.ReplaceFile("system\\SETSBOARD02M.bin", "system\\levels\\Sand Hill\\Tails-SandHill-Act2.bin");


	helperFunctions.ReplaceFile("system\\CAMSBOARD00M.BIN", "system\\cam\\CAMSBOARD00M.BIN");


	//Knuckles
	helperFunctions.ReplaceFile("system\\SETSBOARD00K.bin", "system\\levels\\Sand Hill\\Knux-SandHill-Act1.bin");
	helperFunctions.ReplaceFile("system\\SETSBOARD02K.bin", "system\\levels\\Sand Hill\\Knux-SandHill-Act2.bin");


	helperFunctions.ReplaceFile("system\\CAMSBOARD00K.BIN", "system\\cam\\CAMSBOARD00K.BIN");


	//Amy
	helperFunctions.ReplaceFile("system\\SETSBOARD00A.bin", "system\\levels\\Sand Hill\\Amy-SandHill-Act1.bin");
	helperFunctions.ReplaceFile("system\\SETSBOARD02A.bin", "system\\levels\\Sand Hill\\Amy-SandHill-Act2.bin");


	helperFunctions.ReplaceFile("system\\CAMSBOARD00A.BIN", "system\\cam\\CAMSBOARD00A.BIN");


	//Big
	helperFunctions.ReplaceFile("system\\SETSBOARD00B.bin", "system\\levels\\Sand Hill\\Big-SandHill-Act1.bin");
	helperFunctions.ReplaceFile("system\\SETSBOARD02B.bin", "system\\levels\\Sand Hill\\Big-SandHill-Act2.bin");


	helperFunctions.ReplaceFile("system\\CAMSBOARD00B.BIN", "system\\cam\\CAMSBOARD00B.BIN");


	//Gamma
	helperFunctions.ReplaceFile("system\\SETSBOARD00E.bin", "system\\levels\\Sand Hill\\Gamma-SandHill-Act1.bin");
	helperFunctions.ReplaceFile("system\\SETSBOARD02E.bin", "system\\levels\\Sand Hill\\Gamma-SandHill-Act2.bin");

	helperFunctions.ReplaceFile("system\\CAMSBOARD00E.BIN", "system\\cam\\CAMSBOARD00E.BIN");

}

