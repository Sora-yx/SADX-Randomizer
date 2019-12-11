#include "RandomHelpers.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "stdafx.h"
#include "data\CharactersSettings.h"

int SonicRand = 0;
int TransfoCount = 0;
bool BounceLoaded;
extern int levelCount;

extern int CurrentAI;
extern bool CreditCheck;
extern bool Upgrade;
extern ObjectFuncPtr charfuncs[];
extern bool isAIAllowed;
bool BounceActive = false;
extern bool RNGCharacters;
extern bool GetBackRing;
extern bool Race;

extern bool AmySpeed;
extern bool BigSpeed;



void character_settings_onFrames() {

	if (GameState == 15)
	{
		if (CurrentLevel != 38 && CurrentLevel != 8)
		{
			if (AmySpeed)
				PhysicsArray[Characters_Amy].MaxAccel = 5;
			if (BigSpeed)
				PhysicsArray[Characters_Big].MaxAccel = 5;

			return;
		}

		if (CurrentLevel == 38 || CurrentLevel == 8 && CurrentAct == 2)
		{
			if (CurrentCharacter != Characters_Sonic && CurrentCharacter != Characters_Tails && CurrentCharacter != Characters_Knuckles)
			{
				PhysicsArray[Characters_Amy].MaxAccel = 8;
				PhysicsArray[Characters_Big].MaxAccel = 8;

				SetCameraControlEnabled(1);

				return;
			}
		}
	}
}


