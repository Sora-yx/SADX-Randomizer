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
		// Get the stage list for the character we are requesting
		TrialLevelList levelList = TrialLevels[characterID];

		// Go through the list of stages
		for (int i = 0; i < levelList.Count; i++)
		{
			// If the stage we're currently checking is the same as the one we received as argument, return true
			if (levelList.Levels[i].Level == stageID)
				return true;
		}

		// If nothing matches, returns false
		return false;
	}
}