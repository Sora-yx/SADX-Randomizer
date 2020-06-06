#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"

HelperFunctions help;

void __cdecl StartupLevels_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	help = helperFunctions;

	HedgehogHammer_Init(path, helperFunctions);
	EmeraldCoast_Init(path, helperFunctions);
	WindyValley_Init(path, helperFunctions);
	Casino_Init(path, helperFunctions);
	IceCap_Init(path, helperFunctions);
	TwinklePark_Init(path, helperFunctions);
	SpeedHighway_Init(path, helperFunctions);
	RedMountain_Init(path, helperFunctions);
	SkyDeck_Init(path, helperFunctions);
	LostWorld_Init(path, helperFunctions);
	FinalEgg_Init(path, helperFunctions);
	HotShelter_Init(path, helperFunctions);
	SandHill_Init(path, helperFunctions);

	//Boss
	Chaos0_Init(path, helperFunctions);
	Chaos2_Init(path, helperFunctions);
	Chaos4_Init(path, helperFunctions);
	Chaos6_Init(path, helperFunctions);
	EggHornet_Init(path, helperFunctions);
	EggWalker_Init(path, helperFunctions);
	EggViper_Init(path, helperFunctions);
	Zero_Init(path, helperFunctions);
	PerfectChaos_Init(path, helperFunctions);
	E101_Init(path, helperFunctions);
}


void __cdecl StartupMiscellaneous_Init(const char* path, const HelperFunctions& helperFunctions) {

	helperFunctions.ReplaceFile("system\\AVA_GTITLE0_E.PVM", "system\\textures\\AVA_GTITLE0_E.PVM"); //replace title screen
		//help.ReplaceFile("system\\CON_REGULAR.pvm", "system\\textures\\CON_REGULAR_E.PVMX"); //Test
	helperFunctions.ReplaceFile("system\\SETMCART03S.BIN", "system\\TCAct3.BIN"); //TC act 4 fix
	helperFunctions.ReplaceFile("system\\SETMCART03E.BIN", "system\\TCAct3.BIN");
	WriteCall((void*)0x44B0A4, CheckDeleteAnimThing); 

	//Random Title Card + Missions
	TitleCard_Init();

	//Stats & Value Reset
	WriteCall((void*)0x42ca4f, SoftReset_R); //Reset value and stuff properly when you Soft Reset and quit.
	WriteCall((void*)0x416b7a, TrialModeQuit_R); //Reset value and stuff properly when you Quit Trial Mode
	WriteCall((void*)0x413368, DeleteCustomFlag); //Reset flags when you create a new savefile.
	WriteCall((void*)0x42af45, AddCustomFlag);

	Credits_StartupInit(path, helperFunctions);
}

