#include "stdafx.h"
#include <algorithm>
#include <fstream>
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include "Utils.h"

int Seed = 0;
char StorySplits;
bool RNGCharacters = true;
bool RNGStages = true;
bool Upgrade = true;
bool Vanilla = false;
bool RNGVoices = true;
bool CustomVoices = true;
bool RNGMusic = true;
char SonicCD = 0;
bool Missions = true;
bool Any = true;
bool Viper = false;
extern bool CreditCheck;
bool isCriticalMode = false;
bool isChaoGameplayAllowed = false;

//Character settings
bool AmySpeed = true;
bool BigSpeed = true;

//banned character roster
bool Sonic = false;
bool Tails = false;
bool Knuckles = false;
bool Amy = false;
bool Gamma = false;
bool Big = false;
bool MetalSonic = false;
bool SuperSonic = false;
int ban = 0;
bool banCharacter[8];

//Speedruner splits
uint32_t split = 0;
uint32_t TotalCount = 0; //Total of Random Stage, used to reroll later in-game.

//AI
bool isAIAllowed = true;
uint8_t SwapDelay = 150;

int CustomFlag = 0; //Used for progression story and credits
short CurrentLevelLayout = 0;

int DCModWarningTimer = 0;
int StatsTimer = 4000;

extern CollisionInfo* oldcol;
int SeedCopy = 0;
time_t t;



extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//get current mod information
		HMODULE DCMod = GetModuleHandle(L"DCMods_Main");
		HMODULE SADXFE = GetModuleHandle(L"sadx-fixed-edition");
		HMODULE DCLight = GetModuleHandle(L"sadx-dc-lighting");

		if (DCMod && !DCLight)
			DCModWarningTimer = 0; //don't display the DC Warning message if Lantern Engine is missing.
		else
			if (DCMod || SADXFE)
				DCModWarningTimer = 250;

		if (helperFunctions.Version < 7)
		{
			MessageBox(WindowHandle,
				L"Please update SADX Mod Loader. Randomizer mod requires API version 7 or newer.",
				L"Randomizer Error", MB_OK | MB_ICONERROR);
			Exit();
			return;
		}

		HMODULE HeroesMod = GetModuleHandle(L"sadx-heroes-mod");
		if (HeroesMod) {
			MessageBoxA(WindowHandle, "Warning: Heroes mod is not compatible with SADX Randomizer.", "SADX Randomizer", MB_ICONERROR);
			Exit();
			return;
		}

		//Ini file Configuration
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		StorySplits = config->getInt("Randomizer", "StorySplits", 0); //speedrunners splits
		RNGCharacters = config->getBool("Randomizer", "RNGCharacters", true);
		RNGStages = config->getBool("Randomizer", "RNGStages", true);
		Upgrade = config->getBool("Randomizer", "Upgrade", true);
		Seed = config->getInt("Randomizer", "Seed", 0);
		Vanilla = config->getBool("Randomizer", "Vanilla", false);
		Missions = config->getBool("Randomizer", "Missions", true);

		//Songs Settings
		RNGVoices = config->getBool("SongsStuff", "RNGVoices", true);
		CustomVoices = config->getBool("SongsStuff", "CustomVoices", true);
		RNGMusic = config->getBool("SongsStuff", "RNGMusic", true);
		SonicCD = config->getInt("SongsStuff", "SonicCD", 0);

		//Characters Settings
		AmySpeed = config->getBool("CharactersStuff", "AmySpeed", true);
		BigSpeed = config->getBool("CharactersStuff", "BigSpeed", true);

		//Disable Character settings
		banCharacter[0] = config->getBool("Roster", "Sonic", false);
		banCharacter[2] = config->getBool("Roster", "Tails", false);
		banCharacter[3] = config->getBool("Roster", "Knuckles", false);
		banCharacter[5] = config->getBool("Roster", "Amy", false);
		banCharacter[7] = config->getBool("Roster", "Big", false);
		banCharacter[6] = config->getBool("Roster", "Gamma", false);
		MetalSonic = config->getBool("Roster", "MetalSonic", false);
		SuperSonic = config->getBool("Roster", "SuperSonic", false);

		isAIAllowed = config->getBool("RosterAI", "isAIAllowed", true);
		isChaoGameplayAllowed = config->getBool("RosterAI", "isChaoGameplayAllowed", false);

		Viper = config->getBool("Difficulty", "Viper", true);
		isCriticalMode = config->getBool("Difficulty", "isCriticalMode", false);

		delete config;

		//ban roster check
		for (int i = 0; i < 8; i++)
		{
			if (banCharacter[i] == 1)
				ban++;
		}

		if (ban >= 6)
		{
			MessageBoxA(WindowHandle, "You cannot ban all the characters.", "SADX Randomizer", MB_ICONERROR);
			Exit();
		}

		if (!RNGStages && StorySplits != 0)
			MessageBoxA(WindowHandle, "Failed to generate speedrunner splits, make sure the random stage option is enabled.", "SADX Randomizer Error", MB_ICONINFORMATION);

		if (Seed)
			srand(Seed);
		else
			srand((unsigned)time(&t));

		SeedCopy = Seed;

		//Activate all the edited stages, including custom object, to make them beatable, add custom audio and other stuff.
		StartupLevels_Init(path, helperFunctions);
		StartupAudio_Init(path, helperFunctions);
		StartupMiscellaneous_Init(path, helperFunctions);

		Chao_Init();
		Characters_Management();
		Stages_Management();
		RandomizeStages_Hook();
		AI_Init();

		//RNG generator + Create splits.
		Randomizer_GetNewRNG();
	}


	__declspec(dllexport) void __cdecl OnFrame()
	{
		//DisplayDebugStringFormatted(NJM_LOCATION(2, 1), "HS: %d", CopyRNGLayoutHS);

		//Display DC Conversion warning
		if (DCModWarningTimer && GameMode == GameModes_Menu)
		{
			SetDebugFontSize(11.8f * (unsigned short)VerticalResolution / 480.0f);
			DisplayDebugString(NJM_LOCATION(2, 1), "Randomizer Mod Warning:");
			DisplayDebugString(NJM_LOCATION(2, 2), "You are using the Dreamcast Conversion Mod / SADX FE,");
			DisplayDebugString(NJM_LOCATION(2, 3), "Make sure the Randomizer is loaded AFTER those mods!");

			DCModWarningTimer--;
		}

		//Display Current Randomized Settings Information on Character Select Screen.
		if (!DCModWarningTimer && GameMode == GameModes_Menu && LevelList >= 225)
			DisplayRandoInformation();

		//AI fixes
		AI_FixesOnFrames();

		// Increase Amy and Big MaxAccel so they can complete stages they are not meant to.
		character_settings_onFrames();

		//Credits stat
		Credits_StatsDelayOnFrames();

		if (GameState == 16)  //Pause Menu
			PauseMenuFix();

		if (RNGStages && (GameState == 21 || GameState == 24 || GameState == 17))
			CustomFlagCheck(); //When loading, Check flag and credits

		if (GameState == 15 && (GameMode == 5 || GameMode == 4 || GameMode ==  9))
		{
			//Fix UI issue
			HudDisplayScoreOrTimer();
			HudDisplayRingTimeLife_Check();

			//AI Swap
			if (SwapDelay != 150 && TimeThing == 1 && ControlEnabled)
				SwapDelay++;

			if (TimeThing == 1 && ControllerPointers[0]->PressedButtons & Buttons_Y && SwapDelay >= 150 && ControlEnabled)
				AISwitch();

			//Rings Mission 2 and Treasure Hunting Check
			MissionResultCheck();

			//Chao Mission 3 Check
			if (CurrentLevel < LevelIDs_Chaos0 && CurrentMission == LostChaoCard)
				Chao_OnFrame();

			LoadTriggerObject();
		}
	}

	__declspec(dllexport) void __cdecl OnControl()
	{
		if (GameMode == 4 || GameMode == 5 || GameMode == 9)
		{
			switch (CurrentLevel)
			{
				//fix Casinopolis SFX when using wrong characters
			case LevelIDs_Casinopolis:
				FixCharacterSFX();
				break;
			case LevelIDs_Zero:
				LoadSoundList(46);
				break;
			}
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}