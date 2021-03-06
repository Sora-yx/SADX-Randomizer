#include "stdafx.h"
#include "data\chao.h"
#include <fstream>
#include <iostream> 

ObjectMaster* ChaoObject;
ObjectMaster* CurrentChao;
ObjectMaster* chaoHint;

short ChaoCryDelay = 0;
static bool pvploaded = false;
bool ChaoSpawn = false;

ObjectMaster* ChaoTP = nullptr;

NJS_VECTOR pos;
float Yrot;
bool ChaoSpawnAllowed = false;

void __cdecl ChaoGameplayCheck() {

	HMODULE ChaoGameplay = GetModuleHandle(L"sadx-chao-gameplay");

	if (ChaoGameplay && !isChaoGameplayAllowed) {
		int msgboxID = MessageBoxA(WindowHandle, "Chao Gameplay Mod has been detected, would you like to pick your Chao before starting your Randomizer Adventure? (Note: to disable this message, please Allow Chao Gameplay in the settings.)", "SADX Randomizer", MB_YESNO);
		switch (msgboxID)
		{
		case IDYES:
			isChaoGameplayAllowed = true;
			break;
		case IDNO:
		default:
			isChaoGameplayAllowed = false;
			break;
		}
	}

	if (!ChaoGameplay && isChaoGameplayAllowed)
	{
		MessageBoxA(WindowHandle, "Couldn't find Chao Gameplay Mod, make sure the mod is checked and installed.", "SADX Randomizer Error", MB_ICONERROR);
	}
}

//This is where all the stuff to load "Lost Chao" mission is managed, Thanks to Kell for making a big part of the code here.

int GetCurrentChaoStage_r() {
	if (ChaoObject)
		return 5;
	else
		return CurrentChaoStage;
}


//Load Chao files
void Chao_LoadFiles() {
	float height = -10000000;
	WriteData((float*)0x73C24C, height);

	if (!pvploaded) {
		al_confirmload_load();
		pvploaded = LoadChaoPVPs();
	}

	ChaoManager_Load();
	LoadChaoTexlist("AL_BODY", &ChaoTexLists[0], 0);
	LoadChaoTexlist("AL_ICON", &ChaoTexLists[3], 0);
	LoadChaoTexlist("AL_EYE", &ChaoTexLists[2], 0);
	LoadChaoTexlist("AL_MOUTH", &ChaoTexLists[5], 0);
	LoadChaoTexlist("AL_TEX_COMMON", &ChaoTexLists[1], 1u);
}

void ChaoTPTriggerDelete(ObjectMaster* a1) {

	if (a1 != nullptr) {
		CheckThingButThenDeleteObject(a1);
	}
	ChaoTP = nullptr;
}

void LoadChaoTPTrigger() {

	if (!ChaoTP && CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 2 && CurrentMission == Mission3_LostChao)
	{
		ChaoTP = LoadObject(LoadObj_Data1, 2, ChaoTPTrigger);
		ChaoTP->Data1->Position = { -121, 50, 290 };
		ChaoTP->Data1->Scale.x = 15;
		ChaoTP->DeleteSub = ChaoTPTriggerDelete;
	}
}



void Chao_DeleteFiles() {

	CheckThingButThenDeleteObject(ChaoManager);
	ChaoTPTriggerDelete(ChaoTP);
	CheckThingButThenDeleteObject(chaoHint);
	CheckThingButThenDeleteObject(CurrentChao);
	CheckThingButThenDeleteObject(ChaoObject);
	ChaoManager = nullptr;
	CurrentChao = nullptr;
	ChaoObject = nullptr;
	chaoHint = nullptr;
	ChaoTP = nullptr;

	//Release the chao textures
	FreeChaoTexlists();

	//reset default water height
	float height = 0;
	WriteData((float*)0x73C24C, height);

	njReleaseTexture(&ChaoTexLists[0]);
	njReleaseTexture(&ChaoTexLists[1]);
	njReleaseTexture(&ChaoTexLists[2]);
	njReleaseTexture(&ChaoTexLists[3]);
	njReleaseTexture(&ChaoTexLists[5]);
	ChaoSpawnAllowed = false;
	ChaoSpawn = false;
}

