#include "stdafx.h"
#include "ActsSettings.h"
#include "RandomHelpers.h"
#include "CharactersSettings.h"
#include "sound.h"
#include "Trampoline.h"
#include <fstream>

bool isAIActive = false;
extern bool CreditCheck;
int FlagAI = 0;
int AISwap = 0;
int CharaSwap = 0;
extern int AISwapCount;
int CurrentAI = -1;
float xpos = 0;
float ypos = 0;
float vscale = 1.0f;
float hzscale = 1.0f;
float center_x = (float)HorizontalResolution / 2.0f;
float center_y = (float)VerticalResolution / 2.0f;

static float ActionButtonAlpha = 0;
static bool ActionButtonActive = false;

NJS_TEXNAME Hud_Rando_TEXNAMES[4];
NJS_TEXLIST Hud_Rando_TEXLIST = { arrayptrandlength(Hud_Rando_TEXNAMES) };
PVMEntry Hud_Rando = { "hud_rando", &Hud_Rando_TEXLIST };

enum RandoHudTextures {
	CmnHudTex_SA2ActionBody,
	CmnHudTex_SA2ActionButton,
	CmnHudTex_SA2Action,
};

enum RandoHudSprites {
	CmnHudSprite_SA2ActionBody,
	CmnHudSprite_SA2ActionButton,
	CmnHudSprite_SA2Action,
};

NJS_TEXANIM	Hud_Rando_TEXANIM[]{
	{ hzscale * 0x3F, vscale * 0x2F, 0x24, 0xC, 0, 0, 0x100, 0x100, CmnHudTex_SA2ActionBody, 0x20 },
	{ hzscale * 0x3F, vscale * 0x2F, 0x10, 0x10, 0, 0, 0x100, 0x100, CmnHudTex_SA2ActionButton, 0x20 },
	{ hzscale * 0x6F, vscale * 0x1F, 0x35, 0x8, 0, 0, 0x100, 0x100, CmnHudTex_SA2Action, 0x20 },
};


NJS_SPRITE HUD_Rando_SPRITE = { { 0, 0, 0 }, 1.0, 1.0, 0, &Hud_Rando_TEXLIST, Hud_Rando_TEXANIM };

void ShowActionButton() {
	ActionButtonActive = true;
}

void Hud_ShowActionButton() {
	if (!IsGamePaused()) {
		if (ControllerPointers[0]->PressedButtons & Buttons_Y) {
			ActionButtonActive = false;
		}
		else
			ShowActionButton();

		if (ActionButtonActive == true) {
			ActionButtonActive = false;
			if (ActionButtonAlpha < 1) ActionButtonAlpha += 0.1f;
		}
		else if (ActionButtonAlpha <= 0) {
			return;
		}
		else {
			if (ActionButtonAlpha > 0) ActionButtonAlpha -= 0.2f;
		}
	}
	else {
		njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);

		if (ActionButtonActive == false && ActionButtonAlpha <= 0) {
			return;
		}
	}


	vscale = (float)VerticalResolution / 480.0f;
	hzscale = (float)HorizontalResolution / 640.0f;
	float size_x = 0;
	float size_y = 0;
	size_x = 255.0f * hzscale * 0.5f;
	size_y = 67.0f * vscale * 0.5f;

	xpos = center_x + size_x * vscale -20;
	ypos = 67;
	HUD_Rando_SPRITE.p.x = xpos;
	HUD_Rando_SPRITE.p.y = ypos;
	

	HUD_Rando_SPRITE.sx = 1 + ActionButtonAlpha;
	njDrawSprite2D_ForcePriority(&HUD_Rando_SPRITE, CmnHudSprite_SA2ActionBody, -1.501, NJD_SPRITE_ALPHA);
	HUD_Rando_SPRITE.sx = 1;
	HUD_Rando_SPRITE.p.x = xpos + ypos;
	HUD_Rando_SPRITE.p.y = ypos + 5;

	njDrawSprite2D_ForcePriority(&HUD_Rando_SPRITE, CmnHudSprite_SA2ActionButton, -1.501, NJD_SPRITE_ALPHA);
	HUD_Rando_SPRITE.p.x = xpos - 5;


	if (ActionButtonAlpha >= 1) {
		njDrawSprite2D_ForcePriority(&HUD_Rando_SPRITE, CmnHudSprite_SA2Action, -1.501, NJD_SPRITE_ALPHA);
	}
}


