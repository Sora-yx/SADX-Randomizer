#pragma once

#define Status_KillSound 0x4000
HelperFunctions extern help;
void Sounds_OnFrame();

void PlayCustomSound(int ID);
void PlayDelayedCustomSound(int ID, int time, float volumeoverride);
void PlayCustomSound_Entity(int ID, ObjectMaster* obj, float dist, bool loop);
void PlayCustomSound_EntityAndPos(int ID, ObjectMaster* obj, NJS_VECTOR* pos, float dist, float volume, bool loop);
void PlayCustomSound_EntityAndVolume(int ID, ObjectMaster* obj, float dist, float volume, bool loop);
void PlayCustomSound_Pos(int ID, NJS_VECTOR* pos, float dist, float volume, bool loop);

enum CustomSounds {
	CommonSound_RadarBlink = 6000,
	CommonSound_TikalHint,
	CommonSound_EmeraldGet,
	CommonSound_SonicSwap = 4000,
	CommonSound_TailsSwap,
	CommonSound_KnuxSwap,
	CommonSound_AmySwap,
	CommonSound_EggmanSwap = 4005
};