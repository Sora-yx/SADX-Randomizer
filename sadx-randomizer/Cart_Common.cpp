#include "stdafx.h"
#include "RandomHelpers.h"
#include "StageSettings.h"

ObjectMaster* CurrentCart = nullptr;

void Load_Cart_R() {
	ObjectMaster* play1 = GetCharacterObject(0);

	if (CurrentLevel == LevelIDs_TwinkleCircuit)
		return;

	if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		if (CurrentCharacter <= Characters_Tails)
			return;

	Delete_Cart();
	if (!CurrentCart)
	{
		SwapDelay = 0;
		FlagAutoPilotCart = 0; //fix that bullshit Twinkle Circuit thing.
		LoadPVM("OBJ_SHAREOBJ", &OBJ_SHAREOBJ_TEXLIST);
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


void Delete_Cart()
{

	if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2 && GameState == 15)
			ForcePlayerAction(0, 0x18);

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0)
		return;

	FlagAutoPilotCart = 1;

	if (CurrentCart != nullptr)
		CheckThingButThenDeleteObject(CurrentCart);
	else
		return;

	ObjectMaster* P1 = GetCharacterObject(0);
	if (P1 != nullptr)
	{
		P1->Data1->InvulnerableTime = 0;
		if (++P1->Data1->InvulnerableTime == 1 && P1->Data1->Action >= 42) //wait 1 frame before removing the cart, this fix Knuckles Action.
			ForcePlayerAction(0, 28);
	}

	CurrentCart = nullptr;
}

void FixRestart_Stuff() //Prevent the game to crash if you restart while being in a custom cart, also reset other stuff.
{
	DisableTimeThing();
	DisableControl();

	ObjectMaster* P1 = GetCharacterObject(0);

	FlagAutoPilotCart = 0;
	CurrentCart = nullptr;

	if (P1 != nullptr)
		CharObj2Ptrs[0]->Powerups &= Powerups_Invincibility;

	DeleteTriggerObject();
	//CheckThingButThenDeleteObject(ChaoTP);
	Delete_Cart();

	return;
}


int AmyCartImprovement() {
	if (CurrentCharacter == Characters_Amy) //trick the game to make it think we are playing Sonic.
		return Characters_Sonic;
	else
		return CurrentCharacter;
}