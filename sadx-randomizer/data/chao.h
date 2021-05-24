#pragma once


enum ChaoActions {
	ChaoAction_Init,
	ChaoAction_LoadChao,
	ChaoAction_CheckHit,
	ChaoAction_Hit,
	ChaoAction_Free,
};

void ChaoObj_Delete(ObjectMaster* a1);
void __cdecl ChaoGameplayCheck();
bool DoesChaoNeedGravity(_int16 CurLevel);
void Chao_LoadFiles();

extern bool TPAmyVersion;

void Chao_LoadFiles();
