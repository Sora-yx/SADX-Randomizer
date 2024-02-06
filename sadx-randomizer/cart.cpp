#include "stdafx.h"

task* CurrentCart[PMax] = { nullptr };
Trampoline* LevelItem_Delete_t;
OBJ_CONDITION cartData = { 1, 0, -32767, 0, 0, 4000100.00f };

int AmyCartImprovement()
{
	if (CurrentCharacter == Characters_Amy) //trick the game to make it think we are playing Sonic.
		return Characters_Sonic;
	else
		return CurrentCharacter;
}

void Delete_Cart_r(task* obj)
{
	ObjectFunc(origin, LevelItem_Delete_t->Target());

	for (uint8_t i = 0; i < PMax; i++)
	{
		auto tp = CurrentCart[i];
		if (tp)
		{
			if (obj == tp)
			{
				FreeTask(tp);
				CurrentCart[i] = nullptr;
			}
		}
	}

	FlagAutoPilotCart = 0;
	origin((ObjectMaster*)obj);
}

void DeleteCartAndExitPlayer() {

	FlagAutoPilotCart = 0;
	for (uint8_t i = 0; i < PMax; i++)
	{
		if (playertwp[i])
		{
			auto tp = CurrentCart[i];
			if (tp)
			{
				tp->twp->mode = 3;
				RemovePlayerFromObject(i, 0.0f, 0.5f, 0.0f);
				FreeTask(tp);
				CurrentCart[i] = nullptr;
			}
		}

	}
	CameraReleasEvent();
}

void LoadRemoveCart(ObjectMaster* obj) {

	EntityData1* P1 = EntityData1Ptrs[0];
	EntityData1* data = obj->Data1;

	if (!P1 || CurrentCharacter <= Characters_Tails)
		return;

	if (data->Action == 0) {

		if (CurrentLevel == LevelIDs_SandHill) {
			if (P1->Position.z <= -15150) {
				DeleteCartAndExitPlayer();
				CheckThingButThenDeleteObject(obj);
			}
		}
	}
}

void LoadRemoveCartIceCap() {

	EntityData1* P1 = EntityData1Ptrs[0];

	if (!P1)
		return;

	if (P1->CharID == Characters_Sonic || P1->CharID == Characters_Tails) {
		ForcePlayerAction(0, 0x18);
		return;
	}

	DeleteCartAndExitPlayer();
	return;
}


void Load_Cart_R()
{

	if (CurrentLevel == LevelIDs_TwinkleCircuit)
		return;

	Float dist = 8.0f;
	for (uint8_t i = 0; i < PMax; i++)
	{
		ObjectMaster* play = GetCharacterObject(i);

		if (!play)
			continue;

		if (!isMPMod() || MPPlayers < 2)
		{
			if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
			{

				if (play->Data1->CharID <= Characters_Tails)
				{
					continue;
				}
				else
				{
					SetCameraMode_(0);
				}
			}
		}

		if (!CurrentCart[i])
		{
			SwapDelay = 0;
			CurrentCart[i] = CreateElementalTask(15, 3, (TaskFuncPtr)Cart_Main);
		}

		if (CurrentCart[i])
		{
			cartData.pTask = CurrentCart[i];
			CurrentCart[i]->ocp = &cartData;
			auto twp = CurrentCart[i]->twp;
			twp->scl.y = 1; //Cart will spawn empty.
			twp->scl.z = 0;

			switch (play->Data1->CharID) //Set Color and Size depending on character
			{
			case Characters_Gamma:
				twp->scl.x = 3;
				twp->scl.z = 2;
				break;
			case Characters_Big:
				twp->scl.x = GreenColor;
				twp->scl.z = 1;
				break;
			case Characters_Tails:
				twp->scl.x = OrangeColor;
				break;
			case Characters_Knuckles:
				twp->scl.x = RedColor;
				break;
			case Characters_Amy:
				twp->scl.x = PurpleColor;
				break;
			default:
				twp->scl.x = BlueColor;
				break;
			}

			switch (CurrentLevel)
			{
			case LevelIDs_SandHill:
				twp->pos = play->Data1->Position;
				twp->ang.y = 30300;
				break;
			default:
				twp->pos = play->Data1->Position;
				break;
			}

			CurrentCart[i]->twp->pos.x += dist;
			CurrentCart[i]->dest = (TaskFuncPtr)LevelItem_Delete; //TEST


			dist += 10.0f;
		}
	}
}

void init_CartStuff()
{

	WriteCall((void*)0x79ab84, AmyCartImprovement);
	WriteCall((void*)0x79aa78, AmyCartImprovement);
	WriteCall((void*)0x7979b9, AmyCartImprovement);

	LevelItem_Delete_t = new Trampoline((int)LevelItem_Delete, (int)LevelItem_Delete + 0x5, Delete_Cart_r);
}