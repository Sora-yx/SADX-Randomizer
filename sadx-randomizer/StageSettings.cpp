#include "stdafx.h"
#include <fstream>

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


void Stages_Management() {
	WriteCall((void*)0x4169e1, FixRestart_Stuff); //Delete Cart properly after a game over.
	WriteCall((void*)0x41676b, FixRestart_Stuff); 
}