void Hud_DisplayOnframe() {

	ObjectMaster* P1 = GetCharacterObject(0);

	if (GameState == 15 && isAIActive && isAIAllowed && SwapDelay > 149)
	{
		if (P1 != nullptr && (P1->Data1->Action == 1 || P1->Data1->Action == 2))
			Hud_ShowActionButton();
	}
}



//This is where all the AI is managed: loading and bug fixes. //Using a part of Charsel mod by MainMemory, otherwise that wouldn't be possible.

ObjectFuncPtr charfuncs[] = {
	Sonic_Main,
	Eggman_Main,
	Tails_Main,
	Knuckles_Main,
	Tikal_Main,
	Amy_Main,
	Gamma_Main,
	Big_Main
};

ObjectMaster* CurAI = nullptr;

ObjectMaster* LoadCharObj(int i)
{
	//setup AI correctly

	CurAI = LoadObject((LoadObj)(LoadObj_UnknownA | LoadObj_Data1 | LoadObj_Data2), 1, charfuncs[CurrentAI]);
	CurAI->Data1->CharID = CurrentAI;
	CurAI->Data1->CharIndex = (char)1;
	EntityData1Ptrs[1] = (EntityData1*)CurAI->Data1;
	EntityData2Ptrs[1] = (EntityData2*)CurAI->Data2;
	return CurAI;
}

int CheckTailsAI_R(void) { //restriction and bug fixes.
	if (CurrentAI == -1 || CurrentCharacter >= Characters_Gamma || CurrentCharacter == Characters_Sonic && MetalSonicFlag != 0 || CurrentCharacter == Characters_Knuckles)
	{
		isAIActive = false;
		return 0;
	}

	if (CurrentCharacter == CurrentAI)
	{
		isAIActive = false;
		return 0;
	}

	if (CurrentLevel > 25 && CurrentLevel < 38)
	{
		isAIActive = false;
		return 0;
	}

	if (Race)
	{
		isAIActive = false;
		return 0;
	}

	switch (CurrentLevel)
	{
		case LevelIDs_SpeedHighway: //crash
			if (CurrentAct == 1)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_FinalEgg: //cutscene issue
			if (CurrentCharacter == Characters_Amy)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_Casinopolis:
			if (CurrentAct >= 1 || CurrentAct == 0 && CurrentLevelLayout < 1 && (CurrentAI == Characters_Amy || CurrentCharacter == Characters_Amy)) //cutscene + pinball issue
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_HotShelter: //issue with handle
			if (CurrentAct <= 1)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_Chaos0: //Crash if character is swap with AI
		{
			isAIActive = false;
			return 0;
		}
		break;
		case LevelIDs_Chaos2: //Potential cutscene crash
			if (CurrentCharacter == Characters_Knuckles)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_Chaos6: //Potential cutscene crash
			if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Knuckles || CurrentCharacter == Characters_Sonic)
			{
				isAIActive = false;
				return 0;
			}
			break;
		case LevelIDs_PerfectChaos: //AI makes the fight a lot harder.
		{
			isAIActive = false;
			return 0;
		}
		break;
		case LevelIDs_EggViper: //Potential cutscene crash + fight harder
		{
			isAIActive = false;
			return 0;
		}
		break;
		case LevelIDs_TwinklePark:
		{
			isAIActive = false;
			return 0;
		}
		break;
		case LevelIDs_LostWorld: //cutscene crash
		{
			if (CurrentAct == 2 && CurrentCharacter == Characters_Sonic)
			{
				isAIActive = false;
				return 0;
			}
		}
		break;
		case LevelIDs_SkyDeck:  //cutscene crash
		{
			if (CurrentAct == 2 && CurrentCharacter == Characters_Knuckles)
			{
				isAIActive = false;
				return 0;
			}

			if (CurrentAct < 2 && !TreasureHunting && (CurrentAI == Characters_Amy || CurrentCharacter == Characters_Amy)) 
			{
				isAIActive = false;
				return 0;
			}
			break;
		}
		break;
		case LevelIDs_SandHill:  //cutscene crash
		{
			if (CurrentCharacter == Characters_Tails)
			{
				isAIActive = false;
				return 0;
			}
		}
		break;
		case LevelIDs_EggWalker:  //Character swap is broken in this fight
		{
			isAIActive = false;
			return 0;
		}
		break;
		default:
			isAIActive = true;
			return 1;
			break;
	}

	isAIActive = true;
	return 1;
}

