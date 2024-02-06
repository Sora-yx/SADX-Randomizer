#include "stdafx.h"
#include <fstream>

bool isAIActive = false;
uint8_t SwapDelay = 150;
int FlagAI = 0;
int AISwap = -1;
int CharaSwap = -1;
extern int AISwapCount;
int CurrentAI = -1;
int AIArray[4] = { -1, Characters_Sonic, Characters_Tails, Characters_Amy }; //Ai following you


//This is where all the AI is managed: loading and bug fixes. Using a part of Charsel code by MainMemory.

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
	ObjectMaster* CurAI = nullptr;
	CurAI = LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[CurrentAI]);
	CurAI->Data1->CharID = CurrentAI;
	CurAI->Data1->CharIndex = (char)i;
	EntityData1Ptrs[i] = (EntityData1*)CurAI->Data1;
	EntityData2Ptrs[i] = (EntityData2*)CurAI->Data2;
	return CurAI;
}

int AI_BannedLevel[17]{

	LevelIDs_EmeraldCoast, LevelIDs_TwinklePark, LevelIDs_SpeedHighway, LevelIDs_RedMountain, LevelIDs_IceCap,
	LevelIDs_SkyDeck, LevelIDs_LostWorld, LevelIDs_Casinopolis, LevelIDs_FinalEgg, LevelIDs_Chaos0,
	LevelIDs_Chaos2, LevelIDs_Chaos6, LevelIDs_PerfectChaos, LevelIDs_EggWalker,
	LevelIDs_EggViper, LevelIDs_SandHill, LevelIDs_E101R
};

int CheckTailsAI_R(void) { //restriction and bug fixes.


	if (CurrentAI < 0 || CurrentCharacter >= Characters_Gamma || CurrentCharacter == Characters_Sonic && MetalSonicFlag != 0 || CurrentCharacter == Characters_Knuckles)
	{
		isAIActive = false;
		return 0;
	}

	if (CurrentCharacter == CurrentAI || Race || CurrentLevel >= LevelIDs_StationSquare)
	{
		isAIActive = false;
		return 0;
	}

	for (uint8_t i = 0; i < LengthOfArray(AI_BannedLevel); i++)
	{
		if (CurrentLevel == AI_BannedLevel[i])
		{
			switch (CurrentLevel)
			{
			case LevelIDs_EmeraldCoast:
				if (CurrentStageVersion == SonicVersion && CurrentCharacter == Characters_Tails)
					return 0;
				break;
			case LevelIDs_SpeedHighway: //crash
				if (CurrentAct == 1)
					return 0;
				break;
			case LevelIDs_IceCap:
				if (CurrentStageVersion == SonicVersion)
				{
					return 0;
				}
				break;
			case LevelIDs_FinalEgg: //cutscene issue
				if (CurrentCharacter == Characters_Amy)
					return 0;
				break;
			case LevelIDs_Casinopolis:
				if (CurrentAct >= 1 || CurrentAct == 0 && (CurrentAI == Characters_Amy || CurrentCharacter == Characters_Amy)) //cutscene + pinball issue
					return 0;
				break;
			case LevelIDs_Chaos0:
				if (CurrentCharacter == Characters_Sonic || CurrentAI == Characters_Sonic)
					return 0;
				break;
			case LevelIDs_Chaos2: //Potential cutscene crash
				if (CurrentCharacter == Characters_Knuckles)
					return 0;
				break;
			case LevelIDs_Chaos6: //Potential cutscene crash
				if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Knuckles || CurrentCharacter == Characters_Sonic)
					return 0;
				break;
			case LevelIDs_TwinklePark:
			{
				if (CurrentStageVersion == SonicVersion)
					return 0;
			}
			break;
			case LevelIDs_LostWorld: //cutscene crash
			{
				if (CurrentAct == 2 && CurrentCharacter == Characters_Sonic)
					return 0;
			}
			break;
			case LevelIDs_SkyDeck:  //cutscene crash
			{
				if (CurrentAct == 2 && CurrentCharacter == Characters_Knuckles)
					return 0;

				if (CurrentAct < 2 && CurrentStageVersion != KnucklesVersion && (CurrentAI == Characters_Amy || CurrentCharacter == Characters_Amy))
					return 0;
			}
			break;
			default:
				return 0;
			}
		}
	}

	isAIActive = true;
	return 1;
}

