#include "stdafx.h"
#include "Utils.h"
#include "EmeraldCoast.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Emerald Coast\\" B ".bin")
#define ReplaceCAM(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")


void EC_Cam() {

	if (Mission1_Variation)
	{
		if (CurrentCharacter == Characters_Gamma && !Vanilla)
			LoadCamFile(0, "0100");
		else
			LoadCamFile(0, "0104");
	}
	else
	{
		LoadCamFile(0, "0100");
	}
	

	LoadCamFile(1, "0101");
	LoadCamFile(2, "0102");

	return;

}

void EC_Layout() {

	CurrentLevelLayout = randomizedSets[levelCount].MissionLayout;

	if (CurrentAct != 2)
	{
		switch (CurrentLevelLayout)
		{
		case Mission1:
		default:
			if (CurrentCharacter == Characters_Sonic && !Vanilla)
			{
				LoadSetFile(0, "0104"); //M1 Gamma Version
				CurrentLevelLayout = Mission1_Variation;
			}
			else
			{
				LoadSetFile(0, "0100"); //M1 Sonic Version
			}
			LoadSetFile(1, "0101");
			break;
		case Mission1_Variation:
			if (CurrentCharacter == Characters_Gamma && !Vanilla)
			{
				LoadSetFile(0, "0100");
				CurrentLevelLayout = Mission1;
			}
			else
			{
				LoadSetFile(0, "0104"); //M1 Gamma Version
			}

			LoadSetFile(1, "0101");
			break;
		case Mission2_100Rings:
			if (CurrentCharacter == Characters_Sonic && !Vanilla)
			{
				LoadSetFile(0, "0104"); //M1 Gamma Version
				CurrentLevelLayout = Mission1_Variation;
			}
			else
			{
				LoadSetFile(0, "0100");
			}
			LoadSetFile(1, "0101"); //M2
			break;
		case Mission3_LostChao:
			if (CurrentCharacter == Characters_Sonic && !Vanilla)
			{
				LoadSetFile(0, "0104"); //M1 Gamma Version
				LoadSetFile(1, "0101");
				CurrentLevelLayout = Mission1_Variation;
			}
			else
			{
				LoadSetFile(0, "0100");
				LoadSetFile(1, "0103"); //M3
			}

			break;
		}
	}

	if (CurrentAct == 2)
	{
		LoadSetFile(0, "0100");
		LoadSetFile(1, "0101");
	}

	LoadSetFile(2, "0102");
	EC_Cam();
	return;
}

void __cdecl EmeraldCoast_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteData<5>((void*)0x4f6afa, 0x90); //Prevent the game to start the cutscene as Tails.
	WriteData<1>((void*)0x427FCA, 0x08); //Fix EC HUD display for Tails.

	WriteData<5>((void*)0x422b74, 0x90);
	WriteData<5>((void*)0x422b83, 0x90);
	WriteData<5>((void*)0x422b92, 0x90);
	WriteData<5>((void*)0x422b9e, 0x90);
	WriteData<5>((void*)0x422bad, 0x90);

	WriteCall((void*)0x422bbc, EC_Layout);

	//Sonic
	ReplaceSET("SET0100S", "Sonic-EC-Act1");
	ReplaceSET("SET0101S", "Sonic-EC-Act2");
	ReplaceSET("SET0102S", "Sonic-EC-Act3");
	ReplaceSET("SET0103S", "Sonic-EC-Chao");
	ReplaceSET("SET0104S", "Sonic-EC-Gamma");

	ReplaceCAM("CAM0100S", "CAM0100S");
	ReplaceCAM("CAM0101S", "CAM0101S");
	ReplaceCAM("CAM0102S", "CAM0102S");
	ReplaceCAM("CAM0104S", "CAM0104S");

	helperFunctions.RegisterStartPosition(Characters_Sonic, EC3_StartPositions[0]);

	//Tails
	ReplaceSET("SET0100M", "Tails-EC-Act1");
	ReplaceSET("SET0101M", "Tails-EC-Act2");
	ReplaceSET("SET0102M", "Tails-EC-Act3");
	ReplaceSET("SET0103M", "Tails-EC-Chao");
	ReplaceSET("SET0104M", "Tails-EC-Gamma");

	ReplaceCAM("CAM0100M", "CAM0100M");
	ReplaceCAM("CAM0101M", "CAM0101M");
	ReplaceCAM("CAM0102M", "CAM0102M");
	ReplaceCAM("CAM0104M", "CAM0104M");
	helperFunctions.RegisterStartPosition(Characters_Tails, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, EC3_StartPositions[0]);

	//Knuckles
	ReplaceSET("SET0100K", "Knux-EC-Act1");
	ReplaceSET("SET0101K", "Knux-EC-Act2");
	ReplaceSET("SET0102K", "Knux-EC-Act3");
	ReplaceSET("SET0103K", "Knux-EC-Chao");
	ReplaceSET("SET0104K", "Knux-EC-Gamma");

	ReplaceCAM("CAM0100K", "CAM0100K");
	ReplaceCAM("CAM0101K", "CAM0101K");
	ReplaceCAM("CAM0102K", "CAM0102K");
	ReplaceCAM("CAM0104K", "CAM0104K");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, EC3_StartPositions[0]);

	//Amy
	ReplaceSET("SET0100A", "Amy-EC-Act1");
	ReplaceSET("SET0101A", "Amy-EC-Act2");
	ReplaceSET("SET0102A", "Amy-EC-Act3");
	ReplaceSET("SET0103A", "Amy-EC-Chao");
	ReplaceSET("SET0104A", "Amy-EC-Gamma");

	ReplaceCAM("CAM0100A", "CAM0100A");
	ReplaceCAM("CAM0101A", "CAM0101A");
	ReplaceCAM("CAM0102A", "CAM0102A");
	ReplaceCAM("CAM0104A", "CAM0104A");
	helperFunctions.RegisterStartPosition(Characters_Amy, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, EC3_StartPositions[0]);

	//Big
	ReplaceSET("SET0100B", "Big-EC-Act1");
	ReplaceSET("SET0101B", "Big-EC-Act2");
	ReplaceSET("SET0102B", "Big-EC-Act3");
	ReplaceSET("SET0103B", "Big-EC-Chao");
	ReplaceSET("SET0104B", "Big-EC-Gamma");

	ReplaceCAM("CAM0100B", "CAM0100B");
	ReplaceCAM("CAM0101B", "CAM0101B");
	ReplaceCAM("CAM0102B", "CAM0102B");
	ReplaceCAM("CAM0104B", "CAM0104B");
	helperFunctions.RegisterStartPosition(Characters_Big, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, EC3B_StartPositions[0]);

	//Gamma
	ReplaceSET("SET0100E", "Gamma-EC-Act1");
	ReplaceSET("SET0101E", "Gamma-EC-Act2");
	ReplaceSET("SET0102E", "Gamma-EC-Act3");
	ReplaceSET("SET0103E", "Gamma-EC-Chao");
	ReplaceSET("SET0104E", "Gamma-EC-Gamma");

	ReplaceCAM("CAM0100E", "CAM0100E");
	ReplaceCAM("CAM0101E", "CAM0101E");
	ReplaceCAM("CAM0102E", "CAM0102E");
	ReplaceCAM("CAM0104E", "CAM0104E");
	helperFunctions.RegisterStartPosition(Characters_Gamma, EC1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, EC2_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Gamma, EC3_StartPositions[0]);
}