ObjectMaster* Load2PTails_r(ObjectMaster* player1) //Custom AI
{
	FlagAI = CheckTailsAI_R();

	if (FlagAI != 1)
	{
		isAIActive = false;
		return (ObjectMaster*)0x0;
	}
	else
	{
		ObjectMaster* v1 = LoadObject(LoadObj_Data1, 0, TailsAI_Main); //load AI moveset (basically?)
		TailsAI_ptr = v1;

		if (v1)
		{
			v1->Data1->CharID = (char)CurrentAI;
			v1->Data1->CharIndex = 1;
			v1->DeleteSub = TailsAI_Delete;

			ObjectMaster* v3 = LoadCharObj(1); //load AI

			v3->Data1->Position.x = v1->Data1->Position.x - njCos(v1->Data1->Rotation.y) * 30;
			v3->Data1->Position.y = v1->Data1->Position.y;
			v3->Data1->Position.z = v1->Data1->Position.z - njSin(v1->Data1->Rotation.y) * 30;
			v3->Data1->Action = 0;
			dword_3B2A304 = 0;

			return v3;
		}
	}

	isAIActive = false;
	return (ObjectMaster*)0x0;
}
//}

ObjectMaster* Load2PTails_Original(ObjectMaster* player1) //Original AI (Tails only)
{
	FlagAI = CheckTailsAI_R();

	if (FlagAI != 1)
	{
		isAIActive = false;
		return (ObjectMaster*)0x0;
	}
	else
	{
		if (CurrentCharacter == Characters_Sonic)
		{
			CurrentAI = Characters_Tails; //don't rand, just set tails AI

			ObjectMaster* v1 = LoadObject(LoadObj_Data1, 0, TailsAI_Main); //load AI moveset (basically?)
			TailsAI_ptr = v1;

			if (v1)
			{
				v1->Data1->CharID = (char)CurrentAI;
				v1->Data1->CharIndex = 1;
				v1->DeleteSub = TailsAI_Delete;

				ObjectMaster* v3 = LoadCharObj(1); //load AI

				v3->Data1->Position.x = v1->Data1->Position.x - njCos(v1->Data1->Rotation.y) * 30;
				v3->Data1->Position.y = v1->Data1->Position.y;
				v3->Data1->Position.z = v1->Data1->Position.z - njSin(v1->Data1->Rotation.y) * 30;
				v3->Data1->Action = 0;
				dword_3B2A304 = 0;

				return v3;
			}
		}
	}

	isAIActive = false;
	return (ObjectMaster*)0x0;
}

//SFX characters ai fixes.

void FixAISFXSonic() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Sonic && isAIActive)
				return;
		}
	}

	PlaySound(0x2fa, 0, 0, 0);
	return;
}

void FixAISFXSonic2() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Sonic && isAIActive)
				return;
		}
	}

	if (CurrentCharacter != Characters_Sonic && Race)
		return;

	PlaySound(0x11, 0, 0, 0);
	return;
}

void FixAISFXSonic3() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Sonic && isAIActive)
				return;
		}
	}

	if (CurrentCharacter != Characters_Sonic && Race)
		return;

	PlaySound(0x12, 0, 0, 0);
	return;
}

void FixAISFXSonic4() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Sonic && isAIActive)
				return;
		}
	}

	if (CurrentCharacter != Characters_Sonic && Race)
		return;

	PlaySound(0x4d1, 0, 0, 0);
	return;
}

void FixShowerCasino() {
	if (isAIActive)
		return;

	ForcePlayerAction(0, 0x28); //Shower
}

void FixAISFXJump() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Knuckles || GetChara->Data1->CharID == Characters_Tails || GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}
	PlaySound(0x11, 0, 0, 0);
	return;
}

void FixAISFXAmy() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	if (Race && CurrentCharacter != Characters_Amy)
		return;

	PlaySound(0x31d, 0, 0, 0);
}

void FixAISFXAmy2() { //jump sound
	if (isAIActive && !Race)
	{
		//ObjectMaster* GetChara = GetCharacterObject(0);
		//GetChara->Data1->CharID;

		ObjectMaster* GetAI = GetCharacterObject(1);
		GetAI->Data1->CharID;

		if (GetAI != nullptr)
		{
			if (GetAI->Data1->CharID == Characters_Amy) //|| GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	if (Race && CurrentCharacter != Characters_Amy)
		return;

	PlaySound(0x4ff, 0, 0, 0);
}

void FixAISFXAmy3() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	PlaySound(0x500, 0, 0, 0);
}

void FixAISFXAmy4() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	if (Race && CurrentCharacter != Characters_Amy)
		return;

	PlaySound(0x506, 0, 0, 0);
}