void Load2PTails_r() //Custom AI
{
	FlagAI = CheckTailsAI_R();

	if (FlagAI != 1)
	{
		isAIActive = false;
		return;
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

			return;
		}
	}

	isAIActive = false;
	return;
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
			CurrentAI = Characters_Tails; //don't rand, just set tails AI

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

	isAIActive = false;
	return (ObjectMaster*)0x0;
}

//SFX characters ai fixes.

void FixAISFXSonic() {
	if (isAIActive && !Race)
	{
		if (CurCharacter() == Characters_Sonic)
			return;
	}

	PlaySound(0x2fa, 0, 0, 0);
	return;
}

void FixAISFXSonic2() {
	if (isAIActive && !Race)
	{
		if (CurCharacter() == Characters_Sonic)
			return;
	}

	if (CurrentCharacter != Characters_Sonic && Race)
		return;

	PlaySound(0x11, 0, 0, 0);
	return;
}

void FixAISFXSonic3() {
	if (isAIActive && !Race)
	{
		if (CurCharacter() == Characters_Sonic && isAIActive)
			return;
	}

	if (CurrentCharacter != Characters_Sonic && Race)
		return;

	PlaySound(0x12, 0, 0, 0);
	return;
}

void FixAISFXSonic4() {

	if (EntityData1Ptrs[1]) {
		if (EntityData1Ptrs[1]->CharID == Characters_Sonic)
			return;
	}

	if (isAIActive && !Race)
	{
		if (CurCharacter() == Characters_Sonic && isAIActive)
			return;
	}

	if (CurrentCharacter != Characters_Sonic && Race)
		return;

	PlaySound(0x4d1, 0, 0, 0);
	return;
}

void FixShowerCasino() {
	if (isAIActive)
		return;

	ForcePlayerAction(0, 0x28); //Shower
}

void FixAISFXJump() {
	if (isAIActive && !Race)
	{
		if (CurCharacter() == Characters_Knuckles || CurCharacter() == Characters_Tails || CurCharacter() == Characters_Amy)
			return;
	}

	PlaySound(0x11, 0, 0, 0);
	return;
}

void FixAISFXAmy() {
	if (isAIActive && !Race)
	{
		if (CurCharacter() == Characters_Amy)
			return;
	}

	if (Race && CurrentCharacter != Characters_Amy)
		return;

	PlaySound(0x31d, 0, 0, 0);
}

void FixAISFXAmy2() { //jump sound
	if (isAIActive && !Race)
	{
		//ObjectMaster* GetChara = GetCharacterObject(0);
		//GetChara->Data1->CharID;

		ObjectMaster* GetAI = GetCharacterObject(1);
		GetAI->Data1->CharID;

		if (GetAI != nullptr)
		{
			if (GetAI->Data1->CharID == Characters_Amy) //|| GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	if (Race && CurrentCharacter != Characters_Amy)
		return;

	PlaySound(0x4ff, 0, 0, 0);
}

void FixAISFXAmy3() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	PlaySound(0x500, 0, 0, 0);
}

void FixAISFXAmy4() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	if (Race && CurrentCharacter != Characters_Amy)
		return;

	PlaySound(0x506, 0, 0, 0);
}

void FixAISFXAmy5() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	if (EventFlagArray[EventFlags_Amy_LongHammer] == 1)
		PlaySound(0x31d, 0, 0, 0); //long hammer sound
	else
		PlaySound(0x31c, 0, 0, 0); //hammer sound
}

void FixAISFXAmy6() {
	if (isAIActive && !Race)
	{
		if (CurCharacter() == Characters_Amy)
			return;
	}

	PlaySound(0x508, 0, 0, 0);
}

