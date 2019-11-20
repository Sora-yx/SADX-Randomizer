#include "stdafx.h"
#include "Utils.h"
#include "Casino.h"
#include "Chao.h"
#include "RandomHelpers.h"

HelperFunctions extern help;
extern int CustomLayout;
extern bool Missions;
extern int levelCount;

void CasinoAct4() {

	CustomLayout = 0;

	CustomLayout = randomizedSets[levelCount].layout;


		switch (CustomLayout)
		{
		case 0:
			LoadSetFile(0, "0900"); //M1
			break;
		case 1:
			CustomLayout = 0;
			LoadSetFile(0, "0900"); //M1
			break;
		case 2:
			LoadSetFile(0, "0900"); //M2
			break;
		case 3:
			if (CurrentAct == 1)
			{
				CustomLayout = 2;
				LoadSetFile(0, "0900"); //M2
				return;
			}
			else
				LoadSetFile(0, "0904"); //M3

			break;
		}
	
}


void __cdecl Casino_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	//Sonic
	helperFunctions.ReplaceFile("system\\SET0900S.BIN", "system\\levels\\Casinopolis\\Sonic-Casino-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0901S.BIN", "system\\levels\\Casinopolis\\Sonic-Casino-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0904S.BIN", "system\\levels\\Casinopolis\\Sonic-Casino-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0900S.bin", "system\\cam\\CAM0900S.bin");
	helperFunctions.ReplaceFile("system\\CAM0901S.bin", "system\\cam\\CAM0901S.bin");
	helperFunctions.RegisterStartPosition(Characters_Sonic, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, Casino2_StartPositions[0]);


	//Tails
	helperFunctions.ReplaceFile("system\\SET0900M.BIN", "system\\levels\\Casinopolis\\Tails-Casino-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0901M.BIN", "system\\levels\\Casinopolis\\Tails-Casino-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0904M.BIN", "system\\levels\\Casinopolis\\Tails-Casino-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0900S.bin", "system\\cam\\CAM0900S.bin");
	helperFunctions.ReplaceFile("system\\CAM0901S.bin", "system\\cam\\CAM0901S.bin");
	helperFunctions.RegisterStartPosition(Characters_Tails, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, Casino2_StartPositions[0]);


	//Knuckles
	helperFunctions.ReplaceFile("system\\SET0900K.BIN", "system\\levels\\Casinopolis\\Knux-Casino-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0901K.BIN", "system\\levels\\Casinopolis\\Knux-Casino-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0904K.BIN", "system\\levels\\Casinopolis\\Knux-Casino-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0900K.bin", "system\\cam\\CAM0900K.bin");
	helperFunctions.ReplaceFile("system\\CAM0901K.bin", "system\\cam\\CAM0901K.bin");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Casino2_StartPositions[0]);



	//Amy
	helperFunctions.ReplaceFile("system\\SET0900A.BIN", "system\\levels\\Casinopolis\\Amy-Casino-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0901A.BIN", "system\\levels\\Casinopolis\\Amy-Casino-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0904A.BIN", "system\\levels\\Casinopolis\\Amy-Casino-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0900A.bin", "system\\cam\\CAM0900A.bin");
	helperFunctions.ReplaceFile("system\\CAM0901A.bin", "system\\cam\\CAM0901A.bin");
	helperFunctions.RegisterStartPosition(Characters_Amy, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, Casino2_StartPositions[0]);


	//Big
	helperFunctions.ReplaceFile("system\\SET0900B.BIN", "system\\levels\\Casinopolis\\Big-Casino-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0901B.BIN", "system\\levels\\Casinopolis\\Big-Casino-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0904B.BIN", "system\\levels\\Casinopolis\\Big-Casino-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0900B.bin", "system\\cam\\CAM0900B.bin");
	helperFunctions.ReplaceFile("system\\CAM0901B.bin", "system\\cam\\CAM0901B.bin");
	helperFunctions.RegisterStartPosition(Characters_Big, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, Casino2_StartPositions[0]);


	//Gamma
	helperFunctions.ReplaceFile("system\\SET0900E.BIN", "system\\levels\\Casinopolis\\Gamma-Casino-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0901E.BIN", "system\\levels\\Casinopolis\\Gamma-Casino-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0904E.BIN", "system\\levels\\Casinopolis\\Gamma-Casino-Chao.bin");


	helperFunctions.ReplaceFile("system\\CAM0900E.bin", "system\\cam\\CAM0900E.bin");
	helperFunctions.ReplaceFile("system\\CAM0901E.bin", "system\\cam\\CAM0901E.bin");
	helperFunctions.RegisterStartPosition(Characters_Gamma, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, Casino2_StartPositions[0]);

}

