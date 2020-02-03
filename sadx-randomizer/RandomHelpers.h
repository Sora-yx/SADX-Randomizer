#pragma once
#include "stdafx.h"

extern struct RandomizedEntry randomizedSets[40];

uint8_t getRandomCharacter(bool allow_duplicate = false);
short getRandomStage(uint8_t char_id, bool ban_regular = false);
short getRandomMusic(RandomizedEntry entry);
bool isStageBanned(uint8_t char_id, short stage_id);
bool isRegularStageBanned(uint8_t char_id, short stage_id);
bool isBossStage(short stage_id);
void testRefactor(char stage, char act);
void GoToNextLevel_hook(char stage, char act);
void Split_Init();
void AIAudioFixes();

void FixRMLava();

short randomacts(RandomizedEntry entry);
short randomLayout(RandomizedEntry entry);
short getRandomAI(RandomizedEntry entry);
short getRandomRaceAI(RandomizedEntry entry);
void GetNewLevel();
void SelectBarRace();
void TwinkleCircuitMusic();
void RandomizeStages_Hook();

extern bool RNGCharacters;
extern bool RNGStages;
extern bool Vanilla;
extern int ban;
extern bool ConsistentMusic;
extern bool Missions;
extern bool MetalSonic;
extern bool SuperSonic;
extern bool banCharacter[8];
extern unsigned int split;
extern unsigned int TotalCount;
extern char StorySplits;
extern unsigned char SwapDelay;

struct RandomizedEntry
{
	int8_t character;
	short level;
	short act;
	unsigned char LevelLayout;
	char sonic_mode; //Metal Sonic
	char ss_mode; //Super Sonic
	int ai_mode; //AI following you
	int ai_race; //Tails race AI
	short music;
	short voices;
};

//Mission Card Enum 0 = capsule, 1 = Lost Chao, 2 = Emeralds Knux, 3 = Beat Sonic, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails, 10 = Zero, 11+ Race
enum MissionCard {
	CapsuleCard, LostChaoCard, EmeraldKnuxCard, SonicRaceCard, FinalEggCard, FroggyCard,
	LostWorldCard, MissileRaceCard, RingsCard, RescueTailsCard, BallonCard, TailsRaceCard, KnuxRaceCard, AmyRaceCard,
	BigRaceCard, GammaRaceCard, EggmanRaceCard, TikalRaceCard
};




//SADX / SA2 missions. (M1 Variation is used when a character share the same level and act, but with a different level layout, ex: Amy Hot Shelter and Big Hot Shelter, same act, different version.)
enum CurMission {

	Mission1, Mission1_Variation, Mission2_100Rings, Mission3_LostChao
};

enum CurSplits {

	None, SonicStory, AllStories, AnyPourcent
};

extern unsigned char CurrentLevelLayout;
extern int CustomFlag;
extern bool Race;
extern char AIRace;
extern int levelCount;
extern bool TreasureHunting;

void Set_MusicVoices();
void TitleCard_Init();
void __cdecl CheckDeleteAnimThing(EntityData1* a1, CharObj2** a2, CharObj2* a3);

void BigLayoutHS();
void TargetableEntity(ObjectMaster* obj);
void EggHornet_LoadWithTarget();
void Chaos0_LoadWithTarget();
void Chaos2_LoadWithTarget();
void Chaos6_LoadWithTarget();

ObjectFunc(E101_Main, 0x567fd0);
VoidFunc(LoadE101, 0x568090);
ObjectFunc(InvisibleWallCasino, 0x5d03a0);
void FixInvisibleWall();

void E101Target();

extern int level[22];
extern int AIArray[4];
extern int AIRaceArray[6];
extern char stage;
extern char act;
extern char SonicRand; //Super Sonic or Metal Sonic RNG
extern bool RNGMusic;

extern int character[6];
extern int CharacterCopy;

extern int TransfoCount;  //Super Sonic Stuff
extern bool Vanilla;

extern int CurrentMission;
extern int CurrentAI;
extern bool isAIActive;
extern bool isAIAllowed;

void __cdecl StartupLevels_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl StartupAudio_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl StartupMiscellaneous_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl Randomizer_Config(const char* path, const HelperFunctions& helperFunctions);

void Chao_Init();
void Chao_OnFrame();

void PauseMenuFix();

//all levels

void __cdecl HedgehogHammer_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl EmeraldCoast_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl WindyValley_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl Casino_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl IceCap_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl TwinklePark_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl SpeedHighway_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl RedMountain_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl SkyDeck_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl LostWorld_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl FinalEgg_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl HotShelter_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl SandHill_Init(const char* path, const HelperFunctions& helperFunctions);

//Custom Object level

void __cdecl WVObjects_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl CasinoObjects_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl ICObjects_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl TPObjects_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl SHObjects_Init(const char* path, const HelperFunctions& helperFunctions);

void __cdecl RMObjects_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl SDObjects_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl LWObjects_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl HSObjects_Init(const char* path, const HelperFunctions& helperFunctions);

//Bosses
void __cdecl Chaos0_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl Chaos2_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl Chaos6_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl EggHornet_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl EggWalker_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl EggViper_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl Zero_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl E101_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl PerfectChaos_Init(const char* path, const HelperFunctions& helperFunctions);

void CreditsNewList();
void Credits_StatsDelayOnFrames();
void Race_Init();
void MissionResultCheck();
void DisplayRandoInformation();

//void randomstage(char stage, char act);
void DisableTimeStuff();
void RandomVoice();
void RandomMusic();
void Stages_Management();

