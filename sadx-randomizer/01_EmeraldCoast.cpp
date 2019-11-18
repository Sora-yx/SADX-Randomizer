#include "stdafx.h"
#include "Utils.h"
#include "EmeraldCoast.h"
#include "RandomHelpers.h"
#include "LandTableInfo.h"

//LandTableInfo* ECAct1;

//void __cdecl EmeraldCoast_Init(const char* path, const HelperFunctions& helperFunctions) 

HelperFunctions extern help;
extern int CustomLayout;
extern bool Race;
extern bool Missions;

void ECAct4() {

	CustomLayout = 0;


	if (Missions && CurrentAct != 2)
	{
		CustomLayout = rand() % 4;
	}

	if (CurrentAct == 2)
		CustomLayout = 5; //Froggy

	switch (CustomLayout)
	{
	case 0:
		CustomLayout = 0;
		LoadSetFile(1, "0101"); //M1
		break;
	case 1:
		CustomLayout = 0;
		LoadSetFile(1, "0101"); //M1
		break;
	case 2:
		LoadSetFile(1, "0101"); //M2
		break;
	case 3:
		LoadSetFile(1, "0103"); //M3
		break;
	}

}



void __cdecl EmeraldCoast_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data


	//Sonic
	helperFunctions.ReplaceFile("system\\SET0100S.BIN", "system\\levels\\Emerald Coast\\Sonic-EC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0101S.BIN", "system\\levels\\Emerald Coast\\Sonic-EC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0102S.BIN", "system\\levels\\Emerald Coast\\Sonic-EC-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0103S.BIN", "system\\levels\\Emerald Coast\\Sonic-EC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0100S.BIN", "system\\cam\\CAM0100S.bin");
	helperFunctions.ReplaceFile("system\\CAM0101S.BIN", "system\\cam\\CAM0101S.bin");
	helperFunctions.ReplaceFile("system\\CAM0102S.BIN", "system\\cam\\CAM0102S.bin");
	helperFunctions.RegisterStartPosition(Characters_Sonic, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, EC3_StartPositions[0]);

	//Tails
	helperFunctions.ReplaceFile("system\\SET0100M.BIN", "system\\levels\\Emerald Coast\\Tails-EC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0101M.BIN", "system\\levels\\Emerald Coast\\Tails-EC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0102M.BIN", "system\\levels\\Emerald Coast\\Tails-EC-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0103M.BIN", "system\\levels\\Emerald Coast\\Tails-EC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0100M.BIN", "system\\cam\\CAM0100M.bin");
	helperFunctions.ReplaceFile("system\\CAM0101M.BIN", "system\\cam\\CAM0101M.bin");
	helperFunctions.ReplaceFile("system\\CAM0102M.BIN", "system\\cam\\CAM0102M.bin");
	helperFunctions.RegisterStartPosition(Characters_Tails, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, EC3_StartPositions[0]);

	//Knuckles
	helperFunctions.ReplaceFile("system\\SET0100K.BIN", "system\\levels\\Emerald Coast\\Knux-EC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0101K.BIN", "system\\levels\\Emerald Coast\\Knux-EC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0102K.BIN", "system\\levels\\Emerald Coast\\Knux-EC-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0103K.BIN", "system\\levels\\Emerald Coast\\Knux-EC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0100K.BIN", "system\\cam\\CAM0100K.bin");
	helperFunctions.ReplaceFile("system\\CAM0101K.BIN", "system\\cam\\CAM0101K.bin");
	helperFunctions.ReplaceFile("system\\CAM0102K.BIN", "system\\cam\\CAM0102K.bin");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EC3_StartPositions[0]);


	//Amy
	helperFunctions.ReplaceFile("system\\SET0100A.BIN", "system\\levels\\Emerald Coast\\Amy-EC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0101A.BIN", "system\\levels\\Emerald Coast\\Amy-EC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0102A.BIN", "system\\levels\\Emerald Coast\\Amy-EC-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0103A.BIN", "system\\levels\\Emerald Coast\\Amy-EC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0100A.BIN", "system\\cam\\CAM0100A.bin");
	helperFunctions.ReplaceFile("system\\CAM0101A.BIN", "system\\cam\\CAM0101A.bin");
	helperFunctions.ReplaceFile("system\\CAM0102A.BIN", "system\\cam\\CAM0102A.bin");
	helperFunctions.RegisterStartPosition(Characters_Amy, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, EC3_StartPositions[0]);

	//Big
	helperFunctions.ReplaceFile("system\\SET0100B.BIN", "system\\levels\\Emerald Coast\\Big-EC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0101B.BIN", "system\\levels\\Emerald Coast\\Big-EC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0102B.BIN", "system\\levels\\Emerald Coast\\Big-EC-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0103B.BIN", "system\\levels\\Emerald Coast\\Big-EC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0100B.BIN", "system\\cam\\CAM0100B.bin");
	helperFunctions.ReplaceFile("system\\CAM0101B.BIN", "system\\cam\\CAM0101B.bin");
	helperFunctions.ReplaceFile("system\\CAM0102B.BIN", "system\\cam\\CAM0102B.bin");
	helperFunctions.RegisterStartPosition(Characters_Big, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, EC3_StartPositions[0]);

	//Gamma
	helperFunctions.ReplaceFile("system\\SET0100E.BIN", "system\\levels\\Emerald Coast\\Gamma-EC-Act1.bin");
	helperFunctions.ReplaceFile("system\\SET0101E.BIN", "system\\levels\\Emerald Coast\\Gamma-EC-Act2.bin");
	helperFunctions.ReplaceFile("system\\SET0102E.BIN", "system\\levels\\Emerald Coast\\Gamma-EC-Act3.bin");
	helperFunctions.ReplaceFile("system\\SET0103E.BIN", "system\\levels\\Emerald Coast\\Gamma-EC-Chao.bin");

	helperFunctions.ReplaceFile("system\\CAM0100E.BIN", "system\\cam\\CAM0100E.bin");
	helperFunctions.ReplaceFile("system\\CAM0101E.BIN", "system\\cam\\CAM0101E.bin");
	helperFunctions.ReplaceFile("system\\CAM0102E.BIN", "system\\cam\\CAM0102E.bin");
	helperFunctions.RegisterStartPosition(Characters_Gamma, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, EC3_StartPositions[0]);


}

