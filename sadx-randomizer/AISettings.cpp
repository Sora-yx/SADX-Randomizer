#include "stdafx.h"
#include "ActsSettings.h"
#include "RandomHelpers.h"
#include "CharactersSettings.h"
#include "Trampoline.h"
#include <fstream>

extern bool isAIAllowed;
int CurrentAI = 0;
bool isAIActive = false;
extern bool CreditCheck;

bool isIADeleted;
int FlagAI = 0;
extern bool Race;
int AISwap = 0;
int CharaSwap = 0;
extern int SwapDelay;
int AICount;
extern int CustomLayout;
extern int levelCount;


//This is where all the AI is managed: loading and bug fixes. //Using a part of Charsel mod by MainMemory, otherwise that wouldn't be possible.


ObjectFuncPtr charfuncs[] = { 
	Sonic_Main,
	Eggman_Main,
	Tails_Main,
	Knuckles_Main,
	Tikal_Main,
	Amy_Main,
	Gamma_Main,
	Big_Main
};

ObjectMaster* LoadCharObj(int i)
{
	//setup AI correctly
	ObjectMaster* obj = LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[CurrentAI]);
	obj->Data1->CharID = CurrentAI;
	obj->Data1->CharIndex = (char)1;
	EntityData1Ptrs[1] = (EntityData1*)obj->Data1;
	EntityData2Ptrs[1] = (EntityData2*)obj->Data2;
	return obj;
}




int CheckTailsAI_R(void) { //restriction and bug fixes.

	if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Sonic && MetalSonicFlag != 0 || CurrentCharacter == Characters_Knuckles)
	{
		isAIActive = false;
		return 0;
	}

	if (CurrentCharacter == CurrentAI)
		return 0;

	if (CurrentLevel > 25 && CurrentLevel < 38)
	{
		isAIActive = false;
		return 0;
	}

	if (Race)
	{
		isAIActive = false;
		return 0;
	}


	switch (CurrentLevel)
	{
		case LevelIDs_SpeedHighway:
			if (CurrentAct == 1)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_FinalEgg:
			if (CurrentCharacter == Characters_Amy && CurrentAct == 0)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_RedMountain:
			if (CurrentAct == 1 && CurrentCharacter < 4)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_Casinopolis:
			if (CurrentAct >= 1 || CurrentAct == 0 && CurrentCharacter == Characters_Knuckles)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_HotShelter:
			if (CurrentAct == 0)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_EmeraldCoast:
			if (CurrentAct == 1 && CurrentCharacter == Characters_Tails)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_Chaos0:
			if (CurrentCharacter == Characters_Sonic)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_Chaos2:
			if (CurrentCharacter == Characters_Knuckles)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_Chaos6:
			if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Knuckles || CurrentCharacter == Characters_Sonic)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_PerfectChaos:
		{
			isAIActive = false;
			return 0;
		}
		break;
		case LevelIDs_EggViper:
		{
			isAIActive = false;
			return 0;
		}
		break;
		case LevelIDs_TwinklePark:
		{
			isAIActive = false;
			return 0;
		}
		break;
		case LevelIDs_LostWorld:
		{
			if (CurrentAct == 2 && CurrentCharacter == Characters_Sonic)
			{
				isAIActive = false;
				return 0;
			}
		}
		case LevelIDs_SkyDeck:
		{
			if (CurrentAct == 2 && CurrentCharacter == Characters_Knuckles)
			{
				isAIActive = false;
				return 0;
			}
		}
		break;
		case LevelIDs_SandHill:
		{
			if (CurrentCharacter == Characters_Tails)
			{
				isAIActive = false;
				return 0;
			}
		}
		break;
	}


	isAIActive = true;
	return 1;

}


ObjectMaster* Load2PTails_r(ObjectMaster* player1) //Custom AI
{

	FlagAI = CheckTailsAI_R(); 

	if (FlagAI != 1)
	{
		isAIActive = false;
		return (ObjectMaster*)0x0;
	}
	else
	{

		ObjectMaster* v1 = LoadObject(LoadObj_Data1, 0, TailsAI_Main); //load AI moveset (basically?) 
		TailsAI_ptr = v1;

		if (v1)
		{
			
			v1->Data1->CharID = (char)CurrentAI;
			v1->Data1->CharIndex = 1;
			v1->DeleteSub = TailsAI_Delete;

			ObjectMaster* v3 = LoadCharObj(1); //load AI 

			v3->Data1->Position.x = v1->Data1->Position.x - njCos(v1->Data1->Rotation.y) * 30;
			v3->Data1->Position.y = v1->Data1->Position.y;
			v3->Data1->Position.z = v1->Data1->Position.z - njSin(v1->Data1->Rotation.y) * 30;
			v3->Data1->Action = 0;
			dword_3B2A304 = 0;

			return v3;
		}
	}

	return (ObjectMaster*)0x0;
}
//}

