#pragma once
#include "stdafx.h"
#include "SADXModLoader.h"
#include "RandomHelpers.h"





enum ChaoActions {
	ChaoAction_Init,
	ChaoAction_LoadChao,
	ChaoAction_Hit,
	ChaoAction_Free,
};

struct LostChaoPosition
{
	short version;
	int16_t LevelID;
	NJS_VECTOR Position;
	float YRot;
};



FunctionPointer(int, Chao_Animation, (ObjectMaster* a1, int a2), 0x734F00);
FunctionPointer(bool, Chao_FinishedAnimation, (ObjectMaster* a1), 0x735040);
FunctionPointer(EntityData1*, SpawnAnimal, (int unknown, float x, float y, float z), 0x4BE610);
FunctionPointer(int, WhistleFunction, (EntityData1* a1, EntityData2* a2, CharObj2* a3, int flag), 0x442570);
FunctionPointer(int, BigWhistle, (int a3, int a4, int a5, int a6), 0x423BE0);


void ChaoObj_Delete(ObjectMaster* a1);

bool DoesChaoNeedGravity(_int16 CurLevel);
void Chao_LoadFiles();

extern bool TPAmyVersion;

FunctionPointer(long, Chao_Cry, (ObjectMaster* Chao), 0x75b6c0);
FunctionPointer(long, Chao_Pleasure, (ObjectMaster* Chao), 0x75db80);
FunctionPointer(void, Chao_SetBehavior, (ObjectMaster* Chao, long* a2), 0x71EF10);


void Chao_LoadFiles();
