#include "stdafx.h"

NJS_TEXNAME SA2_OBJ_TEXNAMES[41];
NJS_TEXLIST SA2_OBJ_TEXLIST = { arrayptrandlength(SA2_OBJ_TEXNAMES) };

ObjectMaster* CurrentCart = nullptr;
ModelInfo* MysticMelody;
ModelInfo* MMPlatform;
bool MMPlatformEnabled = false;

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

	njReleaseTexture(&OBJ_SHAREOBJ_TEXLIST);
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
	Delete_Cart();

	return;
}


int AmyCartImprovement() {
	if (CurrentCharacter == Characters_Amy) //trick the game to make it think we are playing Sonic.
		return Characters_Sonic;
	else
		return CurrentCharacter;
}

void PlatformMM_Display(ObjectMaster* obj) {

	if (!MissedFrames && MMPlatformEnabled) {
		njSetTexture(&SA2_OBJ_TEXLIST);
		njPushMatrix(0);
		njTranslateV(0, &obj->Data1->Position);
		njRotateY(nullptr, obj->Data1->Rotation.y);
		DrawObject(obj->Data1->Object);
		njPopMatrix(1u);
	}
}

void PlatformMM_Main(ObjectMaster* obj) {
	if (!ClipSetObject(obj)) {
		EntityData1* data = obj->Data1;

		if (data->Action == 0) {
			obj->DisplaySub = PlatformMM_Display;
			obj->DeleteSub = DynCol_Delete;
			data->Object = MMPlatform->getmodel();
		}

		if (MMPlatformEnabled) {
			DynColRadius(obj, 100, 1);
			obj->DisplaySub(obj);
		}
	}
}


const char* const TikalLostChao_message[] = {
	"	The Lost Chao you are looking for\nis close around. \n",
	NULL,
};

bool Check_TikalMessageDisplay() {

	if (CurrentMission != Mission3_LostChao || !isChaoHintEnabled)
		return false;

	switch (CurrentLevel)
	{
	case LevelIDs_FinalEgg:
		if (CurrentAct == 2 && CurrentStageVersion == SonicVersion)
			return true;
		break;
	case LevelIDs_HotShelter:
		if (CurrentAct == 2)
			return true;
		break;
	case LevelIDs_RedMountain:
		return true;
		break;
	}


	return false;
}

void Check_ObjectMysticMelody() {

	switch (CurrentLevel)
	{
	case LevelIDs_EmeraldCoast:
		if (CurrentAct == 2)
			MMPlatformEnabled = true;
		break;
	case LevelIDs_RedMountain:
		if (CurrentAct == 1)
			MMPlatformEnabled = true;
		break;
	case LevelIDs_SpeedHighway:
		if (CurrentAct == 2)
			MMPlatformEnabled = true;
		break;
	}

	return;
}


void MysticMelody_Display(ObjectMaster* obj) {
	if (!MissedFrames) {
		njSetTexture(&SA2_OBJ_TEXLIST);
		njPushMatrix(0);
		njTranslateV(0, &obj->Data1->Position);
		njRotateY(nullptr, obj->Data1->Rotation.y);
		DrawObject(obj->Data1->Object);
		njPopMatrix(1u);
	}
}

void MysticMelody_Main(ObjectMaster* obj) {
	if (!ClipSetObject(obj)) {
		EntityData1* data = obj->Data1;
		int curAction = EntityData1Ptrs[0]->Action;
		unsigned char getChar = EntityData1Ptrs[0]->CharID;
		int size = 25;

		switch (data->Action)
		{
			case 0:
			{
				obj->DisplaySub = MysticMelody_Display;
				obj->DeleteSub = DynCol_Delete;
				data->Object = MysticMelody->getmodel();
				data->Position.y -= 7;
				data->Action = 1;
			}
			break;
			case 1:
			{
				if (IsPlayerInsideSphere(&obj->Data1->Position, 160)) {
					if (getChar >= Characters_Gamma)
						size = 35;
					if (Check_TikalMessageDisplay())
						DisplayHintText(TikalLostChao_message, 110);
					data->Action = 2;
				}
			}
			break;
			case 2:
			{
		
					if (IsPlayerInsideSphere(&obj->Data1->Position, size) && (curAction == 1 || curAction == 2  || SonicRand == 1 && curAction > 74 && curAction <= 76)) {
						Hud_ShowActionButton();

						if (ControllerPointers[0]->PressedButtons & Buttons_Y)
						{
							DisableControl();
							EntityData1Ptrs[0]->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);
							CharObj2Ptrs[0]->Speed = { 0, 0, 0 };

							ForcePlayerToWhistle();

							PlayDelayedCustomSound(CommonSound_MysticMelody, 1, 2);
							data->Action = 3;
						}
					}
			}
			break;
			case 3:
				if (++obj->Data1->Index == 120) {
					
					if (obj->Data1->Scale.x == 3 && CurrentLevel == LevelIDs_EmeraldCoast && CurrentAct == 2)
					{
						PlayDelayedCustomSound(CommonSound_MM_Warp, 10, 1);
						PositionPlayer(0, 6153.64, 760.9485, 2379.39);
						data->Action = 6;
						return;
					}
						EnableControl();
						if (CurrentMission == Mission3_LostChao)
							data->Action = 4;
						else
							data->Action = 6;
				}
			break;
			case 4:
				NJS_VECTOR CurPos = SetPlayerAroundLostChaoPosition();
				if (CurPos.x != -1 && CurPos.y != -1 && CurPos.z != -1)
				{
					Check_ObjectMysticMelody(); //Does the player need platform after the teleportation?
					
					if (++obj->Data1->InvulnerableTime == 5)
					{
						PlayDelayedCustomSound(CommonSound_MM_Warp, 10, 1);
						data->Action = 5;
					}
				}
				else
				{
					PlayDelayedCustomSound(CommonSound_MM_Platform, 1, 2);
					MMPlatformEnabled = true;
					data->Action = 6;
				}
			break;
			case 5:	
				EntityData1Ptrs[0]->Position = SetPlayerAroundLostChaoPosition();
				data->Action = 6;
			break;
		}
	
		DynColRadius(obj, 100, 1);
		obj->DisplaySub(obj);
	}
}

		

void LoadTriggerObject() {

	if (CurrentLevel == LevelIDs_HotShelter && CurrentAct == 0)
		HotShelterSecretSwitch();

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 2 && CurrentMission == Mission3_LostChao)
		LoadChaoTPTrigger();

	if (CurrentLevel == LevelIDs_SandHill && CurrentCharacter > Characters_Tails)
		LoadRemoveCart();
}

void Load_ObjectsCommon() {

	if (CurrentLevel > 0 && CurrentLevel < 15)
	{
		MysticMelody = LoadObjectModel("MysticMelody");
		MMPlatform = LoadObjectModel("MM-Platform");
	}
}

void DeleteTriggerObject() {

	TriggerOBJHS_Delete();
	TriggerCasinoChao_Delete();
}

void Delete_ObjectsCommon() {

	if (CurrentLevel > 0 && CurrentLevel < 15)
	{
		if (MysticMelody != nullptr)
			FreeMDL(MysticMelody);

		if (MMPlatform != nullptr)
			FreeMDL(MMPlatform);
	}
}