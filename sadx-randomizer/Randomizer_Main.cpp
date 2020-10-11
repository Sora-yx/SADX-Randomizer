#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector> 
#include "Cutscene.h"

using std::string;
using std::vector;

//Contain randomly generated sets of character/level/act to work with (Main Part of the mod)
struct RandomizedEntry randomizedSets[40];
short prev_stage = -1;
bool isGameOver = false;
int8_t CurrentStageVersion = 0;

int character[6] = { Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Gamma, Characters_Big };

//Banned level list, there is few stage impossible to beat, depending on the character.
int bannedLevelsGamma[7] = { LevelIDs_HedgehogHammer, LevelIDs_Chaos0, LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_EggWalker, LevelIDs_PerfectChaos };
int bannedLevelsBig[2] = { LevelIDs_PerfectChaos , LevelIDs_EggViper };

//Initiliaze banned Vanilla stage (if option is enabled)
int bannedRegularSonicAndTails[3] = { LevelIDs_Chaos4, LevelIDs_EggHornet, LevelIDs_SandHill };
int bannedRegularGamma[2] = { LevelIDs_E101, LevelIDs_E101R };

RandomizerGenerator RandoStageArray[50]{

	{LevelAndActIDs_HedgehogHammer, AmyVersion, Characters_Amy, },
	{LevelAndActIDs_EmeraldCoast1, SonicVersion, Characters_Sonic },
	{LevelAndActIDs_EmeraldCoast1, GammaVersion, Characters_Gamma },
	{LevelAndActIDs_EmeraldCoast3, BigVersion, Characters_Big },
	{LevelAndActIDs_WindyValley1, SonicVersion, Characters_Sonic},
	{LevelAndActIDs_WindyValley1, GammaVersion, Characters_Gamma},
	{LevelAndActIDs_WindyValley3, TailsVersion, Characters_Tails},
	{LevelAndActIDs_Casinopolis1, SonicVersion, Characters_Sonic},
	{LevelAndActIDs_Casinopolis1, KnucklesVersion, Characters_Knuckles },
	{LevelAndActIDs_Casinopolis2, TailsVersion, Characters_Tails},
	{LevelAndActIDs_IceCap1, SonicVersion, Characters_Sonic},
	{LevelAndActIDs_IceCap3, TailsVersion, Characters_Tails},
	{LevelAndActIDs_IceCap4, BigVersion, Characters_Big},
	{LevelAndActIDs_TwinklePark1, SonicVersion, Characters_Sonic },
	{LevelAndActIDs_TwinklePark2, AmyVersion, Characters_Amy },
	{LevelAndActIDs_TwinklePark2, BigVersion, Characters_Big },
	{LevelAndActIDs_SpeedHighway1, SonicVersion, Characters_Sonic },
	{LevelAndActIDs_SpeedHighway1, TailsVersion, Characters_Tails },
	{LevelAndActIDs_SpeedHighway3, KnucklesVersion, Characters_Knuckles },
	{LevelAndActIDs_RedMountain1, SonicVersion, Characters_Sonic},
	{LevelAndActIDs_RedMountain2, GammaVersion, Characters_Gamma },
	{LevelAndActIDs_RedMountain3, KnucklesVersion, Characters_Knuckles },
	{LevelAndActIDs_SkyDeck1, SonicVersion, Characters_Sonic},
	{LevelAndActIDs_SkyDeck1, TailsVersion, Characters_Tails},
	{LevelAndActIDs_SkyDeck3, KnucklesVersion, Characters_Knuckles },
	{LevelAndActIDs_LostWorld1, SonicVersion, Characters_Sonic},
	{LevelAndActIDs_LostWorld2, KnucklesVersion, Characters_Knuckles },
	{LevelAndActIDs_FinalEgg1, SonicVersion, Characters_Sonic },
	{LevelAndActIDs_FinalEgg1, AmyVersion, Characters_Amy },
	{LevelAndActIDs_FinalEgg3, GammaVersion, Characters_Gamma,},
	{LevelAndActIDs_HotShelter1, AmyVersion, Characters_Amy },
	{LevelAndActIDs_HotShelter1, BigVersion, Characters_Big },
	{LevelAndActIDs_HotShelter3, GammaVersion, Characters_Gamma },
	{LevelAndActIDs_Chaos0, BossVersion, Characters_Sonic },
	{LevelAndActIDs_Chaos2, BossVersion, Characters_Knuckles },
	{LevelAndActIDs_Chaos4, BossVersion, Characters_Knuckles},
	{LevelAndActIDs_Chaos6, BossVersion, Characters_Sonic },
	{LevelAndActIDs_Chaos6Two, BossVersion, Characters_Knuckles },
	{LevelAndActIDs_PerfectChaos, BossVersion, Characters_Sonic },
	{LevelAndActIDs_EggHornet, BossVersion, Characters_Tails },
	{LevelAndActIDs_EggWalker, BossVersion, Characters_Tails},
	{LevelAndActIDs_EggViper, BossVersion, Characters_Sonic },
	{LevelAndActIDs_Zero, BossVersion, Characters_Amy},
	{LevelAndActIDs_TwinkleCircuit1, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit2, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit3, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit4, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit5, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit6, NormalVersion},
	{LevelAndActIDs_SandHill, TailsVersion, Characters_Tails},
};		


