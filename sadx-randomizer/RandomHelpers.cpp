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
	int actrng[2] = { 0, 1 };
	int actHS[2] = { 0, 2 };
	int actIC[2] = { 0, 3 };

	//Initialize Banned stage impossible to beat
	int bannedLevelsGamma[8] = { 3, 15, 16, 18, 20, 21, 23, 38 };
	int bannedLevelsBig[3] = { 8, 22, 38 };
	int bannedLevelsKnuckles[1] = { 38 };
	int bannedLevelsAmy[1] = { 38 };
	int bannedLevelsTails[1] = { 5 };

	//Initiliaze banned regular stage if option is activated
	int bannedRegularSonic[9] = { 2, 3, 5, 6, 7, 9, 15, 20, 22 };
	int bannedRegularTails[6] = { 4, 5, 6, 20, 21, 38 };
	int bannedRegularKnuckles[2] = { 16, 38 };
	int bannedRegularAmy[3] = { 12, 23, 38 };
	int bannedRegularBig[3] = { 8, 22, 38 };
	int bannedRegularGamma[8] = { 3, 15, 16, 18, 20, 21, 23, 38 };

	
	DataPointer(char, Emblem, 0x974AE0);
	DataPointer(unsigned char, LevelList, 0x3B2C5F8);
	DataPointer(unsigned char, SelectedCharacter, 0x3B2A2FD);




	void randomstage(char stage, char act) {

		if (Emblem == 10 || Emblem == 16 || Emblem == 22 || Emblem == 26 || Emblem == 31 || Emblem == 37 || Emblem == 39)
		{
			// Check if credits need to happen, if not, start the RNG.
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
							CurrentAct = 0;
							MetalSonicFlag = metalsonicrng[rand() % 2];
							CurrentLevel = level[rand() % 18];
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularSonic, CurrentLevel, 9)));
						break;
					case Characters_Tails:
						do {
							CurrentAct = 0;
							MetalSonicFlag = 0;
							CurrentLevel = level[rand() % 18];
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularTails, CurrentLevel, 6)));
						break;
					case Characters_Knuckles:
						do {
							CurrentAct = 0;
							MetalSonicFlag = 0;
							CurrentLevel = level[rand() % 18];
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularKnuckles, CurrentLevel, 2)));
						break;
					case Characters_Amy:
						do {
							CurrentAct = 0;
							MetalSonicFlag = 0;
							CurrentLevel = level[rand() % 18];
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularAmy, CurrentLevel, 3)));
						break;
					case Characters_Big:
						do {
							CurrentAct = 0;
							MetalSonicFlag = 0;
							CurrentLevel = level[rand() % 18];
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularBig, CurrentLevel, 3)));
						break;
					case Characters_Gamma:
						do {
							CurrentAct = 0;
							MetalSonicFlag = 0;
							CurrentLevel = level[rand() % 18];
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
						break;
					}
					do {
						CurrentAct = 0;
						CurrentLevel = level[rand() % 18];
					} while (CurrentLevel == LevelCopy || (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 8) || (CurrentCharacter == Characters_Big && isValueInArray(bannedLevelsBig, CurrentLevel, 3) || (CurrentCharacter == Characters_Amy && isValueInArray(bannedLevelsAmy, CurrentLevel, 1) || (CurrentCharacter == Characters_Knuckles && isValueInArray(bannedLevelsKnuckles, CurrentLevel, 1))))));
				}
			}
			else
			{
				if (RNGStages == false && Regular == true)
				{
					return;
				}
			}
		}
	}
	void nextcutscene(char stage, char act) {
		CutsceneMode = 3;
		void randomstage(char stage, char act);
		return;
	}

	void quitstage() {
		GameState = 20;
		return;
	}

}
