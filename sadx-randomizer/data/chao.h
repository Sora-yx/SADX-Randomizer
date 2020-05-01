#pragma once
#include "stdafx.h"
#include "SADXModLoader.h"
#include "RandomHelpers.h"

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


LostChaoPosition ChaoLevelPosition[22] {

	{ Normal, LevelAndActIDs_EmeraldCoast2, 3857.76, 597.395, -2896.18, 0x8000 },
	{ Normal, LevelAndActIDs_EmeraldCoast3, 6388, 0.8, 1116, 0x8000 },
	{ Normal, LevelAndActIDs_WindyValley1, 4162.019, -4484, -1800, 0x8000 },
	{ Normal, LevelAndActIDs_Casinopolis1, 361, 380, -40, 0x8000 },
	{ Normal,LevelAndActIDs_Casinopolis2, -1565.96, -2205, 2654.24, 0x8000 },
	{ Normal, LevelAndActIDs_IceCap1, 1480.62, 573.3, -256.67, 0x8000 },
	{ Normal, LevelAndActIDs_IceCap4, 1790.85, 371.968811, 11.265, 0x8000 },
	{ Normal, LevelAndActIDs_TwinklePark2, 520, 1330, 1630, 0x8000 }, //Sonic Version
	{ BigTP, LevelAndActIDs_TwinklePark2, 604, 338, 237, 0x8000 }, //Big Version
	{ AmyTP, LevelAndActIDs_TwinklePark3, -41.43054199, 50, 290.7596436, 0x0 }, //Amy Version
	{ Normal,LevelAndActIDs_SpeedHighway1, 4455, -385.135, 2930.18, 0x8000 },
	{ Normal, LevelAndActIDs_RedMountain1, -3861.85, 883.96, -2974.81, 0x8000 },
	{ Normal, LevelAndActIDs_SkyDeck2, -316.7368469, 38.99000168, -687.1625977, 0x8000 },
	{ Normal, LevelAndActIDs_LostWorld2, 7410, -1965, 1316, 0x8000 },
	{ Normal, LevelAndActIDs_FinalEgg1, 2945.652344, 5589.605469, -2211.165039, 0x8000 },
	{ GammaFE, LevelAndActIDs_FinalEgg3, 1939, -3174.049561, -128, 0x8000 }, //Gamma Version
	{ SonicFE, LevelAndActIDs_FinalEgg3, 1480.62, 573.3, -256.67, 0x8000 }, //Sonic Version
	{ BigHS, LevelAndActIDs_HotShelter1, -278.8718262, 80, -499.0888367, 0x8000 }, //Big Version 
	{ AmyHS, LevelAndActIDs_HotShelter2, 716.4085693, 677.8605957, -2952.347412, -1.681558157E-44 + 0x4000 }, //Amy version SADX VANILLA
	{ Normal, LevelAndActIDs_HotShelter3, 2.01, 3222, -3136, 0x8000 },
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