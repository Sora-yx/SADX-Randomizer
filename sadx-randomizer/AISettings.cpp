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
	obj->Data1->CharID = 1;
	obj->Data1->CharIndex = (char)1;
	EntityData1Ptrs[1] = (EntityData1*)obj->Data1;
	EntityData2Ptrs[1] = (EntityData2*)obj->Data2;
	return obj;
}




int CheckTailsAI_R(void) {


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

				CurrentAI = AIArray[rand() % 8];

			} while (CurrentCharacter == CurrentAI || CurrentAI == Characters_Big);
		}
			
		
		ObjectMaster* v1 = LoadObject(LoadObj_Data1, 0, TailsAI_Main); //load AI moveset (basically?) 
		TailsAI_ptr = v1;

		if (v1)
		{
			AICopy = CurrentLevel;
			v1->Data1->CharID = CurrentAI;
			v1->Data1->CharIndex = 1;
			v1->DeleteSub = TailsAI_Delete;

			ObjectMaster* v3 = LoadCharObj(CurrentAI); //load AI 

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

	if (CurrentAI == Characters_Sonic)
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

	if (CurrentAI == Characters_Knuckles)
		return;
	else
		PlaySound(0x317, 0, 0, 0);

}

void FixAISFXKnuckles2() {

	if (CurrentAI == Characters_Knuckles)
		return;
	else
		PlaySound(0x30c, 0, 0, 0);

}

void FixAISFXAmy() {
	if (CurrentAI == Characters_Amy)
		return;
	else
		PlaySound(0x31d, 0, 0, 0);
}

void FixAISFXAmy2() {
	if (CurrentAI == Characters_Amy)
		return;
	else
		PlaySound(0x4ff, 0, 0, 0);
}


void FixAISFXAmy3() {
	if (CurrentAI == Characters_Amy)
		return;
	else
		PlaySound(0x500, 0, 0, 0);
}

void FixAISFXAmy4() {
	if (CurrentAI == Characters_Amy)
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




/*
void AISwitch() {


	ObjectMaster* obj = GetCharacterObject(0);
	CharObj2* obj2 = ((EntityData2*)obj->Data2)->CharacterData;

	short powerups = obj2->Powerups;
	short jumptime = obj2->JumpTime;
	short underwatertime = obj2->UnderwaterTime;
	float loopdist = obj2->LoopDist;
	NJS_VECTOR speed = obj2->Speed;
	ObjectMaster* heldobj = obj2->ObjectHeld;
	obj->DeleteSub(obj);
	obj->MainSub = charfuncs[4];


	/*if (CurrentAI == Characters_Eggman)
		obj->DisplaySub = Eggman_Display;
	obj->Data1->CharID = (char)4;
	obj->Data1->Action = 0;
	obj->Data1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);

	if (!oldcol)
	{
		oldcol = obj->Data1->CollisionInfo;
		obj->Data1->CollisionInfo = nullptr;
	}


	obj->MainSub(obj);
	obj2 = ((EntityData2*)obj->Data2)->CharacterData;
	obj2->Powerups = powerups;
	obj2->JumpTime = jumptime;
	obj2->UnderwaterTime = underwatertime;
	obj2->LoopDist = loopdist;
	obj2->Speed = speed;
	obj2->ObjectHeld = heldobj;
}*/

//Load AI

void LoadTails_AI_R() {

	SetFrameRateMode(1, 1);
	LoadEggmanAI(); //load eggman if Speed highway
	
	if (isAIAllowed == true && CurrentCharacter != Characters_Big && CreditCheck != true)
	{
		if (Race == false)
		{
				ObjectMaster* obj;
				obj = GetCharacterObject(0);
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


//Fix Act transition as Eggman or Tikal.

const int loc_414914 = 0x414914;
__declspec(naked) void ChangeStartPosCharLoading()
{
	__asm
	{
		mov eax, [CurrentCharacter]
		movzx eax, word ptr[eax]
		cmp eax, 7
		jmp loc_414914
	}
}


