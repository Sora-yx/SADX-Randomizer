#include "stdafx.h"


// Mission Card settings, check, texture edit.

short CurrentMission = 0;
int CurrentMissionCard;
NJS_TEXNAME MissionsText[25];
NJS_TEXNAME TitleCard[8];
static NJS_TEXLIST TitleCardTex = { arrayptrandlength(TitleCard) };
char GetCustomLayout;
//extern HelperFunctions help;
static Trampoline* LoadTitleCardTexture_t = nullptr;

bool isSA2Mission() {

	if (SA2M2 || SA2M3)
		return true;

	return false;
}

bool isDuplicateMission(short curMission, short prevMission) {

	if (curMission == 0 && prevMission == 1 || prevMission == 0 && curMission == 1)
		return true;

	return false;
}

short prev_mission = -1;

short randomSA2Mission(short stage_id) {

	short cur_mission = 0;

	if (stage_id >= LevelIDs_Chaos0 || !isSA2Mission())
		return SADX_Mission;

	do {
		//SA2 missions 100 Rings, Lost Chao 
		cur_mission = rand() % 4;
	} while (prev_mission == cur_mission || cur_mission == 1 || !SA2M2 && cur_mission == 2 || !SA2M3 && cur_mission == 3);

	prev_mission = cur_mission;
	return cur_mission;
}


int CheckMissionRequirements_r() {

	GetCustomLayout = CurrentMission;

	if (CurrentLevel > LevelIDs_Chaos0)
		return 0;

	if (GetCustomLayout == Mission2_100Rings) //100 Rings check
		return (int)(99 < (short)Rings);

	if (GetCustomLayout == Mission3_LostChao) //Lost Chao
		return 1;

	return 1;
}


void PauseMenuFix() {
	//Display Current Mission Information
	if (CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel < LevelIDs_Chaos0)
	{
		SetDebugFontSize(13.0f * (float)VerticalResolution / 480.0f);

		if (CurrentStageVersion == KnucklesVersion && CurrentMission < Mission2_100Rings)
			DisplayDebugString(NJM_LOCATION(2, 6), "Current Mission: M1 (Treasure Hunting)");

		if (CurrentMission < Mission2_100Rings && CurrentStageVersion != KnucklesVersion)
			DisplayDebugString(NJM_LOCATION(2, 6), "Current Mission: M1 (Beat the Stage)");

		if (CurrentMission == Mission2_100Rings)
			DisplayDebugString(NJM_LOCATION(2, 6), "Current Mission: M2 (100 Rings)");

		if (CurrentMission == Mission3_LostChao)
			DisplayDebugString(NJM_LOCATION(2, 6), "Current Mission: M3 (Lost Chao)");
	}

	//set gamemode to adventure when the player select quit option, so you will go back to the title screen properly.
	if (GameMode != GameModes_Trial && RNGStages)
	{
		if (PauseSelection == 3)
			GameMode = GameModes_Adventure_Field;
		else
			GameMode = GameModes_Adventure_ActionStg;
	}
}


