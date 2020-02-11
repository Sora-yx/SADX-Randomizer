#include "stdafx.h"
#include "Utils.h"
#include "FE.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Final Egg\\" B ".bin")
#define ReplaceCAM(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")

bool FEGammaVersion = false;

void CamFinalEgg() {
	
	if (CurrentLevelLayout == Mission1_Variation)
	{
		LoadCamFile(0, "1004"); //load the camera used for Amy Final Egg.
	}
	else
	{
		LoadCamFile(0, "1000"); //load the camera used for Sonic.
	}

	LoadCamFile(1, "1001");

	if (CurrentAct == 2 && FEGammaVersion)
	{
		LoadCamFile(2, "1005");
	}
	else
	{
		LoadCamFile(2, "1002");
	}

	LoadCamFile(3, "1003");

	return;
}

void FinalEgg_Layout() {
	
	FEGammaVersion = false;

	CurrentLevelLayout = 1;// randomizedSets[levelCount].LevelLayout;

	if (CurrentAct != 2)
	{
		switch (CurrentLevelLayout)
		{
		case Mission1:
		default:
			if (CurrentCharacter == Characters_Sonic && !Vanilla)
			{
				LoadSetFile(0, "1004"); //don't load Sonic layout.
				CurrentLevelLayout = Mission1_Variation;
			}
			else
			{
				LoadSetFile(0, "1000"); //Sonic Layout
				CurrentLevelLayout = Mission1;
			}
			break;
		case Mission1_Variation:
			if (CurrentCharacter == Characters_Amy && !Vanilla)
			{
				LoadSetFile(0, "1000"); //don't load Amy layout.
				CurrentLevelLayout = Mission1;
			}
			else
			{
				LoadSetFile(0, "1004"); //load Amy layout
			}
			break;
		case Mission2_100Rings:
		case Mission3_LostChao:
			if (CurrentCharacter == Characters_Sonic && !Vanilla)
			{
				LoadSetFile(0, "1004"); //don't load Sonic layout.
				CurrentLevelLayout = Mission1_Variation;
			}
			else
			{
				LoadSetFile(0, "1000"); //Sonic Layout
			}
			break;
		}
	}

	if (CurrentAct == 2)
	{
		FEGammaVersion = true;
		LoadSetFile(0, "1000");
		LoadSetFile(1, "1001");
		LoadSetFile(2, "1005");
	}
	else
	{
		LoadSetFile(1, "1001");
		LoadSetFile(2, "1002");
	}

	LoadSetFile(3, "1003");
	CamFinalEgg();

	return;
}

