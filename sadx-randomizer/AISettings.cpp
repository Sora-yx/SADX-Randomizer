#include "stdafx.h"
#include "ActsSettings.h"
#include "RandomHelpers.h"
#include "CharactersSettings.h"
#include "Trampoline.h"
#include <fstream>

extern bool isAIAllowed;
extern int CurrentAI;
bool isAIActive = false;
extern bool CreditCheck;

bool isIADeleted;
int FlagAI = 0;
extern bool Race;
int AICopy = 0;
int AISwap = 0;
int CharaSwap = 0;
extern int SwapDelay;
extern int TikalRand;
extern int EggmanRand;

//This is where all the AI is managed: Rand, loading and bug fixes. //Using a part of Charsel mod by MainMemory, otherwise that wouldn't be possible.


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




int CheckTailsAI_R(void) {

	if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Gamma)
		return 0;

		if (CurrentLevel == LevelIDs_RedMountain && CurrentAct == 1)
		{
			std::ofstream FunnyAI("AICheck.txt");
			FunnyAI << "return 0 RM act 2 crash";
			FunnyAI << "\n";
			FunnyAI.close();
			isAIActive = false;
			return 0;
		}


	std::ofstream FunnyAI("AICheck.txt");
	if (CurrentLevel > 25)
	{
		FunnyAI << "return 0 Level trop élevé";
		FunnyAI << "\n";
		FunnyAI << "Level numéro:";
		FunnyAI << CurrentLevel;
		FunnyAI << "\n";
		FunnyAI.close();
		isAIActive = false;
		return 0;
	}
	else
	{
		if (CurrentLevel == LevelIDs_HotShelter && CurrentAct == 0 || CurrentLevel == LevelIDs_EmeraldCoast && CurrentAct == 1 && CurrentCharacter == Characters_Tails)
		{
			isAIActive = false;
			return 0;
		}

		if (CurrentLevel == LevelIDs_Casinopolis && CurrentAct == 0 && CurrentCharacter == Characters_Knuckles)
		{
			isAIActive = false;
			return 0; //crash cutscene fix
		}

		if (CurrentLevel == LevelIDs_EggViper || CurrentLevel == LevelIDs_Chaos2 && CurrentCharacter == Characters_Knuckles || CurrentLevel == LevelIDs_PerfectChaos || CurrentLevel == LevelIDs_SpeedHighway && CurrentAct == 1)
		{
			FunnyAI << "return 0 Level imcompatible (egg viper, perfect chaos...)";
			FunnyAI << "\n";
			FunnyAI << "Level numéro:";
			FunnyAI << CurrentLevel;
			FunnyAI << "\n";
			FunnyAI.close();
			isAIActive = false;
			return 0;
		}

		if (CurrentLevel == LevelIDs_Chaos6 && (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Knuckles || CurrentCharacter == Characters_Sonic))
		{
			isAIActive = false;
			return 0;
		}

	}

	//Header
	FunnyAI << "return 1, hey it's working!;";
	FunnyAI << "\n";
	FunnyAI << "Level numéro:";
	FunnyAI << CurrentLevel; 
	FunnyAI << "\n";
	FunnyAI.close(); 
	isAIActive = true;
	return 1;

}


