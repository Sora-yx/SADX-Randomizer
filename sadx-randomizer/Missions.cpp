#include "stdafx.h"
#include "RandomHelpers.h"


// Mission Card settings, check, texture edit.

int CurrentMission;
NJS_TEXNAME MissionsText[25];
char GetCustomLayout;
extern HelperFunctions help;

int CheckMissionRequirements_r() {

	GetCustomLayout = CurrentLevelLayout;

	if (CurrentLevel > LevelIDs_Chaos0)
		return 0;

	if (GetCustomLayout == Mission2_100Rings) //100 Rings check
		return (int)(99 < (short)Rings);

	if (GetCustomLayout == Mission3_LostChao) //Lost Chao
		return 1;

	return 1;
}

int IsSA2MissionAllowed() {

	if (!SA2M2 && !SA2M3)
		return false;
	else
		return true;
}

void LoadStageMissionImage_r() {

	GetCustomLayout = 0;
	CurrentMission = 0;

	if (GetLevelType == 0) { //Mission card check here

		if (CurrentLevel == LevelIDs_HedgehogHammer || CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel <= 42)
			return;

		GetCustomLayout = CurrentLevelLayout;

		if (CurrentLevelLayout < Mission2_100Rings)
		{
			if (CurrentCharacter == Characters_Amy && CurrentLevelLayout < Mission2_100Rings && CurrentStageVersion != BigHS)
				CurrentMission = BalloonCard; //grab ballon

			if (CurrentCharacter == Characters_Big && CurrentLevelLayout < Mission2_100Rings)
				CurrentMission = FroggyCard; //grab Froggy

			if (CurrentCharacter != Characters_Amy && CurrentCharacter != Characters_Big && (CurrentStageVersion != BigHS || CurrentStageVersion != BigTP))
				CurrentMission = CapsuleCard;
		}
		
		switch (CurrentLevel)
		{
		case LevelIDs_EmeraldCoast:
			if (CurrentAct == 2 && CurrentLevelLayout <= Mission1_Variation || CurrentAct == 0 && CurrentLevelLayout == Mission1_Variation)
				CurrentMission = FroggyCard; //Catch Froggy if Big or Gamma layout.
			break;	
		case LevelIDs_WindyValley:
			if (CurrentLevelLayout == Mission1_Variation && CurrentAct == 0 && (CurrentCharacter == Characters_Gamma))
				CurrentMission = E103Card;
			break;
		case LevelIDs_TwinklePark:
			if (CurrentLevelLayout == Mission1 && CurrentAct == 1 && CurrentStageVersion == BigTP)
				CurrentMission = FroggyCard;
			break;
		case LevelIDs_LostWorld:
			if (!CurrentLevelLayout)
				CurrentMission = LostWorldCard; //Go to the center of the ruin.
			 if (CurrentCharacter == Characters_Amy)
				CurrentMission = BalloonCard; //grab balon if Amy regardless of the mission.
			if (TreasureHunting && CurrentAct == 1)
				CurrentMission = EmeraldKnuxCard;
			break;
		case LevelIDs_FinalEgg:
			if (CurrentAct != 2)
			{
				if (CurrentLevelLayout == Mission1_Variation && CurrentCharacter != Characters_Amy && CurrentCharacter != Characters_Big)
					CurrentMission = CapsuleCard; //capsule

				if (CurrentLevelLayout == Mission1)
					CurrentMission = FinalEggCard; //Go to the center of the base.

				if (CurrentCharacter == Characters_Amy)
					CurrentMission = BalloonCard; //grab balon if Amy regardless of the mission.
			}
			else
			{
				if (CurrentAct == 2 && CurrentLevelLayout == Mission1_Variation)
					CurrentMission = SonicDollCard;
			}
			break;
		case LevelIDs_RedMountain:
			if (CurrentAct == 2 && TreasureHunting)
				CurrentMission = EmeraldKnuxCard;
			if (CurrentLevelLayout <= Mission1_Variation && CurrentAct <= 1 && (CurrentCharacter == Characters_Gamma))
				CurrentMission = E104Card; 
			break;
		case LevelIDs_SpeedHighway:
			if (Race && CurrentAct == 0)
				CurrentMission = MissileRaceCard; //Eggman Race
			if (CurrentLevelLayout == Mission1_Variation && CurrentAct == 2 && TreasureHunting)
				CurrentMission = EmeraldKnuxCard;
			break;
		case LevelIDs_SkyDeck:
			if (CurrentLevelLayout == Mission1_Variation && CurrentAct == 2)
				CurrentMission = EmeraldKnuxCard;
			break;
		case LevelIDs_IceCap:
			if (CurrentAct == 3 && CurrentLevelLayout <= Mission1_Variation)
				CurrentMission = FroggyCard;  //Froggy
			break;
		case LevelIDs_Casinopolis:
			if (CurrentAct == 0 && CurrentLevelLayout == Mission1_Variation && TreasureHunting)
				CurrentMission = EmeraldKnuxCard;
			break;
		case LevelIDs_HotShelter:
			if (CurrentLevelLayout == Mission1_Variation && CurrentAct == 0)
				CurrentMission = FroggyCard; //Froggy
			if (CurrentLevelLayout == Mission1 && CurrentAct == 2 && CurrentCharacter == Characters_Gamma)
				CurrentMission = E105Card;
			break;
		default:
			if (CurrentCharacter == Characters_Amy && CurrentLevelLayout < Mission2_100Rings && CurrentStageVersion != BigHS)
				CurrentMission = BalloonCard; //grab ballon
			if (CurrentCharacter == Characters_Big && CurrentLevelLayout < Mission2_100Rings)
				CurrentMission = FroggyCard; //grab Froggy
			if (CurrentCharacter != Characters_Amy && CurrentCharacter != Characters_Big && (CurrentStageVersion != BigHS && CurrentStageVersion != BigTP))
				CurrentMission = CapsuleCard;
			break;
		}

		if (Race && (CurrentLevel == LevelIDs_SkyDeck || CurrentLevel == LevelIDs_Casinopolis || CurrentLevel == LevelIDs_IceCap && CurrentAct == 2 || CurrentLevel == LevelIDs_WindyValley && CurrentAct == 2))
		{
			switch (AIRace)
			{
			case Characters_Eggman:
				CurrentMission = EggmanRaceCard;
				break;
			case Characters_Tails:
				CurrentMission = TailsRaceCard;
				break;
			case Characters_Knuckles:
				CurrentMission = KnuxRaceCard;
				break;
			case Characters_Tikal:
				CurrentMission = TikalRaceCard;
				break;
			case Characters_Amy:
				CurrentMission = AmyRaceCard;
				break;
			case Characters_Gamma:
				CurrentMission = GammaRaceCard;
				break;
			case Characters_Big:
				CurrentMission = BigRaceCard;
				break;
			default:
				CurrentMission = SonicRaceCard;
				break;
			}
		}

		if (!Race)
		{
			if (GetCustomLayout == Mission2_100Rings) //100 Rings
				CurrentMission = RingsCard;

			if (GetCustomLayout == Mission3_LostChao) //Lost Chao
				CurrentMission = LostChaoCard;
		}

		StageMissionTexlist.textures = MissionsText;
		StageMissionTexlist.nbTexture = LengthOfArray(MissionsText);
		LoadPVM("Missions", &StageMissionTexlist);
		MissionSpriteAnim.texid = CurrentMission;

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

		GetCustomLayout = CurrentLevelLayout;

		if (CurrentLevel >= LevelIDs_Chaos0 || CurrentLevel == LevelIDs_HedgehogHammer)
			return;

		StageMissionTexlist.textures = MissionsText;
		StageMissionTexlist.nbTexture = LengthOfArray(MissionsText);
		LoadPVM("Missions", &StageMissionTexlist);
		MissionSpriteAnim.texid = CurrentMission;

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

	if (Rings >= 100 && CurrentLevelLayout == Mission2_100Rings || TreasureHunting && KnuxCheck >= 3 && CurrentCharacter != Characters_Knuckles)
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

