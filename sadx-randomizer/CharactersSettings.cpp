#include "stdafx.h"


//Manage characters stuff, improve and fixes some stuff
char SonicRand = 0;
extern bool Upgrade;


int SetAmyWinPose() {
	switch (CurrentCharacter)
	{
	case Characters_Amy:
		if (CurrentLevel >= LevelIDs_Chaos0 || CurrentMissionCard <= 9 && CurrentMissionCard != 3 || CurrentMission >= 2)
			return 42;
		else
			return 32;
		break;
	default:
		return 42;
		break;
	}
}

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
void LoadCharacter_r() {

	CheckAndLoadRaceOpponent();

	if (isAIAllowed)
		LoadTails_AI_R();
	else
		LoadTails_AI_Original();
	
	if (CurrentCharacter == Characters_Amy)
		CheckLoadBird();

	CheckAndSetUpgrades();
	EmeraldRadar_R();
	LoadCharacter();

	return;
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

void CallStuffWhenLevelStart() {

	ObjectMaster* P1 = GetCharacterObject(0);
	char CurChara = P1->Data1->CharID;
	TimeThing = 1; //activate the timer of the stage.
		
	if (CurChara != Characters_Sonic)
	{
		MetalSonicFlag = 0; //Fix Metal Sonic life icon with wrong characters.
		SonicRand = 0;
	}
	else {
		SuperSonic_TransformationCheck();
	}


	ShowActionButton();
	fixCharacterSoundAfterReset();

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0 && CurChara >= Characters_Gamma ||
		(CurChara > Characters_Tails && CurrentLevel == LevelIDs_SandHill || CurrentLevel == LevelIDs_IceCap && CurrentAct == 2))
		Load_Cart_R();
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

void Characters_Init() {


	WriteCall((void*)0x415a25, LoadCharacter_r); //Hook Load Character

	WriteJump((void*)0x47A907, (void*)0x47A936); // prevent Knuckles from automatically loading Emerald radar
	WriteData<5>((void*)0x48adaf, 0x90); // prevent Amy to load Zero.

	WriteCall((void*)0x4E966C, GetCharacter0ID); // fix ice cap snowboard 1
	WriteCall((void*)0x4E9686, GetCharacter0ID); // fix ice cap snowboard 2
	WriteCall((void*)0x597B1C, GetCharacter0ID); // fix sand hill snowboard

	if (AmySpeed) {
		PhysicsArray[Characters_Amy].MaxAccel = 5;
	}

	if (BigSpeed) {
		PhysicsArray[Characters_Big].MaxAccel = 5;
	}

	//Hook several Knuckles killplane check (Hot Shelter, Red Mountain, Sky Deck...) This fix a weird black screen with Knuckles for some reason.
	WriteData<5>((void*)0x478937, 0x90);
	WriteData<5>((void*)0x478AFC, 0x90);
	WriteData<5>((void*)0x47B395, 0x90);
	WriteData<5>((void*)0x47B423, 0x90);

	
	WriteCall((void*)0x470127, BigWeightHook); //force Big Weight Record to 2000g
	
	if (!isCriticalMode)
		WriteCall((void*)0x414872, SetGammaTimer); //increase Gamma's time limit by 3 minutes.

	//Super Sonic Stuff
	WriteData<2>(reinterpret_cast<Uint8*>(0x0049AC6A), 0x90i8); //Always initialize Super Sonic weld data.
	WriteCall((void*)0x560388, SuperAuraStuff); //Initialize Super Sonic physic and aura when perfect chaos fight starts.
	WriteCall((void*)0x4167da, CallStuffWhenLevelStart); //Call Super Sonic and other stuff when a stage start.	
	WriteCall((void*)0x4175ad, CallStuffWhenLevelStart); 
	WriteData<7>(reinterpret_cast<Uint8*>(0x00494E13), 0x90i8); // Fix Super Sonic position when completing a stage.

	//Amy Stuff
	WriteData<6>((void*)0x48ADA5, 0x90u); // prevent Amy from loading the bird (fix several Bird called, we will call the bird manually.)
	WriteData<1>((void*)0x4c6875, 0x74); //Force Amy's bird to load at every stage. (from JNZ 75 to JZ 74)
	WriteData<1>((void*)0x4c6851, 0x28); //Force Amy's bird to load during boss fight.
	WriteCall((void*)0x4879C2, SetAmyWinPose);
	WriteData((char*)0x4879C1, (char)0x90);

	WriteCall((void*)0x79ab84, AmyCartImprovement);
	WriteCall((void*)0x79aa78, AmyCartImprovement);
	WriteCall((void*)0x7979b9, AmyCartImprovement);
}