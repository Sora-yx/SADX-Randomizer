#include "stdafx.h"
#include "data\chao.h"
#include <fstream>
#include <iostream> 

ObjectMaster* ChaoObject;
ObjectMaster* CurrentChao;
ObjectMaster* chaoHint;
uint8_t chaoWarpAllowedCount = 0;

Trampoline* Chao_Gravity_t;
Trampoline* Chao_Movements_t;
Trampoline* al_confirmsave_t;
Trampoline* al_confirmload_t;

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
		isChaoGameplayAllowed = false;
		return;
	}
}

//Teleport to chao garden every 3 levels/bosses.
void ChaoGardenWarp_Check() {
	if (!isChaoGameplayAllowed)
		return;

	if (chaoWarpAllowedCount < 3)
		chaoWarpAllowedCount++;

}


//Load Chao files
void Chao_LoadFiles() {
	float height = -10000000;
	WriteData((float*)0x73C24C, height);

	ChaoMain_Constructor();
	al_confirmload_load();
	ChaoManager_Load();
}

void ChaoTPTrigger(ObjectMaster* a1) {

	short Size = 10;

	if (CurrentCharacter >= Characters_Gamma)
		Size = 15;

	if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, Size))
	{
		DisableControl();
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
			CharObj2Ptrs[0]->Speed.x = 1.0f;
		data->Action++;
		break;
	case 1:
		if (!flashScreenChao && EnableControl)
			flashScreenChao = LoadObject(LoadObj_Data1, 1, FlashScreen);
		if (++data->field_A == 60) {
			data->Action++;
		}
		break;
	case 2:

		for (int i = 0; i < LengthOfArray(M3_PlayerEndPosition); i++)
		{

			if (CurrentLevel == ConvertLevelActsIDtoLevel(M3_PlayerEndPosition[i].LevelID) && CurrentAct == ConvertLevelActsIDtoAct(M3_PlayerEndPosition[i].LevelID)
				&& CurrentStageVersion == M3_PlayerEndPosition[i].version) {

				TeleportPlayerResultScreen(M3_PlayerEndPosition[i].Position, M3_PlayerEndPosition[i].YRot);
				break;
			}
		}
		data->Action++;
		break;
	case 3:

		StopMusic();
		PauseEnabled = 0;
		if (++data->InvulnerableTime == 15) {
			chaoPB++;
			data->Action++;
		}
		break;
	case 4:
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

	}

	Chao_DeleteFiles();
}

bool isLoaded = false;
void RandomSpawnChao() {

	if (!isLoaded) {
		Chao_LoadFiles();
		isLoaded = true;
	}

	ChaoData* chaodata = new ChaoData();
	CurrentChao = CreateChao(chaodata, 0, 0, &EntityData1Ptrs[0]->Position, 0);
	CurrentChao->Data1->Rotation.y = Yrot;

	Sint8 randomModel = rand() % 26;

	if (randomModel < 2)
		randomModel = 2;

	Change_ChaoType(CurrentChao, randomModel);
}

void Load_ItemBoxOneLife(ObjectMaster* a1) {
	SETObjData* life = new SETObjData();
	a1->SETData.SETData = life;
	a1->MainSub = ItemBox_Main;
	a1->DisplaySub = ItemBox_Display;
	a1->Data1->Scale.x = 6;
}

