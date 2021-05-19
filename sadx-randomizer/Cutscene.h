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
	BigOutri = 0x0E2

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


struct DemoData
{
	__int16 level;
	__int16 act;
	__int16 character;
	__int16 cutscene;
};

struct CutsceneLevelData
{
	int cutscene_id;
	int level;
	int act;
	int character;
	char scene_select;
};


FunctionPointer(void, EV_Wait, (int time), 0x4314d0);
FunctionPointer(void, StopMusicAndLoadNextMenu, (int a1), 0x505B40);
FunctionPointer(void, SeqRun, (), 0x412AC0);
FunctionPointer(void, SeqSetPlayer, (__int16 character), 0x413380);
FunctionPointer(void, SeqSetSection, (__int16 sequence), 0x4133E0);
FunctionPointer(void, RunSceneSelect, (), 0x413870);
DataPointer(ObjectMaster*, CurrentMenuObjectMaster_Maybe, 0x3C5E8D0);
DataPointer(DemoData, FirstDemo, 0x913AE0);
DataArray(DemoData, DemosArray, 0x913AE0, 6);
DataArray(LandTable*, LandTableArray, 0x97DBE8, 193);
DataPointer(AdventureData_*, CurrentAdventureData_, 0x3B0EF4C);
DataPointer(SceneSelectData_*, CurrentSceneSelectData, 0x03B18A08);
DataArray(AdventureData, Stories, 0x3B183A8, 8);

DataPointer(float, flt_3B18244, 0x3B18244);
DataPointer(int, dword_3B28114, 0x3B28114);
ObjectFunc(SeqTaskFadeIn, 0x412fe0);
FunctionPointer(void, EventCutscene_Load2, (long flag), 0x42fa30);
FunctionPointer(void, EV_InitPlayer, (int player), 0x431780);
VoidFunc(EventCutscene_Exec2, 0x431430);
void Init_RandomCutscene();
extern bool isCutsceneAllowed;