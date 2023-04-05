#include "stdafx.h"
#include "Cas.h"


void FixFlipperCharacterPosition() {

	if (CurrentLevel == LevelIDs_Casinopolis && CurrentAct > 1)
	{
		if (CurrentCharacter == Characters_Sonic)
			ForcePlayerAction(0, 0x2d);
		else
			ForcePlayerAction(0, 24);
	}

}

void IncreaseRings_R() { //increase the amount of ring get in the pinball to make this section shorter.

	if (CurrentLevel == LevelIDs_Casinopolis && CurrentAct > 1)
		Rings += 1;

	PlaySound(7, 0x0, 0x0, 0x0);
}

void FixShakeoffGarbageAction() { //This make the game crash as Tails.

	if (!EntityData1Ptrs[0])
		return;

	if (EntityData1Ptrs[0]->CharID != Characters_Sonic)
		return;
	else
		ForcePlayerAction(0, 0x2a);

	return;
}

void FixInvisibleWall() {

	//if Sonic layout, add an invisible wall, if not, return.
	if (CurrentStageVersion == SonicVersion)
		LoadObject((LoadObj)2, 6, InvisibleWallCasino);

	return;
}


void FixTailsVictoryCAS() {

	//Prevent AI to make Tails lose when hiting the capsule if we aren't racing.

	if (CurrentCharacter == Characters_Tails && !Race)
		SetTailsRaceVictory();
	else
		SetOpponentRaceVictory();

	return;
}

void FixGoldenAndCoin() {

	//if Knuckles layout, move the coin in the emerald room and display Sonic Golden Statue, else restore the original function.
	if (CurrentStageVersion == KnucklesVersion && CurrentAct == 0)
	{
		WriteData<1>((char*)0x5c4425, 0x74); //Coin position

		if (CurrentCharacter == Characters_Gamma)
			WriteData<1>((char*)0x5c4232, 0x74); //don't display golden statue
		else
			WriteData<1>((char*)0x5c4232, 0x75); //display golden statue when not Sonic/Gamma
	}
	else
	{
		WriteData<1>((char*)0x5c4425, 0x75); //restore original function coin position
		WriteData<1>((char*)0x5cef47, 0x75);

		if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Knuckles)
			WriteData<1>((char*)0x5c4232, 0x75); //don't display golden statue/ Fix Crash
		else
			WriteData<1>((char*)0x5c4232, 0x74); //display golden statue*/
	}


	if (CurrentCharacter == Characters_Gamma)
		WriteData<1>((char*)0x5D118B, 0x2); //Fix gamma pinball teleportation
	else
		WriteData<1>((char*)0x5D118B, 0x1); //Restore original function.

	return;
}

void FixCasinoSoundEffects() {
	if (GameMode == 4 || GameMode == 5 || GameMode == 9)
	{
		switch (CurrentLevel)
		{
			//fix Casinopolis SFX when using wrong characters
		case LevelIDs_Casinopolis:
			FixCharacterSFX();
			break;
		case LevelIDs_Zero:
			LoadSoundList(46);
			break;
		case LevelIDs_SSGarden:
		case LevelIDs_ECGarden:
		case LevelIDs_MRGarden:
		case LevelIDs_ChaoRace:
			FixCharacterSFX();
			LoadCharVoices();
			break;
		}
	}
}

void Fix_PlayerPositionInPinball(Uint8 charIndex, float x, float y, float z) {

	if (CurrentCharacter >= Characters_Gamma) 
	{
		x = 0;
		y = 192.295f;
		z = 51.5f;
	}

	return PositionPlayer(charIndex, x, y, z);
}


void Casino_Layout() {

	if (CurrentStageVersion != TailsVersion && CurrentStageVersion != KnucklesVersion)
		CurrentStageVersion = SonicVersion;

	if (CurrentAct == 1)
		CurrentStageVersion = TailsVersion;

	if (CurrentMission == Mission3_LostChao && CurrentStageVersion == SonicVersion)
	{
		CurrentMission = SADX_Mission;
	}

	FixGoldenAndCoin();
	return;
}

