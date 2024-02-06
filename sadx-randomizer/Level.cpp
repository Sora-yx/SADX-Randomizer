#include "stdafx.h"
#include "multiapi.h"

static FunctionHook<void, taskwk*> MovePlayerToStartPoint_t((intptr_t)MovePlayerToStartPoint);
static Trampoline* RunLevelDestructor_t = nullptr;
static Trampoline* LoadLevelObject_t = nullptr;

SetLevelPosition PlayerStartPosition[52] { //Casino pos are hardcoded

	{ AmyVersion, LevelAndActIDs_HedgehogHammer, { -55, 0, -31 }, 0 },
	{ SonicVersion, LevelAndActIDs_EmeraldCoast1, { -9, 16, 4 }, 0x6000},
	{ SonicVersion, LevelAndActIDs_EmeraldCoast2, { -986.5f, 1145, -2856 }, 0x4000 },
	{ BigVersion, LevelAndActIDs_EmeraldCoast3, { 6090, 30, 1000 }, 0 },
	{ GammaVersion, LevelAndActIDs_WindyValley1, { -10, -102, -10 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley1, { 1230, -333, -140 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley2, { 49.0571, 288.873, -26.8347 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley3, { 1096, 205, -1251 }, 0x4000 },
	{ TailsVersion, LevelAndActIDs_WindyValley3, { 1093, -158, -1254 }, 0 },
	{ SonicVersion, LevelAndActIDs_TwinklePark1, { -2000, 1770, -985 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, { 520, 975, 1620 }, 0xC000 },
	{ AmyVersion, LevelAndActIDs_TwinklePark2, { 723, 70, -358 }, 0xC000 },
	{ BigVersion, LevelAndActIDs_TwinklePark2, { 230, 80, -538 }, 0xC000 },
	{ AmyVersion, LevelAndActIDs_TwinklePark3, { 75, 0, -390 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway1, { -673, -10, 5 }, 0 },
	{ TailsVersion, LevelAndActIDs_SpeedHighway1, { -673, -10, 5 }, 0 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway2, { -50, 42, 0 }, 0 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway3, { 72, 26, 192 }, 0xC000 },
	{ KnucklesVersion, LevelAndActIDs_SpeedHighway3, { -230, 150, -1740 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_RedMountain1, { 18, 36, 636 }, 0 },
	{ SonicVersion, LevelAndActIDs_RedMountain2, { -78, 831, 1919 }, 0 },
	{ GammaVersion, LevelAndActIDs_RedMountain2, { -78, 831, 1919 }, 0 },
	{ KnucklesVersion, LevelAndActIDs_RedMountain3, { -3147, 764, -1358 }, 0xFFFFC000 },
	{ SonicVersion, LevelAndActIDs_SkyDeck1, {0, -387.625, 379.5}, 270},
	{ TailsVersion, LevelAndActIDs_SkyDeck1, {0, -387.625, 379.5}, 270},
	{ SonicVersion, LevelAndActIDs_SkyDeck2, { 327, -74, 2535 }, 0 },
	{ SonicVersion, LevelAndActIDs_SkyDeck3, { -696, -86, 135 }, 0 },
	{ KnucklesVersion, LevelAndActIDs_SkyDeck3, { 674, 207, 12 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_LostWorld1, { -264, 73, -168 }, 0 },
	{ SonicVersion, LevelAndActIDs_LostWorld2, { 220, 73, -1423 }, 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_LostWorld2, { 7482, -2622, 908 }, 0 },
	{ SonicVersion, LevelAndActIDs_LostWorld3,  { 270, 10, 0 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap1, { 1580, 84, 1074 }, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap2, { 1060, 336, 280 }, 0 },
	{ SonicVersion, LevelAndActIDs_IceCap3, { 120, 375, -40 }, 0x8800 },
	{ TailsVersion, LevelAndActIDs_IceCap3, { 478.602, 352.953, -193.202 }, 0x8800 },
	{ BigVersion, LevelAndActIDs_IceCap4, { 1260, 224, -38 }, 0 },
	{ SonicVersion, LevelAndActIDs_FinalEgg1, { 170, -165, 490 }, 0 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, { 170, -165, 490 }, 0xC000 },
	{ SonicVersion, LevelAndActIDs_FinalEgg2, { 1060, 595, -383 }, 0xC000 },
	{ SonicVersion, LevelAndActIDs_FinalEgg3, { 1071.7f, 240, -518 }, 0x8000 },
	{ GammaVersion, LevelAndActIDs_FinalEgg3, { 46.5f, -3240.6f, -224.5f }, 0 },
	{ AmyVersion, LevelAndActIDs_HotShelter1, { 0, 236, 51.5f }, 0x4000 },
	{ BigVersion, LevelAndActIDs_HotShelter1, { 0, 236, 51.5f }, 0x4000 },
	{ AmyVersion, LevelAndActIDs_HotShelter2, { 215, 278, -398 }, 0x4000 },
	{ GammaVersion, LevelAndActIDs_HotShelter3, { -20, 486, 73 }, 0xC000 },
};

bool MovePlayerToStartPoint_(bool force = false)
{
	uint16_t levelact = (((short)CurrentLevel) << 8) | CurrentAct;

	BackRing_CheckAndApply();

	if (GameMode != 9 && GameMode != 10 && CurrentLevel < LevelIDs_StationSquare && CurrentLevel > LevelIDs_Past)
		GameMode = GameModes_Adventure_ActionStg; //force gamemode to 4 to fix the restart.

	int GetCP = CheckRestartLevel();
	if (!GetCP || force) //don't change player position if a CP has been grabbed.
	{
		if (!GetBackRing && ActCopy == CurrentAct && CurrentLevel != LevelIDs_Casinopolis)
			ResetTime();

		GetBackRing = false;

		if (CurrentCharacter == Characters_Gamma)
			SetTime(6, 0);

		Float diff = 0.0f;
		for (uint8_t i = 0; i < LengthOfArray(PlayerStartPosition); i++)
		{
			if (levelact == PlayerStartPosition[i].LevelID && CurrentStageVersion == PlayerStartPosition[i].version)
			{
				for (uint8_t j = 0; j < PMax; j++)
				{
					auto p = playertwp[j];
					if (p)
					{
						p->pos = PlayerStartPosition[i].Position;
						p->ang.y = PlayerStartPosition[i].YRot;
						p->pos.x += diff;
						diff += 10.0f;
					}
				}

				return true;
			}
		}
	}

	return false;
}

void MovePlayerToStartPoint_r(taskwk* data) 
{
	if (MovePlayerToStartPoint_() == false)
	{
		MovePlayerToStartPoint_t.Original(data);
	}
}

void __cdecl LoadLevelObject_r() 
{
	if (isRandoLevel()) 
	{
		Load_ObjectsCommon();
	}

	if (CurrentCharacter != Characters_Gamma && (CurrentStageVersion == GammaVersion || CurrentLevel == LevelIDs_E101 || CurrentLevel == LevelIDs_E101R))
		LoadCharTextures(Characters_Gamma); //fix E100 Series crash

	LoadPVM("BACKRING", &GoalRingTextures);
	CheckAndLoad_TreasureHunting();
	LoadEnemyAndMiniMalTex();

	if (!isMPMod())
		LoadObject(LoadObj_Data1, 0, AI_Manager);
	else
	{	
		CheckAndSetUpgrades();	
	}

	auto original = reinterpret_cast<decltype(LoadLevelObject_r)*>(LoadLevelObject_t->Target());
	original();
}

void __cdecl RunLevelDestructor_r(int heap) 
{
	if (heap == 0) 
	{
		ResetValueAndObjects(); //Unload rando stuff*/
	}

	FunctionPointer(void, original, (int heap), RunLevelDestructor_t->Target());
	return original(heap);
}

void LevelOnFrames() 
{

	if (!CharObj2Ptrs[0])
		return;

	Chao_OnFrame();
	CheckAndDisplayWarningLayoutError();
	Hud_DisplayOnframe();
	IncreaseSpeedCharactersPerfectChaos();
	CheckAndLoadTriggerObject();
	PlayRandomCutscene_OnFrames();
	CheckAndPlayCredits();
	
}

void __cdecl MovePlayersMulti()
{
	ResetHomingAttackTargetsAndThings();

	if (MPPlayers > 1)
	{
		if (CurrentStageVersion != Characters_Eggman && CurrentStageVersion != Characters_Tikal && CurrentStageVersion < Characters_MetalSonic)
			CurrentCharacter = CurrentStageVersion;
	}
	MovePlayerToStartPoint_(true);
}

void __cdecl FreeEntityCollision_r(taskwk* a1)
{
	colliwk* v1; 

	if (a1)
	{
		v1 = a1->cwp;
		if (v1)
		{
			if ((v1->flag & 0x8000) != 0)
			{
				if (v1->info)
				{
					FreeMemory(v1->info);
					v1->info = 0;
				}
			}
			FreeMemory(v1);
			a1->cwp = 0;
		}
	}
}

void LevelFeaturesInit() {

	if (!RNGStages)
		return;

	MovePlayerToStartPoint_t.Hook(MovePlayerToStartPoint_r);

	if (isMPMod())
		WriteCall((void*)0x415A51, MovePlayersMulti);
	RunLevelDestructor_t = new Trampoline((int)RunLevelDestructor, (int)RunLevelDestructor + 0x6, RunLevelDestructor_r);
	LoadLevelObject_t = new Trampoline((int)LoadLevelObject, (int)LoadLevelObject + 0x7, LoadLevelObject_r);
	return;
}