void getRandomStage(RandomizedEntry* entry, uint8_t Char_id) {

	RandomizerGenerator* generated;

	do {

		generated = &RandoStageArray[rand() % LengthOfArray(RandoStageArray)];

	} while (isStageBanned(generated, Char_id) || !Vanilla && isVanillaStage(generated, Char_id) || DupliCheck && isDuplicateStage(generated)); //Order check here is really important, dupli check MUST be the last thing checked.

	entry->level = generated->levelAndActs >> 8;
	entry->act = generated->levelAndActs & 0xf;
	entry->Layout = generated->version;
	return;
}


bool isStageBanned(RandomizerGenerator* generated, uint8_t char_id)
{

	short curLevel = generated->levelAndActs;
	short curSingleLevel = generated->levelAndActs >> 8;
	short curAct = generated->levelAndActs & 0xF;
	uint8_t curBannedChar = generated->bannedChar;
	short curChar = char_id;

	for (uint8_t i = 0; i < LengthOfArray(bannedLevelsBig); i++)
	{
		if (curSingleLevel == bannedLevelsBig[i] && char_id == Characters_Big)
			return true;
	}

	for (uint8_t i = 0; i < LengthOfArray(bannedLevelsGamma); i++)
	{
		if (curSingleLevel == bannedLevelsGamma[i] && char_id == Characters_Gamma)
			return true;
	}

	return false;
}


bool isVanillaStage(RandomizerGenerator* generated, uint8_t char_id)
{

	short curSingleLevel = generated->levelAndActs >> 8;
	uint8_t curBannedChar = generated->bannedChar;

	if (curBannedChar == char_id)
		return true;

	for (uint8_t i = 0; i < LengthOfArray(bannedRegularSonicAndTails); i++)
	{
		if (curSingleLevel == bannedRegularSonicAndTails[i] && (char_id == Characters_Sonic || char_id == Characters_Tails))
			return true;
	}

	if (char_id == curBannedChar)
		return true;
	
	return false;
}



vector<RandomizerGenerator> DuplicateStages;
RandomizerGenerator StructDupli;