PVMEntry CasinopolisObjectTextures[] = {
	{ "OUM", (TexList*)0x9334EC },
	{ "KUJA", (TexList*)0x93142C },
	{ "MILESRACE", (TexList*)0x91BFC0 },
	{ "SUPI_SUPI", (TexList*)0x96F518 },
	{ "TUBA", (TexList*)0x92F2BC },
	{ "KOAR", (TexList*)0x9359B4 },
	{ "USA", (TexList*)0x93CF74 },
	{ "KAOS_EME", (TexList*)0xC3FE20 },
	{ "UNI_A_UNIBODY", (TexList*)0x96CB5C },
	{ "TOGEBALL_TOGEBALL", (TexList*)0x96BC54 },
	{ "OBJ_HIGHWAY", (TexList*)0x26703F0 },
	{ "OBJ_HIGHWAY2", (TexList*)0x26706AC },
	{ "UNI_A_UNIBODY", (TexList*)0x96CB5C },
	{ 0 }
};


void __cdecl CasinoObjects_Init(const char* path, const HelperFunctions& helperFunctions) {
	//Change the objectlist
	ObjLists[LevelIDs_Casinopolis * 8 + 0] = &CasinopolisObjectList;
	ObjLists[LevelIDs_Casinopolis * 8 + 1] = &CasinopolisObjectList;
	TexLists_Obj[LevelIDs_Casinopolis] = CasinopolisObjectTextures;
	return;
}

void __cdecl Casino_Init(const char* path, const HelperFunctions& helperFunctions) {

	WriteData<5>((void*)0x422ef4, 0x90);
	WriteData<5>((void*)0x422f2d, 0x90);
	WriteData<5>((void*)0x422f3c, 0x90);
	WriteCall((void*)0x422f03, Casino_Layout);

	WriteData<1>((char*)0x5c0595, 0x08); //make pinball working for Knuckles
	WriteData<1>((char*)0x5c0615, 0x08); //make pinball working for Knuckles part 2
	WriteData<1>((char*)0x5C0695, 0x08); //Allow Knuckles to leave the garbage. (why is this checked anyway?)
	WriteData<1>((char*)0x5c4424, 0x08); //Add coin in the drop ring room. (knuckles layout)
	WriteData<2>((int*)0x5d049e, 0x90); //Add Invisible wall when not Sonic. (drop ring Emerald room.)

	WriteCall((void*)0x5d04a9, FixInvisibleWall); //Add invisible wall if sonic version, otherwise remove it.
	WriteCall((void*)0x5dacc8, FixFlipperCharacterPosition);
	WriteCall((void*)0x5d6914, FixFlipperCharacterPosition);
	WriteCall((void*)0x5d6997, FixFlipperCharacterPosition);
	WriteCall((void*)0x5da671, FixFlipperCharacterPosition);
	WriteCall((void*)0x5c14f5, IncreaseRings_R);

	WriteCall((void*)0x5c5906, FixShakeoffGarbageAction);
	WriteCall((void*)0x5dd088, FixTailsVictoryCAS);

	WriteCall((void*)0x5dd08d, FixRaceResult);

	WriteCall((void*)0x5C0812, Fix_PlayerPositionInPinball);
	WriteCall((void*)0x5C0E77, Fix_PlayerPositionInPinball);

	CasinoObjects_Init(path, helperFunctions);

	AddLevelLayout("Casinopolis\\", "Cas0", helperFunctions);
	AddLevelLayout("Casinopolis\\", "Cas1", helperFunctions);
	AddLevelLayout("Casinopolis\\", "CasM", helperFunctions);
	AddLevelLayout("Casinopolis\\", "CasK", helperFunctions);

	AddCam("C0900");
	AddCam("C0901");
	AddCam("C0904"); //Miles act 2
	AddCam("C0905"); //Knuckles


	for (int i = 0; i < 8; i++) //Fix AI Race Position
		helperFunctions.RegisterStartPosition(i, Cas_StartPositions[0]);
}
