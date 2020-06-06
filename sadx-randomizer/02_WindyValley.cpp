#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"

#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Windy Valley\\" B ".bin")
#define ReplaceCAM(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")

void Cam_WV() {

	if (CurrentStageVersion != GammaVersion)
		LoadCamFile(0, "0200");
	else
		LoadCamFile(0, "0203");

	LoadCamFile(1, "0201");

	if (Race && CurrentAct == 2)
		LoadCamFile(2, "0206");
	else
		LoadCamFile(2, "0202");

	return;
}

void FixTailsVictoryWV() {

	//Prevent AI to make Tails lose when hiting the capsule if we aren't racing.

	if (CurrentCharacter == Characters_Tails && !Race)
		SetTailsRaceVictory();
	else
		SetOpponentRaceVictory();

	return;
}



void WindyValley_Layout() {


	switch (CurrentStageVersion)
	{
	case SonicVersion:
	default:
		CurrentStageVersion = SonicVersion;
		break;
	case TailsVersion:
		if (CurrentMission < Mission2_100Rings)
			Race = true;
		break;
	}

	if (CurrentAct == 2)
		CurrentStageVersion = TailsVersion;

	Load_ObjectsCommon();
	LoadSetAndCamLayout();

	if (Race)
		SelectBarRace();

	return;
}


void __cdecl WindyValley_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	
	WVObjects_Init(path, helperFunctions);
	WriteCall((void*)0x422c27, WindyValley_Layout); //WV
	WriteCall((void*)0x4df390, FixTailsVictoryWV);
	WriteData<72>((int*)0x422bdf, 0x90);

	//Sonic
	ReplaceSET("SET0210S", "Sonic-WV-Act1");
	ReplaceSET("SET0211S", "Sonic-WV-Act2");
	ReplaceSET("SET0212S", "Sonic-WV-Act3");
	ReplaceSET("SET0213S", "Sonic-WV-Race");
	ReplaceSET("SET0214S", "Sonic-WV-E102");

	ReplaceCAM("CAM0200S", "CAM0200S");
	ReplaceCAM("CAM0201S", "CAM0201S");
	ReplaceCAM("CAM0202S", "CAM0202S");
	ReplaceCAM("CAM0203S", "CAM0203S");
	ReplaceCAM("CAM0206S", "CAM0206S");

	//Tails
	ReplaceSET("SET0210M", "Tails-WV-Act1");
	ReplaceSET("SET0211M", "Tails-WV-Act2");
	ReplaceSET("SET0212M", "Tails-WV-Act3");
	ReplaceSET("SET0213M", "Tails-WV-Race");
	ReplaceSET("SET0214M", "Tails-WV-E102");

	ReplaceCAM("CAM0200M", "CAM0200M");
	ReplaceCAM("CAM0201M", "CAM0201M");
	ReplaceCAM("CAM0202M", "CAM0202M");
	ReplaceCAM("CAM0203M", "CAM0203M");
	ReplaceCAM("CAM0206M", "CAM0206M");

	//Knuckles								
	ReplaceSET("SET0210K", "Knux-WV-Act1");
	ReplaceSET("SET0211K", "Knux-WV-Act2");
	ReplaceSET("SET0212K", "Knux-WV-Act3");
	ReplaceSET("SET0213K", "Knux-WV-E102");
	ReplaceSET("SET0214K", "Knux-WV-Race");
										
	ReplaceCAM("CAM0200K", "CAM0200K");
	ReplaceCAM("CAM0201K", "CAM0201K");
	ReplaceCAM("CAM0202K", "CAM0202K");
	ReplaceCAM("CAM0203K", "CAM0203K");
	ReplaceCAM("CAM0206K", "CAM0206K");


	//Amy
	ReplaceSET("SET0210A", "Amy-WV-Act1");
	ReplaceSET("SET0211A", "Amy-WV-Act2");
	ReplaceSET("SET0212A", "Amy-WV-Act3");
	ReplaceSET("SET0213A", "Amy-WV-E102");
	ReplaceSET("SET0214A", "Amy-WV-Race");

	ReplaceCAM("CAM0200A", "CAM0200A");
	ReplaceCAM("CAM0201A", "CAM0201A");
	ReplaceCAM("CAM0202A", "CAM0202A");
	ReplaceCAM("CAM0203A", "CAM0203A");
	ReplaceCAM("CAM0206A", "CAM0206A");

	//Big
	ReplaceSET("SET0210B", "Big-WV-Act1");
	ReplaceSET("SET0211B", "Big-WV-Act2");
	ReplaceSET("SET0212B", "Big-WV-Act3");
	ReplaceSET("SET0213B", "Big-WV-E102");
	ReplaceSET("SET0214B", "Big-WV-Race");

	ReplaceCAM("CAM0200B", "CAM0200B");
	ReplaceCAM("CAM0201B", "CAM0201B");
	ReplaceCAM("CAM0202B", "CAM0202B");
	ReplaceCAM("CAM0203B", "CAM0203B");
	ReplaceCAM("CAM0206B", "CAM0206B");

	//Gamma
	ReplaceSET("SET0210E", "Gamma-WV-Act1");
	ReplaceSET("SET0211E", "Gamma-WV-Act2");
	ReplaceSET("SET0212E", "Gamma-WV-Act3");
	ReplaceSET("SET0213E", "Gamma-WV-E102");
	ReplaceSET("SET0214E", "Gamma-WV-Race");

	ReplaceCAM("CAM0200E", "CAM0200E");
	ReplaceCAM("CAM0201E", "CAM0201E");
	ReplaceCAM("CAM0202E", "CAM0202E");
	ReplaceCAM("CAM0203E", "CAM0203E");
	ReplaceCAM("CAM0206E", "CAM0206E");
}