void __cdecl ChaoObj_Main(ObjectMaster* a1) {

	EntityData1* data = a1->Data1;
	EntityData1* P1 = EntityData1Ptrs[0];

	switch (a1->Data1->Action) {
	case ChaoAction_Init:
	{
		if (!CurrentLandTable)
			return;

		if (CurrentMission != Mission3_LostChao) {
			Load_ItemBoxOneLife(a1);
			return;
		}

		Chao_LoadFiles();

		a1->DisplaySub = a1->MainSub;
		a1->DeleteSub = ChaoObj_Delete; //When you quit a level
		data->Action++;
	}
	break;
	case ChaoAction_LoadChao:
	{
		ChaoData* chaodata = new ChaoData();
		a1->Child = CreateChao(chaodata, 0, a1->Child, &a1->Data1->Position, 0);
		CurrentChao = a1->Child;
		a1->Child->Data1->Rotation.y = Yrot;

		if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 2)
			LoadObject(LoadObj_Data1, 2, LoadChaoTPTrigger);


		data->Action++;

	}
	break;
	case ChaoAction_RandomizeChao:
		if (++data->Index == 100) {
			uint8_t isCharChao = rand() % 2;
			Sint8 randomModel = rand() % 26;

			if (isCharChao) {
				randomModel = 23 + rand() % 2;
			}

			if (randomModel < 2)
				randomModel = 2;


			Change_ChaoType(a1->Child, randomModel);

			data->Action++;

		}
		break;
	case ChaoAction_CheckHit:
	{
		if (GameState == 15) {
			if (++data->InvulnerableTime == 80) {	//Loop Cry Animation
				Chao_SetBehavior(a1->Child, (long*)Chao_Cry(a1->Child));
				data->InvulnerableTime = 0;
			}
		}

		//water height
		float height = -10000000;
		WriteData((float*)0x73C24C, height);

		if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, 200)) //Cry Hint
			Chao_CrySound();

		if (IsPlayerInsideSphere(&a1->Data1->Position, 80)) {
			SwapDelay = 0;
		}

		int HitBox = 0;

		if (GetCharacter0ID() >= Characters_Gamma)
			HitBox = 22;
		else
			HitBox = 11;

		if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, HitBox))
		{
			DisableControl();
			data->Action = ChaoAction_Hit;
		}
	}
	break;
	case ChaoAction_Hit:
	{
		StopMusic();
		Chao_SetBehavior(a1->Child, (long*)Chao_Pleasure(a1->Child)); //Move to Happy animation
		LoadObject(LoadObj_Data1, 1, MissionLostChaoResult);
		data->InvulnerableTime = 0;
		data->Action++;
	}
	break;
	case ChaoAction_Transition:
		if (++data->field_A == 90) {
			data->Action++;
		}
		break;
	case ChaoAction_Free:
	{
		if (GameState == 15) 
		{

			if (++data->InvulnerableTime == 120) {
				Chao_SetBehavior(a1->Child, (long*)Chao_Pleasure(a1->Child));
				data->InvulnerableTime = 0;
				return;
			}
		}
	}
	break;
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


void Chao_Gravity_r(ObjectMaster* obj) {
	if (CurrentLevel >= LevelIDs_SSGarden || !TimeThing && DoesChaoNeedGravity(CurrentLevel)) {
		ObjectFunc(original, Chao_Gravity_t->Target());
		original(obj);
	}
}


void Chao_Movements_r(ObjectMaster* obj) {
	if (CurrentLevel >= LevelIDs_SSGarden) {
		ObjectFunc(original, Chao_Movements_t->Target());
		original(obj);
	}
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
		if (ChaoSpawnAllowed && !ChaoObject && GameState == 15 && CurrentLevel < 15) {

			ChaoObject = LoadObject((LoadObj)(LoadObj_Data1), 1, ChaoObj_Main);
			ChaoObject->Data1->Position = pos;
			ChaoObject->Data1->Rotation.y = Yrot;
			ChaoSpawn = true;
		}
	}

	return;
}

//Lost Chao Mission: fix a rare issue for some people where the game crashes when trying to save chao data if a save doesn't already exist.
void al_confirmsave_r(ObjectMaster* obj)
{
	if (IsLevelChaoGarden()) {
		ObjectFunc(original, al_confirmsave_t->Target());
		original(obj);
	}

	return;
}

//see comment above
void al_confirmload_r(ObjectMaster* obj)
{
	if (IsLevelChaoGarden()) {
		ObjectFunc(original, al_confirmload_t->Target());
		original(obj);
	}

	return;
}


void Chao_Init() {

	ChaoGameplayCheck();

	Chao_Gravity_t = new Trampoline(0x73FEF0, 0x73FEF8, Chao_Gravity_r);
	Chao_Movements_t = new Trampoline(0x71EFB0, 0x71EFB9, Chao_Movements_r);
	al_confirmsave_t = new Trampoline((int)al_confirmsave, (int)al_confirmsave + 0x7, al_confirmsave_r);
	al_confirmload_t = new Trampoline((int)al_confirmload, (int)al_confirmload + 0x5, al_confirmload_r);
	return;
}