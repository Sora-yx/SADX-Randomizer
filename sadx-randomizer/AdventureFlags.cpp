#include "stdafx.h"
#include <string>
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>


using json = nlohmann::json;
using namespace std;

Trampoline* DeleteSave_t;
Trampoline* SeqSetSection_t;
Trampoline* seqCheckStage_t;

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
			EventFlagArray[EventFlags_Sonic_Chaos0Clear] = 1;
			EventFlagArray[EventFlags_Sonic_EmeraldCoastClear] = 1;
			break;
		case 2:
			EventFlagArray[EventFlags_Sonic_EggHornetClear] = 1;
			EventFlagArray[EventFlags_Sonic_WindyValleyOpen] = 1;
			break;
		case 3:
			EventFlagArray[EventFlags_Sonic_WindyValleyClear] = 1;
			EventFlagArray[EventFlags_Sonic_CasinopolisOpen] = 1;
			break;
		case 4:
			EventFlagArray[EventFlags_Sonic_CasinopolisClear] = 1;
			EventFlagArray[EventFlags_Sonic_IceCapOpen] = 1;
			EventFlagArray[EventFlags_Sonic_IceCapClear] = 1;
			break;
		case 5:
			EventFlagArray[EventFlags_Sonic_KnucklesDefeated] = 1;
			EventFlagArray[EventFlags_Sonic_Chaos4Clear] = 1;
			break;
		case 6:
			EventFlagArray[EventFlags_Sonic_SkyChaseAct1Clear] = 1;
			EventFlagArray[EventFlags_Sonic_TwinkleParkOpen] = 1;
			EventFlagArray[EventFlags_Sonic_TwinkleParkClear] = 1;
			break;
		case 7:
			EventFlagArray[EventFlags_Sonic_SpeedHighwayOpen] = 1;
			EventFlagArray[EventFlags_Sonic_SpeedHighwayClear] = 1;
			EventFlagArray[EventFlags_Sonic_RedMountainOpen] = 1;
			EventFlagArray[EventFlags_Sonic_RedMountainClear] = 1;
			break;
		case 8:
			EventFlagArray[EventFlags_Sonic_SkyChaseAct2Clear] = 1;
			EventFlagArray[EventFlags_Sonic_SkyDeckClear] = 1;
			EventFlagArray[EventFlags_Sonic_Chaos6Clear] = 1;
			break;
		case 9:
			EventFlagArray[EventFlags_Sonic_LostWorldOpen] = 1;
			EventFlagArray[EventFlags_Sonic_LostWorldClear] = 1;
			EventFlagArray[EventFlags_Sonic_FinalEggOpen] = 1;
			break;
		case 10:
		default:
			if (CustomFlag >= 10) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Sonic_FinalEggClear] = 1;
				EventFlagArray[EventFlags_Sonic_EggViperClear] = 1;
				EventFlagArray[EventFlags_SonicAdventureComplete] = 1;
				EventFlagArray[EventFlags_TailsUnlockedAdventure] = 1;
				CustomFlag = 0;
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
			EventFlagArray[EventFlags_Tails_EggHornetClear] = 1;
			EventFlagArray[EventFlags_Tails_WindyValleyOpen] = 1;
			break;
		case 2:
			CreditCheck = false;
			EventFlagArray[EventFlags_Tails_WindyValleyClear] = 1;
			EventFlagArray[EventFlags_Tails_CasinopolisOpen] = 1;
			break;
		case 3:
			EventFlagArray[EventFlags_Tails_CasinopolisClear] = 1;
			EventFlagArray[EventFlags_Tails_IceCapOpen] = 1;
			break;
		case 4:
			EventFlagArray[EventFlags_Tails_IceCapClear] = 1;
			EventFlagArray[EventFlags_Tails_Chaos4Clear] = 1;
			EventFlagArray[EventFlags_Tails_SkyChaseAct1Clear] = 1;
			break;
		case 5:
			EventFlagArray[EventFlags_Tails_SandHillClear] = 1;
			EventFlagArray[EventFlags_Tails_SkyChaseAct2Clear] = 1;
			EventFlagArray[EventFlags_Tails_SkyDeckClear] = 1;
			break;
		case 6:
		default:
			if (CustomFlag >= 6) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Tails_SpeedHighwayClear] = 1;
				EventFlagArray[EventFlags_Tails_EggWalkerClear] = 1;
				EventFlagArray[EventFlags_TailsAdventureComplete] = 1;
				EventFlagArray[EventFlags_KnucklesUnlockedAdventure] = 1;
				CustomFlag = 0;
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
			EventFlagArray[EventFlags_Knuckles_SpeedHighwayClear] = 1;
			EventFlagArray[EventFlags_Knuckles_CasinopolisOpen] = 1;
			break;
		case 2:
			EventFlagArray[EventFlags_Knuckles_CasinopolisClear] = 1;
			break;
		case 3:
			EventFlagArray[EventFlags_Knuckles_Chaos2Clear] = 1;
			EventFlagArray[EventFlags_Knuckles_RedMountainClear] = 1;
			break;
		case 4:
			EventFlagArray[EventFlags_Knuckles_Chaos4Clear] = 1;
			EventFlagArray[EventFlags_Knuckles_LostWorldClear] = 1;
			break;
		case 5:
			EventFlagArray[EventFlags_Knuckles_EggCarrierSunk] = 1;
			EventFlagArray[EventFlags_Knuckles_SkyDeckClear] = 1;
			break;
		case 6:
		default:
			if (CustomFlag >= 6) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Knuckles_Chaos6Clear] = 1;
				EventFlagArray[EventFlags_KnucklesAdventureComplete] = 1;
				EventFlagArray[EventFlags_AmyUnlockedAdventure] = 1;
				CustomFlag = 0;
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
			EventFlagArray[EventFlags_Amy_TwinkleParkClear] = 1;
			break;
		case 2:
			EventFlagArray[EventFlags_Amy_HotShelterClear] = 1;
			break;
		case 3:
			EventFlagArray[EventFlags_Amy_EggCarrierSunk] = 1;
			EventFlagArray[EventFlags_Amy_FinalEggClear] = 1;
			break;
		case 4:
		default:
			if (CustomFlag >= 4) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Amy_ZeroClear] = 1;
				EventFlagArray[EventFlags_AmyAdventureComplete] = 1;
				EventFlagArray[EventFlags_BigUnlockedAdventure] = 1;
				CustomFlag = 0;
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
			EventFlagArray[EventFlags_Big_TwinkleParkClear] = 1;
			break;
		case 2:
			EventFlagArray[EventFlags_Big_IceCapClear] = 1;
			break;
		case 3:
			EventFlagArray[EventFlags_Big_EmeraldCoastClear] = 1;
			break;
		case 4:
			EventFlagArray[EventFlags_Big_HotShelterClear] = 1;
			break;
		case 5:
		default:
			if (CustomFlag >= 5) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Big_Chaos6Clear] = 1;
				EventFlagArray[EventFlags_BigAdventureComplete] = 1;
				EventFlagArray[EventFlags_GammaUnlockedAdventure] = 1;
				CustomFlag = 0;
			}
			return;
		}

	}

	if (SelectedCharacter == CharGamma) //Gamma
	{
		switch (CustomFlag)
		{
		case 1:
			EventFlagArray[EventFlags_Gamma_FinalEggClear] = 1;
			CreditCheck = false;
			break;
		case 2:
			EventFlagArray[EventFlags_Gamma_E101Clear] = 1;
			EventFlagArray[EventFlags_Gamma_EmeraldCoastClear] = 1;
			EventFlagArray[EventFlags_Gamma_WindyValleyOpen] = 1;
			break;
		case 3:
			EventFlagArray[EventFlags_Gamma_WindyValleyClear] = 1;
			EventFlagArray[EventFlags_Gamma_RedMountainClear] = 1;
			break;
		case 4:
			EventFlagArray[EventFlags_Gamma_HotShelterClear] = 1;
			break;
		case 5:
		default:
			if (CustomFlag >= 5) {
				CreditCheck = true;
				EventFlagArray[EventFlags_Gamma_E101mkIIClear] = 1;
				EventFlagArray[EventFlags_GammaAdventureComplete] = 1;
				EventFlagArray[EventFlags_SuperSonicUnlockedAdventure] = 1;
				CustomFlag = 0;
			}
			return;
		}
	}

	if (SelectedCharacter == CharSuperSonic)
	{
		if (CustomFlag >= 1) {
			CreditCheck = true;
			EventFlagArray[EventFlags_SuperSonicAdventureComplete] = 1;
		}
	}

	return;
}

