#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector> 
#include "Cutscene.h"
#include "multiapi.h"

using std::string;
using std::vector;

//Contain randomly generated sets of character/level/act to work with (Main Part of the mod)
RandomizedEntry randomizedSets[40];
short prev_stage = -1;
bool isGameOver = false;
int8_t CurrentStageVersion = 0;

int character[6] = { Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Gamma, Characters_Big };

//Banned level list, there is few stage impossible to beat, depending on the character.
int bannedLevelsGamma[] = { LevelIDs_HedgehogHammer, LevelIDs_Chaos2, LevelIDs_Chaos4, LevelIDs_Chaos6, LevelIDs_EggWalker, LevelIDs_PerfectChaos, LevelIDs_Zero };
int bannedLevelsBig[] = { LevelIDs_EggViper, LevelIDs_E101R };

//Initiliaze banned Vanilla stage (if option is enabled)
int bannedRegularSonicAndTails[] = { LevelIDs_Chaos4, LevelIDs_EggHornet, LevelIDs_SandHill };
int bannedRegularGamma[] = { LevelIDs_E101, LevelIDs_E101R };

int previousLevel = -1;
uint8_t TCCount = 0;

RandomizerGenerator RandoStageArray[]
{
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
	{LevelAndActIDs_Chaos6Sonic, BossVersion, Characters_Sonic },
	{LevelAndActIDs_Chaos6Knuckles, BossVersion, Characters_Knuckles },
	{LevelAndActIDs_PerfectChaos, BossVersion, Characters_Sonic },
	{LevelAndActIDs_EggHornet, BossVersion, Characters_Tails },
	{LevelAndActIDs_EggWalker, BossVersion, Characters_Tails},
	{LevelAndActIDs_EggViper, BossVersion, Characters_Sonic },
	{LevelAndActIDs_Zero, BossVersion, Characters_Amy},
	{LevelAndActIDs_E101, BossVersion, Characters_Gamma},
	{LevelAndActIDs_E101R, BossVersion, Characters_Gamma},
	{LevelAndActIDs_TwinkleCircuit1, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit2, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit3, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit4, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit5, NormalVersion},
	{LevelAndActIDs_TwinkleCircuit6, NormalVersion},
	{LevelAndActIDs_SandHill, TailsVersion, Characters_Tails},
};

uint16_t failSafeLvlCount = 0;
void getRandomStage(RandomizedEntry* entry, uint8_t Char_id) 
{
	RandomizerGenerator* generated = nullptr;

	do {

		generated = &RandoStageArray[rand() % LengthOfArray(RandoStageArray)];
		failSafeLvlCount++;

		if (failSafeLvlCount >= 300)
		{
			if (isStageBanned(generated, Char_id) || !Vanilla && isVanillaStage(generated, Char_id))
			{
				generated = &RandoStageArray[rand() % LengthOfArray(RandoStageArray)];
			}

			break;
		}

	} while (previousLevel == generated->levelAndActs >> 8 || isStageBanned(generated, Char_id)
		|| !Vanilla && isVanillaStage(generated, Char_id) || DupliCheck && isDuplicateStage(generated)); //Order check here is really important, dupli check MUST be the last thing checked.

	entry->level = generated->levelAndActs >> 8;
	entry->act = generated->levelAndActs & 0xf;
	entry->Layout = generated->version;
	previousLevel = entry->level;
	failSafeLvlCount = 0;
}


bool isStageBanned(RandomizerGenerator* generated, uint8_t char_id)
{
	const short curSingleLevel = generated->levelAndActs >> 8;

	if (curSingleLevel == LevelIDs_TwinkleCircuit)
	{
		if (TCCount >= 2 || isTCBanned == true)
			return true;
		else
			TCCount++;
	}
	else if (isBossStage(curSingleLevel) && !RNGBosses)
	{
		return true;
	}

	for (uint8_t i = 0; i < LengthOfArray(bannedLevelsGamma); i++)
	{
		if (curSingleLevel == bannedLevelsGamma[i] && char_id == Characters_Gamma)
			return true;
	}

	for (uint8_t i = 0; i < LengthOfArray(bannedLevelsBig); i++)
	{
		if (curSingleLevel == bannedLevelsBig[i] && char_id == Characters_Big)
			return true;
	}

	return false;
}


