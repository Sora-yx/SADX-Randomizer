#pragma once
#include "stdafx.h"

extern struct RandomizedEntry randomizedSets[40];

bool isBossStage(short stage_id);
bool isDuplicateMission(short curMission, short prevMission);
void SetRandomStageAct(char stage, char act);
void GoToNextLevel_hook(char stage, char act);
void Split_Init();
void AIAudioFixes();

void FixRMLava();
short randomSA2Mission(short stage_id);
short getRandomAI(uint8_t char_id, short stage_id);
short getRandomRaceAI(RandomizedEntry entry);
void Randomizer_GetNewRNG();
void SelectBarRace();
void TwinkleCircuitMusic();
void RandomizeStages_Hook();
void MovePlayerToStartPoint_R(EntityData1* data);

extern bool RNGCharacters;
extern bool RNGStages;
extern bool Vanilla;
extern bool DupliCheck;
extern int ban;
extern bool SA2M2;
extern bool SA2M3;
extern bool MetalSonic;
extern bool SuperSonic;
extern bool banCharacter[8];
extern uint32_t split;
extern uint32_t TotalCount;
extern char StorySplits;
extern bool isChaoGameplayAllowed;
extern uint8_t SwapDelay;
extern bool ChaoSpawn;
extern bool isTailsVersion;
extern bool isPlayerInWaterSlide;
HelperFunctions extern help;


struct RandomizedEntry
{
	int8_t character;
	short LevelAndActs;
	short level;
	short act;
	short SA2Mission;
	uint8_t Layout;
	char sonic_mode; //Metal Sonic
	char ss_mode; //Super Sonic
	int ai_mode; //AI following you
	int ai_race; //Tails race AI
	short music;
	short voices;
};

struct StageVersion {

	short level;
	short act;
	short version;
};

enum StageVariation {

	NormalVersion = -1,
	SonicVersion = 0,
	TailsVersion = 2,
	KnucklesVersion = 3,
	AmyVersion = 5,
	GammaVersion,
	BigVersion,
	
};

struct RandomizerGenerator {
	short levelAndActs;
	int8_t version;
	int8_t bannedChar;
};


struct SetLevelPosition
{
	int8_t version;
	int16_t LevelID;
	NJS_VECTOR Position;
	float YRot;
};


enum CharacterStageVersion {

	Normal = -1,
	BossVersion = 9
};

//Mission Card Enum 0 = capsule, 1 = Lost Chao, 2 = Emeralds Knux, 3 = Beat Sonic, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails, 10 = Zero, 11+ Race
enum MissionCard {
	CapsuleCard, LostChaoCard, EmeraldKnuxCard, SonicRaceCard, FinalEggCard, FroggyCard,
	LostWorldCard, MissileRaceCard, RingsCard, RescueTailsCard, BalloonCard, TailsRaceCard, KnuxRaceCard, AmyRaceCard,
	BigRaceCard, GammaRaceCard, EggmanRaceCard, TikalRaceCard, MSRaceCard, E103Card, E104Card, E105Card, EmeraldCasinoCard, EmeraldICCard, EmeraldWVCard, SonicDollCard
};

enum CurMission {

	SADX_Mission, Mission1_Variation, Mission2_100Rings, Mission3_LostChao
};

enum CurSplits {

	None, SonicStorySplit, AllStoriesSplit, AnyPourcent
};


uint8_t getRandomCharacter();
bool isStageBanned(RandomizerGenerator* generated, uint8_t char_id);
bool isDuplicateStage(RandomizerGenerator* generated);
void getRandomStage(short* cur_stagePtr, short* cur_actPtr, uint8_t cur_Char);
short getRandomMusic(RandomizedEntry entry);

void BackRingObj_Main(ObjectMaster* obj);

void LoadTriggerObject();
void __cdecl CheckLoadCapsule_r(ObjectMaster* a1);
void __cdecl CheckLoadCasinoEmerald_r(ObjectMaster* a1);
void __cdecl CheckLoadWVEmerald_r(ObjectMaster* a1);
void __cdecl CheckLoadICEmerald_r(ObjectMaster* a1);
void __cdecl CheckLoadTailsPlaneEC_r(ObjectMaster* a1);
void __cdecl CheckLWTrigger_r(ObjectMaster* a1);
void __cdecl CheckFETrigger_r(ObjectMaster* a1);



extern short CurrentMission;
extern int8_t CurrentStageVersion;
extern int CustomFlag;
extern bool Race;
extern char AIRace;
extern int levelCount;
extern bool isCriticalMode;

extern char GetCustomLayout;


void TitleCard_Init();
void __cdecl CheckDeleteAnimThing(EntityData1* a1, CharObj2** a2, CharObj2* a3);
int IsFastSonicAI_R();

