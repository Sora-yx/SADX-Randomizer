#include "stdafx.h"
#include "Utils.h"
#include "IceCap.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"

HelperFunctions extern help;
extern int CustomLayout;
extern bool Missions;
extern int levelCount;
extern int CurrentAI;

void ICAct4() {

	CustomLayout = randomizedSets[levelCount].layout;

		switch (CustomLayout)
		{
		case 0:
		case 1:
			LoadSetFile(1, "0801"); //M1
			CustomLayout = 0;
			break;
		case 2:
			LoadSetFile(1, "0801"); //M2
			break;
		case 3:
			LoadSetFile(1, "0804"); //M3
			break;
		}

}




void __cdecl IceCap_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteCall((void*)0x4ed633, ICAct3Position); //teleport player during IC act 3.
	WriteData<2>((void*)0x4e980a, 0x90); //Make Ice Cap cave spawn as Big.
	WriteCall((void*)0x422e75, ICAct4);

	ICObjects_Init(path, helperFunctions);

	//Sonic
	helperFunctions.ReplaceFile("system\\SET0800S.BIN", "system\\levels\\Ice Cap\\Sonic-IC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0801S.BIN", "system\\levels\\Ice Cap\\Sonic-IC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0802S.BIN", "system\\levels\\Ice Cap\\Sonic-IC-Act3.bin");

	helperFunctions.ReplaceFile("system\\SET0804S.BIN", "system\\levels\\Ice Cap\\Sonic-IC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0800S.BIN", "system\\cam\\CAM0800S.bin");
	helperFunctions.ReplaceFile("system\\CAM0801S.BIN", "system\\cam\\CAM0801S.bin");
	helperFunctions.ReplaceFile("system\\CAM0802S.BIN", "system\\cam\\CAM0802S.bin");
	helperFunctions.RegisterStartPosition(Characters_Sonic, IC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, IC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, IC3_StartPositions[0]);

	//Tails
	helperFunctions.ReplaceFile("system\\SET0800M.BIN", "system\\levels\\Ice Cap\\Tails-IC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0801M.BIN", "system\\levels\\Ice Cap\\Tails-IC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0802M.BIN", "system\\levels\\Ice Cap\\Tails-IC-Act3.bin");

	helperFunctions.ReplaceFile("system\\SET0804M.BIN", "system\\levels\\Ice Cap\\Tails-IC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0800M.BIN", "system\\cam\\CAM0800M.bin");
	helperFunctions.ReplaceFile("system\\CAM0801M.BIN", "system\\cam\\CAM0801M.bin");
	helperFunctions.ReplaceFile("system\\CAM0802M.BIN", "system\\cam\\CAM0802M.bin");
	helperFunctions.RegisterStartPosition(Characters_Tails, IC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, IC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, IC3_StartPositions[0]);

	//Knuckles
	helperFunctions.ReplaceFile("system\\SET0800K.BIN", "system\\levels\\Ice Cap\\Knux-IC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0801K.BIN", "system\\levels\\Ice Cap\\Knux-IC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0802K.BIN", "system\\levels\\Ice Cap\\Knux-IC-Act3.bin");

	helperFunctions.ReplaceFile("system\\SET0804K.BIN", "system\\levels\\Ice Cap\\Knux-IC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0800K.BIN", "system\\cam\\CAM0800K.bin");
	helperFunctions.ReplaceFile("system\\CAM0801K.BIN", "system\\cam\\CAM0801K.bin");
	helperFunctions.ReplaceFile("system\\CAM0802K.BIN", "system\\cam\\CAM0802K.bin");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, IC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, IC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, IC3_StartPositions[0]);


	//Amy
	helperFunctions.ReplaceFile("system\\SET0800A.BIN", "system\\levels\\Ice Cap\\Amy-IC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0801A.BIN", "system\\levels\\Ice Cap\\Amy-IC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0802A.BIN", "system\\levels\\Ice Cap\\Amy-IC-Act3.bin");

	helperFunctions.ReplaceFile("system\\SET0804A.BIN", "system\\levels\\Ice Cap\\Amy-IC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0800A.BIN", "system\\cam\\CAM0800A.bin");
	helperFunctions.ReplaceFile("system\\CAM0801A.BIN", "system\\cam\\CAM0801A.bin");
	helperFunctions.ReplaceFile("system\\CAM0802A.BIN", "system\\cam\\CAM0802A.bin");
	helperFunctions.RegisterStartPosition(Characters_Amy, IC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, IC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, IC3_StartPositions[0]);

	//Big
	helperFunctions.ReplaceFile("system\\SET0800B.BIN", "system\\levels\\Ice Cap\\Big-IC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0801B.BIN", "system\\levels\\Ice Cap\\Big-IC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0802B.BIN", "system\\levels\\Ice Cap\\Big-IC-Act3.bin");

	helperFunctions.ReplaceFile("system\\SET0804B.BIN", "system\\levels\\Ice Cap\\Big-IC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0800B.BIN", "system\\cam\\CAM0800B.bin");
	helperFunctions.ReplaceFile("system\\CAM0801B.BIN", "system\\cam\\CAM0801B.bin");
	helperFunctions.ReplaceFile("system\\CAM0802B.BIN", "system\\cam\\CAM0802B.bin");
	helperFunctions.RegisterStartPosition(Characters_Big, IC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, IC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, IC3_StartPositions[0]);

	//Gamma
	helperFunctions.ReplaceFile("system\\SET0800E.BIN", "system\\levels\\Ice Cap\\Gamma-IC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0801E.BIN", "system\\levels\\Ice Cap\\Gamma-IC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0802E.BIN", "system\\levels\\Ice Cap\\Gamma-IC-Act3.bin");

	helperFunctions.ReplaceFile("system\\SET080E.BIN", "system\\levels\\Ice Cap\\Gamma-IC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0800E.BIN", "system\\cam\\CAM0800E.bin");
	helperFunctions.ReplaceFile("system\\CAM0801E.BIN", "system\\cam\\CAM0801E.bin");
	helperFunctions.ReplaceFile("system\\CAM0802E.BIN", "system\\cam\\CAM0802E.bin");
	helperFunctions.RegisterStartPosition(Characters_Gamma, IC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, IC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, IC3_StartPositions[0]);
}

