#include "stdafx.h"

extern uint32_t TotalCount;
extern bool ChaoSpawn;
extern char GetCustomLayout;
extern char TimeSecCopy;
extern char TimeMinCopy;
extern char TimeFrameCopy;
extern int RingCopy;
static Trampoline* MovePlayerToStartPoint_t = nullptr;
static Trampoline* RunLevelDestructor_t = nullptr;
static Trampoline* LoadLevelObject_t = nullptr;
bool isSetLoaded = false;

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


void MovePlayerToStartPoint_r(EntityData1* data) {

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


	FunctionPointer(void, original, (EntityData1 * data), MovePlayerToStartPoint_t->Target());
	return original(data);
}

void __cdecl LoadLevelObject_r() {
	if (isRandoLevel()) {
		Load_ObjectsCommon();
		LoadTriggerObject();
	}

	auto original = reinterpret_cast<decltype(LoadLevelObject_r)*>(LoadLevelObject_t->Target());
	original();
}


StringLevelLayout SetCamFileArray[51] {

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
}


void __cdecl LoadLevelFiles_r(unsigned int curLevel) {
	
	if (isRandoLevel() && CurrentLevel > LevelIDs_HedgehogHammer && CurrentLevel < LevelIDs_Chaos0)
	{
		for (int i = 0; i < LengthOfArray(SetCamFileArray); i++) //FailSafe, if layout doesn't exist, simply let SADX load the stage (vanilla).
		{
			if (CurrentLevel == SetCamFileArray[i].LevelID && CurrentStageVersion == SetCamFileArray[i].version) 
			{
				ReleaseSetFile();
				ReleaseCamFile();
				RandoLoad_SetCamFiles();
				isSetLoaded = true;
				break;
			}
		}
	} 

	if (!isRandoLevel() || CurrentLevel == LevelIDs_HedgehogHammer || CurrentLevel >= LevelIDs_Chaos0)
		isSetLoaded = true;

	if (CurrentLevel == LevelIDs_Casinopolis)
	{
		LoadSetFile(2, "0902");
		LoadCamFile(2, "0902");
		LoadSetFile(3, "0903");
		LoadCamFile(3, "0903");
	}

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
	if (!CharObj2Ptrs[0]|| isSetLoaded || !IsIngame())
		return;

	DisplayDebugStringFormatted(NJM_LOCATION(2, 6), "WARNING: The Set file from Level %d", CurrentLevel);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 7), "and Version %d didn't load properly", CurrentStageVersion);
	DisplayDebugStringFormatted(NJM_LOCATION(2, 8), "The vanilla Layout has been loaded for safety.");
}

void __cdecl RunLevelDestructor_r(int heap) {
	if (heap == 0)
		ResetValueAndObjects(); //Unload rando stuff

	FunctionPointer(void, original, (int heap), RunLevelDestructor_t->Target());
	return original(heap);
}

void LayoutFunctionInit() {
	WriteData<5>((void*)0x4237b4, 0x90); //remove "SetCurrentCamData" from LoadLevelFiles, we will manually call it later.
	WriteCall((void*)0x4237ba, LoadLevelFiles_r);

	MovePlayerToStartPoint_t = new Trampoline((int)MovePlayerToStartPoint, (int)MovePlayerToStartPoint + 0x6, MovePlayerToStartPoint_r);
	RunLevelDestructor_t = new Trampoline((int)RunLevelDestructor, (int)RunLevelDestructor + 0x6, RunLevelDestructor_r);
	LoadLevelObject_t = new Trampoline((int)LoadLevelObject, (int)LoadLevelObject + 0x7, LoadLevelObject_r);
}

void LevelOnFrames() {
	if (!CharObj2Ptrs[0] || !IsIngame())
		return;

	AI_FixesOnFrames();
	AISwapOnFrames();
	MissionResultCheck();
	Chao_OnFrame();
	character_settings_onFrames();
	Hud_DisplayOnframe();
	PlayRandomCutscene_OnFrames();
}
