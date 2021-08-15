#include "stdafx.h"


int KnuxRadarEmeraldCheck() {  //trick the game to make it think we are playing Knuckles

	if (CurrentStageVersion == KnucklesVersion && CurrentMission < Mission2_100Rings)
		return Characters_Knuckles;

	return 8; //Doesn't exist so the game won't load anything
}


//we first set the rng, then we check if we got diggable piece, if so, we rand again.
void TreasureHunting_SetRNG() {

	Knuckles_SetRNG(); 

	if (CurrentCharacter == Characters_Knuckles)
	{
		return;
	}
	
	KnuxCheck2 = 0; //fix Trial Mode Crash

	switch (CurrentLevel)
	{
	case LevelIDs_SpeedHighway:
		if (CurrentCharacter == Characters_Gamma && KnuxEmerald2 >= 48 && KnuxEmerald2 <= 53) //Gamma cannot break the trash.
		{
			do {
				Knuckles_SetRNG();
			} while (KnuxEmerald2 >= 48 && KnuxEmerald2 <= 53);
		}
		break;
	case LevelIDs_RedMountain:
		if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37) //If diggable emeralds, rand again.
		{
			do {
				Knuckles_SetRNG();
			} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37);
		}
		break;
	case LevelIDs_LostWorld:
		if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37) //If diggable emeralds, rand again.
		{
			do {
				Knuckles_SetRNG();
			} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 37);
		}
		break;
	case LevelIDs_SkyDeck:
		if (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 35) //If diggable emeralds, rand again.
		{
			do {
				Knuckles_SetRNG();
			} while (KnuxEmerald2 >= 32 && KnuxEmerald2 <= 35);
		}
	default:
		Knuckles_SetRNG();
		break;
	}
}

void CheckAndLoad_TreasureHunting() {
	if (CurrentMission > SADX_Mission || CurrentStageVersion != KnucklesVersion || CurrentLevel >= LevelIDs_Chaos0)
		return;
	
	if (CurrentCharacter != Characters_Knuckles) {
		LoadPVM("KNU_EFF", &KNU_EFF_TEXLIST);
	}

	LoadObject(LoadObj_Data1, 6, EmeraldRadarHud_Load_Load);
}

Trampoline KnucklesHint_Main_t((int)KnucklesHint_Main, (int)KnucklesHint_Main + 0x7, KnucklesHintMain_r);

void KnucklesHintMain_r(ObjectMaster* obj) {

	if (CurrentMission < Mission2_100Rings)
	{
		ObjectFunc(origin, KnucklesHint_Main_t.Target());
		origin(obj);
	}

	return;
}


void FixRadarSFX() {

	if (CurrentCharacter != Characters_Knuckles)
		PlayCustomSound(CommonSound_RadarBlink);
	else
		PlaySound(0x314, 0, 0, 0);

	return;
}

void FixEmeraldGetSFX() {

	if (CurrentCharacter != Characters_Knuckles)
		PlayCustomSound(CommonSound_EmeraldGet);
	else
		PlaySound(0x313, 0, 0, 0);

	return;
}


void FixTikalHintSFX() {

	if (CurrentCharacter != Characters_Knuckles)
		PlayCustomSound(CommonSound_TikalHint);
	else
		PlaySound(0x316, 0, 0, 0);

	return;
}

Trampoline PlayKnuxVoice_EmeraldGet(0x474f50, 0x474f55, PlayCharaVoice_EmeraldGet);

void PlayCharaVoice_EmeraldGet(ObjectMaster* a1) {
	ObjectMaster* P1 = GetCharacterObject(0);
	int CurChar = P1->Data1->CharID;

	if (P1 != nullptr)
	{
		switch (CurChar)
		{
		case Characters_Sonic:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_Original(1826);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_Original(315);
			break;
		case Characters_Tails:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_Original(1812);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_Original(1456);
			break;
		case Characters_Amy:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_Original(5020);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_Original(1737);
			break;
		case Characters_Gamma:
			if (EmeraldKnuxCheck == 1 || EmeraldKnuxCheck == 2)
				PlayVoice_Original(5023);
			break;
		case Characters_Big:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_Original(5021);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_Original(5022);
			break;
		}
	}

	if (CurChar == Characters_Knuckles)
	{
		ObjectFunc(origin, PlayKnuxVoice_EmeraldGet.Target());
		origin(a1);
	}
	else
		CheckThingButThenDeleteObject(a1);

	return;
}

void Init_TreasureHunting() {


	WriteData<6>((void*)0x475E7C, 0x90u); // make radar work when not Knuckles
	WriteData<6>((void*)0x4764CC, 0x90u); // make Tikal hints work when not Knuckles
	WriteData<6>((void*)0x4a31f0, 0x90u); // Display the emerald grab thing when not Knuckles.


	WriteCall((void*)0x4762a6, FixRadarSFX);
	WriteCall((void*)0x477e14, FixEmeraldGetSFX);
	WriteCall((void*)0x7a907f, FixTikalHintSFX);
	WriteCall((void*)0x475852, KnuxRadarEmeraldCheck); //radar chara check
	WriteCall((void*)0x4a306a, KnuxRadarEmeraldCheck); //display piece
	WriteCall((void*)0x476661, KnuxRadarEmeraldCheck); //display piece
	WriteCall((void*)0x477d96, KnuxRadarEmeraldCheck); //display piece	

	//Force the game to load treasure hunting stuff for everyone
	WriteData<1>((void*)0x416F06, 0x08);
	WriteData<1>((void*)0x4153E1, 0x08);
	WriteData<1>((void*)0x416f08, 0x74);
	WriteData<1>((void*)0x4153e3, 0x74);
	WriteCall((void*)0x416F0A, TreasureHunting_SetRNG);
	WriteCall((void*)0x4153E5, TreasureHunting_SetRNG);
}