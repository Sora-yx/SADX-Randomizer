#include "stdafx.h"
#include "Utils.h"
#include "HS.h"
#include "RandomHelpers.h"

HelperFunctions extern help;
extern int CustomLayout;
extern bool Missions;
extern int CurrentMission;

void __cdecl HotShelter_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data

	//Sonic
	helperFunctions.ReplaceFile("system\\SET1200S.BIN", "system\\levels\\Hot Shelter\\Sonic-HS-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1201S.BIN", "system\\levels\\Hot Shelter\\Sonic-HS-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1202S.BIN", "system\\levels\\Hot Shelter\\Sonic-HS-Act3.bin");

	helperFunctions.ReplaceFile("system\\CAM1200S.bin", "system\\cam\\CAM1200S.bin");
	helperFunctions.ReplaceFile("system\\CAM1201S.bin", "system\\cam\\CAM1201S.bin");
	helperFunctions.ReplaceFile("system\\CAM1202S.bin", "system\\cam\\CAM1202S.bin");
	helperFunctions.RegisterStartPosition(Characters_Sonic, HS1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, HS2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, HS3_StartPositions[0]);

	//Tails
	helperFunctions.ReplaceFile("system\\SET1200M.BIN", "system\\levels\\Hot Shelter\\Tails-HS-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1201M.BIN", "system\\levels\\Hot Shelter\\Tails-HS-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1202M.BIN", "system\\levels\\Hot Shelter\\Tails-HS-Act3.bin");

	helperFunctions.ReplaceFile("system\\CAM1200M.bin", "system\\cam\\CAM1200M.bin");  
	helperFunctions.ReplaceFile("system\\CAM1201M.bin", "system\\cam\\CAM1201M.bin");
	helperFunctions.ReplaceFile("system\\CAM1202M.bin", "system\\cam\\CAM1202M.bin");
	helperFunctions.RegisterStartPosition(Characters_Tails, HS1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, HS2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, HS3_StartPositions[0]);

	//Knuckles
	helperFunctions.ReplaceFile("system\\SET1200K.BIN", "system\\levels\\Hot Shelter\\Knux-HS-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1201K.BIN", "system\\levels\\Hot Shelter\\Knux-HS-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1202K.BIN", "system\\levels\\Hot Shelter\\Knux-HS-Act3.bin");

	helperFunctions.ReplaceFile("system\\CAM1200K.bin", "system\\cam\\CAM1200K.bin");
	helperFunctions.ReplaceFile("system\\CAM1201K.bin", "system\\cam\\CAM1201K.bin");
	helperFunctions.ReplaceFile("system\\CAM1202K.bin", "system\\cam\\CAM1202K.bin");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, HS1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, HS2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, HS3_StartPositions[0]);


	//Amy
	helperFunctions.ReplaceFile("system\\SET1200A.BIN", "system\\levels\\Hot Shelter\\Amy-HS-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1201A.BIN", "system\\levels\\Hot Shelter\\Amy-HS-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1202A.BIN", "system\\levels\\Hot Shelter\\Amy-HS-Act3.bin");

	helperFunctions.ReplaceFile("system\\CAM1200A.bin", "system\\cam\\CAM1200A.bin");
	helperFunctions.ReplaceFile("system\\CAM1201A.bin", "system\\cam\\CAM1201A.bin");
	helperFunctions.ReplaceFile("system\\CAM1202A.bin", "system\\cam\\CAM1202A.bin");
	helperFunctions.RegisterStartPosition(Characters_Amy, HS1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, HS2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, HS3_StartPositions[0]);

	//Big
	helperFunctions.ReplaceFile("system\\SET1200B.BIN", "system\\levels\\Hot Shelter\\Big-HS-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1201B.BIN", "system\\levels\\Hot Shelter\\Big-HS-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1202B.BIN", "system\\levels\\Hot Shelter\\Big-HS-Act3.bin");

	helperFunctions.ReplaceFile("system\\CAM1200B.bin", "system\\cam\\CAM1200B.bin");
	helperFunctions.ReplaceFile("system\\CAM1201B.bin", "system\\cam\\CAM1201B.bin");
	helperFunctions.ReplaceFile("system\\CAM1202B.bin", "system\\cam\\CAM1202B.bin");
	helperFunctions.RegisterStartPosition(Characters_Big, HS1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, HS2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, HS3_StartPositions[0]);

	//Gamma
	helperFunctions.ReplaceFile("system\\SET1200E.BIN", "system\\levels\\Hot Shelter\\Gamma-HS-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET1201E.BIN", "system\\levels\\Hot Shelter\\Gamma-HS-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET1202E.BIN", "system\\levels\\Hot Shelter\\Gamma-HS-Act3.bin");

	helperFunctions.ReplaceFile("system\\CAM1200E.bin", "system\\cam\\CAM1200E.bin");
	helperFunctions.ReplaceFile("system\\CAM1201E.bin", "system\\cam\\CAM1201E.bin");
	helperFunctions.ReplaceFile("system\\CAM1202E.bin", "system\\cam\\CAM1202E.bin");
	helperFunctions.RegisterStartPosition(Characters_Gamma, HS1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, HS2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, HS3_StartPositions[0]);
}



