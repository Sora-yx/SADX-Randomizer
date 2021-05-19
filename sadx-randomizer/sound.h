#pragma once

#define Status_KillSound 0x4000
extern HelperFunctions help;
void Sounds_OnFrame();

void PlayCustomSound(int ID);
void PlayDelayedCustomSound(int ID, int time, float volumeoverride);
void PlayCustomSound_Entity(int ID, ObjectMaster* obj, float dist, bool loop);
void PlayCustomSound_EntityAndPos(int ID, ObjectMaster* obj, NJS_VECTOR* pos, float dist, float volume, bool loop);
void PlayCustomSound_EntityAndVolume(int ID, ObjectMaster* obj, float dist, float volume, bool loop);
void PlayCustomSound_Pos(int ID, NJS_VECTOR* pos, float dist, float volume, bool loop);

enum CustomSounds {
	CommonSound_Rank = 999,
	CommonSound_SonicRankE,
	CommonSound_SonicRankD,
	CommonSound_SonicRankC,
	CommonSound_SonicRankB,
	CommonSound_SonicRankA,
	CommonSound_TailsRankE,
	CommonSound_TailsRankD,
	CommonSound_TailsRankC,
	CommonSound_TailsRankB,
	CommonSound_TailsRankA,
	CommonSound_KnuxRankE,
	CommonSound_KnuxRankD,
	CommonSound_KnuxRankC,
	CommonSound_KnuxRankB,
	CommonSound_KnuxRankA,
	CommonSound_AmyRankE,
	CommonSound_AmyRankD,
	CommonSound_AmyRankC,
	CommonSound_AmyRankB,
	CommonSound_AmyRankA,
	CommonSound_SonicSwap = 4000,
	CommonSound_TailsSwap,
	CommonSound_KnuxSwap,
	CommonSound_AmySwap,
	CommonSound_EggmanSwap = 4005,
	CommonSound_BackRing = 5000,
	CommonSound_RadarBlink = 6000,
	CommonSound_TikalHint,
	CommonSound_EmeraldGet,
	CommonSound_MysticMelody,
	CommonSound_MM_Platform,	
	CommonSound_MM_Warp,
};