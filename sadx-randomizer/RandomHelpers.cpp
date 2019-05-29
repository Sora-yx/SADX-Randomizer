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
	//Set up several arrays, the "level" one is to avoid randomizing a stage which is impossible to beat.
	int character[6] = { 2, 2, 3, 5, 6, 7 };
	int level[18] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 20, 21, 22, 23, 38 };
	int door[5] = { 0, 1, 2, 3, 4 }; //set up the 5 doors RNG at Final Egg.
	int metalsonicrng[2] = { 0, 1 };

	//Initialize Banned stage impossible to beat
	int bannedLevelsGamma[8] = { 3, 15, 16, 18, 20, 21, 23, 38 };
	int bannedLevelsBig[3] = { 8, 22, 38 };
	//int bannedLevelsKnuckles[1] = { 38 };
	//int bannedLevelsAmy[1] = { 38 };

	//Initiliaze banned regular stage if option is activated
	int bannedRegularSonic[10] = { 2, 3, 5, 6, 7, 8, 9, 15, 20, 22 };
	int bannedRegularTails[5] = { 4, 6, 20, 21, 38 };
	int bannedRegularKnuckles[2] = { 16 };
	int bannedRegularAmy[3] = { 12, 23 };
	int bannedRegularBig[3] = { 8, 22 };
	int bannedRegularGamma[8] = { 3, 15, 16, 18, 20, 21, 23, 38 };

	//Function Credits
	void showcredits() {
		GameMode = GameModes_StartCredits;
		GameState = 21;
		Credits_State = 1;
		Load_SEGALOGO_E();
	}


	//function Randomize stage and characters
	void randomstage(char stage, char act) {

		LastLevel = CurrentLevel;
		LastAct = CurrentAct;

		if (Emblem == 10 || Emblem == 16 || Emblem == 22 || Emblem == 26 || Emblem == 31 || Emblem == 37 || Emblem == 39)
		{
			//void showcredits();
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
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularSonic, CurrentLevel, 10)));
						break;
					case Characters_Tails:
						do {
							CurrentAct = 0;
							MetalSonicFlag = 0;
							CurrentLevel = level[rand() % 18];
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularTails, CurrentLevel, 5)));
						break;
					case Characters_Knuckles:
						do {
							CurrentAct = 0;
							MetalSonicFlag = 0;
							CurrentLevel = level[rand() % 18];
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularKnuckles, CurrentLevel, 1)));
						break;
					case Characters_Amy:
						do {
							CurrentAct = 0;
							MetalSonicFlag = 0;
							CurrentLevel = level[rand() % 18];
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularAmy, CurrentLevel, 2)));
						break;
					case Characters_Big:
						do {
							CurrentAct = 0;
							MetalSonicFlag = 0;
							CurrentLevel = level[rand() % 18];
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularBig, CurrentLevel, 2)));
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
					} while (CurrentLevel == LevelCopy || (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 8) || (CurrentCharacter == Characters_Big && isValueInArray(bannedLevelsBig, CurrentLevel, 3))));
					//while (CurrentLevel == LevelCopy || (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 8) || (CurrentCharacter == Characters_Big && isValueInArray(bannedLevelsBig, CurrentLevel, 3) || (CurrentCharacter == Characters_Amy && isValueInArray(bannedLevelsAmy, CurrentLevel, 1) || (CurrentCharacter == Characters_Knuckles && isValueInArray(bannedLevelsKnuckles, CurrentLevel, 1))))));
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
}

	//cancel the reset position at 0 after quitting a stage.
	 void CancelResetPosition() {
		NextLevel = LastLevel;
		NextAct = LastAct;
	}

	//fix Force the game to return to the title screen when you quit.
	void quitstage() {
		PauseQuitThing();
		GameState = 0x14;
		return;
	}


