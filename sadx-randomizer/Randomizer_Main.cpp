#include "stdafx.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "CharactersSettings.h"
#include <fstream>
#include <iostream>
#include "RandomHelpers.h"
#include "Common.h"
#include <random>
#include <vector> 
using namespace std;


//Contain randomly generated sets of character/level/act to work with (Main Part of the mod)
struct RandomizedEntry randomizedSets[40];
short prev_stage = -1;
bool isGameOver = false;

extern bool RandCongratsDone;
extern bool isCheckpointUsed;
extern bool CasinoTails;
extern bool SA2Voices;
bool isKnucklesVersion = false;
bool isTailsVersion = false;
bool SA2Mission = false;
short CurrentMission = 0;
int CurrentStageVersion = -1;

int character[6] = { Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Gamma, Characters_Big };
int AIArray[4] = { -1, Characters_Sonic, Characters_Tails, Characters_Amy }; //Ai following you
int AIRaceArray[6] = { Characters_Sonic, Characters_Eggman, Characters_Tails, Characters_Tikal, Characters_Amy, Characters_Gamma }; //Tails Race AI


RandomizerGenerator RandoStageArray[50]{

	{LevelAndActIDs_HedgehogHammer, AmyVersion },
	{LevelAndActIDs_EmeraldCoast1, SonicVersion },
	{LevelAndActIDs_EmeraldCoast1, GammaVersion },
	{LevelAndActIDs_EmeraldCoast3, BigVersion },
	{LevelAndActIDs_WindyValley1, SonicVersion},
	{LevelAndActIDs_WindyValley1, GammaVersion},
	{LevelAndActIDs_WindyValley3, TailsVersion},
	{LevelAndActIDs_Casinopolis1, SonicVersion},
	{LevelAndActIDs_Casinopolis1, KnucklesVersion },
	{LevelAndActIDs_Casinopolis2, TailsVersion},
	{LevelAndActIDs_IceCap1, SonicVersion},
	{LevelAndActIDs_IceCap3, TailsVersion},
	{LevelAndActIDs_IceCap4, BigVersion	},
	{LevelAndActIDs_TwinklePark1, SonicVersion },
	{LevelAndActIDs_TwinklePark2, AmyVersion },
	{LevelAndActIDs_TwinklePark2, BigVersion},
	{LevelAndActIDs_SpeedHighway1, SonicVersion },
	{LevelAndActIDs_SpeedHighway1, TailsVersion },
	{LevelAndActIDs_SpeedHighway3, KnucklesVersion },
	{LevelAndActIDs_RedMountain1, SonicVersion},
	{LevelAndActIDs_RedMountain2, GammaVersion },
	{LevelAndActIDs_RedMountain3, KnucklesVersion },
	{LevelAndActIDs_SkyDeck1, SonicVersion},
	{LevelAndActIDs_SkyDeck1, TailsVersion},
	{LevelAndActIDs_SkyDeck3, KnucklesVersion },
	{LevelAndActIDs_LostWorld1, SonicVersion},
	{LevelAndActIDs_LostWorld2, KnucklesVersion },
	{LevelAndActIDs_FinalEgg1, SonicVersion },
	{LevelAndActIDs_FinalEgg1, AmyVersion },
	{LevelAndActIDs_FinalEgg3, GammaVersion  },
	{LevelAndActIDs_HotShelter1, AmyVersion },
	{LevelAndActIDs_HotShelter1, BigVersion },
	{LevelAndActIDs_HotShelter3, GammaVersion },
	{LevelAndActIDs_Chaos0, BossVersion, Characters_Sonic },
	{LevelAndActIDs_Chaos2, BossVersion, Characters_Knuckles },
	{LevelAndActIDs_Chaos4, BossVersion, Characters_Sonic || Characters_Tails || Characters_Knuckles },
	{LevelAndActIDs_Chaos6, BossVersion, Characters_Sonic },
	{LevelAndActIDs_Chaos6Two, BossVersion, Characters_Knuckles },
	{LevelAndActIDs_PerfectChaos, BossVersion, Characters_Sonic },
	{LevelAndActIDs_EggHornet, BossVersion, Characters_Sonic || Characters_Tails },
	{LevelAndActIDs_EggWalker, BossVersion, Characters_Tails},
	{LevelAndActIDs_EggViper, BossVersion, Characters_Sonic },
	{LevelAndActIDs_Zero, BossVersion, Characters_Amy},
	{LevelAndActIDs_TwinkleCircuit1, NormalVersion,},
	{LevelAndActIDs_TwinkleCircuit2, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit3, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit4, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit5, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit6, NormalVersion},
	{LevelAndActIDs_SandHill, NormalVersion, Characters_Sonic || Characters_Tails},
};		