void CheckAndSet_HotShelterFunctions();
void TargetableEntity(ObjectMaster* obj);
void EggHornet_LoadWithTarget();
void Chaos2_LoadWithTarget();
void Chaos6_LoadWithTarget();
void __cdecl ChaoGameplayCheck();
bool isSA2Mission();

int GetCharaProgression();
ObjectFunc(E101_Main, 0x567fd0);
VoidFunc(LoadE101, 0x568090);
ObjectFunc(InvisibleWallCasino, 0x5d03a0);
ObjectFunc(SDCannon, 0x5f84e0);
ObjectFunc(SDCannonS1, 0x5f9710);
ObjectFunc(SDCannonS2, 0x5f8e00);
void FixInvisibleWall();


extern int level[23];
extern int AIArray[4];
extern int AIRaceArray[6];
extern char stage;
extern char act;
extern char SonicRand; //Super Sonic or Metal Sonic RNG
extern bool RNGMusic;
extern bool RNGVoices;

extern int character[6];
extern int CharacterCopy;

extern int TransfoCount;  //Super Sonic Stuff
extern bool Vanilla;
//extern bool isCheckpointUsed;
extern int CurrentMissionCard;
extern int CurrentAI;
extern bool isAIActive;
extern bool isAIAllowed;
extern bool LimitCustomFlag;

extern bool isKnucklesVersion;
extern bool isZeroActive;

void __cdecl StartupLevels_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl StartupMusic_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl StartupVoices_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl StartupMiscellaneous_Init(const char* path, const HelperFunctions& helperFunctions);
__int16 CurCharacter();

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

void __cdecl ECObjects_Init(const char* path, const HelperFunctions& helperFunctions);
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
void __cdecl Chaos4_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl Chaos6_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl EggHornet_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl EggWalker_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl EggViper_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl Zero_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl E101_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl PerfectChaos_Init(const char* path, const HelperFunctions& helperFunctions);
void Load_ObjectsCommon();
void Delete_ObjectsCommon();

void CreditsNewList();
void Credits_StatsDelayOnFrames();
void Credits_StartupInit(const char* path, const HelperFunctions& helperFunctions);
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
void DeleteCustomFlag();

void CancelResetPosition();
void SA2VoicesCheck();

void LoadZero();
void Set_Zero();
void AI_FixesOnFrames();
void FixAISFXGamma();
void FixAISFXGamma2();
void FixAISFXGamma3();
void FixAISFXGamma4();

void FixGammaBounce();
void FixGammaHitBounce();
void TwinkleCircuitResult();
void HedgehogHammerResult();

void FixEggViperCutscene();


void FixRollerCoaster();

//void RandomizerMission();
void SHAct2Position();
void MysticMelody_Main(ObjectMaster* obj);
void PlatformMM_Main(ObjectMaster* obj);
extern bool MMPlatformEnabled;
extern NJS_TEXLIST SA2_OBJ_TEXLIST;
FunctionPointer(int, PerformWhistle, (EntityData1* a1, EntityData2* a2, CharObj2* a3, int flag), 0x442570);

void ForcePlayerToWhistle();

VoidFunc(PauseQuitDisplay, 0x415450);
VoidFunc(E101ShootThing, 0x567ac0);
VoidFunc(Tails_CheckRaceResult, 0x461560);
VoidFunc(EndLevelStuff, 0x4179bc);

VoidFunc(SomethingAboutFlag, 0x42f5d0);

ObjectFunc(Result_Score, 0x4141f0);

VoidFunc(ScreenTextureVer, 0x432ea0);
VoidFunc(SomethingAboutSave, 0x42d2f0);
VoidFunc(FUN_00412ad0, 0x412ad0);
VoidFunc(FUN_00425b00, 0x425b00);

VoidFunc(SetupZero, 0x4b3eb0);
VoidFunc(CheckLoadZero, 0x486a40);

VoidFunc(EggViperCutscene, 0x431430);
ObjectFunc(Load_Chaos4, 0x552bb0);
VoidFunc(DeleteBubbleChaos, 0x7ae5b0);
VoidFunc(ChaosUnderLightDelete, 0x7ad2f0);
VoidFunc(FUN_007a1580, 0x7a1580);

FunctionPointer(void, BossHP_Stuff, (int x, int y, int hp), 0x4b3cc0);

DataPointer(char, BossHP, 0x3c58148);
DataPointer(char, BossHP2, 0x3C58150);
DataPointer(float, Life_Max, 0x3c58158);
DataPointer(char, Emblem, 0x974AE0);
DataPointer(unsigned char, LevelList, 0x3B2C5F8);
DataPointer(unsigned char, SelectedCharacter, 0x3B2A2FD);
DataPointer(char, RNGDoor, 0x3C7457C);
FunctionPointer(void, SetRNGAmyDoor, (), 0x5b06f);
DataPointer(char, FirstHotShelterSwitch, 0x3c72a40);
VoidFunc(Reset_HotShelterSwitch, 0x59a1b0);
VoidFunc(LoadSplines, 0x49c1a0);

