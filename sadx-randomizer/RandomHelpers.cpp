#include <algorithm>
#include "SADXVariables.h"
#include "RandomHelpers.h"

extern bool RNGCharacters;
extern bool RNGStages;

extern "C"
{
	void randomizeCharacter() {
		if (RNGCharacters == true) {
			do {
				CurrentCharacter = character[rand() % 6];
			} while (CurrentCharacter == Characters_Gamma && (CurrentLevel == 3 || CurrentLevel == 15 | CurrentLevel == 16 || CurrentLevel == 18  || CurrentLevel == 20 || CurrentLevel == 21 || CurrentLevel == 23));
		}
	}

	void randomizeStages() {
		if (RNGStages == true) {
			do {
				CurrentLevel = level[rand() % 18];
				CurrentAct = 0;
			} while (CurrentCharacter == Characters_Gamma && (CurrentLevel == 3 || CurrentLevel == 15 | CurrentLevel == 16 || CurrentLevel == 18 || CurrentLevel == 20 || CurrentLevel == 21 || CurrentLevel == 23));
		}
	}
}