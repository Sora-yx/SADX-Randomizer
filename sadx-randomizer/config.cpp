#include "stdafx.h"

int Seed = 0;
char StorySplits;
bool RNGCharacters = true;
bool RNGStages = true;
bool Upgrade = true;
bool Vanilla = false;
bool RNGVoices = true;
bool CustomVoices = true;
bool RNGMusic = true;
bool SA2M2 = true;
bool SA2M3 = false;
bool Viper = false;
bool isKHMod = false;
bool isChaoGameplayAllowed = false;
bool DupliCheck = true;
bool isChaoHintEnabled = true;
bool RNGCutscene = true;
bool RNGBosses = true;
bool RNGEnemies = false;
bool isTCBanned = false;

//Character settings
bool AmySpeed = true;
bool BigSpeed = true;

//banned character roster
bool MetalSonic = false;
bool SuperSonic = false;
int ban = 0;
bool banCharacter[8];
uint8_t MPPlayers = 1;

void ReadConfig(const char* path)
{
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	StorySplits = config->getInt("Randomizer", "StorySplits", 0); //speedrunners splits
	MPPlayers = config->getInt("Randomizer", "Multiplayer", 1);
	RNGCharacters = config->getBool("Randomizer", "RNGCharacters", true);
	RNGStages = config->getBool("Randomizer", "RNGStages", true);
	DupliCheck = config->getBool("Randomizer", "DupliCheck", true);
	RNGCutscene = config->getBool("Randomizer", "RNGCutscene", true);
	RNGBosses = config->getBool("Randomizer", "RNGBosses", true);
	isTCBanned = config->getBool("Randomizer", "isTCBanned", false);

	RNGEnemies = config->getBool("Randomizer", "RNGEnemies", false);
	Seed = config->getInt("Randomizer", "Seed", 0);
	Vanilla = config->getBool("Randomizer", "Vanilla", false);
	SA2M2 = config->getBool("Randomizer", "SA2M2", true);
	SA2M3 = config->getBool("Randomizer", "SA2M3", false);

	//Songs Settings
	RNGVoices = config->getBool("SongsStuff", "RNGVoices", true);
	RNGMusic = config->getBool("SongsStuff", "RNGMusic", true);

	//Disable Character settings
	banCharacter[0] = config->getBool("Roster", "Sonic", false);
	banCharacter[2] = config->getBool("Roster", "Tails", false);
	banCharacter[3] = config->getBool("Roster", "Knuckles", false);
	banCharacter[5] = config->getBool("Roster", "Amy", false);
	banCharacter[7] = config->getBool("Roster", "Big", false);
	banCharacter[6] = config->getBool("Roster", "Gamma", false);
	MetalSonic = config->getBool("Roster", "MetalSonic", false);
	SuperSonic = config->getBool("Roster", "SuperSonic", false);

	isAIAllowed = config->getBool("RosterAI", "isAIAllowed", true);
	isChaoGameplayAllowed = config->getBool("RosterAI", "isChaoGameplayAllowed", false);

	Viper = config->getBool("Difficulty", "Viper", true);
	AmySpeed = config->getBool("Difficulty", "AmySpeed", true);
	BigSpeed = config->getBool("Difficulty", "BigSpeed", true);
	Upgrade = config->getBool("Difficulty", "Upgrade", true);
	AI_Init(help, config);
	delete config;
}