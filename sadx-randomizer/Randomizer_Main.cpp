#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include "RandomHelpers.h"


extern char GetCustomLayout;
extern char StorySplits;
extern int CustomFlag;
extern bool ChaoSpawn;
extern bool RandCongratsDone;
extern bool isPlayerInWaterSlide;
bool TreasureHunting = false;
int musicCount;
extern bool isCheckpointUsed;

//Credits stats
int RageQuit = 0;
int JumpCount = 0;
int ringsPB = 0;
int chaoPB = 0;
int animalPB = 0;
int killPB = 0;
int hurtsPB = 0;
int deathsPB = 0;
int TotalDeathsPB = 0;
int TotalHurtsPB = 0;
int AISwapCount = 0;

int character[6] = { Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Gamma, Characters_Big };
int AIArray[4] = { -1, Characters_Sonic, Characters_Tails, Characters_Amy }; //Ai following you
int AIRaceArray[6] = { Characters_Sonic, Characters_Eggman, Characters_Tails, Characters_Tikal, Characters_Amy, Characters_Gamma }; //Tails Race AI

int TwinkleCircuitRNG = 0;
int level[22] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 16, 18, 19, 20, 21, 22, 23, 35, 38 };

//Banned level list, there is few stage impossible to beat, depending on the character.
int bannedLevelsGamma[8] = { LevelIDs_HedgehogHammer, LevelIDs_Chaos0, LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggWalker, LevelIDs_Zero };
int bannedLevelsBig[2] = { LevelIDs_PerfectChaos , LevelIDs_EggViper };

//Initiliaze banned Vanilla stage (if option is checked)
int bannedRegularSonic[7] = { LevelIDs_Chaos0, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggHornet, LevelIDs_EggViper, LevelIDs_SandHill };
int bannedRegularTails[4] = { LevelIDs_Chaos4, LevelIDs_EggHornet, LevelIDs_EggWalker, LevelIDs_SandHill };
int bannedRegularKnuckles[3] = { LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6 };
int bannedRegularAmy[1] = { LevelIDs_Zero };
int bannedRegularGamma[2] = { LevelIDs_E101, LevelIDs_E101R };

//Few jingle that we don't want in the random music function.
int bannedMusic[29] = { 0x11, 0x1A, 0x29, 0x2C, 0x2e, 0x31, 0x37, 0x38, 0x45, 0x47, 0x4B, 0x55, 0x60, 0x61, 0x62, 0x63, 0x64, 0x66, 0x6e, 0x6f, 0x70, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b };

//Contain randomly generated sets of character/level/act to work with (Main Part of the mod)

struct RandomizedEntry randomizedSets[40];