void FixAISFXAmy5() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(1);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	if (EventFlagArray[EventFlags_Amy_LongHammer] == 1)
		PlaySound(0x31d, 0, 0, 0); //long hammer sound
	else
		PlaySound(0x31c, 0, 0, 0); //hammer sound
}

void FixAISFXAmy6() {
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(0);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	PlaySound(0x508, 0, 0, 0);
}

void FixAISFXAmy7() { //spin dash noise when you press B
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(0);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	if (Race && CurrentCharacter != Characters_Amy)
		return;

	if (EventFlagArray[EventFlags_Amy_LongHammer] == 1)
		PlaySound(0x31d, 0, 0, 0); //long hammer sound
	else
		PlaySound(0x31c, 0, 0, 0); //hammer sound
}

void FixAISFXAmy8() { //spin dash noise when you press B
	if (isAIActive && !Race)
	{
		ObjectMaster* GetChara = GetCharacterObject(0);
		GetChara->Data1->CharID;

		if (GetChara != nullptr)
		{
			if (GetChara->Data1->CharID == Characters_Amy)
				return;
		}
	}

	PlaySound(0x509, 0, 0, 0);
}

bool isZeroActive = false;

void FixAISFXGamma() { 

	if (Race && CurrentCharacter != Characters_Gamma || isZeroActive)
		return;

	PlaySound(0x33b, 0, 0, 0);

	return;
}

void FixAISFXGamma2() { 

	if (Race && CurrentCharacter != Characters_Gamma || isZeroActive)
		return;

	PlaySound(0x33d, 0, 0, 0);

	return;
}

void FixAISFXGamma3() {

	if (Race && CurrentCharacter != Characters_Gamma)
		return;

	PlaySound(0x33e, 0, 0, 0);

	return;
}

void FixAISFXGamma4() {

	if (Race && CurrentCharacter != Characters_Gamma)
		return;

	PlaySound(0x33f, 0, 0, 0);

	return;
}


//Result Voice FIX
void ResultVoiceFix() {
	ObjectMaster* GetChara = GetCharacterObject(0);
	GetChara->Data1->CharID;

	if (GetChara != nullptr)
	{
		switch (GetChara->Data1->CharID)
		{
		case Characters_Sonic:
			if (MetalSonicFlag == 0) {
				if ((short)CurrentLevel < 0xf) {
					Load_DelayedSound_Voice(1840);
				}
				else {
					Load_DelayedSound_Voice(1843);
				}
			}
			else {
				PlayVoice(0x7fc);
			}
			break;
		case Characters_Eggman:
			Load_DelayedSound_Voice(4012);
			break;
		case Characters_Tails:
			Load_DelayedSound_SFX(0x5b2);
			break;
		case Characters_Knuckles:
			if (CurrentLevel < 15)
				Load_DelayedSound_SFX(0x5a5);
			else
				Load_DelayedSound_SFX(0x5a8);
			break;
		case Characters_Amy:
		if (CurrentLevel >= LevelIDs_Chaos0)
			Load_DelayedSound_Voice(1735);
		else
			Load_DelayedSound_Voice(1733);
			break;
		case Characters_Big:
			if (CurrentLevel == LevelIDs_HedgehogHammer || CurrentLevel >= LevelIDs_Chaos0 || CurrentLevelLayout >= Mission2_100Rings || CurrentStageVersion == GammaFE || TreasureHunting)
				Load_DelayedSound_Voice(4011);
			else
				Load_DelayedSound_Voice(4010);
			SoundManager_Delete2();
			TreasureHunting = false;
			break;
		}
	}
}

FunctionPointer(void, sub_43FA90, (EntityData1* a1, CharObj2** a2, CharObj2* a3), 0x43FA90);

void __cdecl CheckDeleteAnimThing(EntityData1* a1, CharObj2** a2, CharObj2* a3)
{
	for (int i = 0; i < 8; i++)
		if (EntityData1Ptrs[i] && EntityData1Ptrs[i] != a1 && EntityData1Ptrs[i]->CharID == a1->CharID)
			return;
	sub_43FA90(a1, a2, a3);
}

