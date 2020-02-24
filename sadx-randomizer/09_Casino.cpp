#include "stdafx.h"
#include "Utils.h"
#include "Casino.h"
#include "Chao.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Casinopolis\\" B ".bin")
#define ReplaceCAM(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")

ObjectMaster* TriggerCasino = nullptr;

void TriggerCasinoChao_Main(ObjectMaster* obj) {

	if (IsPlayerInsideSphere(&obj->Data1->Position, 25))
	{
		PlayVoice_R(5004);
		ForcePlayerAction(0, 12);

		if (++obj->Data1->Index == 5)
		{
			ForcePlayerAction(0, 24);
			PositionPlayer(0, -1541.241, 70.75, 2636.955);
		}
	}
}

void TriggerCasinoChao_Delete()
{
	DeleteObject_(TriggerCasino);
	TriggerCasino = nullptr;
}


void FixFlipperCharacterPosition() {

	if (CurrentLevel == LevelIDs_Casinopolis && CurrentAct > 1)
	{
		if (CurrentCharacter == Characters_Sonic)
			ForcePlayerAction(0, 0x2d);
		else
			ForcePlayerAction(0, 24);
	}

}

void IncreaseRings_R() { //increase the amount of ring get in the pinball to make this section shorter.

	if (CurrentLevel == LevelIDs_Casinopolis && CurrentAct > 1)
		Rings += 1;

	PlaySound(7, 0x0, 0x0, 0x0);
}

void FixShakeoffGarbageAction() { //This make the game crash as Tails.

	ObjectMaster* P1 = GetCharacterObject(0);
	if (P1 != nullptr && P1->Data1->CharID != Characters_Sonic)
		return;
	else
		ForcePlayerAction(0, 0x2a);

	return;
}

void Casino_Layout() {

	CurrentLevelLayout = randomizedSets[levelCount].MissionLayout;

	if (CurrentAct == 1)
	{
		switch (CurrentLevelLayout)
		{
		case Mission1:
		case Mission1_Variation:
		default:
			Race = true;
			LoadSetFile(0, "0900"); //M1 Race
			LoadSetFile(1, "0908"); //M1 Race
			CurrentLevelLayout = Mission1_Variation;
			break;
		case Mission2_100Rings:
			Race = false;
			LoadSetFile(0, "0905"); //M2
			LoadSetFile(1, "0908"); //M2
			break;
		case Mission3_LostChao:
			Race = false;
			LoadSetFile(0, "0904"); //M3
			LoadSetFile(1, "0907"); //M3
			break;
		}

		LoadSetFile(2, "0902");
		LoadSetFile(3, "0903");
		LoadCamFile(0, "0900");
		LoadCamFile(1, "0901");
		LoadCamFile(2, "0902");
		LoadCamFile(3, "0903");
	}

	if (CurrentAct == 0)
	{
		if (CurrentCharacter == Characters_Sonic && !Vanilla)
		{
			Race = false;
			LoadSetFile(0, "0906"); //Knux Treasure Hunting
			LoadSetFile(1, "0901");
			TreasureHunting = true;
			CurrentLevelLayout = Mission1_Variation;
		}
		else
		{			
			switch (CurrentLevelLayout)
			{
			case Mission1:
			default:
				Race = false;
				LoadSetFile(0, "0900"); //M1
				LoadSetFile(1, "0901"); //M1
				CurrentLevelLayout = Mission1;
				break;
			case Mission1_Variation:
				if (CurrentCharacter == Characters_Knuckles && !Vanilla)
				{
					Race = false;
					LoadSetFile(0, "0905"); //M2
					LoadSetFile(1, "0901"); //M2
					CurrentLevelLayout = Mission2_100Rings; //go to M2 instead
				}
				else
				{
					Race = false;
					LoadSetFile(0, "0906"); //Knux Treasure Hunting
					LoadSetFile(1, "0901");
				}
				break;
			case 2:
				Race = false;
				LoadSetFile(0, "0905"); //M2
				LoadSetFile(1, "0901"); //M2
				break;
			case 3:
				Race = false;
				LoadSetFile(0, "0904"); //M3
				LoadSetFile(1, "0901"); //M3
				break;
			}
		}
	}

		LoadSetFile(2, "0902");
		LoadSetFile(3, "0903");

		if (CurrentLevelLayout == Mission1_Variation && CurrentAct == 0) //Knuckles camera
		{
			TreasureHunting = true;
			SetRNGKnuckles();
			LoadCamFile(0, "0906");
		}
		else
		{
			LoadCamFile(0, "0900"); //Sonic Camera
		}

		LoadCamFile(1, "0901");
		LoadCamFile(2, "0902");
		LoadCamFile(3, "0903");
	

	if (Race)
		SelectBarRace();

	FixGoldenAndCoin();

	return;
}