ObjectMaster* flashScreenChao = nullptr;
void MissionLostChaoResult(ObjectMaster* obj) {

	EntityData1* data = obj->Data1;
	CharObj2* co2 = CharObj2Ptrs[0];

	switch (data->Action)
	{
	case 0:
		flashScreenChao = nullptr;
		if (co2->Speed.x > 1.3)
			CharObj2Ptrs[0]->Speed.x = 1.3;
		EntityData1Ptrs[0]->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);

		data->Action = 1;
		break;
	case 1:
		if (!flashScreenChao && EnableControl)
			flashScreenChao = LoadObject(LoadObj_Data1, 1, FlashScreen);
		chaoPB++;
		EntityData1Ptrs[0]->Position.x += 2;
		data->Action = 2;
		break;
	case 2:
		StopMusic();
		PauseEnabled = 0;
		if (++data->InvulnerableTime == 75)
			data->Action = 3;
		break;
	case 3:
		LoadLevelResults_r();
		CheckThingButThenDeleteObject(obj);
		break;
	}
}

void ChaoObj_Delete(ObjectMaster* a1) {
	if (a1->Child != nullptr)
	{
		if (a1->Child) {
			CheckThingButThenDeleteObject(a1->Child);
			a1->Child = nullptr;
		}

		if (a1->Data1->LoopData) {
			delete a1->Data1->LoopData;
			a1->Data1->LoopData = nullptr;
		}
	}

	Chao_DeleteFiles();
}


void __cdecl ChaoObj_Main(ObjectMaster* a1) {

	EntityData1* data = a1->Data1;
	EntityData1* P1 = EntityData1Ptrs[0];

	switch (a1->Data1->Action) {
	case ChaoAction_Init:
	{
		if (!CurrentLandTable)
			return;

		//Load the chao textures
		Chao_LoadFiles();

		a1->DisplaySub = a1->MainSub;
		a1->DeleteSub = ChaoObj_Delete; //When you quit a level
		data->Action = 1; //Wait a frame before loading the chao
	}
	break;
	case ChaoAction_LoadChao:
	{
		ChaoData* chaodata = new ChaoData();

		//Start position is behind the player
		NJS_VECTOR v = a1->Data1->Position;

		//Load the chao
		a1->Data1->LoopData = (Loop*)chaodata;
		a1->Child = CreateChao(chaodata, 0, a1->Child, &a1->Data1->Position, 0);
		CurrentChao = a1->Child;
		a1->Child->Data1->Rotation.y = Yrot;
		LoadChaoTPTrigger();
		data->Action = 2;
	}
	break;
	case ChaoAction_CheckHit:
	{
		if (GameState == 15) {
			if (++a1->Data1->InvulnerableTime == 80) {	//Loop Cry Animation
				Chao_SetBehavior(a1->Child, (long*)Chao_Cry(a1->Child));
				a1->Data1->InvulnerableTime = 0;
			}
		}

		//water height
		float height = -10000000;
		WriteData((float*)0x73C24C, height);

		if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, 200)) //Cry Hint
			Chao_CrySound();

		int HitBox = 0;

		if (GetCharacter0ID() >= Characters_Gamma)
			HitBox = 20;
		else
			HitBox = 9;

		if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, HitBox))
		{
			DisableControl();
			data->Action = ChaoAction_Hit;
		}
	}
	break;
	case ChaoAction_Hit:
	{
		Chao_SetBehavior(a1->Child, (long*)Chao_Pleasure(a1->Child)); //Move to Happy animation
		a1->Child->Data1->Rotation.y = -P1->Rotation.y + 0x4000;
		LoadObject(LoadObj_Data1, 1, MissionLostChaoResult);
		a1->Data1->InvulnerableTime = 0;
		data->Action = ChaoAction_Free;
	}
	break;
	case ChaoAction_Free:
	{
		if (GameState == 15) {

			if (++a1->Data1->InvulnerableTime == 120) {
				Chao_SetBehavior(a1->Child, (long*)Chao_Pleasure(a1->Child));
				a1->Data1->InvulnerableTime = 0;
				return;
			}
		}
		else
		{
			a1->Data1->Action = 4;
			return;
		}
	}
	break;
	}
}