RandomizerGenerator RandoBannedCombination[9]{

	{LevelAndActIDs_HedgehogHammer, AmyVersion, Characters_Gamma },
	{LevelAndActIDs_Chaos0, BossVersion, Characters_Gamma},
	{LevelAndActIDs_Chaos2, BossVersion, Characters_Gamma},
	{LevelAndActIDs_Chaos4, BossVersion, Characters_Gamma },
	{LevelAndActIDs_Chaos6, BossVersion, Characters_Gamma },
	{LevelAndActIDs_Chaos6Two, BossVersion, Characters_Gamma },
	{LevelAndActIDs_PerfectChaos, BossVersion, Characters_Gamma || Characters_Big },
	{LevelAndActIDs_EggViper, BossVersion, Characters_Big },
	{LevelAndActIDs_Zero, BossVersion, Characters_Gamma},
};


void getRandomStage(RandomizedEntry* entry, uint8_t Char_id) {

	RandomizerGenerator* generated;

	do {

		generated = &RandoStageArray[rand() % LengthOfArray(RandoStageArray)];

	} while (isStageBanned(generated, Char_id) || DupliCheck && isDuplicateStage(generated));

	entry->level = generated->levelAndActs >> 8;
	entry->act = generated->levelAndActs &0xf;
	entry->Layout = generated->version;

	return;
}

bool isStageBanned(RandomizerGenerator* generated, uint8_t char_id)
{
	short curVersion = generated->version;
	short curLevel = generated->levelAndActs;

	if (!Vanilla && (curVersion == char_id || curLevel == LevelAndActIDs_TwinkleCircuit1) || generated->bannedChar == char_id && curVersion == BossVersion)
		return true;

	for (uint8_t i = 0; i < LengthOfArray(RandoBannedCombination); i++)
	{
		if (curLevel == RandoBannedCombination[i].levelAndActs && char_id == RandoBannedCombination[i].bannedChar)
			return true;
	}

	if (curLevel >= LevelAndActIDs_TwinkleCircuit1 && curLevel <= LevelAndActIDs_TwinkleCircuit6)
	{
		int trick = rand() % 3;
		if (trick > 0)
			return true;
	}
	
	return false;
}

vector<short> DuplicateStages;

bool isDuplicateStage(RandomizerGenerator* generated) {

	short curLevelAndActID = generated->levelAndActs;
	short curLevel = ConvertLevelActsIDtoLevel(generated->levelAndActs);

	for (short stage: DuplicateStages)  {

		if (curLevelAndActID == stage)
			return true;

		if (DuplicateStages.back() >> 8 == curLevel || generated->version == BossVersion && DuplicateStages.back() >> 8 >= LevelIDs_Chaos0 && DuplicateStages.back() >> 8 <= LevelIDs_E101R)
			return true;
	}

	DuplicateStages.push_back(curLevelAndActID);
	return false;
}


bool isBossStage(short stage_id) 
{
	return stage_id >= LevelIDs_Chaos0 && stage_id <= LevelIDs_E101R;
}


int8_t prev_char = -1;

uint8_t getRandomCharacter() {
	int8_t cur_char = -1;
	size_t char_count = sizeof(character) / sizeof(character[0]);

	do {

		cur_char = character[rand() % char_count];
	} while (cur_char == prev_char && ban < 5 || banCharacter[cur_char]);

	prev_char = cur_char;
	return cur_char;
}