void HotShelterAct4() {

	CustomLayout = 0;
	CurrentMission = 0;

	CustomLayout = rand() % 2;

	if (CustomLayout == 0)
	{
		if (CurrentCharacter == Characters_Amy)
		{
		LoadSetFile(0, "1200"); //load Big version for Amy.
		//Make Big Hot Shelter stuff (secret door etc.) work for everyone.
		WriteData<1>((void*)0x5aaf12, 0x08); //open the door when you activate the switch. (if < 8)
		WriteData<1>((void*)0x5aaf14, 0x9C); //Open the door for everyone. (from SETZ to SETL: if < 8)
		WriteData<1>((void*)0x59a3bb, 0x08);
		WriteData<1>((void*)0x59a3bc, 0x74); //makes the second switch working for everyone.
		WriteData<1>((void*)0x59a125, 0x08);
		WriteData<1>((void*)0x59a126, 0x74);
		return;
		}
		else
		{
			LoadSetFile(0, "1200"); //load Amy hot Shelter version.
			WriteData<1>((void*)0x59a3bb, 0x08); //restore act 2 song
			return;
		}
	}

	if (CustomLayout == 1)
	{
		if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Gamma) //Amy has Big layout by defaut and Big has Amy layout by defaut.
		{
			LoadSetFile(0, "1200");
			WriteData<1>((void*)0x59a3bb, 0x08); //restore act 2 song
			return;
		}
		else
		{
			LoadSetFile(0, "1204"); //load Big version for other characters.
			//Make Big Hot Shelter stuff (secret door etc.) work for everyone.
			WriteData<1>((void*)0x5aaf12, 0x08); //open the door when you activate the switch. (if < 8)
			WriteData<1>((void*)0x5aaf14, 0x9C); //Open the door for everyone. (from SETZ to SETL: if < 8)
			WriteData<1>((void*)0x59a3bb, 0x08);
			WriteData<1>((void*)0x59a3bc, 0x74); //makes the second switch working for everyone.
			WriteData<1>((void*)0x59a125, 0x08);
			WriteData<1>((void*)0x59a126, 0x74);
			return;
		}

	}

}




//Object