void FixInvisibleWall() {

	//if Sonic layout, add an invisible wall, if not, return.
	if (CurrentLevelLayout != 1)
	{
		LoadObject((LoadObj)2, 6, InvisibleWallCasino);
	}

	return;
}

void FixGoldenAndCoin() {

	//if Knuckles layout, move the coin in the emerald room and display Sonic Golden Statue, else restore the original function.
	if (CurrentLevelLayout == 1 && CurrentAct == 0)
	{
		WriteData<1>((void*)0x5c4425, 0x74); //Coin position

		if (CurrentCharacter == Characters_Gamma)
			WriteData<1>((void*)0x5c4232, 0x74); //don't display golden statue
		else
			WriteData<1>((void*)0x5c4232, 0x75); //display golden statue when not Sonic/Gamma
	}
	else
	{
		WriteData<1>((void*)0x5c4425, 0x75); //restore original function coin position
		WriteData<1>((void*)0x5cef47, 0x75);

		if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Knuckles)
			WriteData<1>((void*)0x5c4232, 0x75); //don't display golden statue/ Fix Crash
		else
			WriteData<1>((void*)0x5c4232, 0x74); //display golden statue*/


	}

	if (CurrentAct == 0 && !TreasureHunting)
	{
		if (CurrentCharacter == Characters_Gamma)
			WriteData<1>((void*)0x5D118B, 0x2); //Fix gamma pinball teleportation
		else
			WriteData<1>((void*)0x5D118B, 0x1); //Restore original function.
	}

	return;
}




