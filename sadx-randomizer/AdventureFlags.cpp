#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>


using namespace std;
int CustomFlag = 0; //Used for progression story and credits
bool CreditCheck = false;
extern int musicCount;

int GetCharaProgression() {

	if (!CustomFlag)
	{
		ChaoGardenSSWarpOpen = 1;
		ChaoGardenECWarpOpen = 1;
		ChaoGardenMRWarpOpen = 1;

		switch (SelectedCharacter)
		{
		case 0:
			if (EventFlagArray[EventFlags_Sonic_Chaos0Clear] == 0)
				return 0;
			break;
		case 1:
			if (EventFlagArray[EventFlags_Tails_EggHornetClear] == 0)
				return 0;
			break;
		case 2:
			if (EventFlagArray[EventFlags_Knuckles_SpeedHighwayClear] == 0)
				return 0;
			break;
		case 3:
			if (EventFlagArray[EventFlags_Amy_TwinkleParkClear] == 0)
				return 0;
			break;
		case 4:
			if (EventFlagArray[EventFlags_Big_TwinkleParkClear] == 0)
				return 0;
			break;
		case 5:
			if (EventFlagArray[EventFlags_Gamma_FinalEggClear] == 0 && isChaoGameplayAllowed)
				return 0;
			break;
		case 6:
			if (EventFlagArray[EventFlags_SuperSonicAdventureComplete] == 0 && isChaoGameplayAllowed)
				return 0;
			break;
		}
	}

	return 1;
}


void DeleteCustomFlag() {

	if (CurrentLevel == 0 && GameMode == 12 && !DemoPlaying)
	{
		DeleteCreditStats();
		ResetValueAndObjects();
		if (SeedCopy != 0 && (CustomFlag != 0 || levelCount != 0))
		{
			levelCount = 0;
			TotalCount = 0;
			musicCount = 0;
		}

		if (!SeedCopy && levelCount != 0)
			Randomizer_GetNewRNG();

		CustomFlag = 0;
	}

	return SomethingAboutFlag();
}


void AddCustomFlag() {
	
	if (!IsAdventureComplete(SelectedCharacter))
		CustomFlag++;

	return StartLevelCutscene(1);
}