int prev_AI = -1;

//AI following you
short getRandomAI(uint8_t char_id, short stage_id) {
	int cur_AI = -1;
	size_t ai_count = sizeof(AIArray) / sizeof(AIArray[0]);

	HMODULE IsSuperTailsMod = GetModuleHandle(L"super-tails");

	if (char_id == Characters_Knuckles || char_id >= Characters_Gamma)
		return -1;

	if (stage_id >= LevelIDs_EggWalker || stage_id == LevelIDs_PerfectChaos || stage_id == LevelIDs_Chaos0)
		return -1;

	do {
		cur_AI = AIArray[rand() % ai_count];
	} while (cur_AI == prev_AI || cur_AI == char_id || IsSuperTailsMod && (char_id == Characters_Tails && cur_AI != Characters_Sonic) || (char_id != Characters_Sonic && cur_AI == Characters_Tails));

	prev_AI = cur_AI;
	return cur_AI;
}

short getRandomRaceAI(RandomizedEntry entry) {
	int8_t cur_RaceAI = -1;
	size_t ai_Racecount = sizeof(AIRaceArray) / sizeof(AIRaceArray[0]);

	cur_RaceAI = AIRaceArray[rand() % ai_Racecount];

	return cur_RaceAI;
}


int levelCount;

void SetRandomStageAct(char stage, char act) {

	if (isGameOver)
	{
		SetLevelAndAct(Uint8(stage), (Uint8)(act));
		return;
	}

	int FlagProgress = GetCharaProgression();

	if (!FlagProgress)
	{
		CustomFlag = 0;
		if (isChaoGameplayAllowed && CurrentLevel == 0 && CurrentCharacter == Characters_Gamma) //we don't want the game to play gamma cutscene
			SetLevelAndAct(LevelIDs_SSGarden, 0);
	}
	else
	{
		if (GameMode != 8 && GameMode != 10 && GameMode != 11 && GameMode < 21)
		{
			if (RNGCharacters)
			{
				CurrentCharacter = randomizedSets[levelCount].character;

				if (SuperSonic != true)
					SonicRand = randomizedSets[levelCount].ss_mode;

				if (MetalSonic != true)
					MetalSonicFlag = randomizedSets[levelCount].sonic_mode;
			}

			if (isAIAllowed)
				CurrentAI = randomizedSets[levelCount].ai_mode;

			LastLevel = CurrentLevel;
			CurrentMission = 0;
			GetCustomLayout = 0;
			CurrentLevel = RNGStages ? randomizedSets[levelCount].level : stage;
			CurrentAct = randomizedSets[levelCount].act;

			levelCount++;

			if (levelCount == TotalCount)
				Randomizer_GetNewRNG(); //reroll once the 40 stages have been beated.

			return;
		}
	}

	return SetLevelAndAct(Uint8(stage), (Uint8)(act));
}

