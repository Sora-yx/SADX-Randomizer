#include "stdafx.h"

D3DMATRIX WorldMatrixBackup;

// Object model file functions

inline ModelInfo* LoadMDL(const char* type, const char* name) {
	std::string fullPath = "system\\";
	fullPath = fullPath + type + "\\" + name + ".sa1mdl";

	ModelInfo* temp = new ModelInfo(help.GetReplaceablePath(fullPath.c_str()));

	if (temp->getformat() == ModelFormat_Invalid) {
		delete temp;
		fullPath = "system\\";
		fullPath = fullPath + type + "\\" + name + ".cnkmdl";

		temp = new ModelInfo(help.GetReplaceablePath(fullPath.c_str()));

		if (temp->getformat() == ModelFormat_Invalid) {
			PrintDebug("Failed.\n");
			delete temp;
			return nullptr;
		}
		else {
			PrintDebug("Done.\n");
			return temp;
		}
	}
	else {
		PrintDebug("Done.\n");
		return temp;
	}
}

ModelInfo* LoadObjectModel(const char* name) {
	PrintDebug("[SHM] Loading object model: %s... ", name);
	return LoadMDL("models", name);
}

void LoadModelListFuncPtr(const char** names, int count, ModelInfo** mdls, ModelInfo* (*func)(const char*)) {
	for (int i = 0; i < count; ++i) {
		mdls[i] = func(names[i]);
	}
}

void FreeMDL(ModelInfo* pointer) {
	PrintDebug("[SHM] Freeing model: %s... \n", pointer->getdescription().c_str());
	delete(pointer);
}


// Free a list of files

void FreeMDLFiles(ModelInfo** Files, int size) {
	PrintDebug("[SHM] Freeing %s models... \n", std::to_string(size).c_str());

	for (int i = 0; i < size; ++i) {
		FreeMDL(Files[i]);
		Files[i] = nullptr;
	}

	PrintDebug("Done. \n");
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

void displaySub_ZYX(ObjectMaster* obj) {
	if (!MissedFrames) {
		njSetTexture(&SA2_OBJ_TEXLIST);
		njPushMatrix(0);
		njTranslateV(0, &obj->Data1->Position);
		njRotateZYX(nullptr, obj->Data1->Rotation.x, obj->Data1->Rotation.y, obj->Data1->Rotation.z);
		njDrawModel_SADX(obj->Data1->Object->basicdxmodel);
		njPopMatrix(1u);
	}
}

void displaySub_Multi(ObjectMaster* obj) {
	if (!MissedFrames) {
		njSetTexture(&SA2_OBJ_TEXLIST);
		njPushMatrix(0);
		njTranslateV(0, &obj->Data1->Position);
		njRotateZYX(nullptr, obj->Data1->Rotation.x, obj->Data1->Rotation.y, obj->Data1->Rotation.z);
		DrawObject(obj->Data1->Object);
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

// Load a simple sadx object with children
void LoadBasicObjectMulti(ObjectMaster* obj, NJS_OBJECT* model) {
	obj->MainSub = mainSub_Global;
	obj->DisplaySub = displaySub_Multi;
	obj->Data1->Object = model;
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

// Load Dyncol Objects



// Sphere check functions


NJS_VECTOR GetPathPosition(NJS_VECTOR* orig, NJS_VECTOR* dest, float state) {
	NJS_VECTOR result;
	result.x = (dest->x - orig->x) * state + orig->x;
	result.y = (dest->y - orig->y) * state + orig->y;
	result.z = (dest->z - orig->z) * state + orig->z;

	return result;
}

Rotation3 fPositionToRotation(NJS_VECTOR* orig, NJS_VECTOR* point) {
	NJS_VECTOR dist = *point;
	Rotation3 result;

	njSubVector(&dist, orig);

	result.x = atan2(dist.y, dist.z) * 65536.0 * -0.1591549762031479;
	result.y = -(atan2(dist.x, dist.z) * 65536.0 * 0.1591549762031479) + 0x4000;

	return result;
}

float GetGroundPositionEntity(EntityData1* data, bool rot) {
	WriteData<5>((void*)0x49F201, 0x90);
	WriteData<5>((void*)0x49F1C0, 0x90);
	WriteData<5>((void*)0x49F43D, 0x90);

	struct_a3 dyncolinfo;

	data->Position.y += 20;
	RunEntityIntersections(data, &dyncolinfo);
	data->Position.y -= 20;

	WriteCall((void*)0x49F201, SpawnRipples);
	WriteCall((void*)0x49F1C0, SpawnSplashParticles);
	WriteCall((void*)0x49F43D, (ObjectFuncPtr)0x49F0B0); //DrawCharacterShadow

	if (dyncolinfo.ColFlagsB & ColFlags_Solid) {
		if (dyncolinfo.DistanceMax > -1000000) {
			if (rot == true) {
				data->Rotation = { dyncolinfo.ShadowRotationX, data->Rotation.y, dyncolinfo.ShadowRotationY };
			}

			return dyncolinfo.DistanceMax;
		}
	}

	return -1000000;
}

NJS_VECTOR UnitMatrix_GetPoint(NJS_VECTOR* orig, Rotation3* rot, float x, float y, float z) {
	NJS_VECTOR point;

	njPushMatrix(_nj_unit_matrix_);
	njTranslateV(0, orig);
	if (rot) njRotateXYZ(0, rot->x, rot->y, rot->z);
	njTranslate(0, x, y, z);
	njGetTranslation(_nj_current_matrix_ptr_, &point);
	njPopMatrix(1u);

	return point;
}

// Ninja stuff




void SetupWorldMatrix()
{
	ProjectToWorldSpace();
	WorldMatrixBackup = WorldMatrix;
	Direct3D_SetWorldTransform();
	memcpy(_nj_current_matrix_ptr_, &ViewMatrix, sizeof(NJS_MATRIX));
}

void njTranslateX(float f) {
	njTranslate(nullptr, f, 0, 0);
}

void njTranslateY(float f) {
	njTranslate(nullptr, 0, f, 0);
}

void njTranslateZ(float f) {
	njTranslate(nullptr, 0, 0, f);
}

void njRotateZXY(Rotation3* rot) {
	njRotateZ(0, rot->z);
	njRotateX(0, rot->x);
	njRotateY(0, rot->y);
}

void njScaleX(float f) {
	njScale(nullptr, f, 1, 1);
}

void njScaleY(float f) {
	njScale(nullptr, 1, f, 1);
}

void njScaleZ(float f) {
	njScale(nullptr, 1, 1, f);
}