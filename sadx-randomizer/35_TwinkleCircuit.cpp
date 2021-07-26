#include "stdafx.h"


void TwinkleCircuitResult() {
	TCQuit = 1;
	DisablePause();
	ScreenFade_Timer = 0;
	ScreenFade_Alpha = 0xff;

	if (SelectedCharacter == 6) //Fix Super Sonic Story giving sonic layout
		LastStoryFlag = 1;
	else
		LastStoryFlag = 0;

	//CustomFlag++;
	GameMode = GameModes_Adventure_Field;
	Rings = 0;
	DeleteAllObjects();
	PauseQuitThing2();
	GameState = 0x5;
}

void TwinkleCircuit_Init() { //force the game to chain stages after Twinkle Circuit
	WriteData<1>((void*)0x4DB0B2, 0x05);
	WriteData<5>((void*)0x4db051, 0x90);
	WriteData<5>((void*)0x4DB04A, 0x90);
}

void fixTCCart() {
	WriteData<1>((void*)0x798306, 0x85); //Restore original Functions
	WriteData<1>((void*)0x7983c4, 0x7C);

	return;
}