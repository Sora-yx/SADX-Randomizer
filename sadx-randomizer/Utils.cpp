#include "stdafx.h"


short ConvertLevelActsIDtoLevel(short level) {

	return level >> 8;
}

short ConvertLevelActsIDtoAct(short act) {

	return act & 0xf;
}

__int16 CurCharacter() {

	ObjectMaster* P1 = GetCharacterObject(0);
	if (P1 != nullptr)
		return P1->Data1->CharID;

	return 0;
}


bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius) {
	return GetDistance(center, pos) <= radius;
}

int IsPlayerInsideSphere_(NJS_VECTOR* center, float radius) {
	for (uint8_t player = 0; player < 8; ++player) {
		if (!EntityData1Ptrs[player]) continue;

		NJS_VECTOR* pos = &EntityData1Ptrs[player]->Position;
		if (IsPointInsideSphere(center, pos, radius)) {
			return player + 1;
		}
	}

	return 0;
}

bool IsSpecificPlayerInSphere(NJS_VECTOR* center, float radius, uint8_t player) {
	return IsPlayerInsideSphere_(center, radius) == player + 1;
}


bool isValueInArray(int* array, int value, int size)
{
	for (int i = 0; i < size; i++) {
		if (array[i] == value)
			return true;
	}

	return false;
}

void ForcePlayerToWhistle() {

	int id = 0;

	switch (CurCharacter()) {
	case Characters_Sonic:
		id = 0x854A01;
		break;
	case Characters_Tails:
		id = 8864257;
		break;
	case Characters_Knuckles:
		id = 7485441;
		break;
	case Characters_Amy:
		id = 5518337;
		break;
	case Characters_Gamma:
		id = 5913089;
		break;
	case Characters_Big:
		id = 6829569;
		break;
	}

	EntityData1* ed1 = EntityData1Ptrs[0];
	EntityData2* ed2 = EntityData2Ptrs[0];
	CharObj2* co2 = CharObj2Ptrs[0];

	if (!ed1)
		return;

	if (ed1->Action < 1)
		return;

	int curLevel = CurrentLevel;
	CurrentLevel = LevelIDs_SSGarden;
	PerformWhistle(ed1, ed2, co2, id);
	CurrentLevel = curLevel;
}


int GetCharacter0ID() //player 1 ID
{
	return GetCharacterID(0);
}

int GetCharacter1ID() //AI ID
{
	return GetCharacterID(1);
}


bool isBossStage(short stage_id)
{
	return stage_id >= LevelIDs_Chaos0 && stage_id <= LevelIDs_E101R;
}


void FlashScreen(ObjectMaster* obj) {

	EntityData1* data = obj->Data1;

	if (++data->InvulnerableTime > 80) {

		int color = 0x00000000;
		ScreenFade_Color = *(NJS_COLOR*)&color;
		CheckThingButThenDeleteObject(obj);
	}
	else {
		int color = 0xFFFFFFFF;
		ScreenFade_Color = *(NJS_COLOR*)&color;

		if (data->InvulnerableTime < 120) {
			if (data->InvulnerableTime < 60) {
				data->CharID += 4;
				ScreenFade_Color.argb.a = data->CharID;
			}
			else {
				ScreenFade_Color.argb.a = 0xFF;
			}
		}
		else {
			data->CharID -= 20;
			ScreenFade_Color.argb.a = data->CharID;
		}

		ScreenFade_DrawColor();
	}
}

bool isSA2Mod() {
	HMODULE Mod = GetModuleHandle(L"sadx-sa2-mod");
	if (Mod)
		return true;

	return false;
}

bool isDCMod() {
	HMODULE DCMod = GetModuleHandle(L"DCMods_Main");
	if (DCMod)
		return true;

	return false;
}

bool isRandoLevel() {
	for (int i = 0; i < LengthOfArray(RandoStageArray); i++)
	{
		int level = ConvertLevelActsIDtoLevel(RandoStageArray[i].levelAndActs);

		if (level == CurrentLevel)
			return true;
	}

	return false;
}

// Object model file functions

ModelInfo* LoadBasicModel(const char* name) {
	PrintDebug("[SADX Randomizer] Loading basic model: %s... ", name);

	std::string fullPath = "system\\models\\";
	fullPath = fullPath + name + ".sa1mdl";

	ModelInfo* mdl = new ModelInfo(help.GetReplaceablePath(fullPath.c_str()));

	if (mdl->getformat() != ModelFormat_Basic) {
		PrintDebug("Failed!\n");
		delete mdl;
		return nullptr;
	}

	PrintDebug("Done.\n");
	return mdl;
}

