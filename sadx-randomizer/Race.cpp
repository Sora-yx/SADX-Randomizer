#include "stdafx.h"


char AIRace = -1;
bool Race = false;
extern ObjectFuncPtr charfuncs[];
int AIRaceArray[6] = { Characters_Sonic, Characters_Eggman, Characters_Tails, Characters_Tikal, Characters_Amy, Characters_Gamma }; //Tails Race AI
int AIRaceIconArray[8] = { 1, 11, 2, 12, 15, 13, 14, 16 };

void AIRaceLoad_R() {

	LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[AIRace]);
}

int IsFastSonicAI_R() {

	if (isCriticalMode && CurrentCharacter < Characters_Amy)
		return 1;
	else
		return 0;
}


void RaceResultCheck(ObjectMaster* a1) {

	ObjectMaster* play1 = GetCharacterObject(0);
	EntityData1* v1 = a1->Data1;

	if (Race && !isAIActive)
	{
		if (play1->Data1->CharID != Characters_Tails && IsSpecificPlayerInSphere(&v1->Position, 22, 1))
			SetAIRaceWin();
	}
}

void SetAIRaceWin() {

	if (TimeThing != 0)
	{
		CutsceneMode = 0;
		SetOpponentRaceVictory();

		if (Lives <= 0) {
			KillPlayer(0);
			ScreenFade_Start_CopyAlpha();
		}
		else {	
			GameState = 0xc;
			ScreenFade_Start_CopyAlpha();
		}
	}

	return;
}

void FixRaceResult() {

	if (CurrentCharacter != Characters_Tails)
		return;
	else
		LoadLevelResults_r();

	return;
}


void CheckAndLoadRaceOpponent() {

	//If we aren't racing, return
	if (CurrentCharacter == Characters_Tails && !Vanilla || CurrentStageVersion != TailsVersion || CurrentMission >= Mission1_Variation) {
		Race = false;
		return;
	}


	if (CurrentStageVersion == TailsVersion && CurrentMission < 2) {
		Race = true;
		isAIActive = false;
	}


	if (Race && CurrentLevel != LevelIDs_SpeedHighway) //we don't want a random AI for speed highway, as only eggman AI works here.
	{
		AIRace = randomizedSets[levelCount].ai_race;

		if (AIRace == CurrentCharacter) //Failsafe to prevent crash
		{
			if (CurrentCharacter == Characters_Sonic)
				AIRace = Characters_Tails;
			else
				AIRace = Characters_Sonic;
		}

		if (CurrentCharacter == Characters_Big && (AIRace == Characters_Knuckles || AIRace == Characters_Amy))
			AIRace = Characters_Tails; //Prevent Big crash
	}


	//Make the Texture race bar icon matches the characters

	WriteData<1>((char*)0x91bfec, AIRaceIconArray[AIRace]); //Change Opponent texture ID

	if (CurrentCharacter == Characters_Sonic && MetalSonicFlag == 1)
		WriteData<1>((char*)0x91c000, 17);
	else
		WriteData<1>((char*)0x91c000, AIRaceIconArray[CurrentCharacter]); //Change Current Character texture ID

	if (CurrentLevel == LevelIDs_SpeedHighway && CurrentAct == 0)
		LoadObject(LoadObj_Data1, 8, MRace_EggMobile_TexlistManager);

	LoadTailsOpponent(CurrentCharacter, 1, CurrentLevel);
		
	return;
}


short getRandomRaceAI(RandomizedEntry entry) {
	int8_t cur_RaceAI = -1;
	size_t ai_Racecount = sizeof(AIRaceArray) / sizeof(AIRaceArray[0]);

	cur_RaceAI = AIRaceArray[rand() % ai_Racecount];

	return cur_RaceAI;
}


void Race_Init() {
	//Sonic/Eggman Race Stuff
	WriteData<1>((void*)0x47d947, 0x84); ///Load Race AI for any character
	WriteData<1>((void*)0x47D945, 0x8); ///Load Race AI for any character 
	
	WriteData<5>((void*)0x60ffab, 0x90); //Prevent Eggman AI from spawning during SH
	WriteData<5>((void*)0x415965, 0x90); //Prevent the game to load Race AI. (we will manually call it.)

	WriteCall((void*)0x4616d5, FixVictoryTailsVoice); //Prevent Tails's victory voice to play... when not Tails, lol.
	WriteCall((void*)0x4615b3, FixVictoryTailsVoice); //same
	WriteCall((void*)0x461639, FixVictoryTailsVoice);  //same

	WriteCall((void*)0x47da24, AIRaceLoad_R);  //Swap Sonic Race AI Random. (any character)
	WriteCall((void*)0x47d961, IsFastSonicAI_R);  

	ResizeTextureList((NJS_TEXLIST*)&MILESRACE_TEXLIST, 17);
	help.ReplaceFile("system\\MILESRACE.pvm", "system\\textures\\RACE_HD.pvmx");
}

