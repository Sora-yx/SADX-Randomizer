#include <cstdio>
#include <algorithm>
#include <time.h>
#include "stdafx.h"
#include "SADXModLoader.h"
#include "RandomHelpers.h"
#include "IniFile.hpp"

bool RNGCharacters = true;
bool RNGStages = true;
bool Upgrade = true;

extern "C"
{
	//Set up 2 arrays, one for the stage list and an other for the characters, this is to avoid randomizing a stage which is impossible to beat or a character who can crash the game.
	int character[6] = { 0, 2, 3, 5, 6, 7 };
	int level[18] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 20, 21, 22, 23, 38 };
	int HSact[2] = { 0, 2 };
	int act[2] = { 0, 1 };

	time_t t;

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		unsigned int seed = 0;

		//Ini Configuration
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		RNGCharacters = config->getBool("Randomizer", "RNGCharacters", true);
		RNGStages = config->getBool("Randomizer", "RNGStages", true);
		Upgrade = config->getBool("Randomizer", "upgrade", true);
		seed = config->getInt("Randomizer", "Seed", 0);
		delete config;

		if (seed)
			srand(seed);
		else
			srand((unsigned)time(&t));
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{


		if (Upgrade == true)
		{
			EventFlagArray[EventFlags_Sonic_LightShoes] = true;
			EventFlagArray[EventFlags_Sonic_CrystalRing] = true;
			EventFlagArray[EventFlags_Sonic_AncientLight] = true;
			EventFlagArray[EventFlags_Tails_JetAnklet] = true;
			EventFlagArray[EventFlags_Tails_RhythmBadge] = true;
			EventFlagArray[EventFlags_Amy_LongHammer] = true;
			EventFlagArray[EventFlags_Gamma_JetBooster] = true;
			EventFlagArray[EventFlags_Knuckles_ShovelClaw] = true;
			EventFlagArray[EventFlags_Knuckles_FightingGloves] = true;
			EventFlagArray[EventFlags_Big_LifeRing] = true;
		}

		//*** Adventure Mode Rand ***
		DataPointer(unsigned char, LevelList, 0x3B2C5F8);
		DataPointer(char, SelectedMenu, 0x3B2A2FA);
		DataPointer(char, Emblem, 0x974AE0);

		if (GameState == 21 && (GameMode == 5 || GameMode == 4 && (LevelList == 0 || LevelList == 97 || LevelList == 243)))
		{
			// Starts the Credits once the player gets 10 Emblems. 
			if (Emblem == 10) {
				EventFlagArray[EventFlags_SonicAdventureComplete] = true;
				EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
				EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
				EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
				EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
				EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
				GameMode = GameModes_StartCredits;
				GameState = 21;
				Credits_State = 1;
				CurrentCharacter = 0;
				Load_SEGALOGO_E();
			}
			else {
				randomizeCharacter();
				randomizeStages();
			}

		}

		/*
		TRIAL MODE
		Checks if the player is on the Menu
		*/
		if (GameState == 21 && (SelectedMenu == 1 && (LevelList == 14 || LevelList == 238 || LevelList == 238 || LevelList == 212 || LevelList == 138)))
		{
			randomizeCharacter();
			randomizeStages();
		}
		else
		{
			// Increase their MaxAccel to 5 so they can complete stages they are not meant to.
			PhysicsArray[Characters_Amy].MaxAccel = 5;
			PhysicsArray[Characters_Big].MaxAccel = 5;
			PhysicsArray[Characters_Gamma].MaxAccel = 5;
			return;
		}
	}

	__declspec(dllexport) void __cdecl OnControl()
	{
		//fix Casinopolis SFX while using wrong characters
		switch (CurrentLevel)
		{
		case LevelIDs_Casinopolis:
			if (CurrentCharacter == Characters_Amy)
			{
				LoadSoundList(46);
				if (VoiceLanguage)
					LoadSoundList(64);
				else
					LoadSoundList(63);
			}
			if (CurrentCharacter == Characters_Gamma)
			{
				LoadSoundList(48);
				if (VoiceLanguage)
					LoadSoundList(68);
				else
					LoadSoundList(67);
			}
			if (CurrentCharacter == Characters_Big)
			{
				LoadSoundList(48);
				if (VoiceLanguage)
					LoadSoundList(68);
				else
					LoadSoundList(67);
			}
			break;
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };

}