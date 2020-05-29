#include "stdafx.h"
#include "RandomHelpers.h"
#include "CharactersSettings.h"
#include "StageSettings.h"
#include "Utils.h"


extern bool RandCongratsDone;
bool IceCapCutsceneSkip = false;
extern ObjectMaster* CurAI;

extern ObjectMaster* ChaoTP;

extern bool CasinoTails;



//While load result: "fix" game crash. (There is probably a better way to do this.), restore most of the value to 0 to avoid any conflict.
void DisableTimeStuff() {

	if (GameMode != GameModes_Trial && GameMode != GameModes_Mission && RNGStages)
		GameMode = GameModes_Adventure_Field; //fix game crash

	if (SelectedCharacter == 6) //Fix Super Sonic Story giving sonic layout
		LastStoryFlag = 1;
	else
		LastStoryFlag = 0;

	TimeThing = 0;

	if (CurrentLevel == LevelIDs_SandHill)
	{
		ResetValueWhileLevelResult();
		if (GameMode != GameModes_Trial && GameMode != GameModes_Mission && RNGStages)
			AddCustomFlag(); //Add a flag for story progression.
	}

	ringsPB += Rings; //total Rings credit stat

	if (!Race && CurrentCharacter == Characters_Tails)
		SetTailsRaceVictory();

	ObjectMaster* play1 = GetCharacterObject(0);
	ObjectMaster* play2 = GetCharacterObject(1);

	if (!Race && isAIAllowed && isAIActive && CurrentLevel != LevelIDs_TwinklePark) //Move AI to player 1 if we are not racing.
	{
		if (play2 != nullptr && play1 != nullptr)
		{
			if (CurrentCharacter != Characters_Amy)
			{
				play2->Data1->Position.x = play1->Data1->Position.x - 7;
				play2->Data1->Position.y = play1->Data1->Position.y;
				play2->Data1->Position.z = play1->Data1->Position.z + 5;
				play2->Data1->Rotation.y = play1->Data1->Rotation.y;
			}
			else
			{
				CheckThingButThenDeleteObject(TailsAI_ptr); //prevent crash as Amy.
			}

			if (CurrentAI == Characters_Tails || play1->Data1->CharID == Characters_Tails)
				SetTailsRaceVictory(); //Fix Tails AI victory animation

			ForcePlayerAction(1, 19); //Force AI to Victory pose
			dword_3B2A304 = 0;
		}
	}

	if (Race && CurrentCharacter != Characters_Tails)
	{
		SetTailsRaceVictory();
		Tails_CheckRaceResult();
	}


	Race = false;
	return;
}

void ReleaseScoreTexture() {

	ResetValueWhileLevelResult();
	if (GameMode != GameModes_Trial && GameMode != GameModes_Mission && RNGStages)
		AddCustomFlag(); //Add a flag for story progression.

	njReleaseTexture(&SCORE_RESULT_TEXLIST);
	return;
}


void SetResultsCamera()
{
	switch (GetCharacter0ID())
	{
	case Characters_Sonic:
	case Characters_Tails:
		sub_469300((int*)0x919BF4, 3, 720);
		break;
	case Characters_Knuckles:
		sub_469300((int*)0x91A848, 3, 720);
		break;
	case Characters_Amy:
		sub_469300((int*)0x9196D0, 3, 720);
		break;
	case Characters_Gamma:
		sub_469300((int*)0x91A248, 3, 720);
		break;
	}
}


void __cdecl sub_461560()
{
	CharObj2* v3; // eax@20

	switch (CurrentLevel)
	{
	case LevelIDs_SpeedHighway:
		if (GetRaceWinnerPlayer() == 1)
		{
			SetResultsCamera();
			ResultVoiceFix();
			Load_DelayedSound_BGM(MusicIDs_RoundClear);
		}
		else
			Load_DelayedSound_Voice(225);
		if (GameMode != GameModes_Trial || byte_3B2A2F1 != 1)
			LoadObject(LoadObj_Data1, 3, sub_47D300);
		break;
	case LevelIDs_WindyValley:
	case LevelIDs_SkyDeck:
	case LevelIDs_IceCap:
	case LevelIDs_Casinopolis:
		if (sub_46A820())
		{
			if (sub_46A7F0() == 1)
				SetOpponentRaceVictory();
			else
				SetTailsRaceVictory();
		}
		if (GetRaceWinnerPlayer() == 1)
		{
			SetResultsCamera();
			ResultVoiceFix();
			Load_DelayedSound_BGM(MusicIDs_RoundClear);
		}
		else
			Load_DelayedSound_SFX(214);
		if (GameMode != GameModes_Trial || byte_3B2A2F1 != 1)
			LoadObject(LoadObj_Data1, 3, sub_47D300);
		break;
	default:
		SetTailsRaceVictory();
		if (CurrentLevel == LevelIDs_SandHill)
		{
			v3 = GetCharObj2(0);
			v3->PhysicsData.CollisionSize = 9;
			v3->PhysicsData.YOff = 4.5f;
		}
		SetResultsCamera();
		ResultVoiceFix();
		Load_DelayedSound_BGM(MusicIDs_RoundClear);
		break;
	}
}