void GoToNextLevel_hook(char stage, char act) {

	if (isGameOver) //do not randomize stage / character
	{
		SetLevelAndAct(Uint8(stage), (Uint8)(act)); 
		return;
	}

	if (GameMode != 8 && GameMode != 10 && GameMode != 11 && GameMode < 21)
	{
		if (RNGCharacters)
		{
			CurrentCharacter = randomizedSets[levelCount].character;

			if (SuperSonic != true)
				SonicRand = randomizedSets[levelCount].ss_mode;

			if (MetalSonic != true)
				MetalSonicFlag = randomizedSets[levelCount].sonic_mode;
		}

		if (isAIAllowed)
			CurrentAI = randomizedSets[levelCount].ai_mode;

		//fix mission card display + load stage properly
		if (RNGStages && (SelectedCharacter == 3 && EventFlagArray[EventFlags_Amy_TwinkleParkClear] == 0) || SelectedCharacter == 2 && EventFlagArray[EventFlags_Knuckles_SpeedHighwayClear] == 0) 
		{
			CurrentVideo = 0;
			CutsceneMode = 0;
		}

		LastLevel = CurrentLevel;
		CurrentMission = 0;
		GetCustomLayout = 0;

		if (isChaoGameplayAllowed && CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past && CustomFlag == 0)
		{
			SetLevelAndAct(LevelIDs_SSGarden, 0);
		}
		else
		{
			CurrentLevel = RNGStages ? randomizedSets[levelCount].level : stage;
			CurrentAct = randomizedSets[levelCount].act;
			levelCount++;
		}

		if (levelCount == TotalCount)
			Randomizer_GetNewRNG(); //reroll once the 40 stages have been beated.

		return;
	}

	return GoToNextLevel();
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


void GameOver_R() {

	isGameOver = true;
	isCheckpointUsed = false;
	InitializeSoundManager();
	return;
}

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


void Create_NewRNG() {

	for (uint32_t i = 0; i < split; i++) { //generate 40 levels without any speedrunners splits.

		if (RNGCharacters)
			randomizedSets[i].character = getRandomCharacter();

		if (RNGStages)
			getRandomStage(&randomizedSets[i], randomizedSets[i].character);

			randomizedSets[i].SA2Mission = randomSA2Mission(randomizedSets[i].level);
		 
		if (RNGMusic)
			randomizedSets[i].music = getRandomMusic(randomizedSets[i]);

		if (isAIAllowed)
			randomizedSets[i].ai_mode = getRandomAI(randomizedSets[i].character, randomizedSets[i].level);

			randomizedSets[i].ai_race = getRandomRaceAI(randomizedSets[i]);

		if (randomizedSets[i].character == Characters_Sonic && RNGCharacters)
		{
			randomizedSets[i].sonic_mode = rand() % 2;
			randomizedSets[i].ss_mode = rand() % 2;
		}

		TotalCount++;
	}
}


void Randomizer_GetNewRNG() {

	ResetValueWhileLevelResult();
	TotalCount = 0;
	levelCount = 0;
	split = 0;
	DuplicateStages.clear();

	if (!StorySplits)
	{
		split = 40;
		Create_NewRNG();
	}
	else
	{
		//Splits Initialization
		Split_Init();
	}
}


void Split_Init() { //speedrunner split init. Used when you start the game.
	std::ofstream myfile("SADX_Randomizer_Splits.lss");
	//Header
	myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	myfile << "<Run version=\"1.7.0\">\n";
	myfile << "<GameIcon />\n<GameName>Sonic Adventure DX: Randomizer</GameName>\n<CategoryName> ";
	if (StorySplits == SonicStorySplit)
	{
		split = 10;
		myfile << "Sonic's Story" << "</CategoryName>\n<Metadata>\n";
	}
	if (StorySplits == AllStoriesSplit)
	{
		split = 37;
		myfile << "All Stories" << "</CategoryName>\n<Metadata>\n";
	}

	myfile << "<Run id = \"\" />\n";
	myfile << "<Platform usesEmulator = \"False\">PC\</Platform>\n";
	myfile << "<Region>\n</Region>\n<Variables>\n";

	if (!SeedCopy)
		myfile << " <Variable name=\"Seed\">Seed 0</Variable>\n";
	else
		myfile << "<Variable name=\"Seed\">Set Seed</Variable>\n";

	myfile << "</Variables>\n";
	myfile << "</Metadata>\n<Offset>00:00:00</Offset>\n<AttemptCount>0</AttemptCount>\n";
	myfile << "<AttemptHistory />\n<Segments>\n";

	//Segments

	//Generate a list of random levels on boot, we are looking for 10 stages + bosses if Sonic Story, 37 if all stories and 21 if Any%.
	
	Create_NewRNG();

	for (uint32_t i = 0; i < TotalCount; i++) { //continue to generate split until we have our specific number.

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
		WriteCall((void*)0x417bed, GameOver_R);
		WriteCall((void*)0x41717d, GameOver_R);
	}
}