int TCCount = 0;
int oldStageVersion = -1;
bool isDuplicateStage(RandomizerGenerator* generated) {

	std::ofstream myfile("VectorDebug.txt", std::ios_base::app);
	myfile << "\n";

	short curLevelAndActID = generated->levelAndActs;
	short curVersion = generated->version;
	short curLevel = ConvertLevelActsIDtoLevel(curLevelAndActID);


	for (RandomizerGenerator stage: DuplicateStages)  {

		if (DuplicateStages.size() != 0 && curVersion == BossVersion && DuplicateStages.back().version == BossVersion)
		{
			myfile << "Previous Level was already a Boss: " << curLevel;
			return true;
		}

		if (DuplicateStages.size() >= 40) //Prevent infinite loop.
		{
			myfile << "STOOOOOOP";
			return false;
		}

		if (DuplicateStages.size() != 0 && (curLevelAndActID == stage.levelAndActs && curVersion == stage.version) || DuplicateStages.back().levelAndActs >> 8 == curLevel)
		{
			myfile << "Prevous Stage: " << curLevel;
			myfile << " Previous Version: " << curVersion;
			return true;
		}
	}

	if (TCCount >= 2 && curLevel == LevelIDs_TwinkleCircuit)
		return true;
	else if (curLevel == LevelIDs_TwinkleCircuit)
		TCCount++;

	if (oldStageVersion == curVersion && (oldStageVersion == TailsVersion || oldStageVersion == KnucklesVersion) && DuplicateStages.size() < 40) {
		myfile << "Same custom stage lol: " << curLevel;
		return true;
	}

	myfile << "Added Level: " << curLevel;
	myfile << " Added Version: " << curVersion;
	StructDupli.levelAndActs = curLevelAndActID;
	StructDupli.version = curVersion;
	DuplicateStages.push_back(StructDupli);
	oldStageVersion = curVersion;
	myfile.close();
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



uint8_t prev_Sanic = -1;
uint8_t GetRandomSonicTransfo(uint8_t char_id) {

	int8_t cur_Sanic = -1;

	if (char_id == Characters_Sonic) {
		do {

			cur_Sanic = rand() % 3;
		} while (cur_Sanic == prev_Sanic || MetalSonic && cur_Sanic == 1 || SuperSonic && cur_Sanic == 2);
	}

	prev_Sanic = cur_Sanic;
	return cur_Sanic;
}

int levelCount;

void SetInfoNextRandomStage(char Stage, char Act) {
	if (RNGCharacters)
	{
		CurrentCharacter = randomizedSets[levelCount].character;
		SonicRand = randomizedSets[levelCount].sonic_transfo;

		if (SonicRand == 1)
			MetalSonicFlag = SonicRand;
	}

	if (isAIAllowed)
		CurrentAI = randomizedSets[levelCount].ai_mode;

	LastLevel = CurrentLevel;
	CurrentLevel = RNGStages ? randomizedSets[levelCount].level : Stage;
	CurrentAct = RNGStages ? randomizedSets[levelCount].act : Act;
	CurrentMission = randomizedSets[levelCount].SA2Mission;
	CurrentStageVersion = randomizedSets[levelCount].Layout;
	levelCount++;
}

extern bool isCutsceneAllowed;
void SetRandomStageAct(char stage, char act) {

	if (isGameOver)
	{
		SetLevelAndAct(Uint8(stage), (Uint8)(act));
		return;
	}

	if (!GetCharaProgression())
	{
		CustomFlag = 0;
		if (isChaoGameplayAllowed && CurrentLevel == 0 && CurrentCharacter == Characters_Gamma) { //we don't want the game to play gamma cutscene
			SetLevelAndAct(LevelIDs_SSGarden, 0);
			return;
		}

		isCutsceneAllowed = true;
	}

	if (GameMode != 8 && GameMode != 10 && GameMode != 11 && GameMode < 21)
	{

		bool isCutscene = CheckAndPlayRandomCutscene();
		if (!isCutscene)
			SetInfoNextRandomStage(stage, act);
		else
			return;

		if (levelCount == TotalCount)
			Randomizer_GetNewRNG(); //reroll once the player reached 40 stages.

		return;
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
		//fix mission card display + load stage properly
		if (RNGStages && (SelectedCharacter == 3 && EventFlagArray[EventFlags_Amy_TwinkleParkClear] == 0) || SelectedCharacter == 2 && EventFlagArray[EventFlags_Knuckles_SpeedHighwayClear] == 0)
		{
			CurrentVideo = 0;
			CutsceneMode = 0;
		}

		if (isChaoGameplayAllowed && CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past && CustomFlag == 0) {
			SetLevelAndAct(LevelIDs_SSGarden, 0);
			return;
		}

		bool isCutscene = CheckAndPlayRandomCutscene();

		if (!isCutscene)
			SetInfoNextRandomStage(stage, act);

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
			if (ValueMenu == 14 || ValueMenu == 238 || ValueMenu == 212 || ValueMenu == 138 || ValueMenu == 257)
				SetRandomStageAct((char)CurrentLevel, (char)CurrentAct);
			else
				return;
		}
	}

	return;
}


void GameOver_R() {

	isGameOver = true;
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
		{
			randomizedSets[i].character = getRandomCharacter();
			randomizedSets[i].sonic_transfo = GetRandomSonicTransfo(randomizedSets[i].character);
		}

		if (RNGStages)
			getRandomStage(&randomizedSets[i], randomizedSets[i].character);

			randomizedSets[i].SA2Mission = randomSA2Mission(randomizedSets[i].level);
		 
		if (RNGMusic)
			randomizedSets[i].music = getRandomMusic(randomizedSets[i]);

		if (isAIAllowed)
			randomizedSets[i].ai_mode = getRandomAI(randomizedSets[i].character, randomizedSets[i].level);

			randomizedSets[i].ai_race = getRandomRaceAI(randomizedSets[i]);

		if (RNGCutscene)
			getRandomCutscene(&randomizedSets[i]);
		
		TotalCount++;
	}
}


void Randomizer_GetNewRNG() {

	TotalCount = 0;
	levelCount = 0;
	split = 0;
	DuplicateStages.clear();

	if (!StorySplits) {
		split = 40;
		Create_NewRNG();
	}
	else {
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

	//Generate a list of random levels on boot, we are looking for 10 stages + bosses if Sonic Story and 37 if all stories.
	
	Create_NewRNG();

	if (!RNGStages && StorySplits != 0)
		return;

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
	if (RNGStages == true) {
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