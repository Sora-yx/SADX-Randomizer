#include "stdafx.h"
#include "data\chao.h"
#include "RandomHelpers.h"
#include "CharactersSettings.h"
#include "Trampoline.h"
#include <fstream>
#include <iostream> 

ObjectMaster* ChaoObject;
ObjectMaster* CurrentChao;
ObjectMaster* chaoHint;

short ChaoCryDelay = 0;
static bool pvploaded = false;
extern int chaoPB;
bool ChaoSpawn = false;
extern bool CasinoTails;

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

	CheckThingButThenDeleteObject(a1);
	ChaoTP = nullptr;
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

void ChaoObj_Delete(ObjectMaster* a1) {
	if (a1->Child) {
		DeleteObjectMaster(a1->Child);
		a1->Child = nullptr;
	}

	if (a1->Data1->LoopData) {
		delete a1->Data1->LoopData;
		a1->Data1->LoopData = nullptr;
	}

	Chao_DeleteFiles();
}


void __cdecl ChaoObj_Main(ObjectMaster* a1) {


	switch (a1->Data1->Action) {
		case ChaoAction_Init:
		{
			if (!CurrentLandTable)
				return;
			//Load the chao textures
			Chao_LoadFiles();
	
			a1->DisplaySub = a1->MainSub;
			a1->DeleteSub = ChaoObj_Delete; //When you quit a level
			a1->Data1->Action = 1; //Wait a frame before loading the chao
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
			a1->Data1->Action = 2;

		}
		break;
		case ChaoAction_Hit:
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
	
			if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 2)
				return;
	
			int HitBox = 0;
	
			if (GetCharacter0ID() == Characters_Big || GetCharacter0ID() == Characters_Gamma)
				HitBox = 20;
			else
				HitBox = 9;
	
			if (TimeThing != 0 && IsPlayerInsideSphere(&a1->Data1->Position, HitBox))
			{
				ObjectMaster* P1 = GetCharacterObject(0);
				EntityData1* ent;
				ent = P1->Data1;
				P1->Data1->Rotation.y = -ChaoObject->Data1->Rotation.y + 0x4000;
				P1->Data1->Position.x += 1;
				ent->InvulnerableTime = 0;
				if (!SonicRand && !MetalSonicFlag)
					P1->Data1->Action = 0; //fix potential crash
				P1->Data1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);
	
				if (++ent->InvulnerableTime == 1) //wait 1 frame before loading level result
				{
					if (!SonicRand && !MetalSonicFlag)
						P1->Data1->Action = 1; //fix victory pos
					Chao_SetBehavior(a1->Child, (long*)Chao_Pleasure(a1->Child)); //Move to Happy animation
					a1->Child->Data1->Rotation.y = -P1->Data1->Rotation.y + 0x4000;
					LoadLevelResults_r();
					chaoPB++;
					a1->Data1->InvulnerableTime = 0;
					a1->Data1->Action = 3;
				}
			}
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


LostChaoPosition ChaoLevelPosition[22]{

	{ SonicVersion, LevelAndActIDs_EmeraldCoast2, 3857.76, 597.395, -2896.18, 0x8000 },
	{ BigVersion, LevelAndActIDs_EmeraldCoast3, 6388, 0.8, 1116, 0x8000 },
	{ SonicVersion, LevelAndActIDs_WindyValley3, 4162.019, -4484, -1800, 0x8000 },
	{ SonicVersion, LevelAndActIDs_Casinopolis1, 361, 380, -40, 0x8000 },
	{ TailsVersion, LevelAndActIDs_Casinopolis2, -1565.96, -2205, 2654.24, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap2, 1480.62, 573.3, -256.67, 0x8000 },
	{ BigVersion, LevelAndActIDs_IceCap4, 1790.85, 371.968811, 11.265, 0x8000 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, 520, 1330, 1630, 0x8000 }, //Sonic Version
	{ BigVersion, LevelAndActIDs_TwinklePark2, 604, 338, 237, 0x8000 }, //Big Version
	{ AmyVersion, LevelAndActIDs_TwinklePark3, -41.43054199, 50, 290.7596436, 0x0 }, //Amy Version
	{ SonicVersion,LevelAndActIDs_SpeedHighway1, 4455, -385.135, 2930.18, 0x8000 },
	{ SonicVersion, LevelAndActIDs_RedMountain1, -3861.85, 883.96, -2974.81, 0x8000 },
	{ SonicVersion, LevelAndActIDs_SkyDeck2, -316.7368469, 38.99000168, -687.1625977, 0x8000 },
	{ SonicVersion, LevelAndActIDs_LostWorld2, 7410, -1965, 1316, 0x8000 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, 2945.652344, 5589.605469, -2211.165039, -1.681558157E-44 + 0x4000 },
	{ GammaVersion, LevelAndActIDs_FinalEgg3, 1939, -3174.049561, -128, 0x8000 }, //Gamma Version
	{ SonicVersion, LevelAndActIDs_FinalEgg3, 1480.62, 573.3, -256.67, 0x8000 }, //Sonic Version
	{ BigVersion, LevelAndActIDs_HotShelter1, -278.8718262, 80, -499.0888367, 0x8000 }, //Big Version 
	{ AmyVersion, LevelAndActIDs_HotShelter2, 716.4085693, 677.8605957, -2952.347412, -1.681558157E-44 + 0xC000 }, //Amy version SADX VANILLA
	{ GammaVersion, LevelAndActIDs_HotShelter3, 2.01, 3222, -3136, 0x8000 },
};


bool SetAndGetLostChaoPosition() {

	HMODULE DCModChao = GetModuleHandle(L"DCMods_Main");
	uint16_t levelact = (((short)CurrentLevel) << 8) | CurrentAct;

		for (int i = 0; i < LengthOfArray(ChaoLevelPosition); i++) {
			if (levelact == ChaoLevelPosition[i].LevelID && CurrentStageVersion == ChaoLevelPosition[i].version)
			{
				pos = ChaoLevelPosition[i].Position;
				Yrot = ChaoLevelPosition[i].YRot;
				ChaoSpawnAllowed = true;
				ChaoSpawn = true;
				if (CurrentLevel == LevelIDs_HotShelter && DCModChao && CurrentStageVersion == AmyVersion) //Dreamcast Mod exception as the landtable is different.
					pos = { 716.4085693, 428.2105103, -2952.347412 };
				return true;
			}
		}
	
	ChaoSpawnAllowed = false;
	ChaoSpawn = false;
	return false;
}



void Chao_OnFrame() {
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