ObjectListEntry IceCapObjectList_list[] = {
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
	{ 15, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ItemBoxAir" } /* "O ItemBoxAir" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINT" } /* "O HINT" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A9140, "O KN HINT" } /* "O KN HINT" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 15, 3, 0, 0, 0, (ObjectFuncPtr)0x4BF600, "O LevelItem" } /* "O LevelItem" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4F5CD0, "O Dd" } /* "O Dd" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F57F0, "O Hyo1NoExp" } /* "O Hyo1NoExp" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F5830, "O Hyo1Exp" } /* "O Hyo1Exp" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F5870, "O Hyo2NoExp" } /* "O Hyo2NoExp" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F58B0, "O Hyo2Exp" } /* "O Hyo2Exp" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F58F0, "O Hyo3NoExp" } /* "O Hyo3NoExp" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F5930, "O Hyo3Exp" } /* "O Hyo3Exp" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4DE0, "O ICEJMP" } /* "O ICEJMP" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4F4D80, "O ICICLE" } /* "O ICICLE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4F4B70, "O_Hako" } /* "O_Hako" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4F4AB0, "O_Ele" } /* "O_Ele" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4F4AE0, "O_Fiw4m" } /* "O_Fiw4m" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4F4B10, "O_Fiw5m" } /* "O_Fiw5m" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4F4B40, "O_Fiw6m" } /* "O_Fiw6m" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F49F0, "O_Saku01" } /* "O_Saku01" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4A20, "O_Saku01b" } /* "O_Saku01b" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4A50, "O_Saku02" } /* "O_Saku02" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4A80, "O_Saku02b" } /* "O_Saku02b" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4900, "O_Hashra1B" } /* "O_Hashra1B" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4950, "O_Hashra_C" } /* "O_Hashra_C" */,
	{ 6, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4990, "O_Hashra10C" } /* "O_Hashra10C" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4370, "O_HouseA" } /* "O_HouseA" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4390, "O_HouseB" } /* "O_HouseB" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F43B0, "O_HouseC" } /* "O_HouseC" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F43D0, "O_HouseD" } /* "O_HouseD" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F42D0, "Ki01" } /* "Ki01" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4240, "Kareki01" } /* "Kareki01" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F4270, "Kareki02" } /* "Kareki02" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F42A0, "Kareki03" } /* "Kareki03" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4F4210, "BigIta" } /* "BigIta" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4F41E0, "Maruta" } /* "Maruta" */,
	{ 2, 5, 1, 1440000, 0, (ObjectFuncPtr)0x4F40F0, "O MOKU A" } /* "O MOKU A" */,
	{ 2, 5, 1, 1440000, 0, (ObjectFuncPtr)0x4F4120, "O MOKU B" } /* "O MOKU B" */,
	{ 2, 5, 1, 1440000, 0, (ObjectFuncPtr)0x4F4150, "O MOKU C" } /* "O MOKU C" */,
	{ 2, 5, 1, 1440000, 0, (ObjectFuncPtr)0x4F4180, "O DRY A" } /* "O DRY A" */,
	{ 2, 5, 1, 1440000, 0, (ObjectFuncPtr)0x4F41B0, "O DRY B" } /* "O DRY B" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F3FF0, "O SNOW DOA" } /* "O SNOW DOA" */,
	{ 6, 3, 1, 4840000, 0, (ObjectFuncPtr)0x4F3A00, "TURIBASI 1" } /* "TURIBASI 1" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x4F3850, "O ICEBAR1" } /* "O ICEBAR1" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x4F26E0, "O ICEBAR2" } /* "O ICEBAR2" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4F1750, "O MizukusaA" } /* "O MizukusaA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4F1770, "O MizukusaB" } /* "O MizukusaB" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F15C0, "O ITA01" } /* "O ITA01" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F14E0, "O ITA02" } /* "O ITA02" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4F13F0, "O FUUSYA1" } /* "O FUUSYA1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4F11F0, "O MIZUIWAA" } /* "O MIZUIWAA" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4F1210, "O MIZUIWAB" } /* "O MIZUIWAB" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4F1230, "O MIZUIWAC" } /* "O MIZUIWAC" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x4F0EC0, "O BIGTURARA" } /* "O BIGTURARA" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4EF880, "O SuiTaore" } /* "O SuiTaore" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4EF8C0, "O SuisyouB" } /* "O SuisyouB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4EF8F0, "O SuisyouBM" } /* "O SuisyouBM" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4EF920, "O SuisyouR" } /* "O SuisyouR" */,
	{ 2, 3, 1, 3610000, 0, (ObjectFuncPtr)0x4EF4E0, "O BALLOON1" } /* "O BALLOON1" */,
	{ 2, 3, 1, 3610000, 0, (ObjectFuncPtr)0x4EF510, "O BALLOON2" } /* "O BALLOON2" */,
	{ 2, 3, 1, 3610000, 0, (ObjectFuncPtr)0x4EF540, "O BALLOON3" } /* "O BALLOON3" */,
	{ 2, 3, 1, 3610000, 0, (ObjectFuncPtr)0x4EF570, "O BALLOON4" } /* "O BALLOON4" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4EF360, "O FUTAL" } /* "O FUTAL" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4EF320, "O FUTAM" } /* "O FUTAM" */,
	{ 2, 3, 1, 1440000, 0, (ObjectFuncPtr)0x4EF340, "O FUTAM2" } /* "O FUTAM2" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4EE800, "O BicIwa" } /* "O BicIwa" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4EDBB0, "O BigHone" } /* "O BigHone" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4EDA90, "O SnowBoard" } /* "O SnowBoard" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x4ED4A0, "O SnowNewA" } /* "O SnowNewA" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x4ED4B0, "O SnowMountA" } /* "O SnowMountA" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x4ED4C0, "O SnowMountB" } /* "O SnowMountB" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x4ED4D0, "O SnowMountC" } /* "O SnowMountC" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x4ED4E0, "O SnowMountD" } /* "O SnowMountD" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED4F0, "O SnowRockA" } /* "O SnowRockA" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED500, "O SnowRockB" } /* "O SnowRockB" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED510, "O SnowRockC" } /* "O SnowRockC" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED520, "O SnowRockD" } /* "O SnowRockD" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED530, "O SnowStoneA" } /* "O SnowStoneA" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED540, "O SnowStoneB" } /* "O SnowStoneB" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED550, "O SnowStoneC" } /* "O SnowStoneC" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED560, "O SnowStoneD" } /* "O SnowStoneD" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED570, "O SnowStoneE" } /* "O SnowStoneE" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4ED580, "O SnowStoneF" } /* "O SnowStoneF" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4ED250, "O HasiHasi" } /* "O HasiHasi" */,
	{ 6, 2, 2, 4000000, 0, (ObjectFuncPtr)0x4EBEB0, "ACT23JOIN" } /* "ACT23JOIN" */,
	{ 6, 2, 2, 4000000, 0, (ObjectFuncPtr)0x4EBDF0, "ACT12JOIN" } /* "ACT12JOIN" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x4EC090, "O Kuguri" } /* "O Kuguri" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A1380, "E SAITO" } /* "E SAITO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A0330, "E HEVY " } /* "E HEVY " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4C8FB0, "E SMAN" } /* "E SMAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79F860, "SPRINGH" } /* "SPRINGH" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79B2F0, "O GRING" } /* "O GRING" */,
	{ 2, 2, 1, 2500, 0, (ObjectFuncPtr)0x7A8E50, "O BUBBLE" } /* "O BUBBLE" */,
	{ 2, 4, 1, 2500, 0, (ObjectFuncPtr)0x7A8A60, "O BUBBLES" } /* "O BUBBLES" */,
	{ 3, 3, 1, 2500, 0, (ObjectFuncPtr)0x5977F0, "S BASS " } /* "S BASS " */,
	{ 3, 3, 1, 2500, 0, (ObjectFuncPtr)0x7A7AD0, "S KAERU" } /* "S KAERU" */,
	{ 3, 3, 1, 2500, 0, (ObjectFuncPtr)0x597660, "S GENE " } /* "S GENE " */,
	{ 2, 0, 1, 1000000, 0, (ObjectFuncPtr)0x4D4E10, "NO WATER" } /* "NO WATER" */,
	{ 2, 0, 1, 2500, 0, (ObjectFuncPtr)0x4D4BE0, "BIGWJUMP" } /* "BIGWJUMP" */,
	{ 2, 2, 1, 360000, 0, (ObjectFuncPtr)0x4EA3B0, "COLD" } /* "COLD" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4ECFA0, "O KAOSE" } /* "O KAOSE" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x4ECE30, "YuraYura" } /* "YuraYura" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" } /* "O FROG" */
};

ObjectList IceCapObjectList = { arraylengthandptrT(IceCapObjectList_list, int) };

void __cdecl ICObjects_Init(const char *path, const HelperFunctions &helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_IceCap * 8 + 2] = &IceCapObjectList;
}