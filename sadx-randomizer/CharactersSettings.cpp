#include "stdafx.h"

FunctionHook<void> LoadCharacter_t((intptr_t)0x4157C0);
//Manage characters stuff, improve and fixes some stuff
char SonicRand = 0;
extern bool Upgrade;


void CheckAndSetUpgrades() {
	if (Upgrade == true)
	{
		EventFlagArray[EventFlags_Sonic_LightShoes] = true;
		EventFlagArray[EventFlags_Sonic_CrystalRing] = true;
		EventFlagArray[EventFlags_Sonic_AncientLight] = true;
		EventFlagArray[EventFlags_Tails_JetAnklet] = true;
		EventFlagArray[EventFlags_Tails_RhythmBadge] = true;
		EventFlagArray[EventFlags_Amy_WarriorFeather] = true;
		EventFlagArray[EventFlags_Amy_LongHammer] = true;
		EventFlagArray[EventFlags_Knuckles_ShovelClaw] = true;
		EventFlagArray[EventFlags_Knuckles_FightingGloves] = true;
		EventFlagArray[EventFlags_Big_LifeRing] = true;
		EventFlagArray[EventFlags_Big_PowerRod] = true;
		EventFlagArray[EventFlags_Gamma_JetBooster] = true;
		EventFlagArray[EventFlags_Gamma_LaserBlaster] = true;
	}

	return;
}


void CheckAndLoadRaceOpponent();

//Hook Load Character
void LoadCharacter_r() 
{
	LoadCharacter_t.Original();

	CheckAndLoadRaceOpponent();

	if (isAIAllowed)
		CheckLoadTails_AI_R();
	else
		LoadTails_AI_Original();

	if (CurrentCharacter == Characters_Amy)
		CheckLoadBird();


	CheckAndSetUpgrades();
}

//if CharSel since it WriteJump the thing
void LoadCharacter_r2()
{
	LoadCharacter();

	CheckAndLoadRaceOpponent();

	if (CurrentCharacter == Characters_Amy)
		CheckLoadBird();

	CheckAndSetUpgrades();
}


void fixCharacterSoundAfterReset() {

	if (isAIActive)
	{
		switch (CurrentCharacter)
		{
		case Characters_Sonic:
			if (MetalSonicFlag)
				LoadSoundList(62);
			else
				LoadSoundList(1);

			if (VoiceLanguage)
				LoadSoundList(72);
			else
				LoadSoundList(71);
			break;

		case Characters_Tails:
			LoadSoundList(1);
			if (VoiceLanguage)
				LoadSoundList(72);
			else
				LoadSoundList(71);
			break;
		case Characters_Amy:
			LoadSoundList(46);
			if (VoiceLanguage)
				LoadSoundList(64);
			else
				LoadSoundList(63);
			break;
		}
	}

	return;
}


//Call different stuff when a stage start, like Super Sonic Random transformation, or a custom cart. Also used to call some fixes.

void CallStuffWhenLevelStart() 
{
	TimeThing = 1; //activate the timer of the stage.

	if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past)
		return;

	bool isOneCharSonk = isOnePlayerThisCharacter(Characters_Sonic);

	if (!isOneCharSonk)
	{
		MetalSonicFlag = 0; //Fix Metal Sonic life icon with wrong characters.
		SonicRand = 0;
	}
	else 
	{
		SuperSonic_TransformationCheck();
	}

	ShowActionButton();
	fixCharacterSoundAfterReset();

	if (isMPMod() && MPPlayers > 1)
	{
		if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0 && isOnePlayerThisCharacter(Characters_Gamma)
			|| CurrentLevel == LevelIDs_SandHill || CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)
		{
			Load_Cart_R();
		}
	}
	else
	{
		if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0 && CurrentCharacter >= Characters_Gamma ||
			(CurrentCharacter > Characters_Tails && CurrentLevel == LevelIDs_SandHill || CurrentLevel == LevelIDs_IceCap && CurrentAct == 2)) {
			Load_Cart_R();
		}
	}
}

void BigWeightHook() {

	BigWeightRecord = 2000; //force the record at 2000g so you will get B and A emblems.
	BigWeight = 1990; //meme display
}


//Set Gamma's Timer to 6 min instead of 3.
void SetGammaTimer() {
	TimeMinutes = 6;
	TimeSeconds = 0;
	TimeFrames = 0;
	return;
}