void __cdecl Casino_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteData<5>((void*)0x422ef4, 0x90);
	WriteData<5>((void*)0x422f03, 0x90);
	WriteData<5>((void*)0x422f12, 0x90);
	WriteData<5>((void*)0x422f21, 0x90);
	WriteData<5>((void*)0x422f2d, 0x90);
	WriteData<5>((void*)0x422f3c, 0x90);
	WriteData<5>((void*)0x422f4b, 0x90);

	WriteCall((void*)0x422f5a, Casino_Layout);
	
	WriteData<1>((void*)0x5c0595, 0x08); //make pinball working for Knuckles
	WriteData<1>((void*)0x5c0615, 0x08); //make pinball working for Knuckles
	WriteData<1>((void*)0x5C0695, 0x08); //Allow Knuckles to leave the garbage. (why is this checked anyway?)
	WriteData<1>((void*)0x5c4424, 0x08); //Fix coin (knuckles layout)
	WriteData<2>((void*)0x5d049e, 0x90); //Fix Invisible wall when not Sonic. (drop ring Emerald room.)
	
	WriteCall((void*)0x5d04a9, FixInvisibleWall); //Add invisible wall if sonic version, otherwise remove it.
	WriteCall((void*)0x5dacc8, FixFlipperCharacterPosition);
	WriteCall((void*)0x5d6914, FixFlipperCharacterPosition);
	WriteCall((void*)0x5d6997, FixFlipperCharacterPosition);
	WriteCall((void*)0x5da671, FixFlipperCharacterPosition);
	WriteCall((void*)0x5c14f5, IncreaseRings_R);
	
	WriteCall((void*)0x5c5906, FixShakeoffGarbageAction);

	CasinoObjects_Init(path, helperFunctions);

	//Sonic
	ReplaceSET("SET0900S", "Sonic-Casino-Act1");
	ReplaceSET("SET0901S", "Sonic-Casino-Act2");
	ReplaceSET("SET0904S", "Sonic-Casino-Chao");
	ReplaceSET("SET0905S", "Sonic-Casino-Rings");
	ReplaceSET("SET0906S", "Sonic-Casino-Knux");
	ReplaceSET("SET0907S", "Sonic-Casino-Chao2");
	ReplaceSET("SET0908S", "Sonic-Casino-T");

	ReplaceCAM("CAM0900S", "CAM0900S");
	ReplaceCAM("CAM0901S", "CAM0901S");
	ReplaceCAM("CAM0906S", "CAM0906S");

	helperFunctions.RegisterStartPosition(Characters_Sonic, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Sonic, Casino2_StartPositions[0]);

	//Tails
	ReplaceSET("SET0900M", "Tails-Casino-Act1");
	ReplaceSET("SET0901M", "Tails-Casino-Act2");
	ReplaceSET("SET0904M", "Tails-Casino-Chao");
	ReplaceSET("SET0905M", "Tails-Casino-Rings");
	ReplaceSET("SET0906M", "Tails-Casino-Knux");
	ReplaceSET("SET0907M", "Tails-Casino-Chao2");
	ReplaceSET("SET0908M", "Tails-Casino-T");

	ReplaceCAM("CAM0900M", "CAM0900M");
	ReplaceCAM("CAM0901M", "CAM0901M");
	ReplaceCAM("CAM0906M", "CAM0906M");
	helperFunctions.RegisterStartPosition(Characters_Tails, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Tails, Casino2_StartPositions[0]);

	//Knuckles
	ReplaceSET("SET0900K", "Knux-Casino-Act1");
	ReplaceSET("SET0901K", "Knux-Casino-Act2");
	ReplaceSET("SET0904K", "Knux-Casino-Chao");
	ReplaceSET("SET0905K", "Knux-Casino-Rings");
	ReplaceSET("SET0906K", "Knux-Casino-Knux");
	ReplaceSET("SET0907K", "Knux-Casino-Chao2");
	ReplaceSET("SET0908K", "Knux-Casino-T");

	ReplaceCAM("CAM0900K", "CAM0900K");
	ReplaceCAM("CAM0901K", "CAM0901K");
	ReplaceCAM("CAM0906K", "CAM0906K");
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Knuckles, Casino2_StartPositions[0]);

	//Amy
	ReplaceSET("SET0900A", "Amy-Casino-Act1");
	ReplaceSET("SET0901A", "Amy-Casino-Act2");
	ReplaceSET("SET0904A", "Amy-Casino-Chao");
	ReplaceSET("SET0905A", "Amy-Casino-Rings");
	ReplaceSET("SET0906A", "Amy-Casino-Knux");
	ReplaceSET("SET0907A", "Amy-Casino-Chao2");
	ReplaceSET("SET0908A", "Amy-Casino-T");

	ReplaceCAM("CAM0900A", "CAM0900A");
	ReplaceCAM("CAM0901A", "CAM0901A");
	ReplaceCAM("CAM0906A", "CAM0906A");
	helperFunctions.RegisterStartPosition(Characters_Amy, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Amy, Casino2_StartPositions[0]);

	//Big
	ReplaceSET("SET0900B", "Big-Casino-Act1");
	ReplaceSET("SET0901B", "Big-Casino-Act2");
	ReplaceSET("SET0904B", "Big-Casino-Chao");
	ReplaceSET("SET0905B", "Big-Casino-Rings");
	ReplaceSET("SET0906B", "Big-Casino-Knux");
	ReplaceSET("SET0907B", "Big-Casino-Chao2");
	ReplaceSET("SET0908B", "Big-Casino-T");

	ReplaceCAM("CAM0900B", "CAM0900B");
	ReplaceCAM("CAM0901B", "CAM0901B");
	ReplaceCAM("CAM0906B", "CAM0906B");
	helperFunctions.RegisterStartPosition(Characters_Big, Casino1_StartPositions[0]);
	helperFunctions.RegisterStartPosition(Characters_Big, Casino2_StartPositions[0]);

	//Gamma
	ReplaceSET("SET0900E", "Gamma-Casino-Act1");
	ReplaceSET("SET0901E", "Gamma-Casino-Act2");
	ReplaceSET("SET0904E", "Gamma-Casino-Chao");
	ReplaceSET("SET0905E", "Gamma-Casino-Rings");
	ReplaceSET("SET0906E", "Gamma-Casino-Knux");
	ReplaceSET("SET0907E", "Gamma-Casino-Chao2");
	ReplaceSET("SET0908E", "Gamma-Casino-T");

	ReplaceCAM("CAM0900E", "CAM0900E");
	ReplaceCAM("CAM0901E", "CAM0901E");
	ReplaceCAM("CAM0906E", "CAM0906E");
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
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG " } /* "O FROG " */,
	{ 14, 3, 1, 2250000, 0, (ObjectFuncPtr)0x618030, "O FLYST" } /* "O FLYST" */
};

ObjectList CasinopolisObjectList = { arraylengthandptrT(CasinopolisObjectList_list, int) };


PVMEntry CasinopolisObjectTextures[] = {
	{ "OUM", (TexList*)0x9334EC },
	{ "KUJA", (TexList*)0x93142C },
	{ "MILESRACE", (TexList*)0x91BFC0 },
	{ "SUPI_SUPI", (TexList*)0x96F518 },
	{ "TUBA", (TexList*)0x92F2BC },
	{ "KOAR", (TexList*)0x9359B4 },
	{ "USA", (TexList*)0x93CF74 },
	{ "KAOS_EME", (TexList*)0xC3FE20 },
	{ "UNI_A_UNIBODY", (TexList*)0x96CB5C },
	{ "TOGEBALL_TOGEBALL", (TexList*)0x96BC54 },
	{ "OBJ_HIGHWAY", (TexList*)0x26703F0 },
	{ "OBJ_HIGHWAY2", (TexList*)0x26706AC },
	{ "UNI_A_UNIBODY", (TexList*)0x96CB5C },
	{ 0 }
};



void __cdecl CasinoObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_Casinopolis * 8 + 0] = &CasinopolisObjectList;
	ObjLists[LevelIDs_Casinopolis * 8 + 1] = &CasinopolisObjectList;
	TexLists_Obj[LevelIDs_Casinopolis] = CasinopolisObjectTextures;
}