ObjectMaster* Load2PTails_Original(ObjectMaster* player1) //Original AI (Tails only)
{

		FlagAI = CheckTailsAI_R();

	if (FlagAI != 1)
	{
		isAIActive = false;
		return (ObjectMaster*)0x0;
	}
	else
	{
		if (CurrentCharacter == Characters_Sonic)
		{
			CurrentAI = Characters_Tails; //don't rand and just call tails AI 


			ObjectMaster* v1 = LoadObject(LoadObj_Data1, 0, TailsAI_Main); //load AI moveset (basically?) 
			TailsAI_ptr = v1;

			if (v1)
			{
				v1->Data1->CharID = (char)CurrentAI;
				v1->Data1->CharIndex = 1;
				v1->DeleteSub = TailsAI_Delete;

				ObjectMaster* v3 = LoadCharObj(1); //load AI 

				v3->Data1->Position.x = v1->Data1->Position.x - njCos(v1->Data1->Rotation.y) * 30;
				v3->Data1->Position.y = v1->Data1->Position.y;
				v3->Data1->Position.z = v1->Data1->Position.z - njSin(v1->Data1->Rotation.y) * 30;
				v3->Data1->Action = 0;
				dword_3B2A304 = 0;

				return v3;
			}
		}
	}

	return (ObjectMaster*)0x0;
}
		

//SFX characters ai fixes.

void FixAISFXSonic() {

	if (isAIActive)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;
		if (GetChara->Data1->CharID == Characters_Sonic && isAIActive)
			return;
	}

		PlaySound(0x2fa, 0, 0, 0);
		return;

}

void FixAISFXJump() {

	if (isAIActive)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara->Data1->CharID == Characters_Knuckles || GetChara->Data1->CharID == Characters_Tails || GetChara->Data1->CharID == Characters_Amy)
			return;
	}
		PlaySound(0x11, 0, 0, 0);
		return;
}


void FixAISFXAmy() {
	if (isAIActive)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara->Data1->CharID == Characters_Amy)
			return;
	}

		PlaySound(0x31d, 0, 0, 0);
}

void FixAISFXAmy2() {
	if (isAIActive)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara->Data1->CharID == Characters_Amy)
			return;
	}

		PlaySound(0x4ff, 0, 0, 0);
}


void FixAISFXAmy3() {

	if (isAIActive)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara->Data1->CharID == Characters_Amy)
			return;
	}

		PlaySound(0x500, 0, 0, 0);
}

void FixAISFXAmy4() {
	if (isAIActive)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara->Data1->CharID == Characters_Amy)
			return;
	}

	PlaySound(0x506, 0, 0, 0);
}

void FixAISFXAmy5() {
	if (isAIActive)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara->Data1->CharID == Characters_Amy)
			return;
	}

		PlaySound(0x31c, 0, 0, 0);
}




//Result Voice FIX
void ResultVoiceFix() {

	ObjectMaster* GetChara = GetCharacterObject(0);
	GetChara->Data1->CharID;
	
	switch (GetChara->Data1->CharID)
	{
	case Characters_Sonic:
		if (MetalSonicFlag == 0) {
			if ((short)CurrentLevel < 0xf) {
				Load_DelayedSound_SFX(0x5d7);
			}
			else {
				Load_DelayedSound_SFX(0x5da);
			}
		}
		else {
			PlayVoice(0x7fc);
		}
		break;
	case Characters_Eggman:
		Load_DelayedSound_Voice(4012);
		break;
	case Characters_Tails:
		Load_DelayedSound_SFX(0x5b2);
		break;
	case Characters_Knuckles:
		if (CurrentLevel < 15)
			Load_DelayedSound_SFX(0x5a5);
		else
			Load_DelayedSound_SFX(0x5a8);
		break;
	case Characters_Amy:
		Load_DelayedSound_SFX(0x56c);
	case Characters_Gamma:
		Load_DelayedSound_SFX(0x591);
		break;
	case Characters_Big:
		if (CurrentLevel < 15 || CurrentLevel > 35 && CustomLayout < 2)
			Load_DelayedSound_Voice(4010);
		else
			Load_DelayedSound_Voice(4011);

		SoundManager_Delete2();
		break;
	}

}

FunctionPointer(void, sub_43FA90, (EntityData1* a1, CharObj2** a2, CharObj2* a3), 0x43FA90);
void __cdecl CheckDeleteAnimThing(EntityData1* a1, CharObj2** a2, CharObj2* a3)
{
	for (int i = 0; i < 8; i++)
		if (EntityData1Ptrs[i] && EntityData1Ptrs[i] != a1 && EntityData1Ptrs[i]->CharID == a1->CharID)
			return;
	sub_43FA90(a1, a2, a3);
}



CollisionInfo* oldcol = nullptr;


