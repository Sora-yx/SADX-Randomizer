#include "stdafx.h"
#include "Utils.h"
#include "IceCap.h"
#include "RandomHelpers.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#define ReplaceSET(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\levels\\Ice Cap\\" B ".bin")
#define ReplaceCAM(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" D ".bin")


void IC_Layout() {

	Load_ObjectsCommon();

	if (CurrentStageVersion != BigVersion)
	{
		if (CurrentCharacter > Characters_Tails)
		{
			WriteCall((void*)0x4eda00, ICAct3Position); //Skip snowboard cutscene when not sonic or tails.
			WriteCall((void*)0x4e9415, Load_Cart_R); //Load Cart in act 3
			WriteCall((void*)0x4e95dc, Delete_Cart); //Fix Delete Cart at the end of Ice Cap

			WriteCall((void*)0x4e9de1, DisableController_R);
			WriteData<1>((void*)0x4E9DE0, 0x08); //Cutscene skip

			WriteData<1>((void*)0x798306, 0x84); //Jump auto in the cart
			WriteData<1>((void*)0x7983c4, 0x7F);	
		}
		else //restore original values
		{
			WriteCall((void*)0x4e9415, DisableTimeThing);
			WriteCall((void*)0x4e9de1, DisableController_R);
			WriteData<1>((void*)0x4E9DE0, 0x04);
			WriteCall((void*)0x4eda00, DisableController);
		}
	}


	LoadSetFile(0, "0810"); //M1
	LoadSetFile(1, "0811"); //M1

	switch (CurrentStageVersion)
	{
		case SonicVersion:
		default:
			CurrentStageVersion = SonicVersion;
			LoadSetFile(2, "0812");
			break;
		case TailsVersion:
			LoadSetFile(2, "0814"); //Tails Race
			if (CurrentMission < Mission2_100Rings)
				Race = true;
			else
				Race = false;
			break;	
	}
	
	LoadSetFile(3, "0813"); 

	LoadCamFile(0, "0800");
	LoadCamFile(1, "0801");
	LoadCamFile(2, "0802");
	LoadCamFile(3, "0803");

	if (Race)
		SelectBarRace();

	return;
}



int IC_ReturnCharacter() { //trick the game to make it think we are playing Sonic this will make spawn the Ice Cave as Big.

	if (CurrentCharacter != Characters_Big)
		return GetCurrentCharacterID();
	else
		return (unsigned int)Characters_Sonic;
}


//Prevent the game to disable control for cutscene skip Ice Cap act 3 (Cart thing.)

void DisableController_R() {

	if (CurrentCharacter > Characters_Tails)
	{
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		{
			return EnableController(0);
		}
	}
	else
	{
		ObjectMaster* GetChara = GetCharacterObject(0);
		ObjectMaster* GetAI = GetCharacterObject(1);

		if (isAIActive && GetAI != nullptr)
			GetAI->Data1->Position.z = GetChara->Data1->Position.z + 100;

		return DisableController(0);
	}
}

//Add rings every Checkpoint for cart speed.
void AddRingIceCap() {
	PlaySound(0x15, 0, 0, 0);

	if (CurrentLevel == LevelIDs_IceCap && CurrentCharacter > Characters_Tails)
		AddRings(5);

	return;
}


void ICAct3Position() {
	ObjectMaster* GetChara = GetCharacterObject(0);

	if (CurrentCharacter > Characters_Tails)
	{
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		{
			TimeThing = 1;
			EnableController(0);
			PlayMusic(MusicIDs_icecap3);
		}
	}

	return;
}

void FixTailsVictoryIC() {

	//Prevent AI to make Tails lose when hiting the capsule if we aren't racing.

	if (CurrentCharacter == Characters_Tails && !Race)
		SetTailsRaceVictory();
	else
		SetOpponentRaceVictory();

	return;
}