void AllUpgrades() {

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



void CheckRace();

//Hook Load Character
void LoadCharacter_r()
{

	if (isAIAllowed)
		LoadTails_AI_R();
	else
		LoadTails_AI_Original();

	if (CurrentCharacter != Characters_Sonic)
		MetalSonicFlag = 0;

	if (CurrentCharacter == Characters_Amy)
		CheckLoadBird();

		CheckRace();

	AllUpgrades();
	
	LoadCharacter();

	return;	
}

//Initialize Super Sonic Physic and Aura when Perfect Chaos fight starts.
void SuperAuraStuff() {

	TimeThing = 0;
	
	if (CurrentCharacter != Characters_Sonic)
	{
		CharObj2Ptrs[0]->Upgrades |= Upgrades_SuperSonic;
		LoadObject((LoadObj)2, 2, Sonic_SuperAura_Load);
		LoadObject((LoadObj)8, 2, Sonic_SuperPhysics_Load);
	}
	return;
}

//Initialize Super Sonic 
static void __cdecl SuperSonicManager_Main(ObjectMaster* _this)
{
	if (TransfoCount < 1)
	{
		DeleteObject_(_this);
		return;
	}

}
static void SuperSonicManager_Load()
{
	ObjectMaster* obj = LoadObject(static_cast<LoadObj>(0), 2, SuperSonicManager_Main);
}


extern int CustomLayout;

HelperFunctions extern help;

//Super Sonic Random transformation, used when the timer for a stage start. Also used to call some fixes. (Credit: SonicFreak94).

void SuperSonicStuff() {

	TimeThing = 1; //activate the timer of the stage.
	GetBackRing = false;

	if (CurrentCharacter != Characters_Sonic)
	{
		MetalSonicFlag = 0; //Fix Metal Sonic life icon with wrong characters.
		SonicRand = 0;
	}

	if (CurrentLevel < LevelIDs_Chaos0)
	{
		if (CurrentLevel >= LevelIDs_SkyDeck && CurrentLevel < 13 && CurrentLevel != LevelIDs_IceCap)
		{
			FreeCam = 1;
			SetCameraMode_(FreeCam);
		}
	}

	if (GameMode != 9)
	{
		GameMode = GameModes_Adventure_ActionStg; //force gamemode to 4 to fix the restart.
	}

	SuperSonicFlag = 0;
	TransfoCount = 0;

	//Banned SuperSonic Levels
	if (CurrentCharacter == Characters_Sonic)
	{
		if (CurrentLevel == LevelIDs_SpeedHighway || CurrentLevel == LevelIDs_SkyDeck || CurrentLevel == LevelIDs_Casinopolis || CurrentLevel == LevelIDs_PerfectChaos || CurrentLevel == LevelIDs_EggViper || CurrentLevel == LevelIDs_SandHill || CurrentLevel == LevelIDs_HotShelter && CurrentAct == 0)
		{
			SonicRand = 0;
			CharObj2Ptrs[0]->Upgrades &= ~Upgrades_SuperSonic;
			return;
		}
		else
		{
			if (MetalSonicFlag == 1 && SonicRand == 1)
			{
				SonicRand = 0;
				return;
			}
			else
			{
					if (MetalSonicFlag == 0)
					{
						if (SonicRand == 1 && CurrentCharacter == 0)
						{
							static Uint8 last_action[8] = {};
							Rings = 1;
							static const PVMEntry SuperSonicPVM = { "SUPERSONIC", &SUPERSONIC_TEXLIST };
							for (int i = 0; i < 8; i++)
							{
								EntityData1* data1 = EntityData1Ptrs[i];
								CharObj2* data2 = CharObj2Ptrs[i];

								if (data1 == nullptr || data1->CharID != Characters_Sonic)
								{
									continue;
								}

								bool transformation = (data2->Upgrades & Upgrades_SuperSonic) != 0;
								bool action = !transformation ? (last_action[i] == 8 && data1->Action == 12) : (last_action[i] == 82 && data1->Action == 78);

								//Super Sonic Transformation

								if (!transformation)
								{
									data1->Status &= ~Status_LightDash;
									ForcePlayerAction(i, 46);
									LoadPVM("SUPERSONIC", &SUPERSONIC_TEXLIST);
									PlayVoice(3001);
									data2->Upgrades |= Upgrades_SuperSonic;
									PlayMusic(MusicIDs_ThemeOfSuperSonic);
									if (CurrentVoiceNumber != 3001)
									{
										PlayVoice(3000);
									}
									if (!TransfoCount++)
									{
										SuperSonicManager_Load();
									}
								}
								else
								{
									last_action[i] = data1->Action;
								}
								SuperSonicFlag = TransfoCount > 0;
								return;
							}
						}
					}
			}
		}
	}
}



//Set Gamma's Timer to 6 min instead of 3.
void SetGammaTimer() {

	TimeMinutes = 6;
	TimeSeconds = 0;
	TimeFrames = 0;
	return;
}

//fix infinite gamma bounce on Egg Viper.

void FixGammaBounce() {

	if (CurrentCharacter == Characters_Gamma)
		return;

	EnemyBounceThing(0x0, 0x00, 3.50, 0x0);

}

void FixGammaHitBounce() {

	if (CurrentCharacter == Characters_Gamma)
		return;

	EggViperBounceHit();
}


void BigWeightHook() {

	BigWeightRecord = 2000; //force the record at 2000g so you will get B and A emblems.
	BigWeight = 2000; //display 2000g for Big
}


void FixCharacterSFX() {

	switch (CurrentCharacter)
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


void FixVictoryTailsVoice() {

	if (CurrentCharacter == Characters_Tails)
		ResultVoiceFix();
	else
		return;
}

int GetCharacter0ID() //player 1 ID
{
	return GetCharacterID(0);
}

int GetCharacter1ID() //AI ID
{
	return GetCharacterID(1);
}

void set_character_hook() {

	WriteCall((void*)0x415a25, LoadCharacter_r); //Hook Load Character

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
	WriteJump((void*)0x47A907, (void*)0x47A936); // prevent Knuckles from automatically loading Emerald radar
	WriteData<5>((void*)0x48adaf, 0x90); // prevent Amy to load Zero.

	//Hook several Knuckles killplane check (Hot Shelter, Red Mountain, Sky Deck...) This fix a weird black screen with Knuckles for some reason.
	WriteData<5>((void*)0x478937, 0x90);
	WriteData<5>((void*)0x478AFC, 0x90);
	WriteData<5>((void*)0x47B395, 0x90);
	WriteData<5>((void*)0x47B423, 0x90);

	WriteCall((void*)0x414872, SetGammaTimer); //increase Gamma's time limit by 3 minutes.

	//Super Sonic Stuff
	WriteData<2>(reinterpret_cast<Uint8*>(0x0049AC6A), 0x90i8); //Always initialize Super Sonic weld data.
	WriteCall((void*)0x560388, SuperAuraStuff); //Initialize Super Sonic physic and aura when perfect chaos fight starts.
	WriteCall((void*)0x4167da, SuperSonicStuff); //Call Super Sonic when a stage start.
	WriteData<7>(reinterpret_cast<Uint8*>(0x00494E13), 0x90i8); // Fix Super Sonic position when completing a stage.

		//Amy Stuff
	WriteData<6>((void*)0x48ADA5, 0x90u); // prevent Amy from loading the bird (fix several Bird called, we will call the bird manually.)
	WriteData<1>((void*)0x4c6875, 0x74); //Force Amy's bird to load at every stage. (from JNZ 75 to JZ 74)
	WriteData<1>((void*)0x4c6851, 0x28); //Force Amy's bird to load during boss fight.
}