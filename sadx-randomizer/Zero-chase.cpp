#include "stdafx.h"

bool isZeroActive;

void LoadZero() {
	if (CurrentLevel == LevelIDs_HotShelter)
		PressedSwitches_Reset();

	if (CurrentLevel == LevelIDs_FinalEgg && CurrentAct == 0)
	{
		camerahax_b();
		RNGDoor = rand() % 5;
	}

	if (CurrentLevel == LevelIDs_TwinklePark)
		SetCameraMode_(1);

	if (CurrentLevel == LevelIDs_FinalEgg && CurrentStageVersion != AmyVersion || CurrentLevel == LevelIDs_TwinklePark && CurrentStageVersion != AmyVersion) //don't load Zero if Sonic Layout
		return;

	isZeroActive = true;
	CheckLoadZero();
}

void FixZeroSound() {

	if (CurrentCharacter != Characters_Amy && CurrentLevel != LevelIDs_Zero)
		return;
	else
		PlaySound(0x324, 0x0, 0, 0x0);
}

void FixZeroSound2() {

	if (CurrentCharacter != Characters_Amy && CurrentLevel != LevelIDs_Zero)
		return;
	else
		PlaySound(0x322, 0x0, 0, 0x0);
}

void FixZeroSound3() {

	if (CurrentCharacter != Characters_Amy && CurrentLevel != LevelIDs_Zero)
		return;
	else
		PlaySound(0x332, 0x0, 0, 0x0);
}

void Set_ZeroChase() {
	//Zero Stuff
	WriteCall((void*)0x61d169, LoadZero); //Call Zero at Twinkle Park.
	WriteCall((void*)0x59a119, LoadZero); //Call Zero at Hot Shelter.
	WriteCall((void*)0x5ae104, LoadZero); //Call Zero at Final Egg.
	WriteCall((void*)0x4d2d12, FixZeroSound);
	WriteCall((void*)0x4d31ce, FixZeroSound);
	WriteCall((void*)0x4d218c, FixZeroSound3);

	WriteData<5>((void*)0x4d380d, 0x90); //Remove a special Zero Sound.
	WriteData<6>((void*)0x4d3f4a, 0x90); //Make Zero spawn for every character.	
	WriteData<2>((void*)0x4212c9, 0x90); //Load Zero Texture for any character.
}