void AISwitch() {

	if (!isAIAllowed)
		return;

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0 || CurrentLevel == LevelIDs_EggWalker)
		return;

	if (CurrentAI == Characters_Tikal || CurrentAI == Characters_Eggman)
		if (CurrentLevel > 14 && CurrentLevel < 26)
			return;
		
	if (SonicRand == 0 && isAIActive && CurrentLevel != 15) //don't allow the swap if metal sonic / super sonic or if Chaos 0 fight (crash.)
	{
		
		//initialize swap, taking actual character and ai information

		if (CurrentCharacter <= 5 && CurrentAI <= 5)
		{
			AISwap = GetCharacter0ID();
			CharaSwap = GetCharacter1ID();


			ObjectMaster* obj = GetCharacterObject(0);
			CharObj2* obj2 = ((EntityData2*)obj->Data2)->CharacterData;


			obj->DeleteSub(obj);
			short powerups = obj2->Powerups;
			short jumptime = obj2->JumpTime;
			short underwatertime = obj2->UnderwaterTime;
			float loopdist = obj2->LoopDist;
			NJS_VECTOR speed = obj2->Speed;
			ObjectMaster* heldobj = obj2->ObjectHeld;

			//Display Character swap.
			obj->MainSub = charfuncs[CharaSwap];
			obj->Data1->CharID = (char)CharaSwap;

			//Play voice switch
			switch (obj->Data1->CharID)
			{
			case Characters_Sonic:
				if (MetalSonicFlag == 0)
					PlayVoice(4000);
				break;
			case Characters_Eggman:
				PlayVoice(4005);
				break;
			case Characters_Tails:
				PlayVoice(4001);
				break;
			case Characters_Knuckles:
				PlayVoice(4002);
				break;
			case Characters_Amy:
				PlayVoice(4003);
				break;
			}

			obj->Data1->Action = 0;
			obj->Data1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);
			if (!oldcol)
			{
				oldcol = obj->Data1->CollisionInfo;
				obj->Data1->CollisionInfo = nullptr;
			}
			else
				Collision_Free(obj);
			obj->MainSub(obj);
			obj2 = ((EntityData2*)obj->Data2)->CharacterData;
			obj2->Powerups = powerups;
			obj2->JumpTime = jumptime;
			obj2->UnderwaterTime = underwatertime;
			obj2->LoopDist = loopdist;
			obj2->Speed = speed;
			obj2->ObjectHeld = heldobj;


			//initialize swap, taking AI information
			ObjectMaster* AI = GetCharacterObject(1);
			CharObj2* AI2 = ((EntityData2*)obj->Data2)->CharacterData;

			short AIpowerups = AI2->Powerups;
			short AIjumptime = AI2->JumpTime;
			short AIunderwatertime = AI2->UnderwaterTime;
			float AIloopdist = AI2->LoopDist;
			NJS_VECTOR AIspeed = AI2->Speed;
			ObjectMaster* AIheldobj = AI2->ObjectHeld;

			//Display AI swap.
			AI->MainSub = charfuncs[AISwap];
			AI->Data1->CharID = (char)AISwap;
			AI->Data1->Action = 0;
			AI->Data1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);
			if (!oldcol)
			{
				oldcol = AI->Data1->CollisionInfo;
				AI->Data1->CollisionInfo = nullptr;
			}
			else
				Collision_Free(AI);
			AI->MainSub(AI);
			AI2 = ((EntityData2*)AI->Data2)->CharacterData;
			AI2->Powerups = powerups;
			AI2->JumpTime = jumptime;
			AI2->UnderwaterTime = underwatertime;
			AI2->LoopDist = loopdist;
			AI2->Speed = speed;
			AI2->ObjectHeld = heldobj;

			SwapDelay = 0;

		}

	}
}

	

//Load AI

void LoadTails_AI_R() {

	//SetFrameRateMode(1, 1);
	
	
	if (CreditCheck != true)
	{
		if (Race == false && isAIAllowed)
		{
				ObjectMaster* obj;
				obj = GetCharacterObject(0);
				ObjectMaster* lastobj = obj;
				ObjectMaster* o2 = nullptr;
				o2 = Load2PTails_r(obj);
		}
		else
		{
			if (Race == false && isAIAllowed == false)
			{
				ObjectMaster* obj;
				obj = GetCharacterObject(0);
				ObjectMaster* lastobj = obj;
				ObjectMaster* o2 = nullptr;
				o2 = Load2PTails_r(obj);
			}
		}

	}

	return;
	
}

void LoadTails_AI_Original() {


	if (CreditCheck != true)
	{
		if (!Race && !isAIAllowed)
		{
			ObjectMaster* obj;
			obj = GetCharacterObject(0);
			ObjectMaster* lastobj = obj;
			ObjectMaster* o2 = nullptr;
			o2 = Load2PTails_Original(obj);
		}

	}

	return;

}

