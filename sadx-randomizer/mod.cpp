#include <cstdio>
#include <algorithm>
#include <time.h>
#include "stdafx.h"
#include "SADXModLoader.h"
#include "RandomHelpers.h"
#include "IniFile.hpp"
#include "SADXFunctions.h"
#include "MemAccess.h"

bool RNGCharacters = true;
bool RNGStages = true;
bool Upgrade = true;
bool Regular = false;

extern "C"
{

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
		Regular = config->getBool("Randomizer", "Regular", false);
		delete config;

		if (seed)
			srand(seed);
		else
			srand((unsigned)time(&t));

		if (RNGStages == true || RNGCharacters == true)
		{
			WriteCall((void*)0x416bd4, quitstage); //hook pause quit
			WriteCall((void*)0x41509b, randomstage);  //Hook "SetNextLevel" Used after some specific boss fight? Seems like it fixs egg viper crash.
			WriteCall((void*)0x7b0b0e, randomstage); //hook "Set next level"
			WriteCall((void*)0x416bf8, quitstage); //hook "Set next level cutscene version" When used, Big Red Mountain and WV are fixed.
			WriteCall((void*)0x41709d, randomstage); //hook "Go to next level"
			WriteCall((void*)0x50659a, randomstage); //hook trial mod / hedgehog hammer / sub game
			WriteCall((void*)0x417b47, randomstage); //hook when entering to an action stage in the hub world. MIGHT BE AN ISSUE
			WriteCall((void*)0x42ca8c, randomstage); //hook when selecting a character in adventure mode.
			WriteCall((void*)0x41342a, randomstage); //hook CurrentAdventureData (If hook is disabled, you will get randomly teleported to Gamma's upgrade room for some reason.)
			WriteCall((void*)0x413522, randomstage); //hook CurrentAdventureData Boss soft reset (Same as before, happen if you soft reset during a boss fight.)
		}
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
			EventFlagArray[EventFlags_Amy_WarriorFeather] = true;
			EventFlagArray[EventFlags_Amy_LongHammer] = true;
			EventFlagArray[EventFlags_Knuckles_ShovelClaw] = true;
			EventFlagArray[EventFlags_Knuckles_FightingGloves] = true;
			EventFlagArray[EventFlags_Big_LifeRing] = true;
			EventFlagArray[EventFlags_Big_PowerRod] = true;
			EventFlagArray[EventFlags_Gamma_JetBooster] = true;
			EventFlagArray[EventFlags_Gamma_LaserBlaster] = true;
		}

		

		//When loading: check if Credits need to start and call random act if possible.

		DataPointer(char, Emblem, 0x974AE0);
		DataPointer(unsigned char, LevelList, 0x3B2C5F8);
		DataPointer(unsigned char, SelectedCharacter, 0x3B2A2FD);
		int actrng[2] = { 0, 1 };
		int actHS[2] = { 0, 2 };
		int actIC[2] = { 0, 3 };

		if (GameState == 21 && (GameMode == 5 || GameMode == 4 || GameMode == 17 && (LevelList == 0 || LevelList == 97 || LevelList == 243)))
		{
			if (Emblem == 10 || Emblem == 16 || Emblem == 22 || Emblem == 26 || Emblem == 31 || Emblem == 37 || Emblem == 39)
			{
				// Check if credits need to happen, if not, start the RNG to get Metal Sonic and a random act.
				switch (SelectedCharacter)
				{
				case 0:
					EventFlagArray[EventFlags_SonicAdventureComplete] = true;
					EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
					EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
					EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
					EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
					EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
					break;
				case 1:
					EventFlagArray[EventFlags_TailsAdventureComplete] = true;
					EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
					EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
					EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
					EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
					break;
				case 2:
					EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
					EventFlagArray[EventFlags_KnucklesAdventureComplete] = true;
					EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
					EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
					EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
					break;
				case 3:
					EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
					EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
					EventFlagArray[EventFlags_AmyAdventureComplete] = true;
					EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
					EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
					break;
				case 4:
					EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
					EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
					EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
					EventFlagArray[EventFlags_BigAdventureComplete] = true;
					EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
					break;
				case 5:
					EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
					EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
					EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
					EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
					EventFlagArray[EventFlags_GammaAdventureComplete] = true;
					EventFlagArray[EventFlags_SuperSonicUnlockedAdventure] = true;
					break;
				case 6:
					EventFlagArray[EventFlags_SuperSonicAdventureComplete] = true;
					break;
				}
					GameMode = GameModes_StartCredits;
					GameState = 21;
					Credits_State = 1;
					Load_SEGALOGO_E();
			}

			else
			{
				switch (CurrentLevel)
				{
				case LevelIDs_EmeraldCoast:
					if (CurrentCharacter == Characters_Sonic || MetalSonicFlag == 1)
					{
						CurrentAct = 2;
						NextAct = 2;
					}
					else
					{
						if (CurrentCharacter == Characters_Big)
						{
							CurrentAct = 0;
							NextAct = 0;
						}
						else
						{
							NextAct = actHS[rand() % 2];
							CurrentAct = actHS[rand() % 2];
						}
					}
					break;
				case LevelIDs_IceCap:
					if (CurrentCharacter == Characters_Sonic)
					{
						NextAct = 3;
						CurrentAct = 3;
					}
					else
						if (CurrentCharacter == Characters_Big)
						{
							NextAct = 0;
							CurrentAct = 0;
						}
						else
						{
							NextAct = actIC[rand() % 2];
							CurrentAct = actIC[rand() % 2];
						}
					break;
				case LevelIDs_HotShelter:
					NextAct = actHS[rand() % 2];
					CurrentAct = actHS[rand() % 2];
					break;
				case LevelIDs_SpeedHighway:
					if (CurrentCharacter == Characters_Sonic)
					{
						CurrentAct = 0;
					}
					else
					{
						NextAct = actrng[rand() % 2];
						CurrentAct = actrng[rand() % 2];
					}
					break;
				case LevelIDs_RedMountain:
					if (CurrentCharacter == Characters_Sonic)
					{
						CurrentAct = 0;
					}
					else
					{
						NextAct = actrng[rand() % 2];
						CurrentAct = actrng[rand() % 2];
					}
					break;
				}
			}
		}

		if (GameMode == 4 || GameMode == 5)
		{
			HudShowTimer;
			HudDisplayRingTimeLife;
			HudDisplayScoreOrTimer;
		}

		// Increase their MaxAccel to 5 so they can complete stages they are not meant to.
		{
			PhysicsArray[Characters_Amy].MaxAccel = 5;
			PhysicsArray[Characters_Big].MaxAccel = 5;
			PhysicsArray[Characters_Gamma].MaxAccel = 5;
			return;
		}

	}

	__declspec(dllexport) void __cdecl OnControl()
	{
		
		//fix Casinopolis SFX when using wrong characters
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
				LoadSoundList(47);
				if (VoiceLanguage)
					LoadSoundList(66);
				else
					LoadSoundList(65);
			}
			break;
		}

		//Fix Knuckles Lost World act 2 song
			switch (CurrentLevel)
			{
			case LevelIDs_LostWorld:
				if (CurrentCharacter == Characters_Knuckles && CurrentAct == 1)
				{
					CurrentSong = 64;
				}
				break;
			}

			switch (CurrentLevel)
			{
			case LevelIDs_HotShelter:
				if (CurrentCharacter == Characters_Big && CurrentAct == 1)
				{
					PlayMusic(MusicIDs_HotShelterRedBarrageArea);
				}
				break;
			}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };

}