CollisionInfo* oldcol = nullptr;

extern ObjectMaster* CurrentCart;

void AISwitch() {

	if (!isAIAllowed || CurrentAI == CurrentCharacter)
	{
		isAIActive = false;
		return;
	}

	if (CurrentLevel == LevelIDs_TwinklePark && CurrentAct == 0 || CurrentLevel == LevelIDs_EggWalker)
	{
		isAIActive = false;
		return;
	}

	if (CurrentAI == Characters_Tikal || CurrentAI == Characters_Eggman)
		if (CurrentLevel > 14 && CurrentLevel < 26)
			return;

	if (Rings >= 100 && CurrentLevelLayout == Mission2_100Rings || TreasureHunting && KnuxCheck >= 3 && CurrentCharacter != Characters_Knuckles)
		return;

	if (CurrentCart)
		return;

	if (SonicRand == 0 && isAIActive) //don't allow the swap if metal sonic / super sonic 
	{
		//initialize swap, taking actual character and ai information

		if (CurrentCharacter <= 5 && CurrentAI <= 5)
		{
			AISwap = GetCharacter0ID();
			CharaSwap = GetCharacter1ID();

			ObjectMaster* obj = GetCharacterObject(0);
			char P1Action = obj->Data1->Action;
			CharObj2* obj2 = ((EntityData2*)obj->Data2)->CharacterData;

			if (obj != nullptr && obj2 != nullptr)
			{
				if (P1Action > 15)
					return;

				short powerups = obj2->Powerups;
				short jumptime = obj2->JumpTime;
				short underwatertime = obj2->UnderwaterTime;
				float loopdist = obj2->LoopDist;
				NJS_VECTOR speed = obj2->Speed;
				ObjectMaster* heldobj = obj2->ObjectHeld;

				AISwapCount++; //Credit stat
				//Display Character swap.
				obj->DeleteSub(obj);
				obj->MainSub = charfuncs[CharaSwap];
				obj->Data1->CharID = (char)CharaSwap;

				//Play voice switch
				switch (obj->Data1->CharID)
				{
				case Characters_Sonic:
					if (MetalSonicFlag)
						LoadSoundList(62);
					else
					{
						PlayCustomSound(CommonSound_SonicSwap);
						LoadSoundList(1);
					}

					if (VoiceLanguage)
						LoadSoundList(72);
					else
						LoadSoundList(71);
					break;
				case Characters_Eggman:
						PlayCustomSound(CommonSound_EggmanSwap);
					break;
				case Characters_Tails:
					PlayCustomSound(CommonSound_TailsSwap);
					LoadSoundList(1);
					if (VoiceLanguage)
						LoadSoundList(72);
					else
						LoadSoundList(71);
					break;
				case Characters_Knuckles:
					PlayCustomSound(CommonSound_KnuxSwap);
					LoadSoundList(49);
					if (VoiceLanguage)
						LoadSoundList(70);
					else
						LoadSoundList(69);
					break;
				case Characters_Amy:
					PlayCustomSound(CommonSound_AmySwap);
					LoadSoundList(46);
					if (VoiceLanguage)
						LoadSoundList(64);
					else
						LoadSoundList(63);
					break;
				}

				obj->Data1->Action = 0;
				obj->Data1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);
				if (!oldcol)
				{
					oldcol = obj->Data1->CollisionInfo;
					obj->Data1->CollisionInfo = nullptr;
				}
				else
					Collision_Free(obj);
				
				obj->MainSub(obj);
				obj2 = ((EntityData2*)obj->Data2)->CharacterData;
				obj2->Powerups = powerups;
				obj2->JumpTime = jumptime;
				obj2->UnderwaterTime = underwatertime;
				obj2->LoopDist = loopdist;
				obj2->Speed = speed;
				obj2->ObjectHeld = heldobj;

				//initialize swap, taking AI information
				ObjectMaster* AI = GetCharacterObject(1);
				CharObj2* AI2 = ((EntityData2*)obj->Data2)->CharacterData;

				if (AI != nullptr && AI2 != nullptr)
				{
					short AIpowerups = AI2->Powerups;
					short AIjumptime = AI2->JumpTime;
					short AIunderwatertime = AI2->UnderwaterTime;
					float AIloopdist = AI2->LoopDist;
					NJS_VECTOR AIspeed = AI2->Speed;
					ObjectMaster* AIheldobj = AI2->ObjectHeld;
					//Display AI swap.
					AI->MainSub = charfuncs[AISwap];
					AI->Data1->CharID = (char)AISwap;
					AI->Data1->Action = 0;
					AI->Data1->Status &= ~(Status_Attack | Status_Ball | Status_LightDash | Status_Unknown3);
					if (!oldcol)
					{
						oldcol = AI->Data1->CollisionInfo;
						AI->Data1->CollisionInfo = nullptr;
					}
					else
						Collision_Free(AI);
					AI->MainSub(AI);
					AI2 = ((EntityData2*)AI->Data2)->CharacterData;
					AI2->Powerups = powerups;
					AI2->JumpTime = jumptime;
					AI2->UnderwaterTime = underwatertime;
					AI2->LoopDist = loopdist;
					AI2->Speed = speed;
					AI2->ObjectHeld = heldobj;

					SwapDelay = 0;
				}
			}
		}
	}

	return;
}

