#include "RandomHelpers.h"
#include "Utils.h"
#include "ActsSettings.h"
#include "stdafx.h"
#include "data\CharactersSettings.h"

int SonicRand = 0;
int TransfoCount = 0;
bool loaded;
int TikalRand = 0;
int EggmanRand = 0;

extern int CurrentAI;
extern bool CreditCheck;
extern bool Upgrade;
extern ObjectFuncPtr charfuncs[];




//Characters Settings, Load, Eggman and Tikal stuff.

//Fix Tikal and Eggman act switch.
const void* const sub_7B4450Ptr = (void*)0x7B4450;
inline void sub_7B4450(CharObj2* a2, EntityData1* a3)
{
	__asm
	{
		mov edi, [a2]
		mov esi, [a3]
		call sub_7B4450Ptr
	}
}

void __cdecl Eggman_Display(ObjectMaster* obj)
{
	sub_7B4450(((EntityData2*)obj->Data2)->CharacterData, obj->Data1);
}



FunctionPointer(int, sub_42FB00, (), 0x42FB00);

//Hook Load Character
void LoadCharacter_r()
{
	ClearPlayerArrays();
	ObjectMaster* obj;
	if (CurrentLevel == LevelIDs_SkyChase1 || CurrentLevel == LevelIDs_SkyChase2)
	{
		obj = LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, Tornado_Main);
		obj->Data1->CharID = (char)CurrentCharacter;
		obj->Data1->CharIndex = 0;
		*(void**)0x3B36DD0 = obj->Data2;
		EntityData1Ptrs[0] = (EntityData1*)obj->Data1;
		EntityData2Ptrs[0] = (EntityData2*)obj->Data2;
		MovePlayerToStartPoint(obj->Data1);
	}
	else
	{
			switch (CurrentCharacter)
			{
			case Characters_Knuckles:
				TikalRand = rand() % 2;
				if (TikalRand == 1)
					obj = LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[4]); //Load Tikal
				else
					obj = LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[CurrentCharacter]); //Load Knuckles
				break;
			case Characters_Sonic:
				EggmanRand = rand() % 2;
				if (EggmanRand == 1)
				{
					obj = LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[1]); //Load Eggman
					obj->DisplaySub = Eggman_Display;
				}
				else
					obj = LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[CurrentCharacter]); //Load Sonic
				break;
			default:
				obj = LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[CurrentCharacter]);
				obj->Data1->CharID = (char)CurrentCharacter;
				obj->Data1->CharIndex = 0;
				*(void**)0x3B36DD0 = obj->Data2;
				EntityData1Ptrs[0] = (EntityData1*)obj->Data1;
				EntityData2Ptrs[0] = (EntityData2*)obj->Data2;
				MovePlayerToStartPoint(obj->Data1);
				return;
				break;
			}

			obj->Data1->CharID = (char)CurrentCharacter;
			obj->Data1->CharIndex = 0;
			*(void**)0x3B36DD0 = obj->Data2;
			EntityData1Ptrs[0] = (EntityData1*)obj->Data1;
			EntityData2Ptrs[0] = (EntityData2*)obj->Data2;
			MovePlayerToStartPoint(obj->Data1);
			return;
		
	}

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

//Super Sonic Random transformation, used when the timer for a stage start. Also used to call some specific function and fixes.
void LoadEggmanAI();

void SuperSonicStuff() {

	TimeThing = 1; //activate the timer of the stage.

	if (CurrentCharacter != Characters_Sonic && CustomLayout == 0)
	{
		MetalSonicFlag = 0; //Fix Metal Sonic life icon with wrong characters.
	}


	if (CurrentLevel < 15)
	{
		if (CurrentLevel != LevelIDs_TwinklePark && CurrentAct == 0 || CurrentLevel != LevelIDs_SpeedHighway && CurrentAct == 1)
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
	{
		return;
	}
	else
	{
		EnemyBounceThing(0x0, 0x00, 3.50, 0x0);
	}

}



void FixGammaHitBounce() {

	if (CurrentCharacter == Characters_Gamma)
	{
		return;
	}
	else
	{
		EggViperBounceHit();
	}

}


//doesn't work if I put it on characters.h for some reason................... 

void BigWeightHook() {

	BigWeightRecord = 2000; //force the record at 2000g so you will get B and A emblems.
	BigWeight = 2000; //display 2000g for Big
}

// Metal Sonic Race stuff

void SwapSonicTextures(NJS_TEXLIST* sonictex) {

		if (MetalSonicFlag == 1) {
			LoadPVM("METALSONIC", &METALSONIC_TEXLIST); //called every frame but effectively loads texture only once, don't worry.
			njSetTexture(&METALSONIC_TEXLIST);
		}
		else {
			njSetTexture(sonictex);
		}
}

void SwapMetalSonic(EntityData1* entity1, EntityData2* entity2, CharObj2* obj2) {

		if (entity1->CharIndex == 1) {
			MetalSonicFlag = 1;
		}
		else {
			MetalSonicFlag = 0;
		}

		Sonic_Act1(entity1, entity2, obj2);

}



void AllUpgrades() {

	CharSel_LoadThing();
	CreditCheck == false;
	Credits_CanSkip = 1;

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

		WriteSaveFile();
	}
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
		Load_DelayedSound_SFX(0x5b2);
	else
		return;
}

