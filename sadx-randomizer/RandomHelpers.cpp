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

			// If the character can access this stage in normal conditions, randomize another stage
			if(Regular)
				if (isStageAllowedForCharacter(CurrentCharacter, CurrentLevel))
					randomizeStages();
		}
	}

	bool isStageAllowedForCharacter(short characterID, char stageID, char actNumber) {
		// Get the stage list for the character we are requesting
		TrialLevelListEntry *levelList = TrialLevels[characterID].Levels;

		// Go through the list of stages
		for (int i = 0; i < TrialLevels[characterID].Count; i++)
		{
			// If the stage we're currently checking is the same as the one we received as argument, return true
			if (levelList[i].Level == stageID && levelList[i].Act == actNumber) {
				return true;
			}
		}

		// If nothing matches, returns false
		return false;
	}
}