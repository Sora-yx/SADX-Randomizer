#include "stdafx.h"

std::shared_ptr<ModelInfo> MysticMelody;
std::shared_ptr<ModelInfo> MMPlatform;
bool MMPlatformEnabled = false;


void PlatformMM_Display(ObjectMaster* obj) {

	if (!MissedFrames && (MMPlatformEnabled || obj->Data1->Scale.x == 15)) {
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

		if (data->Action == 0) 
		{
			obj->DisplaySub = PlatformMM_Display;
			obj->DeleteSub = DynCol_Delete;
			data->Object = MMPlatform->getmodel();
		}

		if (MMPlatformEnabled) 
		{
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
	case LevelIDs_EmeraldCoast:
		if (CurrentAct == 2)
			return false;
		break;
	}


	return true;
}

bool Check_ObjectMysticMelody() {

	switch (CurrentLevel)
	{
	case LevelIDs_EmeraldCoast:
		if (CurrentAct == 2)
			return true;
		break;
	case LevelIDs_RedMountain:
		if (CurrentAct == 1)
			return true;
		break;
	case LevelIDs_SpeedHighway:
		if (CurrentAct == 2)
			return true;
		break;
	case LevelIDs_FinalEgg:
		if (CurrentAct == 0)
			return true;
		break;
	}

	return false;
}


void MysticMelody_Display(ObjectMaster* obj)
{
	if (!MissedFrames) {
		njSetTexture(&SA2_OBJ_TEXLIST);
		njPushMatrix(0);
		njTranslateV(0, &obj->Data1->Position);
		njRotateY(nullptr, obj->Data1->Rotation.y);
		DrawObject(obj->Data1->Object);
		njPopMatrix(1u);
	}
}

bool warped = false;
static int timerWarp = 0;
void warpedOnFrames()
{
	if (warped && ++timerWarp == 80)
	{
		for (uint8_t i = 0; i < PMax; i++)
		{
			if (playertwp[i] && IsIngame())
			{
				CharColliOn(playertwp[i]);
			}

			warped = false;
			timerWarp = 0;
		}
	}
}

void MysticMelody_Main(ObjectMaster* obj) 
{
	if (!ClipSetObject(obj))
	{

		if (!playertwp[0] || !playerpwp[0])
			return;

		EntityData1* data = obj->Data1;
		EntityData1* player = EntityData1Ptrs[0];
		int curAction = EntityData1Ptrs[0]->Action;
		unsigned char getChar = EntityData1Ptrs[0]->CharID;
		int size = 25;
		uint8_t pnum = 0;

		switch (data->Action)
		{
		case 0:
		{

			obj->DisplaySub = MysticMelody_Display;
			obj->DeleteSub = DynCol_Delete;
			data->Object = MysticMelody->getmodel();
			data->Position.y -= 7;
			data->Action++;
		}
		break;
		case 1:
		{


			if (IsPlayerInsideSphere(&obj->Data1->Position, 160)) 
			{
				data->InvulnerableTime = 0;
				data->Index = 0;

				if (getChar >= Characters_Gamma)
					size = 35;

				if (Check_TikalMessageDisplay())
					DisplayHintText(TikalLostChao_message, 110);

				data->Action++;
			}
		}
		break;
		case 2:
		{
			if (IsPlayerInsideSphere(&data->Position, 80)) {
				SwapDelay = 0;
			}

			pnum = IsPlayerInsideSphere(&obj->Data1->Position, size) - 1;
			if (IsPlayerInsideSphere(&obj->Data1->Position, size) && (EntityData1Ptrs[pnum]->Status & (Status_Ground | Status_OnColli))) {

				SwapDelay = 0;

				if (!isAIActive)
					Hud_ShowActionButton();

				if (ControllerPointers[pnum]->PressedButtons & Buttons_Y)
				{
					SwapDelay = 0;
					DisableControl();
					for (uint8_t i = 0; i < PMax; i++)
					{
						if (playertwp[i])
						{
							playertwp[i]->flag &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);
							playerpwp[i]->spd = { 0, 0, 0 };
						}
					}
			
					if ((CharObj2Ptrs[pnum]->Upgrades & Upgrades_SuperSonic) == 0)
						ForcePlayerToWhistle();

					PlayDelayedCustomSound(CommonSound_MysticMelody, 1, 2);
					data->Index = 0;
					data->Action++;
				}
			}
		}
		break;
		case 3:
			if (++data->Index == 120)
			{
				EnableControl();
				if (CurrentLevel == LevelIDs_HotShelter && CurrentCharacter == Characters_Gamma && CurrentAct == 0 && CurrentStageVersion == BigVersion) {
					warped = true;
					DisablePlayersCol();
					for (uint8_t i = 0; i < PMax; i++)
					{
						if (playertwp[i])
							PositionPlayer(i, 640.168, 150.123, -435.403 + i);
					}
					
					PlayDelayedCustomSound(CommonSound_MM_Warp, 10, 1);
					data->Action = 2;
				}
				else
				{

					if (CurrentMission == Mission3_LostChao)
						data->Action = 4;
					else
						data->Action = 1;
				}
			}
			break;
		case 4:
			NJS_VECTOR CurPos = SetPlayerAroundLostChaoPosition();
			if (CurPos.x != -1 && CurPos.y != -1 && CurPos.z != -1)
			{
				MMPlatformEnabled = Check_ObjectMysticMelody(); //Does the player need platform after the teleportation?
				if (++data->InvulnerableTime == 5)
				{
					CheckAndAddColLandTable();
					PlayDelayedCustomSound(CommonSound_MM_Warp, 10, 1);
					data->Action = 5;
				}
			}
			else
			{
				PlayDelayedCustomSound(CommonSound_MM_Platform, 1, 2);
				MMPlatformEnabled = true;
				data->Action = 2;
			}
			break;
		case 5:
			data->Action = 1;
	
			DisablePlayersCol();

			for (uint8_t i = 0; i < PMax; i++)
			{
				if (playertwp[i])
				{
					playertwp[i]->pos = SetPlayerAroundLostChaoPosition();
				}
			}

			warped = true;
			break;
		}

		DynColRadius(obj, 100, 1);
		obj->DisplaySub(obj);
	}
}

void LoadMysticMelody_Models() {

	MysticMelody = LoadBasicModel("MysticMelody");
	MMPlatform = LoadBasicModel("MM-Platform");
}