void __cdecl FinalEgg_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteData<5>((void*)0x422f7d, 0x90);
	WriteData<5>((void*)0x422f8c, 0x90);
	WriteData<5>((void*)0x422f9b, 0x90);
	WriteData<5>((void*)0x422faa, 0x90);
	WriteData<5>((void*)0x422fb6, 0x90);
	WriteData<5>((void*)0x422fc5, 0x90);
	WriteData<5>((void*)0x422fd4, 0x90);

	WriteCall((void*)0x422fe3, FinalEgg_Layout); //FE random layout

	//Sonic
	helperFunctions.ReplaceFile("system\\SET1000S.BIN", "system\\levels\\Final Egg\\Sonic-FE-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1001S.BIN", "system\\levels\\Final Egg\\Sonic-FE-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1002S.BIN", "system\\levels\\Final Egg\\Sonic-FE-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET1004S.BIN", "system\\levels\\Final Egg\\Sonic-FE-Amy.bin");
	helperFunctions.ReplaceFile("system\\SET1005S.BIN", "system\\levels\\Final Egg\\Sonic-FE-Gamma.bin");

	ReplaceCAM("CAM1000S", "CAM1000S");
	ReplaceCAM("CAM1001S", "CAM1001S");
	ReplaceCAM("CAM1002S", "CAM1002S");
	ReplaceCAM("CAM1004S", "CAM1004S");
	ReplaceCAM("CAM1005S", "CAM1005S");

	
	helperFunctions.RegisterStartPosition(Characters_Sonic, FE1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, FE2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, FE3_StartPositions[0]);

	//Tails
	helperFunctions.ReplaceFile("system\\SET1000M.BIN", "system\\levels\\Final Egg\\Tails-FE-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1001M.BIN", "system\\levels\\Final Egg\\Tails-FE-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1002M.BIN", "system\\levels\\Final Egg\\Tails-FE-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET1004M.BIN", "system\\levels\\Final Egg\\Tails-FE-Amy.bin");
	helperFunctions.ReplaceFile("system\\SET1005M.BIN", "system\\levels\\Final Egg\\Tails-FE-Gamma.bin");

	ReplaceCAM("CAM1000M", "CAM1000M");
	ReplaceCAM("CAM1001M", "CAM1001M");
	ReplaceCAM("CAM1002M", "CAM1002M");
	ReplaceCAM("CAM1004M", "CAM1004M");
	ReplaceCAM("CAM1005M", "CAM1005M");
	helperFunctions.RegisterStartPosition(Characters_Tails, FE1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, FE2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, FE3_StartPositions[0]);

	//Knuckles
	helperFunctions.ReplaceFile("system\\SET1000K.BIN", "system\\levels\\Final Egg\\Knux-FE-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1001K.BIN", "system\\levels\\Final Egg\\Knux-FE-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1002K.BIN", "system\\levels\\Final Egg\\Knux-FE-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET1004K.BIN", "system\\levels\\Final Egg\\Knux-FE-Amy.bin");
	helperFunctions.ReplaceFile("system\\SET1005K.BIN", "system\\levels\\Final Egg\\Knux-FE-Gamma.bin");

	ReplaceCAM("CAM1000K", "CAM1000K");
	ReplaceCAM("CAM1001K", "CAM1001K");
	ReplaceCAM("CAM1002K", "CAM1002K");
	ReplaceCAM("CAM1004K", "CAM1004K");
	ReplaceCAM("CAM1005K", "CAM1005K");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, FE1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, FE2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, FE3_StartPositions[0]);

	//Amy
	helperFunctions.ReplaceFile("system\\SET1000A.BIN", "system\\levels\\Final Egg\\Amy-FE-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1001A.BIN", "system\\levels\\Final Egg\\Amy-FE-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1002A.BIN", "system\\levels\\Final Egg\\Amy-FE-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET1004A.BIN", "system\\levels\\Final Egg\\Amy-FE-Amy.bin");
	helperFunctions.ReplaceFile("system\\SET1005A.BIN", "system\\levels\\Final Egg\\Amy-FE-Gamma.bin");

	ReplaceCAM("CAM1000A", "CAM1000A");
	ReplaceCAM("CAM1001A", "CAM1001A");
	ReplaceCAM("CAM1002A", "CAM1002A");
	ReplaceCAM("CAM1004A", "CAM1004A");
	ReplaceCAM("CAM1005A", "CAM1005A");
	helperFunctions.RegisterStartPosition(Characters_Amy, FE1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, FE2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, FE3_StartPositions[0]);

	//Big
	helperFunctions.ReplaceFile("system\\SET1000B.BIN", "system\\levels\\Final Egg\\Big-FE-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1001B.BIN", "system\\levels\\Final Egg\\Big-FE-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1002B.BIN", "system\\levels\\Final Egg\\Big-FE-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET1004B.BIN", "system\\levels\\Final Egg\\Big-FE-Amy.bin");
	helperFunctions.ReplaceFile("system\\SET1005B.BIN", "system\\levels\\Final Egg\\Big-FE-Gamma.bin");

	ReplaceCAM("CAM1000B", "CAM1000B");
	ReplaceCAM("CAM1001B", "CAM1001B");
	ReplaceCAM("CAM1002B", "CAM1002B");
	ReplaceCAM("CAM1004B", "CAM1004B");
	ReplaceCAM("CAM1005B", "CAM1005B");
	helperFunctions.RegisterStartPosition(Characters_Big, FE1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, FE2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, FE3_StartPositions[0]);

	//Gamma
	helperFunctions.ReplaceFile("system\\SET1000E.BIN", "system\\levels\\Final Egg\\Gamma-FE-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1001E.BIN", "system\\levels\\Final Egg\\Gamma-FE-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1002E.BIN", "system\\levels\\Final Egg\\Gamma-FE-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET1004E.BIN", "system\\levels\\Final Egg\\Gamma-FE-Amy.bin");
	helperFunctions.ReplaceFile("system\\SET1005E.BIN", "system\\levels\\Final Egg\\Gamma-FE-Gamma.bin");

	ReplaceCAM("CAM1000E", "CAM1000E");
	ReplaceCAM("CAM1001E", "CAM1001E");
	ReplaceCAM("CAM1002E", "CAM1002E");
	ReplaceCAM("CAM1004E", "CAM1004E");
	ReplaceCAM("CAM1005E", "CAM1005E");
	helperFunctions.RegisterStartPosition(Characters_Gamma, FE1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, FE2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, FE3_StartPositions[0]);
}

