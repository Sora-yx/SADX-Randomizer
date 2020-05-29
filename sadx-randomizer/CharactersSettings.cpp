#include "Utils.h"
#include "ActsSettings.h"
#include "stdafx.h"
#include "sound.h"
#include "data\CharactersSettings.h"
#include "Trampoline.h"

char SonicRand = 0;
int TransfoCount = 0;
bool BounceLoaded;

extern bool CreditCheck;
extern bool Upgrade;
extern ObjectFuncPtr charfuncs[];
bool BounceActive = false;
extern bool RNGCharacters;
extern bool GetBackRing;
extern bool isAIAllowed;

extern bool AmySpeed;
extern bool BigSpeed;
extern bool IceCapCutsceneSkip;
extern int CurrentMissionCard;
extern bool Race;
extern bool isCriticalMode;


void character_settings_onFrames() {
	if (CurrentLevel != 0)
	{
		if (AmySpeed)
			PhysicsArray[Characters_Amy].MaxAccel = 5;

		if (BigSpeed)
			PhysicsArray[Characters_Big].MaxAccel = 5;
	}

	return;
}

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
	
	if (CurrentCharacter == Characters_Amy)
		CheckLoadBird();

	CheckRace();

	AllUpgrades();
	EmeraldRadar_R();
	LoadCharacter();

	return;
}




//Initialize Super Sonic Physic and Aura when Perfect Chaos fight starts.
void SuperAuraStuff() {
	TimeThing = 0;

	if (CurrentCharacter != Characters_Sonic)
	{
		CharObj2Ptrs[0]->Upgrades |= Upgrades_SuperSonic;
		CharObj2Ptrs[0]->Powerups |= Powerups_Invincibility;
		LoadObject((LoadObj)2, 2, Sonic_SuperAura_Load);
		LoadObject((LoadObj)8, 2, Sonic_SuperPhysics_Load);
	}
	return;
}

//Initialize Super Sonic  (Credit: SonicFreak94).

static void __cdecl SuperSonicManager_Main(ObjectMaster* _this)
{
	if (TransfoCount < 1)
	{
		CheckThingButThenDeleteObject(_this);
		return;
	}
}

static void SuperSonicManager_Load()
{
	ObjectMaster* obj = LoadObject(static_cast<LoadObj>(0), 2, SuperSonicManager_Main);
}

int SSLevel[9]{ LevelIDs_SpeedHighway, LevelIDs_TwinkleCircuit, LevelIDs_Casinopolis,
LevelIDs_SkyDeck, LevelIDs_EggViper, LevelIDs_SandHill, LevelIDs_HotShelter, LevelIDs_IceCap, LevelIDs_Chaos6 };


extern int8_t CurrentStageVersion;

int GetSSLevelBanned() {

	for (int i = 0; i < LengthOfArray(SSLevel); i++)
	{
		if (CurrentLevel == SSLevel[i])
		{
			switch (CurrentLevel)
			{
			case LevelIDs_TwinklePark:
				if (CurrentAct == 1 && CurrentStageVersion != Characters_Amy || CurrentAct == 0)
					return true;
				else
					return false;
				break;
			case LevelIDs_SpeedHighway:
				if (CurrentAct == 0 && CurrentStageVersion != Characters_Tails)
					return true;
				else
					return false;
				break;
			case LevelIDs_Casinopolis:
				if (CurrentAct == 0 && CurrentStageVersion == 3)
					return false;
				else
					return true;
				break;
			case LevelIDs_IceCap:
				if (CurrentAct == 2)
					return true;
				else
					return false;
				break;
			case LevelIDs_HotShelter:
				if (CurrentAct < 2)
					return true;
				else
					return false;
				break;
			default:
				return true;
				break;
			}
		}
	}

	return false;
}

Trampoline LoadCharTextures_T((int)LoadCharTextures, (int)LoadCharTextures + 0x6, CheckAndLoadSuperSonic_Tex);

void CheckAndLoadSuperSonic_Tex(int curChara) {

	if (CurrentCharacter == Characters_Sonic && !GetSSLevelBanned() || CurrentCharacter != Characters_Sonic && CurrentLevel == LevelIDs_PerfectChaos)
		LoadPVM("SUPERSONIC", &SUPERSONIC_TEXLIST);


	FunctionPointer(void, original, (int curChara), LoadCharTextures_T.Target());
	return original(curChara);
}



