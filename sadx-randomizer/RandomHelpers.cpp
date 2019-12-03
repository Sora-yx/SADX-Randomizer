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
extern int StorySplits;

int character[6] = { Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Gamma, Characters_Big };
int AIArray[3] = { Characters_Sonic, Characters_Tails, Characters_Amy };
int CustomLayout;
int TwinkleCircuitRNG = 0;
int level[21] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 18, 19, 20, 21, 22, 23, 35, 38 };



//Banned level list, there is few stage impossible to beat, depending on the character.
int bannedLevelsGamma[8] = { LevelIDs_Chaos0, LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggHornet, LevelIDs_EggWalker, LevelIDs_Zero };
int bannedLevelsBig[2] = { LevelIDs_PerfectChaos , LevelIDs_EggViper };

//Initiliaze banned Vanilla stage (if option is checked)
int bannedRegularSonic[8] = { LevelIDs_LostWorld, LevelIDs_IceCap, LevelIDs_Chaos0, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggHornet, LevelIDs_EggViper };
int bannedRegularTails[4] = { LevelIDs_Chaos4, LevelIDs_EggHornet, LevelIDs_EggWalker, LevelIDs_SandHill };
int bannedRegularKnuckles[3] = { LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6 };
int bannedRegularAmy[1] = { LevelIDs_Zero };
int bannedRegularBig[2] = { LevelIDs_PerfectChaos, LevelIDs_EggViper };
int bannedRegularGamma[8] = { LevelIDs_Chaos0, LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggHornet, LevelIDs_EggWalker, LevelIDs_Zero };

//Few jingle that we don't want in the random music function.
int bannedMusic[28] = { 0x11, 0x1A, 0x29, 0x2C, 0x2e, 0x37, 0x38, 0x45, 0x47, 0x4B, 0x55, 0x60, 0x61, 0x62, 0x63, 0x64, 0x66, 0x6e, 0x6f, 0x70, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b }; 


//Contain randomly generated sets of character/level/act to work with (Main Part of the mod)

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
		if (Vanilla)
			return rand() % 5;
		else
			return rand() % 5 + 1;
		break;
	default:
		return 0;
		break;
	}
}


short randomLayout(RandomizedEntry entry) {

	if (Missions) //SA2 missions 100 Rings, Lost Chao
		return rand() % 4;
	else
		return rand() % 2; 

}


int8_t prev_char = -1;


uint8_t getRandomCharacter(bool allow_duplicate) {
	
	int8_t cur_char = -1;
	size_t char_count = sizeof(character) / sizeof(character[0]);

	cur_char = character[rand() % char_count];

	while (cur_char == prev_char && ban < 5 || banCharacter[cur_char])
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

	} while (entry.character == cur_AI);
	
	
	return cur_AI;
}




short prev_stage = -1;

short getRandomStage(uint8_t char_id, bool AllowVanilla) {


	short cur_stage = -1;
	int anyLevel = - 1;
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

void Split_Init() { //speedrunner split init.

		std::ofstream myfile("SADX_Randomizer_Splits.lss");
		//Header
		myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		myfile << "<Run version=\"1.7.0\">\n";
		myfile << "<GameIcon />\n<GameName>Sonic Adventure (DX)</GameName>\n<CategoryName>Randomizer: ";
		if (StorySplits == 1)
		{
			split = 10;
			myfile << "Sonic's Story" << "</CategoryName>\n<Metadata>\n";
		}
		if (StorySplits == 2)
		{
			split = 37;
			myfile << "All Stories" << "</CategoryName>\n<Metadata>\n";
		}
		if (StorySplits == 3)
		{
			split = 21;
			myfile << "Any%" << "</CategoryName>\n<Metadata>\n";
		}
		myfile << "<Run id = \"\" />\n";
		myfile << "<Platform usesEmulator = \"False\">\n";
		myfile << "</Platform>\n<Region>\n</Region>\n<Variables />\n</Metadata>\n<Offset>00:00:00</Offset>\n<AttemptCount>0</AttemptCount>\n";
		myfile << "<AttemptHistory />\n<Segments>\n";
	

		//Segments

		//Generate a list of random levels on boot, we are looking for 10 stages + bosses if Sonic Story, 37 if all stories and 21 if Any%.

		int StageSplit = 0; //used to differentiate boss and normal stage.


		for (int i = 0; i < split; i++) { //continue to generate split until we have our specific number. 

			if (RNGCharacters)
				randomizedSets[i].character = getRandomCharacter();

			if (RNGStages)
			{
				randomizedSets[i].level = getRandomStage(randomizedSets[i].character, Vanilla);
				randomizedSets[i].act = randomacts(randomizedSets[i]);
				randomizedSets[i].layout = randomLayout(randomizedSets[i]);
			}

			if (RNGMusic)
				randomizedSets[i].music = getRandomMusic(randomizedSets[i]);

			if (isAIAllowed)
				randomizedSets[i].ai_mode = getRandomAI(randomizedSets[i]);

			TotalCount++;

			if (randomizedSets[i].character == Characters_Sonic)
			{
				randomizedSets[i].sonic_mode = rand() % 2;
				randomizedSets[i].ss_mode = rand() % 2;
			}


			myfile << "<Segment>\n";
			myfile << "<Name>";

			if (isBossStage(randomizedSets[i].level))
				myfile << "Boss: " << randomizedSets[i].level;
			else
				myfile << "Stage: " << randomizedSets[i].level;

			myfile << "</Name>\n";
			myfile << "<Icon />\n";
			myfile << "<SplitTimes>\n<SplitTime name=\"Personal Best\" />\n</SplitTimes>\n<BestSegmentTime />\n<SegmentHistory />";
			myfile << "</Segment>\n";
		}
		myfile << "</Segments>\n<AutoSplitterSettings />\n</Run>";
		myfile.close();
	

}