void FreeMDL(ModelInfo* pointer) {
	if (pointer) {
		PrintDebug("[SHM] Freeing model: %s... \n", pointer->getdescription().c_str());
		delete(pointer);
		pointer = nullptr;
	}
}
// Global display subs

void displaySub_Global(ObjectMaster* obj) {
	if (!MissedFrames) {
		njSetTexture(&SA2_OBJ_TEXLIST);
		njPushMatrix(0);
		njTranslateV(0, &obj->Data1->Position);
		njRotateXYZ(nullptr, obj->Data1->Rotation.x, obj->Data1->Rotation.y, obj->Data1->Rotation.z);
		njDrawModel_SADX(obj->Data1->Object->basicdxmodel);
		njPopMatrix(1u);
	}
}


// Global mainsubs

void mainSub_Global(ObjectMaster* obj) {
	if (!ClipSetObject(obj)) {
		obj->DisplaySub(obj);
	}
}

void mainSub_CollisionGlobal(ObjectMaster* obj) {
	if (!ClipSetObject(obj)) {
		AddToCollisionList(obj->Data1);
		obj->DisplaySub(obj);
	}
}

// SADX Simple object definitions

inline void LoadBasicObject_Set(ObjectMaster* obj, NJS_OBJECT* model) {
	obj->Data1->Object = model;
	obj->DisplaySub = displaySub_Global;
}

// Load a simple sadx object
void LoadBasicObject(ObjectMaster* obj, NJS_OBJECT* model) {
	obj->MainSub = mainSub_Global;
	LoadBasicObject_Set(obj, model);
}

// Load a simple sadx object with one model and one collision
void LoadBasicObject(ObjectMaster* obj, NJS_OBJECT* model, CollisionData* col) {
	obj->MainSub = mainSub_CollisionGlobal;
	Collision_Init(obj, col, 1, 4);
	LoadBasicObject_Set(obj, model);
}


// Dyncol stuff

/*	Add complex/dynamic collisions to an object, limited to 255 collisions at a time
	Delete itself if the global delete sub is used	*/
void DynCol_Add(ObjectMaster* obj, uint8_t col) {
	/*	0 is static
	1 is moving (refresh the colision every frame)
	2 is static, scalable
	3 is moving, scalable	*/

	EntityData1* original = obj->Data1;
	NJS_OBJECT* colobject;

	colobject = ObjectArray_GetFreeObject(); //The collision is a separate object, we add it to the list of object

	//if scalable
	if (col == 2 || col == 3) {
		colobject->scl[0] = original->Scale.x;
		colobject->scl[1] = original->Scale.y;
		colobject->scl[2] = original->Scale.z;
	}
	else {
		colobject->scl[0] = 1.0;
		colobject->scl[1] = 1.0;
		colobject->scl[2] = 1.0;
	}

	//add the rest
	colobject->ang[0] = original->Rotation.x;
	colobject->ang[1] = original->Rotation.y;
	colobject->ang[2] = original->Rotation.z;
	colobject->pos[0] = original->Position.x;
	colobject->pos[1] = original->Position.y;
	colobject->pos[2] = original->Position.z;

	colobject->basicdxmodel = obj->Data1->Object->basicdxmodel; //object it will use as a collision
	obj->Data1->LoopData = (Loop*)colobject; //pointer to the collision object into our original object

	if (col == 0 || col == 2) DynamicCOL_Add(ColFlags_Solid, obj, colobject); //Solid
	else if (col == 1 || col == 3) DynamicCOL_Add((ColFlags)0x8000000, obj, colobject); //Dynamic, solid
	else if (col == 4) DynamicCOL_Add((ColFlags)0x8000001, obj, colobject);
	else if (col == 5) DynamicCOL_Add(ColFlags_Water, obj, colobject);
	else if (col == 6) DynamicCOL_Add((ColFlags)(0x8000000 | ColFlags_Solid | ColFlags_Hurt), obj, colobject);
}

// Only allocate dynamic collision within radius
bool DynColRadius(ObjectMaster* obj, float radius, uint8_t col) {
	if (IsPlayerInsideSphere(&obj->Data1->Position, radius)) {
		if (!obj->Data1->LoopData) {
			DynCol_Add(obj, col);
			return 2;
		}
		return true;
	}
	else {
		DynCol_Delete(obj);
	}

	return false;
}

