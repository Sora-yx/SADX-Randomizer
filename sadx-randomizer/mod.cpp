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
bool RNGVoices = false;
bool RNGMusic = false;

bool BigStuff = true;
bool AmySpeed = true;
bool BigSpeed = true;

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

extern "C"
{

	time_t t;

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{

		int seed = 0;
		

		//Ini file Configuration
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		RNGCharacters = config->getBool("Randomizer", "RNGCharacters", true);
		RNGStages = config->getBool("Randomizer", "RNGStages", true);
		Upgrade = config->getBool("Randomizer", "Upgrade", true);
		seed = config->getInt("Randomizer", "Seed", 0);
		Regular = config->getBool("Randomizer", "Regular", false);
		RNGVoices = config->getBool("Randomizer", "RNGVoices", false);
		RNGMusic = config->getBool("Randomizer", "RNGMusic", false);

		AmySpeed = config->getBool("CharactersStuff", "AmySpeed", true);
		BigSpeed = config->getBool("CharactersStuff", "BigSpeed", true);
		BigStuff = config->getBool("CharactersStuff", "BigStuff", true);

		banCharacter[0] = config->getBool("Roster", "Sonic", false);
		banCharacter[2] = config->getBool("Roster", "Tails", false);
		banCharacter[3] = config->getBool("Roster", "Knuckles", false);
		banCharacter[5] = config->getBool("Roster", "Amy", false);
		banCharacter[7] = config->getBool("Roster", "Big", false);
		banCharacter[6] = config->getBool("Roster", "Gamma", false);
		MetalSonic = config->getBool("Roster", "MetalSonic", false);
		SuperSonic = config->getBool("Roster", "SuperSonic", false);
		delete config;

		if (seed)
			srand(seed);
		else
			srand((unsigned)time(&t));
		
		if (banCharacter[0] || banCharacter[2] || banCharacter[3] || banCharacter[5] || banCharacter[7] || banCharacter[6])
		{
			ban = +1;
		}



		//if the player check the randomize voices option.
		if (RNGVoices)
		{
			WriteCall((void*)0x42571d, RandomVoice);
		}

		//if the player check the randomize music option.
		if (RNGMusic)
		{
			WriteCall((void*)0x425699, RandomMusic); //hook PlayMusic (Stages...)
			WriteCall((void*)0x51b94a, RandomMusic); //hook playmusic (Hub World part 1)
			WriteCall((void*)0x62ec81, RandomMusic); //hook playmusic (Hub World, bosses part 2) 

			WriteCall((void*)0x441dd8, RandomMusic); //hook speed shoes sound
			WriteCall((void*)0x4d6daf, RandomMusic); //hook invincibility music

			WriteCall((void*)0x59a4ba, RandomMusic); //hook hot shelter music.
			WriteCall((void*)0x59a215, RandomMusic); //hook hot shelter music part 2.
			WriteCall((void*)0x59a258, RandomMusic); //hook hot shelter music part 3
			WriteCall((void*)0x59a239, RandomMusic); //hook hot shelter music part 4
			WriteCall((void*)0x59a107, RandomMusic); //hook hot shelter music part 5
			WriteCall((void*)0x59a157, RandomMusic); //hook hot shelter music part 6
			WriteCall((void*)0x59a177, RandomMusic); //hook hot shelter music part 7
			WriteCall((void*)0x59a197, RandomMusic); //hook hot shelter music part 8
		}

		//Allow act swap for all characters
		WriteData<5>((void*)0x601595, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain act 2.
		WriteData<6>((void*)0x61006a, 0x90); // Allow Speed Highway act 2 for every characters.

		//Force the game to let you play Tails at Red Mountain and Emerald Coast act 2.
		WriteData<5>((void*)0x601570, 0x90); //Hook GetCurrentCharacterID when you enter at Red Mountain Act 1.
		WriteData<5>((void*)0x6008b1, 0x90); //Fix Red Mountain Act 2 music as Tails.
		WriteData<5>((void*)0x4f6afa, 0x90); //hook GetCurrentCharacterID when you enter at Emerald Coast act 2.

		WriteData<5>((void*)0x61cb77, 0x90); //Fix Twinkle Park Act 2 crash while using a wrong character.
		WriteData<1>((void*)0x61cf97, 0x00); //Set the Twinkle Park Amy act condition to 0. (if VAR5)
		WriteCall((void*)0x414872, SetGammaTimer); //increase gamma's time limit by 3 minutes.
		WriteCall((void*)0x584430, FixGammaBounce); //Fix Gamma bounce on Egg Viper Fight.
		WriteData<5>((void*)0x5e16c2, 0x90); //Fix Lost World Act 2 music as Knuckles.

		WriteData<7>(reinterpret_cast<Uint8*>(0x00494E13), 0x90i8); // Fix Super Sonic position when completing a stage.

		//Speed Highway race
		WriteCall((void*)0x415965, LoadEggmanAI); //Load EggmanAI as Sonic and prevent Tails to race.

		//Red Mountain
		WriteData<1>((void*)0x6027c5, 0x00); //Fix Red Mountain Lava as Sonic (Gamma layout.)
		WriteData<1>((void*)0x60405e, 0x00); //Allow Sonic to destroy the rocks in RM. (Gamma layout.)
		WriteData<1>((void*)0x606bba, 0x00); //Fix the rock bridge as Gamma.
		WriteData<1>((void*)0x602548, 0x74); //Fix Red Mountain Lava as Sonic part 2

		//Chaos 6 stuff
		WriteData<1>((void*)0x5598f0, 0x00); //makes the bomb spawns for every character. (if ivar == 0)
		WriteData<1>((void*)0x5598f1, 0x0075); //makes the bomb spawns for every character part 2. (convert JZ to JNZ this is important.)
		WriteData<1>((void*)0x55a189, 0x0075); //Force Chaos to act like if you were playing Sonic or Knuckles. (attack, pattern etc.)
		WriteData<5>((void*)0x559d3a, 0x90); //Display Chaos 6 life gauge while using a wrong character and fix camera issue.

		//E101 Stuff
		WriteData<5>((void*)0x567ae4, 0x90); //Fix E-101 crash while using a wrong character.

		//Hook several Knuckles killplane check (Hot Shelter, Red Mountain, Sky Deck...) if disabled, you will get a black screen with Knuckles.
		WriteData<5>((void*)0x478937, 0x90);
		WriteData<5>((void*)0x478AFC, 0x90);
		WriteData<5>((void*)0x47B395, 0x90);
		WriteData<5>((void*)0x47B423, 0x90);

		// Super Sonic Stuff
		WriteData<2>(reinterpret_cast<Uint8*>(0x0049AC6A), 0x90i8); //Always initialize Super Sonic weld data.
		WriteCall((void*)0x560388, SuperAuraStuff); //Initialize Super Sonic physic and aura when perfect chaos fight starts.
		WriteCall((void*)0x4167da, SuperSonicStuff); //Call Super Sonic when a stage start.

		// Amy Stuff
		WriteData<1>((void*)0x4c6875, 0x74); //Force Amy's bird to load at every stage. (from JNZ 75 to JZ 74)
		WriteData<1>((void*)0x4c6851, 0x28); //Force Amy's bird to load during boss fight. (from JNZ 75 to JZ 74)

		//Make Big Hot Shelter stuff (secret door etc.) work when using Amy.
		WriteData<1>((void*)0x5aaf12, 0x05);
		WriteData<1>((void*)0x59a3bb, 0x05);
		WriteData<1>((void*)0x59a123, 0x05);

		//Zero Stuff
		WriteCall((void*)0x61d169, LoadZero); //Call Zero when not Amy at Twinkle Park.
		WriteCall((void*)0x59a119, LoadZero); //Call Zero when not Amy at Hot Shelter.
		WriteCall((void*)0x5ae104, LoadZero); //Call Zero when not Amy at Final Egg.
		WriteData<6>((void*)0x4d3f4a, 0x90); //Make Zero spawn for every character.

		if (BigStuff)
		{
			WriteCall((void*)0x470127, BigWeightHook);
		}


		if (RNGStages == true)
		{
			//Hook all SetLevelandAct to make them random.

			WriteData<1>((void*)0x40c6c0, 0x04); //force gamemode to 4 (action stage.)
			WriteCall((void*)0x415556, DisableTimeStuff); //fix metalsonic emblem and crash.

			WriteCall((void*)0x50659a, randomstage); //hook trial mod / hedgehog hammer / sub game
			WriteCall((void*)0x41709d, randomstage); //hook "Go to next level"
			WriteCall((void*)0x417b47, randomstage); //hook when entering to an action stage in the hub world.
			WriteCall((void*)0x41348f, randomstage); //hook when selecting a character in adventure mode. 
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

		if (RNGStages == true)
		{
			if (GameMode == 5 || GameMode == 4)
			{
			
				//set gamemode to adventure when the player select quit option, so you will go back to the title screen.
				if (GameState == 16)
				{
					if (PauseSelection == 3)
					{
						GameMode = GameModes_Adventure_Field;
					}
					else
					{
						GameMode = GameModes_Adventure_ActionStg;
					}
				}

				if (GameState == 21 && (GameMode == 5 || GameMode == 4 || GameMode == 17 && (LevelList == 0 || LevelList == 97 || LevelList == 111 || LevelList == 243 || LevelList == 225)))
				{
					if (Emblem == 10 || Emblem == 16 || Emblem == 22 || Emblem == 26 || Emblem == 31 || Emblem == 37 || Emblem == 39)
					{
						credits();
					}
				}
			}
		}

		if (GameMode == 5 || GameMode == 4 || GameMode == 9)
		{
			//force the game to display the in-game timer properly.
			HudDisplayRingTimeLife_Check();
			HudDisplayScoreOrTimer();

			//fix Metal Sonic life icon.
		if (CurrentCharacter != Characters_Sonic || CurrentLevel == LevelIDs_PerfectChaos)
		{
			MetalSonicFlag = 0;
			SonicRand = 0;
		}
			// Increase their MaxAccel so they can complete stages they are not meant to.
		
				if (CurrentLevel == 38)
				{
					PhysicsArray[Characters_Amy].MaxAccel = 8;
					PhysicsArray[Characters_Big].MaxAccel = 8;
					SetCameraControlEnabled(1);

				}
				else
				{
					if (AmySpeed)
					{
						PhysicsArray[Characters_Amy].MaxAccel = 5;
					}
					if (BigSpeed)
					{
						PhysicsArray[Characters_Big].MaxAccel = 5;
					}
				}

			//force the game to let you win as Tails in Speed Highway Act 3.
			if (CurrentCharacter == Characters_Tails && CurrentLevel == LevelIDs_SpeedHighway && CurrentAct == 2)
			{
				SetTailsRaceVictory();
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
			case LevelIDs_HotShelter:
				if (CurrentCharacter == Characters_Amy && CurrentAct == 0)
				{
					HotShelterSecretSwitch();
				}

			}
		}

	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };

}