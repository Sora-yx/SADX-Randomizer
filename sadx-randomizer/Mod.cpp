#include "stdafx.h"
#include <algorithm>
#include <fstream>

std::string modpath;
HelperFunctions help;


//Speedruner splits
uint32_t segmentCount = 0;
uint32_t TotalCount = 0; //Total of Random Stage, used to reroll later in-game.

//AI
bool isAIAllowed = true;

int StatsTimer = 4000;
bool SA2Voices = false;

extern int Seed;
int SeedCopy = 0;
time_t t;

bool gMultiplayerModLoaded = false;

extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//get current mod information
		isKHMod = GetModuleHandle(L"sadx-kh-mod") != NULL;
	
		if (helperFunctions.Version < 18)
		{
			MessageBox(WindowHandle,
				L"Error, your version of the mod loader does not support API version 11. Some functionality will not be available.\nPlease exit the game and update the mod loader for the best experience.",
				L"SADX Randomizer Error: Mod Loader out of date", MB_OK | MB_ICONERROR);
		}

		help = helperFunctions;

		gMultiplayerModLoaded = GetModuleHandle(L"sadx-multiplayer.dll") != NULL;

		//Ini file Configuration
		ReadConfig(path);

		RosterBanCheck();

		if (!RNGStages && StorySplits != 0)
			MessageBoxA(WindowHandle, "Failed to generate speedrunner splits, make sure the random stage option is enabled.", "SADX Randomizer Error", MB_ICONINFORMATION);

		SeedCopy = Seed;

		if (Seed)
			srand(Seed);
		else
			srand((unsigned)time(&t));

		modpath = path;


		//Activate all the edited stages, including custom object, to make them beatable, add custom audio and other stuff.
		StartupLevels_Init(path, helperFunctions);
		StartupMusic_Init(path, helperFunctions);
		StartupVoices_Init(path, helperFunctions);
		StartupMiscellaneous_Init(path, helperFunctions);
		
		Chao_Init();
		Characters_Init();	
		RandomizeStages_Init();
		Objects_Common_Init();
		Missions_Init();
		RandoHud_Init();

		//RNG generator + Create splits.
		Randomizer_GetNewRNG();

	}

	__declspec(dllexport) void __cdecl OnFrame()
	{		

		//Display Current Randomized Settings Information on Character Select Screen.
		DisplayRandoInformation();
		Sounds_OnFrame();
		LevelOnFrames();
		Credits_StatsDelayOnFrames();
		warpedOnFrames();


		if (GameState == 16)  //Pause Menu
			PauseMenuFix();

	}

	__declspec(dllexport) void __cdecl OnControl()
	{
		FixCasinoSoundEffects();
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}