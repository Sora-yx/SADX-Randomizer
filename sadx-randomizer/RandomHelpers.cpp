#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include "RandomHelpers.h"


extern bool RNGCharacters;
extern bool RNGStages;
extern bool Vanilla;
extern bool Missions;
extern int ban;
extern bool ConsistentMusic;
int musicCount;
extern int CurrentAI;
extern bool Sonic;
extern bool Tails;
extern bool Knuckles;
extern bool Amy;
extern bool Big;
extern bool Gamma;
extern bool MetalSonic;
extern bool SuperSonic;
extern bool banCharacter[8];
extern int split;
extern int TotalCount;
extern bool isAIAllowed;
extern bool Race;
extern int GetCustomLayout;
extern int ExtraChara;

int character[6] = { Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Gamma, Characters_Big };
int AIArray[3] = { Characters_Sonic, Characters_Tails, Characters_Amy };
int CustomLayout;
int TwinkleCircuitRNG = 0;
int level[21] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 18, 19, 20, 21, 22, 23, 35, 38 };


//Initialize Ban few stage impossible to beat, depending on the character.
int bannedLevelsGamma[8] = { LevelIDs_Chaos0, LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggHornet, LevelIDs_EggWalker, LevelIDs_Zero };
int bannedLevelsBig[2] = { LevelIDs_PerfectChaos , LevelIDs_EggViper };

//Initiliaze banned regular stage
int bannedRegularSonic[8] = { LevelIDs_LostWorld, LevelIDs_IceCap, LevelIDs_Chaos0, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggHornet, LevelIDs_EggViper };
int bannedRegularTails[4] = { LevelIDs_Chaos4, LevelIDs_EggHornet, LevelIDs_EggWalker, LevelIDs_SandHill };
int bannedRegularKnuckles[3] = { LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6 };
int bannedRegularAmy[1] = { LevelIDs_Zero };
int bannedRegularBig[2] = { LevelIDs_PerfectChaos, LevelIDs_EggViper };
int bannedRegularGamma[8] = { LevelIDs_Chaos0, LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggHornet, LevelIDs_EggWalker, LevelIDs_Zero };

int bannedMusic[28] = { 0x11, 0x1A, 0x29, 0x2C, 0x2e, 0x37, 0x38, 0x45, 0x47, 0x4B, 0x55, 0x60, 0x61, 0x62, 0x63, 0x64, 0x66, 0x6e, 0x6f, 0x70, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b };



//Contain randomly generated sets of character/level/act to work with

struct RandomizedEntry randomizedSets[40];

short randomacts(RandomizedEntry entry) {
	//Set up act rng.
	int actHS[2] = { 0, 2 };
	int act0[3] = { 0, 0, 1 }; //increasing chance to get act 1

	switch (entry.level)
	{
	case LevelIDs_EmeraldCoast:
		if (entry.character == Characters_Sonic)
			return 2;
		else
			if (entry.character == Characters_Big)
				return 0;
			else
				return actHS[rand() % 2];
		break;
	case LevelIDs_TwinklePark:
		if (entry.character == Characters_Sonic || entry.character == Characters_Gamma)
			return 1;
		else
		{
			if (entry.character == Characters_Amy)
				return 0;
			else
				return actHS[rand() % 2];
		}
		break;
	case LevelIDs_RedMountain:
		if (entry.character == Characters_Gamma)
			return 0;
		if (entry.character == Characters_Sonic)
			return 1;
		else
			return rand() % 2;
		break;
	case LevelIDs_IceCap:
		if (entry.character == Characters_Big)
			return 1;
		else
			return 0;
		break;
	case LevelIDs_Casinopolis:
		if (entry.character == Characters_Sonic)
			return 1;
		else
		{
			if (entry.character == Characters_Tails)
				return 0;
			else
				return act0[rand() % 3];
		}
		break;
	case LevelIDs_HotShelter:
		if (entry.character == Characters_Gamma)
			return 0;
		else
			return actHS[rand() % 2];
		break;
	case LevelIDs_TwinkleCircuit:
			return rand() % 5;
			break;
	default:
		return 0;
		break;
	}
}