void SuperSonic_TransformationCheck() {

	SuperSonicFlag = 0;
	TransfoCount = 0;

	bool isLevelBanned = GetSSLevelBanned();

	if (isLevelBanned || MetalSonicFlag == 1)
	{
		SonicRand = 0;
		return;
	}
	else
	{
		if (SonicRand == 2 && !MetalSonicFlag)
		{
			static Uint8 last_action[8] = {};
			if (!Rings)
				Rings = 1;

				EntityData1* data1 = EntityData1Ptrs[0];
				CharObj2* data2 = CharObj2Ptrs[0];

				bool transformation = (data2->Upgrades & Upgrades_SuperSonic) != 0;
				bool action = !transformation ? (last_action[0] == 8 && data1->Action == 12) : (last_action[0] == 82 && data1->Action == 78);

				//Super Sonic Transformation (Credit: SonicFreak94).

				if (!transformation)
				{
					data1->Status &= ~Status_LightDash;
					ForcePlayerAction(0, 46);
					njSetTexture(&SUPERSONIC_TEXLIST);
					PlayVoice(3001);
					data2->Upgrades |= Upgrades_SuperSonic;
					PlayMusic(MusicIDs_ThemeOfSuperSonic);

					if (!TransfoCount++)
						SuperSonicManager_Load();
				}

				SuperSonicFlag = TransfoCount > 0;
				return;
		}
		
	}
}

extern bool isAIActive;
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
	else
		SuperSonic_TransformationCheck();


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

int GetCharacter0ID() //player 1 ID
{
	return GetCharacterID(0);
}

int GetCharacter1ID() //AI ID
{
	return GetCharacterID(1);
}

int __cdecl SetSonicWinPose_i()
{
	if (CurrentCharacter != Characters_Amy || (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel != LevelIDs_SandHill))
		return 75;
	else
		return 47;
}

const int loc_4961DD = 0x4961DD;
__declspec(naked) void SetSonicWinPose()
{
	__asm
	{
		call SetSonicWinPose_i
		mov word ptr[esi + 124h], ax
		jmp loc_4961DD
	}
}

int __cdecl SetKnucklesWinPose_i()
{
	if (CurrentCharacter != Characters_Amy || (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel != LevelIDs_SandHill))
		return 39;
	else
		return 84;
}

const int loc_476B62 = 0x476B62;
__declspec(naked) void SetKnucklesWinPose()
{
	__asm
	{
		call SetKnucklesWinPose_i
		mov word ptr[edi + 124h], ax
		jmp loc_476B62
	}
}




void Characters_Management() {
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

	WriteCall((void*)0x4E966C, GetCharacter0ID); // fix ice cap snowboard 1
	WriteCall((void*)0x4E9686, GetCharacter0ID); // fix ice cap snowboard 2
	WriteCall((void*)0x597B1C, GetCharacter0ID); // fix sand hill snowboard

	WriteJump((void*)0x4961D4, SetSonicWinPose);
	WriteJump((void*)0x476B59, SetKnucklesWinPose);

	//Hook several Knuckles killplane check (Hot Shelter, Red Mountain, Sky Deck...) This fix a weird black screen with Knuckles for some reason.
	WriteData<5>((void*)0x478937, 0x90);
	WriteData<5>((void*)0x478AFC, 0x90);
	WriteData<5>((void*)0x47B395, 0x90);
	WriteData<5>((void*)0x47B423, 0x90);

	WriteData<6>((void*)0x475E7C, 0x90u); // make radar work when not Knuckles
	WriteData<6>((void*)0x4764CC, 0x90u); // make Tikal hints work when not Knuckles
	WriteData<6>((void*)0x4a31f0, 0x90u); // Display the emerald grab when not Knuckles.
	WriteCall((void*)0x4762a6, FixRadarSFX);
	WriteCall((void*)0x477e14, FixEmeraldGetSFX);
	WriteCall((void*)0x7a907f, FixTikalHintSFX);
	WriteCall((void*)0x475852, KnuxRadarEmeraldCheck); //radar chara check
	WriteCall((void*)0x4a306a, KnuxRadarEmeraldCheck); //display piece
	WriteCall((void*)0x476661, KnuxRadarEmeraldCheck); //display piece
	WriteCall((void*)0x477d96, KnuxRadarEmeraldCheck); //display piece	
	
	WriteData<1>((void*)0x61A5B8, 0x8);
	WriteData<1>((void*)0x61a5b9, 0x74);
	
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