ObjectListEntry HotShelter2ObjectList_list[] = {
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
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A8A60, "BUBBLE1" } /* "BUBBLE1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBDE0, "DYNAMITE" } /* "DYNAMITE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0C80, "C SCENECHANGER" } /* "C SCENECHANGER" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ITEMBOXAIR" } /* "O ITEMBOXAIR" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0A70, "EROB COLLI" } /* "EROB COLLI" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINTBOX" } /* "O HINTBOX" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x5A3520, "C SWITCH" } /* "C SWITCH" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4AD140, "E SARU" } /* "E SARU" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A6700, "E ROBO" } /* "E ROBO" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A85C0, "E LEON" } /* "E LEON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A33D0, "O ENTOTSU" } /* "O ENTOTSU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3210, "O LIGHT1" } /* "O LIGHT1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3030, "O LIGHT2" } /* "O LIGHT2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2F10, "O LIGHT3" } /* "O LIGHT3" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2DC0, "O CONTAINER" } /* "O CONTAINER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2950, "O KAITENKEY" } /* "O KAITENKEY" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2490, "O KAITENMETER" } /* "O KAITENMETER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2250, "O BIRIBIRI" } /* "O BIRIBIRI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2120, "O GATE1" } /* "O GATE1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A1D70, "O ELEVATOR" } /* "O ELEVATOR" */,
	{ 6, 3, 1, 1690000, 0, (ObjectFuncPtr)0x5A16B0, "O BRIDGE" } /* "O BRIDGE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0C50, "O SASAE1A" } /* "O SASAE1A" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0B10, "O SASAE1B" } /* "O SASAE1B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A09D0, "O SASAE1C" } /* "O SASAE1C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0890, "O SASAE1D" } /* "O SASAE1D" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x5A0720, "O HAGURUMA1" } /* "O HAGURUMA1" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x5A0540, "O HAGURUMA2" } /* "O HAGURUMA2" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x5A0230, "O HAGURUMA3" } /* "O HAGURUMA3" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x59FF30, "O HAGURUMA4" } /* "O HAGURUMA4" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x59FD50, "O HAGURUMA5" } /* "O HAGURUMA5" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x59FA40, "O HAGURUMA6" } /* "O HAGURUMA6" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA60, "O GATE2" } /* "O GATE2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F770, "O TUKIKOU" } /* "O TUKIKOU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F620, "O PROPELLER" } /* "O PROPELLER" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59F470, "O KAIDAN" } /* "O KAIDAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EFE0, "O DRUMCAN" } /* "O DRUMCAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EEA0, "O KAZARI1" } /* "O KAZARI1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59ED50, "O KAZARI2" } /* "O KAZARI2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EBF0, "O SYOUMEI" } /* "O SYOUMEI" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59EB00, "O COMPUTER" } /* "O COMPUTER" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59E940, "O KAITENDAI" } /* "O KAITENDAI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E660, "O TOILE_DOOR" } /* "O TOILE_DOOR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E430, "O DARUMA" } /* "O DARUMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59E170, "O HAKO" } /* "O HAKO" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59DFA0, "O UKIJIMA" } /* "O UKIJIMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59D970, "O HASIGO" } /* "O HASIGO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D840, "O GATESIDE" } /* "O GATESIDE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D760, "O BLUELIGHT" } /* "O BLUELIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D5C0, "O LIGHT4" } /* "O LIGHT4" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D460, "O HIKARI" } /* "O HIKARI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D350, "O FENS" } /* "O FENS" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D1F0, "O KANSO" } /* "O KANSO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D0D0, "O WCMARK1" } /* "O WCMARK1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59CFB0, "O WCMARK2" } /* "O WCMARK2" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59CDF0, "O KAITENASHIBA" } /* "O KAITENASHIBA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA90, "GATE13" } /* "GATE13" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5960, "O GATE SW" } /* "O GATE SW" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A70C0, "O BANJI" } /* "O BANJI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A6EB0, "O SUB TV" } /* "O SUB TV" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A6BB0, "O ROBO TV" } /* "O ROBO TV" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A6800, "O Crash TV" } /* "O Crash TV" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5B70, "O Box Ana" } /* "O Box Ana" */,
	{ 3, 3, 1, 62500, 0, (ObjectFuncPtr)0x59AAF0, "O BOX SWITCH" } /* "O BOX SWITCH" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG " } /* "O FROG " */
};

ObjectList HotShelter2ObjectList = { arraylengthandptrT(HotShelter2ObjectList_list, int) };

void __cdecl HSObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_HotShelter * 8 + 1] = &HotShelter2ObjectList;
}