ObjectListEntry CasinopolisObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 4, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
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
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79B2F0, "O GRING" } /* "O GRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DD0A0, "O KAOSE" } /* "O KAOSE" */,
	{ 2, 0, 1, 1000000, 0, (ObjectFuncPtr)0x4D4E10, "NO WATER" } /* "NO WATER" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5DCEC0, "CC3" } /* "CC3" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DCCE0, "StartShot" } /* "StartShot" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5DCB40, "FlipperL" } /* "FlipperL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5DCBE0, "FlipperLx" } /* "FlipperLx" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5DCB90, "FlipperR" } /* "FlipperR" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5DCC00, "FlipperRx" } /* "FlipperRx" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DC000, "Bumper1" } /* "Bumper1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DC040, "Bumper2" } /* "Bumper2" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5DBBF0, "SlingL" } /* "SlingL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5DBC60, "SlingR" } /* "SlingR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DB6A0, "StoperC" } /* "StoperC" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DB700, "StoperL" } /* "StoperL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DB790, "StoperR" } /* "StoperR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DB150, "Roll" } /* "Roll" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DA8A0, "JdaiL" } /* "JdaiL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DA8B0, "JdaiR" } /* "JdaiR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DA1C0, "Dtarget" } /* "Dtarget" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5DA1E0, "Dtarget2" } /* "Dtarget2" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5D98A0, "RollUpR" } /* "RollUpR" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5D98F0, "RollUpL" } /* "RollUpL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5D9940, "RollDownL" } /* "RollDownL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D9450, "Tuuka" } /* "Tuuka" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D9520, "RightLane" } /* "RightLane" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5D8920, "AkaAoMido" } /* "AkaAoMido" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D8560, "Neon" } /* "Neon" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5D85A0, "Neonkabe" } /* "Neonkabe" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5D82C0, "KuroKabe" } /* "KuroKabe" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5D8170, "ShoogaiL" } /* "ShoogaiL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5D8180, "ShoogaiR" } /* "ShoogaiR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D7E20, "HoudaiL" } /* "HoudaiL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D7E40, "HoudaiR" } /* "HoudaiR" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5D79F0, "Ideacap" } /* "Ideacap" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5D78E0, "Idea" } /* "Idea" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D7760, "Card" } /* "Card" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5D7510, "CardDisp" } /* "CardDisp" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5D6AC0, "Path" } /* "Path" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D6350, "Saico" } /* "Saico" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D61A0, "BigStar" } /* "BigStar" */,
	{ 2, 3, 1, 2102500, 0, (ObjectFuncPtr)0x5D6040, "Loop" } /* "Loop" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D5E20, "KazariYaji" } /* "KazariYaji" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D5D00, "Tanemono" } /* "Tanemono" */,
	{ 2, 3, 1, 902500, 0, (ObjectFuncPtr)0x5D5AE0, "PianTama" } /* "PianTama" */,
	{ 2, 3, 1, 902500, 0, (ObjectFuncPtr)0x5D5B30, "PianPach" } /* "PianPach" */,
	{ 2, 3, 1, 902500, 0, (ObjectFuncPtr)0x5D5B70, "PianWalk" } /* "PianWalk" */,
	{ 2, 3, 1, 902500, 0, (ObjectFuncPtr)0x5D5BB0, "PianFish" } /* "PianFish" */,
	{ 2, 3, 1, 902500, 0, (ObjectFuncPtr)0x5D5BF0, "PianSlee" } /* "PianSlee" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5D56E0, "CardUV" } /* "CardUV" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D5430, "StarNeon" } /* "StarNeon" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D5460, "YajiNeon" } /* "YajiNeon" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D54C0, "Densyoku" } /* "Densyoku" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D5240, "Emergency" } /* "Emergency" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5D5060, "SitaAlEgg" } /* "SitaAlEgg" */,
	{ 2, 3, 2, 0, 0, (ObjectFuncPtr)0x5D5090, "UeAlEgg" } /* "UeAlEgg" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5D4EF0, "BanjuDoor" } /* "BanjuDoor" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0, "DANGER" } /* "DANGER" */,
	{ 7, 3, 1, 62500, 0, (ObjectFuncPtr)0x5D4D40, "O TUTUA" } /* "O TUTUA" */,
	{ 7, 3, 1, 62500, 0, (ObjectFuncPtr)0x5D4D70, "O TUTUB" } /* "O TUTUB" */,
	{ 7, 3, 1, 62500, 0, (ObjectFuncPtr)0x5D4DC0, "O TUTUC" } /* "O TUTUC" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5D4200, "O 6SLOT" } /* "O 6SLOT" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5D3E00, "O CRYSTAL" } /* "O CRYSTAL" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x5D3C80, "O HAGURUMA" } /* "O HAGURUMA" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5D3A20, "O DMGSPHERE" } /* "O DMGSPHERE" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5D3990, "O KKDOOR" } /* "O KKDOOR" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5D33B0, "O SRDOOR" } /* "O SRDOOR" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5D2DF0, "O MANF" } /* "O MANF" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5D2890, "O HYOUJIKI" } /* "O HYOUJIKI" */,
	{ 6, 3, 1, 640000, 0, (ObjectFuncPtr)0x5D22D0, "O LION" } /* "O LION" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5D1450, "O TELEPOT" } /* "O TELEPOT" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C4970, "O FLOWERA" } /* "O FLOWERA" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C4990, "O FLOWERB" } /* "O FLOWERB" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5D0BA0, "O KAZA" } /* "O KAZA" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5D0C00, "O KAZB" } /* "O KAZB" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5D0C20, "O KAZC" } /* "O KAZC" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5D0C40, "O KAZD" } /* "O KAZD" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5D0C60, "O KAZE" } /* "O KAZE" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5D0C80, "O KAZF" } /* "O KAZF" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5D0CA0, "O KAZG" } /* "O KAZG" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5D0480, "O HAND" } /* "O HAND" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4880, "O KIN" } /* "O KIN" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CF6C0, "O KINKA" } /* "O KINKA" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5CF450, "O SHWR" } /* "O SHWR" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CEF20, "O SONZ" } /* "O SONZ" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4210, "O KSONICZO" } /* "O KSONICZO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C3750, "O HAHEN1" } /* "O HAHEN1" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C3770, "O HAHEN2" } /* "O HAHEN2" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C3790, "O HAHEN3" } /* "O HAHEN3" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C37B0, "O HAHEN4" } /* "O HAHEN4" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C37D0, "O HAHEN5" } /* "O HAHEN5" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C37F0, "O HAHEN6" } /* "O HAHEN6" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CED50, "O FL" } /* "O FL" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C49F0, "O SAKU" } /* "O SAKU" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C4A10, "O TARU" } /* "O TARU" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0, "O SMOKE" } /* "O SMOKE" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C4A30, "O HAKO" } /* "O HAKO" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C4A50, "O GBOX" } /* "O GBOX" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4A70, "O GOMIB" } /* "O GOMIB" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4A90, "O GOMIR" } /* "O GOMIR" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4AB0, "O RLT" } /* "O RLT" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4AD0, "O YUKH" } /* "O YUKH" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4AF0, "O RLTI" } /* "O RLTI" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4B10, "O KBB" } /* "O KBB" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4B30, "O KBR" } /* "O KBR" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4B50, "O KB1" } /* "O KB1" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4B80, "O KB2" } /* "O KB2" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4BB0, "O KB3" } /* "O KB3" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4BE0, "O KB4" } /* "O KB4" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CEB30, "O KBC" } /* "O KBC" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CE910, "O KBS" } /* "O KBS" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5CE740, "O SLB" } /* "O SLB" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5CE760, "O SLG" } /* "O SLG" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5CE780, "O SLR" } /* "O SLR" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5CE7A0, "O SLY" } /* "O SLY" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C48F0, "O FKA" } /* "O FKA" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4910, "O FKB" } /* "O FKB" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4C10, "O TDENKI" } /* "O TDENKI" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5CE570, "O SARM" } /* "O SARM" */,
	{ 2, 5, 1, 360000, 0, (ObjectFuncPtr)0x5CE240, "O TSDOOR" } /* "O TSDOOR" */,
	{ 2, 3, 1, 490000, 0, (ObjectFuncPtr)0x5CDBE0, "O MB" } /* "O MB" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5CDA50, "O SHAT1" } /* "O SHAT1" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5CDA60, "O SHAT2" } /* "O SHAT2" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4C30, "O SDFUTIR" } /* "O SDFUTIR" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4C60, "O SDFUTIB" } /* "O SDFUTIB" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4C90, "O MAP2F" } /* "O MAP2F" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4CB0, "O CFO" } /* "O CFO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4CD0, "O MIZUA" } /* "O MIZUA" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4CF0, "O MIZUB" } /* "O MIZUB" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C4D10, "O SYA" } /* "O SYA" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C4D30, "O SYB" } /* "O SYB" */,
	{ 6, 3, 1, 490000, 0, (ObjectFuncPtr)0x5CD2F0, "O TENSC" } /* "O TENSC" */,
	{ 6, 3, 1, 490000, 0, (ObjectFuncPtr)0x5CD2D0, "O TENSS" } /* "O TENSS" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5C4D50, "O SHWRL" } /* "O SHWRL" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5C4D70, "O SHWHD" } /* "O SHWHD" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C4D90, "O NEOKAB" } /* "O NEOKAB" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CCF40, "O M1FNEO" } /* "O M1FNEO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CCD90, "O CARDKAN" } /* "O CARDKAN" */,
	{ 2, 3, 0, 360000, 0, (ObjectFuncPtr)0x5CCAE0, "O SLOTKAN" } /* "O SLOTKAN" */,
	{ 2, 3, 0, 360000, 0, (ObjectFuncPtr)0x5CC5F0, "O HASGO" } /* "O HASGO" */,
	{ 2, 3, 0, 360000, 0, (ObjectFuncPtr)0x5CBFE0, "O FANFAN" } /* "O FANFAN" */,
	{ 6, 3, 1, 490000, 0, (ObjectFuncPtr)0x5CB440, "O FOOK" } /* "O FOOK" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x5CB160, "O TIKEIANIM" } /* "O TIKEIANIM" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5CACD0, "O NEON K" } /* "O NEON K" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CAA20, "O KDANL" } /* "O KDANL" */,
	{ 6, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CAA50, "O KDANM" } /* "O KDANM" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5C4930, "O SLOTISU" } /* "O SLOTISU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5CA850, "O CRECT2" } /* "O CRECT2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5CA680, "O CCYL2" } /* "O CCYL2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5CA700, "O CCAP" } /* "O CCAP" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C4950, "O DENTO" } /* "O DENTO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C48B0, "O LIGHTA" } /* "O LIGHTA" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C48D0, "O LIGHTB" } /* "O LIGHTB" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5CA180, "O 6SLOT2" } /* "O 6SLOT2" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C9D60, "O LHTR" } /* "O LHTR" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C9B40, "O LHTG" } /* "O LHTG" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C9940, "O WSR" } /* "O WSR" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C96B0, "O WSR2" } /* "O WSR2" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C8A10, "O HAE" } /* "O HAE" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C59A0, "O MUDOUT" } /* "O MUDOUT" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x5C88D0, "O LETSGO" } /* "O LETSGO" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C8560, "O KAIZA" } /* "O KAIZA" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C79B0, "O KAIZB" } /* "O KAIZB" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C6EC0, "O KAIZC" } /* "O KAIZC" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C63D0, "O KAIZS" } /* "O KAIZS" */,
	{ 2, 3, 1, 640000, 0, (ObjectFuncPtr)0x5C5960, "O MUD" } /* "O MUD" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5C56F0, "O HOSIN" } /* "O HOSIN" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C5270, "O SUITEKI" } /* "O SUITEKI" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C49B0, "O FLOWERAL" } /* "O FLOWERAL" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C49D0, "O FLOWERBL" } /* "O FLOWERBL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5C4520, "O KINWALL" } /* "O KINWALL" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x5C3880, "O SONZCOL" } /* "O SONZCOL" */,
	{ 2, 3, 5, 360000, 0, (ObjectFuncPtr)0x4AF190, "E UNI A" } /* "E UNI A" */,
	{ 2, 3, 5, 360000, 0, (ObjectFuncPtr)0x4AF500, "E UNI B" } /* "E UNI B" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0DF0, "SPINA A" } /* "SPINA A" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0F40, "SPINA B" } /* "SPINA B" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B1090, "SPINA C" } /* "SPINA C" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG " } /* "O FROG " */
};

ObjectList CasinopolisObjectList = { arraylengthandptrT(CasinopolisObjectList_list, int) };
FunctionPointer(int, Chao_Animation, (ObjectMaster* a1, int a2), 0x734F00);

void __cdecl CasinoObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_Casinopolis * 8 + 0] = &CasinopolisObjectList;
}