void LoadStageMissionImage_r() {


	if (GetLevelType == 0) { //Mission card check here

		if (CurrentLevel == LevelIDs_HedgehogHammer || CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel <= 42)
			return;

		GetCustomLayout = CurrentMission;

		if (CurrentMission < Mission2_100Rings)
		{
			if (CurrentCharacter == Characters_Amy && CurrentStageVersion != BigVersion)
				CurrentMissionCard = BalloonCard; //grab ballon

			if (CurrentCharacter == Characters_Big)
				CurrentMissionCard = FroggyCard; //grab Froggy

			if (CurrentCharacter != Characters_Amy && CurrentCharacter != Characters_Big)
				CurrentMissionCard = CapsuleCard;

			if (CurrentMission == SADX_Mission) {

				if (CurrentStageVersion == BigVersion)
					CurrentMissionCard = FroggyCard;

				if (CurrentStageVersion == KnucklesVersion)
					CurrentMissionCard = EmeraldKnuxCard;
			}
		}

		switch (CurrentLevel)
		{
			case LevelIDs_EmeraldCoast:
				if (CurrentStageVersion == GammaVersion)
					CurrentMissionCard = FroggyCard; //Catch Froggy if Big or Gamma layout.
				break;	
			case LevelIDs_WindyValley:
				if (CurrentStageVersion == GammaVersion)
					CurrentMissionCard = E103Card;
				break;
			case LevelIDs_LostWorld:
				if (CurrentStageVersion != KnucklesVersion && !CurrentMission && CurrentCharacter != Characters_Amy && CurrentCharacter != Characters_Big)
					CurrentMissionCard = LostWorldCard; //Go to the center of the ruin.
				break;
			case LevelIDs_FinalEgg:
					if (CurrentStageVersion == SonicVersion)
						CurrentMissionCard = FinalEggCard; //Go to the center of the base.

					if (CurrentAct == 2 && CurrentStageVersion == GammaVersion)
						CurrentMissionCard = SonicDollCard;	
				break;
			case LevelIDs_RedMountain:
				if (CurrentMission < Mission2_100Rings && (CurrentCharacter == Characters_Gamma) || CurrentStageVersion == GammaVersion)
					CurrentMissionCard = E104Card; 
				break;
			case LevelIDs_SpeedHighway:
				if (Race && CurrentAct == 0)
					CurrentMissionCard = MissileRaceCard; //Eggman Race
				break;
			case LevelIDs_HotShelter:
				if (CurrentStageVersion == GammaVersion && CurrentAct == 2 && CurrentCharacter == Characters_Gamma)
					CurrentMissionCard = E105Card;
				break;
		}


		if (GetCustomLayout == Mission2_100Rings) //100 Rings
			CurrentMissionCard = RingsCard;

		if (GetCustomLayout == Mission3_LostChao) //Lost Chao
			CurrentMissionCard = LostChaoCard;

		if (Race && CurrentStageVersion == TailsVersion && CurrentLevel != LevelIDs_SpeedHighway)
		{
			switch (AIRace)
			{
			case Characters_Eggman:
				CurrentMissionCard = EggmanRaceCard;
				break;
			case Characters_Tails:
				CurrentMissionCard = TailsRaceCard;
				break;
			case Characters_Knuckles:
				CurrentMissionCard = KnuxRaceCard;
				break;
			case Characters_Tikal:
				CurrentMissionCard = TikalRaceCard;
				break;
			case Characters_Amy:
				CurrentMissionCard = AmyRaceCard;
				break;
			case Characters_Gamma:
				CurrentMissionCard = GammaRaceCard;
				break;
			case Characters_Big:
				CurrentMissionCard = BigRaceCard;
				break;
			default:
				CurrentMissionCard = SonicRaceCard;
				break;
			}
		}

		StageMissionTexlist.textures = MissionsText;
		StageMissionTexlist.nbTexture = LengthOfArray(MissionsText);
		LoadPVM("Missions", &StageMissionTexlist);
		MissionSpriteAnim.texid = CurrentMissionCard;

		ObjectMaster* obj = LoadObject(LoadObj_Data1, 6, (ObjectFuncPtr)0x457B60);
		obj->Data1->InvulnerableTime = 120;
		obj->Data1->Position.x = 320.0;
		obj->Data1->Position.y = 360.0;
		obj->DeleteSub = FreeStageMissionImage;
	}
}

void StageMissionImage_result() {

	if (GetLevelType == 0) { //do the mission check here
			//0 = capsule, 1 = Lost Chao, 2 = Emeralds Knux, 3 = Beat Sonic, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails, 10 = Zero, 11+ Race

		GetCustomLayout = CurrentMission;

		if (CurrentLevel >= LevelIDs_Chaos0 || CurrentLevel == LevelIDs_HedgehogHammer)
			return;

		StageMissionTexlist.textures = MissionsText;
		StageMissionTexlist.nbTexture = LengthOfArray(MissionsText);
		LoadPVM("Missions", &StageMissionTexlist);
		MissionSpriteAnim.texid = CurrentMissionCard;

		ObjectMaster* obj = LoadObject(LoadObj_Data1, 6, (ObjectFuncPtr)0x457B60);
		obj->Data1->InvulnerableTime = 120;
		obj->Data1->Position.x = 320.0;
		obj->Data1->Position.y = 240.0;
		obj->DeleteSub = FreeStageMissionImage;
	}
}



int LoadTitleCardTexture_r(int minDispTime) {

	if (!isRandoLevel() || CurrentLevel > 14) {
		CurrentCardTexturePtr = &CurrentCardTexture;
		FunctionPointer(int, original, (int minDispTime), LoadTitleCardTexture_t->Target());
		return original(minDispTime);
	}


	SoundManager_Delete2();
	dword_03b28114 = 0;
	ScreenTextureVer();
	SetFrameRateMode(1, 1);
	SetDefaultAlphaBlend();
	DisableFog();
	SetGlobalPoint2Col_Colors(0xff000000, 0xff000000, 0xff000000);
	Direct3D_SetNearFarPlanes(-1.0, -3000.0);
	TitleCardStuff = 2;
	TitleCardStuff2 = 0;

	GetLevelType = 0;

	TitleCardDispTime = 90;
	if (minDispTime)
		TitleCardDispTime = minDispTime;

	LoadPVM("RandomTitleCard", &TitleCardTex);
	CurrentCardTexturePtr = &TitleCardTex;

	return 1;
}