ObjectListEntry WindyValleyObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79B2F0, "O_GRING" } /* "O_GRING" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4CBDE0, "O DYNAMITE" } /* "O DYNAMITE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A1380, "E SAITO" } /* "E SAITO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A0330, "E HEVY " } /* "E HEVY " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4A85C0, "E LEON " } /* "E LEON " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E7F50, "E E-103" } /* "E E-103" */,
	{ 2, 4, 1, 2250000, 0, (ObjectFuncPtr)0x4E6770, "O TORBRI" } /* "O TORBRI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4DE2F0, "O_SETSMO" } /* "O_SETSMO" */,
	{ 2, 4, 1, 1000000, 0, (ObjectFuncPtr)0x4E5920, "O_VCROK" } /* "O_VCROK" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E1B50, "O_CUBES" } /* "O_CUBES" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E1B90, "O_CUBEM" } /* "O_CUBEM" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E1BD0, "O_CUBEL" } /* "O_CUBEL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4E1C10, "O_UKISIM" } /* "O_UKISIM" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4DFF30, "O_TANPOPO" } /* "O_TANPOPO" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4E5510, "B LEAF " } /* "B LEAF " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4E3C50, "WC WIND" } /* "WC WIND" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4E4C10, "PU WIND" } /* "PU WIND" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x4E0760, "O TURI1" } /* "O TURI1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E33D0, "O YURE" } /* "O YURE" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4E1C50, "O BIGFLA" } /* "O BIGFLA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E0310, "O POPO" } /* "O POPO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E3200, "O POLINE" } /* "O POLINE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E2C40, "O SAKUA" } /* "O SAKUA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E2C80, "O SAKUB" } /* "O SAKUB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E2BC0, "O TREEM" } /* "O TREEM" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E1460, "O SAKUC" } /* "O SAKUC" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E13E0, "O HASIE" } /* "O HASIE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E2AB0, "O BROOBJ" } /* "O BROOBJ" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x4E0F40, "O TURIBR" } /* "O TURIBR" */,
	{ 7, 3, 1, 422500, 0, (ObjectFuncPtr)0x4E0F80, "O TURIBR2" } /* "O TURIBR2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E2880, "O BROCU" } /* "O BROCU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E2040, "O ISHIA" } /* "O ISHIA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E2080, "O ISHIB" } /* "O ISHIB" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4DFEF0, "O HANAA" } /* "O HANAA" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4DFF10, "O HANAB" } /* "O HANAB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E1FA0, "O GATE" } /* "O GATE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E1D80, "O GRASS" } /* "O GRASS" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E1CB0, "O TATES" } /* "O TATES" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E1C70, "O TATEL" } /* "O TATEL" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4E14A0, "O HANEA" } /* "O HANEA" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4E14E0, "O HANEB" } /* "O HANEB" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4E0FC0, "O E102BR" } /* "O E102BR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4E19D0, "O KAZAMI" } /* "O KAZAMI" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x4E16C0, "O BALL" } /* "O BALL" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x4E1520, "O BIGFLO" } /* "O BIGFLO" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4E0A40, "O STBRID" } /* "O STBRID" */,
	{ 11, 3, 0, 0, 0, (ObjectFuncPtr)0x4E0690, "O WASI" } /* "O WASI" */,
	{ 2, 3, 1, 1102500, 0, (ObjectFuncPtr)0x4DE8E0, "O TOROUT" } /* "O TOROUT" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4DFF10, "O GRFLOWERA" } /* "O GRFLOWERA" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4DFF10, "O GRFLOWERB" } /* "O GRFLOWERB" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4DF7D0, "O SETIFF" } /* "O SETIFF" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4DF3B0, "O KAOSE" } /* "O KAOSE" */,
	{ 15, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ItemBoxAir" } /* "O ItemBoxAir" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79F860, "O SPRING H" } /* "O SPRING H" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" }, /* "O FROG" */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};

PVMEntry WindyValleyObjectTextures[] = {
	{ "OBJ_WINDY", (TexList*)0xC055D4 },
	{ "WINDY_E103", (TexList*)0xC409A4 },
	{ "E_SAI", (TexList*)0x38C8EA8 },
	{ "E_LEON", (TexList*)0x9599F4 },
	{ "OUM", (TexList*)0x9334EC },
	{ "KUJA", (TexList*)0x93142C },
	{ "MILESRACE", (TexList*)0x91BFC0 },
	{ "MOUNTAIN_MEXPLOSION", (TexList*)0xC3FEB0 },
	{ "TUBA", (TexList*)0x92F2BC },
	{ "E_SNAKE", (TexList*)0x94E640 },
	{ "MOGU", (TexList*)0x93ECEC },
	{ "KAOS_EME", (TexList*)0xC3FE20 },
	{ "GOMA", (TexList*)0x92ACE4 },
	{ "CHAOS_LIFEGAUGE", (TexList*)0x974000 },
	{ NULL, (TexList*)0x973FB0 },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "common-obj", &SA2_OBJ_TEXLIST },
	{ 0 }
};

ObjectList WindyValleyObjectList = { arraylengthandptrT(WindyValleyObjectList_list, int) };


void __cdecl WVObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_WindyValley * 8 + 0] = &WindyValleyObjectList;
	ObjLists[LevelIDs_WindyValley * 8 + 2] = &WindyValleyObjectList;
	TexLists_Obj[LevelIDs_WindyValley] = WindyValleyObjectTextures;
}