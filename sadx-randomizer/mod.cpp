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


		//Allow act swap for all characters
		WriteData<5>((void*)0x601595, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain act 2.
		WriteData<6>((void*)0x61006a, 0x90); // Allow Speed Highway act 2 for every characters.


		//Force the game to let you play Tails at Red Mountain and Emerald Coast act 2.
		WriteData<5>((void*)0x601570, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain Act 1.
		WriteData<5>((void*)0x4f6afa, 0x90); //hook GetCurrentCharacterID when you enter at Emerald Coast act 2.

		WriteData<5>((void*)0x61cb77, 0x90); //Fix Twinkle Park Act 2 crash while using a wrong character.

		WriteData<1>((void*)0x61cf97, 0x00); //Set the Twinkle Park Amy act condition to 0. (if VAR5)

		WriteCall((void*)0x414872, SetGammaTimer); //increase gamma's time limit by 3 minutes.
		WriteCall((void*)0x415556, DisableTimeStuff); //test fix metalsonic emblem

		//WriteData<6>((void*)0x475E7C, 0x90u); // make radar work when not Knuckles
		//WriteData<6>((void*)0x4764CC, 0x90u); // make tikal hints work when not knuckles


		//Hook several Knuckles killplane check (Hot Shelter, Red Mountain, Sky Deck...) if disabled, you will get a black screen with Knuckles.
		WriteData<5>((void*)0x478937, 0x90); 
		WriteData<5>((void*)0x478AFC, 0x90);
		WriteData<5>((void*)0x47B395, 0x90);
		WriteData<5>((void*)0x47B423, 0x90);

		if (RNGStages == true)
		{
			//Hook all SetLevelandAct to make them random.
			WriteCall((void*)0x50659a, randomstage); //hook trial mod / hedgehog hammer / sub game
			WriteCall((void*)0x41709d, randomstage); //hook "Go to next level"
			WriteCall((void*)0x417b47, randomstage); //hook when entering to an action stage in the hub world.
			WriteCall((void*)0x42ca8c, randomstage); //hook when selecting a character in adventure mode.
			WriteCall((void*)0x41342a, randomstage); //hook CurrentAdventureData (If hook is disabled, you will get randomly teleported to Gamma's upgrade room for some reason.)
			WriteCall((void*)0x413522, randomstage); //hook CurrentAdventureData Boss soft reset (Same as before, happen if you soft reset during a boss fight.)

			WriteCall((void*)0x416be2, CancelResetPosition); //hook "SetStartPos_ReturnToField" used to cancel the reset character position to 0 after quitting a stage.
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

		if (GameMode == 5 || GameMode == 4)
		{

			//force the game to display the in-game timer properly.
			HudDisplayRingTimeLife_Check();
			HudDisplayScoreOrTimer();

			if (GameState == 16 && PauseSelection == 3)
			{
				//force GameMode to "adventure field" if the player select quit option, this is to return to the title screen properly.
				GameMode = GameModes_Adventure_Field;
			}

			else
			{
				if (CurrentLevel == LevelIDs_EggViper || CurrentLevel == LevelIDs_Chaos4 || CurrentLevel == LevelIDs_Casinopolis || (CurrentLevel == LevelIDs_RedMountain && CurrentAct == 1) || (CurrentLevel == LevelIDs_SkyDeck && CurrentAct == 2) || CurrentLevel == LevelIDs_SandHill || (CurrentLevel == LevelIDs_WindyValley && CurrentAct == 2) || (CurrentLevel == LevelIDs_FinalEgg))
				{
					GameMode = GameModes_Adventure_Field;
				}
				else
				{
					if (GameState == 15)
					{
						GameMode = GameModes_Adventure_ActionStg;
					}
				}
			}
		}

		if (GameMode == 5 || GameMode == 4 || GameMode == 9)
		{
			// Increase their MaxAccel to 5 so they can complete stages they are not meant to.

			PhysicsArray[Characters_Amy].MaxAccel = 5;
			PhysicsArray[Characters_Big].MaxAccel = 5;
			PhysicsArray[Characters_Gamma].MaxAccel = 5;
			BigWeight = 2000; //display 2000g as Big.
			BigWeightRecord = 2000; //set the record as 2000 so you will always get the emblem for mission B and A as Big.


			if (CurrentLevel == LevelIDs_SandHill)
			{
				Score = 12000;
			}


			//force the game to let you win as Tails in Speed Highway Act 3.
			if (CurrentCharacter == Characters_Tails && CurrentLevel == LevelIDs_SpeedHighway && CurrentAct == 2)
			{
				SetTailsRaceVictory();
			}
			else
			{
				//fix Metal Sonic life icon.
				if (CurrentCharacter != Characters_Sonic)
				{
					MetalSonicFlag = 0;
				}
			}
		}

		//Set up act rng.
		int actHS[2] = { 0, 2 };

		//When loading: check if Credits need to start and call random act if possible.

		if (GameState == 21 && (GameMode == 5 || GameMode == 4 || GameMode == 17 && (LevelList == 0 || LevelList == 97 || LevelList == 111 || LevelList == 243 || LevelList == 225)))
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
					break;
				case LevelIDs_TwinklePark:
					if (CurrentCharacter == Characters_Sonic)
					{
						CurrentAct = 1;
					}
					else
					{
						if (CurrentCharacter == Characters_Amy)
						{
							CurrentAct = 0;
						}
						else
						CurrentAct = actHS[rand() % 2];
					}
					break;
				case LevelIDs_HotShelter:
					if (CurrentCharacter == Characters_Gamma)
					{
						CurrentAct = 0;
						NextAct = 0;
					}
					else
						if (CurrentCharacter == Characters_Amy)
						{
							NextAct = 2;
							CurrentAct = 2;
						}
						else
						{
							NextAct = actHS[rand() % 2];
							CurrentAct = actHS[rand() % 2];
						}
					break;
				case LevelIDs_Casinopolis:
					if (CurrentCharacter == Characters_Sonic)
					{
						CurrentAct = 1;
					}
					else
					{
						CurrentAct = 0;
					}
					break;
				}

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
				//Fix Knuckles Lost World act 2 song
			case LevelIDs_LostWorld:
				if (CurrentCharacter == Characters_Knuckles && CurrentAct == 1)
				{
					CurrentSong = 64;
				}
				break;
				//fix Tails RM act 1 and 2 song.
			case LevelIDs_RedMountain:
				if (CurrentCharacter == Characters_Tails && CurrentAct == 0)
				{
					PlayMusic(MusicIDs_RedMountainMtRedASymbolOfThrill);
				}
				else
					if (CurrentCharacter == Characters_Tails && CurrentAct == 1 && CurrentSong !=  0x4b && CurrentSong != 0x55 && CurrentSong != 0x5d)
					{
						PlayMusic(MusicIDs_RedMountainRedHotSkull);
					}
				break;
			}
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };

}