short randomLayout(RandomizedEntry entry) {

	if (Missions)
		return rand() % 4;
	else
		return rand() % 2;

}


int8_t prev_char = -1;


uint8_t getRandomCharacter(bool allow_duplicate) {
	
	int8_t cur_char = -1;
	size_t char_count = sizeof(character) / sizeof(character[0]);

	cur_char = character[rand() % char_count];

	while (cur_char == prev_char && ban == 0 || banCharacter[cur_char])
	{
		cur_char = character[rand() % char_count];
	}

	prev_char = cur_char;
	return cur_char;
}






short getRandomAI(RandomizedEntry entry) {

	int8_t cur_AI = -1;
	size_t ai_count = sizeof(AIArray) / sizeof(AIArray[0]);

	do {

		cur_AI = AIArray[rand() % ai_count];

	} while (cur_AI == entry.character || banCharacter[cur_AI]);
	
	
	return cur_AI;
}




short prev_stage = -1;

short getRandomStage(uint8_t char_id, bool AllowVanilla) {

	short cur_stage = -1;
	AllowVanilla = Vanilla;

	if (AllowVanilla != true) {
		do {
			cur_stage = level[rand() % LengthOfArray(level)];
		} while (isStageBanned(char_id, cur_stage) || cur_stage == prev_stage || cur_stage > 14 && cur_stage < 26 && prev_stage > 14 && prev_stage < 26);
	}
	else {
		do {
			cur_stage = level[rand() % LengthOfArray(level)];
		} while (cur_stage == prev_stage || cur_stage > 14 && cur_stage < 26 && prev_stage > 14 && prev_stage < 26);
	}

	prev_stage = cur_stage;
	return cur_stage;
}


bool isStageBanned(uint8_t char_id, short stage_id) {
	int* bannedStages = nullptr;
	size_t arraySize = 0;

	bool result;
	switch (char_id) {
	case Characters_Sonic:
		bannedStages = bannedRegularSonic;
		arraySize = LengthOfArray(bannedRegularSonic);
		break;
	case Characters_Tails:
		bannedStages = bannedRegularTails;
		arraySize = LengthOfArray(bannedRegularTails);
		break;
	case Characters_Knuckles:
		bannedStages = bannedRegularKnuckles;
		arraySize = LengthOfArray(bannedRegularKnuckles);
		break;
	case Characters_Amy:
		bannedStages = bannedRegularAmy;
		arraySize = LengthOfArray(bannedRegularAmy);
		break;
	case Characters_Gamma:
		bannedStages = bannedRegularGamma;
		arraySize = LengthOfArray(bannedRegularGamma);
		break;
	case Characters_Big:
		bannedStages = bannedRegularBig;
		arraySize = LengthOfArray(bannedRegularBig);
		break;
	default:
		//If you reach this place, you're definitely doing something wrong
		return false;
		break;
	}

	result = isValueInArray(bannedStages, stage_id, arraySize);
	return result;
}

bool isBossStage(short stage_id)
{
	return stage_id > 14 && stage_id < 26;
}

int levelCount;

void testRefactor(char stage, char act) {
	if (GameMode != 8 || GameMode != 1 || GameMode != 11)
	{
		if (RNGCharacters)
			CurrentCharacter = randomizedSets[levelCount].character;

		if (SuperSonic != true)
			SonicRand = randomizedSets[levelCount].ss_mode;

		if (MetalSonic != true)
			MetalSonicFlag = randomizedSets[levelCount].sonic_mode;

		CurrentAI = randomizedSets[levelCount].ai_mode;
		ExtraChara = randomizedSets[levelCount].knux_mode;
		
		LastLevel = CurrentLevel;
		CustomLayout = 0;
		GetCustomLayout = 0;
		CurrentLevel = RNGStages ? randomizedSets[levelCount].level : stage;
		CurrentAct = randomizedSets[levelCount].act;
		levelCount++;

			
		if (levelCount == TotalCount)
		{
			GetNewLevel(); //reroll once the 40 stages have been beated.
		}
	}


}