void PlayMusic_R(MusicIDs song);
void PlayVoice_R(int a1);
void Chao_CrySound();

void AddCustomFlag();
void CustomFlagCheck(); //sa2 style

void CancelResetPosition();

void LoadZero();
void Set_Zero();
void AI_FixesOnFrames();


void HotShelterSecretSwitch();

void FixGammaBounce();
void FixGammaHitBounce();
void TwinkleCircuitResult();
void HedgehogHammerResult();

void FixEggViperCutscene();


void FixRollerCoaster();

//void RandomizerMission();
void SHAct2Position();

void ICAct3CutsceneSkip();
void Reset_OriginalMusic();

VoidFunc(PauseQuitDisplay, 0x415450);
VoidFunc(E101ShootThing, 0x567ac0);
VoidFunc(Tails_CheckRaceResult, 0x461560);
VoidFunc(EndLevelStuff, 0x4179bc);

ObjectFunc(Result_Score, 0x4141f0);

VoidFunc(ScreenTextureVer, 0x432ea0);
VoidFunc(SomethingAboutSave, 0x42d2f0);
VoidFunc(FUN_00412ad0, 0x412ad0);

VoidFunc(SetupZero, 0x4b3eb0);
VoidFunc(CheckLoadZero, 0x486a40);

VoidFunc(EggViperCutscene, 0x431430);
FunctionPointer(void, BossHP_Stuff, (int x, int y, int hp), 0x4b3cc0);

DataPointer(char, BossHP, 0x3c58148);
DataPointer(char, BossHP2, 0x3C58150);
DataPointer(float, BossHP3, 0x3c58158);
DataPointer(char, Emblem, 0x974AE0);
DataPointer(unsigned char, LevelList, 0x3B2C5F8);
DataPointer(unsigned char, SelectedCharacter, 0x3B2A2FD);
DataPointer(char, RNGDoor, 0x3C7457C);
DataPointer(char, FirstHotShelterSwitch, 0x3c72a40);
VoidFunc(Reset_HotShelterSwitch, 0x59a1b0);

DataPointer(char, SomethingAboutHotShelterSwitch, 0x3c72a4c);
DataPointer(char, SecretWaterSwitch, 0x3C5B37E);

DataPointer(char, TitleCardStuff, 0x3c53abc);
DataPointer(char, TitleCardStuff2, 0x3c53abd);
DataPointer(char, GetLevelType, 0x3c53abf);
DataPointer(char, dword_03b28114, 0x3b28114);
DataPointer(char, TitleCardCounter, 0x3C53ABD);
DataPointer(NJS_TEXLIST, CurrentCardTexture, 0x91C548);
DataPointer(NJS_TEXLIST*, CurrentCardTexturePtr, 0x3C53AC4);
DataPointer(NJS_TEXANIM, MissionSpriteAnim, 0x917784);

void AI_Init();
int CheckTailsAI_R(void);
int DisplayTitleCard_r();
void LoadStageMissionImage_r();
int LoadTitleCardTexture_r(int minDispTime);
void StageMissionImage_result();
int CheckMissionRequirements_r();


DataPointer(int, dword_3B2A304, 0x3B2A304);


void FinalStat();

void DisableTime_Zero();
void AISwitch();
void HookStats_Inits();
void SetLevelAndAct_R(); //fix trial mod


DataPointer(char, ChaosAdventureData, 0x3B1860A);

DataPointer(char, TailsAdventureData, 0x3B1860E);


DataPointer(char, KnuxCheck, 0x3c52c04);
DataPointer(char, KnuxEmerald2, 0x3C52B48);
DataPointer(char, KnuxCheck2, 0x3c52bd8);
void SetRNGKnuckles();
void RestoreRNGValueKnuckles();



DataPointer(char, TCQuit, 0x3c5d518);
DataPointer(char, EventTailsData, 0x3B18809);

DataPointer(char, AdventureDataChaos4, 0x3B183AA);
DataPointer(char, AdventureDataChaos4Post, 0x3B183AE);
FunctionPointer(void, StartCutsceneFlag, (int event), 0x630590);

FunctionPointer(void, StartCutscene, (int flag), 0x4136e0);
FunctionPointer(void, StartCutscene2, (int flag), 0x52e6c0);
VoidFunc(FUN_0042ce20, 0x42ce20); //Called with Delete Tails AI

VoidFunc(CheckTC, 0x79a8e0);

VoidFunc(CutsceneFlagData, 0x431430);
VoidFunc(SkyDeckResetValue, 0x5ec790);
VoidFunc(SomethingAboutMK2, 0x56b0c0);
VoidFunc(SomethingAboutZeroBoss, 0x5875d0);
VoidFunc(FUN_0040bda0, 0x40bda0);
VoidFunc(FUN_0040be30, 0x40be30);
VoidFunc(GetLevelCutscene, 0x413b20);

VoidFunc(Knuckles_SetRNG, 0x475840);
void ICAct3Position();

VoidFunc(PauseQuitThing2, 0x413f70);
VoidFunc(FUN_00424830, 0x424830);
void SoftReset_R();
void FixRestart_Cart();
void Delete_Cart();
void LoadCamFilePC_R();
void ResetValueWhileLevelResult();
void PlayRace_Music();
void SongRace_Init();
void AddRingSandHill();
void fixTCCart();
void preventCutscene();

extern int RageQuit;
extern int JumpCount;
extern int ringsPB;
extern int chaoPB;
extern int animalPB;
extern int killPB;
extern int hurtsPB;
extern int deathsPB;
extern int TotalDeathsPB;
extern int TotalHurtsPB;
extern int AISwapCount;
