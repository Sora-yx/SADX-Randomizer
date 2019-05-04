#include <algorithm>
#include "SADXVariables.h"
#include "SADXEnums.h"
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

				if (Regular) // If regular stages are banned
					if (isStageAllowedForCharacter(CurrentCharacter, CurrentLevel)) // If the randomize stage is supposed to be playable by this character
						continue; // Restart the loop to try and get a level that isn't

			} while (CurrentCharacter == Characters_Gamma && isValueInArray(bannedLevelsGamma, CurrentLevel, 7));
		}
	}

	bool isStageAllowedForCharacter(short characterID, char stageID) {
		TrialLevelList levelList = TrialLevels[characterID];

		for (int i = 0; i < levelList.Count; i++)
		{
			if (levelList.Levels[i].Level == stageID)
				return true;
		}

		return false;
	}
}