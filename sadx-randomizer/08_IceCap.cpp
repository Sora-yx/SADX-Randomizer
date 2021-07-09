#include "stdafx.h"
#include "IceCap.h"

void IC_Layout() {


	if (CurrentStageVersion != BigVersion)
	{
		if (CurrentCharacter > Characters_Tails)
		{
			WriteCall((void*)0x4eda00, ICAct3Position); //Skip snowboard cutscene when not sonic or tails.
			WriteCall((void*)0x4e9415, Load_Cart_R); //Load Cart in act 3
			WriteCall((void*)0x4e95dc, Delete_Cart); //Fix Delete Cart at the end of Ice Cap

			WriteCall((void*)0x4e9de1, DisableController_R);
			WriteData<1>((void*)0x4E9DE0, 0x08); //Cutscene skip

			WriteData<1>((void*)0x798306, 0x84); //Jump auto in the cart
			WriteData<1>((void*)0x7983c4, 0x7F);	
		}
		else //restore original values
		{
			WriteCall((void*)0x4e9415, DisableTimeThing);
			WriteCall((void*)0x4e9de1, DisableController_R);
			WriteData<1>((void*)0x4E9DE0, 0x04);
			WriteCall((void*)0x4eda00, DisableController);
		}
	}


	//CurrentStageVersion = TailsVersion;
	if (CurrentStageVersion != TailsVersion && CurrentStageVersion != BigVersion && CurrentAct < 2)
		CurrentStageVersion = SonicVersion;

	if (CurrentAct == 3)
		CurrentStageVersion = BigVersion;

	if (CurrentAct == 2)
		CurrentMission = SADX_Mission;

	if (CurrentStageVersion == TailsVersion && CurrentCharacter == Characters_Knuckles)
		CurrentStageVersion = SonicVersion;

	return;
}



int IC_ReturnCharacter() { //trick the game to make it think we are playing Sonic this will make spawn the Ice Cave as Big.
	if (CurrentStageVersion == Characters_Big)
		return (unsigned int)Characters_Big;
	else
		return (unsigned int)Characters_Sonic;
}

int IC_ReturnCharacter2() { //trick the game 
	if (CurrentStageVersion == SonicVersion)
		return (unsigned int)Characters_Big;

	if (CurrentStageVersion == TailsVersion)
		return (unsigned int)Characters_Tails;
}

//Prevent the game to disable control for cutscene skip Ice Cap act 3 (Cart thing.)

void DisableController_R() {

	if (CurrentCharacter > Characters_Tails)
	{
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
			return EnableController(0);
	}
	else
	{
		ObjectMaster* GetChara = GetCharacterObject(0);
		ObjectMaster* GetAI = GetCharacterObject(1);

		if (isAIActive && GetAI != nullptr)
			GetAI->Data1->Position.z = GetChara->Data1->Position.z + 100;

		return DisableController(0);
	}
}

//Add rings every Checkpoint for cart speed.
void AddRingIceCap() {
	PlaySound(0x15, 0, 0, 0);

	if (CurrentLevel == LevelIDs_IceCap && CurrentCharacter > Characters_Tails)
		AddRings(5);

	return;
}


void ICAct3Position() {

	if (CurrentCharacter > Characters_Tails)
	{
		if (CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		{
			TimeThing = 1;
			EnableController(0);
			PlayMusic(MusicIDs_icecap3);
		}
	}

	return;
}

void FixTailsVictoryIC() {

	//Prevent AI to make Tails lose when hiting the capsule if we aren't racing.

	if (CurrentCharacter == Characters_Tails && !Race)
		SetTailsRaceVictory();
	else
		SetOpponentRaceVictory();

	return;
}


PVMEntry IceCapObjectTextures[] = {
	{ "OBJ_ICECAP", (TexList*)0xE48F30 },
	{ "OBJ_ICECAP2", (TexList*)0xE48F78 },
	{ "E102TIME", (TexList*)0x91D5E0 },
	{ "E_SAI", (TexList*)0x38C8EA8 },
	{ "E_SNOWMAN", (TexList*)0x985990 },
	{ "MILESRACE", (TexList*)0x91BFC0 },
	{ "PEN", (TexList*)0x92D39C },
	{ "E_SNAKE", (TexList*)0x94E640 },
	{ "RAKO", (TexList*)0x949FC4 },
	{ "MECHA", (TexList*)0x1726108 },
	{ "MOGU", (TexList*)0x93ECEC },
	{ "KAOS_EME", (TexList*)0xC3FE20 },
	{ "SAKE", (TexList*)0x171BF60 },
	{ "GOMA", (TexList*)0x92ACE4 },
	{ "PIRANIA", (TexList*)0x1728BB8 },
	{ "NEW_BB", (TexList*)0x17126F4 },
	{ "HAMMER", (TexList*)0x1723CF4 },
	{ "SAME", (TexList*)0x172AAC4 },
	{ "UNAGI", (TexList*)0x172CD88 },
	{ "GORI", (TexList*)0x945964 },
	{ "BOARD_SCORE", (TexList*)0x9BE780 },
	{ NULL, (TexList*)0x91CBE8 },
	{ "OBJ_SHAREOBJ", &OBJ_SHAREOBJ_TEXLIST },
	{ 0 }
};

void __cdecl ICObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_IceCap * 8 + 2] = &IceCapObjectList;
	ObjLists[LevelIDs_IceCap * 8 + 3] = &IceCapObjectList;
	TexLists_Obj[LevelIDs_IceCap] = IceCapObjectTextures;
	return;
}

void __cdecl IceCap_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	WriteCall((void*)0x4e92e7, IC_ReturnCharacter);
	WriteCall((void*)0x4e9802, IC_ReturnCharacter);

	WriteCall((void*)0x4e97a0, IC_ReturnCharacter2); //TEST ATM
	WriteCall((void*)0x4e97a9, IC_ReturnCharacter2);
	WriteCall((void*)0x4ec065, AddRingIceCap);
	WriteCall((void*)0x4ecf8f, FixTailsVictoryIC);

	WriteData<5>((int*)0x422e66, 0x90);
	WriteData<5>((int*)0x422e75, 0x90);
	WriteData<5>((int*)0x422e84, 0x90);
	WriteData<5>((int*)0x422e93, 0x90);
	WriteData<5>((int*)0x422e9f, 0x90);
	WriteData<5>((int*)0x422eae, 0x90);
	WriteData<5>((int*)0x422ebd, 0x90);

	WriteCall((void*)0x422ecc, IC_Layout);

	ICObjects_Init(path, helperFunctions);

	AddLevelLayout("Ice Cap\\", "IC0", helperFunctions);
	AddLevelLayout("Ice Cap\\", "IC1", helperFunctions);
	AddLevelLayout("Ice Cap\\", "IC2", helperFunctions);
	AddLevelLayout("Ice Cap\\", "IC3", helperFunctions);
	AddLevelLayout("Ice Cap\\", "ICM", helperFunctions);

	AddCam("C0800");
	AddCam("C0801");
	AddCam("C0802");
	AddCam("C0803");
	return;
}