void Chao_Gravity_r(ObjectMaster* obj);
Trampoline Chao_Gravity_t(0x73FEF0, 0x73FEF8, Chao_Gravity_r);
void Chao_Gravity_r(ObjectMaster* obj) {
	if (CurrentLevel >= LevelIDs_SSGarden || !TimeThing && DoesChaoNeedGravity(CurrentLevel)) {
		ObjectFunc(original, Chao_Gravity_t.Target());
		original(obj);
	}
}


void Chao_Movements_r(ObjectMaster* obj);
Trampoline Chao_Movements_t(0x71EFB0, 0x71EFB9, Chao_Movements_r);
void Chao_Movements_r(ObjectMaster* obj) {
	if (CurrentLevel >= LevelIDs_SSGarden) {
		ObjectFunc(original, Chao_Movements_t.Target());
		original(obj);
	}
}

bool DoesChaoNeedGravity(_int16 CurLevel) {

	switch (CurLevel)
	{
	case LevelIDs_TwinklePark:
		if (CurrentAct == 2)
			return true;
		else
			return false;
		break;
	case LevelIDs_SpeedHighway:
	case LevelIDs_SkyDeck:
	case LevelIDs_LostWorld:
		return false;
		break;
	case LevelIDs_FinalEgg:
		if (CurrentAct == 2)
			return true;
		else
			return false;
		break;
	case LevelIDs_HotShelter:
		if (CurrentAct == 2)
			return false;
		else
			return true;
		break;
	default:
		return true;
		break;
	}

	return true;
}

void Chao_Init() {
	ChaoGameplayCheck();

	//Trick the game into thinking we're in a specific chao garden
	//Needed to change the water height
	WriteJump((void*)0x715140, GetCurrentChaoStage_r);
}

void Chao_CrySound() {
	short cry = -1;

	if (!ChaoCryDelay)
	{
		cry = rand() % 2;

		if (!cry)
			PlayVoice_Original(5003);
		else
			PlayVoice_Original(5002);

		//prevcry = cry;
		ChaoCryDelay = 420;
	}

	return;
}

void TriggerObj(ObjectMaster* obj) {
	if (TimeThing != 0 && IsPlayerInsideSphere(&obj->Data1->Position, 50))
		Chao_CrySound();
}

void ChaoCryHint() {
	//LoadObject(Allocated Memory, Object List, Object Function)
	//Memory: Data1 = EntityData1*; Data2 = EntityData2*, etc.
	//List = ordre d'appel des objets (tous les objets 0 d'abord, puis les objets 1, etc.) 2 et 3 pour les objets de niveaux, 4 pour les enemies je crois.
	//Function = chaque objet va appeler cette fonction, mais avec des donn�es diff�rentes.

	if (!chaoHint && ChaoSpawn && CurrentLevel == LevelIDs_FinalEgg && CurrentAct == 2)
	{
		chaoHint = LoadObject(LoadObj_Data1, 2, TriggerObj);
		chaoHint->Data1->Position = { 2708.575195, -622.6781616, -955.2252808 };
		chaoHint->Data1->Scale.x = 50;
	}
}


void ChaoTPTrigger(ObjectMaster* a1) {

	short Size = 10;

	if (CurrentCharacter >= Characters_Gamma)
		Size = 15;

	if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, Size))
	{
		ChaoObject->Data1->Action = ChaoAction_Hit;
	}
}


