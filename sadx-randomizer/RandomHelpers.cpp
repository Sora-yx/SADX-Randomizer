#include <algorithm>
#include "SADXVariables.h"
#include "RandomHelpers.h"
#include "Utils.h"

extern bool RNGCharacters;
extern bool RNGStages;

extern "C"
{
	int bannedLevelsGamma[7] = { 3, 15, 16, 18, 20, 21, 23 };

	void randomizeCharacter() {
		if (RNGCharacters == true) {
			do {
				CurrentCharacter = character[rand() % 6];
			} while (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 7));
		}
	}

	void randomizeStages() {
		if (RNGStages == true) {
			do {
				CurrentLevel = level[rand() % 18];
				CurrentAct = 0;
			} while (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 7));
		}
	}
}