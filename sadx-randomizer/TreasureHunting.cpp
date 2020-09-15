#include "stdafx.h"


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
				PlayVoice_R(1826);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_R(315);
			break;
		case Characters_Tails:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_R(1812);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_R(1456);
			break;
		case Characters_Amy:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_R(5020);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_R(1737);
			break;
		case Characters_Gamma:
			if (EmeraldKnuxCheck == 1 || EmeraldKnuxCheck == 2)
				PlayVoice_R(5023);
			break;
		case Characters_Big:
			if (EmeraldKnuxCheck == 1)
				PlayVoice_R(5021);
			if (EmeraldKnuxCheck == 2)
				PlayVoice_R(5022);
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

	//Allow characters to break box in Speed Highway
	WriteData<1>((void*)0x61A5B8, 0x8);
	WriteData<1>((void*)0x61a5b9, 0x74);
}