#include "stdafx.h"
#include "Utils.h"
#include "WindyValley.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"

void Cam_WV() {

	if (Mission1_Variation)
	{
		if (CurrentCharacter == Characters_Gamma && !Vanilla)
			LoadCamFile(0, "0200");
		else
			LoadCamFile(0, "0203");
	}
	else
	{
		LoadCamFile(0, "0100");
	}

	
	LoadCamFile(1, "0201");

	if (CurrentAct == 2 && Race)
		LoadCamFile(2, "0206");
	else
		LoadCamFile(2, "0202");

	return;

}

void WindyValley_Layout() {

	CurrentLevelLayout = randomizedSets[levelCount].LevelLayout;

	if (CurrentAct != 2)
	{
		switch (CurrentLevelLayout)
		{
		case Mission1:
		default:
			if (CurrentCharacter == Characters_Sonic && !Vanilla)
			{
				LoadSetFile(0, "0203"); //Gamma Version
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0202");
				CurrentLevelLayout = Mission1_Variation;
			}
			else
			{
				LoadSetFile(0, "0200"); //Sonic Version
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0202");
			}
			break;
		case Mission1_Variation:
			if (CurrentCharacter == Characters_Gamma && !Vanilla)
			{
				LoadSetFile(0, "0200");  //Sonic Version
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0202");
				CurrentLevelLayout = Mission1;
			}
			else
			{
				LoadSetFile(0, "0203"); //Gamma Version
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0202");
			}
			break;
		case 2:
			if (CurrentCharacter == Characters_Sonic && !Vanilla)
			{
				LoadSetFile(0, "0203"); //Gamma Version
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0202");
				CurrentLevelLayout = Mission1_Variation;
			}
			else
			{
				LoadSetFile(0, "0200"); //100 Rings
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0202");
			}
			break;
		case 3:
			if (CurrentCharacter == Characters_Sonic && !Vanilla)
			{
				LoadSetFile(0, "0203"); //Gamma Version
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0202");
				CurrentLevelLayout = Mission1_Variation;
			}
			else
			{
				LoadSetFile(0, "0200");
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0205"); //Lost Chao
			}
			break;
		}
	}
	
		if (CurrentAct == 2)
		{
			if (CurrentCharacter != Characters_Tails && CurrentCharacter != Characters_Big)
			{
				Race = true;
				LoadSetFile(0, "0200");
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0206"); //race
				CurrentLevelLayout = Mission1_Variation;
			}
			else
			{
				Race = false;
				LoadSetFile(0, "0200"); //Sonic Version
				LoadSetFile(1, "0201");
				LoadSetFile(2, "0202");
				CurrentLevelLayout = Mission1;
			}
		}

	if (Race)
		SelectBarRace();

	Cam_WV();

	return;
}