void FixCharacterSFX() {
	ObjectMaster* obj = GetCharacterObject(0);

	if (obj != nullptr)
	{
		//Play voice switch
		switch (obj->Data1->CharID)
		{
		case Characters_Sonic:
			if (MetalSonicFlag)
				LoadSoundList(62);
			else
			{
				if (VoiceLanguage)
					LoadSoundList(60);
				else
					LoadSoundList(59);
			}
			break;
		case Characters_Tails:
			LoadSoundList(1);
			if (VoiceLanguage)
				LoadSoundList(72);
			else
				LoadSoundList(71);
			break;
		case Characters_Knuckles:
			LoadSoundList(49);
			if (VoiceLanguage)
			{
				LoadSoundList(70);
				LoadSoundList(58);
			}
			else
			{
				LoadSoundList(69);
				LoadSoundList(57);
			}
			break;
		case Characters_Amy:
			LoadSoundList(46);
			if (VoiceLanguage)
				LoadSoundList(64);
			else
				LoadSoundList(63);
			break;
		case Characters_Gamma:
			LoadSoundList(48);
			if (VoiceLanguage)
				LoadSoundList(68);
			else
				LoadSoundList(67);
			break;
		case Characters_Big:
			LoadSoundList(47);
			if (VoiceLanguage)
				LoadSoundList(66);
			else
				LoadSoundList(65);
			break;
		}
	}
}



void FixVictoryTailsVoice() {
	if (CurrentCharacter == Characters_Tails)
		ResultVoiceFix();
	else
		return;
}

void RosterBanCheck() {
	//ban roster check
	for (uint8_t i = 0; i < LengthOfArray(banCharacter); i++)
	{
		if (banCharacter[i] == 1)
			ban++;
	}

	if (ban >= 6)
	{
		MessageBoxA(WindowHandle, "You cannot ban all the characters.", "SADX Randomizer", MB_ICONERROR);
		Exit();
	}
}

int8_t prev_char = -1;

uint8_t getRandomCharacter() {
	int8_t cur_char = -1;
	size_t char_count = sizeof(character) / sizeof(character[0]);

	do {

		cur_char = character[rand() % char_count];
	} while (cur_char == prev_char && ban < 5 || banCharacter[cur_char]);

	prev_char = cur_char;
	return cur_char;
}

int8_t prev_charMulti = -1;
uint8_t getRandomCharacterMulti(uint16_t i) 
{
	int8_t cur_char = -1;
	int failSafe = 0;

	do {

		if (randomizedSets[i].character <= Characters_Amy)
		{
			cur_char = character[rand() % 4];
		}			
		else
		{
			cur_char = randomizedSets[i].character;
			break;
		}

		failSafe++;

		if (failSafe >= 100)
		{
			break;
		}

	} while (cur_char == prev_charMulti && ban < 5 || banCharacter[cur_char]);

	prev_charMulti = cur_char;
	return cur_char;
}

void Characters_Init() 
{
	if (!isMPMod() || MPPlayers < 2)
	{
		if (isCharSelActive())
			WriteCall((void*)0x415A25, LoadCharacter_r2);
		else
			LoadCharacter_t.Hook(LoadCharacter_r);
	}

	WriteData<1>((int*)0x47ED60, 0xC3); //remove load Tails AI, we will manually do it
	WriteJump((void*)0x47A907, (void*)0x47A936); // prevent Knuckles from automatically loading Emerald radar
	WriteData<5>((void*)0x48adaf, 0x90); // prevent Amy to load Zero.


	if (AmySpeed) 
	{
		PhysicsArray[Characters_Amy].MaxAccel = 5.0f;
	}

	if (BigSpeed) {
		PhysicsArray[Characters_Big].MaxAccel = 5.0f;
	}

	//Remove several Knuckles killplane check, This fix a weird black screen in some specific stages.
	WriteData<5>((void*)0x478937, 0x90);
	WriteData<5>((void*)0x478AFC, 0x90);
	WriteData<5>((void*)0x47B395, 0x90);
	WriteData<5>((void*)0x47B423, 0x90);

	WriteData<7>((int*)0x4879c7, 0x90); //remove amy victory pose animation, we will manually call it to fix wrong animation.


	WriteCall((void*)0x470127, BigWeightHook); //force Big Weight Record to 2000g

	if (!isKHMod)
		WriteCall((void*)0x414872, SetGammaTimer); //increase Gamma's time limit by 3 minutes.


	WriteCall((void*)0x4167da, CallStuffWhenLevelStart); //Call Super Sonic and other stuff when a stage start.	
	WriteCall((void*)0x4175ad, CallStuffWhenLevelStart);
	initSuperSonicSettings();

	//Amy Stuff
	WriteData<6>((void*)0x48ADA5, 0x90u); // prevent Amy from loading the bird (fix several Bird called, we will call the bird manually.)
	WriteData<1>((void*)0x4c6875, 0x74); //Force Amy's bird to load at every stage. (from JNZ 75 to JZ 74)
	WriteData<1>((void*)0x4c6851, 0x28); //Force Amy's bird to load during boss fight.
}