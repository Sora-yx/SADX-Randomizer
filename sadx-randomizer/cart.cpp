#include "stdafx.h"

ObjectMaster* CurrentCart = nullptr;
Trampoline* LevelItem_Delete_t;

int AmyCartImprovement() {
	if (CurrentCharacter == Characters_Amy) //trick the game to make it think we are playing Sonic.
		return Characters_Sonic;
	else
		return CurrentCharacter;
}


void Delete_Cart_r(ObjectMaster* obj)
{

	ObjectFunc(origin, LevelItem_Delete_t->Target());

	if (obj->MainSub == Cart_Main && CurrentLevel != LevelIDs_TwinklePark && CurrentLevel != LevelIDs_TwinkleCircuit) {

		FlagAutoPilotCart = 1;

		if (CurrentCart != nullptr)
			UpdateSetDataAndDelete(CurrentCart);
		else
			return;

		CurrentCart = nullptr;
	}

	origin(obj);
}


FunctionPointer(void, RemovePlayerFromObject, (unsigned __int8 playerID, float speedX, float speedY, float speedZ), 0x441820);
VoidFunc(CameraReleasEvent, 0x436140);

void DeleteCartAndExitPlayer() {

	FlagAutoPilotCart = 1;
	if (CurrentCart != nullptr)
		UpdateSetDataAndDelete(CurrentCart);
	else {
		return;
	}
	CurrentCart = nullptr;
	RemovePlayerFromObject(0, 0.0, 2.0, 2.0);
	CameraReleasEvent();
}

void LoadRemoveCart(ObjectMaster* obj) {

	EntityData1* P1 = EntityData1Ptrs[0];
	EntityData1* data = obj->Data1;
	ObjectMaster* cart = nullptr;

	if (!P1 || CurrentCharacter <= Characters_Tails)
		return;

	if (data->Action == 0) {
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2) {

			DeleteCartAndExitPlayer();
			data->Action++;
		}
		if (CurrentLevel == LevelIDs_SandHill) {
			if (P1->Position.z <= -15150) {
				DeleteCartAndExitPlayer();
				data->Action++;
			}
		}
	}
}



void Load_Cart_R() {

	ObjectMaster* play1 = GetCharacterObject(0);

	if (CurrentLevel == LevelIDs_TwinkleCircuit)
		return;

	if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2) {

		if (CurrentCharacter <= Characters_Tails)
			return;
	}


	if (!CurrentCart)
	{
		SwapDelay = 0;
		FlagAutoPilotCart = 0; //fix that bullshit Twinkle Circuit thing.
		CurrentCart = LoadObject((LoadObj)(15), 3, Cart_Main);
	}

	if (CurrentCart)
	{
		CurrentCart->Data1->Scale.y = 1; //Cart will spawn empty.

		switch (CurrentCharacter) //Set Color and Size depending on character
		{
		case Characters_Gamma:
			CurrentCart->Data1->Scale.x = 3;
			CurrentCart->Data1->Scale.z = 2;
			break;
		case Characters_Big:
			CurrentCart->Data1->Scale.x = GreenColor;
			CurrentCart->Data1->Scale.z = 1;
			break;
		case Characters_Tails:
			CurrentCart->Data1->Scale.x = OrangeColor;
			CurrentCart->Data1->Scale.z = 0;
			break;
		case Characters_Knuckles:
			CurrentCart->Data1->Scale.x = RedColor;
			CurrentCart->Data1->Scale.z = 0;
			break;
		case Characters_Amy:
			CurrentCart->Data1->Scale.x = PurpleColor;
			CurrentCart->Data1->Scale.z = 0;
			break;
		default:
			CurrentCart->Data1->Scale.x = BlueColor;
			CurrentCart->Data1->Scale.z = 0;
			break;
		}

		switch (CurrentLevel)
		{
		case LevelIDs_SandHill:
			CurrentCart->Data1->Position = play1->Data1->Position;
			CurrentCart->Data1->Rotation.y = 30300;
			break;
		default:
			CurrentCart->Data1->Position = play1->Data1->Position;
			break;
		}

		CurrentCart->field_30 = 59731468;
		CurrentCart->Data1->Unknown = 10;
		CurrentCart->DeleteSub = LevelItem_Delete; //TEST

		//SetData is not initialized even if it's in the list, so we need to manually assign the cart to it.
		SETObjData* cartSETData = new SETObjData();
		CurrentCart->SETData.SETData = cartSETData;

		//Set the data used in Twinkle Park/Twinkle Circuit (should fixes bug hopefully.)
		CurrentCart->SETData.SETData->LoadCount = 1;
		CurrentCart->SETData.SETData->f1 = 0;
		CurrentCart->SETData.SETData->Flags - 32767;
		CurrentCart->SETData.SETData->Distance = 4000100.00;

		SETEntry* cartSETEntry = new SETEntry();
		CurrentCart->SETData.SETData->SETEntry = cartSETEntry;

		CurrentCart->SETData.SETData->SETEntry->ObjectType = 15;
		CurrentCart->SETData.SETData->SETEntry->YRotation = -9841;
		CurrentCart->SETData.SETData->SETEntry->Properties.x = 1.00000000;
		CurrentCart->SETData.SETData->SETEntry->Properties.y = 1.00000000;
		CurrentCart->SETData.SETData->SETEntry->Properties.z = 0.000000000;
	}
}

void init_CartStuff() {

	WriteCall((void*)0x79ab84, AmyCartImprovement);
	WriteCall((void*)0x79aa78, AmyCartImprovement);
	WriteCall((void*)0x7979b9, AmyCartImprovement);

	LevelItem_Delete_t = new Trampoline((int)LevelItem_Delete, (int)LevelItem_Delete + 0x5, Delete_Cart_r);
}