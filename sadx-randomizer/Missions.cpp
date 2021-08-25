#include "stdafx.h"
#include "mission.h"

// Mission Card settings, check, texture edit.
short CurrentMission = 0;
int CurrentMissionCard;
NJS_TEXNAME MissionsText[25];
NJS_TEXNAME TitleCard[8];
static NJS_TEXLIST TitleCardTex = { arrayptrandlength(TitleCard) };

static Trampoline* LoadTitleCardTexture_t = nullptr;


const char* stageVersionString[8] = { "Sonic", "Eggman", "Tails", "Knuckles", "Tikal", "Amy", "Gamma", "Big" };
const char* missionString[4] = { "M1 (Beat the Stage)", "M1 (Treasure Hunting", "M2 (100 Rings)", "M3 (Lost Chao)" };
int characterColor[8] = { lightBlue, redColor, lightOrange,  redColor, redColor, pinkColor, greyColor, purpleColor };
int missionColor[4] = { greyColor, lightGreen, lightOrange, lightBlue };

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

	if (CurrentLevel > LevelIDs_Chaos0)
		return 0;

	if (CurrentMission == Mission2_100Rings) //100 Rings check
		return (int)(99 < (short)Rings);

	if (CurrentMission == Mission3_LostChao) //Lost Chao
		return 1;

	return 1;
}


void PauseMenuFix() {
	//Display Current Mission Information
	if (CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel < LevelIDs_Chaos0)
	{
		SetDebugFontColor(greyColor);
		SetDebugFontSize(14.0f * (float)VerticalResolution / 480.0f);

		DisplayDebugStringFormatted(NJM_LOCATION(2, 6), "Mission:");

		if (CurrentStageVersion == KnucklesVersion && CurrentMission < Mission2_100Rings) {
			SetDebugFontColor(missionColor[Mission1_Variation]);
			DisplayDebugString(NJM_LOCATION(11, 6), missionString[Mission1_Variation]);
		}
		else {
			SetDebugFontColor(missionColor[CurrentMission]);
			DisplayDebugString(NJM_LOCATION(11, 6), missionString[CurrentMission]);
		}
		SetDebugFontColor(greyColor);
		DisplayDebugStringFormatted(NJM_LOCATION(2, 8), "Stage Version:");
		SetDebugFontColor(characterColor[CurrentStageVersion]);
		DisplayDebugStringFormatted(NJM_LOCATION(17, 8), "%s", stageVersionString[CurrentStageVersion]);
		SetDebugFontColor(greyColor);
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

		CurrentMissionCard = -1;

		if (CurrentMission == SADX_Mission)
		{

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
				if (CurrentMission < Mission2_100Rings && CurrentStageVersion == GammaVersion)
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

			if (CurrentMissionCard == -1) {

				if (CurrentCharacter == Characters_Amy && CurrentStageVersion != BigVersion)
					CurrentMissionCard = BalloonCard; //grab ballon

				if (CurrentCharacter == Characters_Big)
					CurrentMissionCard = FroggyCard; //grab Froggy

				if (CurrentCharacter != Characters_Amy && CurrentCharacter != Characters_Big)
					CurrentMissionCard = CapsuleCard;

				if (CurrentStageVersion == BigVersion)
					CurrentMissionCard = FroggyCard;

				if (CurrentStageVersion == KnucklesVersion)
					CurrentMissionCard = EmeraldKnuxCard;
			}
		}


		if (CurrentMission == Mission2_100Rings) //100 Rings
			CurrentMissionCard = RingsCard;

		if (CurrentMission == Mission3_LostChao) //Lost Chao
			CurrentMissionCard = LostChaoCard;


		StageMissionTexlist.textures = MissionsText;
		StageMissionTexlist.nbTexture = LengthOfArray(MissionsText);
		LoadPVM("Missions", &StageMissionTexlist);
		MissionSpriteAnim.texid = CurrentMissionCard;

		ObjectMaster* obj = LoadObject(LoadObj_Data1, 6, (ObjectFuncPtr)0x457B60);
		obj->Data1->InvulnerableTime = 300;
		obj->Data1->Position.x = 320.0;
		obj->Data1->Position.y = 360.0;
		obj->DeleteSub = FreeStageMissionImage;
	}
}

void StageMissionImage_result() {

	if (GetLevelType == 0) { //do the mission check here
			//0 = capsule, 1 = Lost Chao, 2 = Emeralds Knux, 3 = Beat Sonic, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails, 10 = Zero, 11+ Race

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


void CheckAndLoad_CartStopper() {

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0) {
		ObjectMaster* toto = LoadObject((LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA), 3, OCartStopper);
		if (toto) {
			toto->Data1->Position = EntityData1Ptrs[0]->Position;
		}
	}
}


ObjectMaster* Flash = nullptr;

void MissionResultCheck(ObjectMaster* obj) {

	EntityData1* data = obj->Data1;
	CharObj2* co2 = CharObj2Ptrs[0];
	EntityData1* p1 = EntityData1Ptrs[0];

	if (!co2 || !p1)
		return;

	switch (data->Action)
	{
	case 0:
		if ((EntityData1Ptrs[0]->Status & Status_Ground | Status_Unknown1)) {

			if (CurrentLevel == LevelIDs_Casinopolis && CurrentAct > 1)
				return;

			if (Rings >= 100 && CurrentMission == Mission2_100Rings || CurrentStageVersion == KnucklesVersion && KnuxCheck >= 3)
			{
				CheckAndLoad_CartStopper();

				Flash = nullptr;
				ForcePlayerAction(0, 24);
				if (co2->Speed.x > 1.5f)
					co2->Speed.x = 1.5;
				p1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);
				data->Action++;
			}
		}
		break;
	case 1:
		if (!Flash && EnableControl)
			Flash = LoadObject(LoadObj_Data1, 1, FlashScreen);

		data->Action++;
		break;
	case 2:
		StopMusic();
		DisableController(0);
		PauseEnabled = 0;
		if (CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_Zero)
		{
			for (int i = 0; i < LengthOfArray(M2_PlayerEndPosition); i++)
			{
				if (CurrentLevel == ConvertLevelActsIDtoLevel(M2_PlayerEndPosition[i].LevelID) && CurrentAct == ConvertLevelActsIDtoAct(M2_PlayerEndPosition[i].LevelID)
					&& CurrentStageVersion == M2_PlayerEndPosition[i].version) {
					TeleportPlayerResultScreen(M2_PlayerEndPosition[i].Position, M2_PlayerEndPosition[i].YRot);
					break;
				}
			}
		}
		data->Action++;
		break;
	case 3:
		if (++data->InvulnerableTime == 85)
			data->Action++;
		break;
	case 4:
		LoadLevelResults_r();
		CheckThingButThenDeleteObject(obj);
		break;
	}

}

//Credits: PKR
void ScaleDebugFont(int scale)
{
	float FontScale;

	if ((float)HorizontalResolution / (float)VerticalResolution > 1.33f)
		FontScale = floor((float)VerticalResolution / 480.0f);
	else
		FontScale = floor((float)HorizontalResolution / 640.0f);

	SetDebugFontSize(FontScale * scale);
	return;
}


void Missions_Init() {

	Race_Init();
	Init_TreasureHunting();
	ScaleDebugFont(16);
	return;
}