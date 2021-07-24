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



void ChaoTPTrigger(ObjectMaster* a1) {

	short Size = 10;

	if (CurrentCharacter >= Characters_Gamma)
		Size = 15;

	if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, Size))
	{
		ChaoObject->Data1->Action = ChaoAction_Hit;
		a1->Data1->Action++;
	}
}


void LoadChaoTPTrigger(ObjectMaster* obj) {

	EntityData1* data = obj->Data1;

	switch (data->Action) {
	case 0:
		data->Position = { -121, 50, 290 };
		data->Scale.x = 15;
		data->Action++;
		break;
	case 1:
		ChaoTPTrigger(obj);
		break;
	case 2:
		CheckThingButThenDeleteObject(obj);
		break;
	}
}


void Chao_DeleteFiles() {

	CheckThingButThenDeleteObject(ChaoManager);
	CheckThingButThenDeleteObject(chaoHint);
	CheckThingButThenDeleteObject(CurrentChao);
	CheckThingButThenDeleteObject(ChaoObject);
	ChaoManager = nullptr;
	CurrentChao = nullptr;
	ChaoObject = nullptr;
	chaoHint = nullptr;

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

		for (int i = 0; i < LengthOfArray(M3_PlayerEndPosition); i++)
		{

			if (CurrentLevel == ConvertLevelActsIDtoLevel(M3_PlayerEndPosition[i].LevelID) && CurrentAct == ConvertLevelActsIDtoAct(M3_PlayerEndPosition[i].LevelID)
				&& CurrentStageVersion == M3_PlayerEndPosition[i].version) {

				TeleportPlayerResultScreen(M3_PlayerEndPosition[i].Position, M3_PlayerEndPosition[i].YRot);
				break;
			}
		}
		data->Action = 2;
		break;
	case 2:
		StopMusic();
		PauseEnabled = 0;
		if (++data->InvulnerableTime == 75) {
			chaoPB++;
			data->Action = 3;
		}
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
		data->Action++; 
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

		if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 2)
			LoadObject(LoadObj_Data1, 2, LoadChaoTPTrigger);
		data->Action++;
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
	if (!chaoHint && ChaoSpawn && CurrentLevel == LevelIDs_FinalEgg && CurrentAct == 2)
	{
		chaoHint = LoadObject(LoadObj_Data1, 2, TriggerObj);
		chaoHint->Data1->Position = { 2708.575195, -622.6781616, -955.2252808 };
		chaoHint->Data1->Scale.x = 50;
	}
}

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