void __cdecl sub_4141F0(ObjectMaster* obj)
{
	EntityData1* v1 = GetCharacterObject(0)->Data1;
	if (EntityData1Ptrs[1] && sub_46A820() && sub_46A7F0() == 1)
		v1 = EntityData1Ptrs[1];
	if (v1->Status & 3)
	{
		ForcePlayerAction(0, 19);
		switch (CurrentCharacter)
		{
		case Characters_Tails:
			sub_461560();
			break;
		case Characters_Gamma:
			if (GetCharacter0ID() == Characters_Gamma)
			{
				sub_469300((int*)0x91A248, 3, 720);
				switch (CurrentLevel)
				{
				case LevelIDs_EmeraldCoast:
					if (CurrentAct == 2 && CurrentMissionCard == 5 || CurrentAct == 0 && CurrentMissionCard == 1)
						Load_DelayedSound_Voice(1772);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_HotShelter:
					if (CurrentAct == 2 && CurrentMission == SADX_Mission)
						Load_DelayedSound_Voice(1773);
					if (CurrentAct == 0 && CurrentMissionCard == 5 && CurrentStageVersion == BigVersion)
						Load_DelayedSound_Voice(1772);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_TwinklePark:
					if (CurrentAct == 1 && CurrentMission < 2 && CurrentStageVersion == BigVersion)
						Load_DelayedSound_Voice(1772);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_RedMountain:
					if (CurrentAct == 1 && CurrentStageVersion == GammaVersion)
						Load_DelayedSound_Voice(1774);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_WindyValley:
					if (CurrentAct == 0 & CurrentStageVersion == GammaVersion)
						Load_DelayedSound_Voice(1775);
					else
						Load_DelayedSound_Voice(1770);
					break;
				case LevelIDs_IceCap:
					if (CurrentAct == 3 && CurrentMissionCard == 5)
						Load_DelayedSound_Voice(1772);
					else
						Load_DelayedSound_Voice(1770);
					break;
				default:
					Load_DelayedSound_Voice(1770);
					break;
				}
			}
			else
			{
				SetResultsCamera();
				ResultVoiceFix();
			}
			break;
		default:
			SetResultsCamera();
			ResultVoiceFix();
			break;
		}
		sub_457D00();
		LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
		Load_DelayedSound_BGM(MusicIDs_RoundClear);
		CheckThingButThenDeleteObject(obj);
	}
}



void __cdecl LoadLevelResults_r()
{
	NJS_VECTOR a1; // [sp+0h] [bp-18h]@12
	NJS_VECTOR a2; // [sp+Ch] [bp-Ch]@12

	DisableController(0);
	PauseEnabled = 0;
	if (Race && RaceWinnerPlayer == 2 && GameMode < 9)
	{
		GameMode = GameModes_Adventure_ActionStg; //fix Softlock race
		TimeThing = 0;
	}
	else
	{
		DisableTimeStuff();
	}
	if (GameMode == GameModes_Mission)
		sub_5919E0();
	if (CurrentCharacter != Characters_Tails && GetCharacter0ID() == Characters_Tails)
		SetTailsRaceVictory();
	switch (CurrentCharacter)
	{
	case Characters_Tails:
		if (GetRaceWinnerPlayer() == 1)
			LoadObject((LoadObj)0, 3, sub_4141F0);
		else
		{
			ForcePlayerAction(0, 19);
			sub_461560();
			sub_457D00();
			LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
		}
		break;
	case Characters_Knuckles:
		ForcePlayerAction(0, 19);
		sub_457D00();
		LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
		SoundManager_Delete2();
		if ((CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel != LevelIDs_SandHill) || GetCharacter0ID() != Characters_Knuckles)
		{
			SetResultsCamera();
			Load_DelayedSound_SFX(0x5a8);
		}
		else
		{
			sub_469300((int*)0x91A848, 3, 720);
			Load_DelayedSound_SFX(0x5a5);
		}
		Load_DelayedSound_BGM(MusicIDs_RoundClear);
		break;
	case Characters_Amy:
		if (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel != LevelIDs_SandHill || CurrentMission >= 2)
			LoadObject((LoadObj)0, 3, sub_4141F0);
		else
		{
			ForcePlayerAction(0, 19);
			sub_457D00();
			LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
			SoundManager_Delete2();
			if (GetCharacter0ID() == Characters_Amy)
				Load_DelayedSound_Voice(1733);
			else
				ResultVoiceFix();
			Load_DelayedSound_BGM(MusicIDs_RoundClear);
		}
		break;
	case Characters_Big:
		ForcePlayerAction(0, 19);
		a2.x = -36.072899f;
		a2.y = 5.7132001f;
		a2.z = -1.5176001f;
		sub_43EC90(EntityData1Ptrs[0], &a2);
		a1 = EntityData1Ptrs[0]->CollisionInfo->CollisionArray->origin;
		stru_3B2C6DC = a1;
		njSubVector(&a1, &a2);
		stru_3B2C6D0 = a1;
		sub_437D20(sub_464B00, 1, 2);
		sub_457D00();
		LoadObject(LoadObj_Data1, 5, j_ScoreDisplay_Main);
		if ((CurrentAct | (CurrentLevel << 8)) < LevelAndActIDs_Chaos0)
			SoundManager_Delete2();
		ResultVoiceFix();
		Load_DelayedSound_BGM(MusicIDs_RoundClear);
		break;
	default:
		LoadObject((LoadObj)0, 3, sub_4141F0);
		SoundManager_Delete2();
		break;
	}
}



