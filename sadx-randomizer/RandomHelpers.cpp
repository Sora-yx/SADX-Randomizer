#include <algorithm>
#include "SADXVariables.h"
#include "SADXEnums.h"
#include "RandomHelpers.h"
#include "Utils.h"
#include "MemAccess.h"
#include "SADXFunctions.h"
#include "MemAccess.h"



extern bool RNGCharacters;
extern bool RNGStages;
extern bool Regular;


extern "C"
{
	//Set up 2 arrays, one for the stage list and an other for the characters, this is to avoid randomizing a stage which is impossible to beat or a character who can crash the game.
	int character[6] = { 0, 2, 3, 5, 6, 7 };
	int level[18] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 20, 21, 22, 23, 38 };
	int door[5] = { 0, 1, 2, 3, 4 };
	int metalsonicrng[2] = { 0, 1 };

	//Initialize Banned stage impossible to beat
	int bannedLevelsGamma[8] = { 3, 15, 16, 18, 20, 21, 23, 38 };
	int bannedLevelsBig[3] = { 8, 22, 38 };
	int bannedLevelsAmy[1] = { 38 };
	int bannedLevelsTails[1] = { 5 };

	//Initiliaze banned regular stage if option is activated
	int bannedRegularSonic[10] = { 2, 3, 5, 6, 7, 8, 9, 15, 20, 22 };
	int bannedRegularTails[5] = { 4, 5, 20, 21, 38 };
	int bannedRegularKnuckles[1] = { 16 };
	int bannedRegularAmy[3] = { 12, 23, 38 };
	int bannedRegularBig[3] = { 8, 22, 38 };
	int bannedRegularGamma[8] = { 3, 15, 16, 18, 20, 21, 23, 38 };


	DataPointer(char, Emblem, 0x974AE0);

	void randomstage(char stage, char act) {
		// Starts the Credits once the player gets 10 Emblems. 
		if (Emblem == 10 || Emblem == 15 || Emblem == 20 || Emblem == 23 || Emblem == 27 || Emblem == 32 || Emblem == 33)
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
			//set up final egg door rng
			DataPointer(char, RNGDoor, 0x3C7457C);
			RNGDoor = door[rand() % 5];

			if (RNGCharacters == true)
				CurrentCharacter = character[rand() % 6];

			if (RNGStages == true) {
				if (Regular == true)
				{
					switch (CurrentCharacter)
					{
					case Characters_Sonic:
						do {
							CurrentLevel = level[rand() % 18];
							CurrentAct = 0;
							MetalSonicFlag = metalsonicrng[rand() % 2];
							GameState = 17;
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularSonic, CurrentLevel, 10)));
						break;
					case Characters_Tails:
						do {
							CurrentLevel = level[rand() % 18];
							CurrentAct = 0;
							MetalSonicFlag = 0;
							GameState = 17;
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularTails, CurrentLevel, 5)));
						break;
					case Characters_Knuckles:
						do {
							CurrentLevel = level[rand() % 18];
							CurrentAct = 0;
							MetalSonicFlag = 0;
							GameState = 17;
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularKnuckles, CurrentLevel, 1)));
						break;
					case Characters_Amy:
						do {
							CurrentLevel = level[rand() % 18];
							CurrentAct = 0;
							MetalSonicFlag = 0;
							GameState = 17;
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularAmy, CurrentLevel, 3)));
						break;
					case Characters_Big:
						do {
							CurrentLevel = level[rand() % 18];
							CurrentAct = 0;
							MetalSonicFlag = 0;
							GameState = 17;
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularBig, CurrentLevel, 3)));
						break;
					case Characters_Gamma:
						do {
							CurrentLevel = level[rand() % 18];
							CurrentAct = 0;
							MetalSonicFlag = 0;
							GameState = 17;
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularGamma, CurrentLevel, 8)));
						break;
					}
				}
				else
				{
					switch (CurrentCharacter)
					{
					case Characters_Sonic:
						MetalSonicFlag = metalsonicrng[rand() % 2];
						break;
					defaut:
						MetalSonicFlag = 0;
					}
					do {
						CurrentLevel = level[rand() % 18];
						GameState = 17;
						CurrentAct = 0;
					} while (CurrentLevel == LevelCopy || (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 8) || (CurrentCharacter == Characters_Big && isValueInArray(bannedLevelsBig, CurrentLevel, 3))));
				}
			}
			else
			{
				if (RNGStages == false && Regular == true) 
				{ }
			}
			

			

		}
	}
}