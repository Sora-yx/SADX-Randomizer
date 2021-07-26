#include "stdafx.h"
#include "objects.h"

NJS_TEXNAME SA2_OBJ_TEXNAMES[43];
NJS_TEXLIST SA2_OBJ_TEXLIST = { arrayptrandlength(SA2_OBJ_TEXNAMES) };
PVMEntry SA2_OBJ_PVM = { "common-obj", &SA2_OBJ_TEXLIST };
PVMEntry FroggyTex = { "big_kaeru", &big_kaeru_TEXLIST };


void CheckAndLoadTriggerObject() {

	if (!CharObj2Ptrs[0])
		return;

	if (CurrentLevel == LevelIDs_SandHill || CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		LoadObject((LoadObj)2, 1, LoadRemoveCart);

	HotShelterSecretSwitch();
}

void Load_ObjectsCommon() {

	LoadMysticMelody_Models();

	if (CurrentMission == Mission2_100Rings || CurrentStageVersion == KnucklesVersion && CurrentCharacter != Characters_Knuckles)
		LoadObject((LoadObj)2, 1, MissionResultCheck);
}

//Create an object so Gamma can hit some specific bosses.
CollisionData col = { 0, 0, 0x77, 0, 0x800400,  { 6.0, 6.0, 6.0}, 0, 0 };

void TargetableEntity(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1;

	if (data->Action == 0) {
		AllocateObjectData2(obj, obj->Data1);

		//if the scale is specified, temporary set the collision scale to it.
		if (data->Scale.x) {
			Collision_Init(obj, &col, 1, 2u);
		}
		else {
			Collision_Init(obj, &col, 1, 2u);
		}

		data->Action = 1;
	}
	else {
		ObjectMaster* boss = (ObjectMaster*)obj->Data1->LoopData;

		if (CurrentLevel == LevelIDs_Zero && boss->Data1->Action == 9)
			return;

		if (!boss || !boss->Data1) {
			CheckThingButThenDeleteObject(obj);
			return;
		}

		if (EntityData1Ptrs[0]->CharID != Characters_Gamma)
			return;

		data->Position = boss->Data1->Position;
		data->Position.y += 10;


		if (OhNoImDead(obj->Data1, (ObjectData2*)obj->Data2))
		{
			CheckThingButThenDeleteObject(obj);

			//if it is set, don't reload the target object
			if (data->CharID == 1)
				return;

			ObjectMaster* target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
			target->Data1->LoopData = (Loop*)boss;
		}
		else
		{
			AddToCollisionList(data);
		}
	}
}


void ObjectCommons_Init() {

	Set_BackRing();
	Set_ZeroChase();
	init_CartStuff();

	help.RegisterCommonObjectPVM(SA2_OBJ_PVM);	
	help.RegisterCommonObjectPVM(FroggyTex);
}