void __cdecl IceCap_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteCall((void*)0x4e92e7, IC_ReturnCharacter);
	WriteCall((void*)0x4e9802, IC_ReturnCharacter);
	WriteCall((void*)0x4ec065, AddRingIceCap);
	WriteCall((void*)0x4ecf8f, FixTailsVictoryIC);

	WriteData<5>((void*)0x422e66, 0x90);
	WriteData<5>((void*)0x422e75, 0x90);
	WriteData<5>((void*)0x422e84, 0x90);
	WriteData<5>((void*)0x422e93, 0x90);
	WriteData<5>((void*)0x422e9f, 0x90);
	WriteData<5>((void*)0x422eae, 0x90);
	WriteData<5>((void*)0x422ebd, 0x90);

	WriteCall((void*)0x422ecc, IC_Layout);

	ICObjects_Init(path, helperFunctions);

	//Sonic
	ReplaceSET("SET0810S", "Sonic-IC-Act1");
	ReplaceSET("SET0811S", "Sonic-IC-Act2");
	ReplaceSET("SET0812S", "Sonic-IC-Act3");
	ReplaceSET("SET0813S", "Sonic-IC-Big");
	ReplaceSET("SET0814S", "Sonic-IC-T");

	ReplaceCAM("CAM0800S", "CAM0800S");
	ReplaceCAM("CAM0801S", "CAM0801S");
	ReplaceCAM("CAM0802S", "CAM0802S");
	ReplaceCAM("CAM0803S", "CAM0803S");

	//Tails
	ReplaceSET("SET0810M", "Tails-IC-Act1");
	ReplaceSET("SET0811M", "Tails-IC-Act2");
	ReplaceSET("SET0812M", "Tails-IC-Act3");
	ReplaceSET("SET0813M", "Tails-IC-Big");
	ReplaceSET("SET0814M", "Tails-IC-T");


	ReplaceCAM("CAM0800M", "CAM0800M");
	ReplaceCAM("CAM0801M", "CAM0801M");
	ReplaceCAM("CAM0802M", "CAM0802M");
	ReplaceCAM("CAM0803M", "CAM0803M");


	//Knuckles
	ReplaceSET("SET0810K", "Knux-IC-Act1");
	ReplaceSET("SET0811K", "Knux-IC-Act2");
	ReplaceSET("SET0812K", "Knux-IC-Act3");
	ReplaceSET("SET0813K", "Knux-IC-Big");
	ReplaceSET("SET0814K", "Knux-IC-T");

	ReplaceCAM("CAM0800K", "CAM0800K");
	ReplaceCAM("CAM0801K", "CAM0801K");
	ReplaceCAM("CAM0802K", "CAM0802K");
	ReplaceCAM("CAM0803K", "CAM0803K");


	//Amy
	ReplaceSET("SET0810A", "Amy-IC-Act1");
	ReplaceSET("SET0811A", "Amy-IC-Act2");
	ReplaceSET("SET0812A", "Amy-IC-Act3");
	ReplaceSET("SET0813A", "Amy-IC-Big");
	ReplaceSET("SET0814A", "Amy-IC-T");

	ReplaceCAM("CAM0800A", "CAM0800A");
	ReplaceCAM("CAM0801A", "CAM0801A");
	ReplaceCAM("CAM0802A", "CAM0802A");
	ReplaceCAM("CAM0803A", "CAM0803A");


	//Big
	ReplaceSET("SET0810B", "Big-IC-Act1");
	ReplaceSET("SET0811B", "Big-IC-Act2");
	ReplaceSET("SET0812B", "Big-IC-Act3");
	ReplaceSET("SET0813B", "Big-IC-Big");
	ReplaceSET("SET0814B", "Big-IC-T");

	ReplaceCAM("CAM0800B", "CAM0800B");
	ReplaceCAM("CAM0801B", "CAM0801B");
	ReplaceCAM("CAM0802B", "CAM0802B");
	ReplaceCAM("CAM0803B", "CAM0803B");


	//Gamma
	ReplaceSET("SET0810E", "Gamma-IC-Act1");
	ReplaceSET("SET0811E", "Gamma-IC-Act2");
	ReplaceSET("SET0812E", "Gamma-IC-Act3");
	ReplaceSET("SET0813E", "Gamma-IC-Big");
	ReplaceSET("SET0814E", "Gamma-IC-T");

	ReplaceCAM("CAM0800E", "CAM0800E");
	ReplaceCAM("CAM0801E", "CAM0801E");
	ReplaceCAM("CAM0802E", "CAM0802E");
	ReplaceCAM("CAM0803E", "CAM0803E");
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
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" }, /* "O FROG" */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};

ObjectList IceCapObjectList = { arraylengthandptrT(IceCapObjectList_list, int) };

PVMEntry IceCapObjectTextures[] = {
	{ "OBJ_ICECAP", (TexList*)0xE48F30 },
	{ "OBJ_ICECAP2", (TexList*)0xE48F78 },
	{ "E102TIME", (TexList*)0x91D5E0 },
	{ "E_SAI", (TexList*)0x38C8EA8 },
	{ "E_SNOWMAN", (TexList*)0x985990 },
	{ "MILESRACE", (TexList*)0x91BFC0 },
	{ "PEN", (TexList*)0x92D39C },
	{ "E_SNAKE", (TexList*)0x94E640 },
	{ "RAKO", (TexList*)0x949FC4 },
	{ "MECHA", (TexList*)0x1726108 },
	{ "MOGU", (TexList*)0x93ECEC },
	{ "KAOS_EME", (TexList*)0xC3FE20 },
	{ "SAKE", (TexList*)0x171BF60 },
	{ "GOMA", (TexList*)0x92ACE4 },
	{ "PIRANIA", (TexList*)0x1728BB8 },
	{ "NEW_BB", (TexList*)0x17126F4 },
	{ "HAMMER", (TexList*)0x1723CF4 },
	{ "SAME", (TexList*)0x172AAC4 },
	{ "UNAGI", (TexList*)0x172CD88 },
	{ "GORI", (TexList*)0x945964 },
	{ "BOARD_SCORE", (TexList*)0x9BE780 },
	{ NULL, (TexList*)0x91CBE8 },
	{ "big_kaeru", (TexList*)0x91D780 },
	{ "common-obj", &SA2_OBJ_TEXLIST },
	{ "OBJ_SHAREOBJ", &OBJ_SHAREOBJ_TEXLIST },
	{ 0 }
};

void __cdecl ICObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_IceCap * 8 + 2] = &IceCapObjectList;
	ObjLists[LevelIDs_IceCap * 8 + 3] = &IceCapObjectList;
	TexLists_Obj[LevelIDs_IceCap] = IceCapObjectTextures;
}