#include "stdafx.h"
#include "subtitles.h"


void __cdecl StartupLevels_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	HedgehogHammer_Init(helperFunctions);
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
	TwinkleCircuit_Init();

	//Boss
	Chaos0_Init(helperFunctions);
	Chaos2_Init(helperFunctions);
	Chaos4_Init(helperFunctions);
	Chaos6_Init(helperFunctions);
	EggHornet_Init(helperFunctions);
	EggWalker_Init(helperFunctions);
	EggViper_Init(helperFunctions);
	Zero_Init(helperFunctions);
	PerfectChaos_Init();
	E101_Init(helperFunctions);

	LevelFeaturesInit();
	LayoutFunctionInit(); //Set and Cam file
	Result_Init();
}


void __cdecl StartupMiscellaneous_Init(const char* path, const HelperFunctions& helperFunctions) {

	helperFunctions.ReplaceFile("system\\AVA_GTITLE0_E.PVM", "system\\textures\\AVA_GTITLE0_E.PVM"); //replace title screen
	helperFunctions.ReplaceFile("system\\SETMCART03S.BIN", "system\\Sets\\SETMCART03S.BIN"); //TC act 4 fix
	WriteCall((void*)0x44B0A4, CheckDeleteAnimThing); 

	//Random Title Card + Missions
	TitleCard_Init();

	//Stats & Value Reset
	WriteCall((void*)0x42ca4f, SoftReset_R); //Reset value and stuff properly when you Soft Reset and quit.
	WriteCall((void*)0x416b7a, TrialModeQuit_R); //Reset value and stuff properly when you Quit Trial Mode
	WriteCall((void*)0x413368, DeleteCustomFlag); //Reset flags when you create a new savefile.
	WriteCall((void*)0x42af3b, AddCustomFlag);

	Init_Subtitles();
	Init_RandomCutscene();
	Credits_StartupInit(path, helperFunctions);
}

