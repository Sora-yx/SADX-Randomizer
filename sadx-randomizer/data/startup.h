#pragma once

void __cdecl StartupLevels_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl StartupMusic_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl StartupVoices_Init(const char* path, const HelperFunctions& helperFunctions);
void __cdecl StartupMiscellaneous_Init(const char* path, const HelperFunctions& helperFunctions);

//all levels

void __cdecl HedgehogHammer_Init(const HelperFunctions& helperFunctions);
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
void __cdecl Chaos0_Init(const HelperFunctions& helperFunctions);
void __cdecl Chaos2_Init(const HelperFunctions& helperFunctions);
void __cdecl Chaos4_Init(const HelperFunctions& helperFunctions);
void __cdecl Chaos6_Init(const HelperFunctions& helperFunctions);
void __cdecl EggHornet_Init(const HelperFunctions& helperFunctions);
void __cdecl EggWalker_Init(const HelperFunctions& helperFunctions);
void __cdecl EggViper_Init(const HelperFunctions& helperFunctions);
void __cdecl Zero_Init(const HelperFunctions& helperFunctions);
void __cdecl E101_Init(const HelperFunctions& helperFunctions);
void __cdecl PerfectChaos_Init();

void Chao_Init();

void CreditsNewList();
void Credits_StartupInit(const char* path, const HelperFunctions& helperFunctions);
void Race_Init();
void LevelFeaturesInit();

void Load_ObjectsCommon();
void Delete_ObjectsCommon();