#include "stdafx.h"
#include <string>
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>


using json = nlohmann::json;
using namespace std;

Trampoline* DeleteSave_t;
int CustomFlag = 0; //Used for progression story and credits
bool CreditCheck = false;
extern int musicCount;

void Rando_SaveProgression() {

	const char* saveOK = "Successfully Saved Rando progression on seed %d \n";
	string savePath = modpath + "\\SAVEDATA\\";

	json j;

	j["levelCount"] = levelCount;
	j["customFlag"] = CustomFlag;
	j["cutsceneCount"] = cutsceneAllowedCount;
	j["seed"] = SeedCopy;
	j["saveFile"] = CurrentSaveSlot;

	string saveNumber = to_string(CurrentSaveSlot);

	std::ofstream file(savePath + "RandoSave" + saveNumber + ".json");
	file << j;
	file.close();
	PrintDebug(saveOK, SeedCopy);
	return;
}

DataPointer(ObjectMaster*, FileSelTp, 0x3C5E8C0);

void Rando_LoadProgression() {

	if (GameState != 21 && GameMode != 12 || !FileSelTp)
		return;

	const char* loadOK = "Successfully Loaded Rando Save on seed %d \n";
	const char* loadFailed = "Save doesn't match the current seed, load progression cancelled. \n";
	string savePath = modpath + "\\SAVEDATA\\";

	string saveNumber = to_string(CurrentSaveSlot);
	string saveFileFullPath = savePath + "RandoSave" + saveNumber + ".json";

	json j;

	if (checkIfFileExists(saveFileFullPath.c_str()))
	{
		std::ifstream file(saveFileFullPath);
		file >> j;
		file.close();

		if (SeedCopy == (int64_t)j["seed"]) {

			levelCount = (int64_t)j["levelCount"];
			CustomFlag = (int64_t)j["customFlag"];
			cutsceneAllowedCount = (int64_t)j["cutsceneCount"];
			PrintDebug(loadOK, SeedCopy);
		}
		else {
			PrintDebug(loadFailed, SeedCopy);
		}
	}
	else {
		levelCount = 0;
		CustomFlag = 0;
		cutsceneAllowedCount = 0;
	}

	return;
}

void LoadSave_r() {

	j_LoadSave();
	Rando_LoadProgression();
}


void Rando_DeleteProgression() {
	if (GameState != 21 && GameMode != 12)
		return;

	const char* deleteMSG = "Deleted Rando progression. on save: %d \n";
	string savePath = modpath + "\\SAVEDATA\\";

	string saveNumber = to_string(CurrentSaveSlot);
	string saveFileFullPath = savePath + "RandoSave" + saveNumber + ".json";
	LPCSTR delSave = saveFileFullPath.c_str();

	if (checkIfFileExists(saveFileFullPath.c_str()))
	{
		if (DeleteFileA(delSave))
		{
			CustomFlag = 0;
			levelCount = 0;
			PrintDebug(deleteMSG, CurrentSaveSlot);
		}
	}

	return;
}

void DeleteSave_r() {

	Rando_DeleteProgression();
	auto original = reinterpret_cast<decltype(DeleteSave_r)*>(DeleteSave_t->Target());
	original();
}


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

	CustomFlagCheck();
	Rando_SaveProgression();

	return StartLevelCutscene(1);
}

enum SelectedChar {
	CharSonic,
	CharTails,
	CharKnuckles,
	CharAmy,
	CharBig,
	CharGamma,
	CharSuperSonic
};


//SA2 Style
void CustomFlagCheck() {

	if (GameMode == 9 || GameMode == 10)
		return;

	if (SelectedCharacter == CharSonic)
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
			}
			return;
		}
	}

	if (SelectedCharacter == CharTails)
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
			break;
		default:
			if (CustomFlag >= 7) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Tails_SpeedHighwayClear] = true;
				EventFlagArray[EventFlags_Tails_EggWalkerClear] = true;
				EventFlagArray[EventFlags_TailsAdventureComplete] = true;
				EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = true;
			}
			return;
		}
	}



	if (SelectedCharacter == CharKnuckles) //Knuckles
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
			break;
		default:
			if (CustomFlag >= 7) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Knuckles_Chaos6Clear] = true;
				EventFlagArray[EventFlags_KnucklesAdventureComplete] = true;
				EventFlagArray[EventFlags_AmyUnlockedAdventure] = true;
			}
			return;
		}
	}
	if (SelectedCharacter == CharAmy) //Amy
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
			break;
		default:
			if (CustomFlag >= 5) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Amy_ZeroClear] = true;
				EventFlagArray[EventFlags_AmyAdventureComplete] = true;
				EventFlagArray[EventFlags_BigUnlockedAdventure] = true;
			}
			return;
		}
	}

	if (SelectedCharacter == CharBig) //Big
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
			break;
		default:
			if (CustomFlag >= 6) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Big_Chaos6Clear] = true;
				EventFlagArray[EventFlags_BigAdventureComplete] = true;
				EventFlagArray[EventFlags_GammaUnlockedAdventure] = true;
			}
			return;
		}
	}

	if (SelectedCharacter == CharGamma) //Gamma
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
			break;
		default:
			if (CustomFlag >= 6) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Gamma_E101mkIIClear] = true;
				EventFlagArray[EventFlags_GammaAdventureComplete] = true;
				EventFlagArray[EventFlags_SuperSonicUnlockedAdventure] = true;
			}
			return;
		}
	}
	if (SelectedCharacter == CharSuperSonic)
	{
		if (CustomFlag >= 1) {
			CreditCheck = true;
			EventFlagArray[EventFlags_SuperSonicAdventureComplete] = true;
		}
	}

	return;
}

void init_FlagsProgression() {
	WriteCall((void*)0x413368, DeleteCustomFlag); //Reset flags when you create a new savefile.
	WriteCall((void*)0x42af3b, AddCustomFlag);

	WriteCall((void*)0x503782, LoadSave_r);	
	WriteCall((void*)0x5037fc, LoadSave_r);	
	WriteJump((void*)0x5053DD, LoadSave_r);
	DeleteSave_t = new Trampoline((int)DeleteSave, (int)DeleteSave + 0x6, DeleteSave_r);
}