bool isVanillaStage(RandomizerGenerator* generated, uint8_t char_id)
{
	const short curSingleLevel = generated->levelAndActs >> 8;
	const uint8_t curBannedChar = generated->bannedChar;

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


int oldStageVersion = -1;
bool isDuplicateStage(RandomizerGenerator* generated) {

	const short curLevelAndActID = generated->levelAndActs;
	const int8_t curVersion = generated->version;
	short curLevel = ConvertLevelActsIDtoLevel(curLevelAndActID);

	if (ban >= 5)
		return false;


	for (RandomizerGenerator stage : DuplicateStages) {

		if (DuplicateStages.size() != 0 && curVersion == BossVersion && DuplicateStages.back().version == BossVersion)
		{
			return true;
		}

		if (DuplicateStages.size() >= 42) //Prevent infinite loop.
		{
			return false;
		}

		if (DuplicateStages.size() != 0 && (curLevelAndActID == stage.levelAndActs && curVersion == stage.version) || DuplicateStages.back().levelAndActs >> 8 == curLevel)
		{
			return true;
		}
	}

	if (oldStageVersion == curVersion && (oldStageVersion == TailsVersion || oldStageVersion == KnucklesVersion) && DuplicateStages.size() < 40) {
		return true;
	}

	StructDupli.levelAndActs = curLevelAndActID;
	StructDupli.version = curVersion;
	DuplicateStages.push_back(StructDupli);
	oldStageVersion = curVersion;
	return false;
}


int levelCount = 0;

void SetInfoNextRandomStage(char Stage, char Act) 
{

	if (RNGCharacters)
	{
		CurrentCharacter = randomizedSets[levelCount].character;
		SonicRand = randomizedSets[levelCount].sonic_transfo;
		MetalSonicFlag = (SonicRand == 1 && CurrentLevel != LevelIDs_PerfectChaos) ? TRUE : FALSE;

		if (isMPMod())
		{
			for (uint8_t i = 0; i < multi_get_player_count(); i++)
			{
				multi_set_charid(i + 1, (Characters)randomizedSets[levelCount].characterMulti[i]);
			}
		}

	}

	if (isAIAllowed && !isMPMod())
		CurrentAI = randomizedSets[levelCount].ai_mode;

	LastLevel = CurrentLevel;
	CurrentLevel = RNGStages ? randomizedSets[levelCount].level : Stage;
	CurrentAct = RNGStages ? randomizedSets[levelCount].act : Act;
	CurrentMission = randomizedSets[levelCount].SA2Mission;
	CurrentStageVersion = randomizedSets[levelCount].Layout;
	levelCount++;
}

void SetRandomStageAct(char stage, char act) {

	if (isGameOver)
	{
		SetLevelAndAct(Uint8(stage), (Uint8)(act));
		return;
	}

	if (CreditCheck)
	{
		SetLevelAndAct(Uint8(LevelIDs_MysticRuins), (Uint8)0);
		return;
	}

	if (!GetCharaProgression())
	{
		CustomFlag = 0;
		if (isChaoGameplayAllowed && CurrentLevel == 0 && CurrentCharacter == Characters_Gamma) { //we don't want the game to play gamma cutscene
			SetLevelAndAct(LevelIDs_SSGarden, 0);
			return;
		}

		cutsceneAllowedCount = 2;
	}

	if (GameMode != 8 && GameMode != 10 && GameMode != 11 && GameMode < 21)
	{
		if (chaoWarpAllowedCount >= 2 && isChaoGameplayAllowed) {
			SetLevelAndAct(LevelIDs_SSGarden, 0);
			chaoWarpAllowedCount = 0;
			return;
		}
		
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

	if (CreditCheck)
	{
		SetLevelAndAct(Uint8(LevelIDs_MysticRuins), (Uint8)0);
		return;
	}

	if (GameMode != 8 && GameMode != 10 && GameMode != 11 && GameMode < 21)
	{

		if (isChaoGameplayAllowed && CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past && CustomFlag == 0) {
			SetLevelAndAct(LevelIDs_SSGarden, 0);
			return;
		}

		const bool isCutscene = CheckAndPlayRandomCutscene();

		if (!isCutscene)
			SetInfoNextRandomStage(stage, act);

		if (levelCount == TotalCount)
			Randomizer_GetNewRNG(); //reroll once the 40 stages have been beated.

		return;
	}

	return GoToNextLevel();
}

//Fix Trial Mode
void SetLevelAndAct_R() 
{
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


void GameOver_R() 
{

	isGameOver = true;
	InitializeSoundManager();
	return;
}

void DisplayRandoInformation() {

	if (GameMode != GameModes_Menu || !CharObj2Ptrs[0])
		return;

	SetDebugFontSize(13.0f * (unsigned short)VerticalResolution / 480.0f);
	SetDebugFontColor(0x8e8e8e);
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


void Create_NewRNG() 
{

	for (uint32_t i = 0; i < segmentCount; i++) { //generate 40 levels without any speedrunners splits.

		if (RNGCharacters)
		{
			randomizedSets[i].character = getRandomCharacter();
			randomizedSets[i].sonic_transfo = GetRandomSonicTransfo(randomizedSets[i].character);

			for (uint8_t j = 0; j < LengthOfArray(randomizedSets->characterMulti); j++)
			{
				randomizedSets[i].characterMulti[j] = getRandomCharacterMulti(i);
			}
			
		}

		if (RNGStages)
			getRandomStage(&randomizedSets[i], randomizedSets[i].character);

		randomizedSets[i].SA2Mission = randomSA2Mission(randomizedSets[i].level);

		if (RNGMusic)
			randomizedSets[i].music = getRandomMusic();

		if (isAIAllowed)
			randomizedSets[i].ai_mode = getRandomAI(randomizedSets[i].character, randomizedSets[i].level);

		randomizedSets[i].ai_race = getRandomRaceAI();

		if (RNGCutscene)
			getRandomCutscene(&randomizedSets[i]);

		TotalCount++;
	}
}



void Split_Init() { //speedrunner split init. Used when you start the game.


	if (!RNGStages)
		return;

	std::ofstream myfile("SADX_Rando_Splits.lss");
	//Header
	myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	myfile << "<Run version=\"1.7.0\">\n";
	myfile << "<GameIcon />\n<GameName>Sonic Adventure DX: Randomizer</GameName>\n<CategoryName> ";
	if (StorySplits == SonicStorySplit)
	{
		segmentCount = 10;
		myfile << "Sonic's Story" << "</CategoryName>\n<Metadata>\n";
	}
	if (StorySplits == AllStoriesSplit)
	{
		segmentCount = 37;
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


void Randomizer_GetNewRNG() 
{
	TotalCount = 0;
	levelCount = 0;
	segmentCount = 0;
	DuplicateStages.clear();

	if (!StorySplits) 
	{
		segmentCount = 40;
		Create_NewRNG();
	}
	else {
		Split_Init();
	}
}


void RandomizeStages_Init() 
{

	if (!RNGStages)
		return;


	//Hack many functions which teleport the player to the next stage to make them random.
	WriteCall((void*)0x41709d, GoToNextLevel_hook);
	WriteCall((void*)0x417b47, GoToNextLevel_hook);

	WriteCall((void*)0x41348f, SetRandomStageAct); //hook SetLevelAndAct when loading adventure data (used when savefile is complete.)
	WriteCall((void*)0x41342a, SetRandomStageAct); //hook SetLevelAndAct when loading adventure data
	WriteCall((void*)0x4134a2, SetRandomStageAct); //hook SetLevelAndAct when loading adventure data*/

	//miscellaneous fixes because of the hack above.
	WriteData<5>((void*)0x4134f3, 0x90); //Remove SetLevelAndAct when loading adventure data (fixes wrong warp)
	WriteData<1>((void*)0x413502, 0x08);
	WriteData<6>((void*)0x506512, 0x90); //remove Last Story Flag, as it creates many issues with SET layout, we will manually set it.
	WriteCall((void*)0x50659a, SetLevelAndAct_R);

	//WriteCall((void*)0x416be2, CancelResetPosition); //hook "SetStartPos_ReturnToField" used to cancel the reset character position to 0 after quitting a stage.
	WriteCall((void*)0x417bed, GameOver_R);
	WriteCall((void*)0x41717d, GameOver_R);

}