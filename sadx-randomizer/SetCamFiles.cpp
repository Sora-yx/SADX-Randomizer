#include "stdafx.h"

bool isSetLoaded = false;

StringLevelLayout SetCamFileArray[51]{

	{ LevelIDs_EmeraldCoast, GammaVersion, 0, "ECE", "C0103" },
	{ LevelIDs_EmeraldCoast, SonicVersion, 0, "EC0", "C0100", },
	{ LevelIDs_EmeraldCoast, SonicVersion, 1, "EC1", "C0101", },
	{ LevelIDs_EmeraldCoast, BigVersion, 2, "EC2", "C0102", },
	{ LevelIDs_WindyValley, GammaVersion, 0, "WVG", "C0203"},
	{ LevelIDs_WindyValley, SonicVersion, 0, "WV0", "C0200"},
	{ LevelIDs_WindyValley, SonicVersion, 1, "WV1", "C0201"},
	{ LevelIDs_WindyValley, SonicVersion, 2, "WV2", "C0202"},
	{ LevelIDs_WindyValley, TailsVersion, 2, "WVM", "C0204"},
	{ LevelIDs_TwinklePark, SonicVersion, 0, "TP0", "C0300"},
	{ LevelIDs_TwinklePark, SonicVersion, 1, "TP1", "C0301"},
	{ LevelIDs_TwinklePark, AmyVersion,	1, "TPA", "C0303"},
	{ LevelIDs_TwinklePark, BigVersion,	1, "TPB", "C0304"},
	{ LevelIDs_TwinklePark, AmyVersion,	2, "TP2", "C0302"},
	{ LevelIDs_SpeedHighway, SonicVersion, 0, "SH0", "C0400"},
	{ LevelIDs_SpeedHighway, SonicVersion, 1, "SH1", "C0401"},
	{ LevelIDs_SpeedHighway, SonicVersion, 2, "SH2", "C0402"},
	{ LevelIDs_SpeedHighway, TailsVersion, 0, "SHM", "C0403"},
	{ LevelIDs_SpeedHighway, KnucklesVersion, 2, "SHK", "C0404"},
	{ LevelIDs_RedMountain, SonicVersion, 0, "RM0", "C0500"},
	{ LevelIDs_RedMountain, SonicVersion, 1, "RM1", "C0501"},
	{ LevelIDs_RedMountain, GammaVersion, 1, "RMG", "C0503"},
	{ LevelIDs_RedMountain, KnucklesVersion, 2, "RM2", "C0502" },
	{ LevelIDs_SkyDeck, SonicVersion, 0, "SD0", "C0600"},
	{ LevelIDs_SkyDeck, TailsVersion, 0, "SDM", "C0603" },
	{ LevelIDs_SkyDeck, SonicVersion, 1, "SD1", "C0601"},
	{ LevelIDs_SkyDeck, SonicVersion, 2, "SD2", "C0602"},
	{ LevelIDs_SkyDeck, KnucklesVersion, 2, "SDK", "C0604"},
	{ LevelIDs_LostWorld, SonicVersion, 0, "LW0", "C0700" },
	{ LevelIDs_LostWorld, SonicVersion, 1, "LW1",  "C0701"},
	{ LevelIDs_LostWorld, KnucklesVersion, 1, "LWK", "C0703" },
	{ LevelIDs_LostWorld, SonicVersion, 2, "LW2", "C0702"},
	{ LevelIDs_LostWorld, KnucklesVersion, 2, "LW2", "C0702"}, //failsafe since it's possible to reach sonic section
	{ LevelIDs_IceCap, SonicVersion, 0, "IC0", "C0800"},
	{ LevelIDs_IceCap, SonicVersion, 1,	"IC1", "C0801"},
	{ LevelIDs_IceCap, SonicVersion, 2,	"IC2", "C0802"},
	{ LevelIDs_IceCap, TailsVersion, 2, "ICM", "C0802" },
	{ LevelIDs_IceCap, BigVersion, 3, "IC3", "C0803" },
	{ LevelIDs_Casinopolis, SonicVersion, 0, "Cas0", "C0900"},
	{ LevelIDs_Casinopolis, KnucklesVersion, 0, "CasK", "C0905"},
	{ LevelIDs_Casinopolis, SonicVersion, 1, "Cas1", "C0901" },
	{ LevelIDs_Casinopolis, TailsVersion, 1, "CasM", "C0904"},
	{ LevelIDs_FinalEgg, AmyVersion, 0, "FEA", "C1003"},
	{ LevelIDs_FinalEgg, SonicVersion, 0, "FE0", "C1000"},
	{ LevelIDs_FinalEgg, SonicVersion, 1, "FE1", "C1001"},
	{ LevelIDs_FinalEgg, SonicVersion, 2, "FE2", "C1002"},
	{ LevelIDs_FinalEgg, GammaVersion, 2, "FEG", "C1004"},
	{ LevelIDs_HotShelter, BigVersion, 0, "HSB", "C1203"},
	{ LevelIDs_HotShelter, AmyVersion, 0, "HS0", "C1200"},
	{ LevelIDs_HotShelter, AmyVersion, 1, "HS1", "C1201"},
	{ LevelIDs_HotShelter, GammaVersion, 2, "HS2", "C1202"},
};


