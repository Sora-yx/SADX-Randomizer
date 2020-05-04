#include "stdafx.h"
#include "RandomHelpers.h"


// Mission Card settings, check, texture edit.

int CurrentMissionCard;
NJS_TEXNAME MissionsText[25];
char GetCustomLayout;
extern HelperFunctions help;


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

	short cur_mission = -1;

	if (stage_id >= LevelIDs_Chaos0 || !isSA2Mission())
		return SADX_Mission;

	do {
		 //SA2 missions 100 Rings, Lost Chao 
			cur_mission = rand() % 2 + 2;
	} while (prev_mission == cur_mission || (isDuplicateMission(cur_mission, prev_mission) || !SA2M2 && cur_mission == 2 || !SA2M3 && cur_mission == 3));

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

	GetCustomLayout = 0;
	CurrentMissionCard = 0;

	if (GetLevelType == 0) { //Mission card check here

		if (CurrentLevel == LevelIDs_HedgehogHammer || CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel <= 42)
			return;

		GetCustomLayout = CurrentMission;

		if (CurrentMission < Mission2_100Rings)
		{
			if (CurrentCharacter == Characters_Amy && CurrentMission < Mission2_100Rings && CurrentStageVersion != BigVersion)
				CurrentMissionCard = BalloonCard; //grab ballon

			if (CurrentCharacter == Characters_Big && CurrentMission < Mission2_100Rings)
				CurrentMissionCard = FroggyCard; //grab Froggy

			if (CurrentCharacter != Characters_Amy && CurrentCharacter != Characters_Big && CurrentStageVersion != BigVersion)
				CurrentMissionCard = CapsuleCard;
		}
		
		switch (CurrentLevel)
		{
			case LevelIDs_EmeraldCoast:
				if (CurrentStageVersion == BigVersion || CurrentStageVersion == GammaVersion)
					CurrentMissionCard = FroggyCard; //Catch Froggy if Big or Gamma layout.
				break;	
			case LevelIDs_WindyValley:
				if (CurrentStageVersion == GammaVersion && (CurrentCharacter == Characters_Gamma))
					CurrentMissionCard = E103Card;
				break;
			case LevelIDs_TwinklePark:
				if (CurrentMission == SADX_Mission && CurrentStageVersion == BigVersion)
					CurrentMissionCard = FroggyCard;
				break;
			case LevelIDs_LostWorld:
				if (!CurrentMission)
					CurrentMissionCard = LostWorldCard; //Go to the center of the ruin.
				 if (CurrentCharacter == Characters_Amy)
					CurrentMissionCard = BalloonCard; //grab balon if Amy regardless of the mission.
				if (CurrentStageVersion == KnucklesVersion && CurrentAct == 1)
					CurrentMissionCard = EmeraldKnuxCard;
				break;
			case LevelIDs_FinalEgg:
				if (CurrentAct != 2)
				{
					if (CurrentStageVersion == SonicVersion && CurrentCharacter != Characters_Amy && CurrentCharacter != Characters_Big)
						CurrentMissionCard = CapsuleCard; //capsule

					if (CurrentMission == SADX_Mission)
						CurrentMissionCard = FinalEggCard; //Go to the center of the base.

					if (CurrentCharacter == Characters_Amy)
						CurrentMissionCard = BalloonCard; //grab balon if Amy regardless of the mission.
				}
				else
				{
					if (CurrentAct == 2 && CurrentStageVersion == GammaVersion)
						CurrentMissionCard = SonicDollCard;
				}
				break;
			case LevelIDs_RedMountain:
				if (CurrentAct == 2 && CurrentStageVersion == KnucklesVersion)
					CurrentMissionCard = EmeraldKnuxCard;
				if (CurrentMission < Mission2_100Rings && CurrentAct <= 1 && (CurrentCharacter == Characters_Gamma))
					CurrentMissionCard = E104Card; 
				break;
			case LevelIDs_SpeedHighway:
				if (Race && CurrentAct == 0)
					CurrentMissionCard = MissileRaceCard; //Eggman Race
				if (CurrentMission < Mission2_100Rings && CurrentAct == 2 && CurrentStageVersion == KnucklesVersion)
					CurrentMissionCard = EmeraldKnuxCard;
				break;
			case LevelIDs_SkyDeck:
				if (CurrentMission < Mission2_100Rings && CurrentAct == 2)
					CurrentMissionCard = EmeraldKnuxCard;
				break;
			case LevelIDs_IceCap:
				if (CurrentAct == 3 && CurrentMission < Mission2_100Rings)
					CurrentMissionCard = FroggyCard;  //Froggy
				break;
			case LevelIDs_Casinopolis:
				if (CurrentAct == 0 && CurrentStageVersion == KnucklesVersion)
					CurrentMissionCard = EmeraldKnuxCard;
				break;
			case LevelIDs_HotShelter:
				if (CurrentStageVersion == BigVersion && CurrentAct == 0)
					CurrentMissionCard = FroggyCard; //Froggy
				if (CurrentStageVersion == GammaVersion && CurrentAct == 2 && CurrentCharacter == Characters_Gamma)
					CurrentMissionCard = E105Card;
				break;
			default:
				if (CurrentCharacter == Characters_Amy && CurrentMission < Mission2_100Rings && CurrentStageVersion != BigVersion)
					CurrentMissionCard = BalloonCard; //grab ballon
				if (CurrentCharacter == Characters_Big && CurrentMission < Mission2_100Rings)
					CurrentMissionCard = FroggyCard; //grab Froggy
				if (CurrentCharacter != Characters_Amy && CurrentCharacter != Characters_Big && (CurrentStageVersion != BigVersion))
					CurrentMissionCard = CapsuleCard;
				break;
		}

		if (Race && (CurrentLevel == LevelIDs_SkyDeck || CurrentLevel == LevelIDs_Casinopolis || CurrentLevel == LevelIDs_IceCap && CurrentAct == 2 || CurrentLevel == LevelIDs_WindyValley && CurrentAct == 2))
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

		if (!Race)
		{
			if (GetCustomLayout == Mission2_100Rings) //100 Rings
				CurrentMissionCard = RingsCard;

			if (GetCustomLayout == Mission3_LostChao) //Lost Chao
				CurrentMissionCard = LostChaoCard;
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

int DisplayTitleCard_r() {
	if (GetLevelType == 0) {
		return DisplayTitleCard();
	}
	else {
		if (++TitleCardCounter > TitleCardDispTime) return 1;
	}

	return 0;
}

int LoadTitleCardTexture_r(int minDispTime) {
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

	if (CurrentLevel > 14 && CurrentLevel < 40) {
		GetLevelType = 1;
	}
	else {
		GetLevelType = 0;

		TitleCardDispTime = 180;
		if (minDispTime) {
			TitleCardDispTime = minDispTime;
		}

		LoadPVM("textures\\RandomTitleCard", &CurrentCardTexture);
		CurrentCardTexturePtr = &CurrentCardTexture;
	}

	return 1;
}


void TitleCard_Init() {

	if (RNGStages)
	{
		WriteJump(j_LoadTitleCardTexture, LoadTitleCardTexture_r);
		WriteJump(j_DisplayTitleCard, DisplayTitleCard_r);
	}
	WriteJump(LoadStageMissionImage, LoadStageMissionImage_r);
	WriteCall((void*)0x4284ac, StageMissionImage_result);
	WriteCall((int*)0x4284cd, CheckMissionRequirements_r);
	help.ReplaceFile("system\\Missions.pvm", "system\\textures\\Missions.pvmx");
}


int FlashScreenTimer = 0;

void FlashScreen(ObjectMaster* obj) {

	EntityData1* data = obj->Data1;

		if (++data->InvulnerableTime > 80) {

			int color = 0x00000000;
			ScreenFade_Color = *(NJS_COLOR*)&color;
			CheckThingButThenDeleteObject(obj);
		}
		else {
			int color = 0xFFFFFFFF;                            
			ScreenFade_Color = *(NJS_COLOR*)&color;

			if (data->InvulnerableTime < 120) {
				if (data->InvulnerableTime < 60) {
					data->CharID += 4;
					ScreenFade_Color.argb.a = data->CharID;
				}
				else {
					ScreenFade_Color.argb.a = 0xFF;
				}
			}
			else {
				data->CharID -= 20;
				ScreenFade_Color.argb.a = data->CharID;
			}

			ScreenFade_DrawColor();
		}
}



void MissionResultCheck() {

	if (Rings >= 100 && CurrentMission == Mission2_100Rings || CurrentStageVersion == KnucklesVersion && KnuxCheck >= 3 && CurrentCharacter != Characters_Knuckles)
	{
		ObjectMaster* p1 = GetCharacterObject(0);
		EntityData1* ent;
		ent = p1->Data1;
		ObjectMaster* Flash = nullptr;

		if (p1->Data1->Action >= 1 && p1->Data1->Action <= 3 && TimeThing != 0) {

			ent->InvulnerableTime = 0;
			if (!SonicRand && !MetalSonicFlag)
				ent->Action = 0; //fix potential crash
			ent->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);

			if (++ent->InvulnerableTime == 1) //wait 1 frame before loading level result
			{
				if (!Flash)
					Flash = LoadObject(LoadObj_Data1, 1, FlashScreen);

				if (!SonicRand && !MetalSonicFlag)
					p1->Data1->Action = 1; //fix victory pose

				LoadLevelResults_r();
				return;
			}
		}
	}
	
	return;
}

