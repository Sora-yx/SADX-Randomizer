#include "Utils.h"
#include "ActsSettings.h"
#include "stdafx.h"
#include "data\CharactersSettings.h"

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

void character_settings_onFrames() {
	if (CurrentLevel != 38 || (CurrentLevel != 8 && CurrentAct != 2) || CurrentLevel != 0)
	{
		if (AmySpeed)
			PhysicsArray[Characters_Amy].MaxAccel = 5;
		if (BigSpeed)
			PhysicsArray[Characters_Big].MaxAccel = 5;
	}

	if (CurrentLevel == 8 && CurrentAct == 2 && IceCapCutsceneSkip)
	{
		CharObj2Ptrs[0]->PhysicsData.FloorGrip = 10;
		PhysicsArray[Characters_Amy].MaxAccel = 10;
		PhysicsArray[Characters_Big].MaxAccel = 10;
	}

	return;
}

int SetAmyWinPose() {
	switch (CurrentCharacter)
	{
	case Characters_Amy:
		if (CurrentLevel >= LevelIDs_Chaos0 || CurrentLevel == LevelIDs_EmeraldCoast && CurrentLevelLayout == 1 || CurrentLevelLayout >= 2)
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

	if (CurrentCharacter != Characters_Sonic)
		MetalSonicFlag = 0;

	if (CurrentLevel >= LevelIDs_SkyDeck && CurrentLevel < 13 && CurrentLevel != LevelIDs_IceCap)
	{
		FreeCam = 1;
		SetCameraMode_(FreeCam);
	}

	if (CurrentCharacter == Characters_Amy)
		CheckLoadBird();

	if (CurrentLevel == LevelIDs_SpeedHighway || CurrentLevel == LevelIDs_Casinopolis || CurrentLevel == LevelIDs_SkyDeck || CurrentLevel == LevelIDs_WindyValley)
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
		LoadPVM("SUPERSONIC", &SUPERSONIC_TEXLIST);
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
		DeleteObject_(_this);
		return;
	}
}

static void SuperSonicManager_Load()
{
	ObjectMaster* obj = LoadObject(static_cast<LoadObj>(0), 2, SuperSonicManager_Main);
}



//Call different stuff when a stage start, like Super Sonic Random transformation, or a custom cart. Also used to call some fixes.

