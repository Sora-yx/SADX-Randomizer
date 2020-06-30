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

SetLevelPosition PlayerStartPosition[52]{ //Casino pos are hardcoded

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

StringSetFile SetFileArray[51]{

	{ LevelIDs_HedgehogHammer, AmyVersion, 0, "0000", "-HH" "0000" },
	{ LevelIDs_EmeraldCoast, GammaVersion, 0, "0113", "ECG", "0104"},
	{ LevelIDs_EmeraldCoast, SonicVersion, 0, "0110", "EC01", "0100"},
	{ LevelIDs_EmeraldCoast, SonicVersion, 1, "0111", "EC02", "0101"},
	{ LevelIDs_EmeraldCoast, BigVersion, 2, "0112", "EC03", "0102"},
	{ LevelIDs_WindyValley, GammaVersion, 0, "0214", "-WV-E102", "0203"},
	{ LevelIDs_WindyValley, SonicVersion, 0, "0210", "-WV-Act1", "0200"},
	{ LevelIDs_WindyValley, SonicVersion, 1, "0211", "-WV-Act2", "0201"},
	{ LevelIDs_WindyValley, SonicVersion, 2, "0212", "-WV-Act3", "0202"},
	{ LevelIDs_WindyValley, TailsVersion, 2, "0213", "-WV-Race", "0206"},
	{ LevelIDs_TwinklePark, SonicVersion, 0, "0310", "-TP-Act1", "0300"},
	{ LevelIDs_TwinklePark, SonicVersion, 1, "0311", "-TP-Act2", "0301"},
	{ LevelIDs_TwinklePark, AmyVersion,	1, "0313", "-TP-Amy",  "0301"},
	{ LevelIDs_TwinklePark, BigVersion,	1, "0314", "-TP-Big",  "0301"},
	{ LevelIDs_TwinklePark, AmyVersion,	2, "0312", "-TP-Act3", "0305"},
	{ LevelIDs_SpeedHighway, SonicVersion, 0, "0410", "-SH-Act1", "0400" },
	{ LevelIDs_SpeedHighway, TailsVersion, 0, "0413", "-SH-Race", "0403"},
	{ LevelIDs_SpeedHighway, SonicVersion, 1, "0411", "-SH-Act2", "0401"},
	{ LevelIDs_SpeedHighway, SonicVersion, 2, "0412", "-SH-Act3", "0402"},
	{ LevelIDs_SpeedHighway, KnucklesVersion, 2, "0414", "-SH-Knux2", "0405"},
	{ LevelIDs_RedMountain, SonicVersion, 0, "0510", "-RM-Act1", "0500" },
	{ LevelIDs_RedMountain, SonicVersion, 1, "0511", "-RM-Act2", "0501"},
	{ LevelIDs_RedMountain, GammaVersion, 1, "0513", "-RM-E102", "0503"},
	{ LevelIDs_RedMountain, KnucklesVersion, 2, "0512", "-RM-Act3", "0502"},
	{ LevelIDs_SkyDeck, SonicVersion, 0, "0610", "-SD-Act1", "0600"},
	{ LevelIDs_SkyDeck, TailsVersion, 0, "0613", "-SD-Race", "0603" },
	{ LevelIDs_SkyDeck, SonicVersion, 1, "0611", "-SD-Act2", "0601"},
	{ LevelIDs_SkyDeck, SonicVersion, 2, "0612", "-SD-Act3", "0602"},
	{ LevelIDs_SkyDeck, KnucklesVersion, 2, "0614", "-SD-Knux", "0604"},
	{ LevelIDs_LostWorld, SonicVersion, 0, "0710", "-LW-Act1", "0700"},
	{ LevelIDs_LostWorld, SonicVersion, 1, "0711", "-LW-Act2", "0701"},
	{ LevelIDs_LostWorld, KnucklesVersion, 1, "0713", "-LW-Knux", "0704"},
	{ LevelIDs_LostWorld, SonicVersion, 2, "0712", "-LW-Act3", "0702"},
	{ LevelIDs_IceCap, SonicVersion, 0, "0810", "-IC-Act1", "0800" },
	{ LevelIDs_IceCap, SonicVersion, 1,	"0811", "-IC-Act2", "0801" },
	{ LevelIDs_IceCap, SonicVersion, 2,	"0812", "-IC-Act3", "0802" },
	{ LevelIDs_IceCap, TailsVersion, 2,	"0814", "-IC-T", "0802"},
	{ LevelIDs_IceCap, BigVersion, 3, "0813", "-IC-Big", "0803"},
	{ LevelIDs_Casinopolis, SonicVersion, 0, "0910", "-Casino-Act1", "0900"},
	{ LevelIDs_Casinopolis, KnucklesVersion, 0, "0913", "-Casino-Knux", "0906"},
	{ LevelIDs_Casinopolis, SonicVersion, 1, "0911", "-Casino-Act2", "0901"},
	{ LevelIDs_Casinopolis, TailsVersion, 1, "0912", "-Casino-T", "0907"},
	{ LevelIDs_FinalEgg, AmyVersion, 0, "1013", "-FE-Amy", "1004"},
	{ LevelIDs_FinalEgg, SonicVersion, 0, "1010", "-FE-Act1", "1000"},
	{ LevelIDs_FinalEgg, SonicVersion, 1, "1011", "-FE-Act2", "1001"},
	{ LevelIDs_FinalEgg, SonicVersion, 2, "1012", "-FE-Act3", "1002"},
	{ LevelIDs_FinalEgg, GammaVersion, 2, "1014", "-FE-Gamma", "1005"},
	{ LevelIDs_HotShelter, BigVersion, 0, "1213", "-HS-Act4", "1204"},
	{ LevelIDs_HotShelter, AmyVersion, 0, "1210", "-HS-Act1", "1200"},
	{ LevelIDs_HotShelter, AmyVersion, 1, "1211", "-HS-Act2", "1201"},
	{ LevelIDs_HotShelter, GammaVersion, 2, "1212", "-HS-Act3", "1202"},
};


void LoadRando_SetAndCamLayout() {

	for (uint8_t i = 0; i < LengthOfArray(SetFileArray); i++) {

		if (CurrentLevel == SetFileArray[i].LevelID && CurrentStageVersion == SetFileArray[i].version)
		{
			string Set = SetFileArray[i].SetFile;
			string Cam = SetFileArray[i].SetCam;
			int act = SetFileArray[i].act;
			LoadSetFile(act, Set.c_str());
			LoadCamFile(act, Cam.c_str());
		}
	}

	return;
}


static void LoadLevelFiles_r();
static Trampoline LoadLevelFiles_t((int)LoadLevelFiles, (int)LoadLevelFiles + 0x8, LoadLevelFiles_r);


void __cdecl LoadLevelFiles_r() {

	ResetValueAndObjects(); //Unload rando stuff
	Load_ObjectsCommon();
	
	auto original = reinterpret_cast<decltype(LoadLevelFiles_r)*>(LoadLevelFiles_t.Target());
	original();
}