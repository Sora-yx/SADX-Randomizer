#include "stdafx.h"
#include <algorithm>
#include <fstream>

std::string modpath;

int Seed = 0;
char StorySplits;
bool RNGCharacters = true;
bool RNGStages = true;
bool Upgrade = true;
bool Vanilla = false;
bool RNGVoices = true;
bool CustomVoices = true;
bool RNGMusic = true;
bool SA2M2 = true;
bool SA2M3 = true;
bool Viper = false;
extern bool CreditCheck;
bool isCriticalMode = false;
bool isChaoGameplayAllowed = false;
bool DupliCheck = true;
bool isChaoHintEnabled = true;
bool RNGCutscene = true;

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

int StatsTimer = 4000;
bool SA2Voices = false;

extern CollisionInfo* oldcol;
int SeedCopy = 0;
time_t t;

extern NJS_VECTOR pos;
extern bool ChaoSpawnAllowed;
extern bool isCutsceneAllowed;

short chara = 0;

extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//get current mod information
		HMODULE CMMode = GetModuleHandle(L"SADX-Critical-Mode");

		if (CMMode)
			isCriticalMode = true;

		if (helperFunctions.Version < 7)
		{
			MessageBox(WindowHandle,
				L"Please update SADX Mod Loader. Randomizer mod requires API version 7 or newer.",
				L"Randomizer Error", MB_OK | MB_ICONERROR);
		}

		help = helperFunctions;

		//Ini file Configuration
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		StorySplits = config->getInt("Randomizer", "StorySplits", 0); //speedrunners splits
		RNGCharacters = config->getBool("Randomizer", "RNGCharacters", true);
		RNGStages = config->getBool("Randomizer", "RNGStages", true);
		DupliCheck = config->getBool("Randomizer", "DupliCheck", true);
		RNGCutscene = config->getBool("Randomizer", "RNGCutscene", true);
		Upgrade = config->getBool("Randomizer", "Upgrade", true);
		Seed = config->getInt("Randomizer", "Seed", 0);
		Vanilla = config->getBool("Randomizer", "Vanilla", false);
		SA2M2 = config->getBool("Randomizer", "SA2M2", true);
		SA2M3 = config->getBool("Randomizer", "SA2M3", true);

		//Songs Settings
		RNGVoices = config->getBool("SongsStuff", "RNGVoices", true);
		RNGMusic = config->getBool("SongsStuff", "RNGMusic", true);

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
		AI_Init(helperFunctions, config);
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
		ChaoGameplayCheck();
		Characters_Management();
		Stages_Management();
		RandomizeStages_Hook();
		
		//RNG generator + Create splits.
		Randomizer_GetNewRNG();
	}

	extern int levelCount;
	__declspec(dllexport) void __cdecl OnFrame()
	{

		DisplayDebugStringFormatted(NJM_LOCATION(2, 4), "Current Cutscene: %d", randomizedSets[levelCount].cutsceneID);

		//if (TimeThing == 1 && ControllerPointers[0]->PressedButtons & Buttons_Y && ControlEnabled && SwapDelay >= 150)
			//PlayRandomCutscene(13);
		
		//Display Current Randomized Settings Information on Character Select Screen.
		if (GameMode == GameModes_Menu && CharObj2Ptrs[0])
			DisplayRandoInformation();

		CheckAndDisplayWarningLayoutError();
		Sounds_OnFrame();
		LevelOnFrames();

		if (GameState == 16)  //Pause Menu
			PauseMenuFix();

		if (RNGStages && (GameState == 21 || GameState == 24 || GameState == 17))
			CustomFlagCheck(); //When loading, Check flag and credits*/
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
			case LevelIDs_SSGarden:
			case LevelIDs_ECGarden:
			case LevelIDs_MRGarden:
			case LevelIDs_ChaoRace:
				FixCharacterSFX();
				LoadCharVoices();
				break;
			}
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}