void __cdecl SetEventFlag_r(EventFlags a1)
{
	if (RNGStages)
		return;

	EventFlagArray[a1] = 1;
}

void __cdecl SeqSetSection_r()
{
	if (RNGStages) {
		SetRandomStageAct(1, 0);
		return;
	}

	auto original = reinterpret_cast<decltype(SeqSetSection_r)*>(SeqSetSection_t->Target());
	original();
}


int __cdecl seqCheckStage_r(int stage, int act)
{
	if (RNGStages) {
		return 0;
	}

	FunctionPointer(int, original, (int stage, int act), seqCheckStage_t->Target());
	return original(stage, act);
}


FunctionPointer(int, seqCheckStage, (int stage, int act), 0x412D40);


void init_FlagsProgression() {

	if (!RNGStages)
		return;

	WriteCall((void*)0x413368, DeleteCustomFlag); //Reset flags when you create a new savefile.
	WriteCall((void*)0x42af3b, AddCustomFlag);

	WriteCall((void*)0x503782, LoadSave_r);
	WriteCall((void*)0x5037fc, LoadSave_r);
	WriteJump((void*)0x5053DD, LoadSave_r);
	DeleteSave_t = new Trampoline((int)DeleteSave, (int)DeleteSave + 0x6, DeleteSave_r);

	//Prevent the game to set flag to make the story progress, we will do it our own way, this should avoid corrupted save and unexpected behavior.
	WriteJump(SetEventFlag, SetEventFlag_r);
	SeqSetSection_t = new Trampoline((int)SeqSetSection, (int)SeqSetSection + 0x5, SeqSetSection_r);
	seqCheckStage_t = new Trampoline((int)seqCheckStage, (int)seqCheckStage + 0x8, seqCheckStage_r);

	// just to be safe: 
	WriteData<1>((int*)0x413690, 0xC3);	 //Prevent SedEndSection
	WriteData<1>((int*)0x413870, 0XC3); //TEST: remove something which set flag

	WriteData<1>((int*)0x412E20, 0xC3); //remove flag level clear
	return;
}