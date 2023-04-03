#include "stdafx.h"

PVMEntry SSTex = { "SUPERSONIC", &SUPERSONIC_TEXLIST };
//Initialize Super Sonic Physic and Aura when Perfect Chaos fight starts for other characters.
void SuperAuraStuff() 
{
	TimeThing = 0;

	if (CurrentCharacter != Characters_Sonic)
	{
		CharObj2Ptrs[0]->Upgrades |= Upgrades_SuperSonic;
		CharObj2Ptrs[0]->Powerups |= Powerups_Invincibility;
		LoadObject((LoadObj)2, 2, Sonic_SuperAura_Load);
		LoadObject((LoadObj)8, 2, Sonic_SuperPhysics_Load);
	}

}

uint8_t SSLevel[] = { 
	LevelIDs_TwinklePark, LevelIDs_SpeedHighway, LevelIDs_TwinkleCircuit, LevelIDs_Casinopolis,
LevelIDs_SkyDeck, LevelIDs_EggViper, LevelIDs_SandHill, LevelIDs_HotShelter, LevelIDs_IceCap, LevelIDs_Chaos6 
};


int GetSSLevelBanned() {

	for (uint8_t i = 0; i < LengthOfArray(SSLevel); i++)
	{
		if (CurrentLevel == SSLevel[i])
		{
			switch (CurrentLevel)
			{
			case LevelIDs_TwinklePark:
				if (CurrentAct == 1 && CurrentStageVersion != AmyVersion || CurrentAct == 0)
					return true;
				break;
			case LevelIDs_SpeedHighway:
				if (CurrentAct == 0 && CurrentStageVersion != TailsVersion)
					return true;
				break;
			case LevelIDs_Casinopolis:
				if (CurrentAct == 0 && CurrentStageVersion == KnucklesVersion)
					return false;
				else
					return true;
				break;
			case LevelIDs_IceCap:
				return true;
				break;
			case LevelIDs_HotShelter:
				if (CurrentAct < 2)
					return true;
				break;
			default:
				return true;
			}
		}
	}

	return false;
}



void SuperSonic_TransformationCheck() 
{

	const bool isLevelBanned = GetSSLevelBanned();

	if (isLevelBanned || MetalSonicFlag == 1 || SonicRand != 2)
	{
		SonicRand = 0;
		return;
	}
	else
	{

		if (!Rings)
			Rings = 1;

		EntityData1* data1 = EntityData1Ptrs[0];
		CharObj2* data2 = CharObj2Ptrs[0];

		bool transformation = (data2->Upgrades & Upgrades_SuperSonic) != 0;

		//Super Sonic Transformation (Credit: SonicFreak94).
		if (!transformation)
		{
			data1->Status &= ~Status_LightDash;
			ForcePlayerAction(0, 46);
			PlayVoice(3001);
			PlayMusic(MusicIDs_ThemeOfSuperSonic);
		}

		SuperSonicFlag = 1;
		return;
	}
}

uint8_t prev_Sanic = -1;
uint8_t GetRandomSonicTransfo(uint8_t char_id) {

	int8_t cur_Sanic = -1;

	if (char_id == Characters_Sonic) 
	{
		do {

			cur_Sanic = rand() % 3;
		} while (cur_Sanic == prev_Sanic || MetalSonic && cur_Sanic == 1 || SuperSonic && cur_Sanic == 2);
	}

	prev_Sanic = cur_Sanic;
	return cur_Sanic;
}

void initSuperSonicSettings() 
{
	//Super Sonic Stuff
	WriteCall((void*)0x560388, SuperAuraStuff); //Initialize Super Sonic physic and aura when perfect chaos fight starts.

	HMODULE SSMod = GetModuleHandle(L"sadx-super-sonic");
	HMODULE SSMod2 = GetModuleHandle(L"better-super-sonic");

	if (SSMod || SSMod2)
		return;

	help.RegisterCharacterPVM(Characters_Sonic, SSTex);
	WriteData<2>(reinterpret_cast<Uint8*>(0x0049AC6A), 0x90i8); //Always initialize Super Sonic weld data.
	WriteData<7>(reinterpret_cast<Uint8*>(0x00494E13), 0x90i8); // Fix Super Sonic position when completing a stage.
	WriteJump(reinterpret_cast<void*>(0x4879c7), (void*)0x4879CE); //Always initialize Super Sonic weld data.
}