bool DynColRadiusAuto(ObjectMaster* obj, uint8_t col) {
	//Use the model radius
	return DynColRadius(obj, obj->Data1->Object->basicdxmodel->r + 50, col);
}

// Update Dyncol data
void DynCol_Update(EntityData1* data, uint8_t type) {
	NJS_OBJECT* col = (NJS_OBJECT*)data->LoopData;

	if (col) {
		switch (type) {
		case 0:
		posy:
			col->pos[1] = data->Position.y;
			break;
		case 1:
		posxyz:
			col->pos[0] = data->Position.x;
			col->pos[1] = data->Position.y;
			col->pos[2] = data->Position.z;
			break;
		case 2:
			col->ang[1] = data->Rotation.y;
			goto posy;
		case 3:
			col->ang[0] = data->Rotation.x;
			col->ang[1] = data->Rotation.y;
			col->ang[2] = data->Rotation.z;
			goto posy;
		case 4:
			col->ang[0] = data->Rotation.x;
			col->ang[1] = data->Rotation.y;
			col->ang[2] = data->Rotation.z;
			goto posxyz;
		}
	}
}

// Clean dynamic collisions
void DynCol_Delete(ObjectMaster* obj) {
	if (obj->Data1->LoopData)
	{
		DynamicCOL_Remove(obj, (NJS_OBJECT*)obj->Data1->LoopData);
		ObjectArray_Remove((NJS_OBJECT*)obj->Data1->LoopData);
		obj->Data1->LoopData = nullptr;
	}
}


void TeleportPlayerResultScreen(NJS_VECTOR pos, int yRot) {

	if (CurrentMission == Mission3_LostChao) 
	{
		if (CurrentLevel == LevelIDs_HotShelter && CurrentStageVersion == AmyVersion && isDCMod() && CurrentAct == 1) 
		{
			pos = { 734.767, 428.211, -2954.12 };
			yRot = 0xC0;
		}
	}


	for (uint8_t j = 0; j < 8; j++) 
	{
		if (playertwp[j]) 
		{
			if (CurrentMission != Mission3_LostChao)
			{
				CharColliOff(playertwp[j]);
				warped = true;
			}
		
			playertwp[j]->pos = pos;
			playertwp[j]->ang.y = yRot;

			if (j > 0) {
				playertwp[j]->pos.x += 5;
				playertwp[j]->pos.z += 5;
			}
		}
	}
}

struct colLevelStruct 
{
	int currentLevel;
	int currentAct;
};

colLevelStruct levelCol[]{
	{ LevelIDs_SpeedHighway, 0 },
	{ LevelIDs_TwinklePark, 1 },
	{ LevelIDs_SkyDeck, 2 },
	{ LevelIDs_IceCap, 0 },
};

void AddColOnLand() {
	for (int i = 0; i < CurrentLandTable->COLCount; i++) 
	{
		if (CurrentLandTable->Col[i].Flags & ColFlags_Visible) {
			CurrentLandTable->Col[i].Flags |= (int)(ColFlags_Solid);
		}
	}
}

void CheckAndAddColLandTable() {

	for (int j = 0; j < LengthOfArray(levelCol); j++)
	{
		if (CurrentLevel == levelCol[j].currentLevel && CurrentAct == levelCol[j].currentAct) {
			AddColOnLand();
			break;
		}
	}
	return;
}

//Delete gamma shot on target
void Remove_TargetCursor(ObjectMaster* obj) {

	EntityData1* data = obj->Data1;

	if (data) {
		if (data->Status & Status_Hurt) 
		{
			E102KillCursor((task*)obj);
		}
	}
}

//Allow gamma to target object
void Check_AllocateObjectData2(ObjectMaster* obj, EntityData1* data1)
{
	if (!obj || !data1)
		return;

	//if one of the player is gamma, init the target thing
	for (int i = 0; i < 8; i++) {

		if (!EntityData1Ptrs[i])
			continue;

		if (EntityData1Ptrs[i]->CharID == Characters_Gamma)
		{
			if (!data1->Action)
			{
				AllocateObjectData2(obj, data1);
				ObjectData2_SetStartPosition(obj->Data1, (ObjectData2*)obj->Data2);
			}

			Remove_TargetCursor(obj);
		}
	}
}

int checkIfFileExists(const char* filename)
{
	FILE* file;
	errno_t err;

	if ((err = fopen_s(&file, filename, "r")) != 0)
	{
		return 0;
	} 
	else {
		fclose(file);
		return 1;
	}
}