void CallStuffWhenLevelStart() {
	TimeThing = 1; //activate the timer of the stage.
	GetBackRing = false;
	Credits_State = 0;


	if (CurrentCharacter != Characters_Sonic)
	{
		MetalSonicFlag = 0; //Fix Metal Sonic life icon with wrong characters.
		SonicRand = 0;
	}

	if (GameMode != 9)
	{
		GameMode = GameModes_Adventure_ActionStg; //force gamemode to 4 to fix the restart.
	}

	if (CurrentLevel == LevelIDs_E101)
	{
		LoadPVM("E102EFFECT", &E102_EFF_TEXLIST);
	}

	SuperSonicFlag = 0;
	TransfoCount = 0;

	//Banned SuperSonic Levels
	if (CurrentCharacter == Characters_Sonic)
	{
		if (CurrentLevel == LevelIDs_SpeedHighway || CurrentLevel == LevelIDs_TwinkleCircuit || CurrentLevel == LevelIDs_Casinopolis || CurrentLevel == LevelIDs_SkyDeck || CurrentLevel == LevelIDs_EggViper || CurrentLevel == LevelIDs_SandHill || CurrentLevel == LevelIDs_HotShelter && CurrentAct == 0)
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

							//Super Sonic Transformation (Credit: SonicFreak94).

							if (!transformation)
							{
								data1->Status &= ~Status_LightDash;
								ForcePlayerAction(i, 46);
								LoadPVM("SUPERSONIC", &SUPERSONIC_TEXLIST);
								PlayVoice(3001);
								data2->Upgrades |= Upgrades_SuperSonic;
								PlayMusic(MusicIDs_ThemeOfSuperSonic);

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

//Create an object so Gamma can hit some specific bosses.
CollisionData col = { 0, 0, 0x77, 0, 0x800400, {0, 0, 0}, { 6.0, 6.0, 0.0 }, 0, 0 };

void TargetableEntity(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1;

	if (data->Action == 0) {
		AllocateObjectData2(obj, obj->Data1);

		//if the scale is specified, temporary set the collision scale to it.
		if (data->Scale.x) {
			col.scale.x = data->Scale.x;
			Collision_Init(obj, &col, 1, 2u);
			col.scale.x = 6;
		}
		else {
			Collision_Init(obj, &col, 1, 2u);
		}

		data->Action = 1;
	}
	else {
		ObjectMaster* boss = (ObjectMaster*)obj->Data1->LoopData;

		if (!boss || !boss->Data1) {
			DeleteObject_(obj);
			return;
		}

		if (EntityData1Ptrs[0]->CharID != Characters_Gamma) return;

		data->Position = boss->Data1->Position;
		data->Position.y += 10;

		if (OhNoImDead(obj->Data1, (ObjectData2*)obj->Data2))
		{
			DeleteObject_(obj);

			//if it is set, don't reload the target object
			if (data->CharID == 1) return;

			ObjectMaster* target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
			target->Data1->LoopData = (Loop*)boss;
		}
		else
		{
			AddToCollisionList(data);
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
	BigWeight = 1990; //meme display
}

void FixRadarSFX() {

	if (CurrentCharacter != Characters_Knuckles)
		PlayVoice_R(6000);
	else
		PlaySound(0x314, 0, 0, 0);

	return;

}

void FixEmeraldGetSFX() {

	if (CurrentCharacter != Characters_Knuckles)
		PlayVoice_R(6001);
	else
		PlaySound(0x313, 0, 0, 0);

	return;

}

void FixTikalSFX() {

	if (CurrentCharacter != Characters_Knuckles)
		PlayVoice_R(6002);
	else
		PlaySound(0x316, 0, 0, 0);

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



HMODULE SSMod = GetModuleHandle(L"sadx-super-sonic");

void Characters_Management() {
	WriteCall((void*)0x415a25, LoadCharacter_r); //Hook Load Character

	/*if (SSMod)
		WriteJump(reinterpret_cast<void*>(0x004496E1), SomethingAboutWater2); //Cancel Super Sonic Float, restore original code*/ //seem like it works, but need more test for now.

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

	WriteData<6>((void*)0x475E7C, 0x90u); // make radar work when not Knuckles
	WriteData<6>((void*)0x4764CC, 0x90u); // make Tikal hints work when not Knuckles
	WriteData<6>((void*)0x4a31f0, 0x90u); // Display the emerald grab when not Knuckles.
	WriteCall((void*)0x4762a6, FixRadarSFX);
	WriteCall((void*)0x477e14, FixEmeraldGetSFX);
	WriteCall((void*)0x7a907f, FixTikalSFX);

	WriteCall((void*)0x470127, BigWeightHook); //force Big Weight Record to 2000g

	WriteCall((void*)0x414872, SetGammaTimer); //increase Gamma's time limit by 3 minutes.
	WriteCall((void*)0x4230a0, BossesFixes); //allow gamma to target some boss (Called before boss fight.)

	//Super Sonic Stuff
	WriteData<2>(reinterpret_cast<Uint8*>(0x0049AC6A), 0x90i8); //Always initialize Super Sonic weld data.
	WriteCall((void*)0x560388, SuperAuraStuff); //Initialize Super Sonic physic and aura when perfect chaos fight starts.
	WriteCall((void*)0x4167da, CallStuffWhenLevelStart); //Call Super Sonic and other stuff when a stage start.
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

	WriteCall((void*)0x475852, KnuxRadarEmeraldCheck); //radar chara check

	WriteCall((void*)0x4a306a, KnuxRadarEmeraldCheck); //display piece
	WriteCall((void*)0x476661, KnuxRadarEmeraldCheck); //display piece
	WriteCall((void*)0x477d96, KnuxRadarEmeraldCheck); //display piece
}