#include <algorithm>
#include "SADXVariables.h"
#include "SADXEnums.h"
#include "RandomHelpers.h"
#include "Utils.h"

extern bool RNGCharacters;
extern bool RNGStages;
extern bool Regular;


extern "C"
{
	//Initialize Banned stage impossible to beat
	int bannedLevelsGamma[8] = { 3, 15, 16, 18, 20, 21, 23, 38 };
	int bannedLevelsBig[3] = { 8, 22, 38 };
	int bannedLevelsAmy[1] = { 38 };

	//Initiliaze banned regular stage if option is activated
	int bannedRegularSonic[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 15, 20, 22 };
	int bannedRegularTails[4] = { 4, 20, 21, 38 };
	int bannedRegularKnuckles[1] = { 16 };
	int bannedRegularAmy[3] = { 12, 23, 38 };
	int bannedRegularBig[4] = { 8, 12, 22, 38 };
	int bannedRegularGamma[9] = { 1, 3, 15, 16, 18, 20, 21, 23, 38 };


	void randomizeCharacter() {
		if (RNGCharacters == true) {
			do {
				CurrentCharacter = character[rand() % 6];
			} while (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 8) || CurrentCharacter == Characters_Big && isValueInArray(bannedLevelsBig, CurrentLevel, 3 || CurrentCharacter == Characters_Amy && isValueInArray(bannedLevelsAmy, CurrentLevel, 1)));
		}
	}

	void randomizeStages() {
		if (RNGStages == true) {
			if (Regular)
			{
				switch (CurrentCharacter)
				{
				case Characters_Sonic:
					do {
						CurrentLevel = level[rand() % 18];
						CurrentAct = 0;
					} while (isValueInArray(bannedRegularSonic, CurrentLevel, 12));
					break;
				case Characters_Tails:
					do {
						CurrentLevel = level[rand() % 18];
						CurrentAct = 0;
					} while (isValueInArray(bannedRegularTails, CurrentLevel, 4));
					break;
				case Characters_Knuckles:
					do {
						CurrentLevel = level[rand() % 18];
						CurrentAct = 0;
					} while (isValueInArray(bannedRegularKnuckles, CurrentLevel, 1));
					break;
				case Characters_Amy:
					do {
						CurrentLevel = level[rand() % 18];
						CurrentAct = 0;
					} while (isValueInArray(bannedRegularAmy, CurrentLevel, 3));
					break;
				case Characters_Big:
					do {
						CurrentLevel = level[rand() % 18];
						CurrentAct = 0;
					} while (isValueInArray(bannedRegularBig, CurrentLevel, 4));
					break;
				case Characters_Gamma:
					do {
						CurrentLevel = level[rand() % 18];
						CurrentAct = 0;
					} while (isValueInArray(bannedRegularGamma, CurrentLevel, 9));
					break;
				}
			}
			else
			{
				do {
					CurrentLevel = level[rand() % 18];
					CurrentAct = 0;
				} while (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 8) || CurrentCharacter == Characters_Big && isValueInArray(bannedLevelsBig, CurrentLevel, 2 || CurrentCharacter == Characters_Amy && isValueInArray(bannedLevelsAmy, CurrentLevel, 1)));


			}
		}
	}
}