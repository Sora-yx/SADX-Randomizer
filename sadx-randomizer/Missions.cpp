#include "stdafx.h"
#include "RandomHelpers.h"


// Mission Card settings, check, texture edit.

int CurrentMission;
NJS_TEXNAME MissionsText[18];
char GetCustomLayout;


int CheckMissionRequirements_r() {

	GetCustomLayout = CurrentLevelLayout;

	if (CurrentLevel > LevelIDs_Chaos0)
		return 0;

	if (GetCustomLayout == 2) //100 Rings check
		return (int)(99 < (short)Rings);

	if (GetCustomLayout == 3) //Lost Chao
		return 1;

	return 1;
}


void LoadStageMissionImage_r() {

	GetCustomLayout = Mission1;

	if (GetLevelType == 0) { //Mission card check here

		if (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel < LevelIDs_SandHill)
			return;

		GetCustomLayout = CurrentLevelLayout;

		switch (CurrentLevel)
		{
		case LevelIDs_EmeraldCoast:
			if (CurrentAct == 2 || CurrentAct == 0 && CurrentLevelLayout == Mission1_Variation)
				CurrentMission = FroggyCard; //Catch Froggy if Big or Gamma layout.
			break;
		case LevelIDs_LostWorld:
			if (!CurrentLevelLayout)
				CurrentMission = LostWorldCard; //Go to the center of the ruin.
			if (CurrentLevelLayout == 1 && CurrentAct == 1)
				CurrentMission = EmeraldKnuxCard;
			break;
		case LevelIDs_FinalEgg:
			if (CurrentLevelLayout == Mission1_Variation && CurrentCharacter != Characters_Amy)
				CurrentMission = CapsuleCard; //capsule
			else
				CurrentMission = FinalEggCard; //Go to the center of the base.

			if (CurrentCharacter == Characters_Amy)
				CurrentMission = BallonCard; //grab balon if Amy regardless of the mission.
			break;
		case LevelIDs_RedMountain:
			if (CurrentAct == 2)
				CurrentMission = EmeraldKnuxCard;
			if (CurrentLevelLayout == 1 && CurrentAct == 1 && CurrentCharacter == Characters_Amy)
				CurrentMission = BallonCard; //grab ballon
			break;
		case LevelIDs_SpeedHighway:
			if (Race)
				CurrentMission = MissileRaceCard; //Eggman Race
			if (CurrentLevelLayout == Mission1_Variation && CurrentAct == 2)
				CurrentMission = EmeraldKnuxCard;
			break;
		case LevelIDs_SkyDeck:
			if (CurrentLevelLayout == Mission1_Variation && CurrentAct == 2)
				CurrentMission = EmeraldKnuxCard;
			break;
		case LevelIDs_IceCap:
			if (CurrentAct == 3)
				CurrentMission = FroggyCard;  //Froggy
			break;
		case LevelIDs_Casinopolis:
			if (CurrentAct == 0 && CurrentLevelLayout == Mission1_Variation)
				CurrentMission = EmeraldKnuxCard;
			break;
		case LevelIDs_HotShelter:
			if (CurrentLevelLayout == Mission1_Variation && CurrentAct == 0)
				CurrentMission = FroggyCard; //Froggy
			break;
		default:
			CurrentMission = CapsuleCard;
			break;
		}

		if (CurrentCharacter == Characters_Big && GetCustomLayout == Mission1)
		{
			if (CurrentLevel == LevelIDs_HotShelter && CurrentAct == 2)
				CurrentMission = CapsuleCard;
			else if (CurrentLevel == LevelIDs_FinalEgg)
				CurrentMission = CapsuleCard;
			else
				CurrentMission = FroggyCard;
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


		if (CurrentCharacter == Characters_Amy && GetCustomLayout == Mission1)
			CurrentMission = BallonCard; //grab ballon

		if (GetCustomLayout == Mission2_100Rings && !Race) //100 Rings
			CurrentMission = RingsCard;

		if (GetCustomLayout == Mission3_LostChao && !Race) //Lost Chao
			CurrentMission = LostChaoCard;

		StageMissionTexlist.textures = MissionsText;
		StageMissionTexlist.nbTexture = LengthOfArray(MissionsText);
		LoadPVM("textures\\Missions", &StageMissionTexlist);
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

		if (CurrentLevel >= LevelIDs_Chaos0)
			return;

		StageMissionTexlist.textures = MissionsText;
		StageMissionTexlist.nbTexture = LengthOfArray(MissionsText);
		LoadPVM("textures\\Missions", &StageMissionTexlist);
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

	if (CurrentLevel == 0 || CurrentLevel > 14 && CurrentLevel < 35) {
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
	WriteJump(j_LoadTitleCardTexture, LoadTitleCardTexture_r);
	WriteJump(j_DisplayTitleCard, DisplayTitleCard_r);
	WriteJump(LoadStageMissionImage, LoadStageMissionImage_r);
	WriteCall((void*)0x4284ac, StageMissionImage_result);
	WriteCall((int*)0x4284cd, CheckMissionRequirements_r);
}

extern bool isPlayerInWaterSlide;

void MissionResultCheck() {

	if (CurrentLevel < LevelIDs_Chaos0 && GameState == 15)
	{
		if (Rings >= 100 && CurrentMission == RingsCard || CurrentMission == EmeraldKnuxCard && KnuxCheck >= 3 && CurrentCharacter != Characters_Knuckles)
		{
			ObjectMaster* obj = GetCharacterObject(0);
			EntityData1* ent;
			ent = obj->Data1;
			if ((ent->Status & Status_Ground) == Status_Ground && !isPlayerInWaterSlide && TimeThing != 0)
			{
				LoadLevelResults();
			}
		}
	}

	return;
}