void FixAISFXAmy7() { //spin dash noise when you press B
	if (isAIActive && !Race)
	{
		if (CurCharacter() == Characters_Amy)
			return;
	}

	if (Race && CurrentCharacter != Characters_Amy)
		return;

	if (EventFlagArray[EventFlags_Amy_LongHammer] == 1)
		PlaySound(0x31d, 0, 0, 0); //long hammer sound
	else
		PlaySound(0x31c, 0, 0, 0); //hammer sound
}

void FixAISFXAmy8() { //spin dash noise when you press B
	if (isAIActive && !Race)
	{
		if (CurCharacter() == Characters_Amy)
			return;
	}

	PlaySound(0x509, 0, 0, 0);
}


void FixAISFXGamma() {

	if (Race && CurrentCharacter != Characters_Gamma || isZeroActive)
		return;

	PlaySound(0x33b, 0, 0, 0);

	return;
}

void FixAISFXGamma2() {

	if (Race && CurrentCharacter != Characters_Gamma || isZeroActive)
		return;

	PlaySound(0x33d, 0, 0, 0);

	return;
}

void FixAISFXGamma3() {

	if (Race && CurrentCharacter != Characters_Gamma)
		return;

	PlaySound(0x33e, 0, 0, 0);

	return;
}

void FixAISFXGamma4() {

	if (Race && CurrentCharacter != Characters_Gamma)
		return;

	PlaySound(0x33f, 0, 0, 0);

	return;
}


