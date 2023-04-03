#pragma once

enum CutsceneFlag {
	SonicIntro = 1,
	SonicOutro = 0x26,
	TailsIntro = 0x30,
	TailsOutro = 0x52,
	AmyIntro = 0x60,
	AmyOutro = 0x72,
	KnuxIntro = 0x80,
	KnuxOutro = 0x9F,
	GammaIntro = 0x0B0,
	BigIntro = 0x0D0,
	BigOutro = 0x0E2
};

struct AdventureData_
{
	char TimeOfDay;
	char emerald;
	__int16 seqno;
	__int16 seq;
	__int16 nextsec;
	unsigned __int16 stage;
	unsigned __int16 destination;
};

struct SceneSelectData_
{
	void* Code;
	char Level;
	char Act;
	__int16 Entrance;
	char Name[32];
};



struct CutsceneLevelData
{
	int cutscene_id;
	int level;
	int act;
	int character;
	char scene_select;
};


void Init_RandomCutscene();
extern uint8_t cutsceneAllowedCount;

DataPointer(DemoData, FirstDemo, 0x913AE0);
DataArray(LandTable*, LandTableArray, 0x97DBE8, 193);
DataPointer(AdventureData_*, CurrentAdventureData_, 0x3B0EF4C);
DataPointer(SceneSelectData_*, CurrentSceneSelectData, 0x03B18A08);
DataArray(AdventureData, Stories, 0x3B183A8, 8);