ObjectMaster* Load2PTails_r(ObjectMaster* player1)
{

	if (!isAIAllowed)
		FlagAI = CheckTailsAI(); //Check Tails AI if not random AI 
	else
		FlagAI = CheckTailsAI_R(); 

	if (FlagAI != 1)
	{
		isAIActive = false;
		return (ObjectMaster*)0x0;

	}
	else
	{

		if (CurrentLevel != AICopy) //Avoid randing a new AI if player restart or change act.
		{
			do {
				if (isAIAllowed)
					CurrentAI = AIArray[rand() % 6];
				else
					if (CurrentCharacter == Characters_Sonic)
						CurrentAI = Characters_Tails; //don't rand and just call tails AI 

			} while (CurrentCharacter == CurrentAI);
		}
			
		
		ObjectMaster* v1 = LoadObject(LoadObj_Data1, 0, TailsAI_Main); //load AI moveset (basically?) 
		TailsAI_ptr = v1;

		if (v1)
		{
			AICopy = CurrentLevel;
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



//teleport AI to Player 

void moveAItoPlayer() {

	if (isAIAllowed)
	
	{
		ObjectMaster* play1 = GetCharacterObject(0);
		ObjectMaster* play2 = GetCharacterObject(1);

		play2->Data1->Position.x = play1->Data1->Position.x - 7;
		play2->Data1->Position.y = play1->Data1->Position.y;
		play2->Data1->Position.z = play1->Data1->Position.z + 5;
		play2->Data1->Rotation.y = play1->Data1->Rotation.y;

		play2->Data1->Action = 1; 
	}

}


//SFX characters ai fixes.

void FixAISFXSonic() {

	if (CurrentAI == Characters_Sonic || CharaSwap == Characters_Sonic)
		return;
	else
		PlaySound(0x2fa, 0, 0, 0);

}

void FixAISFXJump() {

	if (CurrentAI == Characters_Knuckles || CurrentAI == Characters_Tails || CurrentAI == Characters_Amy)
		return;
	else
		PlaySound(0x11, 0, 0, 0);
}

void FixAISFXKnuckles() {

	if (CurrentAI == Characters_Knuckles || CharaSwap == Characters_Knuckles)
		return;
	else
		PlaySound(0x317, 0, 0, 0);

}

void FixAISFXKnuckles2() {

	if (CurrentAI == Characters_Knuckles || CharaSwap == Characters_Knuckles)
		return;
	else
		PlaySound(0x30c, 0, 0, 0);

}

void FixAISFXAmy() {
	if (CurrentAI == Characters_Amy || CharaSwap == Characters_Amy)
		return;
	else
		PlaySound(0x31d, 0, 0, 0);
}

void FixAISFXAmy2() {
	if (CurrentAI == Characters_Amy || CharaSwap == Characters_Amy)
		return;
	else
		PlaySound(0x4ff, 0, 0, 0);
}


void FixAISFXAmy3() {
	if (CurrentAI == Characters_Amy || CharaSwap == Characters_Amy)
		return;
	else
		PlaySound(0x500, 0, 0, 0);
}

void FixAISFXAmy4() {
	if (CurrentAI == Characters_Amy || CharaSwap == Characters_Amy)
		return;
	else
	PlaySound(0x506, 0, 0, 0);
}

void FixAISFXGamma() {

	if (CurrentAI == Characters_Gamma)
		return;
	else
		PlaySound(0x519, 0, 0, 0);
}

void FixAISFXGamma2() {

	if (CurrentAI == Characters_Gamma)
		return;
	else
		PlaySound(0x33c, 0, 0, 0);

}

void FixAISFXGamma3() {

	if (CurrentAI == Characters_Gamma)
		return;
	else
		PlaySound(0x33b, 0, 0, 0);

}

void FixAISFXGamma4() {
	if (CurrentAI == Characters_Gamma)
		return;
	else
		if (MetalSonicFlag == 0)
		{
			PlaySound(0x21, 0, 0, 0);
		}
		else
			PlaySound(0x30a, 0, 0, 0);
		
}

void FixAISFXGamma5() {
	if (CurrentAI == Characters_Gamma)
		return;
	else
		PlaySound(0x33f, 0, 0, 0);
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
		if (CurrentLevel < 15 || CurrentLevel > 35)
			Load_DelayedSound_Voice(4010);
		else
			Load_DelayedSound_Voice(4011);

		SoundManager_Delete2();
		break;

	}

}

CollisionInfo* oldcol = nullptr;

FunctionPointer(void, sub_43FA90, (EntityData1* a1, CharObj2** a2, CharObj2* a3), 0x43FA90);



void __cdecl CheckDeleteAnimThing(EntityData1* a1, CharObj2** a2, CharObj2* a3)
{
	for (int i = 0; i < 8; i++)
		if (EntityData1Ptrs[i] && EntityData1Ptrs[i] != a1 && EntityData1Ptrs[i]->CharID == a1->CharID)
			return;
	sub_43FA90(a1, a2, a3);
}



void AISwitch() {

	if (SonicRand == 0 && isAIActive) //don't allow the swap if metal sonic or super sonic.
	{
		//initialize swap, taking actual character and ai information

		if (CurrentCharacter <= 5 && CurrentAI <= 5 && CurrentLevel != 15)
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

			switch (obj->Data1->CharID)
			{
			case Characters_Sonic:
				PlayVoice(4000);
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

	SetFrameRateMode(1, 1);
	
	
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
		
		if (!Race && !isAIAllowed)
		{
			ObjectMaster* obj;
			obj = GetCharacterObject(0);
			ObjectMaster* lastobj = obj;
			ObjectMaster* o2 = nullptr;
			o2 = Load2PTails_r(obj);
		}

	}

	std::ofstream FunnyAI("AICheck.txt");
	FunnyAI << "didn't call the AI LUL";
	FunnyAI << "\n";
	FunnyAI.close();
	isAIActive = false;
	return;
	
}