void __cdecl WindyValley_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WVObjects_Init(path, helperFunctions);

	WriteData<5>((void*)0x422bdf, 0x90);
	WriteData<5>((void*)0x422bee, 0x90);
	WriteData<5>((void*)0x422bfd, 0x90);
	WriteData<5>((void*)0x422c09, 0x90);
	WriteData<5>((void*)0x422c18, 0x90);

	WriteCall((void*)0x422c27, WindyValley_Layout); //WV

	//Sonic
	helperFunctions.ReplaceFile("system\\SET0200S.BIN", "system\\levels\\Windy Valley\\Sonic-WV-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0201S.BIN", "system\\levels\\Windy Valley\\Sonic-WV-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0202S.BIN", "system\\levels\\Windy Valley\\Sonic-WV-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0203S.BIN", "system\\levels\\Windy Valley\\Sonic-WV-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0205S.BIN", "system\\levels\\Windy Valley\\Sonic-WV-Chao.bin"); //Chao
	helperFunctions.ReplaceFile("system\\SET0206S.BIN", "system\\levels\\Windy Valley\\Sonic-WV-Race.bin"); //MS Race

	helperFunctions.ReplaceFile("system\\CAM0200S.BIN", "system\\cam\\CAM0200S.bin");
	helperFunctions.ReplaceFile("system\\CAM0201S.BIN", "system\\cam\\CAM0201S.bin");
	helperFunctions.ReplaceFile("system\\CAM0202S.BIN", "system\\cam\\CAM0202S.bin");
	helperFunctions.ReplaceFile("system\\CAM0203S.BIN", "system\\cam\\CAM0203S.bin");
	helperFunctions.ReplaceFile("system\\CAM0206S.BIN", "system\\cam\\CAM0206S.bin");

	if (!Vanilla)
		helperFunctions.RegisterStartPosition(Characters_Sonic, WV1_StartPositions[0]);
	else
		helperFunctions.RegisterStartPosition(Characters_Sonic, WV1S_StartPositions[0]);

	helperFunctions.RegisterStartPosition(Characters_Sonic, WV2S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, WV3S_StartPositions[0]);

	//Tails
	helperFunctions.ReplaceFile("system\\SET0200M.BIN", "system\\levels\\Windy Valley\\Tails-WV-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0201M.BIN", "system\\levels\\Windy Valley\\Tails-WV-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0202M.BIN", "system\\levels\\Windy Valley\\Tails-WV-Act3.bin");

	helperFunctions.ReplaceFile("system\\SET0203M.BIN", "system\\levels\\Windy Valley\\Tails-WV-E102.bin");
	helperFunctions.ReplaceFile("system\\SET0205M.BIN", "system\\levels\\Windy Valley\\Sonic-WV-Chao.bin"); //Chao

	helperFunctions.ReplaceFile("system\\CAM0200M.BIN", "system\\cam\\CAM0200M.bin");
	helperFunctions.ReplaceFile("system\\CAM0201M.BIN", "system\\cam\\CAM0201M.bin");
	helperFunctions.ReplaceFile("system\\CAM0202M.BIN", "system\\cam\\CAM0202M.bin");
	helperFunctions.ReplaceFile("system\\CAM0203M.BIN", "system\\cam\\CAM0203M.bin");
	helperFunctions.ReplaceFile("system\\CAM0206M.BIN", "system\\cam\\CAM0206M.bin");
	helperFunctions.RegisterStartPosition(Characters_Tails, WV1S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, WV2S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, WV3S_StartPositions[0]);

	//Knuckles
	helperFunctions.ReplaceFile("system\\SET0200K.BIN", "system\\levels\\Windy Valley\\Knux-WV-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0201K.BIN", "system\\levels\\Windy Valley\\Knux-WV-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0202K.BIN", "system\\levels\\Windy Valley\\Knux-WV-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0203K.BIN", "system\\levels\\Windy Valley\\Knux-WV-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0205K.BIN", "system\\levels\\Windy Valley\\Sonic-WV-Chao.bin"); //Chao
	helperFunctions.ReplaceFile("system\\SET0206K.BIN", "system\\levels\\Windy Valley\\Knux-WV-Race.bin"); //race

	helperFunctions.ReplaceFile("system\\CAM0200K.BIN", "system\\cam\\CAM0200K.bin");
	helperFunctions.ReplaceFile("system\\CAM0201K.BIN", "system\\cam\\CAM0201K.bin");
	helperFunctions.ReplaceFile("system\\CAM0202K.BIN", "system\\cam\\CAM0202K.bin");
	helperFunctions.ReplaceFile("system\\CAM0203K.BIN", "system\\cam\\CAM0203K.bin");
	helperFunctions.ReplaceFile("system\\CAM0206K.BIN", "system\\cam\\CAM0206K.bin");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, WV1S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, WV2S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, WV3S_StartPositions[0]);

	//Amy
	helperFunctions.ReplaceFile("system\\SET0200A.BIN", "system\\levels\\Windy Valley\\Amy-WV-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0201A.BIN", "system\\levels\\Windy Valley\\Amy-WV-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0202A.BIN", "system\\levels\\Windy Valley\\Amy-WV-Act3.bin");

	helperFunctions.ReplaceFile("system\\SET0203A.BIN", "system\\levels\\Windy Valley\\Amy-WV-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0205A.BIN", "system\\levels\\Windy Valley\\Amy-WV-Chao.bin"); //Chao
	helperFunctions.ReplaceFile("system\\SET0206A.BIN", "system\\levels\\Windy Valley\\Amy-WV-Race.bin");

	helperFunctions.ReplaceFile("system\\CAM0200A.BIN", "system\\cam\\CAM0200A.bin");
	helperFunctions.ReplaceFile("system\\CAM0201A.BIN", "system\\cam\\CAM0201A.bin");
	helperFunctions.ReplaceFile("system\\CAM0202A.BIN", "system\\cam\\CAM0202A.bin");
	helperFunctions.ReplaceFile("system\\CAM0203A.BIN", "system\\cam\\CAM0203A.bin");
	helperFunctions.ReplaceFile("system\\CAM0206A.BIN", "system\\cam\\CAM0206A.bin");
	helperFunctions.RegisterStartPosition(Characters_Amy, WV1S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, WV2S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, WV3S_StartPositions[0]);

	//Big
	helperFunctions.ReplaceFile("system\\SET0200B.BIN", "system\\levels\\Windy Valley\\Big-WV-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0201B.BIN", "system\\levels\\Windy Valley\\Big-WV-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0202B.BIN", "system\\levels\\Windy Valley\\Big-WV-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0203B.BIN", "system\\levels\\Windy Valley\\Big-WV-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0205B.BIN", "system\\levels\\Windy Valley\\Big-WV-Chao.bin"); //Chao

	helperFunctions.ReplaceFile("system\\CAM0200B.BIN", "system\\cam\\CAM0200B.bin");
	helperFunctions.ReplaceFile("system\\CAM0201B.BIN", "system\\cam\\CAM0201B.bin");
	helperFunctions.ReplaceFile("system\\CAM0202B.BIN", "system\\cam\\CAM0202B.bin");
	helperFunctions.ReplaceFile("system\\CAM0203B.BIN", "system\\cam\\CAM0203B.bin");
	helperFunctions.ReplaceFile("system\\CAM0206B.BIN", "system\\cam\\CAM0206B.bin");
	helperFunctions.RegisterStartPosition(Characters_Big, WV1S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, WV2S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, WV3S_StartPositions[0]);

	//Gamma
	helperFunctions.ReplaceFile("system\\SET0200E.BIN", "system\\levels\\Windy Valley\\Gamma-WV-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0201E.BIN", "system\\levels\\Windy Valley\\Gamma-WV-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0202E.BIN", "system\\levels\\Windy Valley\\Gamma-WV-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0203E.BIN", "system\\levels\\Windy Valley\\Gamma-WV-E102.bin");

	helperFunctions.ReplaceFile("system\\SET0205E.BIN", "system\\levels\\Windy Valley\\Gamma-WV-Chao.bin"); //Chao
	helperFunctions.ReplaceFile("system\\SET0206E.BIN", "system\\levels\\Windy Valley\\Gamma-WV-Race.bin");

	helperFunctions.ReplaceFile("system\\CAM0200E.BIN", "system\\cam\\CAM0200E.bin");
	helperFunctions.ReplaceFile("system\\CAM0201E.BIN", "system\\cam\\CAM0201E.bin");
	helperFunctions.ReplaceFile("system\\CAM0202E.BIN", "system\\cam\\CAM0202E.bin");
	helperFunctions.ReplaceFile("system\\CAM0203E.BIN", "system\\cam\\CAM0203E.bin");
	helperFunctions.ReplaceFile("system\\CAM0206E.BIN", "system\\cam\\CAM0206E.bin");
	helperFunctions.RegisterStartPosition(Characters_Gamma, WV1S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, WV2S_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, WV3S_StartPositions[0]);
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
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" } /* "O FROG" */
};

ObjectList WindyValleyObjectList = { arraylengthandptrT(WindyValleyObjectList_list, int) };

void __cdecl WVObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_WindyValley * 8 + 2] = &WindyValleyObjectList;
}