#pragma once
#include "stdafx.h"
#include "SADXModLoader.h"

typedef struct {
	char SelectedChao;
	bool Carried;
	ObjectMaster* Handle;
	ObjectMaster* Chao;
} ChaoLeash;

typedef struct {
	ChaoLeash ChaoHandles[8];
	bool ChaoLoaded;
	bool JustOutOfGarden;
	bool AreChaoPVPLoaded;
} ChaoHandle;

enum ChaoActions {
	ChaoAction_Init,
	ChaoAction_LoadChao,
	ChaoAction_Free,
	ChaoAction_Flight,
	ChaoAction_Attack
};

FunctionPointer(int, Chao_Animation, (ObjectMaster* a1, int a2), 0x734F00);
FunctionPointer(bool, Chao_FinishedAnimation, (ObjectMaster* a1), 0x735040);
FunctionPointer(EntityData1*, SpawnAnimal, (int unknown, float x, float y, float z), 0x4BE610);
FunctionPointer(int, WhistleFunction, (EntityData1* a1, EntityData2* a2, CharObj2* a3, int flag), 0x442570);
FunctionPointer(int, BigWhistle, (int a3, int a4, int a5, int a6), 0x423BE0);

void ChaoObj_Init(ObjectMaster* a1);
void ChaoObj_Delete(ObjectMaster* a1);
void ChaoObj_Reset(ObjectMaster* a1);
bool DoesChaoNeedGravity(_int16 CurLevel);
void Chao_LoadFiles();
void ChaoFix();
extern bool TPAmyVersion;