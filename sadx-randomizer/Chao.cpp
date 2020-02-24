#include "stdafx.h"
#include "data\chao.h"
#include "RandomHelpers.h"
#include "Trampoline.h"

ObjectMaster* ChaoObject;
ObjectMaster* CurrentChao;
ObjectMaster* a2;
ObjectMaster* chaoHint;

uint8_t SelectedChao = 0;
short ChaoCryDelay = 0;
bool ArePvpLoaded = false;
extern int chaoPB;
bool ChaoSpawn = false;


ObjectMaster* ChaoTP = nullptr;

std::vector<NJS_PLANE> waterlist = {};

ChaoHandle ChaoMaster;

void ChaoGameplayCheck() {

	HMODULE ChaoGameplay = GetModuleHandle(L"sadx-chao-gameplay");
	if (ChaoGameplay && !isChaoGameplayAllowed) {
		int msgboxID = MessageBoxA(WindowHandle, "Chao Gameplay Mod has been detected, would you like to pick your Chao before starting your Randomizer Adventure?", "SADX Randomizer", MB_YESNO);

		switch (msgboxID)
		{
		case IDYES:
			isChaoGameplayAllowed = true;
			MessageBoxA(WindowHandle, "Randomizer will now send you to the Chao Garden when starting a new story. You can disable this in the settings.", "SADX Randomizer", MB_ICONINFORMATION);
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
	if (ChaoObject) return 5;
	else return CurrentChaoStage;
}

void ChaoObj_Animate(int id, int length) {
	if (FrameCounterUnpaused % length == 0) {
		Chao_Animation(CurrentChao, id);
	}
}

void ChaoObj_Delete(ObjectMaster* a1) {

	DeleteObject_(ChaoManager);
	ChaoManager = nullptr;
	DeleteObject_(ChaoTP);
	DeleteObject_(chaoHint);
	DeleteObject_(CurrentChao);
	CurrentChao = nullptr;
	ChaoObject = nullptr;
	ChaoTP = nullptr;
	chaoHint = nullptr;

	//Release the chao textures
	FreeChaoTexlists();

	//reset default water height
	float height = 0;
	WriteData((float*)0x73C24C, height);
}

ObjectMaster* ChaoCheck = nullptr;

void ChaoObj_Main(ObjectMaster* a1) {

	uint8_t Action = a1->Data1->Action;
	EntityData1* data = a1->Data1;
	ChaoLeash* Leash = &ChaoMaster.ChaoHandles[a1->Data1->CharIndex];
	

	if (Action == 0) {
		if (!CurrentLandTable) return;

		//Load the chao textures
		LoadChaoTexlist("AL_DX_PARTS_TEX", (NJS_TEXLIST*)0x33A1340, 0);
		LoadChaoTexlist("AL_BODY", ChaoTexLists, 0);
		LoadChaoTexlist("AL_jewel", &ChaoTexLists[4], 0);
		LoadChaoTexlist("AL_ICON", &ChaoTexLists[3], 0);
		LoadChaoTexlist("AL_EYE", &ChaoTexLists[2], 0);
		LoadChaoTexlist("AL_MOUTH", &ChaoTexLists[5], 0);
		LoadChaoTexlist("AL_TEX_COMMON", &ChaoTexLists[1], 1u);

		//PVPs only need to be loaded once
		if (!ArePvpLoaded) {
			al_confirmload_load();
			LoadChaoPVPs();
			ArePvpLoaded = true;
			ChaoManager_Load();
		}

		
		a1->DeleteSub = ChaoObj_Delete; //When you quit a level
		a1->Data1->Action = 1; //Wait a frame before loading the chao
	}
	else if (Action == 1) {
		//We get the chao data in the savefile
		ChaoData* chaodata = new ChaoData();

		//Start position is behind the player
		NJS_VECTOR v = a1->Data1->Position;
		
		//Load the chao
		CurrentChao = CreateChao(chaodata, 0, CurrentChao, &v, 0);
		chaodata->data.FlyStat = 1000;
		chaodata->data.FlyLevel = 50;

		a1->Data1->Action = 2;
	}
	else if (Action == 2) {
		
		if (Chao_FinishedAnimation(CurrentChao)) { Chao_Animation(CurrentChao, 0); }

		CurrentChao->Data1->Position = a1->Data1->Position;

		//water height
		float height = -10000000;
		WriteData((float*)0x73C24C, height);
		
		if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, 200))
			Chao_CrySound();

		if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 2)
			return;

		switch (CurrentCharacter)
		{
		case Characters_Gamma:
		case Characters_Big:
			if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, 20))  //Bigger hitbox for Gamma and Big
			{
				chaoPB++; //Chao Credit Stat
				LoadLevelResults();
				a1->Data1->Action = 3;
			}
			break;
		default:
			if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, 9))
			{
				chaoPB++;
				LoadLevelResults();
				a1->Data1->Action = 3;
			}
			break;
		}
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
	if (CurrentLevel >= LevelIDs_SSGarden || !TimeThing) {
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
			PlayVoice_R(5003);
		else
			PlayVoice_R(5002);

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
	//Function = chaque objet va appeler cette fonction, mais avec des données différentes.

	if (!chaoHint && ChaoSpawn && CurrentLevel == LevelIDs_FinalEgg && CurrentAct == 2)
	{
		chaoHint = LoadObject(LoadObj_Data1, 2, TriggerObj);
		chaoHint->Data1->Position = { 2708.575195, -622.6781616, -955.2252808 };
		chaoHint->Data1->Scale.x = 50;
	}
}