//Result Voice FIX
void ResultVoiceFix() {
	ObjectMaster* GetChara = GetCharacterObject(0);
	GetChara->Data1->CharID;

	if (GetChara != nullptr)
	{
		switch (GetChara->Data1->CharID)
		{
		case Characters_Sonic:
			if (MetalSonicFlag == 0) {
				if ((short)CurrentLevel < 0xf)
					Load_DelayedSound_Voice(1840);
				else
					Load_DelayedSound_Voice(1843);
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
			if (CurrentLevel >= LevelIDs_Chaos0)
				Load_DelayedSound_Voice(1735);
			else
				Load_DelayedSound_Voice(1733);
			break;
		case Characters_Big:
			if (Race && CurrentLevel == LevelIDs_SpeedHighway || CurrentLevel == LevelIDs_HedgehogHammer || CurrentLevel >= LevelIDs_Chaos0 || CurrentMission >= Mission2_100Rings || CurrentStageVersion == GammaVersion && CurrentLevel != LevelIDs_EmeraldCoast && CurrentLevel != LevelIDs_HotShelter || CurrentStageVersion == KnucklesVersion)
				Load_DelayedSound_Voice(4011);
			else
				Load_DelayedSound_Voice(4010);
			SoundManager_Delete2();
			break;
		}
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

extern task* CurrentCart[];

void Player_VoiceSwap() {
	//Play voice switch
	switch (EntityData1Ptrs[0]->CharID)
	{
	case Characters_Sonic:
		if (MetalSonicFlag)
			LoadSoundList(62);
		else
		{
			PlayCustomSound(CommonSound_SonicSwap);
			LoadSoundList(1);
		}

		if (VoiceLanguage)
			LoadSoundList(72);
		else
			LoadSoundList(71);
		break;
	case Characters_Eggman:
		PlayCustomSound(CommonSound_EggmanSwap);
		break;
	case Characters_Tails:
		PlayCustomSound(CommonSound_TailsSwap);
		LoadSoundList(1);
		if (VoiceLanguage)
			LoadSoundList(72);
		else
			LoadSoundList(71);
		break;
	case Characters_Knuckles:
		PlayCustomSound(CommonSound_KnuxSwap);
		LoadSoundList(49);
		if (VoiceLanguage)
			LoadSoundList(70);
		else
			LoadSoundList(69);
		break;
	case Characters_Amy:
		PlayCustomSound(CommonSound_AmySwap);
		LoadSoundList(46);
		if (VoiceLanguage)
			LoadSoundList(64);
		else
			LoadSoundList(63);
		break;
	}
}



void AI_Manager(ObjectMaster* obj) {

	//FailSafe to prevent funny crash
	if (!isAIAllowed || !isAIActive || SonicRand != 0 || CurrentCharacter > 5 && CurrentAI > 5)
	{
		isAIActive = false;
		return;
	}

	if (CurrentCart[0] || !TimeThing || GameState != 15 || !CharObj2Ptrs[0] || Rings >= 100 && CurrentMission == Mission2_100Rings || CurrentStageVersion == KnucklesVersion && KnuxCheck >= 3)
		return;

	AISwapOnFrames();

	//initialize swap, taking actual character and ai information

	CharaSwap = GetCharacter1ID();

	char P1Action = EntityData1Ptrs[0]->Action;
	CharObj2* co2 = CharObj2Ptrs[0];
	CharObj2* co2P2 = CharObj2Ptrs[1];
	EntityData1* P1Data = EntityData1Ptrs[0];
	EntityData1* P2Data = EntityData1Ptrs[1];
	EntityData1* data = obj->Data1;
	ObjectMaster* player1 = GetCharacterObject(0);
	ObjectMaster* player2 = GetCharacterObject(1);


	if (P1Action > 21 || P1Action < 1 || P1Action == 3 || P1Action == 4)
		return;

	switch (data->Action) {
	case 0:
		data->InvulnerableTime = 0;
		data->Index = 0;
		data->Action++;
		break;
	case 1:
		if (!player1 || !player2) {
			CheckThingButThenDeleteObject(obj);
			return;
		}

		if (co2->Upgrades & Upgrades_SuperSonic || P1Action > 21)
			return;

		if (TimeThing == 1 && ControllerPointers[0]->PressedButtons & Buttons_Y && ControlEnabled && SwapDelay >= 150) {
			AISwapCount++; //Credit stat

			P1Data->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);
			player2->Data1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);

			AISwap = GetCharacter0ID();
			data->Action++;
		}
		break;
	case 2:
	{
		short powerups = co2->Powerups;
		short jumptime = co2->JumpTime;
		short underwatertime = co2->UnderwaterTime;
		float loopdist = co2->LoopDist;
		NJS_VECTOR speed = co2->Speed;

		CheckThingButThenDeleteObject(player1);
		player1->Data1->CollisionInfo = nullptr;
		player1->MainSub = charfuncs[CharaSwap];
		P1Data->CharID = CharaSwap;
		P1Data->Action = 0;
		Collision_Free(player1);
		P1Data->Status = 0;
		player1->MainSub(player1);

		CharObj2Ptrs[0]->Powerups = powerups;
		CharObj2Ptrs[0]->JumpTime = jumptime;
		CharObj2Ptrs[0]->UnderwaterTime = underwatertime;
		CharObj2Ptrs[0]->LoopDist = loopdist;
		CharObj2Ptrs[0]->Speed = speed;
		SwapDelay = 0;
		data->Action++;
	}
	break;
	case 3:
		if (++data->Index == 5) {

			Player_VoiceSwap();

			CheckThingButThenDeleteObject(player2);
			player2->Data1->CollisionInfo = nullptr;
			player2->MainSub = charfuncs[AISwap];
			player2->Data1->CharID = (char)AISwap;
			player2->Data1->Action = 0;
			P2Data->Status = 0;
			Collision_Free(player2);

			player2->MainSub(player2);
			data->Action++;
		}
		break;
	case 4:
		if (++data->InvulnerableTime == 5) {
			data->Action = 0;
		}
		break;
	}

	return;
}

//Load AI

void CheckLoadTails_AI_R() {
	if (CreditCheck != true)
	{
		if (!Race && CurrentStageVersion != TailsVersion && isAIAllowed && !isMPMod())
		{
			Load2PTails_r();
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

void AIAudioFixes() {
	WriteCall((void*)0x5cf22f, FixShowerCasino); //Prevent crash after chara swap


	WriteCall((void*)0x494be7, FixAISFXSonic); //fix sonic AI homing attack sound
	WriteCall((void*)0x495eaa, FixAISFXSonic2); //fix sonic jump sound
	WriteCall((void*)0x4972c2, FixAISFXSonic3); //fix sonic sfx
	WriteCall((void*)0x492f08, FixAISFXSonic4); //fix sonic sfx hurt

	WriteCall((void*)0x4768ea, FixAISFXJump); //Fix Jump Tails & Knuckles AI sound

	WriteCall((void*)0x487793, FixAISFXJump); //Fix Amy AI Jump
	WriteCall((void*)0x48af5f, FixAISFXAmy);
	WriteCall((void*)0x4877a3, FixAISFXAmy2);
	WriteCall((void*)0x485023, FixAISFXAmy3);
	WriteCall((void*)0x48b08b, FixAISFXAmy4);
	WriteCall((void*)0x489a75, FixAISFXAmy5);
	WriteCall((void*)0x485844, FixAISFXAmy6);
	WriteCall((void*)0x48947c, FixAISFXAmy7);
	WriteCall((void*)0x4857e0, FixAISFXAmy8);

}

//Reset value when AI is deleted
void AI_ResetValue() {
	isAIActive = false;
	AISwap = -1;
	CharaSwap = -1;
	return FUN_0042ce20();
}



//AI Swap
void AISwapOnFrames() {
	if (SwapDelay != 150 && TimeThing == 1 && ControlEnabled)
		SwapDelay++;
}


int prev_AI = -1;

//AI following you
short getRandomAI(uint8_t char_id, short stage_id) {
	int cur_AI = -1;
	size_t ai_count = sizeof(AIArray) / sizeof(AIArray[0]);

	if (char_id == Characters_Knuckles || char_id >= Characters_Gamma)
		return -1;

	if (stage_id >= LevelIDs_EggWalker || stage_id == LevelIDs_PerfectChaos || stage_id == LevelIDs_Chaos0)
		return -1;

	do {
		cur_AI = AIArray[rand() % ai_count];
	} while (cur_AI == prev_AI || cur_AI == char_id || (char_id != Characters_Sonic && cur_AI == Characters_Tails));

	prev_AI = cur_AI;
	return cur_AI;
}


void __cdecl AI_Init(const HelperFunctions& helperFunctions, const IniFile* config) {

	WriteData<5>((void*)0x415948, 0x90); //remove the original load2PTails in LoadCharacter as we use a custom one.

	WriteData<1>((int*)0x7B52A0, 0x2); //remove Eggman debug mode		
	WriteData<1>((int*)0x7b5290, 0x2); //remove Eggman debug mode	
	WriteData<21>((int*)0x7b52a1, 0x90);

	WriteData<1>((int*)0x7b43bc, 0x2); //remove Tikal debug mode


	if (!isAIAllowed || isMPMod())
		return;

	WriteCall((void*)0x47ed8e, CheckTailsAI_R);
	WriteCall((void*)0x47e943, CheckTailsAI_R);
	WriteCall((void*)0x47ea46, CheckTailsAI_R);
	WriteCall((void*)0x47ec62, CheckTailsAI_R);
	WriteJump((void*)0x47db1a, AI_ResetValue);
	AIAudioFixes();

	//This stuff is needed to fix all the issues with Character and AI Swap 
	WriteCall((void*)0x4BFFEF, GetCharacter0ID); // fix 1up icon
	WriteCall((void*)0x4C02F3, GetCharacter0ID); // ''
	WriteCall((void*)0x4D682F, GetCharacter0ID); // ''
	WriteCall((void*)0x4D69AF, GetCharacter0ID); // ''
	WriteCall((void*)0x425E62, GetCharacter0ID); // fix life icon
	WriteCall((void*)0x4D677C, GetCharacter0ID); // fix item boxes for Gamma
	WriteCall((void*)0x4D6786, GetCharacter0ID); // fix item boxes for Big
	WriteCall((void*)0x4D6790, GetCharacter0ID); // fix item boxes for Sonic
	WriteCall((void*)0x4C06D9, GetCharacter0ID); // fix floating item boxes for Gamma
	WriteCall((void*)0x4C06E3, GetCharacter0ID); // fix floating item boxes for Big
	WriteCall((void*)0x4C06ED, GetCharacter0ID); // fix floating item boxes for Sonic
}