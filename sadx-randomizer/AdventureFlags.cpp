#include "stdafx.h"
#include "Utils.h"
#include <string>
#include <fstream>
#include <iostream>
#include <string.h>


#include "RandomHelpers.h"

using namespace std;
extern int CustomFlag;
bool CreditCheck = false;

//SADX Style
int CustomFlagCheckSA1_R() {

	if (SelectedCharacter == 0) //Sonic
	{
		CurrentCharacter = 0;

		if (NextLevel > LevelIDs_E101R && NextLevel < LevelIDs_SkyChase1)
			return 0;
	
		if (CustomFlag == 1 && EventFlagArray[EventFlags_Sonic_Chaos0Clear] == false)
		{
			EventFlagArray[EventFlags_Sonic_Chaos0Clear] = true;
			ChaosAdventureData = 1;
			CurrentAdventureData + 2;
			EventTailsData = 0;
			CutsceneFlagData();
			SetNextLevelAndAct(26, 4);
			return 0; //Will call original GotoNextLevel, we want the game to follow the story progression
		}

		if (CustomFlag == 2 && EventFlagArray[EventFlags_Sonic_EmeraldCoastClear] == false)
		{
			EventFlagArray[EventFlags_Sonic_EmeraldCoastClear] = true;
			CurrentAdventureData + 2;
			ChaosAdventureData = 1;
			TailsAdventureData = 1;
			SetNextLevelAndAct(26, 4);
			StartCutsceneFlag(3);
			return 0; 
		}

		if (CustomFlag == 3 && EventFlagArray[EventFlags_Sonic_EggHornetClear] == false)
		{
			EventFlagArray[EventFlags_Sonic_EggHornetClear] = true;
			EventFlagArray[EventFlags_Sonic_WindyValleyClear] = true;
			SetNextLevelAndAct(33, 0);
			CurrentAdventureData + 2;
			return 0;
		}

		if (CustomFlag == 4)
		{
			EventFlagArray[EventFlags_Sonic_CasinopolisClear] = true;
			SetNextLevelAndAct(26, 1);
			return 0;
		}

		if (CustomFlag == 5)
		{
			EventFlagArray[EventFlags_Sonic_CasinopolisClear] = true;
			SetNextLevelAndAct(33, 1);
			return 0;
		}


		return 1;

	}
}



void AddCustomFlag() {

	if (CurrentLevel < 40)
	{
		std::ofstream FlagFile("Flags.txt");
		FlagFile << CustomFlag++;
		FlagFile.close();
	}
}




//SA2 Style
void CustomFlagCheck() {

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
			CreditCheck = true;
			EventFlagArray[EventFlags_Sonic_FinalEggClear] = true;
			EventFlagArray[EventFlags_Sonic_EggViperClear] = true;
			EventFlagArray[EventFlags_SonicAdventureComplete] = true;
			EventFlagArray[EventFlags_TailsUnlockedAdventure] = true;
			credits();
			break;
		default:
			CreditCheck = false;
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
			return;
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
			return;
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
			CreditCheck = false;
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
			CreditCheck = false;
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
			CreditCheck = false;
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
			CreditCheck = false;
			break;
		}
	}
		if (SelectedCharacter == 6)
		{
			switch (CustomFlag)
			{
			case 1:
				CreditCheck = true;
				EventFlagArray[EventFlags_SuperSonicAdventureComplete] = true;
				credits();
				break;
			default:
				CreditCheck = false;
				break;
			}
		}

		return;
	
}