void RaceResultCheck(ObjectMaster* a1);
void SetAIRaceWin();
void FixRaceResult();
DataPointer(char, ChaoGardenSSWarpOpen, 0x3B188BF);
DataPointer(char, ChaoGardenECWarpOpen, 0x3B188C0);
DataPointer(char, ChaoGardenMRWarpOpen, 0x3B188C1);
FunctionPointer(void, DrawObject, (NJS_OBJECT*), 0x408530);
DataPointer(char, SomethingAboutHotShelterSwitch, 0x3c72a4c);
DataPointer(char, SecretWaterSwitch, 0x3C5B37E);

DataPointer(char, FlagAutoPilotCart, 0x3D08E00);

DataPointer(char, TornadoThing, 0x3c5d670);

DataPointer(char, TitleCardStuff, 0x3c53abc);
DataPointer(char, TitleCardStuff2, 0x3c53abd);
DataPointer(char, GetLevelType, 0x3c53abf);
DataPointer(char, dword_03b28114, 0x3b28114);
DataPointer(char, TitleCardCounter, 0x3C53ABD);
DataPointer(NJS_TEXLIST, CurrentCardTexture, 0x91C548);
DataPointer(NJS_TEXLIST*, CurrentCardTexturePtr, 0x3C53AC4);
DataPointer(NJS_TEXANIM, MissionSpriteAnim, 0x917784);


void __cdecl AI_Init(const HelperFunctions& helperFunctions, const IniFile* config);
void Hud_DisplayOnframe();
int CheckTailsAI_R(void);
int DisplayTitleCard_r();
void LoadStageMissionImage_r();
int LoadTitleCardTexture_r(int minDispTime);
void StageMissionImage_result();
int CheckMissionRequirements_r();
void __cdecl LoadLevelResults_r();

DataPointer(int, dword_3B2A304, 0x3B2A304);
void DeleteCreditStats();


void DisableTime_Zero();
void AISwitch();
void HookStats_Inits();
void SetLevelAndAct_R(); //fix trial mod
void GotoNextLevel_RngLess(char stage, char act);


DataPointer(char, ChaosAdventureData, 0x3B1860A);

DataPointer(char, TailsAdventureData, 0x3B1860E);
DataPointer(char, CasinoSwitch, 0x3c5b37c);


DataPointer(char, KnuxCheck, 0x3c52c04);
DataPointer(char, KnuxEmerald2, 0x3C52B48);
DataPointer(char, KnuxCheck2, 0x3c52bd8);
void SetRNGKnuckles();
void RestoreRNGValueKnuckles();

NJS_VECTOR SetPlayerAroundLostChaoPosition();
DataPointer(char, TCQuit, 0x3c5d518);
DataPointer(char, EventTailsData, 0x3B18809);
DataPointer(char, SonicChaos4Flag, 0x3B188B9);
DataPointer(char, AdventureDataChaos4, 0x3B183AA);
DataPointer(char, AdventureDataChaos4Post, 0x3B183AE);
FunctionPointer(void, StartCutsceneFlag, (int event), 0x630590);
FunctionPointer(void, CameraSetEventCamera, (short a1, unsigned char a2), 0x437bf0);

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
FunctionPointer(int, CapsuleCheck, (), 0x46a820);

VoidFunc(Knuckles_SetRNG, 0x475840);
void ICAct3Position();
void LoadChaoTPTrigger();
void ChaoTPTrigger(ObjectMaster* a1);
void TriggerCasinoChao_Main(ObjectMaster* obj);
void TriggerOBJHS_Delete();
void LoadRemoveCart();
VoidFunc(PauseQuitThing2, 0x413f70);
VoidFunc(FUN_00424830, 0x424830);
void SoftReset_R();
void TrialModeQuit_R();
void FixRestart_Stuff();
void Delete_Cart();
void LoadCamFilePC_R();
void ResetValueWhileLevelResult();

void AddRingSandHill();
void fixTCCart();
void preventCutscene();
void FlashScreen(ObjectMaster* obj);
void Chao_DeleteFiles();


float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);
FunctionPointer(void, SetPlayerNumberForGame, (unsigned short player), 0x414470);

extern int RageQuit;
extern int JumpPB;
extern int ringsPB;
extern int chaoPB;
extern int animalPB;
extern int killPB;
extern int hurtsPB;
extern int deathsPB;
extern int TotalDeathsPB;
extern int TotalHurtsPB;
extern int AISwapCount;
extern bool isGameOver;
extern int SeedCopy;