#include "stdafx.h"
#include <algorithm>
#include <fstream>
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include "Utils.h"


//global Randomizer value settings
int StorySplits;

bool RNGCharacters = true;
bool RNGStages = true;
bool Upgrade = true;
bool Vanilla = false;
bool RNGVoices = true;
bool RNGMusic = true;
bool ConsistentMusic = false;
int SonicCD = 0;
bool Missions = true;
bool Any = true;
extern int CustomLayout;
extern bool CreditCheck;
extern int levelCount;

//Character settings
bool Weight = true;
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
int split = 0;
int TotalCount = 0; //Total of Random Stage, used to reroll later in-game.

//AI
bool isAIAllowed = true;
int SwapDelay = 150;
extern int CurrentAI;
extern bool isAIActive;

int CustomFlag = 0; //Used for progression story and credits

//Credits stats
int RageQuit = 0;
int JumpCount = 0;
int ringsPB = 0;
int chaoPB = 0;
int animalPB = 0;
int killPB = 0;
int hitsPB = 0;
int deathsPB = 0;
int AISwapCount = 0;

int DCModWarningTimer = 0;
int StatsTimer = 3000;

extern CollisionInfo* oldcol;
extern bool Race;
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

		int seed = 0;

		//Ini file Configuration
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		StorySplits = config->getInt("Randomizer", "StorySplits", 0); //speedrunners splits
		RNGCharacters = config->getBool("Randomizer", "RNGCharacters", true);
		RNGStages = config->getBool("Randomizer", "RNGStages", true);
		Upgrade = config->getBool("Randomizer", "Upgrade", true);
		seed = config->getInt("Randomizer", "Seed", 0);
		Vanilla = config->getBool("Randomizer", "Vanilla", false);
		Missions = config->getBool("Randomizer", "Missions", true);

		//Songs Settings
		RNGVoices = config->getBool("SongsStuff", "RNGVoices", true);
		RNGMusic = config->getBool("SongsStuff", "RNGMusic", true);
		ConsistentMusic = config->getBool("SongsStuff", "ConsistentMusic", false);
		SonicCD = config->getInt("SongsStuff", "SonicCD", 0);

		//Characters Settings
		AmySpeed = config->getBool("CharactersStuff", "AmySpeed", true);
		BigSpeed = config->getBool("CharactersStuff", "BigSpeed", true);
		Weight = config->getBool("CharactersStuff", "Weight", true);

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

		delete config;

		if (!RNGStages && StorySplits != 0)
			MessageBoxA(WindowHandle, "Failed to generate speedrunner splits, make sure the random stage option is enabled.", "SADX Randomizer", MB_ICONINFORMATION);

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

		if (seed)
			srand(seed);
		else
			srand((unsigned)time(&t));

		SeedCopy = seed;
	
		//Activate all the edited stages, including custom object, to make them beatable.

		Startup_Init(path, helperFunctions);
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
		Chaos6_Init(path, helperFunctions);
		EggHornet_Init(path, helperFunctions);
		EggWalker_Init(path, helperFunctions);
		EggViper_Init(path, helperFunctions);
		Zero_Init(path, helperFunctions);

		//Credits
		//CreditsNewList(); //Initialize custom credits
		WriteCall((void*)0x641aef, CreditFlag);
		//Credits Stat init
		HookStats_Inits();

		//Chao
		Chao_Init();

		//Characters Fixes and other Stuff, really important.
		set_character_hook();

		//Musics, Voices
		Set_MusicVoices();

	

		if (Weight)
		{
			WriteCall((void*)0x470127, BigWeightHook); //force Big Weight Record to 2000g if the player activated the option.
		}

		//Random Title Card + Missions
		TitleCard_Init();

		//Back Rings for M2 & M3
		Set_BackRing();

		if (isAIAllowed)
		{
			//Allow the AI to spawn everywhere
			AI_Init();
			//AI SFX Fixes 
			AIAudioFixes();
		}
		else
		{
			WriteData<5>((void*)0x415948, 0x90); //remove the original load2PTails in LoadCharacter as we use a custom one.
		}
	
		/*
		//Randomizer Fixes
		*/

		//Stages Fixes

		WriteCall((void*)0x415556, DisableTimeStuff); //While result screen: avoid crash and add race result. (really important)

		 //Zero Stuff
		Set_Zero();

		//Bosses Fixes

		//Chaos 4 Stuff
		WriteData<1>((void*)0x5525f9, 0x74); //Reduce HP Bar when not Tails
			//E101 Stuff
		WriteData<5>((void*)0x567ae4, 0x90); //Fix E-101 crash while using a wrong character.

		//Sonic/Eggman Race Stuff
		Race_Init();

		WriteCall((void*)0x4235f8, TwinkleCircuitMusic); //random music between "super sonic racing" and "twinkle circuit"
		
		//SA2 Story Style, Hook all SetLevelandAct to make them random.

		if (RNGStages == true) 
		{
			WriteData<1>((void*)0x40c6c0, 0x04); //force gamemode to 4 (action stage.)
			WriteData<5>((void*)0x4174a1, 0x90); //Remove the Chaos 0 fight and cutscene
			WriteData<6>((void*)0x506512, 0x90); //remove Last Story Flag
			WriteCall((void*)0x50659a, SetLevelAndAct_R); //Remove one "SetLevelAndAct" as it's called twice and Fix trial mod RNG.

			WriteCall((void*)0x41709d, GoToNextLevel_hook); //hook "Go to next level"
			WriteCall((void*)0x417b47, GoToNextLevel_hook); //GameStateHandler_Adventure hook after movie cutscene
			//Redirect SetLevelAndAct in FUN_0x4133e0
			WriteCall((void*)0x41348f, testRefactor); //hook SetLevelAndAct when loading adventure data
			WriteCall((void*)0x4134f3, testRefactor); //hook SetLevelAndAct when loading adventure data
			WriteCall((void*)0x41342a, testRefactor); //hook SetLevelAndAct when loading adventure data
			WriteCall((void*)0x413522, testRefactor);

			WriteCall((void*)0x4db051, TwinkleCircuitResult); //Twinkle Circuit Stuff
			WriteCall((void*)0x416be2, CancelResetPosition); //hook "SetStartPos_ReturnToField" used to cancel the reset character position to 0 after quitting a stage.
		}

		//Splits + RNG generator

		if (StorySplits == 0)
		{
			split = 40;
			for (int i = 0; i < split; i++) { //generate 40 levels without any speedrunners splits.

				if (RNGCharacters)
					randomizedSets[i].character = getRandomCharacter();

				if (RNGStages)
				{
					randomizedSets[i].level = getRandomStage(randomizedSets[i].character, Vanilla);
					randomizedSets[i].act = randomacts(randomizedSets[i]);
					randomizedSets[i].layout = randomLayout(randomizedSets[i]);
				}

				if (RNGMusic)
					randomizedSets[i].music = getRandomMusic(randomizedSets[i]);

				if (isAIAllowed)
					randomizedSets[i].ai_mode = getRandomAI(randomizedSets[i]);

				TotalCount++;

				if (randomizedSets[i].character == Characters_Sonic)
				{
					randomizedSets[i].sonic_mode = rand() % 2;
					randomizedSets[i].ss_mode = rand() % 2;
				}
			}
		}
		else
		{
			//Splits Initialization 
			Split_Init();
		}
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		//Display DC Conversion warning
		if (DCModWarningTimer && GameMode == GameModes_Menu)
		{
			SetDebugFontSize(11.8f * (float)VerticalResolution / 480.0f);
			DisplayDebugString(NJM_LOCATION(2, 1), "Warning,");
			DisplayDebugString(NJM_LOCATION(2, 2), "you are using the Dreamcast Conversion Mod / SADX FE,");
			DisplayDebugString(NJM_LOCATION(2, 3), "Make sure the Randomizer is loaded AFTER these mods!!");
			DCModWarningTimer--;
		}

		//Display Current Randomized Settings Information on Character Select Screen.

		if (!DCModWarningTimer && GameMode == GameModes_Menu && LevelList >= 225)
		{
			SetDebugFontSize(12.0f * (float)VerticalResolution / 480.0f);
			DisplayDebugStringFormatted(NJM_LOCATION(2, 1), "Current Seed: %d", SeedCopy);
			
			if (Vanilla)
				DisplayDebugModeString(NJM_LOCATION(2, 2), "Vanilla Stage: Allowed");
			else
				DisplayDebugModeString(NJM_LOCATION(2, 2), "Vanilla Stage: Banned");

			if (ban != 0)
				DisplayDebugString(NJM_LOCATION(2, 3), "Character Roster: Edited");
			else
				DisplayDebugString(NJM_LOCATION(2, 3), "Character Roster: Normal");

			switch (StorySplits)
			{
			case 1:
				DisplayDebugString(NJM_LOCATION(2, 4), "Actual Splits: Sonic's Story");
				break;
			case 2:
				DisplayDebugString(NJM_LOCATION(2, 4), "Actual Splits: All Stories");
				break;
			case 3:
				DisplayDebugString(NJM_LOCATION(2, 4), "Actual Splits: Any%");
				break;
			}

		}

		//Credits stat
		if (StatsTimer && Credits_State >= 2)
			StatsTimer--;

		if (StatsTimer && Credits_State >= 2 && ControllerPointers[0]->PressedButtons & Buttons_Start)
			StatsTimer = 0;

		if (RNGStages == true)
		{
			if (GameMode == 5 || GameMode == 4)
			{
				if (GameState == 16)  //Pause Menu
				{
					//Display Current Mission Information
					if (CurrentLevel < 15)
					{
						SetDebugFontSize(12.0f * (float)VerticalResolution / 480.0f);
						if (CustomLayout <= 1 || CustomLayout > 3)
							DisplayDebugString(NJM_LOCATION(2, 4), "Current Mission: M1");

						if (CustomLayout == 2)
							DisplayDebugString(NJM_LOCATION(2, 4), "Current Mission: M2 (100 Rings)");

						if (CustomLayout == 3)
							DisplayDebugString(NJM_LOCATION(2, 4), "Current Mission: M3 (Lost Chao)");
					}

					//set gamemode to adventure when the player select quit option, so you will go back to the title screen properly.
					if (PauseSelection == 3)
						GameMode = GameModes_Adventure_Field;
					else
						GameMode = GameModes_Adventure_ActionStg;

				}

			if (GameState == 21 || GameState == 24 || GameState == 17)
				{
					CustomFlagCheck(); //When loading, Check flag and credits
				}
			}
		}

		//AI fixes
		if (!IsGamePaused() && oldcol)
		{
			if (HIBYTE(oldcol->Flags) & 0x80)
			{
				if (oldcol->CollisionArray)
				{
					FreeMemory(oldcol->CollisionArray);
					oldcol->CollisionArray = nullptr;
				}
			}
			FreeMemory(oldcol);
			oldcol = nullptr;
		}

		if (GameMode == 5 && GameState == 15 || GameMode == 4 && GameState == 15 || GameMode == 9 && GameState == 15)
		{
			//Fix UI issue
			HudDisplayScoreOrTimer();
			HudDisplayRingTimeLife_Check();

			//AI Swap
			if (SwapDelay != 150)
				SwapDelay++;

			if (TimeThing == 1 && ControllerPointers[0]->PressedButtons & Buttons_Y && SwapDelay >= 150 && ControlEnabled == 1)
				AISwitch();

			//Rings Mission 2 Check
			if (Rings >= 100 && CurrentLevel != LevelIDs_TwinkleCircuit && CurrentMission == 8)
			{
				ObjectMaster* obj = GetCharacterObject(0);
				EntityData1* ent;
				ent = obj->Data1;
				if ((ent->Status & Status_Ground) == Status_Ground && TimeThing != 0)
				{
					LoadLevelResults();
				}
			}

			//Chao Mission 3 Check
			if (CurrentLevel < 15 && CurrentMission == 1)
				Chao_OnFrame();
		}

		// Increase Amy and Big MaxAccel so they can complete stages they are not meant to.
		character_settings_onFrames();

		//force the game to let you win as Tails in Speed Highway Act 3.
		if (CurrentCharacter == Characters_Tails && CurrentLevel == LevelIDs_SpeedHighway && CurrentAct == 2)
			SetTailsRaceVictory();
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
			case LevelIDs_HotShelter:
				if (CurrentAct == 0)
					HotShelterSecretSwitch();
				break;
			case LevelIDs_Zero:
				LoadSoundList(46);
			break;
			}

		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };

}