void RestorePuzzleBoxVanillaThing() {
	//Restore the Amy Check for puzzle box.
	WriteData<1>((void*)0x442249, 0xF);
	WriteData<1>((void*)0x44224A, 0x85);
	WriteData<1>((void*)0x44224B, 0xB3);
	WriteData<1>((void*)0x44224C, 0x0);
	WriteData<1>((void*)0x44224D, 0x0);
	WriteData<1>((void*)0x44224E, 0x0);
	return;
}

void ResetValueWhileLevelResult() {
	isZeroActive = false;
	LimitCustomFlag = false;
	isGameOver = false;
	SonicRand = 0;
	KnuxCheck = 0;
	KnuxCheck2 = 0; //fix trial crash
	ChaoSpawn = false;
	GetBackRing = false;
	CurrentStageVersion = 0;
	isPlayerInWaterSlide = false;
	CasinoTails = false;
	isKnucklesVersion = false;
	isTailsVersion = false;
	MMPlatformEnabled = false;

	RestoreRNGValueKnuckles();
	RestorePuzzleBoxVanillaThing();
	Delete_ObjectsCommon();
	njReleaseTexture(&SUPERSONIC_TEXLIST);
	njReleaseTexture(&EGGROB_TEXLIST);

	if (CurrentLevel == LevelIDs_PerfectChaos && CurrentCharacter != Characters_Sonic)
		CharObj2Ptrs[0]->Powerups &= Powerups_Invincibility;
		
	if (CurrentLevel != 0)
	{
		DeleteTriggerObject();
		CheckThingButThenDeleteObject(ChaoTP);
		Delete_Cart();
		Chao_DeleteFiles();
	}
	
	fixTCCart();
	return;
}

void fixTCCart() {
	WriteData<1>((void*)0x798306, 0x85); //Restore original Functions
	WriteData<1>((void*)0x7983c4, 0x7C);

	return;
}



void ResetStatsValues() {
	LimitCustomFlag = false;
	isZeroActive = false;
	isAIActive = false;
	ChaoSpawn = false;
	CasinoTails = false;
	isGameOver = false;
	isKnucklesVersion = false;
	isTailsVersion = false;
	MMPlatformEnabled = false;
	KnuxCheck = 0;
	KnuxCheck2 = 0; //fix trial crash
	CurrentAI = 0;
	SonicRand = 0;
	TransfoCount = 0;
	CurrentMission = 0;
	CurrentStageVersion = 0;
	CurrentMissionCard = 0;
	GetCustomLayout = 0;
	Credits_State = 0;
	RageQuit++;
	ringsPB += Rings; //total Rings credit stat
	Race = false;
	RandCongratsDone = false;
	isPlayerInWaterSlide = false;
	fixTCCart();

	if (CurrentLevel != 0)
		Delete_Cart();

	njReleaseTexture(&SUPERSONIC_TEXLIST);
	njReleaseTexture(&EGGROB_TEXLIST);
	RestoreRNGValueKnuckles();
}

//cancel the reset position at 0 after quitting a stage.
void CancelResetPosition() {
	NextAct = LastAct;
	NextLevel = LastLevel;

	ResetStatsValues();
	GameMode = GameModes_Adventure_Field;
	return;
}

void SoftReset_R() {

	if (LevelCopy != 0 && Credits_State == 0)
		ResetStatsValues();

	if (LevelCopy != 0)
	{
		GameMode = GameModes_Adventure_Field;
		PauseQuitThing2(); //Delete stuff correctly.
	}

	return FUN_00412ad0();
}

void TrialModeQuit_R() {
	if (LevelCopy != 0 && Credits_State == 0)
		ResetStatsValues();

	return FUN_00425b00();
}