void DisplayTitleCard_r() {

	if (!isRandoLevel()) {
		return DisplayScreenTexture(0x4000000, HorizontalStretch * 320.00000000 + 32.00000000,
			VerticalStretch * 240.00000000, 1.00000000);
	}

	return DisplayScreenTexture(0x4000000 + CurrentCharacter, HorizontalStretch * 320.00000000 + 32.00000000, //Last number of "0x4000000" is the texture ID, the rest is used for the position/Flag
		VerticalStretch * 240.00000000, 1.00000000);
}



void TitleCard_Init() {

	if (RNGStages) {
		LoadTitleCardTexture_t = new Trampoline((int)LoadTitleCardTexture, (int)LoadTitleCardTexture + 0x5, LoadTitleCardTexture_r);
		WriteCall((void*)0x47e276, DisplayTitleCard_r);
	}

	WriteJump(LoadStageMissionImage, LoadStageMissionImage_r);
	WriteCall((void*)0x4284ac, StageMissionImage_result);
	WriteCall((int*)0x4284cd, CheckMissionRequirements_r);
}



SetLevelPosition PlayerEndPosition[50]{ //Used for M2 and Bosses

	{ SonicVersion, LevelAndActIDs_EmeraldCoast1, { 3954.57, 9.5, 365.366 }, 0x6000},
	{ SonicVersion, LevelAndActIDs_EmeraldCoast2, { 5825.86, 2, -2641.14 }, 0x4000 },
	{ BigVersion, LevelAndActIDs_EmeraldCoast3, { 6119.79, 402, 921.151 }, 0 },
	{ GammaVersion, LevelAndActIDs_WindyValley1, { 2677.56, -589, -1299.88 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley1, { 2677.56, -589, -1299.88 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley2, { -25.3528, 1800, -15.8911 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley3, { 1425.96, -2619, 1021.17 }, 0x4000 },
	{ TailsVersion, LevelAndActIDs_WindyValley3, { 1425.96, -2619, 1021.17 }, 0 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, { 646.891, 45.3108, -452.654 }, 1.0 },
	{ AmyVersion, LevelAndActIDs_TwinklePark2, { 646.891, 45.3108, -452.654}, 1.0 },
	{ BigVersion, LevelAndActIDs_TwinklePark2, { 586.078, 3, -626.673 }, 0xC000 },
	{ AmyVersion, LevelAndActIDs_TwinklePark3, { 259.408, 100, 604.734 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway1, { 2353.51, -1302.91, 1800.38 }, 0 },
	{ TailsVersion, LevelAndActIDs_SpeedHighway1, { 2353.51, -1302.91, 1800.38 }, 0 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway2, { 154.396, -19192, -19.7557 }, 0 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway3, {-226.168, 140, -1586.82 }, 0xC000 },
	{ KnucklesVersion, LevelAndActIDs_SpeedHighway3, { -226.168, 140, -1586.82 }, 6.0 },
	{ SonicVersion, LevelAndActIDs_RedMountain1, { -598.868, 1254.71, -164.334 }, 0 },
	{ SonicVersion, LevelAndActIDs_RedMountain2, { -1177.33, 433.466, 1515.36 }, 0 },
	{ GammaVersion, LevelAndActIDs_RedMountain2, { -1553, 139.435, 2145.21 }, 0 },
	{ KnucklesVersion, LevelAndActIDs_RedMountain3, { -2966.09, 884.294, -1750.13 }, 0xFFFFC000 },
	{ SonicVersion, LevelAndActIDs_SkyDeck1, {67.038, -484.717, 2548.98}, 270},
	{ TailsVersion, LevelAndActIDs_SkyDeck1, {67.038, -484.717, 2548.98}, 270},
	{ SonicVersion, LevelAndActIDs_SkyDeck2, { -420.854, 100, -2941.77 }, 0 },
	{ SonicVersion, LevelAndActIDs_SkyDeck3, { -508.999, -100, 3.30111 }, 0 },
	{ KnucklesVersion, LevelAndActIDs_SkyDeck3, { -508.999, -100, 3.30111 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_LostWorld1, { 5463.01, -2480, 996.691 }, 0 },
	{ SonicVersion, LevelAndActIDs_LostWorld2, { 7427, -2192.32, 1313.69 }, 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_LostWorld2, { 7427, -2192.32, 1313.69 }, 0 },
	{ SonicVersion, LevelAndActIDs_IceCap1, { 646.767, 425.752, 330.22 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap2, { 1553.5, 363.257, 102.466 }, 0 },
	{ SonicVersion, LevelAndActIDs_IceCap3, { -2472.33, -21746.4, -3980.41 }, 0x8800 },
	{ TailsVersion, LevelAndActIDs_IceCap3, { -2472.33, -21746.4, -3980.41 }, 0x8800 },
	{ BigVersion, LevelAndActIDs_IceCap4, { 1557.57, 363.204, 104.399 }, 0 },
	{ SonicVersion, LevelAndActIDs_Casinopolis1, { 408.814, -200.009, -170.418}, 0 },
	{ KnucklesVersion, LevelAndActIDs_Casinopolis1, 339.147, 230, -166.386 },
	{ SonicVersion, LevelAndActIDs_Casinopolis2, { -1570.98, -2205, 2646.02 }, 0 },
	{ TailsVersion, LevelAndActIDs_Casinopolis2, {-1570.98, -2205, 2646.02 }, 0 },
	{ SonicVersion, LevelAndActIDs_FinalEgg1, { 2083.96, 197.99, -1398.53}, 0 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, { 1271.06, -232, -1513.3 }, 0xC000 },
	{ SonicVersion, LevelAndActIDs_FinalEgg2, { 1058.81, -1614.85, -951.257 }, 0xC000 },
	{ SonicVersion, LevelAndActIDs_FinalEgg3, { 1815.14, -3173.87, -274.59 }, 0x8000 },
	{ GammaVersion, LevelAndActIDs_FinalEgg3, { 1815.14, -3173.87, -274.59 }, 0 },
	{ AmyVersion, LevelAndActIDs_HotShelter1, { -426.892, 80, -705.821 }, 0x4000 },
	{ BigVersion, LevelAndActIDs_HotShelter1, { -426.892, 80, -705.821 }, 0x4000 },
	{ AmyVersion, LevelAndActIDs_HotShelter2, { 933.355, 428.844, -2836.94 }, 0x4000 },
	{ GammaVersion, LevelAndActIDs_HotShelter3, { -841.37, 582.239, -2689.82 }, 0xC000 },
	{ BossVersion, LevelAndActIDs_EggHornet, { 1016.954, 132.8002, 984.1979 }, 0xC000 },
	{ SonicVersion, LevelAndActIDs_Chaos6, { 1.125, 750.75, -384.625 }, 0xC000 },
	{ BossVersion, LevelAndActIDs_Zero, { -131, 745, -385 }, 0xC000 },
};


void MissionResultCheck() {

	if (CurrentLevel < LevelIDs_EmeraldCoast || CurrentLevel > LevelIDs_HotShelter)
		return;

	if (Rings >= 100 && CurrentMission == Mission2_100Rings || CurrentStageVersion == KnucklesVersion && KnuxCheck >= 3 && CurrentCharacter != Characters_Knuckles)
	{
		int curAction = EntityData1Ptrs[0]->Action;
		ObjectMaster* Flash = nullptr;

		if (TimeThing != 0) {
			if ((EntityData1Ptrs[0]->Status & Status_Ground | Status_Unknown1) || CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0) {

				CharObj2Ptrs[0]->Speed.x = 1;
				if (CurrentLevel != LevelIDs_TwinklePark)
					ForcePlayerAction(0, 24);
				EntityData1Ptrs[0]->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);

				if (!Flash)
					Flash = LoadObject(LoadObj_Data1, 1, FlashScreen);

				if (!SonicRand && !MetalSonicFlag)
					EntityData1Ptrs[0]->Action = 1; //fix victory pose

				if (CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_Zero)
				{
					for (int i = 0; i < LengthOfArray(PlayerEndPosition); i++)
					{
						if (CurrentMission == Mission2_100Rings && CurrentLevel == ConvertLevelActsIDtoLevel(PlayerEndPosition[i].LevelID) && CurrentAct == ConvertLevelActsIDtoAct(PlayerEndPosition[i].LevelID) && CurrentStageVersion == PlayerEndPosition[i].version)
						{
							EntityData1Ptrs[0]->Position = PlayerEndPosition[i].Position;
							EntityData1Ptrs[0]->Rotation.y = PlayerEndPosition[i].YRot;
							break;
						}
					}
				}

				LoadLevelResults_r();
			}
		}

		return;
	}
}

