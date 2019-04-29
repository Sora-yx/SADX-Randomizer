#include "SADXModLoader.h"
#include "SADXStructs.h"
#include "SADXVariables.h"
#include "SADXEnums.h"
#include "SADXFunctions.h"
#include "Trampoline.h"
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include "IniFile.hpp"

static int Seed = 0;
static bool RNGCharacters = true;
static bool RNGStages = true;
static bool Upgrade = true;
static bool Accel = true;


extern "C"
{
	//Set up 2 arrays, one for the stage list and an other for the characters, this is to avoid randing a stage which is impossible to beat or a wrong character who can crash the game.
	time_t t;
	int level[18] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 20, 21, 22, 23, 38 };
	int HSact[2] = { 0, 2 };
	int act[2] = { 0, 1 };
	int character[6] = { 0, 2, 3, 5, 6, 7 };


	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{

		//Ini Configuration

		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		Seed = config->getInt("Randomizer", "Seed", 0);
		RNGCharacters = config->getBool("Randomizer", "RNGCharacters", true);
		RNGStages = config->getBool("Randomizer", "RNGStages", true);
		Upgrade = config->getBool("Randomizer", "upgrade", true);
		delete config;


		if (Seed)
			srand((unsigned)Seed);
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

		DataPointer(byte, Emblem, 0x974AE0);

		if (GameState == 21 && (GameMode == 5 || GameMode == 4 && (LevelList == 0 || LevelList == 97 || LevelList == 243)))
		{
			if (Emblem == 10) //Starts the Credits once the player gets 10 Emblems.
			{
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

			else
			{
				if (RNGCharacters == true)
				{
					do {
						CurrentCharacter = character[rand() % 6];
					} while (CurrentCharacter == 6 && (CurrentLevel == 15 | CurrentLevel == 16 || CurrentLevel == 18 || CurrentLevel == 3 || CurrentLevel == 20 || CurrentLevel == 21 || CurrentLevel == 23));
				}

				if (RNGStages == true)
				{
					do {
						CurrentLevel = level[rand() % 18];
						CurrentAct = 0;
					}

					while (CurrentCharacter == 6 && (CurrentLevel == 15 | CurrentLevel == 16 || CurrentLevel == 18 || CurrentLevel == 3 || CurrentLevel == 20 || CurrentLevel == 21 || CurrentLevel == 23));
				}
			}

		}

		//Trial MODE RNG
		//Check if the player is on Menu / Loading (21).

		if (GameState == 21 && (SelectedMenu == 1 && (LevelList == 14 || LevelList == 238 || LevelList == 238 || LevelList == 212 || LevelList == 138)))
		{
			if (RNGCharacters == true)
			{
				do {
					CurrentCharacter = character[rand() % 6];
				} while (CurrentCharacter == 6 && (CurrentLevel == 15 | CurrentLevel == 16 || CurrentLevel == 18 || CurrentLevel == 3 || CurrentLevel == 20 || CurrentLevel == 21 || CurrentLevel == 23));

			}

			if (RNGStages == true)
				do {
					CurrentLevel = level[rand() % 18];
					CurrentAct = 0;
				}

			while (CurrentCharacter == 6 && (CurrentLevel == 15 | CurrentLevel == 16 || CurrentLevel == 18 || CurrentLevel == 3 || CurrentLevel == 20 || CurrentLevel == 21 || CurrentLevel == 23));
		}

		else
		{
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