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
	//Set up several arrays, the "level" one doesn't include some specific stages impossible to beat.
	int character[6] = { 0, 2, 3, 5, 6, 7 };
	int level[18] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 20, 21, 22, 23, 38 };
	int door[5] = { 0, 1, 2, 3, 4 }; //set up the 5 doors RNG at Final Egg.
	int metalsonicrng[2] = { 0, 1 }; //Used to randomize Metal Sonic.

	//Initialize Ban few stage impossible to beat, depending on the character.
	int bannedLevelsGamma[7] = { 3, 15, 16, 18, 20, 21, 23 };
	int bannedLevelsBig[2] = { 8, 22 };
	int bannedLevelsKnuckles[2] = { 5, 6 };

	//Initiliaze banned regular stage if option is activated
	int bannedRegularSonic[10] = { 2, 3, 5, 6, 7, 8, 9, 15, 20, 22 };
	int bannedRegularTails[5] = { 4, 6, 20, 21, 38 };
	int bannedRegularKnuckles[3] = { 5, 6, 16 };
	int bannedRegularAmy[2] = { 12, 23 };
	int bannedRegularBig[2] = { 8, 22 };
	int bannedRegularGamma[7] = { 3, 15, 16, 18, 20, 21, 23 };



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
				if (Regular == true) //if the player activated the "banned regular stage option", check and ban the regular combination.
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
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularKnuckles, CurrentLevel, 3)));
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
						} while (CurrentLevel == LevelCopy || (isValueInArray(bannedRegularGamma, CurrentLevel, 7)));
						break;
					}
				}
				else //if the player didn't activate the regular option
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
					} while (CurrentLevel == LevelCopy || (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 7) || (CurrentCharacter == Characters_Big && isValueInArray(bannedLevelsBig, CurrentLevel, 2) || (CurrentCharacter == Characters_Knuckles && isValueInArray(bannedLevelsKnuckles, CurrentLevel, 2)))));
		
				}
			}
			else
			{
				if (RNGStages == false && Regular == true) //It's technically useless, but I need to make some test later.
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

// Force the game to return to the title screen when you quit.
void quitstage() {
	PauseQuitThing();
	CurrentCharacter = 0;
	GameState = 0x14;
	return;
}

//Set Gamma's Timer to 6 min instead of 3.
void SetGammaTimer(char param_1, char param_2) {
	param_1 = 6;
	param_2 = 0;
	TimeFrames = 0;
	TimeMinutes = param_1;
	TimeSeconds = param_2;
	return;
}