ObjectListEntry FinalEggObjectList_list[] = {
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
	{ 14, 3, 0, 0, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A6700, "E HIYOKO  " } /* "E HIYOKO  " */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4B0DF0, "E SPINNA A" } /* "E SPINNA A" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4B0F40, "E SPINNA B" } /* "E SPINNA B" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4B1090, "E SPINNA C" } /* "E SPINNA C" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A6700, "E ROBO " } /* "E ROBO " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5C0260, "O UP_ARM" } /* "O UP_ARM" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BF9A0, "O SIDE_ARM" } /* "O SIDE_ARM" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BEFA0, "O UP_ARM_FIX" } /* "O UP_ARM_FIX" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BED90, "O SIDE_ARM_FIX" } /* "O SIDE_ARM_FIX" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BEBA0, "O CONTAINER" } /* "O CONTAINER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BE9B0, "O SETSTEP" } /* "O SETSTEP" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BE880, "O MOVA_THORN" } /* "O MOVA_THORN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BE660, "O DSCHG_LAMP" } /* "O DSCHG_LAMP" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5BD880, "O CONV_BELT" } /* "O CONV_BELT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BD310, "O CONV_STOP" } /* "O CONV_STOP" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5BD110, "O SPIN_TUBEB" } /* "O SPIN_TUBEB" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5BCDB0, "O SPIN_TUBEM" } /* "O SPIN_TUBEM" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5BCA80, "O SPIN_TUBES" } /* "O SPIN_TUBES" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BC760, "O HAMMER" } /* "O HAMMER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BC4F0, "O ROTDOOR" } /* "O ROTDOOR" */,
	{ 2, 5, 0, 0, 0, (ObjectFuncPtr)0x5BC200, "O PURS_CAMERA" } /* "O PURS_CAMERA" */,
	{ 2, 5, 0, 0, 0, (ObjectFuncPtr)0x5BC0A0, "0 LIGHT CAMERA" } /* "0 LIGHT CAMERA" */,
	{ 2, 5, 0, 0, 0, (ObjectFuncPtr)0x5BBDC0, "0 BLUE LIGHT" } /* "0 BLUE LIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BBA40, "O GATE_A" } /* "O GATE_A" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BB5D0, "O GATE_B" } /* "O GATE_B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BB160, "O GATE_C" } /* "O GATE_C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BACF0, "O GATE_D" } /* "O GATE_D" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BA900, "O GATE_E" } /* "O GATE_E" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BA490, "O GATE_F" } /* "O GATE_F" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5BA020, "O GATE_G" } /* "O GATE_G" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B9C40, "O DOUBLE_GATE" } /* "O DOUBLE_GATE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B9730, "O ROBO WALL" } /* "O ROBO WALL" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5B8F60, "O ROBO SHUTTER" } /* "O ROBO SHUTTER" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x5B23B0, "O DRUM" } /* "O DRUM" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B85C0, "O ARM WALL" } /* "O ARM WALL" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5B03B0, "E GACHA" } /* "E GACHA" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x5B3C40, "O GACHA" } /* "O GACHA" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5AFE10, "COLLI GACHA" } /* "COLLI GACHA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B7EB0, "O Suikomi" } /* "O Suikomi" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5B7D70, "O Hakidashi" } /* "O Hakidashi" */,
	{ 6, 4, 1, 160000, 0, (ObjectFuncPtr)0x5B7BF0, "O Ukishima" } /* "O Ukishima" */,
	{ 2, 5, 0, 0, 0, (ObjectFuncPtr)0x5B78A0, "O Big Light" } /* "O Big Light" */,
	{ 2, 4, 1, 160000, 0, (ObjectFuncPtr)0x5B7600, "O Fun" } /* "O Fun" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5B66E0, "O Target" } /* "O Target" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5AE450, "O Texture" } /* "O Texture" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5B7210, "O Elevator1" } /* "O Elevator1" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5B6C20, "O Hall Gate" } /* "O Hall Gate" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B6590, "O UP TARGET1" } /* "O UP TARGET1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B5E70, "0 UP TARGET2" } /* "0 UP TARGET2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B5530, "O Pin Lamp" } /* "O Pin Lamp" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B5550, "O Side Lamp" } /* "O Side Lamp" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B5260, "O Stand Light" } /* "O Stand Light" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B5100, "O Egg Kanban" } /* "O Egg Kanban" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B4D00, "O HASIGO" } /* "O HASIGO" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5B4B30, "O Elevator2" } /* "O Elevator2" */,
	{ 2, 3, 1, 40000, 0, (ObjectFuncPtr)0x5B4840, "O TATEKAN" } /* "O TATEKAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B45D0, "O AMY DRUM" } /* "O AMY DRUM" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B0910, "O COLOR DOOR" } /* "O COLOR DOOR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B07A0, "C FAKE AMY" } /* "C FAKE AMY" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B43D0, "C APP ZERO" } /* "C APP ZERO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B4480, "C KILL ZERO" } /* "C KILL ZERO" */,
	{ 2, 3, 1, 250000, 0, (ObjectFuncPtr)0x5B41F0, "O SHUTTER" } /* "O SHUTTER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B40A0, "C HANE" } /* "C HANE" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x5B3E30, "O GSHOOTER" } /* "O GSHOOTER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B0730, "O COLOR DOOR2" } /* "O COLOR DOOR2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B3620, "O FSAKU" } /* "O FSAKU" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0C80, "C SCENECHANGER" } /* "C SCENECHANGER" */,
	{ 2, 5, 0, 0, 0, (ObjectFuncPtr)0x5B27B0, "O Light1" } /* "O Light1" */,
	{ 2, 5, 0, 0, 0, (ObjectFuncPtr)0x5B2680, "O Light2" } /* "O Light2" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0A70, "EROB COLLI" } /* "EROB COLLI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5B24F0, "C RELEASE" } /* "C RELEASE" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ITEMBOXAIR" } /* "O ITEMBOXAIR" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" } /* "O FROG" */
};

ObjectList FinalEggObjectList = { arraylengthandptrT(FinalEggObjectList_list, int) };

void __cdecl FinalEggbjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_FinalEgg * 8 + 2] = &FinalEggObjectList;
}