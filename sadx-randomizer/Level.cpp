#include "stdafx.h"
#include "Trampoline.h"
#include "RandomHelpers.h"
#include "StageSettings.h"

extern uint32_t TotalCount;
extern bool ChaoSpawn;
extern char GetCustomLayout;
extern char TimeSecCopy;
extern char TimeMinCopy;
extern char TimeFrameCopy;
extern int RingCopy;

SetLevelPosition PlayerStartPosition[52] { //Casino pos are hardcoded

	{ AmyVersion, LevelAndActIDs_HedgehogHammer, { -55, 0, -31 }, 0 },
	{ SonicVersion, LevelAndActIDs_EmeraldCoast1, { -9, 16, 4 }, 0x6000},
	{ SonicVersion, LevelAndActIDs_EmeraldCoast2, { -986.5f, 1145, -2856 }, 0x4000 },
	{ BigVersion, LevelAndActIDs_EmeraldCoast3, { 6090, 30, 1000 }, 0 },
	{ GammaVersion, LevelAndActIDs_WindyValley1, { -10, -102, -10 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley1, { 1230, -333, -140 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley2, { 49.0571, 288.873, -26.8347 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley3, { 1096, 205, -1251 }, 0x4000 },
	{ TailsVersion, LevelAndActIDs_WindyValley3, { 1093, -158, -1254 }, 0 },
	{ SonicVersion, LevelAndActIDs_TwinklePark1, { -2000, 1770, -985 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, { 520, 975, 1620 }, 0xC000 },
	{ AmyVersion, LevelAndActIDs_TwinklePark2, { 723, 70, -358 }, 0xC000 },
	{ BigVersion, LevelAndActIDs_TwinklePark2, { 230, 80, -538 }, 0xC000 },
	{ AmyVersion, LevelAndActIDs_TwinklePark3, { 75, 0, -390 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway1, { -673, -10, 5 }, 0 },
	{ TailsVersion, LevelAndActIDs_SpeedHighway1, { -673, -10, 5 }, 0 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway2, { -50, 42, 0 }, 0 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway3, { 72, 26, 192 }, 0xC000 },
	{ KnucklesVersion, LevelAndActIDs_SpeedHighway3, { -230, 150, -1740 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_RedMountain1, { 18, 36, 636 }, 0 },
	{ SonicVersion, LevelAndActIDs_RedMountain2, { -78, 831, 1919 }, 0 },
	{ GammaVersion, LevelAndActIDs_RedMountain2, { -78, 831, 1919 }, 0 },
	{ KnucklesVersion, LevelAndActIDs_RedMountain3, { -3147, 764, -1358 }, 0xFFFFC000 },
	{ SonicVersion, LevelAndActIDs_SkyDeck1, {0, -387.625, 379.5}, 270},
	{ TailsVersion, LevelAndActIDs_SkyDeck1, {0, -387.625, 379.5}, 270},
	{ SonicVersion, LevelAndActIDs_SkyDeck2, { 327, -74, 2535 }, 0 },
	{ SonicVersion, LevelAndActIDs_SkyDeck3, { -696, -86, 135 }, 0 },
	{ KnucklesVersion, LevelAndActIDs_SkyDeck3, { 674, 207, 12 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_LostWorld1, { -264, 73, -168 }, 0 },
	{ SonicVersion, LevelAndActIDs_LostWorld2, { 220, 73, -1423 }, 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_LostWorld2, { 7482, -2622, 908 }, 0 },
	{ SonicVersion, LevelAndActIDs_LostWorld3,  { 270, 10, 0 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap1, { 1580, 84, 1074 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap2, { 1060, 336, 280 }, 0 },
	{ SonicVersion, LevelAndActIDs_IceCap3, { 120, 375, -40 }, 0x8800 },
	{ TailsVersion, LevelAndActIDs_IceCap3, { 120, 375, -40 }, 0x8800 },
	{ BigVersion, LevelAndActIDs_IceCap4, { 1260, 224, -38 }, 0 },
	{ SonicVersion, LevelAndActIDs_FinalEgg1, { 170, -165, 490 }, 0 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, { 170, -165, 490 }, 0xC000 },
	{ SonicVersion, LevelAndActIDs_FinalEgg2, { 1060, 595, -383 }, 0xC000 },
	{ SonicVersion, LevelAndActIDs_FinalEgg3, { 1071.7f, 240, -518 }, 0x8000 },
	{ GammaVersion, LevelAndActIDs_FinalEgg3, { 46.5f, -3240.6f, -224.5f }, 0 },
	{ AmyVersion, LevelAndActIDs_HotShelter1, { 0, 236, 51.5f }, 0x4000 },
	{ BigVersion, LevelAndActIDs_HotShelter1, { 0, 236, 51.5f }, 0x4000 },
	{ AmyVersion, LevelAndActIDs_HotShelter2, { 215, 278, -398 }, 0x4000 },
	{ GammaVersion, LevelAndActIDs_HotShelter3, { -20, 486, 73 }, 0xC000 },
};


Trampoline MovePlayerToStartPoint_T((int)MovePlayerToStartPoint, (int)MovePlayerToStartPoint + 0x5, MovePlayerToStartPoint_R);

void MovePlayerToStartPoint_R(EntityData1* data) {

	uint16_t levelact = (((short)CurrentLevel) << 8) | CurrentAct;

	if (GetBackRing && CurrentMission >= Mission2_100Rings)
	{
		Rings = RingCopy;
		TimeSeconds = TimeSecCopy;
		TimeMinutes = TimeMinCopy;
		TimeFrames = TimeFrameCopy;
		if (CurrentStageVersion == AmyVersion && CurrentLevel == LevelIDs_FinalEgg || isTailsVersion || CurrentStageVersion == TailsVersion && CurrentLevel == LevelIDs_SpeedHighway)
			Lives++;
		ResetRestartData();
		ResetGravity();
		GameMode = GameModes_Adventure_ActionStg;
		GetBackRing = false;
	}

	if (GameMode != 9 && GameMode != 10 && CurrentLevel < LevelIDs_StationSquare && CurrentLevel > LevelIDs_Past)
		GameMode = GameModes_Adventure_ActionStg; //force gamemode to 4 to fix the restart.

	int GetCP = CheckRestartLevel();
	if (!GetCP || GetBackRing && CurrentMission >= 2) //don't change player position if a CP has been grabbed.
	{
		for (uint8_t i = 0; i < LengthOfArray(PlayerStartPosition); i++)
		{
			if (levelact == PlayerStartPosition[i].LevelID && CurrentStageVersion == PlayerStartPosition[i].version)
			{
				 EntityData1Ptrs[0]->Position = PlayerStartPosition[i].Position;
				EntityData1Ptrs[0]->Rotation.y = PlayerStartPosition[i].YRot;
				return;
			}
		}
	}


	FunctionPointer(void, original, (EntityData1 * PlayerPos), MovePlayerToStartPoint_T.Target());
	return original(data);
}




/*StringLevelLayout SetCamFileArray[51]{

	{ LevelIDs_EmeraldCoast, GammaVersion,  "ECG", {"C0104", "C0101", "C0102", nullptr}},
	{ LevelIDs_EmeraldCoast, SonicVersion,  "EC", {"C0100", "C0101", "C0102", nullptr}},
	{ LevelIDs_WindyValley, GammaVersion,  "WVG", {"C0203", "C0201", "C0202", nullptr} },
	{ LevelIDs_WindyValley, SonicVersion,  "WV", {"C0200", "C0201", "C0202", nullptr}},
	{ LevelIDs_WindyValley, TailsVersion,  "WVM", {"C0200", "C0201", "C0206", nullptr} },
	{ LevelIDs_TwinklePark, SonicVersion,  "TP", {"C0300", "C0301", "C0302", nullptr}},
	{ LevelIDs_SpeedHighway, SonicVersion,  "SH", {"C0400", "C0401", "C0402", nullptr}},
	{ LevelIDs_SpeedHighway, TailsVersion,  "SHM", {"C0403", "C0401", "C0402", nullptr}},
	{ LevelIDs_SpeedHighway, KnucklesVersion, "SHK", {"C0400", "C0401", "C0404", nullptr}},
	{ LevelIDs_RedMountain, SonicVersion, "RM", {"C0500", "C0501", "C0502", nullptr}},
	{ LevelIDs_RedMountain, GammaVersion, "RMG", {"C0500", "C0503", "C0502", nullptr}},
	{ LevelIDs_SkyDeck, SonicVersion, "SD", {"C0600", "C0601", "C0602", nullptr}},
	{ LevelIDs_SkyDeck, TailsVersion, "SDM", {"C0603", "C0601", "C0602", nullptr}},
	{ LevelIDs_SkyDeck, KnucklesVersion, "SDK", {"C0600", "C0601", "C0604", nullptr}},
	{ LevelIDs_LostWorld, SonicVersion, "LW", {"C0700", "C0701", "C0702", nullptr}},
	{ LevelIDs_LostWorld, KnucklesVersion, "LWK", {"C0700", "C0703", "C0702", nullptr}},
	{ LevelIDs_IceCap, SonicVersion, "IC", {"C0800", "C0801", "C0802", "C0803"}},
	{ LevelIDs_Casinopolis, SonicVersion, "CAS", {"C0900", "C0901", "C0902", "C0903"}},
	{ LevelIDs_Casinopolis, KnucklesVersion, "CASK", {"C0904", "C0901", "C0902", "C0903"}},
	{ LevelIDs_Casinopolis, TailsVersion, "CASM", {"C0900", "C0905", "C0902", "C0903"}},
	{ LevelIDs_FinalEgg, AmyVersion, "FEA", {"C1003", "C1001", "C1002", nullptr}},
	{ LevelIDs_FinalEgg, SonicVersion, "FE", {"C1000", "C1001", "C1002", nullptr}},
	{ LevelIDs_FinalEgg, GammaVersion, "FEG", { "C1000", "C1001", "C1004", nullptr}},
	{ LevelIDs_HotShelter, BigVersion, "HSB", {"C1203", "C1001", "C1002", nullptr}},
	{ LevelIDs_HotShelter, AmyVersion, "HSA", {"C1200", "C1201", "C1202", nullptr}},
};*/

StringLevelLayout SetCamFileArray[51]{

	{ LevelIDs_HedgehogHammer, AmyVersion, 0, "HH", "C0000"},
	{ LevelIDs_EmeraldCoast, GammaVersion, 0, "ECG", "C0103" },
	{ LevelIDs_EmeraldCoast, SonicVersion, 0, "EC0", "C0100", },
	{ LevelIDs_EmeraldCoast, SonicVersion, 1, "EC1", "C0101", },
	{ LevelIDs_EmeraldCoast, BigVersion, 2, "EC2", "C0112", },
	{ LevelIDs_WindyValley, GammaVersion, 0, "WVG", "C0203"},
	{ LevelIDs_WindyValley, SonicVersion, 0, "WV0", "C0200"},
	{ LevelIDs_WindyValley, SonicVersion, 1, "WV1", "C0201"},
	{ LevelIDs_WindyValley, SonicVersion, 2, "WV2", "C0202"},
	{ LevelIDs_WindyValley, TailsVersion, 2, "WVM", "C0204"},
	{ LevelIDs_TwinklePark, SonicVersion, 0, "TP0", "C0300"},
	{ LevelIDs_TwinklePark, SonicVersion, 1, "TP1", "C0301"},
	{ LevelIDs_TwinklePark, AmyVersion,	1, "TPA", "C0303"},
	{ LevelIDs_TwinklePark, BigVersion,	1, "TPB", "0304"},
	{ LevelIDs_TwinklePark, AmyVersion,	2, "TP2", "0302"},
	{ LevelIDs_SpeedHighway, SonicVersion, 0, "0410"},
	{ LevelIDs_SpeedHighway, TailsVersion, 0, "0413"},
	{ LevelIDs_SpeedHighway, SonicVersion, 1, "0411"},
	{ LevelIDs_SpeedHighway, SonicVersion, 2, "0412",},
	{ LevelIDs_SpeedHighway, KnucklesVersion, 2, "0414",},
	{ LevelIDs_RedMountain, SonicVersion, 0, "0510",},
	{ LevelIDs_RedMountain, SonicVersion, 1, "0511",},
	{ LevelIDs_RedMountain, GammaVersion, 1, "0513",},
	{ LevelIDs_RedMountain, KnucklesVersion, 2, "0512", },
	{ LevelIDs_SkyDeck, SonicVersion, 0, "0610", },
	{ LevelIDs_SkyDeck, TailsVersion, 0, "0613",  },
	{ LevelIDs_SkyDeck, SonicVersion, 1, "0611",  },
	{ LevelIDs_SkyDeck, SonicVersion, 2, "0612",  },
	{ LevelIDs_SkyDeck, KnucklesVersion, 2, "0614", },
	{ LevelIDs_LostWorld, SonicVersion, 0, "0710", },
	{ LevelIDs_LostWorld, SonicVersion, 1, "0711", },
	{ LevelIDs_LostWorld, KnucklesVersion, 1, "0713", },
	{ LevelIDs_LostWorld, SonicVersion, 2, "0712",  },
	{ LevelIDs_IceCap, SonicVersion, 0, "0810",  },
	{ LevelIDs_IceCap, SonicVersion, 1,	"0811",   },
	{ LevelIDs_IceCap, SonicVersion, 2,	"0812",  },
	{ LevelIDs_IceCap, TailsVersion, 2,	"0814"},
	{ LevelIDs_IceCap, BigVersion, 3, "0813",},
	{ LevelIDs_Casinopolis, SonicVersion, 0, "0910"},
	{ LevelIDs_Casinopolis, KnucklesVersion, 0, "0913"},
	{ LevelIDs_Casinopolis, SonicVersion, 1, "0911" },
	{ LevelIDs_Casinopolis, TailsVersion, 1, "0912"},
	{ LevelIDs_FinalEgg, AmyVersion, 0, "1013", "-FE-Amy"},
	{ LevelIDs_FinalEgg, SonicVersion, 0, "1010"},
	{ LevelIDs_FinalEgg, SonicVersion, 1, "1011"},
	{ LevelIDs_FinalEgg, SonicVersion, 2, "1012"},
	{ LevelIDs_FinalEgg, GammaVersion, 2, "1014"},
	{ LevelIDs_HotShelter, BigVersion, 0, "1213"},
	{ LevelIDs_HotShelter, AmyVersion, 0, "1210"},
	{ LevelIDs_HotShelter, AmyVersion, 1, "1211"},
	{ LevelIDs_HotShelter, GammaVersion, 2, "1212"},
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

	
}


void __cdecl LoadLevelFiles_r(unsigned int curLevel) {

	ResetValueAndObjects(); //Unload rando stuff
	Load_ObjectsCommon();
	
	if (!isHeroesMod() && !isSA2Mod() && isRandoLevel())
	{
		ReleaseSetFile();
		ReleaseCamFile();
		RandoLoad_SetCamFiles();
	} 

	SetCurrentCamData(curLevel);
	SetCurrentSetData(curLevel);
}


void AddLevelLayout(std::string FolderName, std::string LevelName, const HelperFunctions& helperFunctions) {
	for (int i = 0; i < 8; i++) {
		std::string path = "system\\";
		std::string path2 = "system\\sets\\" + FolderName;
		std::string bin = LevelName + ".bin";
		std::string lvl = path + CharIDStrings[i] + bin;
		std::string lvl2 = path2 + CharIDStrings[i] + bin;
		helperFunctions.ReplaceFile(lvl.c_str(), lvl2.c_str());
	}
}


void LayoutFunctionInit() {
	WriteData<5>((void*)0x4237b4, 0x90); //remove "SetCurrentCamData" from LoadLevelFiles, we will manually call it later.
	WriteCall((void*)0x4237ba, LoadLevelFiles_r);
}