//SA2 Style
void CustomFlagCheck() {

	if (GameMode == 9 || GameMode == 10)
		return;

	if (SelectedCharacter == 0) //Sonic
	{
		switch (CustomFlag)
		{
		case 1:
			EventFlagArray[EventFlags_Sonic_Chaos0Clear] = true;
			EventFlagArray[EventFlags_Sonic_EmeraldCoastClear] = true;
			break;
		case 2:
			EventFlagArray[EventFlags_Sonic_EggHornetClear] = true;
			EventFlagArray[EventFlags_Sonic_WindyValleyOpen] = true;
			break;
		case 3:
			EventFlagArray[EventFlags_Sonic_WindyValleyClear] = true;
			EventFlagArray[EventFlags_Sonic_CasinopolisOpen] = true;
			break;
		case 4:
			EventFlagArray[EventFlags_Sonic_CasinopolisClear] = true;
			EventFlagArray[EventFlags_Sonic_IceCapOpen] = true;
			EventFlagArray[EventFlags_Sonic_IceCapClear] = true;
			break;
		case 5:
			EventFlagArray[EventFlags_Sonic_KnucklesDefeated] = true;
			EventFlagArray[EventFlags_Sonic_Chaos4Clear] = true;
			break;
		case 6:
			EventFlagArray[EventFlags_Sonic_SkyChaseAct1Clear] = true;
			EventFlagArray[EventFlags_Sonic_TwinkleParkOpen] = true;
			EventFlagArray[EventFlags_Sonic_TwinkleParkClear] = true;
			break;
		case 7:
			EventFlagArray[EventFlags_Sonic_SpeedHighwayOpen] = true;
			EventFlagArray[EventFlags_Sonic_SpeedHighwayClear] = true;
			EventFlagArray[EventFlags_Sonic_RedMountainOpen] = true;
			EventFlagArray[EventFlags_Sonic_RedMountainClear] = true;
			break;
		case 8:
			EventFlagArray[EventFlags_Sonic_SkyChaseAct2Clear] = true;
			EventFlagArray[EventFlags_Sonic_SkyDeckClear] = true;
			EventFlagArray[EventFlags_Sonic_Chaos6Clear] = true;
			break;
		case 9:
			EventFlagArray[EventFlags_Sonic_LostWorldOpen] = true;
			EventFlagArray[EventFlags_Sonic_LostWorldClear] = true;
			EventFlagArray[EventFlags_Sonic_FinalEggOpen] = true;
			break;
		case 10:
		default:
			if (CustomFlag >= 10) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Sonic_FinalEggClear] = true;
				EventFlagArray[EventFlags_Sonic_EggViperClear] = true;
				EventFlagArray[EventFlags_SonicAdventureComplete] = true;
				EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
				credits();
			}
			break;
		}
	}

	if (SelectedCharacter == 1) //Tails
	{
		switch (CustomFlag)
		{
		case 1:
			CreditCheck = false;
			EventFlagArray[EventFlags_Tails_EggHornetClear] = true;
			EventFlagArray[EventFlags_Tails_WindyValleyOpen] = true;
			break;
		case 2:
			CreditCheck = false;
			EventFlagArray[EventFlags_Tails_WindyValleyClear] = true;
			EventFlagArray[EventFlags_Tails_CasinopolisOpen] = true;
			break;
		case 3:
			EventFlagArray[EventFlags_Tails_CasinopolisClear] = true;
			EventFlagArray[EventFlags_Tails_IceCapOpen] = true;
			break;
		case 4:
			EventFlagArray[EventFlags_Tails_IceCapClear] = true;
			EventFlagArray[EventFlags_Tails_Chaos4Clear] = true;
			EventFlagArray[EventFlags_Tails_SkyChaseAct1Clear] = true;
			break;
		case 5:
			EventFlagArray[EventFlags_Tails_SandHillClear] = true;
			EventFlagArray[EventFlags_Tails_SkyChaseAct2Clear] = true;
			EventFlagArray[EventFlags_Tails_SkyDeckClear] = true;
			break;
		case 6:
			CreditCheck = true;
			EventFlagArray[EventFlags_Tails_SpeedHighwayClear] = true;
			EventFlagArray[EventFlags_Tails_EggWalkerClear] = true;
			EventFlagArray[EventFlags_TailsAdventureComplete] = true;
			EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
			credits();
			break;
		default:
			if (CustomFlag >= 7) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Tails_SpeedHighwayClear] = true;
				EventFlagArray[EventFlags_Tails_EggWalkerClear] = true;
				EventFlagArray[EventFlags_TailsAdventureComplete] = true;
				EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
				credits();
			}
			break;
		}
	}

	

	if (SelectedCharacter == 2) //Knuckles
	{
		switch (CustomFlag)
		{
		case 1:
			CreditCheck = false;
			EventFlagArray[EventFlags_Knuckles_SpeedHighwayClear] = true;
			EventFlagArray[EventFlags_Knuckles_CasinopolisOpen] = true;
			break;
		case 2:
			EventFlagArray[EventFlags_Knuckles_CasinopolisClear] = true;
			break;
		case 3:
			EventFlagArray[EventFlags_Knuckles_Chaos2Clear] = true;
			EventFlagArray[EventFlags_Knuckles_RedMountainClear] = true;
			break;
		case 4:
			EventFlagArray[EventFlags_Knuckles_Chaos4Clear] = true;
			EventFlagArray[EventFlags_Knuckles_LostWorldClear] = true;
			break;
		case 5:
			EventFlagArray[EventFlags_Knuckles_EggCarrierSunk] = true;
			EventFlagArray[EventFlags_Knuckles_SkyDeckClear] = true;
			break;
		case 6:
			CreditCheck = true;
			EventFlagArray[EventFlags_Knuckles_Chaos6Clear] = true;
			EventFlagArray[EventFlags_KnucklesAdventureComplete] = true;
			EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
			credits();
			break;
		default:
			if (CustomFlag >= 7) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Knuckles_Chaos6Clear] = true;
				EventFlagArray[EventFlags_KnucklesAdventureComplete] = true;
				EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
				credits();
			}
			break;
		}
	}
	if (SelectedCharacter == 3) //Amy
	{
		switch (CustomFlag)
		{
		case 1:
			CreditCheck = false;
			EventFlagArray[EventFlags_Amy_TwinkleParkClear] = true;
			break;
		case 2:
			EventFlagArray[EventFlags_Amy_HotShelterClear] = true;
			break;
		case 3:
			EventFlagArray[EventFlags_Amy_EggCarrierSunk] = true;
			EventFlagArray[EventFlags_Amy_FinalEggClear] = true;
			break;
		case 4:
			CreditCheck = true;
			EventFlagArray[EventFlags_Amy_ZeroClear] = true;
			EventFlagArray[EventFlags_AmyAdventureComplete] = true;
			EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
			credits();
			break;
		default:
			if (CustomFlag >= 5) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Amy_ZeroClear] = true;
				EventFlagArray[EventFlags_AmyAdventureComplete] = true;
				EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
				credits();
			}
			break;
		}
	}

	if (SelectedCharacter == 4) //Big
	{
		switch (CustomFlag)
		{
		case 1:
			CreditCheck = false;
			EventFlagArray[EventFlags_Big_TwinkleParkClear] = true;
			break;
		case 2:
			EventFlagArray[EventFlags_Big_IceCapClear] = true;
			break;
		case 3:
			EventFlagArray[EventFlags_Big_EmeraldCoastClear] = true;
			break;
		case 4:
			EventFlagArray[EventFlags_Big_HotShelterClear] = true;
			break;
		case 5:
			CreditCheck = true;
			EventFlagArray[EventFlags_Big_Chaos6Clear] = true;
			EventFlagArray[EventFlags_BigAdventureComplete] = true;
			EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
			credits();
			break;
		default:
			if (CustomFlag >= 6) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Big_Chaos6Clear] = true;
				EventFlagArray[EventFlags_BigAdventureComplete] = true;
				EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
				credits();
			}
			break;
		}
	}

	if (SelectedCharacter == 5) //Gamma
	{
		switch (CustomFlag)
		{
		case 1:
			EventFlagArray[EventFlags_Gamma_FinalEggClear] = true;
			CreditCheck = false;
			break;
		case 2:
			EventFlagArray[EventFlags_Gamma_E101Clear] = true;
			EventFlagArray[EventFlags_Gamma_EmeraldCoastClear] = true;
			EventFlagArray[EventFlags_Gamma_WindyValleyOpen] = true;
			break;
		case 3:
			EventFlagArray[EventFlags_Gamma_WindyValleyClear] = true;
			EventFlagArray[EventFlags_Gamma_RedMountainClear] = true;
			break;
		case 4:
			EventFlagArray[EventFlags_Gamma_HotShelterClear] = true;
			break;
		case 5:
			CreditCheck = true;
			EventFlagArray[EventFlags_Gamma_E101mkIIClear] = true;
			EventFlagArray[EventFlags_GammaAdventureComplete] = true;
			EventFlagArray[EventFlags_SuperSonicUnlockedAdventure] = true;
			credits();
			break;
		default:
			if (CustomFlag >= 6) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Gamma_E101mkIIClear] = true;
				EventFlagArray[EventFlags_GammaAdventureComplete] = true;
				EventFlagArray[EventFlags_SuperSonicUnlockedAdventure] = true;
				credits();
			}
			break;
		}
	}
	if (SelectedCharacter == 6)
	{
		if (CustomFlag >= 1) {
			CreditCheck = true;
			EventFlagArray[EventFlags_SuperSonicAdventureComplete] = true;
			credits();
		}
	}

	return;
}