void ChaoTPTriggerDelete(ObjectMaster* a1) {

	DeleteObject_(ChaoTP);
	ChaoTP = nullptr;
}


void ChaoTPTrigger(ObjectMaster* a1) {

	short Size = 10;

	if (CurrentCharacter >= Characters_Gamma)
		Size = 15;

	if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, Size))
	{
		chaoPB++; //Chao Credit Stat
		LoadLevelResults();
		a1->Data1->Action = 3;
	}
}


void LoadChaoTPTrigger() {

	if (!ChaoTP)
	{
		ChaoTP = LoadObject(LoadObj_Data1, 2, ChaoTPTrigger);
		ChaoTP->Data1->Position = { -121, 50, 290 };
		ChaoTP->Data1->Scale.x = 15;
		ChaoTP->DeleteSub = ChaoTPTriggerDelete;
	}
}

NJS_VECTOR pos;
float Yrot;

bool isChaoAllowedtoSpawn(short CurLevel, short CurAct) 
{

	switch (CurLevel)
	{
	case LevelIDs_EmeraldCoast:
		if (CurAct == 1)
		{
			pos = { 3857.76, 597.395, -2896.18 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		if (CurAct == 2)
		{
			pos = { 6388, 0.8, 1116 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_WindyValley:
		if (CurAct == 2)
		{
			pos = { 4162.019, -4484, -1800 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_Casinopolis:
		if (CurAct == 0)
		{
			pos = { -361, 380, -40 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		if (CurAct == 1 && CasinoSwitch == 3)
		{
			pos = { -1565.96, -2205, 2654.24 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_IceCap:
		if (CurAct == 1)
		{
			pos = { 1480.62, 573.3, -256.67 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		if (CurAct == 3)
		{
			pos = { 1790.85, 371.968811, 11.265 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_TwinklePark:
		if (CurAct == 1 && !TPAmyVersion && !TPBigVersion)
		{
			pos = { 520, 1330, 1630 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		if (CurAct == 1 && TPBigVersion && !TPAmyVersion)
		{
			pos = { 604, 338, 237 };
			Yrot = 16000;
			ChaoSpawn = true;
		}
		if (CurAct == 2 && TPAmyVersion)
		{
			pos = { -41.43054199, 50, 290.7596436 };
			Yrot = 0;
			LoadChaoTPTrigger();
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_SpeedHighway:
		if (CurAct == 0)
		{
			pos = { 4455, -385.135, 2930.18 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_RedMountain:
		if (CurAct == 0)
		{
			pos = { -3861.85, 883.96, -2974.81 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_SkyDeck:
		if (CurAct == 1)
		{
			pos = { -316.7368469, 50.99000168, -687.1625977 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_LostWorld:
		if (CurAct == 1)
		{
			pos = { 7410, -1965, 1316 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_FinalEgg:
		if (CurAct == 2)
		{
			if (!FEGammaVersion) //Sonic Version
			{
				pos = { 2660.566406, -2888.049561, -943.2208862 };
				Yrot = 0x8000;
				ChaoCryHint();
				ChaoSpawn = true;
			}
			else //Gamma Version
			{
				pos = { 1939, -3174.049561, -128 };
				Yrot = 0x8000;
				ChaoSpawn = true;
			}
		}
		if (CurAct == 0 && FEAmyVersion)
		{
			pos = { 2945.652344, 5589.605469, -2211.165039 };
			ChaoSpawn = true;
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	case LevelIDs_HotShelter:
		if (CurAct == 2)
		{
			pos = { 2.01, 3222, -3136 };
			Yrot = 0x8000;
			ChaoSpawn = true;
		}
		if (CurAct == 1 && HSAmyVersion)
		{
			HMODULE DCModChao = GetModuleHandle(L"DCMods_Main");
			if (DCModChao)
			{
				pos = { 716.4085693, 428.2105103, -2952.347412 };
				Yrot = 0x8000;
				ChaoSpawn = true;
			}
			else
			{
				pos = { 716.4085693, 677.8605957, -2952.347412 };
				Yrot = 0x8000;
				ChaoSpawn = true;
			}
		}
		else
		{
			ChaoSpawn = false;
		}
		if (CurAct == 0 && HSBigVersion)
		{
			if (CurrentCharacter != Characters_Gamma)
			{
				pos = { -254, 0, -461 };
				ChaoSpawn = true;
			}
			else
			{
				pos = { -278.8718262, 80, -499.0888367 };
				ChaoSpawn = true;
			}
		}
		else
		{
			ChaoSpawn = false;
		}
		break;
	default:
		ChaoSpawn = false;
		return ChaoSpawn;
		break;
	}

	return ChaoSpawn;

	//position for each levels
}


void Chao_OnFrame() {
	if (ChaoCryDelay > 0)
		ChaoCryDelay--;

	bool ChaoSpawnAllowed = isChaoAllowedtoSpawn(CurrentLevel, CurrentAct);

	if (!ChaoSpawnAllowed && ChaoObject != nullptr)
	{
		DeleteObject_(ChaoObject); //Fix wrong chao spawn act
		DeleteObject_(ChaoTP);
		DeleteObject_(chaoHint);
		ChaoSpawn = false;
	}

	if (ChaoSpawnAllowed && !ChaoObject && GameState == 15 && CurrentMission == 1 && CurrentLevel < 15) {
		ChaoObject = LoadObject((LoadObj)(LoadObj_Data1), 1, ChaoObj_Main);

		ChaoObject->Data1->Position = pos;
		ChaoObject->Data1->Rotation.y = Yrot;
	}

	return;
}
