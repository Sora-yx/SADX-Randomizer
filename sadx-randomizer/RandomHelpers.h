#pragma once
#include "stdafx.h"

extern struct RandomizedEntry randomizedSets[40];

uint8_t getRandomCharacter(bool allow_duplicate = false);
short getRandomStage(uint8_t char_id, bool ban_regular = false);
bool isStageBanned(uint8_t char_id, short stage_id);
bool isBossStage(short stage_id);
void testRefactor(char stage, char act);
void GoToNextLevel_hook(char stage, char act);
short randomacts(RandomizedEntry entry);

//void AISwitch();

struct RandomizedEntry
{
	int8_t character;
	short level;
	short act;
	char sonic_mode;
};

void LoadCharacter_r();
void ChangeStartPosCharLoading();
void __cdecl CheckDeleteAnimThing(EntityData1* a1, CharObj2** a2, CharObj2* a3);

extern int level[21];
extern int AIArray[6];
extern char stage;
extern char act; 
extern int SonicRand; //Super Sonic or Metal Sonic RNG

extern int character[6];
extern int CharacterCopy;

extern int TransfoCount;  //Super Sonic Stuff
extern int RNGSong;
extern bool Vanilla;



void __cdecl Startup_Init(const char* path, const HelperFunctions& helperFunctions);

//all levels

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


void CreditsNewList();



//void randomstage(char stage, char act);
void DisableTimeStuff();
void RandomVoice();
void RandomMusic();

void AddCustomFlag();
void CustomFlagCheck();

void CancelResetPosition();

void SuperAuraStuff();
void SuperSonicStuff();
void LoadZero();

void credits();
void HotShelterSecretSwitch();
void HotShelterHandle();

void FixGammaBounce();
void FixGammaHitBounce();
void TwinkleCircuitResult();

void FixEggViperCutscene();
void EggViperVoice();

void LoadEggmanAI();
void FixRollerCoaster();

//void RandomizerMission();
void SHAct2Position();
void MissionObject(ObjectMaster *obj);
void MetalSonicRace_Init();
void LoadEggman_AI_R();

VoidFunc(PauseQuitDisplay, 0x415450);
VoidFunc(E101ShootThing, 0x567ac0);
VoidFunc(Tails_CheckRaceResult, 0x461560);
VoidFunc(EndLevelStuff, 0x4179bc);

ObjectFunc(Result_Score, 0x4141f0);

VoidFunc(ScreenTextureVer, 0x432ea0);

VoidFunc(SetupZero, 0x4b3eb0);
VoidFunc(CheckLoadZero, 0x486a40);

VoidFunc(EggViperCutscene, 0x431430);


DataPointer(char, BossHP, 0x3C58150);
DataPointer(char, Emblem, 0x974AE0);
DataPointer(unsigned char, LevelList, 0x3B2C5F8);
DataPointer(unsigned char, SelectedCharacter, 0x3B2A2FD);
DataPointer(char, RNGDoor, 0x3C7457C);
DataPointer(char, FirstHotShelterSwitch, 0x3c72a40);

DataPointer(char, SomethingAboutHotShelterSwitch, 0x3c72a4c);
DataPointer(char, SecretWaterSwitch, 0x3C5B37E);

DataPointer(char, TitleCardStuff, 0x3c53abc);
DataPointer(char, TitleCardStuff2, 0x3c53abd);
DataPointer(char, GetLevelType, 0x3c53abf);
DataPointer(char, dword_03b28114, 0x3b28114);
DataPointer(NJS_TEXLIST, CurrentCardTexture, 0x91C548);
DataPointer(NJS_TEXLIST*, CurrentCardTexturePtr, 0x3C53AC4);

DataPointer(char, DWORD_03c53ac4, 0x3c53ac4);


void LoadTails_AI_R();


int IsFastSonicAI_R(void);
int CheckTailsAI_R(void);
int DisplayTitleCard_R(void);

//int FunnyTest(void);

void FunnyTest();

DataPointer(int, dword_3B2A304, 0x3B2A304);

void CreditFlag();

void DisableTime_Zero();
void AISwitch();

void SetLevelAndAct_R(); //fix trial mod 
void GetStats(); //get stats for credits