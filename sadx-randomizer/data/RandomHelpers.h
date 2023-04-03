#pragma once

#define TaskHook FunctionHook<void, task*>
extern struct RandomizedEntry randomizedSets[];
extern std::string modpath;

struct RandomizedEntry
{
	int8_t character;
	short LevelAndActs;
	short level;
	short act;
	short SA2Mission;
	uint8_t Layout;
	uint8_t sonic_transfo; //Metal Sonic
	int ai_mode; //AI following you
	int ai_race; //Tails race AI
	short music;
	int cutsceneID;
	int8_t cutsceneChara;
	int cutsceneLevel;
	int cutsceneAct;
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

struct StringLevelLayout
{
	int16_t LevelID;
	int8_t version;
	int8_t act;
	const char* SetFileName;
	const char* CamFileName;
};


enum CharacterStageVersion {

	Normal = -1,
	BossVersion = 9
};

enum LevelAndActIDs_
{
	LevelAndActIDs_Chaos6_ = LevelIDs_Chaos6 << 8,
	LevelAndActIDs_Chaos6Two,
};

extern RandomizerGenerator RandoStageArray[52];



enum CurSplits {

	None, SonicStorySplit, AllStoriesSplit, AnyPourcent
};



bool isBossStage(short stage_id);
bool isDuplicateMission(short curMission, short prevMission);
uint8_t GetRandomSonicTransfo(uint8_t char_id);
void SetRandomStageAct(char stage, char act);
void GoToNextLevel_hook(char stage, char act);
void Split_Init();
void AIAudioFixes();
void PlayRandomCutscene(long flag);
void FixRMLava();
short randomSA2Mission(short stage_id);
short getRandomAI(uint8_t char_id, short stage_id);
short getRandomRaceAI();
void Randomizer_GetNewRNG();
void TwinkleCircuitMusic();
void RandomizeStages_Init();
void AddCustomFlag();
void AddLevelLayout(std::string FolderName, std::string LevelName, const HelperFunctions& helperFunctions);
void Rando_SaveProgression();
void Rando_LoadProgression();

void init_FlagsProgression();

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
extern bool RNGCutscene;
extern uint32_t segmentCount;
extern uint32_t TotalCount;
extern char StorySplits;
extern bool isChaoGameplayAllowed;
extern uint8_t SwapDelay;
extern bool ChaoSpawn;
extern bool isPlayerInWaterSlide;
extern bool isChaoHintEnabled;
extern bool AmySpeed;
extern bool BigSpeed;
extern bool isKHMod;
extern bool isTCBanned;


uint8_t getRandomCharacter();
bool isVanillaStage(RandomizerGenerator* generated, uint8_t char_id);
bool isStageBanned(RandomizerGenerator* generated, uint8_t char_id);
bool isDuplicateStage(RandomizerGenerator* generated);
short getRandomMusic();
void BackRingObj_Main(ObjectMaster* obj);

void CheckAndLoadTriggerObject();
void __cdecl CheckLoadCapsule_r(ObjectMaster* a1);
void __cdecl CheckLoadCasinoEmerald_r(ObjectMaster* a1);
void __cdecl CheckLoadWVEmerald_r(ObjectMaster* a1);
void __cdecl CheckLoadICEmerald_r(ObjectMaster* a1);
void __cdecl CheckLoadTailsPlaneEC_r(ObjectMaster* a1);
void __cdecl CheckLWTrigger_r(ObjectMaster* a1);
void __cdecl CheckFETrigger_r(ObjectMaster* a1);
void PlayRandomCutscene_OnFrames();
void getRandomCutscene(RandomizedEntry* entry);
bool CheckAndPlayRandomCutscene();
void set_event_flags(long cutsceneID);

void CheckAndDrawSubTtiles();

extern short CurrentMission;
extern int8_t CurrentStageVersion;
extern int CustomFlag;
extern bool Race;
extern char AIRace;
extern int levelCount;

extern ObjectFuncPtr charfuncs[];

void TitleCard_Init();
void __cdecl CheckDeleteAnimThing(EntityData1* a1, CharObj2** a2, CharObj2* a3);
int IsFastSonicAI_R();
void CheckAndSet_HotShelterLayoutFeatures();
void TargetableEntity(ObjectMaster* obj);

bool isSA2Mission();

int GetCharaProgression();

void KnucklesHintMain_r(ObjectMaster* obj);
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

extern bool Vanilla;
//extern bool isCheckpointUsed;
extern int CurrentMissionCard;
extern int CurrentAI;
extern bool isAIActive;
extern bool isAIAllowed;
extern bool LimitCustomFlag;

extern bool isZeroActive;

__int16 CurCharacter();
void Chao_OnFrame();
void PauseMenuFix();
void DisplayRandoInformation();

//void randomstage(char stage, char act);
void DisableTimeStuff();
void PlayRandomVoice(int a1);
void RandomMusic();

void PlayMusic_Original(MusicIDs song);
void PlayVoice_Original(int a1);
void Chao_CrySound();

void CustomFlagCheck(); //sa2 style
void DeleteCustomFlag();

void CancelResetPosition();
void SA2VoicesCheck();

void LoadZero();
void Set_ZeroChase();
void FixAISFXGamma();
void FixAISFXGamma2();
void FixAISFXGamma3();
void FixAISFXGamma4();

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

bool isHeroesMod();
bool isSA2Mod();

void ForcePlayerToWhistle();
void Hud_ShowSwapButton();
void Hud_ShowActionButton();

void RaceResultCheck(ObjectMaster* a1);
void SetAIRaceWin();
void FixRaceResult();

void __cdecl AI_Init(const HelperFunctions& helperFunctions, const IniFile* config);
void Hud_DisplayOnframe();
int CheckTailsAI_R(void);
void LoadStageMissionImage_r();
int LoadTitleCardTexture_r(int minDispTime);
void StageMissionImage_result();
int CheckMissionRequirements_r();
void __cdecl LoadLevelResults_r();

void DeleteCreditStats();

void DisableTime_Zero();
void SetLevelAndAct_R(); //fix trial mod


NJS_VECTOR SetPlayerAroundLostChaoPosition();

void ICAct3Position();
void HotShelterSecretSwitch();
void ChaoTPTrigger(ObjectMaster* a1);

void LoadRemoveCart(ObjectMaster* obj);

void SoftReset_R();
void TrialModeQuit_R();
void ResetValueAndObjects();
void Init_TreasureHunting();

void AddRingSandHill();
void fixTCCart();
void FlashScreen(ObjectMaster* obj);
void Chao_DeleteFiles();
void AISwapOnFrames();
void AI_Manager(ObjectMaster* obj);
void LevelOnFrames();


float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);

extern bool warped;

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

bool isRandoLevel();
void LayoutFunctionInit();
void CheckAndDisplayWarningLayoutError();
void IncreaseSpeedCharactersPerfectChaos();
void MissionResultCheck(ObjectMaster* obj);
void Result_Init();
void Objects_Common_Init();
void Missions_Init();

void warpedOnFrames();