short randomacts(RandomizedEntry entry) {
	//Set up act rng.
	int actHS[2] = { 0, 2 };
	int act0[3] = { 0, 0, 1 }; //increasing chance to get act 1
	int act1[3] = { 0, 0, 2 };
	int actIC[2] = { 0, 3 };

	switch (entry.level)
	{
	case LevelIDs_EmeraldCoast:
		if (entry.character == Characters_Big && !Vanilla)
			return 0;
		else
			return act1[rand() % 3];
		break;
	case LevelIDs_WindyValley:
		if (entry.character == Characters_Big || entry.character == Characters_Tails)
			return 0;
		else
			return actHS[rand() % 2];
		break;
	case LevelIDs_TwinklePark:
		if (entry.character == Characters_Sonic && !Vanilla)
			return 1;
		if (entry.character == Characters_Amy && !Vanilla)
			return 0;
		else
			return rand() % 2;
		break;
	case LevelIDs_SpeedHighway:
		if (entry.character == Characters_Knuckles && !Vanilla)
			return 0;
		else
			return actHS[rand() % 2];
		break;
	case LevelIDs_RedMountain:
		if (entry.character == Characters_Sonic && !Vanilla)
			return actHS[rand() % 2];
		if (entry.character == Characters_Gamma && !Vanilla)
			return actHS[rand() % 2];
		if (entry.character != Characters_Gamma && entry.character != Characters_Sonic || Vanilla)
			return rand() % 3;
		break;
	case LevelIDs_SkyDeck:
		if (entry.character == Characters_Knuckles && !Vanilla)
			return 0;
		else
			return actHS[rand() % 2];
		break;
	case LevelIDs_LostWorld:
		if (entry.character == Characters_Knuckles && !Vanilla)
			return 0;
		else if (entry.character == Characters_Sonic && !Vanilla)
			return 1;
		else
			return rand() % 2;
		break;
	case LevelIDs_IceCap:
		if (entry.character == Characters_Big && !Vanilla)
			return 0;
		if (entry.character == Characters_Sonic && !Vanilla)
			return 3;
		else
			return actIC[rand() % 2];
		break;
	case LevelIDs_Casinopolis:
		if (entry.character == Characters_Tails || entry.character == Characters_Big)
			return 0;
		else
			return act0[rand() % 3];
		break;
	case LevelIDs_FinalEgg:
		if (entry.character == Characters_Gamma && !Vanilla)
			return 0;
		else
			return actHS[rand() % 2];
		break;
	case LevelIDs_HotShelter:
		if (!Vanilla && entry.character == Characters_Gamma)
			return 0;
		else
			return actHS[rand() % 2];
		break;
	case LevelIDs_Chaos6:
			return rand() % 2;
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

short prev_mission = -1;

short randomLayout(RandomizedEntry entry) {
	short cur_mission = -1;

	do {
		if (Missions) //SA2 missions 100 Rings, Lost Chao (also SADX Tails Race and Knux Treasure Hunting)
			cur_mission = rand() % 4;
		else
			cur_mission = rand() % 2;
	} while (prev_mission == cur_mission);

	prev_mission = cur_mission;
	return cur_mission;
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

int8_t prev_AI = -1;

//AI following you
short getRandomAI(RandomizedEntry entry) {
	int8_t cur_AI = -1;
	size_t ai_count = sizeof(AIArray) / sizeof(AIArray[0]);

	do {
		cur_AI = AIArray[rand() % ai_count];
	} while (cur_AI == prev_AI);

	prev_AI = cur_AI;
	return cur_AI;
}

short getRandomRaceAI(RandomizedEntry entry) {
	int8_t cur_RaceAI = -1;
	size_t ai_Racecount = sizeof(AIRaceArray) / sizeof(AIRaceArray[0]);

	cur_RaceAI = AIRaceArray[rand() % ai_Racecount];

	return cur_RaceAI;
}

short prev_stage = -1;

short getRandomStage(uint8_t char_id, bool AllowVanilla) {
	AllowVanilla = Vanilla;
	short cur_stage = -1;

	do {
		cur_stage = level[rand() % LengthOfArray(level)];

	} while (isRegularStageBanned(char_id, cur_stage) && !AllowVanilla || isStageBanned(char_id, cur_stage) || cur_stage == prev_stage || cur_stage > 14 && cur_stage < 26 && prev_stage > 14 && prev_stage < 26);

	if (cur_stage == LevelIDs_HedgehogHammer || cur_stage == LevelIDs_TwinkleCircuit || cur_stage == LevelIDs_PerfectChaos || cur_stage >= LevelIDs_EggWalker && cur_stage < LevelIDs_Zero) //reduce the chance to get TC and few bosses.
	{
		short trick = 0;
		trick = rand() % 3;

		if (trick >= 1)
		{
			do {
				cur_stage = level[rand() % 15]; //pick a random stage instead.
			} while (isRegularStageBanned(char_id, cur_stage) && !AllowVanilla || isStageBanned(char_id, cur_stage) || cur_stage == prev_stage);
		}
	}

	prev_stage = cur_stage;
	return cur_stage;
}

bool isRegularStageBanned(uint8_t char_id, short stage_id) {
	int* bannedVanillaStages = nullptr;
	size_t arraySize = 0;

	bool result;
	switch (char_id) {
	case Characters_Sonic:
		bannedVanillaStages = bannedRegularSonic;
		arraySize = LengthOfArray(bannedRegularSonic);
		break;
	case Characters_Tails:
		bannedVanillaStages = bannedRegularTails;
		arraySize = LengthOfArray(bannedRegularTails);
		break;
	case Characters_Knuckles:
		bannedVanillaStages = bannedRegularKnuckles;
		arraySize = LengthOfArray(bannedRegularKnuckles);
		break;
	case Characters_Amy:
		bannedVanillaStages = bannedRegularAmy;
		arraySize = LengthOfArray(bannedRegularAmy);
		break;
	case Characters_Gamma:
		bannedVanillaStages = bannedRegularGamma;
		arraySize = LengthOfArray(bannedRegularGamma);
		break;
	default:
		//If you reach this place, you're definitely doing something wrong
		return false;
		break;
	}

	result = isValueInArray(bannedVanillaStages, stage_id, arraySize);
	return result;
}

bool isStageBanned(uint8_t char_id, short stage_id) {
	int* bannedStages = nullptr;
	size_t arraySize = 0;

	bool result;
	switch (char_id) {
	case Characters_Gamma:
		bannedStages = bannedLevelsGamma;
		arraySize = LengthOfArray(bannedLevelsGamma);
		break;
	case Characters_Big:
		bannedStages = bannedLevelsBig;
		arraySize = LengthOfArray(bannedLevelsBig);
		break;
	default:
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

int GetCharaProgression() {

	if (!CustomFlag)
	{
		ChaoGardenSSWarpOpen = 1;
		ChaoGardenECWarpOpen = 1;
		ChaoGardenMRWarpOpen = 1;

		switch (SelectedCharacter)
		{
		case 0:
			if (EventFlagArray[EventFlags_Sonic_Chaos0Clear] == 0)
				return 0;
			break;
		case 1:
			if (EventFlagArray[EventFlags_Tails_EggHornetClear] == 0)
				return 0;
			break;
		case 2:
			if (EventFlagArray[EventFlags_Knuckles_SpeedHighwayClear] == 0)
				return 0;
			break;
		case 3:
			if (EventFlagArray[EventFlags_Amy_TwinkleParkClear] == 0)
				return 0;
			break;
		case 4:
			if (EventFlagArray[EventFlags_Big_TwinkleParkClear] == 0)
				return 0;
			break;
		default: 
			return 1;
			break;
		}
	}

	return 1;
}

int levelCount;

void SetRandomStageAct(char stage, char act) {

	int FlagProgress = GetCharaProgression();

	if (FlagProgress != 0)
	{
		if (GameMode != 8 && GameMode != 10 && GameMode != 11 && GameMode < 21)
		{
			if (RNGCharacters)
				CurrentCharacter = randomizedSets[levelCount].character;

			if (SuperSonic != true)
				SonicRand = randomizedSets[levelCount].ss_mode;

			if (MetalSonic != true)
				MetalSonicFlag = randomizedSets[levelCount].sonic_mode;

			CurrentAI = randomizedSets[levelCount].ai_mode;

			LastLevel = CurrentLevel;
			CurrentLevelLayout = 0;
			GetCustomLayout = 0;
			CurrentLevel = RNGStages ? randomizedSets[levelCount].level : stage;
			CurrentAct = randomizedSets[levelCount].act;

			levelCount++;

			if (levelCount == TotalCount)
			{
				GetNewLevel(); //reroll once the 40 stages have been beated.
			}
		}
		else
		{
			SetLevelAndAct(stage, act);
		}
	}
	else
	{
		SetLevelAndAct(stage, act);
	}

	return;
}

void GoToNextLevel_hook(char stage, char act) {
	if (GameMode != 8 && GameMode != 10 && GameMode != 11 && GameMode < 21)
	{
		if (RNGCharacters)
			CurrentCharacter = randomizedSets[levelCount].character;

		if (SuperSonic != true)
			SonicRand = randomizedSets[levelCount].ss_mode;

		if (MetalSonic != true)
			MetalSonicFlag = randomizedSets[levelCount].sonic_mode;

		CurrentAI = randomizedSets[levelCount].ai_mode;

		LastLevel = CurrentLevel;
		CurrentLevelLayout = 0;
		GetCustomLayout = 0;
		CurrentLevel = RNGStages ? randomizedSets[levelCount].level : stage;
		CurrentAct = randomizedSets[levelCount].act;

		levelCount++;


		if (levelCount == TotalCount)
		{
			GetNewLevel(); //reroll once the 40 stages have been beated.
		}
	}
	else
	{
		SetLevelAndAct(stage, act);
	}

	return;
}

extern ObjectMaster* TriggerOBJ;
extern ObjectMaster* TriggerHS;

void ResetStatsValues() {
	isAIActive = false;
	TreasureHunting = false;
	ChaoSpawn = false;
	KnuxCheck = 0;
	KnuxCheck2 = 0; //fix trial crash
	CurrentAI = 0;
	SonicRand = 0;
	TransfoCount = 0;
	CurrentLevelLayout = 0;
	CurrentMission = 0;
	GetCustomLayout = 0;
	Credits_State = 0;
	RageQuit++;
	ringsPB += Rings; //total Rings credit stat
	Race = false;
	RandCongratsDone = false;
	isPlayerInWaterSlide = false;
	isCheckpointUsed = false;
	fixTCCart();
	Delete_Cart();


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

//Fix Trial Mode
void SetLevelAndAct_R() {
	if (EventFlagArray[EventFlags_SuperSonicAdventureComplete] == 1)
	{
		if (GameMode == GameModes_Menu)
		{
			if (LevelList == 14 || LevelList == 238 || LevelList == 212 || LevelList == 138 || LevelList == 257)
				SetRandomStageAct((char)CurrentLevel, (char)CurrentAct);
			else
				return;
		}
	}

	return;
}

//randomize voices
void RandomVoice() {
	if (VoicesEnabled != 0) {
		CurrentVoiceNumber = rand() % 2043;
	}

	return;
}

short prev_music = -1;

short getRandomMusic(RandomizedEntry entry) {
	short cur_music = -1;

	do {
		cur_music = rand() % 125;
	} while (cur_music == prev_music || isValueInArray(bannedMusic, cur_music, 29));

	prev_music = cur_music;

	return cur_music;
}

void RandomMusic() {
	if (Music_Enabled != 0) {

		CurrentSong = randomizedSets[musicCount].music;
		LastSong = CurrentSong;

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

void PlayMusic_R(MusicIDs song) {

	if (Music_Enabled != 0) {
		CurrentSong = song;
		LastSong = song;
	}

	return;
}

void PlayVoice_R(int a1) {

	if (VoicesEnabled != 0) {
		CurrentVoiceNumber = a1;
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

void PauseMenuFix() {
	//Display Current Mission Information
	if (CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel < LevelIDs_Chaos0)
	{
		SetDebugFontSize(13.0f * (float)VerticalResolution / 480.0f);

		if (TreasureHunting && CurrentLevelLayout == Mission1_Variation)
			DisplayDebugString(NJM_LOCATION(2, 5), "Current Mission: M1 (Treasure Hunting)");

		if (CurrentLevelLayout <= Mission1_Variation && !TreasureHunting)
			DisplayDebugString(NJM_LOCATION(2, 5), "Current Mission: M1 (Beat the Stage)");

		if (CurrentLevelLayout == Mission2_100Rings)
			DisplayDebugString(NJM_LOCATION(2, 5), "Current Mission: M2 (100 Rings)");

		if (CurrentLevelLayout == Mission3_LostChao)
			DisplayDebugString(NJM_LOCATION(2, 5), "Current Mission: M3 (Lost Chao)");
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

extern int SeedCopy;

void DisplayRandoInformation() {

		SetDebugFontSize(13.0f * (unsigned short)VerticalResolution / 480.0f);
		DisplayDebugStringFormatted(NJM_LOCATION(2, 1), "Current Seed: %d", SeedCopy);

		if (ban != 0)
			DisplayDebugString(NJM_LOCATION(2, 2), "Character Roster: Edited");
		else
			DisplayDebugString(NJM_LOCATION(2, 2), "Character Roster: Normal");

		if (Vanilla)
			DisplayDebugString(NJM_LOCATION(2, 3), "Vanilla Stage: Allowed");
		else
			DisplayDebugString(NJM_LOCATION(2, 3), "Vanilla Stage: Banned");

		switch (StorySplits)
		{
		case 1:
			DisplayDebugString(NJM_LOCATION(2, 4), "Actual Splits: Sonic's Story");
			break;
		case 2:
			DisplayDebugString(NJM_LOCATION(2, 4), "Actual Splits: All Stories");
			break;
		case 3:
			DisplayDebugString(NJM_LOCATION(2, 4), "Actual Splits: Any%");
			break;
		}
}

void GetNewLevel() {
	for (int i = 0; i < 40; i++) { //generate 40 new levels. Used if you reach the maximum of level during a run.
		if (RNGCharacters)
			randomizedSets[i].character = getRandomCharacter();

		if (RNGStages)
		{
			randomizedSets[i].level = getRandomStage(randomizedSets[i].character, Vanilla);
			randomizedSets[i].act = randomacts(randomizedSets[i]);
		}

		randomizedSets[i].LevelLayout = randomLayout(randomizedSets[i]);

		if (RNGMusic)
			randomizedSets[i].music = getRandomMusic(randomizedSets[i]);

		if (isAIAllowed)
			randomizedSets[i].ai_mode = getRandomAI(randomizedSets[i]);

		randomizedSets[i].ai_race = getRandomRaceAI(randomizedSets[i]);

		if (randomizedSets[i].character == Characters_Sonic)
		{
			randomizedSets[i].sonic_mode = rand() % 2;
			randomizedSets[i].ss_mode = rand() % 2;
		}

		levelCount = 0;
		return;
	}
}

void Split_Init() { //speedrunner split init. Used when you start the game.
	std::ofstream myfile("SADX_Randomizer_Splits.lss");
	//Header
	myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	myfile << "<Run version=\"1.7.0\">\n";
	myfile << "<GameIcon />\n<GameName>Sonic Adventure (DX)</GameName>\n<CategoryName>Randomizer: ";
	if (StorySplits == SonicStory)
	{
		split = 10;
		myfile << "Sonic's Story" << "</CategoryName>\n<Metadata>\n";
	}
	if (StorySplits == AllStories)
	{
		split = 37;
		myfile << "All Stories" << "</CategoryName>\n<Metadata>\n";
	}
	if (StorySplits == AnyPourcent)
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

	for (unsigned int i = 0; i < split; i++) { //continue to generate split until we have our specific number.
		if (RNGCharacters)
			randomizedSets[i].character = getRandomCharacter();

		if (RNGStages)
		{
			randomizedSets[i].level = getRandomStage(randomizedSets[i].character, Vanilla);
			randomizedSets[i].act = randomacts(randomizedSets[i]);
		}

		randomizedSets[i].LevelLayout = randomLayout(randomizedSets[i]);

		if (RNGMusic)
			randomizedSets[i].music = getRandomMusic(randomizedSets[i]);

		if (isAIAllowed)
			randomizedSets[i].ai_mode = getRandomAI(randomizedSets[i]);

		randomizedSets[i].ai_race = getRandomRaceAI(randomizedSets[i]);

		if (randomizedSets[i].character == Characters_Sonic)
		{
			randomizedSets[i].sonic_mode = rand() % 2;
			randomizedSets[i].ss_mode = rand() % 2;
		}

		TotalCount++;

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

	return;
}

void RandomizeStages_Hook() {
	if (RNGStages == true)
	{
		WriteData<6>((void*)0x506512, 0x90); //remove Last Story Flag
		//WriteData<1>((void*)0x40c6c0, 0x04); //force gamemode to 4 (action stage.)

		WriteCall((void*)0x50659a, SetLevelAndAct_R); //Remove one "SetLevelAndAct" as it's called twice and Fix trial mod RNG.

		WriteCall((void*)0x41709d, GoToNextLevel_hook); //hook "Go to next level"
		WriteCall((void*)0x417b47, GoToNextLevel_hook); //GameStateHandler_Adventure hook after movie cutscene
		//Redirect SetLevelAndAct in FUN_0x4133e0

		WriteData<5>((void*)0x4134f3, 0x90); //Remove SetLevelAndAct when loading adventure data
		WriteData<1>((void*)0x413502, 0x08);

		WriteCall((void*)0x41348f, SetRandomStageAct); //hook SetLevelAndAct when loading adventure data (used when savefile is complete.)
		WriteCall((void*)0x41342a, SetRandomStageAct); //hook SetLevelAndAct when loading adventure data
		WriteCall((void*)0x4134a2, SetRandomStageAct); //hook SetLevelAndAct when loading adventure data

		WriteCall((void*)0x4db0b3, TwinkleCircuitResult); //Twinkle Circuit Stuff
		WriteData<1>((void*)0x4DB0B2, 0x05);
		WriteData<5>((void*)0x4db051, 0x90);
		WriteCall((void*)0x416be2, CancelResetPosition); //hook "SetStartPos_ReturnToField" used to cancel the reset character position to 0 after quitting a stage.
	}

}