//Load AI

void LoadTails_AI_R() {
	if (CreditCheck != true)
	{
		if (Race == false && isAIAllowed)
		{
			ObjectMaster* obj;
			obj = GetCharacterObject(0);
			ObjectMaster* lastobj = obj;
			ObjectMaster* o2 = nullptr;
			o2 = Load2PTails_r(obj);
		}
	}

	return;
}

void LoadTails_AI_Original() {
	if (CreditCheck != true)
	{
		if (!Race && !isAIAllowed)
		{
			ObjectMaster* obj;
			obj = GetCharacterObject(0);
			ObjectMaster* lastobj = obj;
			ObjectMaster* o2 = nullptr;
			o2 = Load2PTails_Original(obj);
		}
	}

	return;
}



void AIAudioFixes() {
	WriteCall((void*)0x5cf22f, FixShowerCasino); //Prevent crash after chara swap

	//(there is probably a nicer way to do this, but I have no clue how)

	WriteCall((void*)0x494be7, FixAISFXSonic); //fix sonic AI homing attack sound
	WriteCall((void*)0x495eaa, FixAISFXSonic2); //fix sonic jump sound
	WriteCall((void*)0x4972c2, FixAISFXSonic3); //fix sonic sfx
	WriteCall((void*)0x492f08, FixAISFXSonic4); //fix sonic sfx hurt

	WriteCall((void*)0x4768ea, FixAISFXJump); //Fix Jump Tails & Knuckles AI sound

	WriteCall((void*)0x487793, FixAISFXJump); //Fix Amy AI Jump
	WriteCall((void*)0x48af5f, FixAISFXAmy);
	WriteCall((void*)0x4877a3, FixAISFXAmy2);
	WriteCall((void*)0x485023, FixAISFXAmy3);
	WriteCall((void*)0x48b08b, FixAISFXAmy4);
	WriteCall((void*)0x489a75, FixAISFXAmy5);
	WriteCall((void*)0x485844, FixAISFXAmy6);
	WriteCall((void*)0x48947c, FixAISFXAmy7);
	WriteCall((void*)0x4857e0, FixAISFXAmy8);

}

//Reset value when AI is deleted
void AI_ResetValue() {
	isAIActive = false;
	DeleteObject_(CurAI);
	return FUN_0042ce20();
}

void AI_FixesOnFrames() {

	if (!IsGamePaused() && oldcol)
	{
		if (HIBYTE(oldcol->Flags) & 0x80)
		{
			if (oldcol->CollisionArray)
			{
				FreeMemory(oldcol->CollisionArray);
				oldcol->CollisionArray = nullptr;
			}
		}
		FreeMemory(oldcol);
		oldcol = nullptr;
	}
}

void __cdecl AI_Init(const HelperFunctions& helperFunctions, const IniFile* config) {

	WriteData<5>((void*)0x415948, 0x90); //remove the original load2PTails in LoadCharacter as we use a custom one.

	if (isAIAllowed)
	{
		WriteCall((void*)0x47ed8e, CheckTailsAI_R);
		WriteCall((void*)0x47e943, CheckTailsAI_R);
		WriteCall((void*)0x47ea46, CheckTailsAI_R);
		WriteCall((void*)0x47ec62, CheckTailsAI_R);
		WriteJump((void*)0x47db1a, AI_ResetValue);
		AIAudioFixes();
		helperFunctions.RegisterCommonObjectPVM(Hud_Rando);
	}

}