SetLevelPosition PlayerAroundChaoPosition[15]{

	{ BigVersion, LevelAndActIDs_EmeraldCoast3, 5901.4, 537.225, 568.47, 0x8000 },
	{ SonicVersion, LevelAndActIDs_WindyValley3, 3608.115, -4250.02, -2132.28, 0x8000 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, 330.48, 942.379, -133.624, 0x8000 },
	{ BigVersion, LevelAndActIDs_TwinklePark2, 608.112, 499.01, -55.8172, 0x8000 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway1, 3653.31, -127.07, 2924.58, 0x8000 },
	{ TailsVersion, LevelAndActIDs_SpeedHighway1, 8019, -597, 8868, 0x8000 },
	{ KnucklesVersion, LevelAndActIDs_SpeedHighway3, -230.366, 410.935, -1891.33, 324.125 },
	{ SonicVersion, LevelAndActIDs_RedMountain1, -3855.28, 1000.21, -2946.56 },
	{ GammaVersion, LevelAndActIDs_RedMountain2, -430, 1200, 3141 },
	{ KnucklesVersion, LevelAndActIDs_LostWorld2, 7421, -1580, 1403 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, 2897.51, 5810.17, -1993.62},
	{ GammaVersion, LevelAndActIDs_FinalEgg3, 1517.56, -3139.29, -274.385},
	{ BigVersion, LevelAndActIDs_HotShelter1, -211.615, 418.875, -275.99 },
	{ AmyVersion, LevelAndActIDs_HotShelter2, 1060.4085693, 750.8605957, -2952.347412 },
	{ GammaVersion, LevelAndActIDs_HotShelter3, -1302.44, 3378.13, -3116.41 },
};

NJS_VECTOR SetPlayerAroundLostChaoPosition() {

	HMODULE DCModChao = GetModuleHandle(L"DCMods_Main");
	uint16_t levelact = (((short)CurrentLevel) << 8) | CurrentAct;

	for (int i = 0; i < LengthOfArray(PlayerAroundChaoPosition); i++) {
		if (levelact == PlayerAroundChaoPosition[i].LevelID && CurrentStageVersion == PlayerAroundChaoPosition[i].version)
		{
			if (CurrentLevel == LevelIDs_HotShelter && DCModChao && CurrentStageVersion == AmyVersion) //Dreamcast Mod exception, as the landtable is different.
				return { 1060.4085693, 528.2105103, -2952.347412 };
			else
				return PlayerAroundChaoPosition[i].Position;
		}
	}

	return { -1, -1, -1 };
}