void GoToNextLevel_hook(char stage, char act) {
	if (GameMode != 8 || GameMode != 1 || GameMode != 11)
	{
		if (RNGCharacters)
			CurrentCharacter = randomizedSets[levelCount].character;

		if (SuperSonic != true)
			SonicRand = randomizedSets[levelCount].ss_mode;

		if (MetalSonic != true)
			MetalSonicFlag = randomizedSets[levelCount].sonic_mode;

		CurrentAI = randomizedSets[levelCount].ai_mode;
		ExtraChara = randomizedSets[levelCount].knux_mode;

		LastLevel = CurrentLevel;
		CustomLayout = 0;
		GetCustomLayout = 0;
		CurrentLevel = RNGStages ? randomizedSets[levelCount].level : stage;
		CurrentAct = randomizedSets[levelCount].act;
	

		levelCount++;

		if (ConsistentMusic)
			musicCount++;

		if (levelCount == TotalCount)
		{
			GetNewLevel(); //reroll once the 40 stages have been beated.
		}
	}
}


//cancel the reset position at 0 after quitting a stage.
void CancelResetPosition() {
	NextLevel = LastLevel;
	NextAct = LastAct;
	SonicRand = 0;
	CustomLayout = 0;
	GetCustomLayout = 0;
	Race = false;
	GameMode = GameModes_Adventure_Field;
}


//Fix Trial Mode 
void SetLevelAndAct_R() {

	if (GameMode == GameModes_Menu)
	{
		if (LevelList == 14 || LevelList == 238)
			testRefactor(NextLevel, NextAct);
		else
			return;
	}
}



//randomize voices
void RandomVoice() {
	if (VoicesEnabled != 0) {
		CurrentVoiceNumber = rand() % 2043;
	}

}



short getRandomMusic(RandomizedEntry entry) {

	short cur_music = -1;

		do {
			cur_music = rand() % 125;

		} while (isValueInArray(bannedMusic, cur_music, 28));
	
		return cur_music;
}



void RandomMusic() {

	if (Music_Enabled != 0) {

		CurrentSong = randomizedSets[musicCount].music;
		LastSong = CurrentSong;

		if (!ConsistentMusic)
			musicCount++;

		if (musicCount == TotalCount)
		{
			for (int i = 0; i < 40; i++) { //generate 40 musics.
				randomizedSets[i].music = getRandomMusic(randomizedSets[i]);
			}

			musicCount = 0;
		}
	}
	
	return;
}



void TwinkleCircuitMusic() {
	if (Music_Enabled != 0) {

		LoadSetFile(0, "MCart00");
		TwinkleCircuitRNG = rand() % 2;

		if (TwinkleCircuitRNG == 0)
			WriteData<1>((char*)0x004DAB4E, 0x57);
			else
				WriteData<1>((char*)0x004DAB4E, 0x19);
	}

}

void GetNewLevel() {

	for (int i = 0; i < 40; i++) { //generate 40 new levels.
		randomizedSets[i].character = getRandomCharacter();
		randomizedSets[i].level = getRandomStage(randomizedSets[i].character, Vanilla);
		randomizedSets[i].act = randomacts(randomizedSets[i]);
		randomizedSets[i].layout = randomLayout(randomizedSets[i]);

		if (RNGMusic)
			randomizedSets[i].music = getRandomMusic(randomizedSets[i]);

		if (isAIAllowed)
			randomizedSets[i].ai_mode = getRandomAI(randomizedSets[i]);

		if (randomizedSets[i].character == Characters_Sonic)
		{
			randomizedSets[i].sonic_mode = rand() % 2;
		}


		levelCount = 0;
		return;
	}
}