void __cdecl RandoLoad_SetCamFiles() {

	for (int i = 0; i < LengthOfArray(SetCamFileArray); i++) 
	{
		if (CurrentLevel == SetCamFileArray[i].LevelID && CurrentStageVersion == SetCamFileArray[i].version)
		{
			std::string lvl = SetCamFileArray[i].SetFileName;
			std::string cam = SetCamFileArray[i].CamFileName;
			lvl = CharIDStrings[CurrentCharacter] + lvl + ".bin";
			cam = cam + ".bin";
			int act = SetCamFileArray[i].act;
			LoadFileWithMalloc(lvl.c_str(), (LPVOID*)&SetFiles[act]);
			LoadFileWithMalloc(cam.c_str(), (LPVOID*)&CamData[act]);
		}
	}

	return;
}


void __cdecl LoadLevelFiles_r(unsigned int curLevel) {

	if (isRandoLevel() && CurrentLevel > LevelIDs_HedgehogHammer && CurrentLevel < LevelIDs_Chaos0)
	{
		for (int i = 0; i < LengthOfArray(SetCamFileArray); i++) //FailSafe, if layout doesn't exist, simply let SADX load the stage (vanilla).
		{
			if (CurrentLevel == SetCamFileArray[i].LevelID && CurrentStageVersion == SetCamFileArray[i].version)
			{
				if (CurrentLevel != LevelIDs_Casinopolis) {
					ReleaseSetFile();
					ReleaseCamFile();
				}
				RandoLoad_SetCamFiles();
				isSetLoaded = true;
				break;
			}
		}
	}

	if (!isRandoLevel() || CurrentLevel == LevelIDs_HedgehogHammer || CurrentLevel >= LevelIDs_Chaos0)
		isSetLoaded = true;

	SetCurrentCamData(curLevel);
	SetCurrentSetData(curLevel);
}


void AddLevelLayout(std::string FolderName, std::string LevelName, const HelperFunctions& helperFunctions) {
	for (int i = 0; i < 8; i++) { //Add Custom Set File from Mod folder for each character, using different name than SADX vanilla to prevent mod order conflict and overwrite shit.
		std::string path = "system\\";
		std::string path2 = "system\\sets\\" + FolderName;
		std::string bin = LevelName + ".bin";
		std::string lvl = path + CharIDStrings[i] + bin;
		std::string lvl2 = path2 + CharIDStrings[i] + bin;
		helperFunctions.ReplaceFile(lvl.c_str(), lvl2.c_str());
	}
}

void CheckAndDisplayWarningLayoutError() {
	if (!CharObj2Ptrs[0] || isSetLoaded  || !IsIngame() || !RNGStages)
		return;

	DisplayDebugStringFormatted(NJM_LOCATION(2, 6), "WARNING: The Set file from Level %d", CurrentLevel);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 7), "and Version %d didn't load properly", CurrentStageVersion);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 8), "The vanilla Layout has been loaded for safety.");
}

void LayoutFunctionInit() {

	if (!RNGStages)
		return;

	WriteData<5>((void*)0x4237b4, 0x90); //remove "SetCurrentCamData" from LoadLevelFiles, we will manually call it later.
	WriteCall((void*)0x4237ba, LoadLevelFiles_r);
}