SetLevelPosition ChaoLevelPosition[26]{

	{ GammaVersion, LevelAndActIDs_EmeraldCoast1, 1599, 114.75, 840, 0x0 - 0x4000 },
	{ SonicVersion, LevelAndActIDs_EmeraldCoast2, 3857.76, 596.395, -2896.18, 0x8000 },
	{ BigVersion, LevelAndActIDs_EmeraldCoast3, 6103.9, 559.725, 630.345, 0xBDAC},
	{ SonicVersion, LevelAndActIDs_WindyValley3, 3489.99, -4340.27, -2132.28, 0x8000 },
	{ SonicVersion, LevelAndActIDs_Casinopolis1, 361, 380, -40, 0x8000 },
	{ TailsVersion, LevelAndActIDs_Casinopolis2, -1565.96, -2205, 2654.24, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap2, 1480.62, 573.3, -256.67, 0x8000 },
	{ BigVersion, LevelAndActIDs_IceCap4, 1790.85, 371.968811, 11.265, 0x8000 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, -89.1414, 830, -991.721, 0x8000 }, //Sonic Version
	{ BigVersion, LevelAndActIDs_TwinklePark2, 604, 338, 237, 0x8000 }, //Big Version
	{ AmyVersion, LevelAndActIDs_TwinklePark3, -41.43054199, 50, 290.7596436, 0x0 - 0x4000  }, //Amy Version
	{ SonicVersion, LevelAndActIDs_SpeedHighway1, 4455, -386.135, 2930.18, 4.479076996E-43 - 0x4000},
	{ TailsVersion, LevelAndActIDs_SpeedHighway1, 8570.973, -950.125, 8984.435, 0x8000 + 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_SpeedHighway3, -232.625, 483.875, -2216, 2.0  },
	{ SonicVersion, LevelAndActIDs_RedMountain1, -3861.85, 883.96, -2974.81, 13754 - 0x3200 },
	{ GammaVersion, LevelAndActIDs_RedMountain2, -119.452, 1051.5, 3375.85, 40880},
	{ KnucklesVersion, LevelAndActIDs_RedMountain3, -1761.775, 71.5, -1862.41, 5.479076996E-43 + 0x4000 },
	{ SonicVersion, LevelAndActIDs_SkyDeck2, -316.7368469, 38.99000168, -687.1625977, 0x8000 },
	{ SonicVersion, LevelAndActIDs_LostWorld2, 909.875, 164.625, 152.5, 0x0 + 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_LostWorld2, 7410, -1965, 1316, 0x8000 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, 2974.897, 5663.096, -1992.15, -1.681558157E-44 + 0x4000 },
	{ GammaVersion, LevelAndActIDs_FinalEgg3, 1939, -3174.049561, -128, 0x8000 }, //Gamma Version
	{ SonicVersion, LevelAndActIDs_FinalEgg3, 2659.293457, -2888.063965, -946.1408081, 0x8000 }, //Sonic Version
	{ BigVersion, LevelAndActIDs_HotShelter1, -157.615, 418.875, -271.49, 0x8000 }, //Big Version 
	{ AmyVersion, LevelAndActIDs_HotShelter2, 716.4085693, 677.8605957, -2952.347412, -1.681558157E-44 + 0xC000 }, //Amy version SADX VANILLA
	{ GammaVersion, LevelAndActIDs_HotShelter3, 2.01, 3221, -3136, 0x8000 },
};


bool SetAndGetLostChaoPosition() {

	HMODULE DCModChao = GetModuleHandle(L"DCMods_Main");
	uint16_t levelact = (((short)CurrentLevel) << 8) | CurrentAct;

	for (int i = 0; i < LengthOfArray(ChaoLevelPosition); i++) {
		if (levelact == ChaoLevelPosition[i].LevelID && CurrentStageVersion == ChaoLevelPosition[i].version)
		{
			if (CurrentLevel == LevelIDs_SpeedHighway && CurrentAct == 2 && !MMPlatformEnabled)
				return false;

			if (CurrentLevel == LevelIDs_HotShelter && DCModChao && CurrentStageVersion == AmyVersion) //Dreamcast Mod exception, as the landtable is different.
				pos = { 716.4085693, 428.2105103, -2952.347412 };
			else
				pos = ChaoLevelPosition[i].Position;
			Yrot = ChaoLevelPosition[i].YRot;
			ChaoSpawnAllowed = true;
			ChaoSpawn = true;
			return true;
		}
	}

	ChaoSpawnAllowed = false;
	ChaoSpawn = false;
	return false;
}


void Chao_OnFrame() {

	if (CurrentLevel >= LevelIDs_Chaos0 || CurrentMission != Mission3_LostChao)
		return;

	if (ChaoCryDelay > 0)
		ChaoCryDelay--;

	ChaoSpawnAllowed = SetAndGetLostChaoPosition();

	if (!ChaoSpawnAllowed && ChaoObject != nullptr)
	{
		Chao_DeleteFiles();
	}
	else
	{
		if (ChaoSpawnAllowed && !ChaoObject && GameState == 15 && CurrentMissionCard == 1 && CurrentLevel < 15) {
			ChaoObject = LoadObject((LoadObj)(LoadObj_Data1), 1, ChaoObj_Main);
			ChaoObject->Data1->Position = pos;
			ChaoObject->Data1->Rotation.y = Yrot;
			ChaoSpawn = true;
		}
	}

	return;
}

